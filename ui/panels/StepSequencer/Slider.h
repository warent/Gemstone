//
//  StepSequencerPanelSlider.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

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