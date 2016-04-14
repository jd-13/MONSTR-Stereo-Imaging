/*
  ==============================================================================

    MONSTRWidthSlider.h
    Created: 9 Apr 2016 5:08:55pm
    Author:  Jack Devlin

  ==============================================================================
*/

#ifndef MONSTRWIDTHSLIDER_H_INCLUDED
#define MONSTRWIDTHSLIDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MONSTRWidthSlider : public Slider {
public:
    MONSTRWidthSlider(String name);
    
    virtual void mouseDown(const MouseEvent& event) override;
    
    bool getIsBandActive();
    
private:
    bool isBandActive;
};



#endif  // MONSTRWidthSlider_H_INCLUDED
