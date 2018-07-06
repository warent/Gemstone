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

#ifndef StepSequencerPanelSlider_h
#define StepSequencerPanelSlider_h


#endif /* StepSequencerPanelSlider_h */

#include "../../components/ReverseSlider.h"

struct StepSequencerPanelSlider : public Component {
  StepSequencerPanelSlider() {
    slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(slider);
    slider.setRange(0, 16, 1);
    slider.setValue(4.0, NotificationType::dontSendNotification);
  }

  void resized() override {
    slider.setBounds(0, 0, getLocalBounds().getWidth(), getLocalBounds().getHeight());
  }

  void setOnValueChange(std::function<void()> onValueChange) {
    slider.onValueChange =  onValueChange;
  }

  int getValue() {
    return int(slider.getValue());
  }

private:
  ReverseSlider slider;
};