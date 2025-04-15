#include <JuceHeader.h>
#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

RandomGenerator::~RandomGenerator()
{
    
}

void RandomGenerator::paint (juce::Graphics& g)
{

}

void RandomGenerator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
}

// start of code I wrote
std::vector<float> RandomGenerator::getRandFloat()
{
    srand(time(0));
    
    // generates 1000 numbers between 0.1 and 1
    // number is pushed into a vector, randList
    
    while(randList.size() != 1000)
    {
        float num = rand();
        num = num/10000000;
        
        if(num < 1 && num > 0.1 && num != 0)
        {
            randList.push_back(num);
        }
    }
    
    return randList;
}
// end of code I wrote
