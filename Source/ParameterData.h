/*
 *	File:		ParameterData.h
 *
 *	Created:	21/01/2016
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

#ifndef PARAMETERDATA_H_INCLUDED
#define PARAMETERDATA_H_INCLUDED

#include <array>

#include "../JuceLibraryCode/JuceHeader.h"
#include "General/ParameterDefinition.h"
#include "MONSTRFilters/MONSTRParameters.h"

const String NUMBANDS_STR = "NumBands";

struct BandStrings {
    String isActive;
    String isMuted;
    String isSoloed;
    String width;
};

const std::array<BandStrings, WECore::MONSTR::Parameters::_MAX_NUM_BANDS> BAND_STRINGS {{
    {"Band1Bypass", "Band1Mute", "Band1Solo", "Band1Width"},
    {"Band2Bypass", "Band2Mute", "Band2Solo", "Band2Width"},
    {"Band3Bypass", "Band3Mute", "Band3Solo", "Band3Width"},
    {"Band4Bypass", "Band4Mute", "Band4Solo", "Band4Width"},
    {"Band5Bypass", "Band5Mute", "Band5Solo", "Band5Width"},
    {"Band6Bypass", "Band6Mute", "Band6Solo", "Band6Width"}
}};

const std::array<String, WECore::MONSTR::Parameters::_MAX_NUM_BANDS - 1> CROSSOVER_STRINGS {
    "Crossover1Frequency",
    "Crossover2Frequency",
    "Crossover3Frequency",
    "Crossover4Frequency",
    "Crossover5Frequency"
};

#endif  // PARAMETERDATA_H_INCLUDED
