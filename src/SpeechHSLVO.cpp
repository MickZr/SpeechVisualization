#include "SpeechHSLVO.h"

Vec3f *SpeechHSLVO::HSLValue = new Vec3f[GlobalVar::SPEECH_BIN_AMOUNT];
float special_mod_2(float H_prime)
{
	float quotient = floorf(H_prime / 2);
	float remainder = H_prime - quotient * 2;
	return remainder;
}
SpeechHSLVO::SpeechHSLVO(AudioDataRef audioDataRef)
{
	mAudioDataRef = audioDataRef;
	int size = GlobalVar::SPEECH_BIN_AMOUNT;
	for (int i = 0; i < size; i++)
	{
		// HSL to RGB
		// from http://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
		float H = (float)i / (float)size; // h range [0,1)
		float S = 1.0;
		float L = 0.5;
		float C = (1 - abs(2 * L - 1)) * S;
		float H_prime = H * 6;
		float X = C*(1 - abs(special_mod_2(H_prime) - 1));
		Vec3f RGB1;
		if (0 <= H_prime && H_prime < 1)
			RGB1 = Vec3f(C, X, 0);
		else if (H_prime < 2)
			RGB1 = Vec3f(X, C, 0);
		else if (H_prime < 3)
			RGB1 = Vec3f(0, C, X);
		else if (H_prime < 4)
			RGB1 = Vec3f(0, X, C);
		else if (H_prime < 5)
			RGB1 = Vec3f(X, 0, C);
		else if (H_prime < 6)
			RGB1 = Vec3f(C, 0, X);

		float m = L - C / 2;
		Vec3f RGB = RGB1 + Vec3f(m, m, m);
		HSLValue[i] = RGB;
	}
}

void SpeechHSLVO::draw()
{
	int size = GlobalVar::SPEECH_BIN_AMOUNT;
	// draw HSL value
	for (int i = 0; i < size; i++)
	{
		gl::color(HSLValue[i].x, HSLValue[i].y, HSLValue[i].z, 1);
		gl::drawSolidCircle(Vec2f(30, (float)i * 4 + 150), 10);
	}
	// sum up and plot color
	for (int i = 0; i < mAudioDataRef->mSpeechRangeBuffer->size(); i++)
	{
		cirbuf_speech_ref cir_buf_ref = mAudioDataRef->mSpeechRangeBuffer;
		for (int j = 0; j < GlobalVar::SPEECH_BIN_AMOUNT; j++)
		{
			float value = (*cir_buf_ref)[i][GlobalVar::SPEECH_BIN_AMOUNT - 1 - j];
			if (value == 0) value = 0.0000001f;
			float value_db = remapToAlpha(20 * log10f(value) + GlobalVar::SPEECH_OFFSET_DB, -90, -30);

			gl::color(HSLValue[j].x, HSLValue[j].y, HSLValue[j].z, value_db);
			gl::drawSolidCircle(Vec2f(50 + (float)i * 20, (float)j * 4 + 150), 10);
		}
	}
}