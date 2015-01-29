#pragma once
#include "boost\circular_buffer.hpp"
#include "boost\array.hpp"
#include "GlobalVar.h"
#include <array>

// SPEECH RANGE
typedef std::array<float, GlobalVar::SPEECH_BIN_AMOUNT> array_speech;
typedef boost::circular_buffer<array_speech> cirbuf_speech;
typedef cirbuf_speech* cirbuf_speech_ref;

// PITCH RANGE
typedef std::array<float, GlobalVar::PITCH_BIN_AMOUNT> array_pitch;
typedef boost::circular_buffer<array_pitch> cirbuf_pitch;
typedef cirbuf_pitch* cirbuf_pitch_ref;

class AudioData
{
public:
	AudioData();
	void update();
	cirbuf_speech_ref mSpeechRangeBuffer;
	cirbuf_pitch_ref mPitchRangeBuffer;
	//F0Estimation mF0Estimation;

private:

};