package com.android.support;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Toast;


public class MainActivity extends Activity {

	

    //To call onCreate, please refer to README.md
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Toast.makeText(getApplicationContext(),"Mod does not show without game yet",Toast.LENGTH_LONG).show();
      


    }
    
   /* static {
         System.loadLibrary("native-lib");
     }*/
    /*When you change the lib name, change also on Android.mk file
     Both must have same name
    Remember to put the smali of load library in game's mainactivity for the menu to show up, no extra java or dex files needed to show imgui
    */
}
