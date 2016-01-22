/*
  ==============================================================================

    MONSTR.h
    Created: 21 Jan 2016 9:53:21pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTR_H_INCLUDED
#define MONSTR_H_INCLUDED

#include "MONSTRBand.h"
#include "../JuceLibraryCode/JuceHeader.h"

class MONSTR {
public:
    MONSTR();
    ~MONSTR();
        
    MONSTRBand  band1,
                band2,
                band3;
    
    void ClockProcess(float* leftSample, float* rightSample);
    
    
private:
    
};



#endif  // MONSTR_H_INCLUDED
