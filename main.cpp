#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

#include "Synthesizer.h"
#include "PhaseModulationStream.h"

int main()
{
    unsigned int sampleRate = 44100;
    unsigned int channelCount = 1;

    PhaseModulationStream mStream;

    mStream.setCarrierNote(0);
    mStream.setModulationNote(5);
    mStream.setModulationIndex(0.25f);

    mStream.play();

    char input;
    std::cout << "Press anything to stop\n";
    std::cin.get(input);

    return 0;
}
