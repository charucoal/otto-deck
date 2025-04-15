# OtoDecks – C++ Audio Mixing Application

## Overview

OtoDecks is a basic digital DJ application developed in C++ using the JUCE framework. It simulates the core features of a DJ deck, allowing users to load, play, and mix audio tracks in real-time through an interactive graphical user interface.

This project demonstrates fundamental audio processing, GUI development, and user interaction in C++, providing a hands-on introduction to multimedia programming.

## Core Components and Functions

### MainComponent
- Acts as the central controller of the application.
- Hosts two deck interfaces and the playlist manager.
- Coordinates playback and user interaction.

### DeckGUI
- Provides a visual interface for each DJ deck.
- Displays waveforms, buttons, sliders, and volume controls.
- Interfaces directly with the audio player to control playback.

### DJAudioPlayer
- Handles core audio playback functions.
- Uses JUCE audio classes such as `TransportSource`, `ResamplingAudioSource`, and `AudioFormatReaderSource`.

### PlaylistComponent
- Manages the playlist of audio tracks.
- Allows users to upload, remove, and view tracks in a queue.
- Displays track details using JUCE's `TableListBoxModel`.

### WaveformDisplay
- Draws a real-time waveform of the currently playing audio.
- Shows a moving playhead to indicate progress.
- Helps users visually cue and manage playback.

## Purpose

OtoDecks serves as a beginner-to-intermediate level project for understanding:
- Audio playback in C++
- GUI development using JUCE
- Real-time media interaction
- Object-oriented software design

## Note

This is an educational project and not intended for professional DJ use. It focuses on demonstrating the integration of multiple C++ and JUCE components into a functional multimedia application.

