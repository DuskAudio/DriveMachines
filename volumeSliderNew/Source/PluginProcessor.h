/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"
#define POLARITY_ID "polarity"
#define POLARITY_NAME "Polarity"
#define HPF_ID "highPass"
#define HPF_NAME "HighPass"
#define SAT_ID "saturation"
#define SAT_NAME "Saturation"
#define CMB_ID "comboDrives"
#define CMB_NAME "ComboDrives"


//==============================================================================
/**
*/
class VolumeSliderNewAudioProcessor : public AudioProcessor
{
public:


	//==============================================================================
	VolumeSliderNewAudioProcessor();
	~VolumeSliderNewAudioProcessor();
	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void releaseResources() override;
	//==============================================================================
#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif
	//==============================================================================
	FFAU::LevelMeterSource* getMeterSource()
	{
		return &meterSource;
	}
	//==============================================================================
	FFAU::LevelMeter* clearMaxLevelDisplay()
	{
		const int channel = -1;
	}
	//==============================================================================
	void processBlock(AudioBuffer<float>& buffer, MidiBuffer&) override;
	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;
	void updateFilter();



	//float rawGainVolume;
	bool polarInvert;

	//==============================================================================

	AudioProcessorValueTreeState treeState;
	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();


private:
	dsp::ProcessorDuplicator < dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> highpassFilter;
	
	FFAU::LevelMeterSource meterSource;
	FFAU::OutlineBuffer outline;

	float lastSampleRate;



	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VolumeSliderNewAudioProcessor)
};
