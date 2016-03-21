/*
  ==============================================================================

    MONSTRLookAndFeel.cpp
    Created: 1 Mar 2016 6:51:29pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRLookAndFeel.h"

// Initialise static const members
const Colour MONSTRLookAndFeel::lightGrey(200, 200, 200);
const Colour MONSTRLookAndFeel::darkGrey(107, 107, 107);
const Colour MONSTRLookAndFeel::red(250, 0, 0);
const Colour MONSTRLookAndFeel::yellow(255, 255, 0);
const Colour MONSTRLookAndFeel::green(30, 255, 0);
const Colour MONSTRLookAndFeel::redTrans(static_cast<uint8>(250), 0, 0, 100.0f);     // casts to remove constructor ambiguity
const Colour MONSTRLookAndFeel::yellowTrans(static_cast<uint8>(255), 255, 0, 100.0f);
const Colour MONSTRLookAndFeel::greenTrans(static_cast<uint8>(30), 255, 0 , 100.0f);


MONSTRLookAndFeel::MONSTRLookAndFeel() : LookAndFeel_V2() {
}

MONSTRLookAndFeel::~MONSTRLookAndFeel() {
    
}


void MONSTRLookAndFeel::drawLinearSliderThumb(Graphics &g,
                                              int x,
                                              int y,
                                              int width,
                                              int height,
                                              float sliderPos,
                                              float minSliderPos,
                                              float maxSliderPos,
                                              const Slider::SliderStyle style,
                                              juce::Slider &slider) {
    
    
}

void MONSTRLookAndFeel::drawLinearSliderBackground(Graphics &g,
                                                   int x,
                                                   int y,
                                                   int width,
                                                   int height,
                                                   float sliderPos,
                                                   float minSliderPos,
                                                   float maxSliderPos,
                                                   const Slider::SliderStyle style,
                                                   Slider& slider) {
    // do nothing
}







