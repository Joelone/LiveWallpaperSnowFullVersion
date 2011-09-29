
#include <jni.h>
#include <GLES/gl.h>
#include <android/log.h>

#include "NDKParticle.h"
#include "Particle.h"
#include "Config.h"

#define NDK_INTERFACE_TAG_PARTICLE "NDK I/F:Particle"

Particle* particle = NULL;

//------------------------------------
//Particle
//------------------------------------
jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_test(JNIEnv *env, jobject obj){
	__android_log_write(ANDROID_LOG_DEBUG,NDK_INTERFACE_TAG_PARTICLE,"TEST");

	return 0;
}
jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKcreateNativeClass(JNIEnv *env, jobject obj ) {
	__android_log_write(ANDROID_LOG_DEBUG,NDK_INTERFACE_TAG_PARTICLE,"NDKcleateNativeClass");

	if(particle != NULL) {
		delete particle;
	}

	particle = new Particle();
	
	Config *config;
	config = Config::getInstance();
	config->addNotifyClass( (WallpaperObject*)particle );
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKinitialize(JNIEnv *env, jobject obj ) {
	__android_log_write(ANDROID_LOG_DEBUG,NDK_INTERFACE_TAG_PARTICLE,"NDKinitialize");

	if(particle == NULL) {
		return -1;
	}

	particle->initialize();

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKsetOrientation( JNIEnv *env, jobject obj, jint orientation ) {

}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKsetTextureData( JNIEnv *env,
																  jobject obj,
																  jint width,
																  jint height,
																  jintArray data ) {

	__android_log_print( ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_PARTICLE, "width=%d", width );
	__android_log_print( ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_PARTICLE, "height=%d", height );
	if( particle == NULL) {
		return -1;
	}

	jint* p_buf;
	p_buf = env->GetIntArrayElements(data, 0);

	particle->setupTexture( width, height, p_buf );

}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKrelease(JNIEnv *env, jobject obj) {
	__android_log_write(ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_PARTICLE,"NDKrelease");

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKdraw(JNIEnv *env, jobject obj) {
	if( particle == NULL) {
		return -1;
	}

	particle->draw();

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKsetParticleNum(JNIEnv *env,
																	 jobject obj,
																	 jint particle_num) {
	__android_log_write(ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_PARTICLE,"NDKsetParticleNum");
	if( particle == NULL) {
		return -1;
	}

	particle->setNum( particle_num );

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_Particle_NDKsetParticleSpeed(JNIEnv *env,
																	   jobject obj,
																	   jint particle_speed) {
	__android_log_write(ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_PARTICLE,"NDKsetParticleSpeed");
	if( particle == NULL) {
		return -1;
	}

	particle->setSpeed( particle_speed );

	return 0;
}

