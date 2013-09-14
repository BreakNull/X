package com.test;

import android.util.Log;
import x.core.ui.JAnimHelper;
import x.core.ui.JApplication;
import x.core.ui.JPlatform;

public class TApplication extends JApplication {
	public TApplication() {
	}
	
	public void onCreate() {
		super.onCreate();
		JPlatform.init(R.class);
		System.loadLibrary("TestX");
	}
	
	@Override
	public String getFirstPageName() {
		return "HelloPage";
	}

	@Override
	public boolean isFullScreen() {
		return false;
	}

}
