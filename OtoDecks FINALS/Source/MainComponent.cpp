#include "MainComponent.h"

MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    // start of code I wrote
    
    // master deck
    addAndMakeVisible(masterPlay);
    addAndMakeVisible(masterPause);
    addAndMakeVisible(masterShuffle);
    addAndMakeVisible(masterVol);
    
    // button listeners
    masterPlay.addListener(this);
    masterPause.addListener(this);
    masterShuffle.addListener(this);
    
    // slider listeners
    masterVol.addListener(this);
    masterVol.setRange(-1.0,1.0);
    masterVol.setValue(0.0);
    
    // end of code I wrote
    
    // sub decks
    addAndMakeVisible(deckGUI1); 
    addAndMakeVisible(deckGUI2);

    // need to call, if not it does not know the audio formats
    formatManager.registerBasicFormats();
    
    // start of code I wrote
    indexPos1 = 0;
    indexPos2 = 500;
    // end of code I wrote
}

MainComponent::~MainComponent()
{
    // shuts down the audio device and clears the audio source.
    shutdownAudio();
}

// birth
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

// life
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

// death
void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

void MainComponent::paint (Graphics& g)
{
    // start of code I wrote
    
    g.fillAll(Colours::black);
    
    // remove outlines of master deck buttons
    masterPlay.setColour(ComboBox::outlineColourId, Colours::black);
    masterPause.setColour(ComboBox::outlineColourId, Colours::black);
    masterShuffle.setColour(ComboBox::outlineColourId, Colours::black);
    masterVol.setColour(masterVol.textBoxOutlineColourId, Colours::black);

    // set fill colour of master deck buttons
    masterPlay.setColour(0x1000100, Colours::crimson);
    masterPause.setColour(0x1000100, Colours::maroon);
    masterShuffle.setColour(0x1000100, Colours::maroon);
    
    // master volume design settings
    masterVol.setColour(0x1001200, Colours::orangered); // right hand slider fill
    masterVol.setColour(0x1001310, Colours::orange); // left hand slider fill
    masterVol.setColour(0x1001300, Colours::papayawhip); // scroller fill
    masterVol.setTextBoxStyle(juce::Slider::TextBoxAbove, true, getWidth(), getHeight() * 0.15/2); // shows slider value above slider

    // end of code I wrote
}
    
void MainComponent::resized()
{
    // start of code I wrote
    
    float bufferSpace = 0.01;
    float widthButton = (1 - bufferSpace*4)/3;
    
    masterPlay.setBounds(getWidth()*bufferSpace, getHeight()*0.02, getWidth() * widthButton, getHeight() * 0.15/2);
    masterPause.setBounds(getWidth()*(bufferSpace*2 + widthButton), getHeight()*0.02, getWidth() * widthButton, getHeight() * 0.15/2);
    masterShuffle.setBounds(getWidth()*(bufferSpace*3 + 2*widthButton), getHeight()*0.02, getWidth() * widthButton, getHeight() * 0.15/2);
    
    masterVol.setBounds(getWidth() * 0.1, getHeight() * 0.1, getWidth() * 0.8, getHeight() * 0.15/2);
    
    // end of code I wrote
    
    deckGUI1.setBounds(0, getHeight() * 0.2, getWidth()/2, getHeight()*0.8);
    deckGUI2.setBounds(getWidth()/2, getHeight() * 0.2, getWidth()/2, getHeight()*0.8);
    
    DBG("This is a test . resized.");
}

// start of code I wrote

void MainComponent::sliderValueChanged(Slider *slider)
{
    double orgGain1 = 0.5;
    double orgGain2 = 0.5;
    
    if (slider == &masterVol)
    {
        // deck 1 volume increases
        // deck 2 volume decreases
        if(slider->getValue() < 0)
        {
            double change = -1 * slider->getValue();
            
            double vol1 = orgGain1 + change * (1 - orgGain1);
            player1.setGain(vol1);
            
            double vol2 = orgGain2 - change * orgGain2;
            player2.setGain(vol2);
        }
        
        // deck 1 volume decreases
        // deck 2 volume increases
        else if(slider->getValue() > 0)
        {
            double change = slider->getValue();
            
            double vol1 = orgGain1 - change * orgGain1;
            player1.setGain(vol1);
            
            double vol2 = orgGain2 + change * (1 - orgGain2);
            player2.setGain(vol2);
        }
    }
}

void MainComponent::buttonClicked (Button *button)
{
    if(button == &masterPlay)
    {
        if(deckGUI1.isEmpty() == false)
        {
            player1.start();
        }
        
        if(deckGUI2.isEmpty() == false)
        {
            player2.start();
        }
    }
    
    if (button == &masterPause)
    {
        player1.stop();
        player2.stop();
    }
    
    if(button == &masterShuffle)
    {
        player1.setPositionRelative(randNum.getRandFloat()[indexPos1]);
        player2.setPositionRelative(randNum.getRandFloat()[indexPos2]);
        
        indexPos1 += 1;
        indexPos2 += 1;
    }
}

// end of code I wrote
