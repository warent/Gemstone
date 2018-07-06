/*
 ==============================================================================
 Gemstone, a polyphonic step-sequenced sound synthesizer.
 Copyright (C) 2018 Wyatt Arent
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.
 
 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ==============================================================================
 */

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
            synths[i][j].addVoice(new SineWaveVoice(*this));
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

    std::map<int, bool> processedSynthId;
    std::map<int, bool> processedSoundId;
    
    MidiBuffer::Iterator it(midiMessages);
    while (it.getNextEvent(midi, samplePosition)) {
        String midiNoteName = midi.getMidiNoteName(midi.getNoteNumber(), true, true, 4);
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
            
            sendChangeMessage();

            if (selectedSynthId == -1) {
                continue;
            }
            
            processedSynthId[selectedSynthId] = true;
            processedSoundId[selectedSoundId] = true;
            auto singleBuffer = MidiBuffer(midi);
            synths[selectedSynthId][selectedSoundId].renderNextBlock(buffer, singleBuffer, 0, buffer.getNumSamples());
            synthIsActive[selectedSynthId][selectedSoundId] = midiNoteName;
            midiNoteToSynth[midiNoteName] = std::pair<int, int>(selectedSynthId, selectedSoundId);
            
        } else if (isNoteOff) {
            auto gemId = midiNoteToSynth[midiNoteName].first;
            auto soundId = midiNoteToSynth[midiNoteName].second;
            if (synthIsActive[gemId][soundId] != midiNoteName) {
                continue;
            }
            processedSynthId[gemId] = true;
            processedSoundId[soundId] = true;
            auto singleBuffer = MidiBuffer(midi);
            synths[gemId][soundId].renderNextBlock(buffer, singleBuffer, 0, buffer.getNumSamples());
        }
    }

    midiMessages.clear();

    for (auto synthId = 0; synthId < 8; synthId++) {
        for (auto soundId = 0; soundId < 4; soundId++) {
            if (!processedSynthId[synthId]) {
                synths[synthId][soundId].renderNextBlock(buffer, MidiBuffer(), 0, buffer.getNumSamples());
            }
        }
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
