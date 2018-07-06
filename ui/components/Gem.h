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

#ifndef Gem_h
#define Gem_h


#endif /* Gem_h */

#include "ShapeButtonHitPath.h"

struct SquareComponent : public Component {
    SquareComponent() : buttonTop("buttonTop", Colour(150, 172, 183), Colour(200, 0, 0), Colour(150, 0, 0)),
                        buttonRight("buttonRight", Colour(54, 85, 143), Colour(200, 200, 0), Colour(150, 150, 0)),
                        buttonBottom("buttonBottom", Colour(64, 55, 110), Colour(0, 200, 0), Colour(0, 150, 0)),
                        buttonLeft("buttonLeft", Colour(72, 35, 60), Colour(0, 0, 200), Colour(0, 0, 150)) {

        
        addAndMakeVisible(buttonTop);
        addAndMakeVisible(buttonBottom);
        addAndMakeVisible(buttonRight);
        addAndMakeVisible(buttonLeft);
    }

    void paint (Graphics& g) override {
        auto bounds = getLocalBounds();

        FillType ft;
        ft.setGradient(ColourGradient(Colour(72,85,99), 0, 0, Colour(0,0,0), bounds.getWidth()/2, bounds.getHeight()/2, true));

        g.setFillType(ft);
        g.fillRect(bounds.getWidth(), bounds.getHeight(), bounds.getWidth()+20, bounds.getHeight()+20);
    }
    
    void resized() override {
        auto localBounds = getLocalBounds();
        auto lHeight = localBounds.getHeight();
        auto lWidth = localBounds.getWidth();
        auto lX = localBounds.getX();
        auto lY = localBounds.getY();
        buttonTop.setBounds(lX, lY, lWidth, lHeight/2);
        buttonBottom.setBounds(lX, lY + (lHeight/2), lWidth, lHeight/2);
        buttonLeft.setBounds(lX, lY, lWidth/2, lHeight);
        buttonRight.setBounds(lX + (lWidth/2), lY, lWidth/2, lHeight);

        Path buttonTopPath;
        buttonTopPath.addTriangle(
            0, 0,
            lWidth/2, lHeight/2,
            lWidth, 0
        );
        buttonTop.setPath(buttonTopPath);

        Path buttonBottomPath;
        buttonBottomPath.addTriangle(
            lWidth/2, 0,
            0, lHeight/2,
            lWidth, lHeight/2);
        buttonBottom.setPath(buttonBottomPath);

        Path buttonRightPath;
        buttonRightPath.addTriangle(
            0, lHeight/2,
            lWidth/2, 0,
            lWidth/2, lHeight
        );
        buttonRight.setPath(buttonRightPath);

        Path buttonLeftPath;
        buttonLeftPath.addTriangle(
            0, 0,
            lWidth/2, lHeight/2,
            0, lHeight
        );
        buttonLeft.setPath(buttonLeftPath);
    }

private:
    ShapeButtonHitPath buttonTop, buttonRight, buttonBottom, buttonLeft;
};
