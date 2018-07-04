//
//  TabsPanel.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef TabsPanel_h
#define TabsPanel_h


#endif /* TabsPanel_h */

#include "TabButton.h"

struct TabsPanel : public Component {
  TabsPanel() {

    addAndMakeVisible(currentLocationName);
    addAndMakeVisible(btn);

    btn.setButtonText("Global ADSR");
    currentLocationName.setText("Hello there", NotificationType::dontSendNotification);
    currentLocationName.setJustificationType(Justification::centred);
  }

  void resized() override {
    FlexBox fb(
      FlexBox::Direction::row,
      FlexBox::Wrap::noWrap,
      FlexBox::AlignContent::flexEnd,
      FlexBox::AlignItems::flexEnd,
      FlexBox::JustifyContent::spaceBetween);
    fb.items.add(FlexItem());
    fb.items.add(FlexItem(currentLocationName).withMinWidth(100.0f).withMinHeight(32.0f));
    fb.items.add(FlexItem());
    fb.performLayout(getLocalBounds());
  }

private:
  Label currentLocationName;
  TextButton btn;
};