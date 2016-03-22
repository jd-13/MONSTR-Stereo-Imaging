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
#include "MONSTRCrossover.h"
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

    addAndMakeVisible (crossoverLowerSld = new Slider ("Crossover Lower Slider"));
    crossoverLowerSld->setRange (0, 1, 0);
    crossoverLowerSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverLowerSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverLowerSld->addListener (this);

    addAndMakeVisible (crossoverUpperSld = new Slider ("Crossover Upper Slider"));
    crossoverUpperSld->setRange (0, 1, 0);
    crossoverUpperSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverUpperSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverUpperSld->addListener (this);

    addAndMakeVisible (switchBand1Btn = new ToggleButton ("Switch Band 1 Button"));
    switchBand1Btn->setButtonText (TRANS("new toggle button"));
    switchBand1Btn->addListener (this);

    addAndMakeVisible (switchBand2Btn = new ToggleButton ("Switch Band 2 Button"));
    switchBand2Btn->setButtonText (TRANS("new toggle button"));
    switchBand2Btn->addListener (this);

    addAndMakeVisible (switchBand3Btn = new ToggleButton ("Switch Band 3 Button"));
    switchBand3Btn->setButtonText (TRANS("new toggle button"));
    switchBand3Btn->addListener (this);

    addAndMakeVisible (width1Sld = new Slider ("Band 1 Width Slider"));
    width1Sld->setRange (0, 1, 0.01);
    width1Sld->setSliderStyle (Slider::LinearVertical);
    width1Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width1Sld->addListener (this);

    addAndMakeVisible (width2Sld = new Slider ("Band 2 Width Slider"));
    width2Sld->setRange (0, 1, 0.01);
    width2Sld->setSliderStyle (Slider::LinearVertical);
    width2Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width2Sld->addListener (this);

    addAndMakeVisible (width3Sld = new Slider ("Band 3 Width Slider"));
    width3Sld->setRange (0, 1, 0.01);
    width3Sld->setSliderStyle (Slider::LinearVertical);
    width3Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width3Sld->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

    // Define a rectangle for the sine wave to be drawn in
    crossoverBounds = Rectangle<float>(crossoverLowerSld->getX(),
                                       crossoverLowerSld->getY(),
                                       crossoverUpperSld->getX() + crossoverUpperSld->getWidth() - crossoverLowerSld->getX(),
                                       crossoverLowerSld->getHeight());
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    crossoverLowerSld = nullptr;
    crossoverUpperSld = nullptr;
    switchBand1Btn = nullptr;
    switchBand2Btn = nullptr;
    switchBand3Btn = nullptr;
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


    // Then draw the sine
    MONSTRCrossover::update(g,
                            crossoverBounds,
                            TranslateParam_Norm2Inter(crossoverLowerSld->getValue(), CROSSOVERLOWER_MIN, CROSSOVERLOWER_MAX),
                            TranslateParam_Norm2Inter(crossoverUpperSld->getValue(), CROSSOVERUPPER_MIN, CROSSOVERUPPER_MAX),
                            *width1Sld,
                            *width2Sld,
                            *width3Sld);

    //[/UserPaint]
}

void MonstrAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    crossoverLowerSld->setBounds (16, 8, 288, 200);
    crossoverUpperSld->setBounds (312, 8, 288, 200);
    switchBand1Btn->setBounds (48, 232, 64, 40);
    switchBand2Btn->setBounds (144, 232, 64, 40);
    switchBand3Btn->setBounds (240, 232, 64, 40);
    width1Sld->setBounds (24, 280, 72, 264);
    width2Sld->setBounds (128, 280, 72, 264);
    width3Sld->setBounds (232, 288, 72, 256);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MonstrAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    MonstrAudioProcessor* ourProcessor {getProcessor()};
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == crossoverLowerSld)
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
    else if (sliderThatWasMoved == width1Sld)
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MonstrAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    MonstrAudioProcessor* ourProcessor {getProcessor()};
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == switchBand1Btn)
    {
        //[UserButtonCode_switchBand1Btn] -- add your button handler code here..
        //ourProcessor->setParameter(MonstrAudioProcessor::, <#float newValue#>)
        //[/UserButtonCode_switchBand1Btn]
    }
    else if (buttonThatWasClicked == switchBand2Btn)
    {
        //[UserButtonCode_switchBand2Btn] -- add your button handler code here..
        //[/UserButtonCode_switchBand2Btn]
    }
    else if (buttonThatWasClicked == switchBand3Btn)
    {
        //[UserButtonCode_switchBand3Btn] -- add your button handler code here..
        //[/UserButtonCode_switchBand3Btn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
  <SLIDER name="Crossover Lower Slider" id="e131cd39bf883688" memberName="crossoverLowerSld"
          virtualName="" explicitFocusOrder="0" pos="16 8 288 200" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Crossover Upper Slider" id="d5eaf01002d1395" memberName="crossoverUpperSld"
          virtualName="" explicitFocusOrder="0" pos="312 8 288 200" min="0"
          max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <TOGGLEBUTTON name="Switch Band 1 Button" id="2480ca9153c32a51" memberName="switchBand1Btn"
                virtualName="" explicitFocusOrder="0" pos="48 232 64 40" buttonText="new toggle button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="Switch Band 2 Button" id="3247d14a24a05021" memberName="switchBand2Btn"
                virtualName="" explicitFocusOrder="0" pos="144 232 64 40" buttonText="new toggle button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="Switch Band 3 Button" id="d478f5021d1920df" memberName="switchBand3Btn"
                virtualName="" explicitFocusOrder="0" pos="240 232 64 40" buttonText="new toggle button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="Band 1 Width Slider" id="a19cf5783381f0f4" memberName="width1Sld"
          virtualName="" explicitFocusOrder="0" pos="24 280 72 264" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 2 Width Slider" id="4c81fe5c3b84dad" memberName="width2Sld"
          virtualName="" explicitFocusOrder="0" pos="128 280 72 264" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Band 3 Width Slider" id="f1626a0c5e7a4180" memberName="width3Sld"
          virtualName="" explicitFocusOrder="0" pos="232 288 72 256" min="0"
          max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
