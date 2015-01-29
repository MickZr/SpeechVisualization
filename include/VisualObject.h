#pragma once
#include "AudioData.h"
#include "cinder/gl/gl.h"

using namespace ci;

typedef AudioData* AudioDataRef;

class VisualObject
{
public:
	virtual void draw() = 0;
	float remapToAlpha(float value_db, float min_db, float max_db)
	{
		float temp = (value_db - min_db) / (max_db - min_db);
		if (temp > 1) temp = 1.0f;
		if (temp < 0) temp = 0.0f;
		return temp;
	}
protected:
	AudioDataRef mAudioDataRef;
};