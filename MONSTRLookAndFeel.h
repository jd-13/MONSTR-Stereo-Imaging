/*
  ==============================================================================

    MONSTRLookAndFeel.h
    Created: 1 Mar 2016 6:51:29pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTRLOOKANDFEEL_H_INCLUDED
#define MONSTRLOOKANDFEEL_H_INCLUDED

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRCrossover.h"
#include "math.h"

class MONSTRLookAndFeel : public LookAndFeel_V2 {
public:
    MONSTRLookAndFeel();
    
    ~MONSTRLookAndFeel();
    
    virtual void drawLinearSliderThumb(Graphics& g,
                                       int x,
                                       int y,
                                       int width,
                                       int height,
                                       float sliderPos,
                                       float minSliderPos,
                                       float maxSliderPos,
                                       const Slider::SliderStyle style,
                                       Slider& slider) override;
    
    virtual void drawLinearSliderBackground(Graphics& g,
                                            int x,
                                            int y,
                                            int width,
                                            int height,
                                            float sliderPos,
                                            float minSliderPos,
                                            float maxSliderPos,
                                            const Slider::SliderStyle style,
                                            Slider& slider) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MONSTRLookAndFeel)
};



#endif  // MONSTRLOOKANDFEEL_H_INCLUDED
