/*
  ==============================================================================

    MONSTRCrossover.cpp
    Created: 6 Mar 2016 10:37:32am
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRCrossover.h"

MONSTRCrossover::MONSTRCrossover() {
    
}

MONSTRCrossover::~MONSTRCrossover() {
    
}

bool MONSTRCrossover::needsSetup {true};

void MONSTRCrossover::update(Graphics &g,
                             const Rectangle<float>& bounds,
                             Slider& crossoverLowerSld,
                             Slider& crossoverUpperSld,
                             Slider& width1Sld,
                             Slider& width2Sld,
                             Slider& width3Sld) {
    
    // calculate the crossover values in Hz from the sliders
    const double crossoverLowerHz {TranslateParam_Norm2Inter(crossoverLowerSld.getValue(), CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX)};
    const double crossoverUpperHz {TranslateParam_Norm2Inter(crossoverUpperSld.getValue(), CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX)};
    
    // calculate the raw logarithmic values
    double crossoverLowerXPos {log2((crossoverLowerHz + scaleCoefficient) / scaleCoefficient) / log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient)};
    double crossoverUpperXPos {log2((crossoverUpperHz + scaleCoefficient) / scaleCoefficient) / log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient)};

    // normalise so that they correspond to actual coordinates
    crossoverLowerXPos *= bounds.getWidth() * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    crossoverUpperXPos *= bounds.getWidth() * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    
    drawAll(g,
            bounds,
            crossoverLowerXPos,
            crossoverUpperXPos,
            width1Sld.getValue(),
            width2Sld.getValue(),
            width3Sld.getValue());
    
    resizeWidthSliders(g,
                       bounds,
                       crossoverLowerXPos,
                       crossoverUpperXPos,
                       width1Sld,
                       width2Sld,
                       width3Sld);
    
    // if update has not been called yet, perform any necessary setup
    if (needsSetup) {
        needsSetup = false;
        
        positionHorizontalSliders(bounds, crossoverLowerSld, crossoverUpperSld);
    }
}


// calls all of the private draw methods
void MONSTRCrossover::drawAll(Graphics &g,
                              Rectangle<float> bounds,
                              float crossoverLowerXPos,
                              float crossoverUpperXPos,
                              float width1Value,
                              float width2Value,
                              float width3Value) {
    

    
    drawNeutralLine(g, bounds);
    drawWidthRectangle(g,
                       bounds,
                       crossoverLowerXPos,
                       crossoverUpperXPos,
                       width1Value,
                       width2Value,
                       width3Value);
    drawSine(g, bounds, crossoverLowerXPos, crossoverUpperXPos);

}

void MONSTRCrossover::resizeWidthSliders(Graphics &g,
                                         const Rectangle<float>& bounds,
                                         float crossoverLowerXPos,
                                         float crossoverUpperXPos,
                                         Slider& width1Sld,
                                         Slider& width2Sld,
                                         Slider& width3Sld) {
    // a margin to be applied where the edges of the vertical sliders meet the thumbs
    // of the horizontal sliders to prevent overlap
    const int margin {10};
    

    
    width1Sld.setBounds(bounds.getX(),
                        bounds.getY(),
                        crossoverLowerXPos - margin,
                        bounds.getHeight());
    
    width2Sld.setBounds(bounds.getX() + crossoverLowerXPos + margin,
                        bounds.getY(),
                        crossoverUpperXPos - crossoverLowerXPos - margin,
                        bounds.getHeight());
    
    width3Sld.setBounds(bounds.getX() + crossoverUpperXPos + margin,
                        bounds.getY(),
                        bounds.getWidth() - crossoverUpperXPos,
                        bounds.getHeight());
}

// draws the sine wave behind each band
void MONSTRCrossover::drawSine(Graphics &g,
                                         Rectangle<float> bounds,
                                         float crossoverLowerXPos,
                                         float crossoverUpperXPos) {
    
    const int totalPoints {2000}; // sets the resolution of the path

    Path p;
    p.startNewSubPath(bounds.getX(), bounds.getY() + SineFunc(0) * bounds.getHeight());
    
    // move from left to right calculating the sine wave to draw
    // calculate the half left of the thumb, then change colour and calculate
    // the second half
    
    // start from 1 since the first point is already drawn (above)
    const int pointsToLowerSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverLowerXPos / bounds.getWidth()))};
    double absXPos {0};
    for (int iii {1}; iii < pointsToLowerSliderPos; iii++) {
        absXPos = {(1.0 / totalPoints) * iii};
        
        double absAmplitude {SineFunc(absXPos)};
        
        p.lineTo(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + absAmplitude * bounds.getHeight());
    }
    
    g.setColour(MONSTRLookAndFeel::red);
    g.strokePath(p, PathStrokeType(2.0f));
    
    // start second band
    p.clear();
    absXPos = (1.0 / totalPoints) * pointsToLowerSliderPos;
    p.startNewSubPath(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + SineFunc(absXPos) * bounds.getHeight());
    const int pointsToUpperSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverUpperXPos / bounds.getWidth()))};
    for (int iii {pointsToLowerSliderPos + 1}; iii < pointsToUpperSliderPos; iii++) {
        absXPos = (1.0 / totalPoints) * iii;
        
        double absAmplitude {SineFunc(absXPos)};
        
        p.lineTo(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + absAmplitude * bounds.getHeight());
    }
    
    g.setColour(MONSTRLookAndFeel::yellow);
    g.strokePath(p, PathStrokeType(2.0f));
    
    // start final band
    p.clear();
    absXPos = (1.0 / totalPoints) * pointsToUpperSliderPos;
    p.startNewSubPath(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + SineFunc(absXPos) * bounds.getHeight());
    for (int iii {pointsToUpperSliderPos + 1}; iii < totalPoints; iii++) {
        absXPos = (1.0 / totalPoints) * iii;
        
        double absAmplitude {SineFunc(absXPos)};
        
        p.lineTo(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + absAmplitude * bounds.getHeight());
    }
    
    g.setColour(MONSTRLookAndFeel::green);
    g.strokePath(p, PathStrokeType(2.0f));
    
    
}

// draws the rectangles showing the width of each band
void MONSTRCrossover::drawWidthRectangle(Graphics &g,
                                                   Rectangle<float> bounds,
                                                   float crossoverLowerXPos,
                                                   float crossoverUpperXPos,
                                                   float width1Value,
                                                   float width2Value,
                                                   float width3Value) {
    const float range {0.25};
    
    if (width1Value > 0.5) {
        g.setColour(MONSTRLookAndFeel::redTrans);
        
        /* left edge
         * top edge
         * width
         * height
         */
        
        g.fillRect(bounds.getX(),
                   bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width1Value - 0.5),
                   crossoverLowerXPos,
                   (bounds.getY() + bounds.getHeight() * neutralPos) - (bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width1Value - 0.5)));
        
        g.fillRect(bounds.getX(),
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos),
                   crossoverLowerXPos,
                   bounds.getHeight() * range * (width1Value - 0.5));
        
        
    } else {
        g.setColour(MONSTRLookAndFeel::redTrans);
        
        g.fillRect(bounds.getX(),
                   bounds.getY() + bounds.getHeight() * neutralPos,
                   crossoverLowerXPos,
                   bounds.getHeight() * range * (0.5 - width1Value));
        
        g.fillRect(bounds.getX(),
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width1Value),
                   crossoverLowerXPos,
                   (bounds.getY() + bounds.getHeight() * (1 - neutralPos)) - (bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width1Value)));
    }
    
    
    
    if (width2Value > 0.5) {
        g.setColour(MONSTRLookAndFeel::yellowTrans);
        
        g.fillRect(bounds.getX() + crossoverLowerXPos,
                   bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width2Value - 0.5),
                   crossoverUpperXPos - crossoverLowerXPos,
                   (bounds.getY() + bounds.getHeight() * neutralPos) - (bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width2Value - 0.5)));
        
        g.fillRect(bounds.getX() + crossoverLowerXPos,
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos),
                   crossoverUpperXPos - crossoverLowerXPos,
                   bounds.getHeight() * range * (width2Value - 0.5));
    } else {
        g.setColour(MONSTRLookAndFeel::yellowTrans);
        
        g.fillRect(bounds.getX() + crossoverLowerXPos,
                   bounds.getY() + bounds.getHeight() * neutralPos,
                   crossoverUpperXPos - crossoverLowerXPos,
                   bounds.getHeight() * range * (0.5 - width2Value));
        
        g.fillRect(bounds.getX() + crossoverLowerXPos,
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width2Value),
                   crossoverUpperXPos - crossoverLowerXPos,
                   (bounds.getY() + bounds.getHeight() * (1 - neutralPos)) - (bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width2Value)));
    }
    
    
    
    if (width3Value > 0.5) {
        g.setColour(MONSTRLookAndFeel::greenTrans);
        
        g.fillRect(bounds.getX() + crossoverUpperXPos,
                   bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width3Value - 0.5),
                   bounds.getWidth() - crossoverUpperXPos,
                   (bounds.getY() + bounds.getHeight() * neutralPos) - (bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (width3Value - 0.5)));
        
        g.fillRect(bounds.getX() + crossoverUpperXPos,
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos),
                   bounds.getWidth() - crossoverUpperXPos,
                   bounds.getHeight() * range * (width3Value - 0.5));
    } else {
        g.setColour(MONSTRLookAndFeel::greenTrans);
        
        g.fillRect(bounds.getX() + crossoverUpperXPos,
                   bounds.getY() + bounds.getHeight() * neutralPos,
                   bounds.getWidth() - crossoverUpperXPos,
                   bounds.getHeight() * range * (0.5 - width3Value));
        
        g.fillRect(bounds.getX() + crossoverUpperXPos,
                   bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width3Value),
                   bounds.getWidth() - crossoverUpperXPos,
                   (bounds.getY() + bounds.getHeight() * (1 - neutralPos)) - (bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - width3Value)));
    }
    
}

// draws the lines representing neutral width
void MONSTRCrossover::drawNeutralLine(Graphics &g,
                                                Rectangle<float> bounds) {
    
    Path p;
    p.addLineSegment(Line<float>(bounds.getX(),
                                 bounds.getY() + bounds.getHeight() * neutralPos,
                                 bounds.getX() + bounds.getWidth(),
                                 bounds.getY() + bounds.getHeight() * neutralPos),
                     1);
    p.addLineSegment(Line<float>(bounds.getX(),
                                 bounds.getY() + bounds.getHeight() * (1 - neutralPos),
                                 bounds.getX() + bounds.getWidth(),
                                 bounds.getY() + bounds.getHeight() * (1 - neutralPos)),
                     1);
    
    
    g.setColour(MONSTRLookAndFeel::lightGrey);
    g.strokePath(p, PathStrokeType(0.5f));
}


// calculates the positions of the horizontal crossover sliders
void MONSTRCrossover::positionHorizontalSliders(const Rectangle<float> &bounds,
                                                juce::Slider &crossoverLowerSld,
                                                juce::Slider &crossoverUpperSld) {
    // calculate the positions of the vertical edges of the sliders on the logarithmic scale
    const double crossoverLowerLogMin {bounds.getWidth() * (log2((CROSSOVERLOWER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverLowerLogMax {bounds.getWidth() * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMin {bounds.getWidth() * (log2((CROSSOVERUPPER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMax {bounds.getWidth() * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    
    crossoverLowerSld.setBounds(bounds.getX() + crossoverLowerLogMin - MONSTRLookAndFeel::sliderThumbRadius,
                                bounds.getY(),
                                crossoverLowerLogMax - crossoverLowerLogMin + 2 *
                                MONSTRLookAndFeel::sliderThumbRadius,
                                bounds.getHeight());
    
    crossoverUpperSld.setBounds(bounds.getX() + crossoverUpperLogMin - MONSTRLookAndFeel::sliderThumbRadius,
                                bounds.getY(),
                                bounds.getWidth() - crossoverUpperLogMax + MONSTRLookAndFeel::sliderThumbRadius,
                                bounds.getHeight());
}