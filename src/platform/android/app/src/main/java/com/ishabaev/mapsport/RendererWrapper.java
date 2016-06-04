package com.ishabaev.mapsport;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Environment;

import com.ishabaev.mapsport.platform.PlatformFileUtils;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RendererWrapper implements GLSurfaceView.Renderer {
	static {
		System.loadLibrary("mapsport");
	}

	private final Context context;

	public RendererWrapper(Context context) {
		this.context = context;
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		PlatformFileUtils.init_file_manager(Environment.getExternalStorageDirectory().getPath());
		PlatformFileUtils.init_http_platform();
		PlatformFileUtils.init_asset_manager(context.getAssets());
		PlatformFileUtils.init_asset_manager_cpp(context.getAssets());
		on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		on_draw_frame();
	}

	private static native void on_surface_created();

	private static native void on_surface_changed(int width, int height);

	private static native void on_draw_frame();

	public void handleTouchPress(float normalizedX, float normalizedY) {
		on_touch_press(normalizedX, normalizedY);
	}

	public void handleTouchDrag(float normalizedX, float normalizedY) {
		on_touch_drag(normalizedX, normalizedY);
	}

	public void handleTouchesEnded(float normalizedX, float normalizedY) {
		on_touches_ended(normalizedX, normalizedY);
	}

	public void zoomIn() {
		zoom_in();
	}

	public void zoomOut() {
		zoom_out();
	}

	private static native void zoom_in();

	private static native void zoom_out();

	private static native void on_touch_press(float normalized_x, float normalized_y);

	private static native void on_touches_ended(float normalized_x, float normalized_y);
	
	private static native void on_touch_drag(float normalized_x, float normalized_y);
}