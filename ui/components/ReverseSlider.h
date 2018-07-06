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

#ifndef ReverseSlider_H
#define ReverseSlider_H
class ReverseSlider : public JUCE_NAMESPACE::Slider
{
public:
    ReverseSlider (): JUCE_NAMESPACE::Slider() {
      lf.setColour(Slider::trackColourId, Colour(0, 0, 0));
      setLookAndFeel(&lf);
    };
    ~ReverseSlider() {};
    double proportionOfLengthToValue (double proportion) {   return JUCE_NAMESPACE::Slider::proportionOfLengthToValue(1.0f-proportion);};
    double valueToProportionOfLength (double value) {   return 1.0f-(JUCE_NAMESPACE::Slider::valueToProportionOfLength(value)); };    

private:
  LookAndFeel_V4 lf;
};
#endif // ReverseSlider_H