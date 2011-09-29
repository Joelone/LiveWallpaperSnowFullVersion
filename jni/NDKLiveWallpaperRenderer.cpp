
#include <jni.h>
#include <GLES/gl.h>
#include <android/log.h>
#include <math.h>

#define NDK_INTERFACE_TAG_RENDERER "NDK I/F:LiveWallpaperRenderer"

#include "NDKLiveWallpaperRenderer.h"
#include "Config.h"

//サンプルから拝借
/* Following gluLookAt implementation is adapted from the
 * Mesa 3D Graphics library. http://www.mesa3d.org
 */
static void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
	              GLfloat centerx, GLfloat centery, GLfloat centerz,
	              GLfloat upx, GLfloat upy, GLfloat upz)
{
    GLfloat m[16];
    GLfloat x[3], y[3], z[3];
    GLfloat mag;

    /* Make rotation matrix */

    /* Z vector */
    z[0] = eyex - centerx;
    z[1] = eyey - centery;
    z[2] = eyez - centerz;
    mag = (float)sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
    if (mag) {			/* mpichler, 19950515 */
        z[0] /= mag;
        z[1] /= mag;
        z[2] /= mag;
    }

    /* Y vector */
    y[0] = upx;
    y[1] = upy;
    y[2] = upz;

    /* X vector = Y cross Z */
    x[0] = y[1] * z[2] - y[2] * z[1];
    x[1] = -y[0] * z[2] + y[2] * z[0];
    x[2] = y[0] * z[1] - y[1] * z[0];

    /* Recompute Y = Z cross X */
    y[0] = z[1] * x[2] - z[2] * x[1];
    y[1] = -z[0] * x[2] + z[2] * x[0];
    y[2] = z[0] * x[1] - z[1] * x[0];

    /* mpichler, 19950515 */
    /* cross product gives area of parallelogram, which is < 1.0 for
     * non-perpendicular unit-length vectors; so normalize x, y here
     */

    mag = (float)sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    if (mag) {
        x[0] /= mag;
        x[1] /= mag;
        x[2] /= mag;
    }

    mag = (float)sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag) {
        y[0] /= mag;
        y[1] /= mag;
        y[2] /= mag;
    }

#define M(row,col)  m[col*4+row]
    M(0, 0) = x[0];
    M(0, 1) = x[1];
    M(0, 2) = x[2];
    M(0, 3) = 0.0;
    M(1, 0) = y[0];
    M(1, 1) = y[1];
    M(1, 2) = y[2];
    M(1, 3) = 0.0;
    M(2, 0) = z[0];
    M(2, 1) = z[1];
    M(2, 2) = z[2];
    M(2, 3) = 0.0;
    M(3, 0) = 0.0;
    M(3, 1) = 0.0;
    M(3, 2) = 0.0;
    M(3, 3) = 1.0;
#undef M
    {
        int a;
        GLfixed fixedM[16];
        for (a = 0; a < 16; ++a)
            fixedM[a] = (GLfixed)(m[a] * 65536);
        glMultMatrixx(fixedM);
    }

    /* Translate Eye to Origin */
    glTranslatex((GLfixed)(-eyex * 65536),
                 (GLfixed)(-eyey * 65536),
                 (GLfixed)(-eyez * 65536));
}


jint Java_jp_ks_livewallpaper_opengl_snowfull_LiveWallpaperRenderer_NDKonSurfaceCreated( JNIEnv *env, jobject obj ) {
	__android_log_write(ANDROID_LOG_DEBUG, NDK_INTERFACE_TAG_RENDERER,"NDKonSurfaceCreated");

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
//	glShadeModel( GL_FLAT );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
//	glEnableClientState( GL_TEXTURE_COORD_ARRAY);

	glShadeModel(GL_SMOOTH);

	return 0;
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_LiveWallpaperRenderer_NDKsetAspect
  (JNIEnv *env, jobject obj, jint orientation, jfloat vertical, jfloat horizontal ) {
	Config* config;
	
	config = Config::getInstance();
	
	config->setAspect( orientation, vertical, horizontal );
	
	return 0;
	
}


jint Java_jp_ks_livewallpaper_opengl_snowfull_LiveWallpaperRenderer_NDKonDrawFrame
	(JNIEnv *env, jobject obj, jfloat xOffset ) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
		
	gluLookAt( 	xOffset*1.5, 0.0f, 3.0f,
				xOffset*1.5, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f );	
}

jint Java_jp_ks_livewallpaper_opengl_snowfull_LiveWallpaperRenderer_NDKinitialize
  (JNIEnv *env, jobject obj) {
	Config* config;
	//このタイミングでは、一度必ずインスタンスを削除
	Config::deleteInstance();
	
	config = Config::getInstance();
}


jint Java_jp_ks_livewallpaper_opengl_snowfull_LiveWallpaperRenderer_NDKrelease
  (JNIEnv *env, jobject obj) {
	
}
