#include "SpeechVisualization.h"
#include "SpeechRangeVO.h"
#include "PitchRangeVO.h"
#include "SpeechHSLVO.h"
SpeechVisualization::SpeechVisualization()
{
	mAudioDataRef = new AudioData();
	//VisualObject *speechRangeVO = new SpeechRangeVO(mAudioDataRef);
	//mVisualObjectVec.push_back(speechRangeVO);
	VisualObject *pitchRangeVO = new PitchRangeVO(mAudioDataRef);
	mVisualObjectVec.push_back(pitchRangeVO);
	VisualObject *speechHSLVO = new SpeechHSLVO(mAudioDataRef);
	mVisualObjectVec.push_back(speechHSLVO);
}

void SpeechVisualization::update()
{
	mAudioDataRef->update();
}

void SpeechVisualization::draw()
{
	for (int i = 0; i < mVisualObjectVec.size(); i++)
	{
		mVisualObjectVec[i]->draw();
	}
}