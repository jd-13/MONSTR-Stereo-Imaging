/*
  ==============================================================================

    MONSTRBand.cpp
    Created: 21 Jan 2016 10:27:06pm
    Author:  Jack Devlin

  ==============================================================================
*/

#include "MONSTRBand.h"

MONSTRBand::MONSTRBand(bool newIsLower, bool newIsUpper, int newSampleRate) :
                            isBypassed(BANDSWITCH_DEFAULT),
                            width(WIDTH_DEFAULT),
                            lowCutoff(CROSSOVERLOWER_DEFAULT),
                            highCutoff(CROSSOVERUPPER_DEFAULT),
                            sampleRate(newSampleRate),
                            lowCut(),
                            highCut(),
                            lowCutCoef(),
                            highCutCoef(),
                            isLower(newIsLower),
                            isUpper(newIsUpper) {
    assert(isLower != isUpper);
}



MONSTRBand::~MONSTRBand() {
}



void MONSTRBand::setLowCutoff(float val) {
    // TODO: add better bounds checks
    if (!isLower && !isUpper) {
        lowCutoff = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        lowCutCoef.makeHighPass(sampleRate, lowCutoff);
        lowCut.setCoefficients(lowCutCoef);
    } else if (isUpper) {
        lowCutoff = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        lowCutCoef.makeHighPass(sampleRate, lowCutoff);
        lowCut.setCoefficients(lowCutCoef);
    }
}

void MONSTRBand::setHighCutoff(float val) {
    if (!isLower && !isUpper) {
        highCutoff = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        highCutCoef.makeLowPass(sampleRate, highCutoff);
        highCut.setCoefficients(highCutCoef);
    } else if (isLower) {
        highCutoff = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        highCutCoef.makeLowPass(sampleRate, highCutoff);
        highCut.setCoefficients(highCutCoef);
    }
}

void MONSTRBand::setWidth(float val) {
    width = boundsCheck<float>(val, WIDTH_MIN, WIDTH_MAX);
}

void MONSTRBand::setIsbypassed(bool val) {
    isBypassed = val;
}

float MONSTRBand::getLowCutoff() const {
    return lowCutoff;
}

float MONSTRBand::getHighCutoff() const {
    return highCutoff;
}

float MONSTRBand::getWidth() const {
    return width;
}

float MONSTRBand::getIsBypassed() const {
    return isBypassed;
}

void MONSTRBand::makeBandLower(bool val) {
    isLower = val;
    isUpper = !val;
    lowCut.makeInactive();
}

void MONSTRBand::makeBandUpper(bool val) {
    isLower = !val;
    isUpper = val;
    highCut.makeInactive();
}

void MONSTRBand::process(float& inLeftSample, float& inRightSample) const {
    float leftSample {inLeftSample};
    float rightSample {inRightSample};
    
    
}


template <typename T>
T MONSTRBand::boundsCheck(T param, T min, T max) {
    if (param < min) param = min;
    if (param > max) param = max;
    
    return param;
}