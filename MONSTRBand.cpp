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
                            lowCut1(),
                            lowCut2(),
                            highCut1(),
                            highCut2() {
    lowCut1.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    lowCut2.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    highCut1.setup(FILTER_ORDER, sampleRate, highCutoffHz);
    highCut2.setup(FILTER_ORDER, sampleRate, highCutoffHz);
}



MONSTRBand::~MONSTRBand() {
}



void MONSTRBand::setLowCutoff(float val) {
    // if this is the lowest band, then do not cut the low frequencies
    if (!isLower && !isUpper) {
        lowCutoffHz = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        lowCut1.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
        lowCut2.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    } else if (isUpper) {
        lowCutoffHz = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        lowCut1.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
        lowCut2.setup(FILTER_ORDER, sampleRate, lowCutoffHz);
    }
}

void MONSTRBand::setHighCutoff(float val) {
    // if this is the highest band, then do not cut the high frequencies
    if (!isLower && !isUpper) {
        highCutoffHz = boundsCheck<float>(val, CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX);
        highCut1.setup(FILTER_ORDER, sampleRate, highCutoffHz);
        highCut2.setup(FILTER_ORDER, sampleRate, highCutoffHz);
    } else if (isLower) {
        highCutoffHz = boundsCheck<float>(val, CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX);
        highCut1.setup(FILTER_ORDER, sampleRate, highCutoffHz);
        highCut2.setup(FILTER_ORDER, sampleRate, highCutoffHz);
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
    lowCut1.reset();
    lowCut2.reset();
    highCut1.reset();
    highCut2.reset();
}

void MONSTRBand::filterSamples(float *inLeftSamples, float *inRightSamples, int numSamples) {
    float** channelsArray = new float*[2];
    channelsArray[0] = inLeftSamples;
    channelsArray[1] = inRightSamples;
    
    if (isLower) {
        highCut1.process(numSamples, channelsArray);
        highCut2.process(numSamples, channelsArray);
    } else if (isUpper) {
        lowCut1.process(numSamples, channelsArray);
        lowCut2.process(numSamples, channelsArray);
    } else {
        lowCut1.process(numSamples, channelsArray);
        lowCut2.process(numSamples, channelsArray);
        highCut1.process(numSamples, channelsArray);
        highCut2.process(numSamples, channelsArray);
    }
    
    delete[] channelsArray;
}

void MONSTRBand::process2in2out(std::vector<float>& inLeftSamples,
                                std::vector<float>& inRightSamples,
                                int numSamples) {
    
    // Apply the filtering before processing
    filterSamples(&inLeftSamples[0], &inRightSamples[0], numSamples);
    
    if (isActive) {
        // Do the actual stereo widening or narrowing
        // Based on: http://musicdsp.org/showArchiveComment.php?ArchiveID=256
        double coef_S {width * 0.5};
        
        for (size_t iii {0}; iii < numSamples; iii++) {
            
            double mid {(inLeftSamples[iii] + inRightSamples[iii]) * 0.5};
            double side {(inRightSamples[iii] - inLeftSamples[iii]) * coef_S};
            
            inLeftSamples[iii] = mid - side;
            inRightSamples[iii] = mid + side;
        }

    }

    
}


