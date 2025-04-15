#include <JuceHeader.h>
#include "PlaylistComponent.h"

PlaylistComponent::PlaylistComponent(AudioFormatManager & formatManagerToUse,
                                     AudioThumbnailCache & cacheToUse) : waveformDisplay(formatManagerToUse, cacheToUse)
{
    // track name to show when no files have been uploaded to playlist queue
    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");
    trackTitles.push_back("Track 7");

    // header names for playlist table
    tableComponent.getHeader().addColumn("", 1, 1); // columnID cannot be 0?
    tableComponent.getHeader().addColumn("TRACK TITLE", 2, 1);
    tableComponent.getHeader().addColumn("", 3, 1);
    tableComponent.getHeader().addColumn("", 4, 1);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
    
    // start of code I wrote
    // playlist table colour settings
    tableComponent.getHeader().setColour(tableComponent.getHeader().backgroundColourId, Colours::black);
    tableComponent.getHeader().setColour(tableComponent.getHeader().textColourId, Colours::papayawhip);
    tableComponent.getHeader().setColour(tableComponent.getHeader().outlineColourId, Colours::transparentBlack);

    // puts the file's path to empty when no files have been uploaded to playlist queue
    initialLink = URL(File(""));
    
    for(int i = 0; i < trackTitles.size(); ++i)
    {
        path.push_back(initialLink);
    }
    // end of code I wrote
}

PlaylistComponent::~PlaylistComponent()
{
    
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    // start of code I wrote
    g.fillAll(Colours::black); // background
    g.setFont (14.0f);
    // end of code I wrote
}

void PlaylistComponent::resized()
{
    // set playlist table's dimensions
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    
    // start of code I wrote
    // set height of playlist table's rows
    tableComponent.setHeaderHeight(getHeight()/8); // header row
    tableComponent.setRowHeight(getHeight()/8); // track rows
    
    // set width of playlist table's columns
    tableComponent.getHeader().setColumnWidth(1, getWidth() * 0.1);
    tableComponent.getHeader().setColumnWidth(2, getWidth() * 0.5);
    tableComponent.getHeader().setColumnWidth(3, getWidth() * 0.2);
    tableComponent.getHeader().setColumnWidth(4, getWidth() * 0.2);
    // end of code I wrote
}

int PlaylistComponent::getNumRows()
{
    return int(trackTitles.size());
}

void PlaylistComponent::paintRowBackground(Graphics & g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
    // start of code I wrote
    if(rowIsSelected)
    {
        g.fillAll(Colours::darkslategrey);
    }
    
    else
    {
        g.fillAll(Colours::black);
    }
    // end of code I wrote
}

void PlaylistComponent::paintCell(Graphics & g,
                                  int rowNumber,
                                  int columnId,
                                  int width,
                                  int height,
                                  bool rowIsSelected)
{
    // serial number column
    // start of code I wrote
    if(columnId == 1)
    {
        g.setColour(Colours::papayawhip);
        g.drawText(String(rowNumber + 1),
                   0, 0,
                   width, height,
                   Justification::horizontallyCentred,
                   true);
    }
    // end of code I wrote
    
    // track title column
    if(columnId == 2)
    {
        // start of code I wrote
        g.setColour(Colours::papayawhip);
        // end of code I wrote
        
        g.drawText(trackTitles[rowNumber],
                   5, 0,
                   width - 4, height,
                   Justification::centredLeft,
                   true);
    }
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component *existingComponentToUpdate)
{
    // start of code I wrote
    // upload track column
    if(columnId == 3)
    {
        if(existingComponentToUpdate == nullptr)
        {
            // adds upload button
            TextButton* btn = new TextButton{"UPLOAD"};
            String id{std::to_string(rowNumber)};
            btn -> setComponentID(id); // indicates row number on button
            
            btn->addListener(this);
            
            // sets upload button to green text and outline with no fill
            btn->setColour(0x1000100, Colours::transparentBlack); // button colour
            btn->setColour(btn->textColourOnId, Colours::forestgreen); // text colour when button is on
            btn->setColour(btn->textColourOffId, Colours::forestgreen); // text colour when button is off
            btn->setColour(ComboBox::outlineColourId, Colours::forestgreen); // button outline
            
            existingComponentToUpdate = btn;
        }
    }
    // end of code I wrote
    
    // start of code I wrote
    // remove track column
    if(columnId == 4)
    {
        if(existingComponentToUpdate == nullptr)
        {
            // adds remove button
            TextButton* btn = new TextButton{"REMOVE"};
            String id{std::to_string(rowNumber)};
            btn -> setComponentID(id); // indicates row number on button
            
            btn->addListener(this);
            
            // sets remove button to red text and outline with no fill
            btn->setColour(0x1000100, Colours::transparentBlack); // button colour
            btn->setColour(btn->textColourOnId, Colours::red); // text colour when button is on
            btn->setColour(btn->textColourOffId, Colours::red); // text colour when button is off
            btn->setColour(ComboBox::outlineColourId, Colours::red); // button outline
            
            existingComponentToUpdate = btn;
        }
    }
    // end of code I wrote
    
    return existingComponentToUpdate;
}

// calls this function when a button (upload / remove) is clicked
void PlaylistComponent::buttonClicked(Button* button)
{
    // JUCE string --> std::string --> int
    int id = stoi(button->getComponentID().toStdString());
    
    // start of code I wrote
    for (int i = 0; i < trackTitles.size(); ++i)
    {
        // start of code I wrote
        // upload button actions
        if(id == i && button->getX() == getWidth()*0.6)
        {
            // shows the file explorer to choose audio file
            auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
            fChooser.launchAsync(fileChooserFlags, [this, i](const FileChooser& chooser)
            {
                auto chosenFile = chooser.getResult();
                trackTitles[i] = chooser.getURLResult().getFileName().toStdString(); // gets filename to display
                path[i] = chooser.getURLResult(); // changes empty filepath to track's filepath
            });
        }

        // remove button actions
        if(id == i && button->getX() == getWidth()*0.8)
        {
            trackTitles[i] = "Track " + std::to_string(i + 1); // puts track number in place of removed track title
            path[i] = initialLink; // changes filepath to empty path
            removeClicked = true; // to remove from playback queue in DeckGUI
        }
    }
    // end of code I wrote
}
