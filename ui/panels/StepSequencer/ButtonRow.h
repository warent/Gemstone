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

#include <string>

#ifndef StepSequencerButtonRow_h
#define StepSequencerButtonRow_h


#endif /* StepSequencerButtonRow_h */

#pragma once

struct StepSequencerButtonRow : public Component, Button::Listener {
  StepSequencerButtonRow(int id, SynthAudioProcessor& p, int buttonCount = 8) : processor(p) {
    isOddRow = id % 2 > 0;
    rowId = id;
    for (auto i = 0; i < buttonCount; i++) {
        auto sb = stepButtons.add(new ShapeButton(String(i), Colour(0, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0)));
        Path square;
        square.addRectangle(0, 0, 16, 16);
        sb->setShape(square, true, true, false);
        sb->addListener(this);
        processor.globalSynthIsActiveInStep[rowId][i] = false;
        addAndMakeVisible(sb);
    }
  }

  void buttonClicked(Button* button) override {
    auto nameChrPointer = button->getName().getCharPointer();
    auto buttonId = int(CharacterFunctions::readDoubleValue<CharPointer_UTF8>(nameChrPointer));
    this->setToggleButton(dynamic_cast<ShapeButton*>(button), !processor.globalSynthIsActiveInStep[rowId][buttonId]);
  }

  void buttonStateChanged(Button* button) override {
  }

  void toggleClearAll() {
    for (auto* button : stepButtons) {
      this->setToggleButton(button, false);
    }
  }
  void toggleSetAll() {
    for (auto* button : stepButtons) {
      this->setToggleButton(button, true);
    }
  }
  void toggleRandomizeAll() {
    for (auto* button : stepButtons) {
      this->setToggleButton(button, bool(rand() % static_cast<int>(2)));
    }
  }

  void setToggleButton(ShapeButton* button, bool value) {
    auto nameChrPointer = button->getName().getCharPointer();
    auto buttonId = int(CharacterFunctions::readDoubleValue<CharPointer_UTF8>(nameChrPointer));
    std::cout << processor.globalSynthIsActiveInStep << " " << rowId << " " << buttonId << "\n";
    processor.globalSynthIsActiveInStep[rowId][buttonId] = value;
    if (processor.globalSynthIsActiveInStep[rowId][buttonId]) {
      button->setColours(Colour(255, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0));
    } else {
      button->setColours(Colour(0, 0, 0), Colour(255, 100, 100), Colour(255, 0, 0));
    }
    button->repaint();
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
  int rowId;
  SynthAudioProcessor& processor;
};
