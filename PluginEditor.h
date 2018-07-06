/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ui/panels/Gems/Main.h"
#include "ui/panels/ADSR/Main.h"
#include "ui/panels/StepSequencer/Main.h"

//==============================================================================
/**
*/
class SynthAudioProcessorEditor  : public AudioProcessorEditor, public ChangeListener
{
public:
    SynthAudioProcessorEditor (SynthAudioProcessor&);
    ~SynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void changeListenerCallback(ChangeBroadcaster*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthAudioProcessor& processor;
    GemsPanel gemsPanel;
    StepSequencerPanel stepSequencerPanel;
    TabbedComponent tabsGemSettings;
    ADSRPanel adsrPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioProcessorEditor)
};
