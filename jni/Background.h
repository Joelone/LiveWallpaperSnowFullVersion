#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "WallpaperObject.h"
#include "NDKBackground.h"

class Background : public WallpaperObject  {
public:
	Background();
	virtual ~Background();

	int  initialize( void );
	int  draw( void );
	int  updateOrientation( int orientation );
	int  setAspect(  int orientation, float vertical, float horizontal );
	int  setPattern( int pattern );
	int  setMoonVisibility( bool isVisible );
	int  setupTexture( int width, int height, int* p_buf );
	
	
private:
	static const int BACKGROUND_VERTEX_NUM;
	static const int BACKGROUND_SKIN_NONE;
	static const int BACKGROUND_SKIN_GRADATION;
	static const int BACKGROUND_MOON_COOR_ADJ_VALUE;

	int *mpSquare;
	int *mpColor;
	int *mpMoonSquare;
	GLubyte* mpTexture;
	
	int  mPattern;
	bool mIsMoonVisible;
	int  mOrientation;
	int  mVertical;
	int  mHorizontal;

	int mMoonWidth;
	int mMoonHeight;

	GLuint mTextureID;
};

#endif
