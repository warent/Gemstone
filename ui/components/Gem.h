//
//  Gem.h
//  Synth
//
//  Created by Wyatt Arent on 7/1/18.
//

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
