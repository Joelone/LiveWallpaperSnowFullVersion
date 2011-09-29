package jp.ks.livewallpaper.opengl.snowfull;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import net.rbgrn.android.glwallpaperservice.GLWallpaperService;
import android.util.Log;
import android.content.Context;
import android.content.SharedPreferences;
import android.opengl.GLU;

// Original code provided by Robert Green
// http://www.rbgrn.net/content/354-glsurfaceview-adapted-3d-live-wallpapers
public class LiveWallpaperRenderer implements GLWallpaperService.Renderer {
	private Particle mParticle = null;
	private Background mBackground = null;
	private Context mWallpaperServiceContext;
	private float   mViewxOffset=0.0f;
	private boolean mIsFpsDebug=false;
	private boolean mIsSetTexture=false;
	
	//fps60に設定
	//但し、なんらかの制約なのか何も処理をしなくても33fps以上のスペックがでない
	//(GLWallpaperServiceで制約されてる？調査要)
	private int		mSleepTimeMillis=17; 
	private long	mPrevTimeMillis=0;
	
	private long start_time;
	private int  fps=0;
	
	//Native Method
	native private int NDKinitialize();
	native private int NDKonSurfaceCreated();
	native private int NDKsetAspect( int oriental, float vertical, float horizontal );
	native private int NDKonDrawFrame( float xOffset );
	native private int NDKrelease();
	
	
	
	public LiveWallpaperRenderer( Context context ) {
		Log.d("LiveWallpaperRenderer", "create");
		mWallpaperServiceContext = context;
		NDKinitialize();
		mParticle = new Particle( mWallpaperServiceContext );
		mBackground = new Background( mWallpaperServiceContext );
		mPrevTimeMillis = System.currentTimeMillis();
		
		fpsdebug_start();
	}
	
	private void fpsdebug_start() {
		if( mIsFpsDebug ) {
			start_time =  System.currentTimeMillis();
		}
	}
	
	private void fpsdebug_sprit() {
		if( mIsFpsDebug ) {
			long end_time =  System.currentTimeMillis();
			fps++;
			if( end_time-start_time >= 1000 ) {
				Log.d( "FPS", "fps="+fps);
				fps=0;
				start_time = end_time;
			}
		}
	}
	
	private void fps_spleep() {
		long nowTimeMillis=System.currentTimeMillis();
		long sleepTimeMillis = mSleepTimeMillis - (nowTimeMillis - mPrevTimeMillis);
		try {
			if( sleepTimeMillis < 0 ) {
				//1回の描画に17msec以上かかっている
				//但し、現状のシステムでは、30fps以上でないがデバイス依存とも考えられるため、
				//fps制御処理は入れておく
				//ToDo:現在は原因不明のため、調査要
				//GLWallpaperServiceの不具合？
				sleepTimeMillis = 0;
			}
			
			Thread.sleep( mSleepTimeMillis );
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		mPrevTimeMillis=nowTimeMillis;
	}
	
	public void onDrawFrame(GL10 gl) {
		NDKonDrawFrame( mViewxOffset );
		
		mBackground.draw(gl);
		mParticle.draw(gl);

    	fpsdebug_sprit();
    	fps_spleep();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
//		float ratio = (float) width / height;
		Log.d( "LiveWallpaperRenderer", "onSurfaceChanged" );
		float f_horizontal;
		float f_vertical;
		
		if( width < height ) {
			f_vertical   = 1.0f;
			f_horizontal = (float)width / height;
		}
		else {
			f_vertical   = (float)height / width;
			f_horizontal = 1.0f;
		}
		
		Log.d( "LiveWallpaperRenderer", "vertical="+f_vertical+" horizontal="+f_horizontal );
		
		gl.glViewport( 0, 0, width, height );	
    	gl.glMatrixMode( GL10.GL_PROJECTION );
    	gl.glLoadIdentity();
    	
    	gl.glFrustumf( -f_horizontal, 
    					f_horizontal, 
    					-f_vertical, 
    					f_vertical, 
    					1.0f, 
    					10.0f );
    	
    	NDKsetAspect( 0, f_vertical, f_horizontal );
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		Log.d( "LiveWallpaperRenderer", "onSurfaceCreated" );
    	NDKonSurfaceCreated();
    	if( mIsSetTexture == false ) {
    		//onDestroy->onResume時のメモリリーク対策
    		mParticle.setTexture();
    		mBackground.setTexture();
    		mIsSetTexture = true;
    	}
	}
	
	public void setXOffset( float xOffset ) {
		mViewxOffset = xOffset;
	}
	
	/**
	 * Called when the engine is destroyed. Do any necessary clean up because
	 * at this point your renderer instance is now done for.
	 */
	public void release() {
//		mSnow.release();
		
		NDKrelease();
	}
	
	public void setPreference( SharedPreferences sharedPreferences, String key ) {
		mParticle.setPreference(sharedPreferences, key);
		mBackground.setPreference(sharedPreferences, key);
	}
}