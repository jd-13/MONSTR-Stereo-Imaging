/*
 *	File:		MONSTRCrossover.cpp
 *
 *	Version:	1.0.0
 *
 *	Created:	06/03/2016
 *
 *	This file is part of MONSTR.
 *
 *  MONSTR is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MONSTR is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MONSTR.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MONSTRCrossover.h"

const Colour MONSTRCrossover::lightGrey(200, 200, 200);
const Colour MONSTRCrossover::darkGrey(107, 107, 107);
const Colour MONSTRCrossover::red(250, 0, 0);
const Colour MONSTRCrossover::yellow(255, 255, 0);
const Colour MONSTRCrossover::green(30, 255, 0);
const Colour MONSTRCrossover::redTrans(static_cast<uint8_t>(250), 0, 0, 0.5f);     // casts to remove constructor ambiguity
const Colour MONSTRCrossover::yellowTrans(static_cast<uint8_t>(255), 255, 0, 0.5f);
const Colour MONSTRCrossover::greenTrans(static_cast<uint8_t>(30), 255, 0 , 0.5f);
const Colour MONSTRCrossover::lightGreyTrans(static_cast<uint8_t>(200), 200, 200, 0.5f);

MONSTRCrossover::MONSTRCrossover(String name,
                                 Slider* newCrossoverLowerSld,
                                 Slider* newCrossoverUpperSld,
                                 MONSTRWidthSlider* newWidth1Sld,
                                 MONSTRWidthSlider* newWidth2Sld,
                                 MONSTRWidthSlider* newWidth3Sld)
                                    :   Component(name),
                                        crossoverLowerSld(newCrossoverLowerSld),
                                        crossoverUpperSld(newCrossoverUpperSld),
                                        width1Sld(newWidth1Sld),
                                        width2Sld(newWidth2Sld),
                                        width3Sld(newWidth3Sld) {
                                            
    // Generate sine wave table
    for (size_t iii {0}; iii < sineWaveTable.size(); iii++) {
        double xVal {(1.0 / sineWaveTable.size()) * iii};
        sineWaveTable[iii] = sin(pow(M_E, 1.5 * xVal + 1.83)) / 2 + 0.5;
    }                                            
}

void MONSTRCrossover::paint(Graphics &g) {
    
    // calculate the crossover values in Hz from the sliders
    const float crossoverLowerHz {
        TranslateParam_Norm2Inter(static_cast<float>(crossoverLowerSld->getValue()),
                                  CROSSOVERLOWER_MIN,
                                  CROSSOVERLOWER_MAX)
    };
    
    const float crossoverUpperHz {
        TranslateParam_Norm2Inter(static_cast<float>(crossoverUpperSld->getValue()),
                                  CROSSOVERUPPER_MIN,
                                  CROSSOVERUPPER_MAX)
    };
    
    // calculate the raw logarithmic values
    float crossoverLowerXPos {
        log2f((crossoverLowerHz + scaleCoefficient) / scaleCoefficient) / log2f((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient)
    };
    float crossoverUpperXPos {
        log2f((crossoverUpperHz + scaleCoefficient) / scaleCoefficient) / log2f((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient)
    };
    
    // normalise so that they correspond to actual coordinates
    crossoverLowerXPos *=   getWidth()
                            * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    crossoverUpperXPos *=   getWidth()
                            * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000));
    
    drawSine(g, crossoverLowerXPos, crossoverUpperXPos);
    
    drawNeutralLine(g);
    
    drawWidthRectangles(g,
                        crossoverLowerXPos,
                        crossoverUpperXPos);
    
    drawFrequencyText(g,
                      crossoverLowerXPos,
                      crossoverLowerHz,
                      crossoverUpperXPos,
                      crossoverUpperHz);
    
    drawSliderThumbs(g,
                     crossoverLowerXPos,
                     crossoverUpperXPos);

    
    resizeWidthSliders(crossoverLowerXPos,
                       crossoverUpperXPos);
}

void MONSTRCrossover::resizeWidthSliders(int crossoverLowerXPos,
                                         int crossoverUpperXPos) {
    // a margin to be applied where the edges of the vertical sliders meet the thumbs
    // of the horizontal sliders to prevent overlap
    width1Sld->setBounds(getX(),
                        getY(),
                        crossoverLowerXPos - sliderThumbRadius,
                        getHeight());
    
    width2Sld->setBounds(getX() + crossoverLowerXPos + sliderThumbRadius,
                        getY(),
                        crossoverUpperXPos - crossoverLowerXPos - sliderThumbRadius * 2,
                        getHeight());
    
    width3Sld->setBounds(getX() + crossoverUpperXPos + sliderThumbRadius,
                        getY(),
                        getWidth() - crossoverUpperXPos,
                        getHeight());
}

// draws the sine wave behind each band
void MONSTRCrossover::drawSine(Graphics &g,
                               float crossoverLowerXPos,
                               float crossoverUpperXPos) {
    Path p;
    const int pointsToLowerSliderPos {static_cast<int>(sineWaveTable.size() * static_cast<float>(crossoverLowerXPos / getWidth()))};
    const int pointsToUpperSliderPos {static_cast<int>(sineWaveTable.size() * static_cast<float>(crossoverUpperXPos / getWidth()))};
    double absXPos {0};
    
    // define the lambda used in for loops to draw the sine
    auto sineLoop = [&absXPos, &p, this](int index) -> void {
        absXPos = {(1.0 / sineWaveTable.size()) * index};
        p.lineTo(absXPos * getWidth(),
                 sineWaveTable[index] * getHeight());
    };
    
    p.startNewSubPath(0,
                      sineWaveTable[0] * getHeight());

    // move from left to right calculating the sine wave to draw
    // calculate the half left of the thumb, then change colour and calculate
    // the second half
    for (int iii {1}; iii <= pointsToLowerSliderPos; iii++) {
        sineLoop(iii);
    }
    
    g.setColour(red);
    g.strokePath(p, PathStrokeType(2.0f));
    
    // start second band
    p.clear();
    p.startNewSubPath(absXPos * getWidth(),
                      sineWaveTable[pointsToLowerSliderPos] * getHeight());
    
    for (int iii {pointsToLowerSliderPos + 1}; iii <= pointsToUpperSliderPos; iii++) {
        sineLoop(iii);
    }
    
    g.setColour(yellow);
    g.strokePath(p, PathStrokeType(2.0f));

    // start final band
    p.clear();
    p.startNewSubPath(absXPos * getWidth(),
                      sineWaveTable[pointsToUpperSliderPos] * getHeight());
    for (int iii {pointsToUpperSliderPos + 1}; iii < sineWaveTable.size(); iii++) {
        sineLoop(iii);
    }
    
    g.setColour(green);
    g.strokePath(p, PathStrokeType(2.0f));
}

// draws the rectangles showing the width of each band
void MONSTRCrossover::drawWidthRectangles(Graphics &g,
                                          int crossoverLowerXPos,
                                          int crossoverUpperXPos) {
    const float range {0.25};
    
    // lambda to draw the width rectangles for each band
    auto drawWidth = [&g, &range, this](const Colour& colour,
                                          float widthValue,
                                          float x,
                                          float bandWidth,
                                          bool isBandActive) -> void {
        
        if (isBandActive) {
            g.setColour(colour);
        } else {
            g.setColour(lightGreyTrans);
        }
        
        if (widthValue > 0.5) {
            
            /* left edge
             * top edge
             * width
             * height
             */
            
            g.fillRect(x,
                       getHeight() * neutralPos - getHeight() * range * (widthValue - 0.5),
                       bandWidth,
                       (getHeight() * neutralPos) - (getHeight() * neutralPos - getHeight() * range * (widthValue - 0.5)));
            
            g.fillRect(x,
                       getHeight() * (1 - neutralPos),
                       bandWidth,
                       getHeight() * range * (widthValue - 0.5));
        } else {
            g.fillRect(x,
                       getHeight() * neutralPos,
                       bandWidth,
                       getHeight() * range * (0.5 - widthValue));
            
            g.fillRect(x,
                       getHeight() * (1 - neutralPos) - getHeight() * range * (0.5 - widthValue),
                       bandWidth,
                       (getHeight() * (1 - neutralPos)) - (getHeight() * (1 - neutralPos) - getHeight() * range * (0.5 - widthValue)));
        }
    };
    
    drawWidth(redTrans,
              width1Sld->getValue(),
              0,
              crossoverLowerXPos,
              width1Sld->isEnabled());
    
    drawWidth(yellowTrans,
              width2Sld->getValue(),
              crossoverLowerXPos,
              crossoverUpperXPos - crossoverLowerXPos,
              width2Sld->isEnabled());
    
    drawWidth(greenTrans,
              width3Sld->getValue(),
              crossoverUpperXPos,
              getWidth() - crossoverUpperXPos,
              width3Sld->isEnabled());
}

// draws the lines representing neutral width
void MONSTRCrossover::drawNeutralLine(Graphics &g) {
    
    Path p;
    p.addLineSegment(Line<float>(0,
                                 getHeight() * neutralPos,
                                 getWidth(),
                                 getHeight() * neutralPos),
                     1);
    p.addLineSegment(Line<float>(0,
                                 getHeight() * (1 - neutralPos),
                                 getWidth(),
                                 getHeight() * (1 - neutralPos)),
                     1);
    
    
    g.setColour(lightGrey);
    g.strokePath(p, PathStrokeType(0.5f));
}


// calculates the positions of the horizontal crossover sliders
void MONSTRCrossover::positionHorizontalSliders() {
    // calculate the positions of the vertical edges of the sliders on the logarithmic scale
    const double crossoverLowerLogMin {getWidth() * (log2((CROSSOVERLOWER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverLowerLogMax {getWidth() * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMin {getWidth() * (log2((CROSSOVERUPPER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMax {getWidth() * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    
    crossoverLowerSld->setBounds(getX() + crossoverLowerLogMin - sliderThumbRadius,
                                getY(),
                                crossoverLowerLogMax - crossoverLowerLogMin + 2 * sliderThumbRadius,
                                getHeight());
    
    crossoverUpperSld->setBounds(getX() + crossoverUpperLogMin - sliderThumbRadius,
                                getY(),
                                getWidth() - crossoverUpperLogMax + sliderThumbRadius,
                                getHeight());
}

void MONSTRCrossover::drawFrequencyText(Graphics &g,
                                        int crossoverLowerXPos,
                                        float crossoverLowerHz,
                                        int crossoverUpperXPos,
                                        float crossoverUpperHz) {
    const double fractionOfHeight {0.9};
    const int spacing {5};
    
    g.setColour(yellow);
    g.drawText(String(static_cast<int>(crossoverLowerHz)) + " Hz",
               crossoverLowerXPos + spacing,
               getHeight() * fractionOfHeight,
               60,
               20,
               Justification::centredLeft,
               false);
    
    g.setColour(green);
    g.drawText(String(static_cast<int>(crossoverUpperHz)) + " Hz",
               crossoverUpperXPos + spacing,
               getHeight() * fractionOfHeight,
               60,
               20,
               Justification::centredLeft,
               false);
}

void MONSTRCrossover::drawSliderThumbs(Graphics& g,
                                       float crossoverLowerXPos,
                                       float crossoverUpperXPos) {
    
    auto drawSingleThumb = [&g, this](int crossoverXPos,
                                      Colour topColour,
                                      Colour bottomColour) -> void {
        Path p;
        const float lineWidth {1.5f};

        g.setColour(topColour);
        p.addLineSegment(Line<float>(crossoverXPos,
                                     0,
                                     crossoverXPos,
                                     getHeight() * 0.5),
                         1);
        g.strokePath(p, PathStrokeType(lineWidth));
        
        p.clear();
        
        g.setColour(bottomColour);
        p.addLineSegment(Line<float>(crossoverXPos,
                                     getHeight() * 0.5,
                                     crossoverXPos,
                                     getHeight()),
                         1);
        g.strokePath(p, PathStrokeType(lineWidth));
        
        p.clear();
        g.setColour(darkGrey);
        p.addEllipse(crossoverXPos - sliderThumbRadius,
                     getHeight() * 0.5 - sliderThumbRadius,
                     sliderThumbRadius * 2,
                     sliderThumbRadius * 2);
        g.fillPath(p);
        
        p.clear();
        g.setColour(topColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        sliderThumbRadius,
                        sliderThumbRadius,
                        M_PI,
                        0,
                        M_PI,
                        true);
        g.strokePath(p, PathStrokeType(lineWidth));
        
        p.clear();
        g.setColour(bottomColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        sliderThumbRadius,
                        sliderThumbRadius,
                        0,
                        0,
                        M_PI,
                        true);
        g.strokePath(p, PathStrokeType(lineWidth));
    };
    
    drawSingleThumb(crossoverLowerXPos, red, yellow);
    drawSingleThumb(crossoverUpperXPos, yellow, green);
}