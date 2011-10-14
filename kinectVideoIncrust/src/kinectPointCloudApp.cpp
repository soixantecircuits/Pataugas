#include "VideoKin.h"
#include "Video.h"

#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;

class kinectPointCloudApp : public AppBasic {
public:
	void prepareSettings( Settings* settings );
	void setup();
	void mouseUp( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    // KINECT AND MOVIE
    VideoKin            mVideoKin;
    Video               mVideo;
    
};

void kinectPointCloudApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( 640, 480 );
    settings->setFrameRate( 30.0f );
}

void kinectPointCloudApp::setup()
{   
    mVideoKin = VideoKin();
    mVideoKin.setup();
    mVideo = Video(1);//By default, alpha = 0.5 
    mVideo.setup();
}

void kinectPointCloudApp::mouseUp( MouseEvent event )
{	
    //Size of the window
    console() << "Window's size is: " << getWindowSize() << std::endl;
}

void kinectPointCloudApp::keyDown( KeyEvent event )
{
    if( event.getCode() == KeyEvent::KEY_ESCAPE )
	{
		this->quit();
		this->shutdown();
	}
    else if( event.getChar() == 'f' || event.getChar() == 'F' )
    {
		setFullScreen( ! isFullScreen() );
	}
}

void kinectPointCloudApp::update()
{	    
    mVideoKin.update();
    
    mVideo.update();
}

void kinectPointCloudApp::draw()
{
    gl::clear();
    
    
    mVideoKin.draw();
    
    mVideo.draw();
}

CINDER_APP_BASIC( kinectPointCloudApp, RendererGl )