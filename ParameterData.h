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
#include "ParameterDefinition.h"

const ParameterDefinition::RangedParameter<float>   CROSSOVERLOWER(40, 500, 100),
                                                    CROSSOVERUPPER(3000, 19500, 5000),
                                                    WIDTH(0, 2, 1);


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


#endif  // PARAMETERDATA_H_INCLUDED
