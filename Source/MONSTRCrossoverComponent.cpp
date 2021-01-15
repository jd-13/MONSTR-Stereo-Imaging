/*
 *	File:		MONSTRCrossoverComponent.cpp
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

#include <algorithm>
#include "WEFilters/StereoWidthProcessorParameters.h"

namespace {
    double sliderValueToInternalLog(double sliderValue) {
        return std::pow(10, 1.0414 * sliderValue - 1) - 0.1;
    }

    double internalLogToSliderValue(double internalValue) {
        return (std::log10(internalValue + 0.1) + 1) / 1.0414;
    }

    double sliderValueToXPos(double sliderValue, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return (internalLogToSliderValue(sliderValue) * realRange) + MARGIN_PX;
    }

    double XPosToSliderValue(int XPos, int componentWidth) {
        const double MARGIN_PX {componentWidth * 0.05};
        const double realRange {componentWidth - 2 * MARGIN_PX};

        return sliderValueToInternalLog(std::max(XPos - MARGIN_PX, 0.0) / realRange);
    }

    double YPosToWidthValue(int YPos, int componentHeight) {
        return 1 - std::min(std::max(0.0, YPos - componentHeight / 4.0) / (componentHeight / 2.0), 1.0);
    }
}

const Colour MONSTRCrossoverComponent::lightGrey(200, 200, 200);
const Colour MONSTRCrossoverComponent::darkGrey(107, 107, 107);
const Colour MONSTRCrossoverComponent::red(250, 0, 0);
const Colour MONSTRCrossoverComponent::yellow(255, 255, 0);
const Colour MONSTRCrossoverComponent::green(30, 255, 0);
const Colour MONSTRCrossoverComponent::redTrans(static_cast<uint8_t>(250), 0, 0, 0.5f);     // casts to remove constructor ambiguity
const Colour MONSTRCrossoverComponent::yellowTrans(static_cast<uint8_t>(255), 255, 0, 0.5f);
const Colour MONSTRCrossoverComponent::greenTrans(static_cast<uint8_t>(30), 255, 0 , 0.5f);
const Colour MONSTRCrossoverComponent::lightGreyTrans(static_cast<uint8_t>(200), 200, 200, 0.5f);

MONSTRCrossoverComponent::MONSTRCrossoverComponent(MonstrAudioProcessor* newAudioProcessor)
        : _processor(newAudioProcessor) {

    // Generate sine wave table
    for (size_t iii {0}; iii < sineWaveTable.size(); iii++) {
        double xVal {(1.0 / sineWaveTable.size()) * iii};
        sineWaveTable[iii] = sin(pow(M_E, 1.5 * xVal + 1.83)) / 2 + 0.5;
    }

    // Initialise parameters to default values
    for (double& position : _crossoverValues) {
        position = 0;
    }

    for (double& width : _bandWidths) {
        width = 0;
    }

    for (bool& active : _bandActives) {
        active = false;
    }
}

MONSTRCrossoverComponent::~MONSTRCrossoverComponent() {
}

void MONSTRCrossoverComponent::updateParameters() {
    for (size_t index {0}; index < _bandActives.size(); index++) {
        _bandActives[index] = _processor->bandParameters[index].isActive->get();
        _bandWidths[index] = _processor->bandParameters[index].width->get();
    }

    for (size_t index {0}; index < _crossoverValues.size(); index++) {
        _crossoverValues[index] = _processor->crossoverParameters[index]->get();
    }
}

void MONSTRCrossoverComponent::paint(Graphics &g) {

    _drawNeutralLine(g);

    const double crossoverLowerXPos {
        sliderValueToXPos(_crossoverValues[0], getWidth())
    };
    const double crossoverUpperXPos {
        sliderValueToXPos(_crossoverValues[1], getWidth())
    };

    _drawSine(g, crossoverLowerXPos, crossoverUpperXPos);

    _drawWidthRectangles(g, crossoverLowerXPos, crossoverUpperXPos);

    _drawSliderThumbs(g, crossoverLowerXPos, crossoverUpperXPos);

    const double crossoverLowerHz {
        WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.NormalisedToInternal(_crossoverValues[0])
    };

    const double crossoverUpperHz {
        WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.NormalisedToInternal(_crossoverValues[1])
    };

    _drawFrequencyText(g,
                       crossoverLowerXPos,
                       crossoverLowerHz,
                       crossoverUpperXPos,
                       crossoverUpperHz);
}

void MONSTRCrossoverComponent::mouseDown(const MouseEvent& event) {

    constexpr int CROSSOVER_DRAG_TARGET_WIDTH {SLIDER_THUMB_RADIUS * 2};
    const int mouseDownX {event.getMouseDownX()};

    const double crossoverLowerXPos {
        sliderValueToXPos(_crossoverValues[0], getWidth())
    };
    const double crossoverUpperXPos {
        sliderValueToXPos(_crossoverValues[1], getWidth())
    };

    // Going from left to right, find which part of the component the mouse was over when the drag
    // started, and set the appropriate callback
    if (mouseDownX < crossoverLowerXPos - CROSSOVER_DRAG_TARGET_WIDTH) {
        // Drag started below the first crossover
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(0, YPosToWidthValue(event.getPosition().getY(), getHeight()));
        };

    } else if (mouseDownX < crossoverLowerXPos + CROSSOVER_DRAG_TARGET_WIDTH) {
        // Drag started on the first crossover
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setCrossoverFrequency(0, XPosToSliderValue(event.getPosition().getX(), getWidth()));
        };

    } else if (mouseDownX < crossoverUpperXPos - CROSSOVER_DRAG_TARGET_WIDTH) {
        // Drag started below the second crossover
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(1, YPosToWidthValue(event.getPosition().getY(), getHeight()));
        };
    } else if (mouseDownX < crossoverUpperXPos + CROSSOVER_DRAG_TARGET_WIDTH) {
        // Drag started on the second crossover
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setCrossoverFrequency(1, XPosToSliderValue(event.getPosition().getX(), getWidth()));
        };

    } else {
        // Drag started above the second crossover
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(2, YPosToWidthValue(event.getPosition().getY(), getHeight()));
        };
    }
}

void MONSTRCrossoverComponent::mouseDrag(const MouseEvent& event) {

    if (_mouseDragCallback.has_value()) {
        (*_mouseDragCallback)(event);
    }

    updateParameters();
    repaint();
}

void MONSTRCrossoverComponent::mouseUp(const MouseEvent& event) {
    _mouseDragCallback.reset();
}

void MONSTRCrossoverComponent::_drawNeutralLine(Graphics &g) {

    Path p;
    p.addLineSegment(Line<float>(0,
                                 getHeight() / 2,
                                 getWidth(),
                                 getHeight() / 2),
                     1);

    g.setColour(lightGrey);
    g.strokePath(p, PathStrokeType(0.5f));
}

// Draws the sine wave behind each band
void MONSTRCrossoverComponent::_drawSine(Graphics &g,
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

void MONSTRCrossoverComponent::_drawSliderThumbs(Graphics& g,
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
        p.addEllipse(crossoverXPos - SLIDER_THUMB_RADIUS,
                     getHeight() * 0.5 - SLIDER_THUMB_RADIUS,
                     SLIDER_THUMB_RADIUS * 2,
                     SLIDER_THUMB_RADIUS * 2);
        g.fillPath(p);

        p.clear();
        g.setColour(topColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        SLIDER_THUMB_RADIUS,
                        SLIDER_THUMB_RADIUS,
                        WECore::CoreMath::DOUBLE_PI,
                        0,
                        WECore::CoreMath::DOUBLE_PI,
                        true);
        g.strokePath(p, PathStrokeType(lineWidth));

        p.clear();
        g.setColour(bottomColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        SLIDER_THUMB_RADIUS,
                        SLIDER_THUMB_RADIUS,
                        0,
                        0,
                        WECore::CoreMath::DOUBLE_PI,
                        true);
        g.strokePath(p, PathStrokeType(lineWidth));
    };

    drawSingleThumb(crossoverLowerXPos, red, yellow);
    drawSingleThumb(crossoverUpperXPos, yellow, green);
}

void MONSTRCrossoverComponent::_drawWidthRectangles(Graphics &g,
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

        float ypos {0};
        float height {0};

        // Move the width value to the range -0.5:0.5
        widthValue -= 0.5;

        if (widthValue > 0) {
            height = (getHeight() / 2.0) * widthValue;
            ypos = getHeight() / 2.0 - height;
        } else {
            ypos = getHeight() / 2.0;
            height = (getHeight() / 2.0) * std::abs(widthValue);
        }

        g.fillRect(x, ypos, bandWidth, height);
    };

    drawWidth(redTrans,
              _bandWidths[0],
              0,
              crossoverLowerXPos,
              _bandActives[0]);

    drawWidth(yellowTrans,
              _bandWidths[1],
              crossoverLowerXPos,
              crossoverUpperXPos - crossoverLowerXPos,
              _bandActives[1]);

    drawWidth(greenTrans,
              _bandWidths[2],
              crossoverUpperXPos,
              getWidth() - crossoverUpperXPos,
              _bandActives[2]);
}

void MONSTRCrossoverComponent::_drawFrequencyText(Graphics &g,
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
