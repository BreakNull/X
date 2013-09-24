package com.test;

import android.util.Log;
import x.core.ui.JAnimHelper;
import x.core.ui.JApplication;
import x.core.ui.JPlatform;
import x.core.ui.p.JApplication2;

public class TApplication extends JApplication2 {
	public TApplication() {
	}
	
	public void onCreate() {
		super.onCreate();
		System.loadLibrary("TestX");
	}

	@Override
	public String getEntryPageName() {
		return "HelloPage";
	}

	@Override
	public Class getR() {
		return com.test.R.class;
	}

}
