/*
  ==============================================================================

    MONSTRCrossoverBackground.cpp
    Created: 6 Mar 2016 10:37:32am
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRCrossoverBackground.h"

MONSTRCrossoverBackground::MONSTRCrossoverBackground() {
    
}

MONSTRCrossoverBackground::~MONSTRCrossoverBackground() {
    
}

// calls all of the private draw methods
void MONSTRCrossoverBackground::drawAll(Graphics &g,
                                        Rectangle<float> bounds,
                                        float crossoverLowerHz,
                                        float crossoverUpperHz,
                                        float width1Value,
                                        float width2Value,
                                        float width3Value) {
    drawNeutralLine(g, bounds);
    drawWidthRectangle(g, bounds, crossoverLowerHz, crossoverUpperHz, width1Value, width2Value, width3Value);
    drawSine(g, bounds, crossoverLowerHz, crossoverUpperHz);

}

// draws the sine wave behind each band
void MONSTRCrossoverBackground::drawSine(Graphics &g,
                                         Rectangle<float> bounds,
                                         float crossoverLowerHz,
                                         float crossoverUpperHz) {
    
    const int totalPoints {2000}; // sets the resolution of the path

    Path p;
    p.startNewSubPath(bounds.getX(), bounds.getY() + SineFunc(0) * bounds.getHeight());
    
    // move from left to right calculating the sine wave to draw
    // calculate the half left of the thumb, then change colour and calculate
    // the second half
    
    // start from 1 since the first point is already drawn (above)
    const int pointsToLowerSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverLowerHz / 20000))};
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
    const int pointsToUpperSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverUpperHz / 20000))};
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
void MONSTRCrossoverBackground::drawWidthRectangle(Graphics &g,
                                                   Rectangle<float> bounds,
                                                   float crossoverLowerHz,
                                                   float crossoverUpperHz,
                                                   float width1Value,
                                                   float width2Value,
                                                   float width3Value) {
    const float range {0.25};
    const float crossoverLowerXPos {bounds.getWidth() * (crossoverLowerHz / 20000)};
    const float crossoverUpperXPos {bounds.getWidth() * (crossoverUpperHz / 20000)};
    
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
void MONSTRCrossoverBackground::drawNeutralLine(Graphics &g,
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