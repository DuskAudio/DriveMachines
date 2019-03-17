/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "ff_meters/ff_meters.h"

//==============================================================================
VolumeSliderNewAudioProcessorEditor::VolumeSliderNewAudioProcessorEditor(VolumeSliderNewAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	//Allocating on the Heap
	volumeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, volumeSlider);
	invertValue = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, POLARITY_ID, invertToggle);
	highPassValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, HPF_ID, highPassfilter);
	saturationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, SAT_ID, saturationGain);
	drivesMenuValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.treeState,CMB_ID ,drivesMenu );

	

	//Volume Slider
	volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	volumeSlider.setColour(Slider::thumbColourId, Colours::orange);
	volumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	volumeSlider.setTextValueSuffix(" dB");

	addAndMakeVisible(&volumeSlider);

	//Volume Label
	volumeLabel.setText("Volume", dontSendNotification);
	volumeLabel.setColour(Label::outlineColourId, Colours::orange);
	volumeLabel.setJustificationType(juce::Justification::centredTop);
	volumeLabel.attachToComponent(&volumeSlider, false);

	addAndMakeVisible(&volumeLabel);

	//==============================================================

	//HighPass Slider
	highPassfilter.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	highPassfilter.setColour(Slider::thumbColourId, Colours::orange);
	highPassfilter.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	highPassfilter.setTextValueSuffix(" Hz");

	addAndMakeVisible(&highPassfilter);

	//HighPass Label
	highpassLabel.setText("HPF", dontSendNotification);
	highpassLabel.setJustificationType(juce::Justification::centredTop);
	highpassLabel.setColour(Label::outlineColourId, Colours::orange);
	highpassLabel.attachToComponent(&highPassfilter, false);

	addAndMakeVisible(&highpassLabel);

	//==============================================================

	//Clipper Slider
	saturationGain.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	saturationGain.setColour(Slider::thumbColourId, Colours::mediumpurple);
	saturationGain.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	saturationGain.setTextValueSuffix(" %");

	addAndMakeVisible(&saturationGain);

	//Clipper Label
	saturationLabel.setText("Drive", dontSendNotification);
	saturationLabel.setColour(Label::outlineColourId, Colours::mediumpurple);
	saturationLabel.setJustificationType(juce::Justification::centredBottom);
	saturationLabel.attachToComponent(&saturationGain, false);

	addAndMakeVisible(&saturationLabel);

	//==============================================================
	//Polarity reverse toggle Button
	invertToggle.setButtonText("Polarity");
	addAndMakeVisible(&invertToggle);

	//ComboBox Drives

	drivesMenu.addItem("Hard Clipper", 1);
	drivesMenu.addItem("Soft Clipper", 2);
	drivesMenu.addItem("Smoother"    , 3);
	drivesMenu.setJustificationType(juce::Justification::centredBottom);
	drivesMenu.setColour(ComboBox::backgroundColourId, Colours::transparentBlack);
	drivesMenu.setColour(ComboBox::outlineColourId, Colours::transparentBlack);
	drivesMenu.setColour(ComboBox::textColourId, Colours::orange);
	
	addAndMakeVisible(&drivesMenu);

	//Background
	background = ImageCache::getFromMemory(BinaryData::bg_duskSatur_png, BinaryData::bg_duskSatur_pngSize);

	//ff_audio Meter - Daniel JUCE discord
	//{
	//	lnf = new FFAU::LevelMeterLookAndFeel();
	//	// adjust the colours to how you like them
	//	lnf->setColour(FFAU::LevelMeter::lmMeterBackgroundColour, juce::Colours::black);
	//	lnf->setColour(FFAU::LevelMeter::lmBackgroundColour, juce::Colours::black);
	//	lnf->setColour(FFAU::LevelMeter::lmOutlineColour, juce::Colours::orange);
	//	lnf->setColour(FFAU::LevelMeter::lmTicksColour, juce::Colours::white);
	//	lnf->setColour(FFAU::LevelMeter::lmTextColour, juce::Colours::orange);
	//	lnf->setColour(FFAU::LevelMeter::lmMeterGradientLowColour, juce::Colours::orange);

	//	meter = new FFAU::LevelMeter(FFAU::LevelMeter::Horizontal); // See FFAU::LevelMeter::MeterFlags for options
	//	meter->setLookAndFeel(lnf);
	//	meter->setMeterSource(processor.getMeterSource());
	//	
	//	addAndMakeVisible(meter);
	//}

	setSize(435, 400);
}

VolumeSliderNewAudioProcessorEditor::~VolumeSliderNewAudioProcessorEditor()
{
}

//==============================================================================
void VolumeSliderNewAudioProcessorEditor::paint(Graphics& g)
{

	//g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	//g.fillAll(juce::Colours::black);
	g.drawImageAt(background, 0, 0);

	auto outerLine = getLocalBounds().toFloat().reduced(10.0f);
	g.setColour(Colours::orange);
	g.drawRoundedRectangle(outerLine, 5.0f, 3.0f);

	auto innerLine = getLocalBounds().toFloat().reduced(20.0f);
	g.setColour(Colours::mediumpurple);
	g.drawRoundedRectangle(innerLine, 5.0f, 3.0f);

	
}

void VolumeSliderNewAudioProcessorEditor::resized()
{
	auto r = getLocalBounds();
	auto topSection = r.removeFromTop(200);
	auto bottSection = r.removeFromBottom(200);

	invertToggle.setBounds(topSection.removeFromLeft(145).reduced(20));
	saturationGain.setBounds(topSection.removeFromLeft(145).reduced(20));
	drivesMenu.setBounds(topSection.removeFromLeft(145).reduced(20));

	volumeSlider.setBounds(bottSection.removeFromLeft(217.50).reduced(30));
	highPassfilter.setBounds(bottSection.removeFromLeft(217.50).reduced(30));




	//Old GUI
	//auto border = 30;
	//
	////Sliders
	//volumeSlider.setBounds(border, border, getWidth() - 300, getHeight() - 300);
	//saturationGain.setBounds(150, border, getWidth() - 300, getHeight() - 300);
	//highPassfilter.setBounds(270, border, getWidth() - 300, getHeight() - 300);
	//invertToggle.setBounds(170, 240, 80, 50);

	////Labels
	//volumeLabel.setBounds(70, 165, 50, 20);
	//saturationLabel.setBounds(196,165,40,20);
	//highpassLabel.setBounds(318,165,30,20);

	////ComboBox

	//drivesMenu.setBounds(175, 190, 80, 20);

	//meter->setBounds(25, 280, 380, 120);

}

