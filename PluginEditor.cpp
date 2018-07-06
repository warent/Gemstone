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
