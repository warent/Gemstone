//
//  TabButton.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef TabButton_h
#define TabButton_h


#endif /* TabButton_h */

struct TabButton : public Component {
  TabButton(String buttonText) : btn("name", Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0)) {
    addAndMakeVisible(btn);
    btn.setButtonText(buttonText);
  }

  void resized() override {
    btn.setBounds(getLocalBounds());
  }

private:
  String buttonText;
  ShapeButton btn;
};