#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalogStereo   adcs_input;     //xy=102,382
AudioInputI2S            i2s_input;      //xy=104,166
AudioInputAnalog         adc_input_freq; //xy=161,1036
AudioSynthWaveformDc     dc_filter_freq_ctrl; //xy=171,977
AudioSynthWaveformModulated player_waveform_mod; //xy=195,792
AudioSynthNoiseWhite     player_white_noise; //xy=207,850
AudioSynthNoisePink      player_pink_noise; //xy=211,907
AudioSynthSimpleDrum     player_drum;    //xy=225,676
AudioSynthKarplusStrong  player_string;  //xy=226,737
AudioEffectDigitalCombine combine2;       //xy=317,491
AudioEffectMultiply      multiply_left;      //xy=320,439
AudioEffectDigitalCombine combine1;       //xy=323,57
AudioEffectMultiply      multiply_right; //xy=331,106
AudioAmplifier           amp_input_freq; //xy=340,1034
AudioMixer4              mixer_voice_input; //xy=484,766
AudioEffectEnvelope      envelope_filter; //xy=502,908
AudioMixer4              mixer_input_left; //xy=598,397
AudioMixer4              mixer_input_right; //xy=602,177
AudioFilterStateVariable filter_synth;   //xy=676,773
AudioEffectGranular      granular1;      //xy=788,177
AudioEffectGranular      granular2;      //xy=795,397
AudioEffectEnvelope      envelope_synth; //xy=861,761
AudioMixer4              mixer_raw_left; //xy=1098,544
AudioMixer4              mixer_raw_right; //xy=1100,407
AudioEffectDelay         delay_left;     //xy=1363,676
AudioEffectDelay         delay_right;    //xy=1365,231
AudioEffectFlange        flange_right;   //xy=1367,389
AudioEffectReverb        reverb_right;   //xy=1368,351
AudioEffectReverb        reverb_left;    //xy=1368,554
AudioEffectChorus        chorus_left;    //xy=1368,591
AudioEffectFlange        flange_left;    //xy=1369,518
AudioEffectChorus        chorus_right;   //xy=1372,313
AudioMixer4              mixer_main_left; //xy=1443,1120
AudioMixer4              mixer_main_right; //xy=1446,1008
AudioMixer4              mixer_fx_left;  //xy=1588,555
AudioMixer4              mixer_fx_right; //xy=1595,333
AudioOutputI2S           i2s_output;     //xy=1683,1111
AudioOutputAnalogStereo  dacs_output;    //xy=1690,1016
AudioConnection          patchCord1(adcs_input, 0, mixer_input_right, 1);
AudioConnection          patchCord2(adcs_input, 0, combine1, 1);
AudioConnection          patchCord3(adcs_input, 0, multiply_right, 1);
AudioConnection          patchCord4(adcs_input, 1, mixer_input_left, 1);
AudioConnection          patchCord5(adcs_input, 1, combine2, 1);
AudioConnection          patchCord6(adcs_input, 1, multiply_left, 1);
AudioConnection          patchCord7(i2s_input, 0, mixer_input_right, 0);
AudioConnection          patchCord8(i2s_input, 0, combine1, 0);
AudioConnection          patchCord9(i2s_input, 0, multiply_right, 0);
AudioConnection          patchCord10(i2s_input, 1, mixer_input_left, 0);
AudioConnection          patchCord11(i2s_input, 1, combine2, 0);
AudioConnection          patchCord12(i2s_input, 1, multiply_left, 0);
AudioConnection          patchCord13(adc_input_freq, amp_input_freq);
AudioConnection          patchCord14(player_waveform_mod, 0, mixer_voice_input, 1);
AudioConnection          patchCord15(player_white_noise, 0, mixer_voice_input, 2);
AudioConnection          patchCord16(player_pink_noise, 0, mixer_voice_input, 3);
AudioConnection          patchCord17(combine2, 0, mixer_input_left, 2);
AudioConnection          patchCord18(multiply_left, 0, mixer_input_left, 3);
AudioConnection          patchCord19(combine1, 0, mixer_input_right, 2);
AudioConnection          patchCord20(multiply_right, 0, mixer_input_right, 3);
AudioConnection          patchCord21(amp_input_freq, envelope_filter);
AudioConnection          patchCord22(mixer_voice_input, 0, filter_synth, 0);
AudioConnection          patchCord23(envelope_filter, 0, filter_synth, 1);
AudioConnection          patchCord24(mixer_input_left, granular2);
AudioConnection          patchCord25(mixer_input_right, granular1);
AudioConnection          patchCord26(filter_synth, 0, envelope_synth, 0);
AudioConnection          patchCord27(granular1, 0, mixer_raw_right, 0);
AudioConnection          patchCord28(granular2, 0, mixer_raw_left, 0);
AudioConnection          patchCord29(envelope_synth, 0, mixer_raw_right, 1);
AudioConnection          patchCord30(envelope_synth, 0, mixer_raw_left, 1);
AudioConnection          patchCord31(mixer_raw_left, flange_left);
AudioConnection          patchCord32(mixer_raw_left, reverb_left);
AudioConnection          patchCord33(mixer_raw_left, delay_left);
AudioConnection          patchCord34(mixer_raw_left, 0, mixer_main_left, 0);
AudioConnection          patchCord35(mixer_raw_left, chorus_left);
AudioConnection          patchCord36(mixer_raw_right, delay_right);
AudioConnection          patchCord37(mixer_raw_right, chorus_right);
AudioConnection          patchCord38(mixer_raw_right, reverb_right);
AudioConnection          patchCord39(mixer_raw_right, flange_right);
AudioConnection          patchCord40(mixer_raw_right, 0, mixer_main_right, 0);
AudioConnection          patchCord41(delay_left, 0, mixer_fx_left, 3);
AudioConnection          patchCord42(delay_right, 0, mixer_fx_right, 0);
AudioConnection          patchCord43(flange_right, 0, mixer_fx_right, 3);
AudioConnection          patchCord44(reverb_right, 0, mixer_fx_right, 2);
AudioConnection          patchCord45(reverb_left, 0, mixer_fx_left, 1);
AudioConnection          patchCord46(chorus_left, 0, mixer_fx_left, 2);
AudioConnection          patchCord47(flange_left, 0, mixer_fx_left, 0);
AudioConnection          patchCord48(chorus_right, 0, mixer_fx_right, 1);
AudioConnection          patchCord49(mixer_main_left, 0, dacs_output, 1);
AudioConnection          patchCord50(mixer_main_left, 0, i2s_output, 1);
AudioConnection          patchCord51(mixer_main_right, 0, dacs_output, 0);
AudioConnection          patchCord52(mixer_main_right, 0, i2s_output, 0);
AudioConnection          patchCord53(mixer_fx_left, 0, mixer_main_left, 1);
AudioConnection          patchCord54(mixer_fx_right, 0, mixer_main_right, 1);
// GUItool: end automatically generated code
