package x.core.ui;

import android.app.Application;

public abstract class JApplication extends Application {
	private static JApplication app;
	
	public JApplication() {
		app = this;
	}
	
	public static JApplication instance() {
		return app;
	}
	
	public void onCreate() {
		super.onCreate();
		System.loadLibrary("X");
	}
	
	public abstract String getEntryPageName();
	
	public abstract Class getR();
}
