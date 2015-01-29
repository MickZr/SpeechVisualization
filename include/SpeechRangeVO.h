#pragma once
#include "VisualObject.h"

class SpeechRangeVO : public VisualObject
{
public:
	SpeechRangeVO(AudioDataRef audioDataRef);
	virtual void draw();
private:
};