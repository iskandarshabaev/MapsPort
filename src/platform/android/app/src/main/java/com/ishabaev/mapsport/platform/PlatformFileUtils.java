package com.ishabaev.mapsport.platform;

import android.content.res.AssetManager;
import android.util.Log;

public class PlatformFileUtils {
	public static native void init_asset_manager(AssetManager assetManager);

	public static native void init_asset_manager_cpp(AssetManager assetManager);

	public static native void init_file_manager(String path);

	public static native void init_http_platform();

	public static void log(){
		Log.d("Native", "bla bla bla");
	}

}
