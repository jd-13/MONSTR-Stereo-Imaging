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
#include "UIUtils.h"

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

    void drawBandButton(String text, const Colour& colour, Graphics& g, double XPos, double YPos) {

        constexpr int CORNER_RADIUS {2};
        constexpr int LINE_THICKNESS {1};

        g.setColour(colour);

        g.drawRoundedRectangle(XPos,
                               YPos,
                               UIUtils::BAND_BUTTON_WIDTH,
                               UIUtils::BAND_BUTTON_WIDTH,
                               CORNER_RADIUS,
                               LINE_THICKNESS);

        g.drawText(text,
                   XPos,
                   YPos,
                   UIUtils::BAND_BUTTON_WIDTH,
                   UIUtils::BAND_BUTTON_WIDTH,
                   Justification::centred);
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

    _mouseListener = std::make_unique<MONSTRCrossoverMouseListener>(_processor);
    addMouseListener(_mouseListener.get(), false);
}

MONSTRCrossoverComponent::~MONSTRCrossoverComponent() {
}

void MONSTRCrossoverComponent::paint(Graphics &g) {

    _drawNeutralLine(g);
    _drawSine(g);
    _drawWidthRectangles(g);
    _drawSliderThumbs(g);
    _drawFrequencyText(g);
    _drawBandButtons(g);
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
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())
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
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())
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
        p.addEllipse(crossoverXPos - UIUtils::SLIDER_THUMB_RADIUS,
                     getHeight() * 0.5 - UIUtils::SLIDER_THUMB_RADIUS,
                     UIUtils::SLIDER_THUMB_RADIUS * 2,
                     UIUtils::SLIDER_THUMB_RADIUS * 2);
        g.fillPath(p);

        p.clear();
        g.setColour(topColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        UIUtils::SLIDER_THUMB_RADIUS,
                        UIUtils::SLIDER_THUMB_RADIUS,
                        WECore::CoreMath::DOUBLE_PI,
                        0,
                        WECore::CoreMath::DOUBLE_PI,
                        true);
        g.strokePath(p, PathStrokeType(lineWidth));

        p.clear();
        g.setColour(bottomColour);
        p.addCentredArc(crossoverXPos,
                        getHeight() * 0.5,
                        UIUtils::SLIDER_THUMB_RADIUS,
                        UIUtils::SLIDER_THUMB_RADIUS,
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

    // Check if any bands are soloed
    bool isSomethingSoloed {false};
    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {
        if (_processor->bandParameters[bandIndex].isSoloed->get()) {
            isSomethingSoloed = true;
        }
    }

    for (size_t bandIndex {0}; bandIndex < numBands; bandIndex++) {

        // For the last band use the value of getWidth() rather than the next crossover as there
        // isn't one
        const double nextCrossoverXPos {
            (bandIndex < numBands - 1) ?
                UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth()) :
                getWidth()
        };

        // Band is grey if inactive
        const bool bandActive {
            _processor->bandParameters[bandIndex].isActive->get() &&
            !_processor->bandParameters[bandIndex].isMuted->get() &&
            (!isSomethingSoloed || _processor->bandParameters[bandIndex].isSoloed->get())
        };

        if (bandActive) {
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
            UIUtils::sliderValueToXPos(crossoverValue, getWidth())
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

void MONSTRCrossoverComponent::_drawBandButtons(Graphics &g) {


    for (size_t bandIndex {0}; bandIndex < _processor->numBands->get(); bandIndex++) {
        const double crossoverXPos {bandIndex < _processor->numBands->get() - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth()) :
            getWidth()
        };

        const double XPos {UIUtils::crossoverXPosToButtonXPos(crossoverXPos)};

        const Colour& activeColour = bandColours[(bandIndex) % bandColours.size()].main;

        drawBandButton("B",
                       !_processor->bandParameters[bandIndex].isActive->get() ? activeColour : lightGrey,
                       g,
                       XPos,
                       UIUtils::getButtonYPos(0));

        drawBandButton("M",
                       _processor->bandParameters[bandIndex].isMuted->get() ? activeColour : lightGrey,
                       g,
                       XPos,
                       UIUtils::getButtonYPos(1));

        drawBandButton("S",
                       _processor->bandParameters[bandIndex].isSoloed->get() ? activeColour : lightGrey,
                       g,
                       XPos,
                       UIUtils::getButtonYPos(2));
    }
}
