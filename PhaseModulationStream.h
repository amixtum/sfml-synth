#ifndef PHASE_MODULATION_STREAM_H
#define PHASE_MODULATION_STREAM_H

#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>

class PhaseModulationStream : public sf::SoundStream
{
public:
    PhaseModulationStream()
    {
        initialize(channelCount, sampleRate);
        carrierIncrement = (twopi * carrierFrequency) / (float)sampleRate;
        modulationIncrement = (twopi * modulationFrequency) / (float)sampleRate;
    }
    ~PhaseModulationStream() {}

    void setCarrierFrequency(float frequency)
    {
        carrierFrequency = frequency;
        carrierIncrement = (twopi * carrierFrequency) / (float)sampleRate;
    }

    void setModulationFrequency(float frequency)
    {
        modulationFrequency = frequency;
        modulationIncrement = (twopi * modulationFrequency) / (float)sampleRate;
    }

    void setCarrierNote(int halfStepsFromA4)
    {
        setCarrierFrequency(getFrequency(halfStepsFromA4));
    }

    void setModulationNote(int halfStepsFromA4)
    {
        setModulationFrequency(getFrequency(halfStepsFromA4));
    }

    void setModulationIndex(float modIndex)
    {
        modulationIndex = modIndex;
    }
private:
    virtual bool onGetData(sf::SoundStream::Chunk &data)
    {
        buffer.reserve(chunkSize);

        for (int i = 0; i < chunkSize; ++i)
        {
            buffer.push_back((short)(amplitude *
                                     SHORT_SCALE *
                                     compute()));
        }

        data.samples = &buffer[0];

        data.sampleCount = chunkSize;

        buffer.clear();

        return true;
    }

    virtual void onSeek (sf::Time timeOffset)
    {
        return;
    }

    void incrementCarrierPhase()
    {
        carrierPhase += carrierIncrement;

        if (carrierPhase >= twopi) carrierPhase -= twopi;
        if (carrierPhase < 0) carrierPhase += twopi;
    }

    void incrementModulationPhase()
    {
        modulationPhase += modulationIncrement;

        if (modulationPhase >= twopi) modulationPhase -= twopi;
        if (modulationPhase < 0) modulationPhase += twopi;
    }

    float compute()
    {
        float val = (float)(std::sin(carrierPhase + modulationIndex *
                                             std::cos(modulationPhase)));

        incrementCarrierPhase();
        incrementModulationPhase();

        return val;
    }
private:
    float carrierIncrement;
    float carrierFrequency = A4;

    float modulationIndex = 0;
    float modulationIncrement;
    float modulationFrequency = 0;

    float carrierPhase = 0.0;
    float modulationPhase = 0.0;

    float amplitude = 0.5f;

    int chunkSize = 1024;
    std::vector<short> buffer;

    unsigned int channelCount = 1;
    unsigned int sampleRate = 44100;
};

#endif /* end of include guard:  PHASE_MODULATION_STREAM_H*/
