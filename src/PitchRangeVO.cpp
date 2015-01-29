#include "PitchRangeVO.h"

PitchRangeVO::PitchRangeVO(AudioDataRef audioDataRef)
{
	mAudioDataRef = audioDataRef;
}


void PitchRangeVO::draw()
{
	for (int i = 0; i < mAudioDataRef->mPitchRangeBuffer->size(); i++)
	{
		cirbuf_pitch_ref cir_buf_ref = mAudioDataRef->mPitchRangeBuffer;
		for (int j = 0; j < GlobalVar::PITCH_BIN_AMOUNT; j++)
		{
			float value = (*cir_buf_ref)[i][GlobalVar::PITCH_BIN_AMOUNT-1-j];
			if (value == 0) value = 0.0000001f;
			float value_db = remapToAlpha(20 * log10f(value) + GlobalVar::PITCH_OFFSET_DB, -90, -30);

			gl::color(1, 1, 0, value_db);
			gl::drawSolidCircle(Vec2f(50 + (float)i * 20, (float)j * 8 + 350), 10);
		}
	}
}