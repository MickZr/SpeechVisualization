#pragma once

class GlobalVar{
public:

#define SAMPLING_RATE 44100.0f
#define SPEECH_FREQ_MAX_HZ 4000.0f

	static const int WINDOW_SIZE = 512;
	static const int FFT_SIZE = 512;

	static float *PCMBuffer;
	static float *FourierBuffer;
	//static const float SPEECH_FREQ_MAX_HZ;
	//static const float SAMPLING_RATE;

	static const int SPEECH_CIRCULAR_BUFFER_SIZE = 20;
	static const int SPEECH_BIN_AMOUNT = (int)(SPEECH_FREQ_MAX_HZ / SAMPLING_RATE * GlobalVar::FFT_SIZE) + 1;

	//static float MIN_PITCH;
	//static float MAX_PITCH;
	static const int MIN_PITCH = 80;
	static const int MAX_PITCH = 260;
	static const int PITCH_CIRCULAR_BUFFER_SIZE = 20;
	static const int PITCH_BIN_AMOUNT = (int)((MAX_PITCH - MIN_PITCH) / SAMPLING_RATE * GlobalVar::FFT_SIZE) + 1;

	// SPEECH
	static float SPEECH_OFFSET_DB;

	// PITCH
	static float PITCH_OFFSET_DB;
	
};

