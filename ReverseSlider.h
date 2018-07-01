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