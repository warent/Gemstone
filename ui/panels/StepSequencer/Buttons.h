//
//  StepSequencerPanelButtons.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef StepSequencerPanelButtons_h
#define StepSequencerPanelButtons_h


#endif /* StepSequencerPanelButtons_h */

#include "ButtonRow.h"

struct StepSequencerPanelButtons : public Component {
  StepSequencerPanelButtons(SynthAudioProcessor& p) : processor(p) {
    for (auto i = 0; i < 16; i++) {
        addAndMakeVisible(stepButtonRows.add(new StepSequencerButtonRow(i, p)));
    }
  }

  void paint (Graphics& g) override {
    g.fillAll(Colour(45, 48, 71));
  }

  void resized() override {
    Grid grid;

    using Track = Grid::TrackInfo;

    Array<FlexBox> flexRows;

    FlexBox fb(
      FlexBox::Direction::column,
      FlexBox::Wrap::noWrap,
      FlexBox::AlignContent::center,
      FlexBox::AlignItems::center,
      FlexBox::JustifyContent::flexStart);
    for (auto* buttonRow : stepButtonRows) {
      fb.items.add(FlexItem(*buttonRow).withHeight(32.0f).withMinWidth(getLocalBounds().getWidth()));
    }
    fb.performLayout(getLocalBounds());
  }

OwnedArray<StepSequencerButtonRow> stepButtonRows;
protected:
  SynthAudioProcessor& processor;
};