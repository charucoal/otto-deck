#pragma once

#include <vector>
#include <string>

#include <JuceHeader.h>
#include "WaveformDisplay.h"

class PlaylistComponent : public juce::Component,
                          public TableListBoxModel,
                          public Button::Listener
{
    public:
        PlaylistComponent(AudioFormatManager & formatManagerToUse,
                          AudioThumbnailCache & cacheToUse);
        ~PlaylistComponent() override;

        void paint (juce::Graphics&) override;
        void resized() override;
        
        // inherited from TableListBoxModel
        int getNumRows() override;
        void paintRowBackground(Graphics &,
                                int rowNumber,
                                int width,
                                int height,
                                bool rowIsSelected) override;
        
        void paintCell(Graphics &,
                       int rowNumber,
                       int columnId,
                       int width,
                       int height,
                       bool rowIsSelected) override;
        
        Component* refreshComponentForCell(int rowNumber,
                                           int columnId,
                                           bool isRowSelected,
                                           Component *existingComponentToUpdate) override;
        
        // start of code I wrote
        void buttonClicked(Button* button) override;
        
        std::vector<URL> path; // stores audio file's path
        std::vector<std::string> trackTitles; // stores audio file's name
        
        URL initialLink; // set to empty path
        bool removeClicked; // checks if remove button is clicked
        // end of code I wrote

    private:
        TableListBox tableComponent;
        WaveformDisplay waveformDisplay;
        FileChooser fChooser{"Select a file..."};
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
