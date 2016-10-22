#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Batch.h"

#include "FMOD.hpp"

#include "PoemTrack.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class InteractivePoetryApp : public App {
  public:
	void setup() override;
	void draw() override;
    void update() override;
    
private:
    void updateIntensity();

	FMOD::System	*mSystem;
    
    vector< vector< PoemTrack * > > mPoems;
    PoemTrack * mTrackPlaying;
    
    int mCurrentPoem;
    int mCurrentIntensity;
    int mCurrentLine;
};

void InteractivePoetryApp::setup()
{
    FMOD::System_Create( &mSystem );
    mSystem->init( 32, FMOD_INIT_NORMAL | FMOD_INIT_ENABLE_PROFILE, NULL );
    
    mTrackPlaying = nullptr;
    
    mCurrentPoem = 0;
    mCurrentIntensity = 0;
    mCurrentLine = 0;
    
    int lPoemCount = 1;
    int lIntensityCount = 4;
    for(int p = 0; p < lPoemCount; p++)
    {
        mPoems.push_back(vector< PoemTrack * >());
        for(int i = 0; i < lIntensityCount; i++)
        {
            mPoems[mPoems.size() - 1].push_back(new PoemTrack(mPoems.size(), i + 1, mSystem));
        }
    }
}

void InteractivePoetryApp::update()
{
    if(!mTrackPlaying)
    {
        mTrackPlaying = mPoems[mCurrentPoem][mCurrentIntensity];
        mTrackPlaying->play();
    }
    if(mTrackPlaying->isFinished())
    {
        mCurrentLine++;
        updateIntensity();
        mTrackPlaying->setPositionIndex(mCurrentLine);
    }
}

void InteractivePoetryApp::updateIntensity()
{
    int lNewIndex = mCurrentLine % 2;
    mTrackPlaying->pause();
    mTrackPlaying = mPoems[mCurrentPoem][lNewIndex];
    mTrackPlaying->play();
}

void InteractivePoetryApp::draw()
{
	gl::clear();
	
	// grab 512 samples of the wave data
	float waveData[512];
	mSystem->getWaveData( waveData, 512, 0 );
	
	// render the 512 samples to a VertBatch
	gl::VertBatch vb( GL_LINE_STRIP );
	for( int i = 0; i < 512; ++i )
		vb.vertex( getWindowWidth() / 512.0f * i, getWindowCenter().y + 100 * waveData[i] );

	// draw the points as a line strip
	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	vb.draw();
}

CINDER_APP( InteractivePoetryApp, RendererGl )
