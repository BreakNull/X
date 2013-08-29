package com.test;

import x.core.ui.JPage;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class FirstActivity extends JPage {
	
	public FirstActivity() {
		super("MainPage");
	}

	static {
		System.loadLibrary("X");
		System.loadLibrary("TestX");
	}
   
}