package jp.ks.livewallpaper.opengl.snowfull;


import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;


public class Particle {
	private int			mParticleNum = 700;		//描画する雪の数
	private Bitmap 		mParticleBitmap;		//32bit bitmap
	private Context		mWallpaperServiceContext;
	private String		mLogTag = "Particle";
	
	native private int NDKcreateNativeClass();
	native private int NDKinitialize();
	native private int NDKrelease();
	native private int NDKsetTextureData( int width, int height, int[] p_image );
	native private int NDKdraw();
	native private int NDKsetParticleNum( int particle_num );
	native private int NDKsetParticleSpeed( int particle_speed );
	native private int NDKsetOrientation( int orientation );
	
	static final int	ORIENTATION_LANDSCAPE = 0;
	static final int 	ORIENTATION_PORTRAIT  = 1;
	
	public Particle(Context context){
		mWallpaperServiceContext = context;
		
		NDKcreateNativeClass();
	}
	
	public void setTexture() {
		int width;
		int height;
		
		//リソースからバイナリイメージ読み込み
		Resources res = mWallpaperServiceContext.getResources();
		Bitmap particle_bitmap = BitmapFactory.decodeResource(res, R.drawable.snow);
		
		width = particle_bitmap.getWidth();
		height = particle_bitmap.getHeight();
		
		int[] pixels = new int[width*height];
		
		particle_bitmap.getPixels(pixels, 0, width, 0, 0, width, height );
		
		//Native側にセット
		NDKsetTextureData( width, height, pixels );
		
		particle_bitmap.recycle();
		particle_bitmap = null;
		pixels = null;
	}
	
	public void release() {
		NDKrelease();
	}
	 
	public void draw(GL10 gl) {
		NDKdraw();
	}
	
	public void setOrientation( int orientation ) {
		int arg_orientation;
		
		switch( orientation ) {
		case  Configuration.ORIENTATION_LANDSCAPE:
			arg_orientation = ORIENTATION_LANDSCAPE;
			break;
		case  Configuration.ORIENTATION_PORTRAIT:
		default:
			arg_orientation = ORIENTATION_PORTRAIT;
			break;
		}
		
		NDKsetOrientation(arg_orientation);
	}
	
	public void setPreference( SharedPreferences sharedPreferences, String key ) {

		Resources res = mWallpaperServiceContext.getResources();
		
		
		NDKsetParticleNum( Integer.valueOf(
								sharedPreferences.getString(
										res.getString( R.string.particle_density_key ), 
										"512")
								)
		);
		
		NDKsetParticleSpeed(Integer.valueOf(
								sharedPreferences.getString(
										res.getString( R.string.particle_speed_key ), 
										"4096")
								)
		);
		
		NDKinitialize();
	}
}
