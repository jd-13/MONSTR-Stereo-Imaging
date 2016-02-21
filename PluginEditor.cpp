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

    addAndMakeVisible (width1Sld = new Slider ("Band 1 Width Slider"));
    width1Sld->setRange (0, 1, 0.01);
    width1Sld->setSliderStyle (Slider::LinearVertical);
    width1Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width1Sld->addListener (this);

    addAndMakeVisible (width2Sld = new Slider ("Band 2 Width Slider"));
    width2Sld->setRange (0, 1, 0.01);
    width2Sld->setSliderStyle (Slider::LinearVertical);
    width2Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width2Sld->addListener (this);

    addAndMakeVisible (width3Sld = new Slider ("Band 3 Width Slider"));
    width3Sld->setRange (0, 1, 0.01);
    width3Sld->setSliderStyle (Slider::LinearVertical);
    width3Sld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    width3Sld->addListener (this);

    addAndMakeVisible (crossoverLowerSld = new Slider ("Crossover Lower Slider"));
    crossoverLowerSld->setRange (0, 1, 0);
    crossoverLowerSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverLowerSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    crossoverLowerSld->addListener (this);

    addAndMakeVisible (crossoverUpperSld = new Slider ("Crossover Upper Slider"));
    crossoverUpperSld->setRange (0, 10, 0);
    crossoverUpperSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverUpperSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    crossoverUpperSld->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    width1Sld = nullptr;
    width2Sld = nullptr;
    width3Sld = nullptr;
    crossoverLowerSld = nullptr;
    crossoverUpperSld = nullptr;


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

    width1Sld->setBounds (16, 112, 72, 264);
    width2Sld->setBounds (120, 112, 72, 264);
    width3Sld->setBounds (216, 112, 72, 264);
    crossoverLowerSld->setBounds (16, 40, 168, 24);
    crossoverUpperSld->setBounds (192, 40, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MonstrAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    MonstrAudioProcessor* ourProcessor {getProcessor()};
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == width1Sld)
    {
        //[UserSliderCode_width1Sld] -- add your slider handling code here..
        ourProcessor->setParameter(MonstrAudioProcessor::widthBand1, static_cast<float>(width1Sld->getValue()));
        //[/UserSliderCode_width1Sld]
    }
    else if (sliderThatWasMoved == width2Sld)
    {
        //[UserSliderCode_width2Sld] -- add your slider handling code here..
        ourProcessor->setParameter(MonstrAudioProcessor::widthBand2, static_cast<float>(width2Sld->getValue()));
        //[/UserSliderCode_width2Sld]
    }
    else if (sliderThatWasMoved == width3Sld)
    {
        //[UserSliderCode_width3Sld] -- add your slider handling code here..
        ourProcessor->setParameter(MonstrAudioProcessor::widthBand3, static_cast<float>(width3Sld->getValue()));
        //[/UserSliderCode_width3Sld]
    }
    else if (sliderThatWasMoved == crossoverLowerSld)
    {
        //[UserSliderCode_crossoverLowerSld] -- add your slider handling code here..
        ourProcessor->setParameter(MonstrAudioProcessor::crossoverLower, static_cast<float>(crossoverLowerSld->getValue()));
        //[/UserSliderCode_crossoverLowerSld]
    }
    else if (sliderThatWasMoved == crossoverUpperSld)
    {
        //[UserSliderCode_crossoverUpperSld] -- add your slider handling code here..
        ourProcessor->setParameter(MonstrAudioProcessor::crossoverUpper, static_cast<float>(crossoverUpperSld->getValue()));
        //[/UserSliderCode_crossoverUpperSld]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MonstrAudioProcessorEditor::timerCallback() {
    MonstrAudioProcessor* ourProcessor = getProcessor();

    if (ourProcessor->NeedsUIUpdate()) {
        crossoverLowerSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverLower), dontSendNotification);
        crossoverUpperSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverUpper), dontSendNotification);

        width1Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand1), dontSendNotification);
        width2Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand2), dontSendNotification);
        width3Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand3), dontSendNotification);

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
                 fixedSize="1" initialWidth="600" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Band 1 Width Slider" id="a19cf5783381f0f4" memberName="width1Sld"
          virtualName="" explicitFocusOrder="0" pos="16 112 72 264" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 2 Width Slider" id="4c81fe5c3b84dad" memberName="width2Sld"
          virtualName="" explicitFocusOrder="0" pos="120 112 72 264" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 3 Width Slider" id="f1626a0c5e7a4180" memberName="width3Sld"
          virtualName="" explicitFocusOrder="0" pos="216 112 72 264" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Crossover Lower Slider" id="e131cd39bf883688" memberName="crossoverLowerSld"
          virtualName="" explicitFocusOrder="0" pos="16 40 168 24" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Crossover Upper Slider" id="d5eaf01002d1395" memberName="crossoverUpperSld"
          virtualName="" explicitFocusOrder="0" pos="192 40 150 24" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
