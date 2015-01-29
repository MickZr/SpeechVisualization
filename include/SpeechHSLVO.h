#pragma once
#include "VisualObject.h"

class SpeechHSLVO : public VisualObject
{
public:
	SpeechHSLVO(AudioDataRef audioDataRef);
	virtual void draw();
	static Vec3f *HSLValue;//

private:
};