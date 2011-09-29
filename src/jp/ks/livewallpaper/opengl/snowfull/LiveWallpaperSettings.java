package jp.ks.livewallpaper.opengl.snowfull;


import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceActivity;
import android.view.Gravity;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;

import com.google.ads.*; 

public class LiveWallpaperSettings extends PreferenceActivity implements SharedPreferences.OnSharedPreferenceChangeListener {
	private AdView adView;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getPreferenceManager().setSharedPreferencesName(SnowWallpaperService.SHARED_PREFS_NAME);
        addPreferencesFromResource(R.xml.settings);
        getPreferenceManager().getSharedPreferences().registerOnSharedPreferenceChangeListener(this);
        
        //----------------------------------------------------------
        //admob çLçêï\é¶ê›íË
        //----------------------------------------------------------
/*
        adView = new AdView(this, AdSize.BANNER, "a14e75596403699");
        adView.setVisibility(android.view.View.VISIBLE);
        adView.loadAd(new AdRequest());
        
        
        LayoutParams adLayoutParams = new LinearLayout.LayoutParams(
        									LayoutParams.FILL_PARENT, 
        									LayoutParams.WRAP_CONTENT);
        adView.setLayoutParams(adLayoutParams); 
        
        LinearLayout linearlayout = new LinearLayout(this);
        linearlayout.addView(adView);
        linearlayout.setGravity(Gravity.BOTTOM);
        
        LayoutParams layoutParams = new LinearLayout.LayoutParams(
        									LayoutParams.FILL_PARENT, 
        									LayoutParams.FILL_PARENT);
        addContentView(linearlayout, layoutParams);
*/
    }
    
    @Override
    protected void onDestroy() {
        getPreferenceManager().getSharedPreferences().unregisterOnSharedPreferenceChangeListener(this);
        super.onDestroy();
    }
    
    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
    }
}
