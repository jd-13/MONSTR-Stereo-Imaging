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

class MONSTRBand {
public:
    MONSTRBand();
    ~MONSTRBand();
    
    void setLowCutoff(float val);
    void setHighCutoff(float val);
    void setWidth(float val);
    void setIsbypassed(bool val);
    
    float getLowCutoff() const;
    float getHighCutoff() const;
    float getWidth() const;
    float getIsBypassed() const;
    
    void makeBandBottom(bool val);
    void makeBandTop(bool val);
    
    void process(float inLeftSample, float inRightSample) const;
    
private:
    bool isBypassed;
    
    float width;
    
    IIRFilter   lowCut,
                highCut;
    
    IIRCoefficients lowCutCoef,
                    highCutCoef;
    
    
};



#endif  // MONSTRBAND_H_INCLUDED
