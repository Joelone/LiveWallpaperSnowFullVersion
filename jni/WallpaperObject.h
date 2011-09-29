#ifndef __WALLPAPER_OBJECT__
#define __WALLPAPER_OBJECT__

#include "common.h"


class WallpaperObject {
public:
	WallpaperObject() {

	};

	virtual ~WallpaperObject() {

	};

	virtual int initialize( void ) = 0;
	virtual int draw( void ) = 0;
	virtual int setAspect(int orientation, float vertical, float horizontal ) = 0;
	
	
	
protected:
	static int CORDINATES_NUM;	//Position Number( x, y, z = 3Å@)
	static int COLOR_NUM;		//Color Number
	static int ONE;						//OpenGL Integer Position value(1.0 = 0x10000)
};

#endif
