#pragma once

#include <JuceHeader.h>

class RandomGenerator  : public juce::Component
{
    public:
        RandomGenerator();
        ~RandomGenerator() override;

        void paint (juce::Graphics&) override;
        void resized() override;
  
        // start of code I wrote
        std::vector<float> getRandFloat();
        // end of code I wrote

    private:
        // start of code I wrote
        std::vector<float> randList;
        // end of code I wrote
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RandomGenerator)
};
