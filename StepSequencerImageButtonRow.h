//
//  StepSequencerImageButtonRow.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef StepSequencerImageButtonRow_h
#define StepSequencerImageButtonRow_h


#endif /* StepSequencerImageButtonRow_h */

#pragma once

struct StepSequencerImageButtonRow : public Component {
  StepSequencerImageButtonRow(int id) {
    isOddRow = id % 2 > 0;
    rowId = id;
    String idToName[3] = {"r", "a", "x"};
    for (auto i = 0; i < 3; i++) {
        auto ib = imageButtons.add(new TextButton(idToName[i]));
        addAndMakeVisible(ib);
    }
  }

  void paint (Graphics& g) override {
    if (isOddRow) {
      g.fillAll(Colour(185, 185, 185));
    } else {
      g.fillAll(Colour(155, 155, 155));
    }
  }

  void resized() override {
    Array<FlexBox> flexRows;

    FlexBox fb(
      FlexBox::Direction::row,
      FlexBox::Wrap::noWrap,
      FlexBox::AlignContent::center,
      FlexBox::AlignItems::center,
      FlexBox::JustifyContent::spaceAround);
    for (auto* button : imageButtons) {
      fb.items.add(FlexItem(*button).withWidth(16.0f).withHeight(16.0f));
    }
    fb.performLayout(getLocalBounds());
  }

private:
  OwnedArray<TextButton> imageButtons;
  bool isOddRow;
  int rowId;
};
