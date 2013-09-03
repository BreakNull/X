package com.test;

import x.core.ui.JAnimHelper;
import x.core.ui.JPage;
import x.core.ui.JPlatform;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class FirstActivity extends JPage {
	
	public FirstActivity() {
		super("MainPage");
	}

	static {
		JPlatform.init(R.class);
		JAnimHelper.init(R.class);
		System.loadLibrary("X");
		System.loadLibrary("TestX");
	}
   
}