
#include <stdio.h>
#include <android/log.h>

#include "common.h"
#include "Config.h"

Config* Config::mpInstance = NULL;

#define LOG_TAG_CONFIG "Config"

Config::Config(){
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"constructor");
	
	for( int i = 0; i < CONFIG_NOTIFY_OBJS_NUM; i++ ) {
		mpWallpaperObjs[i] = NULL;
	}
	mWallpaperObjsNum = 0;
	
}

Config::~Config() {
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"destructor");
}

Config* Config::getInstance( void ) {
	if( mpInstance == NULL ) {
		mpInstance = new Config;
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"Create Instance");
	}
	
	return mpInstance;
}

void Config::deleteInstance( void ) {
	if( mpInstance != NULL ) {
		delete mpInstance;
		mpInstance = NULL;
		
		__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"Delete Instance");
	}
}

int Config::setAspect( int orientation, float vertical, float horizontal ) {
	mOrientation = orientation;
	mVertical    = vertical;
	mHorizontal  = horizontal;
	
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"setAspect");
	
	//“o˜^ƒNƒ‰ƒX‚É’Ê’m
	for( int i = 0; i < mWallpaperObjsNum; i++ ) {
		__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"setAspect[%d]", i);
		
		mpWallpaperObjs[i]->setAspect( mOrientation,
									   vertical,
									   horizontal );
	}
	
	
	
	return R_NORMAL;
}

int Config::addNotifyClass( WallpaperObject *p_wallpaper_object ) {
	if( p_wallpaper_object == NULL ) {
		return R_PARAMETER;
	}
	
	__android_log_write(ANDROID_LOG_DEBUG, LOG_TAG_CONFIG,"addNotifyClass");
	
	mpWallpaperObjs[mWallpaperObjsNum] = p_wallpaper_object;
	
	mWallpaperObjsNum++;
	
	return R_NORMAL;
}



