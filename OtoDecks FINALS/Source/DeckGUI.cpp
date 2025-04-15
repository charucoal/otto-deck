#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse) : player(_player),
                                                     waveformDisplay(formatManagerToUse, cacheToUse)
{
    // show GUI items on deck
    addAndMakeVisible(waveformDisplay);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    // start of code I wrote
    addAndMakeVisible(gainText);
    addAndMakeVisible(speedText);
    addAndMakeVisible(posText);
    // end of code I wrote
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    //addAndMakeVisible(loadButton);
    
    // start of code I wrote
    addAndMakeVisible(restartButton);
    addAndMakeVisible(autoButton);
    
    addAndMakeVisible(nextButton);
    addAndMakeVisible(prevButton);
    addAndMakeVisible(clearButton);
    addAndMakeVisible(showTrack);
    // end of code I wrote
    
    addAndMakeVisible(playlistComponent);

    // listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    //loadButton.addListener(this);
    
    // start of code I wrote
    restartButton.addListener(this);
    autoButton.addListener(this);
    // end of code I wrote
    
    // start of code I wrote
    nextButton.addListener(this);
    prevButton.addListener(this);
    clearButton.addListener(this);
    // end of code I wrote

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    // start of code I wrote
    // slider settings
    gainText.setReadOnly(true);
    gainText.setText("GAIN");
    volSlider.setRange(0.0, 1.0);
    volSlider.setValue(1.0);
    
    speedText.setReadOnly(true);
    speedText.setText("SPEED");
    speedSlider.setRange(0.1, 10.0);
    speedSlider.setValue(1.0);
    
    posText.setReadOnly(true);
    posText.setText("POSITION");
    posSlider.setRange(0.0, 1.0);
    posSlider.setValue(0.0);
    
    // 1 milliseconds (every 0.001 seconds) -- CHANGE TIME TO MAKE THE PLAYHEAD UPDATE MORE REGULARLY
    startTimer(1);
    
    num = 0;
    index = 0; //
    
    autoPlay = false; // checks if autoplay button has been pressed
    clear = false; // checks if queue is empty
    // end of code I wrote // start of code I wrote
}

// called when an instance of the DeckGUI class is destroyed
DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    // start of code I wrote
    g.setFont (14.0f);
    
    // track name colour
    showTrack.setColour(0x1000100, Colours::black);
    
    // set sliders' colour
    // gain
    gainText.setColour(gainText.backgroundColourId, Colours::transparentBlack); // slider background colour
    volSlider.setColour(volSlider.rotarySliderFillColourId, Colours::darkorange); // slider fill
    volSlider.setColour(0x1001300, Colours::papayawhip); // slider cursor fill
    
    // speed
    speedText.setColour(speedText.backgroundColourId, Colours::transparentBlack); // slider background colour
    speedSlider.setColour(speedSlider.rotarySliderFillColourId, Colours::darkorange); // slider fill
    speedSlider.setColour(0x1001300, Colours::papayawhip); // slider cursor fill

    // position
    posText.setColour(speedText.backgroundColourId, Colours::transparentBlack); // slider background colour
    posSlider.setColour(posSlider.rotarySliderFillColourId, Colours::darkorange); // slider fill
    posSlider.setColour(0x1001300, Colours::papayawhip); // slider cursor fill
    
    // set buttons' colour
    playButton.setColour(0x1000100, Colours::darkturquoise);
    stopButton.setColour(0x1000100, Colours::darkblue);
    restartButton.setColour(0x1000100, Colours::darkblue);
    autoButton.setColour(0x1000100, Colours::darkblue);
    //loadButton.setColour(0x1000100, Colours::darkblue);
    
    prevButton.setColour(0x1000100, Colours::navy);
    nextButton.setColour(0x1000100, Colours::navy);
    clearButton.setColour(0x1000100, Colours::navy);
    
    // remove of outlines of GUI components
    playButton.setColour(ComboBox::outlineColourId, Colours::black);
    stopButton.setColour(ComboBox::outlineColourId, Colours::black);
    restartButton.setColour(ComboBox::outlineColourId, Colours::black);
    autoButton.setColour(ComboBox::outlineColourId, Colours::black);
    //loadButton.setColour(ComboBox::outlineColourId, Colours::black);
    
    prevButton.setColour(ComboBox::outlineColourId, Colours::black);
    nextButton.setColour(ComboBox::outlineColourId, Colours::black);
    clearButton.setColour(ComboBox::outlineColourId, Colours::black);
    
    gainText.setColour(gainText.outlineColourId, Colours::transparentBlack);
    speedText.setColour(speedText.outlineColourId, Colours::transparentBlack);
    posText.setColour(speedText.outlineColourId, Colours::transparentBlack);
    
    showTrack.setColour(ComboBox::outlineColourId, Colours::black);
    // end of code I wrote
}

void DeckGUI::resized()
{
    // start of code I wrote
    double rowH = getHeight() / 15;
    double colW = getWidth() / 3;
    
    showTrack.setBounds(0, rowH*0.5, getWidth(), rowH);
    waveformDisplay.setBounds(getWidth()*0.05, rowH * 2, getWidth()*0.9, rowH * 1.6);

    volSlider.setBounds(0, rowH * 4.5, colW, (rowH - 2)*3);
    gainText.setBounds((colW-40)/2, rowH * 4, 40, rowH/2);
    
    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false,
                              volSlider.getTextBoxWidth(),
                              volSlider.getTextBoxHeight());
    
    speedSlider.setBounds(colW, rowH * 4.5, colW, (rowH - 2)*3);
    speedText.setBounds((colW + (colW-45)/2), rowH * 4, 45, rowH/2);
    
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false,
                              volSlider.getTextBoxWidth(),
                              volSlider.getTextBoxHeight()*0.9);
    
    posSlider.setBounds(colW*2, rowH * 4.5, colW, (rowH - 2)*3);
    posText.setBounds((colW*2 + (colW-65)/2), rowH * 4, 65, rowH/2);
    
    posSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false,
                              volSlider.getTextBoxWidth(),
                              volSlider.getTextBoxHeight()*0.9);
    
    playButton.setBounds(0, rowH * 8, getWidth()/4, rowH);
    stopButton.setBounds(getWidth()/4, rowH * 8, getWidth()/4, rowH);
    restartButton.setBounds(getWidth() * 2/4, rowH * 8, getWidth()/4, rowH);
    autoButton.setBounds(getWidth() * 3/4, rowH * 8, getWidth()/4, rowH);
    //loadButton.setBounds(0, 0, getWidth(), rowH);
    
    prevButton.setBounds(0, rowH * 9, getWidth()/3, rowH);
    nextButton.setBounds(getWidth() * 1/3, rowH * 9, getWidth()/3, rowH);
    clearButton.setBounds(getWidth() * 2/3, rowH * 9, getWidth()/3, rowH);
    
    playlistComponent.setBounds(0, rowH * 10, getWidth(), rowH * 5);
    // end of code I wrote
}

void DeckGUI::buttonClicked(Button* button)
{
    // start of code I wrote
    std::vector<URL> list;
    std::vector<int> indexPos;
    int checkEmpty = 0;
    
    for(int i = 0; i < playlistComponent.path.size(); i++)
    {
        if(playlistComponent.path[i] != playlistComponent.initialLink)
        {
            list.push_back(playlistComponent.path[i]);
            indexPos.push_back(i);
            
            checkEmpty += 1;
        }
    }
    
    int length = int(list.size());
    // end of code I wrote
    
    if (button == &playButton and checkEmpty != 0)
    {
        std::cout << "Play button was clicked" << std::endl;
        player->start();
        
        // start of code I wrote
        if(player->getPositionRelative() >= 1)
        {
            player->setPosition(0.0);
        }
        
        std::string currentTrackTitle = playlistComponent.path[indexPos[num]].getFileName().toStdString();
        showTrack.setButtonText("CURRENTLY PLAYING:" + currentTrackTitle);
        // end of code I wrote
    }
    
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
        player->stop();
    }
    
//    if (button == &loadButton)
//    {
//        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
//        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
//        {
//            auto chosenFile = chooser.getResult();
//            player->loadURL(URL{chosenFile}); //loadURL(URL{playlistComponent.pathways[0]});
//            waveformDisplay.loadURL(URL{chosenFile}); // not a pointer, it's a regular object that's why no arrow (->)
//
//            std::string nextTrackTitle = chosenFile.getFileName().toStdString();
//        });
//    }
    
    // start of code I wrote
    if (button == &restartButton and checkEmpty != 0)
    {
        player->setPosition(0.0);
        if(autoPlay == false)
        {
            player->stop();
        }
    }
    
    if(button == &autoButton)
    {
        autoPlay = !autoPlay;
        
        if(autoPlay)
        {
            autoButton.setButtonText("AUTO: ON");
        }
        
        else
        {
            autoButton.setButtonText("AUTO: OFF");
        }
    }
    
    if (button == &nextButton)
    {
        if(autoPlay == false)
        {
            player->stop();
        }
        
        if(length >= 1)
        {
            std::string currentTrackTitle = playlistComponent.path[indexPos[num]].getFileName().toStdString();
            showTrack.setButtonText("CURRENTLY PLAYING: " + currentTrackTitle);
            
            if(length == 1)
            {
                player->loadURL(URL{list[0]});
                waveformDisplay.loadURL(URL{list[0]});
                
                std::string nextTrackTitle = list[0].getFileName().toStdString();
                nextButton.setButtonText("NEXT: " + nextTrackTitle);
            }
            
            else
            {
                // set prev button track title
                if(index - 1 == -1)
                {
                    std::string prevTrack = playlistComponent.path[indexPos[index]].getFileName().toStdString();
                    prevButton.setButtonText( "PREVIOUS: " + prevTrack);
                }
                
                else
                {
                    std::string prevTrack = playlistComponent.path[indexPos[index - 1]].getFileName().toStdString();
                    prevButton.setButtonText("PREVIOUS: " + prevTrack);
                }
                
                // set next button track title
                if(index + 1 == length)
                {
                    std::string nextTrack = playlistComponent.path[0].getFileName().toStdString();
                    nextButton.setButtonText("NEXT: " + nextTrack);
                }
                
                else
                {
                    std::string nextTrack = playlistComponent.path[indexPos[index + 1]].getFileName().toStdString();
                    nextButton.setButtonText("NEXT: " + nextTrack);
                }
                
                std::string currentTrackTitle = playlistComponent.path[indexPos[index]].getFileName().toStdString();
                
                player->loadURL(URL{playlistComponent.path[indexPos[index]]});
                waveformDisplay.loadURL(URL{playlistComponent.path[indexPos[index]]});
                
                index += 1;
                
                if(index == length)
                {
                    index = 0;
                }
            }
        }
    }
    
    if (button == &prevButton)
    {
        if(autoPlay == false)
        {
            player->stop();
        }
        
        if(length >= 1)
        {
            if(length == 1)
            {
                player->loadURL(URL{list[0]});
                waveformDisplay.loadURL(URL{list[0]});
                
                std::string nextTrackTitle = list[0].getFileName().toStdString();
                prevButton.setButtonText("PREVIOUS: " + nextTrackTitle);
            }
            
            else
            {
                // set prev button track title
                if(index - 1 == -1)
                {
                    std::string prevTrack = playlistComponent.path[indexPos[index]].getFileName().toStdString();
                    prevButton.setButtonText("PREVIOUS: " + prevTrack);
                }
                
                else
                {
                    std::string prevTrack = playlistComponent.path[indexPos[index - 1]].getFileName().toStdString();
                    prevButton.setButtonText("PREVIOUS: " + prevTrack);
                }
                
                // set next button track title
                if(index + 1 == length)
                {
                    std::string nextTrack = playlistComponent.path[0].getFileName().toStdString();
                    nextButton.setButtonText("NEXT: " + nextTrack);
                }
                
                else
                {
                    std::string nextTrack = playlistComponent.path[indexPos[index + 1]].getFileName().toStdString();
                    nextButton.setButtonText("NEXT: " + nextTrack);
                }
                
                std::string currentTrackTitle = playlistComponent.path[indexPos[index]].getFileName().toStdString();
                
                player->loadURL(URL{playlistComponent.path[indexPos[index]]});
                waveformDisplay.loadURL(URL{playlistComponent.path[indexPos[index]]});
                
                index -= 1;
                
                if(index == -1)
                {
                    index = length - 1;
                }
            }
        }
    }
    
    if (button == &clearButton)
    {
        player->stop();
        clear = true;
        autoPlay = false;
    }
    // end of code I wrote
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
        waveformDisplay.loadURL(URL{File{files[0]}});
    }
}
    
void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    
    // start of code I wrote
    int check = 1;
    
    if(playlistComponent.removeClicked)
    {
        check = 0;
        for(int i = 0; i < playlistComponent.path.size(); ++i)
        {
            if(playlistComponent.path[i] != playlistComponent.initialLink)
            {
                check += 1;
            }
        }
    }
    
    if(clear or check == 0)
    {
        if(check == 0)
        {
            player->stop();
        }
        
        for(int i = 0; i < playlistComponent.path.size(); ++i)
        {
            int in = i + 1;
            std::string index = std::to_string(in);
            playlistComponent.trackTitles[i] = "Track " + index;
            playlistComponent.path[i] = playlistComponent.initialLink;
        }
        
        showTrack.setButtonText("CURRENTLY PLAYING: ");
        nextButton.setButtonText("QUEUE PLAYLIST");
        prevButton.setButtonText("PREVIOUS TRACK");
        
        waveformDisplay.loadURL(URL{});
        
        clear = false;
        playlistComponent.removeClicked = false;
    }

    if(player->getPositionRelative() >= 1 && autoPlay)
    {
        std::vector<URL> list;
        std::vector<int> indexPos;
        
        for(int i = 0; i < playlistComponent.path.size(); ++i)
        {
            if(playlistComponent.path[i] != playlistComponent.initialLink)
            {
                list.push_back(playlistComponent.path[i]);
                indexPos.push_back(i);
            }
        }
        
        num += 1;
        
        if(num == list.size())
        {
            num = 0;
        }
        
        player->loadURL(URL{playlistComponent.path[indexPos[num]]});
        waveformDisplay.loadURL(URL{playlistComponent.path[indexPos[num]]});
        
        std::string currentTrackTitle = playlistComponent.path[indexPos[num]].getFileName().toStdString();
        
        player->start();
        
        showTrack.setButtonText("CURRENTLY PLAYING: " + currentTrackTitle);
        
        if(num + 1 == list.size())
        {
            std::string nextTrack = playlistComponent.path[indexPos[0]].getFileName().toStdString();
            nextButton.setButtonText("NEXT: " + nextTrack);
        }
        
        else
        {
            std::string nextTrack = playlistComponent.path[indexPos[num + 1]].getFileName().toStdString();
            nextButton.setButtonText("NEXT: " + nextTrack);
        }
        
        if(num - 1 == -1)
        {
            std::string previousTrack = playlistComponent.path[indexPos[list.size() - 1]].getFileName().toStdString();
            prevButton.setButtonText("PREVIOUS: " + previousTrack);
        }
        
        else
        {
            std::string previousTrack = playlistComponent.path[indexPos[num - 1]].getFileName().toStdString();
            prevButton.setButtonText("PREVIOUS: " + previousTrack);
        }
        
    }
}

bool DeckGUI::isEmpty()
{
    int checkEmpty = 0;
    
    // checks if there are empty path names
    for(int i = 0; i < playlistComponent.path.size(); ++i)
    {
        if(playlistComponent.path[i].getFileName().toStdString() != "")
        {
            checkEmpty += 1;
        }
    }
    
    if(checkEmpty != 0)
    {
        return false;
    }
    
    else
    {
        return true;
    }
    // end of code I wrote
}
