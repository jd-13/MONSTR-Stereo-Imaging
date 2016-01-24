/*
  ==============================================================================

    MONSTRBand.h
    Created: 21 Jan 2016 10:27:06pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTRBAND_H_INCLUDED
#define MONSTRBAND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterData.h"

class MONSTRBand {
public:
    MONSTRBand(bool newIsLower, bool newIsUpper, int newSampleRate);
    ~MONSTRBand();
    
    void setLowCutoff(float val);
    void setHighCutoff(float val);
    void setWidth(float val);
    void setIsbypassed(bool val);
    
    float getLowCutoff() const;
    float getHighCutoff() const;
    float getWidth() const;
    float getIsBypassed() const;
    
    void makeBandLower(bool val);
    void makeBandUpper(bool val);
    
    void process(float& inLeftSample, float& inRightSample) const;
    
private:
    bool    isBypassed,
            isLower,
            isUpper;
    
    float   width,
            lowCutoff,
            highCutoff;
    
    int sampleRate;
    
    IIRFilter   lowCut,
                highCut;
    
    IIRCoefficients lowCutCoef,
                    highCutCoef;
    
    template<typename T>
    T boundsCheck(T param, T min, T max);
    
};



#endif  // MONSTRBAND_H_INCLUDED
