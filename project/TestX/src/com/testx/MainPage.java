package com.testx;

import x.core.ui.JPage;
import x.core.ui.Platform;

public class MainPage extends JPage {

	static {
		Platform.init(com.testx.R.class);
		
		System.loadLibrary("X");
		System.loadLibrary("TestX");
	}
	
	public MainPage() {
		super("MainPage");
	}

}
