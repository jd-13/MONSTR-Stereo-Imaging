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

    //[UserPreSize]
    addAndMakeVisible(mCrossover = new MONSTRCrossover("mCrossover",
                                                       getProcessor()));
    crossoverBounds = Rectangle<int>(40,
                                     40,
                                     560,
                                     210);
    //[/UserPreSize]

    setSize (640, 290);


    //[Constructor] You can add your own custom stuff here..
    startTimer(200);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);
    
    // Define a rectangle for the sine wave to be drawn in

    
    //[/Constructor]
}

MonstrAudioProcessorEditor::~MonstrAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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

    //[UserResized] Add your own custom resize handling here..
    mCrossover->setBounds(crossoverBounds);
    //[/UserResized]
}

void MonstrAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MonstrAudioProcessorEditor::timerCallback() {

    MonstrAudioProcessor* ourProcessor = getProcessor();
    
    if (ourProcessor->NeedsUIUpdate()) {
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
