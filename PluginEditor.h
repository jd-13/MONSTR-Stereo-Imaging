/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_51C532A7320DE07A__
#define __JUCE_HEADER_51C532A7320DE07A__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MonstrAudioProcessorEditor  : public AudioProcessorEditor,
                                    public Timer,
                                    public SliderListener
{
public:
    //==============================================================================
    MonstrAudioProcessorEditor (MonstrAudioProcessor& ownerFilter);
    ~MonstrAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback();
    MonstrAudioProcessor* getProcessor() const {
        return static_cast<MonstrAudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> crossoverSld;
    ScopedPointer<Slider> width1Sld;
    ScopedPointer<Slider> width2Sld;
    ScopedPointer<Slider> width3Sld;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonstrAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_51C532A7320DE07A__