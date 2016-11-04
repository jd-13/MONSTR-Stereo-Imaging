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

#include "MONSTRCrossoverComponent.h"

const Colour MONSTRCrossoverComponent::lightGrey(200, 200, 200);
const Colour MONSTRCrossoverComponent::darkGrey(107, 107, 107);
const Colour MONSTRCrossoverComponent::red(250, 0, 0);
const Colour MONSTRCrossoverComponent::yellow(255, 255, 0);
const Colour MONSTRCrossoverComponent::green(30, 255, 0);
const Colour MONSTRCrossoverComponent::redTrans(static_cast<uint8_t>(250), 0, 0, 0.5f);     // casts to remove constructor ambiguity
const Colour MONSTRCrossoverComponent::yellowTrans(static_cast<uint8_t>(255), 255, 0, 0.5f);
const Colour MONSTRCrossoverComponent::greenTrans(static_cast<uint8_t>(30), 255, 0 , 0.5f);
const Colour MONSTRCrossoverComponent::lightGreyTrans(static_cast<uint8_t>(200), 200, 200, 0.5f);

MONSTRCrossoverComponent::MONSTRCrossoverComponent(String name,
                                 MonstrAudioProcessor* newAudioProcessor)
                                    :   Component(name),
                                        ourProcessor(newAudioProcessor) {
                                            
    // Generate sine wave table
    for (size_t iii {0}; iii < sineWaveTable.size(); iii++) {
        double xVal {(1.0 / sineWaveTable.size()) * iii};
        sineWaveTable[iii] = sin(pow(M_E, 1.5 * xVal + 1.83)) / 2 + 0.5;
    }
    
                                            
    // Add Sliders
    mListener = new MONSTRCrossoverListener(this);

    addAndMakeVisible (crossoverLowerSld = new Slider ("Crossover Lower Slider"));
    crossoverLowerSld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
                                         "\n"
                                         "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
                                         "\n"
                                         "Right click near the middle of a band to bypass its stereo processing."));
    crossoverLowerSld->setRange (0, 1, 0);
    crossoverLowerSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverLowerSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverLowerSld->addListener (mListener);
    crossoverLowerSld->setSkewFactor (0.7);

    addAndMakeVisible (crossoverUpperSld = new Slider ("Crossover Upper Slider"));
    crossoverUpperSld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover freqencies of each band.\n"
                                         "\n"
                                         "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
                                         "\n"
                                         "Right click near the middle of a band to bypass its stereo processing."));
    crossoverUpperSld->setRange (0, 1, 0);
    crossoverUpperSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverUpperSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverUpperSld->addListener (mListener);
    crossoverUpperSld->setSkewFactor (0.7);

    addAndMakeVisible (width1Sld = new MONSTRWidthSlider ("Band 1 Width Slider",
                                                          ourProcessor,
                                                          MonstrAudioProcessor::isActiveBand1));
    width1Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
                                 "\n"
                                 "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
                                 "\n"
                                 "Right click near the middle of a band to bypass its stereo processing."));
    width1Sld->setRange (0, 1, 0.01);
    width1Sld->setSliderStyle (Slider::LinearVertical);
    width1Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width1Sld->addListener (mListener);

    addAndMakeVisible (width2Sld = new MONSTRWidthSlider ("Band 2 Width Slider",
                                                          ourProcessor,
                                                          MonstrAudioProcessor::isActiveBand2));
    width2Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
                                 "\n"
                                 "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
                                 "\n"
                                 "Right click near the middle of a band to bypass its stereo processing."));
    width2Sld->setRange (0, 1, 0.01);
    width2Sld->setSliderStyle (Slider::LinearVertical);
    width2Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width2Sld->addListener (mListener);

    addAndMakeVisible (width3Sld = new MONSTRWidthSlider ("Band 3 Width Slider",
                                                          ourProcessor,
                                                          MonstrAudioProcessor::isActiveBand3));
    width3Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
                                 "\n"
                                 "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
                                 "\n"
                                 "Right click near the middle of a band to bypass its stereo processing."));
    width3Sld->setRange (0, 1, 0.01);
    width3Sld->setSliderStyle (Slider::LinearVertical);
    width3Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width3Sld->addListener (mListener);


    // Configure sliders
    crossoverLowerSld->setSliderSnapsToMousePosition(false);
    crossoverUpperSld->setSliderSnapsToMousePosition(false);
                                            
    crossoverLowerSld->setMouseDragSensitivity(100);
    crossoverUpperSld->setMouseDragSensitivity(100);
    crossoverLowerSld->setVelocityBasedMode(false);
    crossoverUpperSld->setVelocityBasedMode(false);
                                            
    width1Sld->setSliderSnapsToMousePosition(false);
    width2Sld->setSliderSnapsToMousePosition(false);
    width3Sld->setSliderSnapsToMousePosition(false);
}

MONSTRCrossoverComponent::~MONSTRCrossoverComponent() {
    crossoverLowerSld = nullptr;
    crossoverUpperSld = nullptr;
    width1Sld = nullptr;
    width2Sld = nullptr;
    width3Sld = nullptr;
}

void MONSTRCrossoverComponent::paint(Graphics &g) {
    
    updateSliders();
    
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

void MONSTRCrossoverComponent::resized() {
    positionHorizontalSliders();
    
    width1Sld->setBounds (64, 8, 72, 192);
    width2Sld->setBounds (232, 16, 72, 184);
    width3Sld->setBounds (432, 8, 72, 208);
}

void MONSTRCrossoverComponent::resizeWidthSliders(int crossoverLowerXPos,
                                         int crossoverUpperXPos) {
    // a margin to be applied where the edges of the vertical sliders meet the thumbs
    // of the horizontal sliders to prevent overlap
    width1Sld->setBounds(0,
                         0,
                         crossoverLowerXPos - sliderThumbRadius,
                         getHeight());
    
    width2Sld->setBounds(crossoverLowerXPos + sliderThumbRadius,
                         0,
                         crossoverUpperXPos - crossoverLowerXPos - sliderThumbRadius * 2,
                         getHeight());
    
    width3Sld->setBounds(crossoverUpperXPos + sliderThumbRadius,
                         0,
                         getWidth() - crossoverUpperXPos,
                         getHeight());
}

// draws the sine wave behind each band
void MONSTRCrossoverComponent::drawSine(Graphics &g,
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
void MONSTRCrossoverComponent::drawWidthRectangles(Graphics &g,
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
void MONSTRCrossoverComponent::drawNeutralLine(Graphics &g) {
    
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
void MONSTRCrossoverComponent::positionHorizontalSliders() {
    // calculate the positions of the vertical edges of the sliders on the logarithmic scale
    const double crossoverLowerLogMin {getWidth() * (log2((CROSSOVERLOWER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverLowerLogMax {getWidth() * (log2((CROSSOVERLOWER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMin {getWidth() * (log2((CROSSOVERUPPER_MIN + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    const double crossoverUpperLogMax {getWidth() * (log2((CROSSOVERUPPER_MAX + scaleCoefficient) / scaleCoefficient) / log2(20000))};
    
    crossoverLowerSld->setBounds(crossoverLowerLogMin - sliderThumbRadius,
                                 0,
                                 crossoverLowerLogMax - crossoverLowerLogMin + 2 * sliderThumbRadius,
                                 getHeight());
    
    crossoverUpperSld->setBounds(crossoverUpperLogMin - sliderThumbRadius,
                                 0,
                                 getWidth() - crossoverUpperLogMax + sliderThumbRadius,
                                 getHeight());
}

void MONSTRCrossoverComponent::drawFrequencyText(Graphics &g,
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

void MONSTRCrossoverComponent::drawSliderThumbs(Graphics& g,
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

void MONSTRCrossoverComponent::updateSliders() {
    crossoverLowerSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverLower), dontSendNotification);
    crossoverUpperSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverUpper), dontSendNotification);
    
    width1Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand1), dontSendNotification);
    width2Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand2), dontSendNotification);
    width3Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand3), dontSendNotification);
    
    width1Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand1));
    width2Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand2));
    width3Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand3));
}

void MONSTRCrossoverComponent::MONSTRCrossoverListener::sliderValueChanged(Slider* sliderThatWasMoved) {
    if (sliderThatWasMoved == parent->crossoverLowerSld)
    {
        //[UserSliderCode_crossoverLowerSld] -- add your slider handling code here..
        parent->ourProcessor->setParameter(MonstrAudioProcessor::crossoverLower, static_cast<float>(parent->crossoverLowerSld->getValue()));
        //[/UserSliderCode_crossoverLowerSld]
    }
    else if (sliderThatWasMoved == parent->crossoverUpperSld)
    {
        //[UserSliderCode_crossoverUpperSld] -- add your slider handling code here..
        parent->ourProcessor->setParameter(MonstrAudioProcessor::crossoverUpper, static_cast<float>(parent->crossoverUpperSld->getValue()));
        //[/UserSliderCode_crossoverUpperSld]
    }
    
    if (sliderThatWasMoved == parent->width1Sld)
    {
        //[UserSliderCode_width1Sld] -- add your slider handling code here..
        parent->ourProcessor->setParameter(MonstrAudioProcessor::widthBand1, static_cast<float>(parent->width1Sld->getValue()));
        //[/UserSliderCode_width1Sld]
    }
    else if (sliderThatWasMoved == parent->width2Sld)
    {
        //[UserSliderCode_width2Sld] -- add your slider handling code here..
        parent->ourProcessor->setParameter(MonstrAudioProcessor::widthBand2, static_cast<float>(parent->width2Sld->getValue()));
        //[/UserSliderCode_width2Sld]
    }
    else if (sliderThatWasMoved == parent->width3Sld)
    {
        //[UserSliderCode_width3Sld] -- add your slider handling code here..
        parent->ourProcessor->setParameter(MonstrAudioProcessor::widthBand3, static_cast<float>(parent->width3Sld->getValue()));
        //[/UserSliderCode_width3Sld]
    }
}
