package x.core.ui;

import android.app.Application;

public abstract class JApplication extends Application {
	public JApplication() {
		
	}
	
	public void onCreate() {
		super.onCreate();
		System.loadLibrary("X");
	}
	
	public abstract String getFirstPageName();
}
