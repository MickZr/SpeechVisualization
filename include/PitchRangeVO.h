#pragma once
#include "VisualObject.h"

class PitchRangeVO : public VisualObject
{
public:
	PitchRangeVO(AudioDataRef audioDataRef);
	virtual void draw();
private:
};