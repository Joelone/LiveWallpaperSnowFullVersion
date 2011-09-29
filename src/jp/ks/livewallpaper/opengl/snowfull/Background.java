package jp.ks.livewallpaper.opengl.snowfull;

import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class Background {
	Context mWallpaperServiceContext;
	
	native private int NDKcreateNativeClass();
	native private int NDKinitialize();
	native private int NDKdraw();
	native private int NDKsetOrientation( int orientation );
	native private int NDKsetPattern( int pattern );
	native private int NDKsetTextureData( int width, int height, int[] p_image );
	native private int NDKsetMoonVisibility( boolean isVisible );
	
	public Background(Context context) {
		mWallpaperServiceContext = context;
		
		NDKcreateNativeClass();
	}
	
	public void setTexture(){
		int width;
		int height;
		
		//リソースからバイナリイメージ読み込み
		Resources res = mWallpaperServiceContext.getResources();
		Bitmap  moon_bitmap = BitmapFactory.decodeResource(res, R.drawable.moon);
		
		width = moon_bitmap.getWidth();
		height = moon_bitmap.getHeight();
		
		int[] pixels = new int[width*height];
		
		moon_bitmap.getPixels(pixels, 0, width, 0, 0, width, height );
		
		//Native側にセット
		NDKsetTextureData( width, height, pixels );
		
		moon_bitmap.recycle();
		moon_bitmap = null;
		pixels = null;
	}
	
	public void draw( GL10 gl ) {
		NDKdraw();
	}
	
	public void setPreference( SharedPreferences sharedPreferences, String key ) {

		Resources res = mWallpaperServiceContext.getResources();
		
		NDKsetPattern( Integer.valueOf(
								sharedPreferences.getString(
										res.getString( R.string.background_skin_key ), 
										"1")
								)
		);
		
		NDKsetMoonVisibility( Boolean.valueOf(
								sharedPreferences.getString(
										res.getString( R.string.background_moon_key ), 
										"false")
								)
		);
		
		NDKinitialize();
	}
}
