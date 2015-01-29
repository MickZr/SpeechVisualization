#include "AudioData.h"

AudioData::AudioData()
{
	mSpeechRangeBuffer = new cirbuf_speech(GlobalVar::SPEECH_CIRCULAR_BUFFER_SIZE);
	mPitchRangeBuffer = new cirbuf_pitch(GlobalVar::PITCH_CIRCULAR_BUFFER_SIZE);
}

void AudioData::update()
{
	// Speech Range Buffer Copying
	array_speech a;
	for (int i = 0; i < GlobalVar::SPEECH_BIN_AMOUNT; i++)
	{
		a[i] = GlobalVar::FourierBuffer[i];
	}
	mSpeechRangeBuffer->push_back(a);

	// Pitch Range Buffer Copying
	array_pitch b;
	for (int i = (int)(GlobalVar::MIN_PITCH / 44100.0f*GlobalVar::WINDOW_SIZE);
		i < (int)(GlobalVar::MAX_PITCH / 44100.0f*GlobalVar::WINDOW_SIZE); i++)
	{
		b[i] = GlobalVar::FourierBuffer[i];
	}
	mPitchRangeBuffer->push_back(b);
}

