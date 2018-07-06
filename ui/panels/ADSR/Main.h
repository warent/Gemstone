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

#ifndef ADSRPanel_H
#define ADSRPanel_H

#endif /* ADSRPanel */

struct ADSRPanel : public Component {
  ADSRPanel() {
      sliderAttack.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderDecay.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderSustain.setSliderStyle(Slider::SliderStyle::LinearVertical);
      sliderRelease.setSliderStyle(Slider::SliderStyle::LinearVertical);

      sliderAttack.setRange(0.05, 60, 0.05);
      sliderDecay.setRange(0.05, 60, 0.05);
      sliderRelease.setRange(0.05, 60, 0.05);
      
      addAndMakeVisible(sliderAttack);
      addAndMakeVisible(sliderDecay);
      addAndMakeVisible(sliderSustain);
      addAndMakeVisible(sliderRelease);
  }

  void onAttackChange(std::function<void()> onValueChange) {
    sliderAttack.onValueChange = onValueChange;
  }

  void onDecayChange(std::function<void()> onValueChange) {
    sliderDecay.onValueChange =  onValueChange;
  }

  void onReleaseChange(std::function<void()> onValueChange) {
    sliderRelease.onValueChange = onValueChange;
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

  Slider sliderAttack;
  Slider sliderDecay;
  Slider sliderSustain;
  Slider sliderRelease;
};
