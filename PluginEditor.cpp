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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MonstrAudioProcessorEditor::MonstrAudioProcessorEditor (MonstrAudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (crossoverSld = new Slider ("Crossover Slider"));
    crossoverSld->setRange (0, 10, 0);
    crossoverSld->setSliderStyle (Slider::ThreeValueHorizontal);
    crossoverSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    crossoverSld->addListener (this);

    addAndMakeVisible (width1Sld = new Slider ("Band 1 Width Slider"));
    width1Sld->setRange (0, 10, 0);
    width1Sld->setSliderStyle (Slider::LinearVertical);
    width1Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width1Sld->addListener (this);

    addAndMakeVisible (width2Sld = new Slider ("Band 2 Width Slider"));
    width2Sld->setRange (0, 10, 0);
    width2Sld->setSliderStyle (Slider::LinearVertical);
    width2Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width2Sld->addListener (this);

    addAndMakeVisible (width3Sld = new Slider ("Band 3 Width Slider"));
    width3Sld->setRange (0, 10, 0);
    width3Sld->setSliderStyle (Slider::LinearVertical);
    width3Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width3Sld->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    getProcessor()->RequestUIUpdate();
    startTimer(200);
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    crossoverSld = nullptr;
    width1Sld = nullptr;
    width2Sld = nullptr;
    width3Sld = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MonstrAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MonstrAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    crossoverSld->setBounds (16, 16, 344, 88);
    width1Sld->setBounds (40, 176, 48, 264);
    width2Sld->setBounds (136, 176, 48, 264);
    width3Sld->setBounds (240, 176, 48, 264);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MonstrAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == crossoverSld)
    {
        //[UserSliderCode_crossoverSld] -- add your slider handling code here..
        //[/UserSliderCode_crossoverSld]
    }
    else if (sliderThatWasMoved == width1Sld)
    {
        //[UserSliderCode_width1Sld] -- add your slider handling code here..
        //[/UserSliderCode_width1Sld]
    }
    else if (sliderThatWasMoved == width2Sld)
    {
        //[UserSliderCode_width2Sld] -- add your slider handling code here..
        //[/UserSliderCode_width2Sld]
    }
    else if (sliderThatWasMoved == width3Sld)
    {
        //[UserSliderCode_width3Sld] -- add your slider handling code here..
        //[/UserSliderCode_width3Sld]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MonstrAudioProcessorEditor::timerCallback() {
    MonstrAudioProcessor* ourProcessor = getProcessor();

    if (ourProcessor->NeedsUIUpdate()) {

    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MonstrAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="MonstrAudioProcessor&amp; ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Crossover Slider" id="23e2227821456115" memberName="crossoverSld"
          virtualName="" explicitFocusOrder="0" pos="16 16 344 88" min="0"
          max="10" int="0" style="ThreeValueHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 1 Width Slider" id="a19cf5783381f0f4" memberName="width1Sld"
          virtualName="" explicitFocusOrder="0" pos="40 176 48 264" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 2 Width Slider" id="4c81fe5c3b84dad" memberName="width2Sld"
          virtualName="" explicitFocusOrder="0" pos="136 176 48 264" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 3 Width Slider" id="f1626a0c5e7a4180" memberName="width3Sld"
          virtualName="" explicitFocusOrder="0" pos="240 176 48 264" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
