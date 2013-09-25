package com.test;

import x.core.ui.JApplication;

public class TApplication extends JApplication {
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
