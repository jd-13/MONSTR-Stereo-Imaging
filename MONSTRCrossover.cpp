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
                             const Rectangle<int>& bounds,
                             Slider& crossoverLowerSld,
                             Slider& crossoverUpperSld,
                             MONSTRWidthSlider& width1Sld,
                             MONSTRWidthSlider& width2Sld,
                             MONSTRWidthSlider& width3Sld) {
    
    // calculate the crossover values in Hz from the sliders
    const double crossoverLowerHz {TranslateParam_Norm2Inter(crossoverLowerSld.getValue(), CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX)};
    const double crossoverUpperHz {TranslateParam_Norm2Inter(crossoverUpperSld.getValue(), CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX)};
    
    // calculate the raw logarithmic values
    double crossoverLowerXPos {log2((crossoverLowerHz + scaleCoefficient) / scaleCoefficient) / log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient)};
    double crossoverUpperXPos {log2((crossoverUpperHz + scaleCoefficient) / scaleCoefficient) / log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient)};
    
    // normalise so that they correspond to actual coordinates
    crossoverLowerXPos *= bounds.getWidth() * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    crossoverUpperXPos *= bounds.getWidth() * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    
    drawSine(g, bounds, crossoverLowerXPos, crossoverUpperXPos);

    drawNeutralLine(g, bounds);
    
    drawWidthRectangles(g,
                        bounds,
                        crossoverLowerXPos,
                        crossoverUpperXPos,
                        width1Sld,
                        width2Sld,
                        width3Sld);
    
    
    drawFrequencyText(g,
                      bounds,
                      crossoverLowerXPos,
                      crossoverLowerHz,
                      crossoverUpperXPos,
                      crossoverUpperHz);
    
    drawSliderThumbs(g,
                     bounds,
                     crossoverLowerXPos,
                     crossoverUpperXPos);
    
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

void MONSTRCrossover::resizeWidthSliders(Graphics &g,
                                         const Rectangle<int>& bounds,
                                         float crossoverLowerXPos,
                                         float crossoverUpperXPos,
                                         MONSTRWidthSlider& width1Sld,
                                         MONSTRWidthSlider& width2Sld,
                                         MONSTRWidthSlider& width3Sld) {
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
                                         Rectangle<int> bounds,
                                         float crossoverLowerXPos,
                                         float crossoverUpperXPos) {
    
    // define the lambda for the sine function
    auto SineFunc {[](double x) -> double {
        return sin(pow(M_E, 1.5 * x + 1.83)) / 2 + 0.5;
    }};
    
    const int totalPoints {2000}; // sets the resolution of the path

    Path p;
    p.startNewSubPath(bounds.getX(), bounds.getY() + SineFunc(0) * bounds.getHeight());
    
    // move from left to right calculating the sine wave to draw
    // calculate the half left of the thumb, then change colour and calculate
    // the second half

    
    // start from 1 since the first point is already drawn (above)
    const int pointsToLowerSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverLowerXPos / bounds.getWidth()))};
    double absXPos {0};
    
    
    // define the lambda used in for loops to draw the sine
    auto sineLoop {[totalPoints, &absXPos, &p, &bounds, SineFunc](int index) -> void {
        absXPos = {(1.0 / totalPoints) * index};
        
        double absAmplitude {SineFunc(absXPos)};
        
        p.lineTo(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + absAmplitude * bounds.getHeight());
    }};
    
    
    for (int iii {1}; iii < pointsToLowerSliderPos; iii++) {
        sineLoop(iii);
    }
    
    g.setColour(MONSTRLookAndFeel::red);
    g.strokePath(p, PathStrokeType(2.0f));
    
    
    // start second band
    p.clear();
    absXPos = (1.0 / totalPoints) * pointsToLowerSliderPos;
    p.startNewSubPath(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + SineFunc(absXPos) * bounds.getHeight());
    const int pointsToUpperSliderPos {static_cast<int>(totalPoints * static_cast<float>(crossoverUpperXPos / bounds.getWidth()))};
    
    for (int iii {pointsToLowerSliderPos + 1}; iii < pointsToUpperSliderPos; iii++) {
        sineLoop(iii);
    }
    
    g.setColour(MONSTRLookAndFeel::yellow);
    g.strokePath(p, PathStrokeType(2.0f));
    
    
    // start final band
    p.clear();
    absXPos = (1.0 / totalPoints) * pointsToUpperSliderPos;
    p.startNewSubPath(bounds.getX() + absXPos * bounds.getWidth(), bounds.getY() + SineFunc(absXPos) * bounds.getHeight());
    
    for (int iii {pointsToUpperSliderPos + 1}; iii < totalPoints; iii++) {
        sineLoop(iii);
    }
    
    g.setColour(MONSTRLookAndFeel::green);
    g.strokePath(p, PathStrokeType(2.0f));
    

}

// draws the rectangles showing the width of each band
void MONSTRCrossover::drawWidthRectangles(Graphics &g,
                                                   const Rectangle<int>& bounds,
                                                   float crossoverLowerXPos,
                                                   float crossoverUpperXPos,
                                                   MONSTRWidthSlider& width1Sld,
                                                   MONSTRWidthSlider& width2Sld,
                                                   MONSTRWidthSlider& width3Sld) {
    const float range {0.25};
    
    // lambda to draw the width rectangles for each band
    auto drawWidth {[&g, &bounds, &range](const Colour& colour,
                                          float widthValue,
                                          float x,
                                          float bandWidth,
                                          bool isBandActive) -> void {
        
        if (isBandActive) {
            g.setColour(colour);
        } else {
            g.setColour(MONSTRLookAndFeel::lightGrey);
        }
        
        if (widthValue > 0.5) {
            
            /* left edge
             * top edge
             * width
             * height
             */
            
            g.fillRect(x,
                       bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (widthValue - 0.5),
                       bandWidth,
                       (bounds.getY() + bounds.getHeight() * neutralPos) - (bounds.getY() + bounds.getHeight() * neutralPos - bounds.getHeight() * range * (widthValue - 0.5)));
            
            g.fillRect(x,
                       bounds.getY() + bounds.getHeight() * (1 - neutralPos),
                       bandWidth,
                       bounds.getHeight() * range * (widthValue - 0.5));
        } else {
            g.fillRect(x,
                       bounds.getY() + bounds.getHeight() * neutralPos,
                       bandWidth,
                       bounds.getHeight() * range * (0.5 - widthValue));
            
            g.fillRect(x,
                       bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - widthValue),
                       bandWidth,
                       (bounds.getY() + bounds.getHeight() * (1 - neutralPos)) - (bounds.getY() + bounds.getHeight() * (1 - neutralPos) - bounds.getHeight() * range * (0.5 - widthValue)));
        }
    }};
    
    drawWidth(MONSTRLookAndFeel::redTrans,
              width1Sld.getValue(),
              bounds.getX(),
              crossoverLowerXPos,
              width1Sld.getIsBandActive());
    
    drawWidth(MONSTRLookAndFeel::yellowTrans,
              width2Sld.getValue(),
              bounds.getX() + crossoverLowerXPos,
              crossoverUpperXPos - crossoverLowerXPos,
              width2Sld.getIsBandActive());
    
    drawWidth(MONSTRLookAndFeel::greenTrans,
              width3Sld.getValue(),
              bounds.getX() + crossoverUpperXPos,
              bounds.getWidth() - crossoverUpperXPos,
              width3Sld.getIsBandActive());
}

// draws the lines representing neutral width
void MONSTRCrossover::drawNeutralLine(Graphics &g,
                                      Rectangle<int> bounds) {
    
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
void MONSTRCrossover::positionHorizontalSliders(const Rectangle<int> &bounds,
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

void MONSTRCrossover::drawFrequencyText(Graphics &g,
                                        const Rectangle<int> &bounds,
                                        float crossoverLowerXPos,
                                        float crossoverLowerHz,
                                        float crossoverUpperXPos,
                                        float crossoverUpperHz) {
    const float fractionOfHeight {0.9};
    
    g.setColour(MONSTRLookAndFeel::yellow);
    g.drawText(String(crossoverLowerHz),
               bounds.getX() + crossoverLowerXPos,
               bounds.getHeight() * fractionOfHeight,
               50,
               20,
               Justification::centredLeft,
               false);
    
    g.setColour(MONSTRLookAndFeel::green);
    g.drawText(String(crossoverUpperHz),
               bounds.getX() + crossoverUpperXPos,
               bounds.getY() + bounds.getHeight() * fractionOfHeight,
               50,
               20,
               Justification::centredLeft,
               false);
}

void MONSTRCrossover::drawSliderThumbs(Graphics& g,
                                       const Rectangle<int>& bounds,
                                       float crossoverLowerXPos,
                                       float crossoverUpperXPos) {
    const int sliderThumbRadius {2};
    
    auto drawSingleThumb = [sliderThumbRadius, &bounds, &g](int crossoverXPos,
                                                            Colour topColour,
                                                            Colour bottomColour) -> void {
        Path p;
        g.setColour(MONSTRLookAndFeel::darkGrey);
        p.addEllipse(bounds.getX() + crossoverXPos - sliderThumbRadius,
                     bounds.getY() + bounds.getHeight() * 0.5,
                     sliderThumbRadius * 2,
                     sliderThumbRadius * 2);
        g.fillPath(p);
        p.clear();
        
        g.setColour(topColour);
        p.addLineSegment(Line<float>(bounds.getX() + crossoverXPos,
                                     bounds.getY(),
                                     bounds.getX() + crossoverXPos,
                                     bounds.getY() + bounds.getHeight() * 0.5),
                         1);
        g.strokePath(p, PathStrokeType(1.0f));
        
        p.clear();
        
        g.setColour(bottomColour);
        p.addLineSegment(Line<float>(bounds.getX() + crossoverXPos,
                                     bounds.getY() + bounds.getHeight() * 0.5,
                                     bounds.getX() + crossoverXPos,
                                     bounds.getY() + bounds.getHeight()),
                         1);
        g.strokePath(p, PathStrokeType(1.0f));
    };
    
    drawSingleThumb(crossoverLowerXPos, MONSTRLookAndFeel::red, MONSTRLookAndFeel::yellow);
    drawSingleThumb(crossoverUpperXPos, MONSTRLookAndFeel::yellow, MONSTRLookAndFeel::green);
}