/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>

//==============================================================================
/**
*/
class SynthAudioProcessor  : public AudioProcessor, public ChangeBroadcaster
{
public:
    //==============================================================================
    SynthAudioProcessor();
    ~SynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    MidiKeyboardState keyboardState;

    int globalStepCount = 4;
    int currentGlobalStep = 0;
    int synthStepCount[8];
    int currentSynthStep[8];

    // globalSynthIsActiveInStep[stepId][gemId]
    bool globalSynthIsActiveInStep[16][8];

    // [gemId][stepId][soundId]
    bool soundIsActiveInSynthStep[8][16][4];

    /// map<midiNoteNumber, pair<gemId, synthId>>
    std::map<String, std::pair<int, int>> midiNoteToSynth;
    String synthIsActive[8][4];

    double attackTime = 0.05;
    double decayTime = 0.05;
    double sustainLevel = 0;
    double releaseTime = 0.05;

private:
    //==============================================================================
    // synths aka gems
    Synthesiser synths[8][4];
    MidiMessageCollector midiCollector;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessor)
};
