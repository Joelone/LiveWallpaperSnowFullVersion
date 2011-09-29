package jp.ks.livewallpaper.opengl.snowfull;


import java.io.IOException;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PixelFormat;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import net.rbgrn.android.glwallpaperservice.GLWallpaperService;



// Original code provided by Robert Green
// http://www.rbgrn.net/content/354-glsurfaceview-adapted-3d-live-wallpapers
public class SnowWallpaperService extends GLWallpaperService {
	static {
        System.loadLibrary("LiveWallpaperNative");
	}
	
	public static final String SHARED_PREFS_NAME = " jp.ks.livewallpaper.opengl.snow";
	
	public SnowWallpaperService() {
		super();
		Log.d("SnowWallpaperService", "SnowWallpaperService");
	}
	public Engine onCreateEngine() {
		SnowEngine engine = new SnowEngine(this);
		Log.d("SnowWallpaperService", "onCreateEngine");
		return engine;
	}
	
	

	class SnowEngine extends GLEngine implements SharedPreferences.OnSharedPreferenceChangeListener {
		LiveWallpaperRenderer renderer;
		
		private SharedPreferences prefs;
		
		
		public SnowEngine( Context activityContext) {
			super();
			// handle prefs, other initialization
			Log.d("SnowEngine", "SnowEngine");
			//ÉåÉìÉ_ÉâÅ[ÇÃÇÃê›íË
			renderer = new LiveWallpaperRenderer(activityContext);
			setRenderer(renderer);
			setRenderMode(RENDERMODE_CONTINUOUSLY);
			
			//ê›íËâÊñ ÇÃéÊìæÅEèâä˙âª
			prefs = SnowWallpaperService.this.getSharedPreferences(SHARED_PREFS_NAME, 0);
	        prefs.registerOnSharedPreferenceChangeListener(this);
	        onSharedPreferenceChanged(prefs, null);
		}

		@Override
		public void onDestroy() {
			Log.d("SnowEngine", "onDestroy");
			super.onDestroy();
			if (renderer != null) {
				renderer.release(); // assuming yours has this method - it should!
			}
//			renderer = null;
		}
		
		@Override
		public void onOffsetsChanged(float xOffset, float yOffset,
            float xOffsetStep, float yOffsetStep, int xPixelOffset,
            int yPixelOffset) {
//			Log.d("SnowEngine", "xOffset="+xOffset);
			renderer.setXOffset( xOffset );
		}
		
		@Override
		public void onSharedPreferenceChanged( SharedPreferences sharedPreferences, String key) {
//			Log.d("SnowEngine", "key="+key );
//			Log.d("SnowEngine", "value="+sharedPreferences.getString(key, "120") );
			renderer.setPreference(prefs, key);
		}
		
		
	}
}
