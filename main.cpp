#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>
#include <Leap.h>

#include "Synthesizer.h"
#include "PhaseModulationStream.h"
#include "SynthController.h"

int main()
{
    Leap::Controller controller;

    std::cout << "Attempting to connect to Leap Motion\n";

    while (!controller.isConnected()) {}

    std::cout << "connected succesfully\n";

    sf::RenderWindow window(sf::VideoMode(512,512), "Testing Window");

    unsigned int sampleRate = 44100;
    unsigned int channelCount = 1;

    //PhaseModulationStream pmStream;
    int currentNote = 0;
    SynthController synth;

    synth.CreateTestPartitions();
    //
    
    //pmStream.play();
    //pmStream.setLoop(true);

    while (window.isOpen())
    {
        sf::Event ev;

        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
           
        }

        auto frame = controller.frame();

        synth.playLeapPartitionNote(frame);
       
        window.clear();
        window.display();
    }


    return 0;
}
