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
#include "MONSTRWidthSlider.h"
#include "ParameterData.h"
#include "math.h"
#include <memory>

class MONSTRCrossover {
public:
    
    MONSTRCrossover();
    ~MONSTRCrossover();
    
    static void update(Graphics& g,
                       const Rectangle<int>& bounds,
                       Slider& lowerSlider,
                       Slider& upperSlider,
                       MONSTRWidthSlider& width1Sld,
                       MONSTRWidthSlider& width2Sld,
                       MONSTRWidthSlider& width3Sld);
    
private:
    static void resizeWidthSliders(Graphics& g,
                                   const Rectangle<int>& bounds,
                                   float crossoverLowerXPos,
                                   float crossoverUpperXPos,
                                   MONSTRWidthSlider& width1Sld,
                                   MONSTRWidthSlider& width2Sld,
                                   MONSTRWidthSlider& width3Sld);
    
    static void drawSine(Graphics& g,
                         Rectangle<int> bounds,
                         float crossoverLowerHz,
                         float crossoverUpperHz);
    
    static void drawWidthRectangles(Graphics& g,
                                    const Rectangle<int>& bounds,
                                    float crossoverLowerXPos,
                                    float crossoverUpperXPos,
                                    MONSTRWidthSlider& width1Sld,
                                    MONSTRWidthSlider& width2Sld,
                                    MONSTRWidthSlider& width3Sld);
    
    static void drawNeutralLine(Graphics& g,
                                Rectangle<int> bounds);
    
    static void positionHorizontalSliders(const Rectangle<int>& bounds,
                                          Slider& crossoverLowerSld,
                                          Slider& crossoverUpperSld);
    static void drawFrequencyText(Graphics& g,
                                  const Rectangle<int>& bounds,
                                  float crossoverLowerXPos,
                                  float crossoverLowerHz,
                                  float crossoverUpperXPos,
                                  float crossoverUpperHz);
    
    static void drawSliderThumbs(Graphics& g,
                                 const Rectangle<int>& bounds,
                                 float crossoverLowerXPos,
                                 float crossoverUpperXPos);
    
    
    static bool needsSetup;
    
    // defines the fraction of the distance from the top and bottom
    // of the crossover GUI element which represents neutral stereo width
    constexpr static const float neutralPos {0.25};
    
    // decrease the scaling coefficient to increase the on-screen space
    // used by the lower frequencies
    constexpr static const int scaleCoefficient {20};
    
    constexpr static const int sliderThumbRadius {6};
    
    static const Colour lightGrey,
                        darkGrey,
                        red,
                        yellow,
                        green,
                        redTrans,
                        yellowTrans,
                        greenTrans,
                        lightGreyTrans;
};

#endif  // MONSTRCROSSOVERBACKGROUND_H_INCLUDED
