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

#ifndef StepSequencerPanelUtility_h
#define StepSequencerPanelUtility_h


#endif /* StepSequencerPanelUtility_h */

#include "UtilityButtonsRow.h"

struct StepSequencerPanelUtility : public Component {
  StepSequencerPanelUtility() {
    for (auto i = 0; i < 16; i++) {
        addAndMakeVisible(utilityButtonsRow.add(new StepSequencerUtilityButtonRow(i, [&](int id, String name) {
          if (name == "R")
              onRandomize(id);
          if (name == "A")
              onSetAll(id);
          if (name == "X")
              onClear(id);
        })));
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
    for (auto* buttonRow : utilityButtonsRow) {
      fb.items.add(FlexItem(*buttonRow).withHeight(32.0f).withMinWidth(getLocalBounds().getWidth()));
    }
    fb.performLayout(getLocalBounds());
  }


  OwnedArray<StepSequencerUtilityButtonRow> utilityButtonsRow;
  std::function<void(int)> onRandomize;
  std::function<void(int)> onSetAll;
  std::function<void(int)> onClear;
private:
};