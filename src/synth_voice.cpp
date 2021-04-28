#include "synth_voice.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VoiceInput::VoiceInput()
{
  source= nullptr;
  patch = nullptr;
}

void VoiceInput::create(VoiceInput::eType type)
{
  destroy();

  switch ( type )
  {
    case type_drum:        source= new AudioSynthSimpleDrum();        break;
    case type_string:      source= new AudioSynthKarplusStrong();     break;
    case type_wave:        source= new AudioSynthWaveformModulated(); break;
    case type_noise_white: source= new AudioSynthNoiseWhite();        break;
    case type_noise_pink:  source= new AudioSynthNoisePink();         break;
    default:
      break;
  }

  this->type= type;
}

void VoiceInput::connect(AudioStream *destination, unsigned char destinationInput)
{
  if ( source == nullptr )
    return;

  disconnect();

  patch= new AudioConnection(*source,1,*destination,destinationInput);
}

void VoiceInput::disconnect()
{
  if ( patch != nullptr )
  {
    patch->disconnect();
    delete patch;
  }

  patch= nullptr;
}

void VoiceInput::destroy()
{
  disconnect();

  if ( source != nullptr )
    delete[] source;

  source= nullptr;
}

VoiceInput::eType VoiceInput::getType()
{
  return type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SynthVoice::SynthVoice()
: AudioStream(1,inputQueueArray)
{
}

SynthVoice::~SynthVoice()
{

}

void SynthVoice::setFilterModDepth(float depth)
{
}

void SynthVoice::setFilterEnvDepth(float depth)
{
}