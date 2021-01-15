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
    struct BandColour {
        Colour main;
        Colour translucent;
    };

    const std::array<BandColour, 3> bandColours {{
        {Colour(250, 0, 0), Colour(static_cast<uint8_t>(250), 0, 0, 0.5f)}, // casts to remove constructor ambiguity
        {Colour(255, 255, 0), Colour(static_cast<uint8_t>(255), 255, 0, 0.5f)},
        {Colour(30, 255, 0), Colour(static_cast<uint8_t>(30), 255, 0, 0.5f)}
    }};

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
const Colour MONSTRCrossoverComponent::lightGreyTrans(static_cast<uint8_t>(200), 200, 200, 0.5f);

MONSTRCrossoverComponent::MONSTRCrossoverComponent(MonstrAudioProcessor* newAudioProcessor)
        : _processor(newAudioProcessor),
          _numAvailableBands(WECore::MONSTR::Parameters::NUM_BANDS.defaultValue) {

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
    _numAvailableBands = _processor->getNumBands();

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
    _drawSine(g);
    _drawWidthRectangles(g);
    _drawSliderThumbs(g);
    _drawFrequencyText(g);
}

void MONSTRCrossoverComponent::mouseDown(const MouseEvent& event) {

    constexpr int CROSSOVER_DRAG_TARGET_WIDTH {SLIDER_THUMB_RADIUS * 2};
    const int mouseDownX {event.getMouseDownX()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    for (size_t bandIndex {0}; bandIndex < _numAvailableBands; bandIndex++) {
        const double crossoverXPos {sliderValueToXPos(_crossoverValues[bandIndex], getWidth())};

        if (mouseDownX < crossoverXPos - CROSSOVER_DRAG_TARGET_WIDTH) {

            // Drag started below a crossover handle, so is a width change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setBandWidth(bandIndex, YPosToWidthValue(event.getPosition().getY(), getHeight()));
            };

            break;

        } else if (mouseDownX < crossoverXPos + CROSSOVER_DRAG_TARGET_WIDTH) {

            // Drag started on a crossover handle, so is a frequency change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setCrossoverFrequency(bandIndex, XPosToSliderValue(event.getPosition().getX(), getWidth()));
            };

            break;
        }
    }

    if (!_mouseDragCallback.has_value()) {
        // If none of the previous if statements caught it then the drag started in the furthest
        // right part of the component, so must be a width change on the highest band
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(_numAvailableBands - 1, YPosToWidthValue(event.getPosition().getY(), getHeight()));
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
void MONSTRCrossoverComponent::_drawSine(Graphics &g) {

    Path p;
    double absXPos {0};
    int pointsDrawn {0};

    // For each band, draw the points of the sine up until the next crossover then switch colour
    for (size_t bandIndex {0}; bandIndex < _numAvailableBands; bandIndex++) {

        const double crossoverXPos {
            sliderValueToXPos(_crossoverValues[bandIndex], getWidth())
        };

        // On the last band we don't really have another crossover point, we just need to keep going
        // all the way to the right of the component
        const int pointsToCrossoverXPos {
            (bandIndex < _numAvailableBands - 1) ?
                static_cast<int>(sineWaveTable.size() * (crossoverXPos / getWidth())) :
                static_cast<int>(sineWaveTable.size() - 1)
        };

        p.clear();
        p.startNewSubPath(absXPos * getWidth(), sineWaveTable[pointsDrawn] * getHeight());

        pointsDrawn++;

        for (; pointsDrawn <= pointsToCrossoverXPos; pointsDrawn++) {
            absXPos = (1.0 / sineWaveTable.size()) * pointsDrawn;
            p.lineTo(absXPos * getWidth(), sineWaveTable[pointsDrawn] * getHeight());
        }

        pointsDrawn--;

        g.setColour(bandColours[bandIndex % bandColours.size()].main);
        g.strokePath(p, PathStrokeType(2.0f));
    }
}

void MONSTRCrossoverComponent::_drawSliderThumbs(Graphics& g) {

    for (size_t bandIndex {0}; bandIndex < _numAvailableBands - 1; bandIndex++) {
        const double crossoverXPos {
            sliderValueToXPos(_crossoverValues[bandIndex], getWidth())
        };

        const Colour& topColour = bandColours[bandIndex % bandColours.size()].main;
        const Colour& bottomColour = bandColours[(bandIndex + 1) % bandColours.size()].main;

        Path p;
        constexpr float lineWidth {1.5f};

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
    }
}

void MONSTRCrossoverComponent::_drawWidthRectangles(Graphics &g) {

    double currentXPos {0};

    for (size_t bandIndex {0}; bandIndex < _numAvailableBands; bandIndex++) {

        // For the last band use the value of getWidth() rather than the next crossover as there
        // isn't one
        const double nextCrossoverXPos {
            (bandIndex < _numAvailableBands - 1) ?
                sliderValueToXPos(_crossoverValues[bandIndex], getWidth()) :
                getWidth()
        };

        // Band is grey if inactive
        if (_bandActives[bandIndex]) {
            g.setColour(bandColours[bandIndex % bandColours.size()].translucent);
        } else {
            g.setColour(lightGreyTrans);
        }

        float ypos {0};
        float height {0};

        // Move the width value to the range -0.5:0.5
        const double widthValue {_bandWidths[bandIndex] - 0.5};

        if (widthValue > 0) {
            height = (getHeight() / 2.0) * widthValue;
            ypos = getHeight() / 2.0 - height;
        } else {
            ypos = getHeight() / 2.0;
            height = (getHeight() / 2.0) * std::abs(widthValue);
        }

        g.fillRect(currentXPos, ypos, nextCrossoverXPos - currentXPos, height);

        currentXPos = nextCrossoverXPos;
    }
}

void MONSTRCrossoverComponent::_drawFrequencyText(Graphics &g) {
    constexpr double fractionOfHeight {0.9};
    constexpr int spacing {5};

    for (size_t bandIndex {0}; bandIndex < _numAvailableBands - 1; bandIndex++) {
        g.setColour(bandColours[(bandIndex + 1) % bandColours.size()].main);

        const double crossoverXPos {
            sliderValueToXPos(_crossoverValues[bandIndex], getWidth())
        };

        const double crossoverHz {
            WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.NormalisedToInternal(_crossoverValues[bandIndex])
        };

        g.drawText(String(static_cast<int>(crossoverHz)) + " Hz",
                   crossoverXPos + spacing,
                   getHeight() * fractionOfHeight,
                   60,
                   20,
                   Justification::centredLeft,
                   false);
    }
}
