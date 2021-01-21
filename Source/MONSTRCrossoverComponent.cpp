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
        : _processor(newAudioProcessor) {

    // Generate sine wave table
    for (size_t iii {0}; iii < sineWaveTable.size(); iii++) {
        double xVal {(1.0 / sineWaveTable.size()) * iii};
        sineWaveTable[iii] = sin(pow(M_E, 1.5 * xVal + 1.83)) / 2 + 0.5;
    }
}

MONSTRCrossoverComponent::~MONSTRCrossoverComponent() {
}

void MONSTRCrossoverComponent::paint(Graphics &g) {

    _drawNeutralLine(g);
    _drawSine(g);
    _drawWidthRectangles(g);
    _drawSliderThumbs(g);
    _drawFrequencyText(g);
}

void MONSTRCrossoverComponent::mouseDown(const MouseEvent& event) {

    const int mouseDownX {event.getMouseDownX()};

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())};

        if (mouseDownX < crossoverXPos - SLIDER_THUMB_TARGET_WIDTH) {

            // Drag started below a crossover handle, so is a width change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setBandWidth(bandIndex, YPosToWidthValue(event.getPosition().getY(), getHeight()));
            };

            break;

        } else if (mouseDownX < crossoverXPos + SLIDER_THUMB_TARGET_WIDTH) {

            // Drag started on a crossover handle, so is a frequency change
            _mouseDragCallback = [bandIndex, this](const MouseEvent& event) {
                _processor->setCrossoverFrequency(bandIndex, XPosToSliderValue(event.getPosition().getX(), getWidth()));
            };

            break;
        }
    }

    // Handle the case for the highest band of the component in the furthest right
    const double topCrossoverXPos {sliderValueToXPos(_processor->crossoverParameters[numBands - 1]->get(), getWidth())};

    if (mouseDownX > topCrossoverXPos + SLIDER_THUMB_TARGET_WIDTH) {
        _mouseDragCallback = [&](const MouseEvent& event) {
            _processor->setBandWidth(numBands - 1, YPosToWidthValue(event.getPosition().getY(), getHeight()));
        };
    }
}

void MONSTRCrossoverComponent::mouseDrag(const MouseEvent& event) {

    if (_mouseDragCallback.has_value()) {
        (*_mouseDragCallback)(event);
    }

    repaint();
}

void MONSTRCrossoverComponent::mouseUp(const MouseEvent& event) {
    _mouseDragCallback.reset();
}

void MONSTRCrossoverComponent::mouseDoubleClick(const MouseEvent& event) {

    // This implements "double click to default" for the width parameters

    const int mouseDownX {event.getMouseDownX()};

    const double defaultWidth {
        WECore::StereoWidth::Parameters::WIDTH.InternalToNormalised(WECore::StereoWidth::Parameters::WIDTH.defaultValue)
    };

    // For each available band, check if the cursor landed on a crossover frequency handle or on
    // the gaps in between
    const int numBands {_processor->numBands->get()};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        const double crossoverXPos {sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())};

        if (mouseDownX < crossoverXPos - SLIDER_THUMB_TARGET_WIDTH) {
            // Click landed below a crossover handle, so reset the width to its default
            _processor->setBandWidth(bandIndex, defaultWidth);
            break;

        } else if (mouseDownX < crossoverXPos + SLIDER_THUMB_TARGET_WIDTH) {
            // Drag started on a crossover handle - do nothing and exit the loop
            break;
        }
    }

    // We need to do one final check for if the cursor landed in the top band, above the highest
    // crossover
    const double topCrossoverXPos {sliderValueToXPos(_processor->crossoverParameters[numBands - 1]->get(), getWidth())};
    if (mouseDownX > topCrossoverXPos + SLIDER_THUMB_TARGET_WIDTH) {
        _processor->setBandWidth(numBands - 1, defaultWidth);
    }
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
    const int numBands {_processor->numBands->get()};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {

        const double crossoverXPos {
            sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())
        };

        // On the last band we don't really have another crossover point, we just need to keep going
        // all the way to the right of the component
        const int pointsToCrossoverXPos {
            (bandIndex < numBands - 1) ?
                static_cast<int>(sineWaveTable.size() * (crossoverXPos / getWidth())) :
                static_cast<int>(sineWaveTable.size() - 1)
        };

        constexpr double SINE_Y_FACTOR {0.9};
        const double sineYScale {getHeight() * SINE_Y_FACTOR};
        const double sineYOffset {((1 - SINE_Y_FACTOR) / 2) * getHeight()};

        p.clear();
        p.startNewSubPath(absXPos * getWidth(), sineWaveTable[pointsDrawn] * sineYScale + sineYOffset);

        pointsDrawn++;

        for (; pointsDrawn <= pointsToCrossoverXPos; pointsDrawn++) {
            absXPos = (1.0 / sineWaveTable.size()) * pointsDrawn;
            p.lineTo(absXPos * getWidth(), sineWaveTable[pointsDrawn] * sineYScale + sineYOffset);
        }

        pointsDrawn--;

        g.setColour(bandColours[bandIndex % bandColours.size()].main);
        g.strokePath(p, PathStrokeType(2.0f));
    }
}

void MONSTRCrossoverComponent::_drawSliderThumbs(Graphics& g) {

    for (size_t bandIndex {0}; bandIndex < _processor->numBands->get() - 1; bandIndex++) {
        const double crossoverXPos {
            sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())
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
    const int numBands {_processor->numBands->get()};

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {

        // For the last band use the value of getWidth() rather than the next crossover as there
        // isn't one
        const double nextCrossoverXPos {
            (bandIndex < numBands - 1) ?
                sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth()) :
                getWidth()
        };

        // Band is grey if inactive
        if (_processor->bandParameters[bandIndex].isActive->get()) {
            g.setColour(bandColours[bandIndex % bandColours.size()].translucent);
        } else {
            g.setColour(lightGreyTrans);
        }

        float ypos {0};
        float height {0};

        // Move the width value to the range -0.5:0.5
        const double widthValue {_processor->bandParameters[bandIndex].width->get() - 0.5};

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

    for (size_t bandIndex {0}; bandIndex < _processor->numBands->get() - 1; bandIndex++) {
        g.setColour(bandColours[(bandIndex + 1) % bandColours.size()].main);

        const float crossoverValue {_processor->crossoverParameters[bandIndex]->get()};

        const double crossoverXPos {
            sliderValueToXPos(crossoverValue, getWidth())
        };

        const double crossoverHz {
            WECore::MONSTR::Parameters::CROSSOVER_FREQUENCY.NormalisedToInternal(crossoverValue)
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
