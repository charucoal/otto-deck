#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"

class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer
{
    public:
        DeckGUI(DJAudioPlayer* player,
                AudioFormatManager & formatManagerToUse,
                AudioThumbnailCache & cacheToUse);
        
        ~DeckGUI();

        void paint (Graphics&) override;
        void resized() override;
    
        DJAudioPlayer* player;
        PlaylistComponent playlistComponent{formatManager, thumbCache};

        // implement Button::Listener
        void buttonClicked (Button *) override;

        // implement Slider::Listener
        void sliderValueChanged (Slider *slider) override;

        // to drag file to load to deck
        bool isInterestedInFileDrag (const StringArray &files) override;
        void filesDropped (const StringArray &files, int x, int y) override;
        
        // allows for continous update of the audio application
        void timerCallback() override;
    
        // start of code I wrote
        // returns true if queue is empty, else false
        bool isEmpty();
        // end of code I wrote

    private:
    
        // start of code I wrote
        int num; // number of songs uploaded to queue
        int index; // variable to navigate the list of indexes of where songs are uploaded from playlist
        bool autoPlay; // checks if autoplay button has been pressed
        bool clear; // checks if queue is empty
        // end of code I wrote

        FileChooser fChooser{"Select a file..."};
        
        WaveformDisplay waveformDisplay;
        
        // start of code I wrote
        AudioFormatManager formatManager;
        AudioThumbnailCache thumbCache{100};
        // end of code I wrote
    
        // sliders for gain (volume), speed and position
        Slider volSlider;
        Slider speedSlider;
        Slider posSlider;
        
        // start of code I wrote
        // slider labels
        TextEditor gainText;
        TextEditor speedText;
        TextEditor posText;
        // end of code I wrote
        
        // buttons to control music playback
        TextButton playButton{"PLAY"};
        TextButton stopButton{"PAUSE"};
        //TextButton loadButton{"LOAD"};
        
        // start of code I wrote
        TextButton restartButton{"RESTART"};
        TextButton autoButton{"AUTO: OFF"};
        // end of code I wrote
        
        // start of code I wrote
        // buttons for accessing playlist
        TextButton nextButton{"QUEUE PLAYLIST"};
        TextButton prevButton{"PREVIOUS TRACK"};
        TextButton clearButton{"CLEAR QUEUE"};
        
        // shows current track playing
        TextButton showTrack{"CURRENTLY PLAYING: "};
        // end of code I wrote

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
