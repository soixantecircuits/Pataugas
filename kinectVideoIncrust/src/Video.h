#pragma once
#include "cinder/qtime/QuickTime.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rect.h"

class Video {
public:
    Video(float alpha = 0.5);
    void setup();
	void update();
	void draw();
    
    ci::qtime::MovieSurface      mMovie; 
    ci::gl::Texture         mFrameTexture;
    ci::Surface             mFrameSurface;
    ci::gl::Texture::Format mFrameFormat;
    ci::Rectf               mCenteredRect;
	float                   mAlpha;
};