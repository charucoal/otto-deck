#include <JuceHeader.h>
#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse,
                                 AudioThumbnailCache & cacheToUse) : audioThumb(1000,
                                                                                formatManagerToUse,
                                                                                cacheToUse),
                                                                     fileLoaded(false),
                                                                     position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
    
}

// only called when necessary
void WaveformDisplay::paint (juce::Graphics& g)
{
    // start of code I wrote
    g.fillAll(Colours::black);
    // end of code I wrote
    
    // draws the waveform + playhead here
    if(fileLoaded)
    {
        // draws pale orange waveform
        
        // start of code I wrote
        g.setColour (juce::Colours::papayawhip);
        // end of code I wrote
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.0f);
        
        // draws red playhead
        
        // start of code I wrote
        g.setColour(Colours::red);
        g.drawRect(position * getWidth(), 0, 3, getHeight());
        g.fillRect(position * getWidth(), 0, 3, getHeight());
        // end of code I wrote
    }
    
    // draws some placeholder text
    else
    {
        g.setFont (20.0f);
        g.setColour (juce::Colours::papayawhip);
        g.drawText ("File Not Loaded Yet...", getLocalBounds(),
                    juce::Justification::centred, true);
    }
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::loadURL(URL audioURL)
{
    std::cout << "WFD: loadURL" << std::endl;
    
    audioThumb.clear();
    
    // returns true if the source could be opened as a valid audio file, else false
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    
    if(fileLoaded)
    {
        std::cout << "WFD: loaded!" << std::endl;
    }
    
    else
    {
        std::cout << "WFD: not loaded!" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source)
{
    std::cout << "WFD: change received" << std::endl;
    
    repaint(); // calls repaint when there is a change
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if(pos != position)
    {
        position = pos;
        repaint();
    }
}
