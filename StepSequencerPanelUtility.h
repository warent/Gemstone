//
//  StepSequencerPanelUtility.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef StepSequencerPanelUtility_h
#define StepSequencerPanelUtility_h


#endif /* StepSequencerPanelUtility_h */

#include "StepSequencerImageButtonRow.h"

struct StepSequencerPanelUtility : public Component {
  StepSequencerPanelUtility() {
    for (auto i = 0; i < 16; i++) {
        addAndMakeVisible(stepButtonRows.add(new StepSequencerImageButtonRow(i)));
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

private:
  OwnedArray<StepSequencerImageButtonRow> stepButtonRows;
};