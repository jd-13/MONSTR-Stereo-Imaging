/*
  ==============================================================================

    MONSTRLookAndFeel.cpp
    Created: 1 Mar 2016 6:51:29pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRLookAndFeel.h"

MONSTRLookAndFeel::MONSTRLookAndFeel() :    LookAndFeel_V2(),
                                            lightGrey(200, 200, 200),
                                            darkGrey(107, 107, 107),
                                            red(250, 0, 0),
                                            yellow(255, 255, 0),
                                            green(30, 255, 0) {
}

/*void MONSTRLookAndFeel::drawLinearSliderThumb(Graphics &g,
                                              int x,
                                              int y,
                                              int width,
                                              int height,
                                              float sliderPos,
                                              float minSliderPos,
                                              float maxSliderPos,
                                              const Slider::SliderStyle style,
                                              juce::Slider &slider) {

    
}*/

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
    if (style == Slider::LinearHorizontal) {
        const int totalPoints {1000}; // sets the resolution of the path
        
        // change appearance for upper and lower parts of slider
        int waveOffset {0};
        Colour* lowerColour {&red};
        Colour* upperColour {&yellow};
        if (slider.getName() == "Crossover Upper Slider") {
            waveOffset = 1;
            lowerColour = &yellow;
            upperColour = &green;
        }
        
        Path p;
        p.startNewSubPath(0, GuiSine(0, waveOffset));
        
        // move from left to right calculating the sine wave to draw
        // calculate the half left of the thumb, then change colour and calculate
        // the second half
        
        // start from 1 since the first point is already drawn (above)
        const int pointsToSliderPos {static_cast<int>(totalPoints * static_cast<float>(slider.getValue()))};
        for (int iii {1}; iii < pointsToSliderPos; iii++) {
            double absXPos {(1.0 / totalPoints) * iii};
            
            double absAmplitude {GuiSine(absXPos, waveOffset)};
            
            p.lineTo(absXPos * width, absAmplitude * height);
        }
        
        g.setColour(*lowerColour);
        g.strokePath(p, PathStrokeType(2.0f));
        
        // start second half
        p.clear();
        double absXPos {(1.0 / totalPoints) * pointsToSliderPos};
        p.startNewSubPath(absXPos * width, GuiSine(absXPos, waveOffset) * height);
        
        for (int iii {pointsToSliderPos + 1}; iii < totalPoints; iii++) {
            absXPos = (1.0 / totalPoints) * iii;
            
            double absAmplitude {GuiSine(absXPos, waveOffset)};
            
            p.lineTo(absXPos * width, absAmplitude * height);
        }
        
        g.setColour(*upperColour);
        g.strokePath(p, PathStrokeType(2.0f));
        
    } else {

        
    }
}

inline double MONSTRLookAndFeel::GuiSine(double x, double offset) const {
    return sin(pow(M_E, 1.5 * (x + offset) + 1.83)) / 2 + 0.5;
}