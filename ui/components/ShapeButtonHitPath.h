//
//  ShapeButtonHitPath.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

#ifndef ShapeButtonHitPath_h
#define ShapeButtonHitPath_h


#endif /* ShapeButtonHitPath_h */

struct ShapeButtonHitPath : public ShapeButton {
    ShapeButtonHitPath(const juce::String &name, juce::Colour normalColour, juce::Colour overColour, juce::Colour downColour) :
    ShapeButton(name, normalColour, overColour, downColour) {}

    void setPath(juce::Path path) {
        setShape(path, false, false, false);
        hitPath = path;
    }

    bool hitTest(int x, int y) override {
        return hitPath.contains(x, y, 0.0f);
    }

private:
    Path hitPath;
};
