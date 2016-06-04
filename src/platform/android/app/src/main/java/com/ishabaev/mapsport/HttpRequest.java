package com.ishabaev.mapsport;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.os.StrictMode;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.ByteBuffer;

public class HttpRequest {

    public HttpRequest(){

    }

    public boolean writeFile(byte[] data, long length) {

        return false;
    }

    public byte[] getString(int x) {
        return new byte[]{0,1,2,3,4,5,6,7};
    }

    public byte[] send(int x, int y, int z) {
        //synchronized (this) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();

            StrictMode.setThreadPolicy(policy);
            InputStream input = null;
            OutputStream output = null;
            HttpURLConnection connection = null;
            String sUrl = "http://c.tile.openstreetmap.org/" + (-z) + "/" + x + "/" + y + ".png";
            try {
                URL url = new URL(sUrl);
                connection = (HttpURLConnection) url.openConnection();
                connection.connect();

                // this will be useful to display download percentage
                // might be -1: server did not report the length
                //int fileLength = connection.getContentLength();

                // download the file
                input = connection.getInputStream();


            /*
            String filePaTh = Environment.getExternalStorageDirectory().getPath() +
                   "/tiles/osm/" + (-z) + "/" + x;

            File folder = new File(filePaTh);

            if (!folder.exists()) {
                folder.mkdirs();
            }

            output = new FileOutputStream(filePaTh + "/" + y + ".png");

            byte data[] = new byte[4096];
            long total = 0;
            int count;
            while ((count = input.read(data)) != -1) {
                total += count;
                output.write(data, 0, count);
            }
            */

                //BufferedInputStream bis = new BufferedInputStream(input);
                //Bitmap bm = BitmapFactory.decodeStream(bis);
                //bis.close();
                //input.close();
                //ByteBuffer buffer = ByteBuffer.allocateDirect(bm.getByteCount());
                //bm.copyPixelsToBuffer(buffer);
                //int[] pixels = new int[bm.getByteCount()];
                //bm.getPixels(pixels, 0,0,0,0,bm.getWidth(),bm.getHeight());
                byte[] d = new byte[connection.getContentLength()];
                //byte data[] = new byte[connection.getContentLength()];
                connection.getInputStream().read(d, 0, connection.getContentLength());
                return d;
            } catch (Exception e) {
                e.printStackTrace();
                return null;
            } finally {
                try {
                    if (output != null)
                        output.close();
                    if (input != null)
                        input.close();
                } catch (IOException ignored) {
                    ignored.printStackTrace();
                }

                if (connection != null)
                    connection.disconnect();
            }
        //}
    }
}
