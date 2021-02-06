/*
 *	File:		MONSTRCrossoverImagerComponent.h
 *
 *	Version:	1.0.0
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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"

/**
 * Draws the calculated width for each band behind the crossover controls.
 */
class MONSTRCrossoverImagerComponent : public Component {
public:
    MONSTRCrossoverImagerComponent(MonstrAudioProcessor* processor);

    void paint(Graphics& g) override;

private:
    MonstrAudioProcessor* _processor;
};
