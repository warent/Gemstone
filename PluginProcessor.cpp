#include <random>

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "synth/SineWave.h"

//==============================================================================
SynthAudioProcessor::SynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
        #if ! JucePlugin_IsMidiEffect
            #if ! JucePlugin_IsSynth
            .withInput  ("Input",  AudioChannelSet::stereo(), true)
            #endif
        .withOutput ("Output", AudioChannelSet::stereo(), true)
        #endif
        )
#endif
{
    for (auto i = 0; i < 8; i++) {
        for (auto j = 0; j < 4; j++) {
            synths[i][j].addVoice(new SineWaveVoice());
            synths[i][j].addSound(new SineWaveSound());
            synths[i][j].setNoteStealingEnabled(true);
        }
    }

    std::fill_n(synthStepCount, 8, 0);
    std::fill_n(currentSynthStep, 8, 0);

    for (auto i = 0; i < 16; i++) {
        std::fill_n(globalSynthIsActiveInStep[i], 8, false);
    }
}

SynthAudioProcessor::~SynthAudioProcessor()
{
}

//==============================================================================
const String SynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (auto i = 0; i < 8; i++) {
        for (auto j = 0; j < 4; j++) {
            synths[i][j].setCurrentPlaybackSampleRate (sampleRate);
        }
    }
    midiCollector.reset (sampleRate);
}

void SynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    if (globalStepCount == 0) {
        midiMessages.clear();
        return;
    }

    int samplePosition = 0;
    MidiMessage midi;

    Array<std::pair<MidiBuffer, std::pair<int, int>>> midiBufferForSynth;

    MidiBuffer::Iterator it(midiMessages);
    while (it.getNextEvent(midi, samplePosition)) {
        bool isNoteOn = midi.isNoteOn();
        bool isNoteOff = midi.isNoteOff();
        if (isNoteOn) {
            Array<int> synthIds = {};
            for (auto i = 0; i < 8; i++) {
                if (globalSynthIsActiveInStep[currentGlobalStep][i]) {
                    synthIds.add(i);
                }
            }

            auto selectedSynthId = -1;
            auto selectedSoundId = 0;

            if (synthIds.size() > 0) {
                std::mt19937 rng;
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> dist(0,synthIds.size()-1);
                selectedSynthId = synthIds[dist(rng)];
            }
            
            currentGlobalStep += 1;
            if (currentGlobalStep >= globalStepCount) {
                currentGlobalStep = 0;
            }

            if (selectedSynthId == -1) {
                continue;
            }

            midiBufferForSynth.add(std::pair<MidiBuffer, std::pair<int, int>>(MidiBuffer(MidiMessage(midi)), std::pair<int, int>(selectedSynthId, selectedSoundId)));
            
        } else if (isNoteOff) {
            auto gemId = midiNoteToSynth[midi.getNoteNumber()].first;
            auto soundId = midiNoteToSynth[midi.getNoteNumber()].second;
            midiBufferForSynth.add(std::pair<MidiBuffer, std::pair<int, int>>(MidiBuffer(MidiMessage(midi)), std::pair<int, int>(gemId, soundId)));
        }
    }
    
    for (auto item : midiBufferForSynth) {
        auto selectedSynthId = item.second.first;
        auto selectedSoundId = item.second.second;
        auto singleBuffer = item.first;
        synths[selectedSynthId][selectedSoundId].renderNextBlock(buffer, singleBuffer, 0, buffer.getNumSamples());
        midiNoteToSynth[midi.getNoteNumber()] = std::pair<int, int>(selectedSynthId, selectedSoundId);
    }

    midiMessages.clear();
    
    for (auto item : midiNoteToSynth) {
        synths[item.second.first][item.second.second].renderNextBlock(buffer, MidiBuffer(), 0, buffer.getNumSamples());
    }
    
    
}

//==============================================================================
bool SynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthAudioProcessor::createEditor()
{
    return new SynthAudioProcessorEditor (*this);
}

//==============================================================================
void SynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthAudioProcessor();
}
