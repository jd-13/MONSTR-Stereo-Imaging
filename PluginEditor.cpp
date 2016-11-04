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
    addAndMakeVisible(mCrossover = new MONSTRCrossoverComponent("mCrossover",
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
