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
    : AudioProcessorEditor (&p), processor (p), stepSequencerPanel(p), tabsGemSettings(TabbedButtonBar::Orientation::TabsAtTop)
{
    getLookAndFeel().setColour(ResizableWindow::backgroundColourId, Colour(224, 202, 60));
    addAndMakeVisible(gemsPanel);
    addAndMakeVisible(stepSequencerPanel);
    addAndMakeVisible(adsrPanel);

    adsrPanel.onAttackChange([&]() {
        p.attackTime = adsrPanel.sliderAttack.getValue();
    });

    adsrPanel.onDecayChange([&]() {
        p.decayTime = adsrPanel.sliderAttack.getValue();
    });

    adsrPanel.onReleaseChange([&]() {
        p.releaseTime = adsrPanel.sliderAttack.getValue();
    });

    setSize(768, 576);
    
    p.addChangeListener(this);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (Graphics& g)
{
    auto bounds = getLocalBounds();

    // FillType ft;
    // ft.setGradient(ColourGradient(Colour(72,85,99), 0, 0, Colour(41,50,60), bounds.getWidth(), bounds.getHeight(), true));

    // g.setFillType(ft);
    g.fillAll(Colour(72,85,99));
    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void SynthAudioProcessorEditor::resized()
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { Track (5_fr), Track (5_fr), Track (12_fr) };
    grid.templateColumns = { Track (1_fr) };

    grid.items = { GridItem (gemsPanel).withMargin(10), GridItem(adsrPanel).withMargin(10), GridItem (stepSequencerPanel).withMargin(10) };

    grid.performLayout (getLocalBounds());
}

void SynthAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster* source) {
    repaint();
}
