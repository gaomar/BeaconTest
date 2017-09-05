/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.annotation.TargetApi;
import android.bluetooth.le.AdvertiseCallback;
import android.bluetooth.le.AdvertiseSettings;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;

import org.altbeacon.beacon.Beacon;
import org.altbeacon.beacon.BeaconParser;
import org.altbeacon.beacon.BeaconTransmitter;
import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.UUID;

import static android.os.Build.ID;

public class AppActivity extends Cocos2dxActivity {
    private static Beacon beacon;
    private static BeaconTransmitter beaconTransmitter;
    private static AppActivity myref;
    private String wkUUID;

    public static synchronized AppActivity getInstance() {
        return myref;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        myref = this;

    }

    // UUID取得
    public static String initBeaconUUID()
    {
        return UUID.randomUUID().toString();
    }

    // Beacon初期化
    public static void initBeacon(String uuid)
    {
        beacon = new Beacon.Builder()
                .setId1(uuid)
                .setId2("1")
                .setId3("80")
                .setManufacturer(0x004C)
                .build();

        BeaconParser beaconParser = new BeaconParser()
                .setBeaconLayout("m:2-3=0215,i:4-19,i:20-21,i:22-23,p:24-24");
        beaconTransmitter = new BeaconTransmitter(AppActivity.getInstance(), beaconParser);

    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public static void beaconAction(boolean flg)
    {
        if (flg) {
            //送信開始
            AppActivity.getInstance().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    beaconTransmitter.startAdvertising(beacon, new AdvertiseCallback() {
                        @Override
                        public void onStartSuccess(AdvertiseSettings settingsInEffect) {
                            super.onStartSuccess(settingsInEffect);
                            Log.d("BeaconTest", "Beacon Success!");
                            beaconActionCallback(true);
                        }

                        @Override
                        public void onStartFailure(int errorCode) {
                            super.onStartFailure(errorCode);
                            beaconActionCallback(false);
                            Log.d("BeaconTest", "Beacon Failure!");
                        }
                    });

                }
            });
        } else {
            if (beaconTransmitter.isStarted()) {
                beaconTransmitter.stopAdvertising();
            }

            beaconActionCallback(true);
        }

    }

    @Override
    protected void onStop() {
        super.onStop();

        if (beaconTransmitter.isStarted()) {
            beaconTransmitter.stopAdvertising();
        }
    }

    private static native void beaconActionCallback(boolean flg);
}
