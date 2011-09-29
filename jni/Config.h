#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "WallpaperObject.h"

#define CONFIG_NOTIFY_OBJS_NUM 10

class Config {
public:
	
	static Config* getInstance( void );
	static void    deleteInstance( void );
	
	int setAspect( int orientation, float vertical, float horizontal );
	int addNotifyClass( WallpaperObject *wallpaperObject );
	
	static int ORIENTATION_LANDSCAPE;
	static int ORIENTATION_PORTRAIT;
	
private:
	
	static Config* mpInstance;

	Config();
	virtual ~Config();

	int   mOrientation;
	float mVertical;
	float mHorizontal;
	
	int   mWallpaperObjsNum;
	WallpaperObject* mpWallpaperObjs[CONFIG_NOTIFY_OBJS_NUM];
};

#endif
