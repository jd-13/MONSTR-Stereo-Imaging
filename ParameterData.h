/*
 *	File:		ParameterData.h
 *
 *	Version:	0.01.00
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

#include "../JuceLibraryCode/JuceHeader.h"


const float CROSSOVERLOWER_MIN {40},
            CROSSOVERLOWER_MAX {1000},
            CROSSOVERLOWER_DEFAULT {100},

            CROSSOVERUPPER_MIN {5000},
            CROSSOVERUPPER_MAX {19000},
            CROSSOVERUPPER_DEFAULT {5000},

            WIDTH_MIN {0},
            WIDTH_MAX {2},
            WIDTH_DEFAULT {1};


const bool  BANDSWITCH_OFF {false},
            BANDSWITCH_ON {true},
            BANDSWITCH_DEFAULT {BANDSWITCH_ON};


const String    SWITCHBAND1_STR {"Band1Bypass"},
                SWITCHBAND2_STR {"Band2Bypass"},
                SWITCHBAND3_STR {"Band3Bypass"},
                WIDTHBAND1_STR {"Band1Width"},
                WIDTHBAND2_STR {"Band2Width"},
                WIDTHBAND3_STR {"Band3Width"},
                CROSSOVERLOWER_STR {"LowerCrossover"},
                CROSSOVERUPPER_STR {"UpperCrossover"};


// Translates betweeen the normalised 0 - 1 range used by VSTs and the ranges used by the plugin internally
inline float TranslateParam_Norm2Inter(float val, float min, float max) {
    return val * (max - min) + min;
}

inline float TranslateParam_Inter2Norm(float val, float min, float max) {
    return (val - min) / (max - min);
}

#endif  // PARAMETERDATA_H_INCLUDED
