#include "GlobalVar.h"
#include <array>

float *GlobalVar::FourierBuffer = new float[GlobalVar::WINDOW_SIZE];

float GlobalVar::SPEECH_OFFSET_DB = 30.0f;
float GlobalVar::PITCH_OFFSET_DB = 30.0f;

//float GlobalVar::MIN_PITCH = 80;
//float GlobalVar::MAX_PITCH = 260;

//const float GlobalVar::SPEECH_FREQ_MAX_HZ = 4000.0f;
//const float GlobalVar::SAMPLING_RATE = 44100;

//const int SPEECH_BIN_AMOUNT = (int)(4000.0f / 44100.0f * GlobalVar::WINDOW_SIZE) + 1;
