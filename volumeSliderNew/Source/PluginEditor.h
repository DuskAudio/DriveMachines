/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class VolumeSliderNewAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    VolumeSliderNewAudioProcessorEditor (VolumeSliderNewAudioProcessor&);
    ~VolumeSliderNewAudioProcessorEditor();
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
private:
    
    VolumeSliderNewAudioProcessor& processor;

	Slider volumeSlider,highPassSlider,saturationSlider;
	Label volumeLabel, highpassLabel,saturationLabel;
	ToggleButton invertToggle;
	ComboBox drivesMenu;
	Image background;

	ScopedPointer<FFAU::LevelMeter> meter;
	ScopedPointer<FFAU::LevelMeterLookAndFeel> lnf;

	

public:
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> saturationValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> highPassValue;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> invertValue;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> drivesMenuValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeSliderNewAudioProcessorEditor)
};
