#include "synth_voice.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VoiceInput::VoiceInput()
{
  source  = nullptr;
  patchOut= nullptr;
  patchMod= nullptr;

  frequency= 440.0;
  velocity = 1.0;
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

  patchOut= new AudioConnection(*source,1,*destination,destinationInput);
}

void VoiceInput::disconnect()
{
  if ( patchOut != nullptr )
  {
    patchOut->disconnect();
    delete patchOut;
  }

  patchOut= nullptr;
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

void VoiceInput::setFrequency(float freq)
{
  frequency= freq;
  switch ( type )
  {
    case type_drum:        ((AudioSynthSimpleDrum*)source)->frequency(frequency);        break;
    case type_wave:        ((AudioSynthWaveformModulated*)source)->frequency(frequency); break;
    case type_string:      
    case type_noise_white: 
    case type_noise_pink:  
    default:
      break;
  }
}

void VoiceInput::setVelocity(float vel)
{
  velocity= vel;

  switch ( type )
  {
    case type_wave:        ((AudioSynthWaveformModulated*)source)->amplitude(velocity); break;
    case type_noise_white: ((AudioSynthNoiseWhite*)source)->amplitude(velocity);        break;
    case type_noise_pink:  ((AudioSynthNoisePink*)source)->amplitude(velocity);         break;
    case type_drum:
    case type_string:      
    default:
      break;
  }
}

void VoiceInput::noteOn()
{
  switch ( type )
  {
    case type_drum:        ((AudioSynthSimpleDrum*)source)->noteOn();                      break;
    case type_string:      ((AudioSynthKarplusStrong*)source)->noteOn(frequency,velocity); break;
    case type_wave:         
    case type_noise_white: 
    case type_noise_pink:  
    default:
      break;
  }
}

void VoiceInput::noteOff()
{
  switch ( type )
  {
    case type_string:      ((AudioSynthKarplusStrong*)source)->noteOff(0.0); break;
    case type_drum:        
    case type_wave:         
    case type_noise_white: 
    case type_noise_pink:  
    default:
      break;
  }
}

void VoiceInput::setShapeModulation(AudioStream *input)
{
  if ( patchMod != nullptr )
  {
    patchMod->disconnect();
    delete patchMod;
    patchMod= nullptr;
  }  

  if ( type == type_wave && input != nullptr )
    patchMod= new AudioConnection(*input,0,*source,1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SynthVoice::SynthVoice()
: patch_mixer_filter(mixer,filter),
  patch_dc_envelope(dc,envelope),
  patch_amp_filter(amp,0,filter,1)
{
  patch_envelope_out     = nullptr;
  patch_filter_modulation= nullptr;

  dc.amplitude(1.0);

  setFilterType(filter_low_pass);
  setFilterFrequency(5000);
  setFilterModulation(modulation_none);
}

SynthVoice::~SynthVoice()
{

}

void SynthVoice::setFilterType(SynthVoice::eFilterType type)
{
  if ( patch_envelope_out != nullptr )
  {
    patch_envelope_out->disconnect();
    delete patch_envelope_out;
    patch_envelope_out= nullptr;
  }

  patch_envelope_out= new AudioConnection(filter,type,envelopeOut,0);
} 

void SynthVoice::setFilterFrequency(float freq)
{
  filter.frequency(freq);
}

void SynthVoice::setFilterResonance(float Q)
{
  filter.resonance(Q);
}

void SynthVoice::setFilterModulation(eModulation modulation, AudioStream *input)
{
  if ( patch_filter_modulation != nullptr )
  {
    patch_filter_modulation->disconnect();
    delete patch_filter_modulation;
    patch_filter_modulation= nullptr;
  }  

  if ( modulation == modulation_lfo )
    patch_filter_modulation= new AudioConnection(lfo,amp);
  else
  if ( modulation == modulation_envelope )
    patch_filter_modulation= new AudioConnection(envelope,amp);
  else
  if ( modulation == modulation_extern )
    patch_filter_modulation= new AudioConnection(*input,amp);

  modFilter= modulation;
}

void SynthVoice::setFilterModDepth(float depth)
{
  amp.gain(depth);
}

void SynthVoice::setFrequency(float freq)
{
  for ( int i= 0; i < 4; i++ )
  {
    voices[i].setFrequency(freq);
  }
}

void SynthVoice::setShapeModulation(eModulation modulation, AudioStream *input)
{
  for ( int i= 0; i < 4; i++ )
  {
    if ( modulation == modulation_lfo )
      voices[i].setShapeModulation(&lfo);
    else
    if ( modulation == modulation_envelope )
      voices[i].setShapeModulation(&envelope);
    else
    if ( modulation == modulation_extern )
      voices[i].setShapeModulation(input);
  }
}

void SynthVoice::noteOn()
{
  envelope.noteOn();
  envelopeOut.noteOn();

  for ( int i= 0; i < 4; i++ )
  {
    voices[i].noteOn();
  }
}

void SynthVoice::noteOff()
{
  envelope.noteOff();
  envelopeOut.noteOff();

  for ( int i= 0; i < 4; i++ )
  {
    voices[i].noteOff();
  }
}