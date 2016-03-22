/*
  ==============================================================================

    MONSTRCrossover.h
    Created: 6 Mar 2016 10:37:32am
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTRCROSSOVERBACKGROUND_H_INCLUDED
#define MONSTRCROSSOVERBACKGROUND_H_INCLUDED

#define _USE_MATH_DEFINES

#include "../JuceLibraryCode/JuceHeader.h"
#include "MONSTRLookAndFeel.h"
#include "ParameterData.h"
#include "math.h"

class MONSTRCrossover {
public:
    
    MONSTRCrossover();
    ~MONSTRCrossover();
    
    static void update(Graphics& g,
                       const Rectangle<float>& bounds,
                       float crossoverLowerHz,
                       float crossoverUpperHz,
                       Slider& width1Sld,
                       Slider& width2Sld,
                       Slider& width3Sld);
    
private:
    static void drawAll(Graphics& g,
                        Rectangle<float> bounds,
                        float crossoverLowerHz,
                        float crossoverUpperHz,
                        float crossoverLowerXPos,
                        float crossoverUpperXPos,
                        float width1Value,
                        float width2Value,
                        float width3Value);
    
    static void resizeSliders(Graphics& g,
                              const Rectangle<float>& bounds,
                              float crossoverLowerXPos,
                              float crossoverUpperXPos,
                              Slider& width1Sld,
                              Slider& width2Sld,
                              Slider& width3Sld);
    
    static void drawSine(   Graphics& g,
                            Rectangle<float> bounds,
                            float crossoverLowerHz,
                            float crossoverUpperHz);
    
    static void drawWidthRectangle( Graphics& g,
                                    Rectangle<float> bounds,
                                    float crossoverLowerXPos,
                                    float crossoverUpperXPos,
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
