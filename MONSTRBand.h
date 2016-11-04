/*
 *	File:		MONSTRBand.h
 *
 *	Version:	1.0.0
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

#ifndef MONSTRBAND_H_INCLUDED
#define MONSTRBAND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include "ParameterData.h"
#include "DspFilters/Butterworth.h"

class MONSTRBand {
public:
    MONSTRBand(bool newIsLower, bool newIsUpper) :  isActive(BANDSWITCH_DEFAULT),
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
    
    virtual ~MONSTRBand();
    
    
    void setLowCutoff(float val) {
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
    
    void setHighCutoff(float val) {
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
    
    
    
    void setWidth(float val) { width = boundsCheck<float>(val, WIDTH_MIN, WIDTH_MAX); }
    
    void setIsActive(bool val) { isActive = val; }
    
    void setSampleRate(double newSampleRate) {
        // if the new sample rate is different, recalculate the filter coefficients
        if (newSampleRate != sampleRate) {
            sampleRate = boundsCheck<double>(newSampleRate, 0, 192000); //TODO: confirm highest expected sample rate
            setLowCutoff(lowCutoffHz);
            setHighCutoff(highCutoffHz);
        }
    }
    
    float getLowCutoff() const { return lowCutoffHz;
    }
    
    float getHighCutoff() const { return highCutoffHz; }
    
    float getWidth() const { return width; }
    
    float getIsActive() const { return isActive; }
    
    
    /**
     * Lets the band know if it covers the lowest frequencies, so will
     * apply only a high cut filter.
     */
    void makeBandLower() {
        isLower = true;
        isUpper = false;
    }
    
    /**
     * Lets the band know if it covers the middle frequencies, so will
     * apply both a low and high cut filter.
     */
    void makeBandMiddle() {
        isLower = false;
        isUpper = false;
    }
    
    /**
     * Lets the band know if it covers the highest frequencies, so will
     * apply only a low cut filter.
     */
    void makeBandUpper() {
        isLower = false;
        isUpper = true;
    }
    
    /**
     * Resets filter states. Call before beginning a new buffer of
     * samples.
     */
    void reset() {
        lowCut1.reset();
        lowCut2.reset();
        highCut1.reset();
        highCut2.reset();
    }
    
    /**
     * Performs the effect processing on inLeftSample and inRightSample. Use for
     * stereo in->stereo out signals.
     *
     * @param   inLeftSamples   Reference to a vector of left samples to be processed
     * @param   inRightSamples  Reference to a vector of right samples to be processed
     */
    void process2in2out(std::vector<float>& inLeftSamples,
                                    std::vector<float>& inRightSamples) {
        
        if (inLeftSamples.size() == inRightSamples.size()) {
            // Apply the filtering before processing
            filterSamples(&inLeftSamples[0], &inRightSamples[0], inLeftSamples.size());
            
            if (isActive) {
                // Do the actual stereo widening or narrowing
                // Based on: http://musicdsp.org/showArchiveComment.php?ArchiveID=256
                double coef_S {width * 0.5};
                
                for (size_t iii {0}; iii < inLeftSamples.size(); iii++) {
                    
                    double mid {(inLeftSamples[iii] + inRightSamples[iii]) * 0.5};
                    double side {(inRightSamples[iii] - inLeftSamples[iii]) * coef_S};
                    
                    inLeftSamples[iii] = mid - side;
                    inRightSamples[iii] = mid + side;
                }
            }
        }
    }
    
private:
    bool    isActive,
            isLower,
            isUpper;
    
    float   width,
            lowCutoffHz,
            highCutoffHz;
    
    double sampleRate;
    static const int FILTER_ORDER {2};
    
    Dsp::SimpleFilter<Dsp::Butterworth::HighPass<2>, 2> lowCut1;
    Dsp::SimpleFilter<Dsp::Butterworth::HighPass<2>, 2> lowCut2;
    Dsp::SimpleFilter<Dsp::Butterworth::LowPass<2>, 2> highCut1;
    Dsp::SimpleFilter<Dsp::Butterworth::LowPass<2>, 2> highCut2;
    
    
    void filterSamples(float *inLeftSamples, float *inRightSamples, int numSamples) {
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
    
    template <typename T>
    T boundsCheck(T param, T min, T max) {
        if (param < min) param = min;
        if (param > max) param = max;
        
        return param;
    }
    
};



#endif  // MONSTRBAND_H_INCLUDED
