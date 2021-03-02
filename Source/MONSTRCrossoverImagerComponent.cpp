/*
 *	File:		MONSTRCrossoverImagerComponent.cpp
 *
 *	Created:	06/02/2021
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

#include "MONSTRCrossoverImagerComponent.h"

#include "UIUtils.h"

MONSTRCrossoverImagerComponent::MONSTRCrossoverImagerComponent(MonstrAudioProcessor* processor)
        : _processor(processor) {
}

void MONSTRCrossoverImagerComponent::paint(Graphics& g) {

    double currentXPos {0};
    const int numBands {_processor->numBands->get()};

    for (int bandIndex {0}; bandIndex < numBands; bandIndex++) {

        // For the last band use the value of getWidth() rather than the next crossover as there
        // isn't one
        const double nextCrossoverXPos {
            (bandIndex < numBands - 1) ?
                UIUtils::sliderValueToXPos(_processor->crossoverParameters[bandIndex]->get(), getWidth()) :
                getWidth()
        };

        const double widthValue {_processor->getProcessedWidthValue(bandIndex)};

        const float rectHeight {(getHeight() / 2.0f) * static_cast<float>(widthValue)};

        g.setColour(UIUtils::imagerColour);

        // Draw the top rectangle
        g.fillRect(currentXPos,
                   getHeight() / 2.0 - rectHeight,
                   nextCrossoverXPos - currentXPos,
                   rectHeight);

        // Draw the bottom rectangle
        g.fillRect(currentXPos,
                   getHeight() / 2.0,
                   nextCrossoverXPos - currentXPos,
                   rectHeight);

        currentXPos = nextCrossoverXPos;
    }
}
