//
//  SquaresPanel.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef SquaresPanel_h
#define SquaresPanel_h


#endif /* SquaresPanel_h */

#include "../../components/Gem.h"

struct SquaresPanel : public Component {
  SquaresPanel() {
    for (auto i = 0; i < 8; i++) {
        addAndMakeVisible(squares.add(new SquareComponent()));
    }
  }

  void paint (Graphics& g) override {
    g.fillAll(Colour(45, 48, 71));
  }

  void resized() override {
    FlexBox squaresContainer(
        FlexBox::Direction::row,
        FlexBox::Wrap::noWrap,
        FlexBox::AlignContent::center,
        FlexBox::AlignItems::center,
        FlexBox::JustifyContent::spaceAround);

    for (auto* square : squares) {
        squaresContainer.items.add(FlexItem(*square).withMinWidth(64.0f).withMinHeight(64.0f));
    }
    squaresContainer.performLayout(getLocalBounds().toFloat());
  }

private:
  OwnedArray<SquareComponent> squares;
};