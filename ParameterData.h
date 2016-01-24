/*
  ==============================================================================

    ParameterData.h
    Created: 22 Jan 2016 10:07:09pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef PARAMETERDATA_H_INCLUDED
#define PARAMETERDATA_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


const float CROSSOVERLOWER_MIN {40},
            CROSSOVERLOWER_MAX {10000},
            CROSSOVERLOWER_DEFAULT {100},

            CROSSOVERUPPER_MIN {CROSSOVERLOWER_MAX + 1},
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
