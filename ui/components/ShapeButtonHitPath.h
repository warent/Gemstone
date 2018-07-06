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
