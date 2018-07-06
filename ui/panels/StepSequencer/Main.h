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

#ifndef StepSequencerPanel_h
#define StepSequencerPanel_h


#endif /* StepSequencerPanel_h */

#include "Buttons.h"
#include "Slider.h"
#include "UtilityButtons.h"

struct StepSequencerPanel : public Component {
  StepSequencerPanel(SynthAudioProcessor& p) : processor(p), panelButtons(p) {
    addAndMakeVisible(panelSlider);
    addAndMakeVisible(panelButtons);
    addAndMakeVisible(panelUtility);

    panelUtility.onRandomize = [&](int i) {
      panelButtons.stepButtonRows[i]->toggleRandomizeAll();
    };
    panelUtility.onClear = [&](int i) {
      panelButtons.stepButtonRows[i]->toggleClearAll();
    };
    panelUtility.onSetAll = [&](int i) {
      panelButtons.stepButtonRows[i]->toggleSetAll();
    };

    panelSlider.setOnValueChange([&]() {
      p.globalStepCount = panelSlider.getValue();
      repaint();
    });
  }

  void paint (Graphics& g) override {
    g.fillAll(Colour(45, 48, 71));
  }


  void paintOverChildren(Graphics& g) override {
    auto panelButtonsBounds = panelButtons.getBoundsInParent();
    auto panelUtilityButtonsBounds = panelUtility.getBoundsInParent();

    for (auto i = 0; i < processor.globalStepCount; i++) {
      auto* buttonRow = panelButtons.stepButtonRows[i];
      auto* utilityButtonRow = panelUtility.utilityButtonsRow[i];
      buttonRow->setInterceptsMouseClicks(true, true);
      utilityButtonRow->setInterceptsMouseClicks(true, true);
    }

    for (auto i = processor.globalStepCount; i < panelButtons.stepButtonRows.size(); i++) {
      auto* buttonRow = panelButtons.stepButtonRows[i];
      auto buttonRowBounds = buttonRow->getBoundsInParent();
      g.setColour(Colour(0, 0, 0));
      g.setOpacity(0.7);
      g.fillRect(
        panelButtonsBounds.getX(),
        buttonRowBounds.getY(),
        buttonRowBounds.getWidth(),
        buttonRowBounds.getHeight()
      );
      buttonRow->setInterceptsMouseClicks(false, false);

      auto* utilityButtonRow = panelUtility.utilityButtonsRow[i];
      auto utilityButtonRowBounds = utilityButtonRow->getBoundsInParent();
      g.setColour(Colour(0, 0, 0));
      g.setOpacity(0.7);
      g.fillRect(
        panelUtilityButtonsBounds.getX(),
        utilityButtonRowBounds.getY(),
        utilityButtonRowBounds.getWidth(),
        utilityButtonRowBounds.getHeight()
      );
      utilityButtonRow->setInterceptsMouseClicks(false, false);
    }

    auto* buttonRow = panelButtons.stepButtonRows[processor.currentGlobalStep];
    auto buttonRowBounds = buttonRow->getBoundsInParent();
    g.setColour(Colour(0, 255, 0));
    g.setOpacity(0.4);
    g.fillRect(
        panelButtonsBounds.getX(),
        buttonRowBounds.getY(),
        buttonRowBounds.getWidth(),
        buttonRowBounds.getHeight()
        );
    
    auto* utilityButtonRow = panelUtility.utilityButtonsRow[processor.currentGlobalStep];
    auto utilityButtonRowBounds = utilityButtonRow->getBoundsInParent();
    g.setColour(Colour(0, 255, 0));
    g.setOpacity(0.4);
    g.fillRect(
        panelUtilityButtonsBounds.getX(),
        utilityButtonRowBounds.getY(),
        utilityButtonRowBounds.getWidth(),
        utilityButtonRowBounds.getHeight()
        );
  }

  void resized() override {
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { Track (1_fr) };
    grid.templateColumns = { Track (1_fr), Track (8_fr), Track (1_fr) };

    grid.items = { GridItem (panelSlider), GridItem(panelButtons), GridItem (panelUtility) };

    grid.performLayout (getLocalBounds());
  }

private:
  StepSequencerPanelButtons panelButtons;
  StepSequencerPanelSlider panelSlider;
  StepSequencerPanelUtility panelUtility;
  SynthAudioProcessor& processor;
};
