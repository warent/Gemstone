//
//  ADSRPanel.h
//  Synth
//
//  Created by Wyatt Arent on 7/4/18.
//

#ifndef ADSRPanel_H
#define ADSRPanel_H

#endif /* ADSRPanel */

struct ADSRPanel : public Component {
  ADSRPanel() {
      sliderAttack.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderDecay.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderSustain.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderRelease.setSliderStyle(Slider::SliderStyle::LinearVertical);

      addAndMakeVisible(sliderAttack);
      addAndMakeVisible(sliderDecay);
      addAndMakeVisible(sliderSustain);
      addAndMakeVisible(sliderRelease);
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
    FlexBox fb(
      FlexBox::Direction::row,
      FlexBox::Wrap::noWrap,
      FlexBox::AlignContent::center,
      FlexBox::AlignItems::center,
      FlexBox::JustifyContent::spaceAround);

    auto bounds = getLocalBounds();

    fb.items.add(FlexItem(sliderAttack).withMinWidth(64.0f).withMinHeight(bounds.getHeight()));
    fb.items.add(FlexItem(sliderDecay).withMinWidth(64.0f).withMinHeight(bounds.getHeight()));
    fb.items.add(FlexItem(sliderSustain).withMinWidth(64.0f).withMinHeight(bounds.getHeight()));
    fb.items.add(FlexItem(sliderRelease).withMinWidth(64.0f).withMinHeight(bounds.getHeight()));
    fb.performLayout(getLocalBounds().toFloat());
  }


private:
  Slider sliderAttack;
  Slider sliderDecay;
  Slider sliderSustain;
  Slider sliderRelease;
};
