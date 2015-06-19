#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <Leap.h>

#include "Synthesizer.h"
#include "PhaseModulationStream.h"

int main()
{
    Leap::Controller controller;

    std::cout << "Attempting to connect to Leap Motion\n";

    while (!controller.isConnected()) {}

    sf::RenderWindow window(sf::VideoMode(512,512), "Testing Window");

    unsigned int sampleRate = 44100;
    unsigned int channelCount = 1;

    PhaseModulationStream mStream;

    mStream.setCarrierNote(0);
    mStream.setModulationNote(0);
    mStream.setModulationIndex(2);

    mStream.play();

    while (window.isOpen())
    {
        sf::Event ev;

        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        auto frame = controller.frame();



        window.clear();
        window.display();
    }

    return 0;
}
