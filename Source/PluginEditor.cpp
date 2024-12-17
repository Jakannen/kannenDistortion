/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KannenDistortionAudioProcessorEditor::KannenDistortionAudioProcessorEditor (KannenDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Initialize the knobs (sliders)
    driveKnob = std::make_unique<juce::Slider>("Drive");
    driveKnob->setSliderStyle(juce::Slider::Rotary);
    driveKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    driveKnob->setRange(0.0, 1.0, 0.0001); // Set range for the Drive knob
    driveKnob->setValue(1.0); // Default value

    rangeKnob = std::make_unique<juce::Slider>("Range");
    rangeKnob->setSliderStyle(juce::Slider::Rotary);
    rangeKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    rangeKnob->setRange(0.0, 3000.0, 0.0001); // Set range for the Range knob
    rangeKnob->setValue(1.0); // Default value

    blendKnob = std::make_unique<juce::Slider>("Blend");
    blendKnob->setSliderStyle(juce::Slider::Rotary);
    blendKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    blendKnob->setRange(0.0, 1.0, 0.0001); // Set range for the Blend knob
    blendKnob->setValue(1.0); // Default value

    volKnob = std::make_unique<juce::Slider>("Volume");
    volKnob->setSliderStyle(juce::Slider::Rotary);
    volKnob->setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    volKnob->setRange(0.0, 3.0, 0.0001); // Set range for the Volume knob
    volKnob->setValue(1.0); // Default value

    // Add knobs to the editor component
    addAndMakeVisible(*driveKnob);
    addAndMakeVisible(*rangeKnob);
    addAndMakeVisible(*blendKnob);
    addAndMakeVisible(*volKnob);

    // Attach the sliders to the parameters in the AudioProcessor
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), "drive", *driveKnob);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), "range", *rangeKnob);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), "blend", *blendKnob);
    volAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getState(), "volume", *volKnob);

    // Set the size of the editor window
    setSize(500, 200);
}

KannenDistortionAudioProcessorEditor::~KannenDistortionAudioProcessorEditor()
{
}

//==============================================================================
void KannenDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawText("Drive", (getWidth() / 5 * 1) - 50, (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Range", (getWidth() / 5 * 2) - 50, (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Blend", (getWidth() / 5 * 3) - 50, (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
    g.drawText("Volume", (getWidth() / 5 * 4) - 50, (getHeight() / 2) + 5, 100, 100, juce::Justification::centred, false);
}

void KannenDistortionAudioProcessorEditor::resized()
{
    driveKnob->setBounds((getWidth() / 5 * 1) - 50, (getHeight() / 2) - 50, 100, 100);
    rangeKnob->setBounds((getWidth() / 5 * 2) - 50, (getHeight() / 2) - 50, 100, 100);
    blendKnob->setBounds((getWidth() / 5 * 3) - 50, (getHeight() / 2) - 50, 100, 100);
    volKnob->setBounds((getWidth() / 5 * 4) - 50, (getHeight() / 2) - 50, 100, 100);
}
