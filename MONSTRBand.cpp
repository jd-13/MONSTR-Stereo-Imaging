/*
 *	File:		MONSTRBand.cpp
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

#include "MONSTRBand.h"

MONSTRBand::MONSTRBand(bool newIsLower, bool newIsUpper) :
                            isActive(BANDSWITCH_DEFAULT),
                            isLower(newIsLower),
                            isUpper(newIsUpper),
                            width(WIDTH_DEFAULT),
                            lowCutoffHz(CROSSOVERLOWER_DEFAULT),
                            highCutoffHz(CROSSOVERUPPER_DEFAULT),
                            sampleRate(44100),
                            lowCut(),
                            highCut() {
    lowCut.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    highCut.setup(FILTER_ORDER, sampleRate, highCutoffHz);
}



MONSTRBand::~MONSTRBand() {
}



void MONSTRBand::setLowCutoff(float val) {
    // if this is the lowest band, then do not cut the low frequencies
    if (!isLower && !isUpper) {
        lowCutoffHz = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        lowCut.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    } else if (isUpper) {
        lowCutoffHz = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        lowCut.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    }
}

void MONSTRBand::setHighCutoff(float val) {
    // if this is the highest band, then do not cut the high frequencies
    if (!isLower && !isUpper) {
        highCutoffHz = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        highCut.setup(FILTER_ORDER, sampleRate, highCutoffHz);
    } else if (isLower) {
        highCutoffHz = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        highCut.setup(FILTER_ORDER, sampleRate, highCutoffHz);
    }
}

void MONSTRBand::setWidth(float val) {
    width = boundsCheck<float>(val, WIDTH_MIN, WIDTH_MAX);
}

void MONSTRBand::setIsActive(bool val) {
    isActive = val;
}

void MONSTRBand::setSampleRate(double newSampleRate) {
    // if the new sample rate is different, recalculate the filter coefficients
    if (newSampleRate != sampleRate) {
        sampleRate = boundsCheck<double>(newSampleRate, 0, 192000); //TODO: confirm highest expected sample rate
        setLowCutoff(lowCutoffHz);
        setHighCutoff(highCutoffHz);
    }
}

float MONSTRBand::getLowCutoff() const {
    return lowCutoffHz;
}

float MONSTRBand::getHighCutoff() const {
    return highCutoffHz;
}

float MONSTRBand::getWidth() const {
    return width;
}

float MONSTRBand::getIsActive() const {
    return isActive;
}

void MONSTRBand::makeBandLower() {
    // lets the band know if it covers the lowest frequencies
    isLower = true;
    isUpper = false;
}

void MONSTRBand::makeBandMiddle() {
    // lets the band know if it covers the middle frequencies
    isLower = false;
    isUpper = false;
}

void MONSTRBand::makeBandUpper() {
    // lets the band know if it covers the highest frequencies
    isLower = false;
    isUpper = true;
}

void MONSTRBand::reset() {
    lowCut.reset();
    highCut.reset();
}

void MONSTRBand::process2in2out(float* inLeftSamples, float* inRightSamples, int numSamples) {
    // add upper/lower bypass depending on isupper/islower
    
    float** channelsArray = new float*[2];
    channelsArray[0] = inLeftSamples;
    channelsArray[1] = inRightSamples;
    
    if (isLower) {
        highCut.process(numSamples, channelsArray);
    } else if (isUpper) {
        lowCut.process(numSamples, channelsArray);
    } else {
        lowCut.process(numSamples, channelsArray);
        highCut.process(numSamples, channelsArray);
    }
}


