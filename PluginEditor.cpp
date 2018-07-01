/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    getLookAndFeel().setColour(ResizableWindow::backgroundColourId, Colour(224, 202, 60));
    addAndMakeVisible(squaresPanel);
    setSize(1024, 768);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void SynthAudioProcessorEditor::resized()
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { Track (1_fr), Track (1_fr), Track (1_fr) };
    grid.templateColumns = { Track (1_fr) };

    grid.items = { GridItem (squaresPanel) };

    grid.performLayout (getLocalBounds());
}
