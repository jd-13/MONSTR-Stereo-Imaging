/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_51C532A7320DE07A__
#define __JUCE_HEADER_51C532A7320DE07A__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "MONSTRLookAndFeel.h"
#include "MONSTRWidthSlider.h"
#include "MONSTRCrossover.h"
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
    void timerCallback() override;
    MonstrAudioProcessor* getProcessor() const {
        return static_cast<MonstrAudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MONSTRLookAndFeel customLookAndFeel;
    SharedResourcePointer<TooltipWindow> tooltipWindow;
    Rectangle<int> crossoverBounds;
    ScopedPointer<MONSTRCrossover> mCrossover;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MONSTRWidthSlider> width1Sld;
    ScopedPointer<MONSTRWidthSlider> width2Sld;
    ScopedPointer<MONSTRWidthSlider> width3Sld;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonstrAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_51C532A7320DE07A__
