/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.9

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "MONSTRLookAndFeel.h"
#include "MONSTRCrossoverWrapperComponent.h"
#include "CoreJUCEPlugin/CoreProcessorEditor.h"
#include "CoreJUCEPlugin/TooltipLabelUpdater.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MonstrAudioProcessorEditor  : public WECore::JUCEPlugin::CoreProcessorEditor,
                                    public Timer,
                                    public juce::Button::Listener
{
public:
    //==============================================================================
    MonstrAudioProcessorEditor (MonstrAudioProcessor& ownerFilter);
    ~MonstrAudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    MonstrAudioProcessor* getProcessor() const {
        return static_cast<MonstrAudioProcessor*>(getAudioProcessor());
    }
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MONSTRLookAndFeel customLookAndFeel;
    WECore::JUCEPlugin::TooltipLabelUpdater _tooltipLabelUpdater;

    virtual void _onParameterUpdate() override;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<MONSTRCrossoverWrapperComponent> crossoverWrapper;
    std::unique_ptr<juce::TextButton> AddBandBtn;
    std::unique_ptr<juce::TextButton> RemoveBandBtn;
    std::unique_ptr<MONSTRWidthLabel> widthValueLbl;
    std::unique_ptr<juce::Label> tooltipLbl;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonstrAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

