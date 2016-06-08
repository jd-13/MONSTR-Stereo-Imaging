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

    addAndMakeVisible (crossoverLowerSld = new Slider ("Crossover Lower Slider"));
    crossoverLowerSld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
    "\n"
    "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
    "\n"
    "Right click near the middle of a band to bypass its stereo processing."));
    crossoverLowerSld->setRange (0, 1, 0);
    crossoverLowerSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverLowerSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverLowerSld->addListener (this);
    crossoverLowerSld->setSkewFactor (0.7);

    addAndMakeVisible (crossoverUpperSld = new Slider ("Crossover Upper Slider"));
    crossoverUpperSld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover freqencies of each band.\n"
    "\n"
    "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
    "\n"
    "Right click near the middle of a band to bypass its stereo processing."));
    crossoverUpperSld->setRange (0, 1, 0);
    crossoverUpperSld->setSliderStyle (Slider::LinearHorizontal);
    crossoverUpperSld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    crossoverUpperSld->addListener (this);
    crossoverUpperSld->setSkewFactor (0.7);

    addAndMakeVisible (width1Sld = new MONSTRWidthSlider ("Band 1 Width Slider",
                                                          getProcessor(),
                                                          MonstrAudioProcessor::isActiveBand1));
    width1Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
    "\n"
    "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
    "\n"
    "Right click near the middle of a band to bypass its stereo processing."));
    width1Sld->setRange (0, 1, 0.01);
    width1Sld->setSliderStyle (Slider::LinearVertical);
    width1Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width1Sld->addListener (this);

    addAndMakeVisible (width2Sld = new MONSTRWidthSlider ("Band 2 Width Slider",
                                                          getProcessor(),
                                                          MonstrAudioProcessor::isActiveBand2));
    width2Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
    "\n"
    "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
    "\n"
    "Right click near the middle of a band to bypass its stereo processing."));
    width2Sld->setRange (0, 1, 0.01);
    width2Sld->setSliderStyle (Slider::LinearVertical);
    width2Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width2Sld->addListener (this);

    addAndMakeVisible (width3Sld = new MONSTRWidthSlider ("Band 3 Width Slider",
                                                          getProcessor(),
                                                          MonstrAudioProcessor::isActiveBand3));
    width3Sld->setTooltip (TRANS("Drag the horizontal sliders left or right to change the crossover frequencies of each band.\n"
    "\n"
    "Drag up or down near the middle of a band to increase or decrease that band\'s stereo width.\n"
    "\n"
    "Right click near the middle of a band to bypass its stereo processing."));
    width3Sld->setRange (0, 1, 0.01);
    width3Sld->setSliderStyle (Slider::LinearVertical);
    width3Sld->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    width3Sld->addListener (this);


    //[UserPreSize]
    addAndMakeVisible(mCrossover = new MONSTRCrossover("mCrossover",
                                                       crossoverLowerSld,
                                                       crossoverUpperSld,
                                                       width1Sld,
                                                       width2Sld,
                                                       width3Sld));
    crossoverBounds = Rectangle<int>(40,
                                     40,
                                     560,
                                     210);
    //[/UserPreSize]

    setSize (640, 290);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);
    crossoverLowerSld->setSliderSnapsToMousePosition(false);
    crossoverUpperSld->setSliderSnapsToMousePosition(false);
    width1Sld->setSliderSnapsToMousePosition(false);
    width2Sld->setSliderSnapsToMousePosition(false);
    width3Sld->setSliderSnapsToMousePosition(false);

    crossoverLowerSld->setMouseDragSensitivity(100);
    crossoverUpperSld->setMouseDragSensitivity(100);
    crossoverLowerSld->setVelocityBasedMode(false);
    crossoverUpperSld->setVelocityBasedMode(false);
    
    mCrossover->toBack();
    
    // Define a rectangle for the sine wave to be drawn in

    
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    crossoverLowerSld = nullptr;
    crossoverUpperSld = nullptr;
    width1Sld = nullptr;
    width2Sld = nullptr;
    width3Sld = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    mCrossover = nullptr;
    //[/Destructor]
}

//==============================================================================
void MonstrAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..

    Image bg {ImageCache::getFromMemory(BinaryData::MONSTR_Background_png, BinaryData::MONSTR_Background_pngSize)};
    g.drawImage(bg, 0, 0, 640, 290, 0, 0, 5 * 640, 5 * 290);

    //[/UserPaint]
}

void MonstrAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    crossoverLowerSld->setBounds (16, 8, 288, 200);
    crossoverUpperSld->setBounds (312, 8, 288, 200);
    width1Sld->setBounds (64, 8, 72, 192);
    width2Sld->setBounds (232, 16, 72, 184);
    width3Sld->setBounds (432, 8, 72, 208);
    //[UserResized] Add your own custom resize handling here..
    mCrossover->setBounds(crossoverBounds);
    mCrossover->positionHorizontalSliders();
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MonstrAudioProcessorEditor::timerCallback() {

    MonstrAudioProcessor* ourProcessor = getProcessor();
    
    
    if (ourProcessor->NeedsUIUpdate()) {
        crossoverLowerSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverLower), dontSendNotification);
        crossoverUpperSld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::crossoverUpper), dontSendNotification);

        width1Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand1), dontSendNotification);
        width2Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand2), dontSendNotification);
        width3Sld->setValue(ourProcessor->getParameter(MonstrAudioProcessor::widthBand3), dontSendNotification);

        width1Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand1));
        width2Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand2));
        width3Sld->setEnabled(ourProcessor->getParameter(MonstrAudioProcessor::isActiveBand3));
        
        mCrossover->repaint();        
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MonstrAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="MonstrAudioProcessor&amp; ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="640" initialHeight="290">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Crossover Lower Slider" id="e131cd39bf883688" memberName="crossoverLowerSld"
          virtualName="" explicitFocusOrder="0" pos="16 8 288 200" tooltip="Drag the horizontal sliders left or right to change the crossover frequencies of each band.&#10;&#10;Drag up or down near the middle of a band to increase or decrease that band's stereo width.&#10;&#10;Right click near the middle of a band to bypass its stereo processing."
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.69999999999999995559"
          needsCallback="1"/>
  <SLIDER name="Crossover Upper Slider" id="d5eaf01002d1395" memberName="crossoverUpperSld"
          virtualName="" explicitFocusOrder="0" pos="312 8 288 200" tooltip="Drag the horizontal sliders left or right to change the crossover freqencies of each band.&#10;&#10;Drag up or down near the middle of a band to increase or decrease that band's stereo width.&#10;&#10;Right click near the middle of a band to bypass its stereo processing."
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="0.69999999999999995559"
          needsCallback="1"/>
  <SLIDER name="Band 1 Width Slider" id="a19cf5783381f0f4" memberName="width1Sld"
          virtualName="MONSTRWidthSlider" explicitFocusOrder="0" pos="64 8 72 192"
          tooltip="Drag the horizontal sliders left or right to change the crossover frequencies of each band.&#10;&#10;Drag up or down near the middle of a band to increase or decrease that band's stereo width.&#10;&#10;Right click near the middle of a band to bypass its stereo processing."
          min="0" max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="Band 2 Width Slider" id="4c81fe5c3b84dad" memberName="width2Sld"
          virtualName="MONSTRWidthSlider" explicitFocusOrder="0" pos="232 16 72 184"
          tooltip="Drag the horizontal sliders left or right to change the crossover frequencies of each band.&#10;&#10;Drag up or down near the middle of a band to increase or decrease that band's stereo width.&#10;&#10;Right click near the middle of a band to bypass its stereo processing."
          min="0" max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="Band 3 Width Slider" id="f1626a0c5e7a4180" memberName="width3Sld"
          virtualName="MONSTRWidthSlider" explicitFocusOrder="0" pos="432 8 72 208"
          tooltip="Drag the horizontal sliders left or right to change the crossover frequencies of each band.&#10;&#10;Drag up or down near the middle of a band to increase or decrease that band's stereo width.&#10;&#10;Right click near the middle of a band to bypass its stereo processing."
          min="0" max="1" int="0.010000000000000000208" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
