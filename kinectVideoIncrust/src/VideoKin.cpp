#include "VideoKin.h"
#include "libfreenect.h"
#include "Resources.h"

#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;

VideoKin::VideoKin() 
{
}

void VideoKin::setup() 
{
    try {
        console() << "There is " << Kinect::getNumDevices() << " Kinect connected." << std::endl;
        mKinect = Kinect( Kinect::Device() );
        console() << "Kinect is initailized." << std::endl; 
    } 
    catch ( ... ) {
        console() << "Unable to initialize the Kinect!" << std::endl;
    } 
    
    mColorFormat = gl::Texture::Format();
    mColorFormat.setTargetRect();
    mColorTexture = gl::Texture( loadImage( loadResource( RES_CINDER_LOGO ) ), mColorFormat );
    mCenteredRect = Rectf( mColorTexture.getBounds() ).getCenteredFit( getWindowBounds(), true );
}

void VideoKin::update()
{
    if   ( Kinect::getNumDevices() > 0){
        if( mKinect.checkNewVideoFrame())
                mColorTexture = gl::Texture( mKinect.getVideoImage() );
    }
    mCenteredRect = Rectf( mColorTexture.getBounds() ).getCenteredFit( getWindowBounds(), true );
}

void VideoKin::draw()
{
    if( mColorTexture )
    {
        gl::color( ColorA(1.0f, 1.0f, 1.0f, 1.0f) );
        
        glMatrixMode(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, mColorTexture.getId());
        glLoadIdentity();
        //glTranslatef(800.0,600.0,0.0);
        //glRotatef(70.0, 0.0, 0.0, 1.0);
        //glTranslatef(0.0,10.0,0.0);
        glMatrixMode(GL_MODELVIEW);
    
        gl::draw(mColorTexture, mCenteredRect);

        
    }

}
