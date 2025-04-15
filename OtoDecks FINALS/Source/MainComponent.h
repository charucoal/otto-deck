#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

// start of code I wrote
#include "RandomGenerator.h"
// end of code I wrote

class MainComponent : public AudioAppComponent,
                      // start of code I wrote
                      public Slider::Listener,
                      public Button::Listener
                      // end of code I wrote
{
    public:
        MainComponent();
        ~MainComponent();

        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        void paint (Graphics& g) override;
        void resized() override;

    private:
        AudioFormatManager formatManager;
        AudioThumbnailCache thumbCache{100}; // will store upto a 100 cached waveforms at any one time
        
        MixerAudioSource mixerSource; // allows 2 or more audios to be played at the same time
        
        // LEFT DECK
        DJAudioPlayer player1{formatManager};
        DeckGUI deckGUI1{&player1, formatManager, thumbCache};

        // RIGHT DECK
        DJAudioPlayer player2{formatManager};
        DeckGUI deckGUI2{&player2, formatManager, thumbCache};
    
        // start of code I wrote
        
        void sliderValueChanged (Slider *slider) override;
        void buttonClicked (Button *) override;
        
        // MASTER DECK
        TextButton masterPlay{"PLAY"};
        TextButton masterPause{"PAUSE"};
        TextButton masterShuffle{"SHUFFLE"};
        
        Slider masterVol;
        
        // PSUEDO-RANDOM NUMBER GENERATOR
        RandomGenerator randNum;
        
        int indexPos1; // 0 - 499
        int indexPos2; // 500 - 999
    
        // end of code I wrote
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
