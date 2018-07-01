//
//  StepSequencerPanel.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef StepSequencerPanel_h
#define StepSequencerPanel_h


#endif /* StepSequencerPanel_h */

#include "StepSequencerPanelButtons.h"
#include "StepSequencerPanelSlider.h"
#include "StepSequencerPanelUtility.h"

struct StepSequencerPanel : public Component {
  StepSequencerPanel(SynthAudioProcessor& p) : processor(p), panelButtons(p) {
    addAndMakeVisible(panelSlider);
    addAndMakeVisible(panelButtons);
    addAndMakeVisible(panelUtility);
  }

  void paint (Graphics& g) override {
    g.fillAll(Colour(45, 48, 71));
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
