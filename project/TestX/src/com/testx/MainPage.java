package com.testx;

import x.core.ui.JPage;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class MainPage extends JPage {

	static {
		System.loadLibrary("X");
		System.loadLibrary("TestX");
	}
	
	public MainPage() {
		super("MainPage");
	}

}
