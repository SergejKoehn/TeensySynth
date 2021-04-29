#include <Audio.h>

typedef enum _eModulation {
  modulation_none,
  modulation_lfo,
  modulation_envelope,
  modulation_extern,
} eModulation;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VoiceInput 
{
public:
  typedef enum _eType {
    type_drum,
    type_string,
    type_wave,
    type_noise_white,
    type_noise_pink,
  } eType;

protected:
  eType            type;
  AudioStream     *source;
  AudioConnection *patchOut;
  AudioConnection *patchMod;
  float            frequency;
  float            velocity;

public:
  VoiceInput();

  void create(eType type);
  void destroy();

  void connect(AudioStream *destination, unsigned char destinationInput);
  void disconnect();

  eType getType();

  void setFrequency(float freq);
  void setVelocity(float velocity);

  void noteOn();
  void noteOff();

  void setShapeModulation(AudioStream *input= nullptr);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SynthVoice
{
public:
  typedef enum _eFilterType {
    filter_low_pass  = 0,
    filter_band_pass = 1,
    filter_heigh_pass= 2
  } eFilterType;

protected:
  VoiceInput                  voices[4];

  AudioMixer4                 mixer;
  AudioFilterStateVariable    filter;
  eModulation                 modShape;
  eModulation                 modFilter;
  AudioSynthWaveformModulated lfo;
  AudioSynthWaveformDc        dc;
  AudioEffectEnvelope         envelope;
  AudioEffectEnvelope         envelopeOut;
  AudioAmplifier              amp;
  
  AudioConnection             patch_mixer_filter;
  AudioConnection             patch_dc_envelope;
  AudioConnection             patch_amp_filter;
  AudioConnection             *patch_envelope_out;
  AudioConnection             *patch_filter_modulation;

public:
  SynthVoice();
  virtual ~SynthVoice();

  void setFilterType(eFilterType type);

  void setFilterFrequency(float freq);
  void setFilterResonance(float Q);
  
  void setFilterModulation(eModulation modulation, AudioStream *input= nullptr);
  void setFilterModDepth(float depth);

  void setFrequency(float freq);
  void setShapeModulation(eModulation modulation, AudioStream *input= nullptr); 

  void noteOn();
  void noteOff();
};
