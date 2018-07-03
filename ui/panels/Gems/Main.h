//
//  GemsPanel.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef GemsPanel_H
#define GemsPanel_H

#endif /* GemsPanel */

#include "../../components/Gem.h"

struct GemsPanel : public Component {
  GemsPanel() {
    for (auto i = 0; i < 8; i++) {
        addAndMakeVisible(squares.add(new SquareComponent()));
    }
  }

  void paint (Graphics& g) override {
    auto bounds = getLocalBounds();
    g.fillAll(Colour(41, 50, 60));
    g.setColour(Colour(0, 0, 0));
    g.drawRect(0, 0, bounds.getWidth(), 2, 1);
    g.drawRect(0, 0, 2, bounds.getHeight(), 1);
    g.setColour(Colour(72,85,99));
    g.drawRect(bounds.getWidth()-2, 0, 2, bounds.getHeight(), 1);
    g.drawRect(0, bounds.getHeight()-2, bounds.getWidth(), 2, 1);
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
