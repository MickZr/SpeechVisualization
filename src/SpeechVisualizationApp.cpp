#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "cinder/audio/Context.h"
#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"

#include "cinder/audio/SamplePlayerNode.h"

#include "boost\circular_buffer.hpp"
#include "boost\array.hpp"
#include "GlobalVar.h"
#include <array>

#include "cinder/Json.h"

#include "Resources.h"
#include "cinder/qtime/MovieWriter.h"
#include "SpeechVisualization.h"

#include "cinder/params/Params.h"

#define CONFIG_FILENAME "config.json"

using namespace ci;
using namespace ci::app;
using namespace std;

class SpeechVisualizationApp : public AppNative {
  public:
	void setup();
	void update();
	void draw();
private:
	enum InputMode {BUFFERMODE = 0, WAVMODE = 1};

	InputMode mInputMode;

	audio::InputDeviceNodeRef		mInputDeviceNode;
	audio::MonitorSpectralNodeRef	mMonitorSpectralNode;
	vector<float>					mMagSpectrum;
	audio::MonitorNodeRef			mMonitor;

	audio::BufferPlayerNodeRef		mBufferPlayerNode;

	float *mPCMData;
	float *mMagSpecData;
	
	qtime::MovieWriterRef	mMovieWriter;
	bool shouldRecord;
	
	SpeechVisualization mSpeechVisualization;

	// UI AntTweak
	params::InterfaceGlRef	mParams;

};

void SpeechVisualizationApp::setup()
{
	//
	mSpeechVisualization = SpeechVisualization();
/// JSON CONFIGURATION
	JsonTree myTree(loadAsset(CONFIG_FILENAME));
	shouldRecord = myTree.getChild("movieRecord").getValue<bool>();
	mInputMode = (InputMode) myTree.getChild("inputMode").getValue<int>();
	GlobalVar::SPEECH_OFFSET_DB = myTree.getChild("globalVar").getChild("speech_offset_db").getValue<float>();
	GlobalVar::SPEECH_OFFSET_DB = myTree.getChild("globalVar").getChild("pitch_offset_db").getValue<float>();

/// AUDIO STEAM AND PROCESSING CONFIGURATION
	auto ctx = audio::Context::master();

//REGION WAV STEAMING CONFIGURATION
	if (mInputMode == WAVMODE)
	{
		// create a SourceFile and set its output samplerate to match the Context.
		audio::SourceFileRef sourceFile = audio::load(loadAsset("audiofile.wav"));

		// load the entire sound file into a BufferRef, and construct a BufferPlayerNode with this.
		audio::BufferRef buffer = sourceFile->loadBuffer();
		mBufferPlayerNode = ctx->makeNode(new audio::BufferPlayerNode(buffer));

		// connect and enable the Context
		mBufferPlayerNode >> ctx->getOutput();
		mBufferPlayerNode->start();///
	}
//ENDREGION

	// By providing an FFT size double that of the window size, we 'zero-pad' the analysis data, which gives
	// an increase in resolution of the resulting spectrum data.
	//auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(GlobalVar::FFT_SIZE).windowSize(GlobalVar::WINDOW_SIZE);
	mMonitorSpectralNode = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));
	
	mMonitor = ctx->makeNode(new audio::MonitorNode);

	if (mInputMode == BUFFERMODE)
	{
		// The InputDeviceNode is platform-specific, so you create it using a special method on the Context:
		mInputDeviceNode = ctx->createInputDeviceNode();
		mInputDeviceNode >> mMonitorSpectralNode;
		mInputDeviceNode >> mMonitor;
		mInputDeviceNode->enable();
	}
	else if (mInputMode == WAVMODE)
	{
		mBufferPlayerNode >> mMonitorSpectralNode;
		mBufferPlayerNode >> mMonitor;
	}

	// InputDeviceNode (and all InputNode subclasses) need to be enabled()'s to process audio. So does the Context:
	
	ctx->enable();

/// ANTTWEAK BAR CONFIG
	mParams = params::InterfaceGl::create(getWindow(), "App parameters", toPixels(Vec2i(220, 100)));
	mParams->setOptions("", "position='400 30' ");
	// Add Ant Tweak Bar Parameter
	mParams->addParam("Speech offset(dB)", &GlobalVar::SPEECH_OFFSET_DB, "min=0 max = 90 step=1");
	mParams->addParam("Pitch offset(dB)", &GlobalVar::PITCH_OFFSET_DB, "min=0 max = 90 step=1");
	//e.g. mParams->addParam("Overall Offset(dB)", &miInputAudioProcessor.energy_offset, "min=-30 max=30 step=0.5");
	mParams->addSeparator();

/// QUICKTIME WRITER CONFIGURATION (should be last (uninvestigated))
	if (shouldRecord){
		fs::path path = getSaveFilePath();
		if (path.empty())
			return; // user cancelled save

		qtime::MovieWriter::Format format;
		if (qtime::MovieWriter::getUserCompressionSettings(&format, loadImage(loadResource(RES_PREVIEW_IMAGE)))) {
			mMovieWriter = qtime::MovieWriter::create(path, getWindowWidth(), getWindowHeight(), format);
		}
	}
}

void SpeechVisualizationApp::update()
{
	// We copy the magnitude spectrum out from the Node on the main thread, once per update:
	mMagSpectrum = mMonitorSpectralNode->getMagSpectrum();
	GlobalVar::FourierBuffer = &mMagSpectrum[0];
	//float sam = mMonitorSpectralNode->getSampleRate();

	mSpeechVisualization.update();
}

void SpeechVisualizationApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	gl::enableAlphaBlending();

	mSpeechVisualization.draw();

	////draw Fourier Data
	//gl::color(1, 1, 0);
	//const float *temp_pcm = mMonitor->getBuffer().getChannel(0); // channel L only ?
	//for (int i = 0; i < GlobalVar::FFT_SIZE/2 - 1; i++)
	//	gl::drawLine(Vec2f((float)i/2 + 50, GlobalVar::FourierBuffer[i] * 10000 + 50),
	//		Vec2f((float)i/2 + 51, GlobalVar::FourierBuffer[i + 1] * 10000 + 50));
	////draw PCM Data
	//gl::color(0, 1, 1);
	//for (int i = 0; i < GlobalVar::WINDOW_SIZE - 1; i++)
	//	gl::drawLine(Vec2f((float)i/2 + 50, temp_pcm[i] * 1000 + 100),
	//	Vec2f((float)i/2 + 51, temp_pcm[i + 1] * 1000 + 100));

	//draw Ant Tweak bar
	mParams->draw();

	// add this frame to our movie
	if (mMovieWriter && shouldRecord)
		mMovieWriter->addFrame(copyWindowSurface());
}



CINDER_APP_NATIVE( SpeechVisualizationApp, RendererGl )
