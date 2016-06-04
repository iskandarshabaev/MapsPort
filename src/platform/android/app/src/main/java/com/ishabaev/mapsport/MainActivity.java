package com.ishabaev.mapsport;

import android.opengl.GLSurfaceView;
import android.os.Build;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;
    private RendererWrapper rendererWrapper;
    private Button zoomInBtn;
    private Button zoomOutBtn;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        glSurfaceView = (GLSurfaceView) findViewById(R.id.glsurface);

        if (isProbablyEmulator()) {
            // Avoids crashes on startup with some emulator images.
            glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        }

        rendererWrapper = new RendererWrapper(this);
        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(rendererWrapper);


        glSurfaceView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event != null) {
                    // Convert touch coordinates into normalized device
                    // coordinates, keeping in mind that Android's Y
                    // coordinates are inverted.
                    final float normalizedX = (event.getX() / 256) * 2;
                    final float normalizedY = -((event.getY() / 256) * 2);

                    if (event.getAction() == MotionEvent.ACTION_DOWN) {
                        glSurfaceView.queueEvent(new Runnable() {
                            @Override
                            public void run() {
                                rendererWrapper.handleTouchPress(normalizedX, normalizedY);
                            }
                        });
                    } else if (event.getAction() == MotionEvent.ACTION_MOVE) {
                        glSurfaceView.queueEvent(new Runnable() {
                            @Override
                            public void run() {
                                rendererWrapper.handleTouchDrag(normalizedX, normalizedY);
                            }
                        });
                    } else if (event.getAction() == MotionEvent.ACTION_UP) {
                        glSurfaceView.queueEvent(new Runnable() {
                            @Override
                            public void run() {
                                rendererWrapper.handleTouchesEnded(normalizedX, normalizedY);
                            }
                        });
                    }

                    return true;
                } else {
                    return false;
                }
            }
        });


        zoomInBtn = (Button) findViewById(R.id.zoomIn);
        zoomOutBtn = (Button) findViewById(R.id.zoomOut);
        zoomInBtn.setOnClickListener(onClickListener);
        zoomOutBtn.setOnClickListener(onClickListener);
    }

    View.OnClickListener onClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            switch (v.getId()){
                case R.id.zoomIn:
                    rendererWrapper.zoomIn();
                    break;
                case (R.id.zoomOut):
                    rendererWrapper.zoomOut();
                    break;
            }
        }
    };

    private boolean isProbablyEmulator() {
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
                && (Build.FINGERPRINT.startsWith("generic")
                || Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk")
                || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86"));
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
    }
}
