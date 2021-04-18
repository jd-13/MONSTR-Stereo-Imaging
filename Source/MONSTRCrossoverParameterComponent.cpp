/*
 *	File:		MONSTRCrossoverParameterComponent.cpp
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

#include "MONSTRCrossoverParameterComponent.h"

#include <algorithm>
#include "WEFilters/StereoWidthProcessorParameters.h"
#include "UIUtils.h"

namespace {

    void drawBandButton(String text, const Colour& colour, Graphics& g, double crossoverXPos, double index) {

        constexpr int CORNER_RADIUS {2};
        constexpr int LINE_THICKNESS {1};

        const Rectangle<float> buttonRectange = UIUtils::getButtonBounds(crossoverXPos, index);

        const Colour buttonBackground(static_cast<uint8_t>(0), 0, 0, 0.5f);
        g.setColour(buttonBackground);
        g.fillRoundedRectangle(buttonRectange, CORNER_RADIUS);

        g.setColour(colour);
        g.drawRoundedRectangle(buttonRectange, CORNER_RADIUS, LINE_THICKNESS);

        g.drawText(text, buttonRectange, Justification::centred);
    }
}

MONSTRCrossoverParameterComponent::MONSTRCrossoverParameterComponent(MonstrAudioProcessor* newAudioProcessor)
        : _processor(newAudioProcessor) {
}

void MONSTRCrossoverParameterComponent::paint(Graphics &g) {

    _drawNeutralLine(g);
    _drawWidthRectangles(g);
    _drawSliderThumbs(g);
    _drawFrequencyText(g);
    _drawBandButtons(g);
}

void MONSTRCrossoverParameterComponent::_drawNeutralLine(Graphics &g) {

    Path p;
    p.addLineSegment(Line<float>(0,
                                 getHeight() / 2,
                                 getWidth(),
                                 getHeight() / 2),
                     1);

    g.setColour(UIUtils::lightGrey);
    g.strokePath(p, PathStrokeType(0.5f));
}

void MONSTRCrossoverParameterComponent::_drawSliderThumbs(Graphics& g) {

    for (int bandIndex {0}; bandIndex < _processor->numBands->get() - 1; bandIndex++) {
        const double crossoverXPos {
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth())
        };


        Path p;
        constexpr float LINE_WIDTH {1.0f};

        g.setColour(UIUtils::darkGrey);
        p.addLineSegment(Line<float>(crossoverXPos, 0, crossoverXPos, getHeight()),
                         1);
        g.strokePath(p, PathStrokeType(LINE_WIDTH));
    }
}

void MONSTRCrossoverParameterComponent::_drawWidthRectangles(Graphics &g) {

    double currentXPos {0};
    const int numBands {_processor->numBands->get()};

    // Check if any bands are soloed
    bool isSomethingSoloed {false};
    for (int bandIndex {0}; bandIndex < numBands; bandIndex++) {
        if (_processor->bandParameters[bandIndex].isSoloed->get()) {
            isSomethingSoloed = true;
        }
    }

    for (int bandIndex {0}; bandIndex < numBands; bandIndex++) {

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

        float rectYPos {0};
        float rectHeight {0};
        float lineHeight {0};

        // Move the width value to the range -0.5:0.5
        const double widthValue {_processor->bandParameters[bandIndex].width->get() / 2 - 0.5};

        if (widthValue > 0) {
            rectHeight = (getHeight() / 2.0) * widthValue;
            rectYPos = getHeight() / 2.0 - rectHeight;
            lineHeight = rectYPos;
        } else {
            rectYPos = getHeight() / 2.0;
            rectHeight = (getHeight() / 2.0) * std::abs(widthValue);
            lineHeight = rectYPos + rectHeight;
        }

        if (bandActive) {
            g.setColour(UIUtils::mainHighlight);
            g.drawLine(currentXPos, lineHeight, nextCrossoverXPos, lineHeight, 0.5f);

            g.setColour(UIUtils::transHighlight);
        } else {
            g.setColour(UIUtils::lightGreyTrans);
        }

        g.fillRect(currentXPos, rectYPos, nextCrossoverXPos - currentXPos, rectHeight);

        currentXPos = nextCrossoverXPos;
    }
}

void MONSTRCrossoverParameterComponent::_drawFrequencyText(Graphics &g) {
    constexpr double fractionOfHeight {0.85};
    constexpr int spacing {10};

    for (int bandIndex {0}; bandIndex < _processor->numBands->get() - 1; bandIndex++) {
        g.setColour(UIUtils::mainHighlight);

        const float crossoverValue {_processor->crossoverParameters[bandIndex]->get()};

        const double crossoverXPos {
            UIUtils::sliderValueToXPos(crossoverValue, getWidth())
        };

        GlyphArrangement ga;
        ga.addLineOfText(Font(16.0f), String(static_cast<int>(crossoverValue)) + " Hz", 0, 0);

        Path p;
        ga.createPath(p);

        Rectangle<float> pathBounds = p.getBounds();

        p.applyTransform(
            AffineTransform().rotated(WECore::CoreMath::DOUBLE_PI / 2,
                                      pathBounds.getCentreX(),
                                      pathBounds.getCentreY()).translated(crossoverXPos - pathBounds.getWidth() / 2.0 + spacing,
                                                                          getHeight() * fractionOfHeight)


        );

        g.fillPath(p);
    }
}

void MONSTRCrossoverParameterComponent::_drawBandButtons(Graphics &g) {

    const Colour bypassColour(252, 252, 22);
    const Colour muteColour(252, 0, 0);
    const Colour soloColour(252, 137, 22);

    for (int bandIndex {0}; bandIndex < _processor->numBands->get(); bandIndex++) {
        const double crossoverXPos {bandIndex < _processor->numBands->get() - 1 ?
            UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth()) :
            getWidth()
        };

        drawBandButton("B",
                       !_processor->bandParameters[bandIndex].isActive->get() ? bypassColour : UIUtils::lightGrey,
                       g,
                       crossoverXPos,
                       0);

        drawBandButton("M",
                       _processor->bandParameters[bandIndex].isMuted->get() ? muteColour : UIUtils::lightGrey,
                       g,
                       crossoverXPos,
                       1);

        drawBandButton("S",
                       _processor->bandParameters[bandIndex].isSoloed->get() ? soloColour : UIUtils::lightGrey,
                       g,
                       crossoverXPos,
                       2);
    }
}
