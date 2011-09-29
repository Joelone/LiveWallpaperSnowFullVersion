
#include <jni.h>
#include <GLES/gl.h>
#include <android/log.h>

#include "NDKBackground.h"
#include "Background.h"
#include "Config.h"

Background *background = NULL;

#define NDK_INTERFACE_TAG_BACKGROUND "NDK I/F:Background"

/*
 * Class:     jp_ks_livewallpaper_opengl_snowfull_Background
 * Method:    NDKcreateNativeClass
 * Signature: ()I
 */
jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKcreateNativeClass(JNIEnv *env, jobject obj){
	__android_log_write(ANDROID_LOG_DEBUG,NDK_INTERFACE_TAG_BACKGROUND,"NDKcleateNativeClass");

	if(background != NULL) {
		delete background;
	}

	background = new Background();

	Config *config;
	config = Config::getInstance();
	config->addNotifyClass( (WallpaperObject*)background );
	
//	background->initialize();
	
	return 0;
}

/*
 * Class:     jp_ks_livewallpaper_opengl_snowfull_Background
 * Method:    NDKinitialize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKinitialize(JNIEnv *env, jobject obj) {
	background->initialize();
	
	return 0;
}

/*
 * Class:     jp_ks_livewallpaper_opengl_snowfull_Background
 * Method:    NDKsetPattern
 * Signature: (I)I
 */
jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKsetPattern(JNIEnv *env, jobject obj, jint pattern ) {
	if( background == NULL ) {
		return -1;
	}
	
	__android_log_print(ANDROID_LOG_DEBUG,NDK_INTERFACE_TAG_BACKGROUND,"NDKsetPattern=%d", pattern);
	
	background->setPattern( pattern );
	
	return 0;
}

/*
 * Class:     jp_ks_livewallpaper_opengl_snowfull_Background
 * Method:    NDKdraw
 * Signature: ()I
 */
jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKdraw(JNIEnv *env, jobject obj) {
	if( background == NULL ) {
		return -1;
	}
	
	background->draw();
	
	return 0;
}

/*
 * Class:     jp_ks_livewallpaper_opengl_snowfull_Background
 * Method:    NDKsetOrientation
 * Signature: (I)I
 */
jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKsetOrientation(JNIEnv *env, jobject obj, jint orientation) {
	if( background == NULL ) {
		return -1;
	}
	
	return 0;	
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKsetTextureData(
		JNIEnv *env,
		jobject obj,
		jint width,
		jint height,
		jintArray data) {

	if( background == NULL ) {
		return -1;
	}

	__android_log_print( ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_BACKGROUND, "width=%d", width );
	__android_log_print( ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_BACKGROUND, "height=%d", height );

	jint* p_buf;
	p_buf = env->GetIntArrayElements(data, 0);

	background->setupTexture( width, height, p_buf );

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Background_NDKsetMoonVisibility(
		JNIEnv *env,
		jobject obj,
		jboolean is_visible ) {
	if( background == NULL ) {
		return -1;
	}
	
	background->setMoonVisibility( is_visible );

	return 0;
}

