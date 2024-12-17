/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KannenDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KannenDistortionAudioProcessorEditor (KannenDistortionAudioProcessor&);
    ~KannenDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Sliders for drive, range, blend, and volume
    std::unique_ptr<juce::Slider> driveKnob;
    std::unique_ptr<juce::Slider> rangeKnob;
    std::unique_ptr<juce::Slider> blendKnob;
    std::unique_ptr<juce::Slider> volKnob;

    // Slider attachments for binding sliders to the processor parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volAttachment;

    KannenDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KannenDistortionAudioProcessorEditor)
};
