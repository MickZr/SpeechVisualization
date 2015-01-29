#include "SpeechRangeVO.h"

SpeechRangeVO::SpeechRangeVO(AudioDataRef audioDataRef)
{
	mAudioDataRef = audioDataRef;
}
void SpeechRangeVO::draw()
{
	for (int i = 0; i < mAudioDataRef->mSpeechRangeBuffer->size(); i++)
	{
		cirbuf_speech_ref cir_buf_ref = mAudioDataRef->mSpeechRangeBuffer;
		for (int j = 0; j < GlobalVar::SPEECH_BIN_AMOUNT; j++)
		{	
			float value = (*cir_buf_ref)[i][GlobalVar::SPEECH_BIN_AMOUNT-1-j];
			if (value == 0) value = 0.0000001f;
			float value_db = remapToAlpha(20 * log10f(value) + GlobalVar::SPEECH_OFFSET_DB, -90, -30);

			gl::color(1, 1, 1, value_db);
			gl::drawSolidCircle(Vec2f(50 + (float)i * 20, (float)j * 4 + 150), 10);
		}
	}
}