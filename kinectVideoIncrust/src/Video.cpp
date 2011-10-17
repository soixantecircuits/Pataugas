#include "Video.h"
#include "Resources.h"

#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;


Video::Video(float alpha) : mAlpha(alpha)
{
}

void Video::setup()
{   
    try {
        mMovie = qtime::MovieSurface( loadResource( "BandesBleues.mov" ) );
        mMovie.setLoop();
        mMovie.play();
        //mMovie.setRate(100.0);

        console() << "The movie is loaded and playing." << std::endl;
    } 
    catch ( ... ) {
        console() << "Unable to load or play the movie!" << std::endl;
    }

    mFrameFormat = gl::Texture::Format();
    mFrameFormat.setTargetRect();
    mFrameTexture = gl::Texture( loadImage( loadResource( RES_CINDER_LOGO ) ), mFrameFormat ); 
    mFrameSurface = ci::Surface( loadImage( loadResource( RES_CINDER_LOGO ) ) );
    mCenteredRect = Rectf( mFrameTexture.getBounds() ).getCenteredFit( getWindowBounds(), true );
}

void Video::update()
{
    if( mMovie.checkPlayable() ){
        Area area = mMovie.getSurface().getBounds();
        mFrameSurface = ci::Surface(area.getWidth(), area.getHeight(), true);
		mFrameSurface.copyFrom(mMovie.getSurface(), mFrameSurface.getBounds() );
        
        /*
        mFrameSurface = ci::Surface(mMovie.getSurface());
        mFrameTexture = gl::Texture(mFrameSurface, mFrameFormat);
        */
        
        Surface::Iter iter = mFrameSurface.getIter( mFrameSurface.getBounds() );

        while( iter.line() ) {
            while( iter.pixel() ) {
                //if (iter.b() > 50 && iter.r() < 50 && iter.g() < 50){
                if (iter.g() > 50 && iter.g() > iter.r() && iter.g() > iter.b()){
                    //std::cout << "yes" << std::endl;
                    //iter.r() = 0;
                    //iter.g() = 0;
                    //iter.b() = 0;
                    iter.a() = 0;
                }
                else{
                    iter.a() = 255;
                    //std::cout << "no" << std::endl;
                }
            }
        }
        //mFrameSurface = ci::Surface( loadImage( loadResource( "bomb.png")) );
        mFrameTexture = gl::Texture(mFrameSurface, mFrameFormat);
         
    }
    //mCenteredRect = Rectf( mFrameTexture.getBounds() ).getCenteredFit( getWindowBounds(), true );
    mCenteredRect = Rectf(-40,0,800,600);
    
   
     
}

void Video::draw()
{ 
    //mFrameSurface = ci::Surface(mFrameTexture);
    
    
    //mAlpha = 1;
    gl::enableAlphaBlending();//the order is important for the velocity 
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //glAlphaFunc(0, GL_EQUAL);
    //gl::color( ColorA( 0.0f, 0.0f, 0.5f, 1.0f ) );
    
    gl::draw(mFrameTexture, mCenteredRect);
    gl::disableAlphaBlending();
    glDisable( GL_BLEND );
     
    //gl::draw(mFrameTexture, mCenteredRect);
}