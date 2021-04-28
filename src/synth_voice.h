#include <Audio.h>

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
  AudioConnection *patch;

public:
  VoiceInput();

  void create(eType type);
  void destroy();

  void connect(AudioStream *destination, unsigned char destinationInput);
  void disconnect();

  eType getType();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SynthVoice : public AudioStream
{
protected:
  audio_block_t           *inputQueueArray[1];
  AudioMixer4              mixer;
  AudioFilterStateVariable filter;
  AudioEffectEnvelope      filterEnvelope;
  AudioEffectEnvelope      outEnvelope;
  VoiceInput               voices[4];
public:
  SynthVoice();
  virtual ~SynthVoice();

  void setFilterModDepth(float depth);
  void setFilterEnvDepth(float depth);  
};
