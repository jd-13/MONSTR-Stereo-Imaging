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
#include "PluginProcessor.h"

class MONSTRWidthSlider : public Slider {
public:
    MONSTRWidthSlider(String name,
                      MonstrAudioProcessor* newProcessor,
                      int parameter);
    
    virtual void mouseDown(const MouseEvent& event) override;
    
private:
    MonstrAudioProcessor* ourProcessor;
    int parameter;

};



#endif  // MONSTRWidthSlider_H_INCLUDED
