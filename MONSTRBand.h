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
    MONSTRBand(bool newIsLower, bool newIsUpper);
    ~MONSTRBand();
    
    
    void setLowCutoff(float val);
    void setHighCutoff(float val);
    void setWidth(float val);
    void setIsActive(bool val);
    
    void setSampleRate(double newSampleRate);
    
    float getLowCutoff() const;
    float getHighCutoff() const;
    float getWidth() const;
    float getIsActive() const;
    
    
    /* makeBandLower
     *
     * Lets the band know if it covers the lowest frequencies, so will
     * apply only a high cut filter.
     */
    void makeBandLower();
    
    /* makeBandMiddle
     *
     * Lets the band know if it covers the middle frequencies, so will
     * apply both a low and high cut filter.
     */
    void makeBandMiddle();
    
    /* makeBandUpper
     *
     * Lets the band know if it covers the highest frequencies, so will
     * apply only a low cut filter.
     */
    void makeBandUpper();
    
    /* reset
     *
     * Resets filter states. Call before beginning a new buffer of
     * samples.
     */
    void reset();
    
    /* process2in2out
     *
     * Performs the effect processing on inLeftSample and inRightSample. Use for
     * stereo in->stereo out signals.
     *
     * args: inLeftSamples    Reference to a vector of left samples to be processed
     *       inRightSamples   Reference to a vector of right samples to be processed
     */
    void process2in2out(std::vector<float>& inLeftSamples,
                        std::vector<float>& inRightSamples);
    
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
    
    void filterSamples(float* inLeftSamples, float* inRightSamples, int numSamples);
    
    template <typename T>
    T boundsCheck(T param, T min, T max) {
        if (param < min) param = min;
        if (param > max) param = max;
        
        return param;
    }
    
};



#endif  // MONSTRBAND_H_INCLUDED
