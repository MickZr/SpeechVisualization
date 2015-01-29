#pragma once
#include "AudioData.h"
#include <vector>
#include "VisualObject.h"
using namespace std;
class SpeechVisualization
{
public:
	SpeechVisualization();
	void update();
	void draw();

	vector<VisualObject*> mVisualObjectVec;

private:
	AudioDataRef mAudioDataRef;
};