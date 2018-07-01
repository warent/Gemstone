//
//  StepSequencerButtonRow.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef StepSequencerButtonRow_h
#define StepSequencerButtonRow_h


#endif /* StepSequencerButtonRow_h */

#include <map>

#pragma once

struct StepSequencerButtonRow : public Component, Button::Listener {
  StepSequencerButtonRow(int id, int buttonCount = 8) {
    isOddRow = id % 2 > 0;
    for (auto i = 0; i < buttonCount; i++) {
        auto sb = stepButtons.add(new ShapeButton(String(i), Colour(0, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0)));
        Path square;
        square.addRectangle(0, 0, 16, 16);
        sb->setShape(square, true, true, false);
        sb->addListener(this);
        buttonIsToggled[String(i)] = false;
        addAndMakeVisible(sb);
    }
  }

  void buttonClicked(Button* button) override {
    buttonIsToggled[button->getName()] = !buttonIsToggled[button->getName()];
    if (buttonIsToggled[button->getName()]) {
      dynamic_cast<ShapeButton*>(button)->setColours(Colour(255, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0));
    } else {
      dynamic_cast<ShapeButton*>(button)->setColours(Colour(0, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0));
    }
    button->repaint();
  }

  void buttonStateChanged(Button* button) override {
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
    for (auto* button : stepButtons) {
      fb.items.add(FlexItem(*button).withWidth(16.0f).withHeight(16.0f));
    }
    fb.performLayout(getLocalBounds());
  }

private:
  OwnedArray<ShapeButton> stepButtons;
  bool isOddRow;
  std::map<String, bool> buttonIsToggled;
};
