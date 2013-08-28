package com.test;

import x.core.ui.JPage;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class FirstActivity extends JPage {
	
	public FirstActivity() {
		super("MainActivity");
		Log.i("TestX", "MainActivity in....");
	}

	static {
		Log.i("TestX", "MainActivity library load begin....");
		System.loadLibrary("X");
		System.loadLibrary("TestX");
		Log.i("TestX", "MainActivity library load end....");
	}

	private native void MyInit(); 
   
}