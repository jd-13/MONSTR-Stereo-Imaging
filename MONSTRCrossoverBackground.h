/*
  ==============================================================================

    MONSTRCrossoverBackground.h
    Created: 6 Mar 2016 10:37:32am
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTRCROSSOVERBACKGROUND_H_INCLUDED
#define MONSTRCROSSOVERBACKGROUND_H_INCLUDED

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRLookAndFeel.h"
#include "math.h"

class MONSTRCrossoverBackground {
public:
    
    MONSTRCrossoverBackground();
    ~MONSTRCrossoverBackground();
    
    static void drawAll(Graphics& g,
                        Rectangle<float> bounds,
                        float crossoverLowerHz,
                        float crossoverUpperHz,
                        float width1Value,
                        float width2Value,
                        float width3Value);
    
private:
    static void drawSine(   Graphics& g,
                            Rectangle<float> bounds,
                            float crossoverLowerHz,
                            float crossoverUpperHz);
    
    static void drawWidthRectangle( Graphics& g,
                                    Rectangle<float> bounds,
                                    float crossoverLowerHz,
                                    float crossoverUpperHz,
                                    float width1Value,
                                    float width2Value,
                                    float width3Value);
    
    static void drawNeutralLine(Graphics& g,
                                Rectangle<float> bounds);
    
    static inline double SineFunc(double x) {
        return sin(pow(M_E, 1.5 * x + 1.83)) / 2 + 0.5;
    }
    
    constexpr static const float neutralPos {0.25};
};



#endif  // MONSTRCROSSOVERBACKGROUND_H_INCLUDED
