#pragma once
#include "cinder/Json.h"
#include "GlobalVar.h"
using namespace ci;

class PitchEstimation
{
public:
	float mPitch;
	float mWeight;
	
	PitchEstimation()
	{
		mPitch = 0;
		mWeight = 0;
	}
	void update()
	{
		float sam_rate = GlobalVar::SAMPLING_RATE;
		float min = GlobalVar::MIN_PITCH;
		float max = GlobalVar::MAX_PITCH;
		float cur_pitch = 0;
		float cur_weight = 0;

	}
private:
};