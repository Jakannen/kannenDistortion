# kannenDistortion

This project is a personal implementation of a **VST Distortion Effect Plugin** created using the [JUCE Framework](https://juce.com). The plugin provides a simple and effective audio distortion effect with adjustable parameters to shape the sound as needed.

## Features

The plugin provides the following adjustable controls:

- **Drive**: Controls the intensity of the distortion effect.
- **Range**: Adjusts the frequency range affected by the distortion.
- **Blend**: Balances between the distorted and clean signal.
- **Volume**: Controls the output volume.

## Requirements

To build and use the plugin, you need the following:

- **JUCE Framework**: Download from [juce.com](https://juce.com).
- **C++ Compiler**: Compatible with JUCE projects.
- **DAW (Digital Audio Workstation)**: For testing and using the plugin.

The plugin has been tested and works with FL Studio and other VST-supported hosts.

## Installation

1. Clone this repository to your local system

2. Open the project in Projucer (part of JUCE Framework).

3. Export the project for your desired IDE (Visual Studio, Xcode, CodeBlocks, etc.).

4. Build the project in your IDE to create the plugin binary (VST or AU file).

5. Copy the compiled plugin file to your DAW's plugin directory.

6. Scan for and load the kannenDistortion Plugin.

## Usage
### Controls

The plugin provides an intuitive UI with four rotary knobs:

- Drive: Increase to add more distortion to the signal.
- Range: Tune the frequency range to focus the distortion.
- Blend: Blend between clean and distorted signal.
- Volume: Control the final output volume after distortion.

#### Example Workflow
- Load the plugin onto an audio track.
- Set the Drive to taste (start around 0.5 for subtle distortion).
- Adjust the Range to focus on bass, mids, or treble.
- Use Blend to mix in the original clean signal.
- Tweak the Volume to maintain output consistency.
