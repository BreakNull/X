package x.core.ui.p;

import android.app.Application;

public abstract class JApplication2 extends Application {
	private static JApplication2 app;
	
	public JApplication2() {
		app = this;
	}
	
	public static JApplication2 instance() {
		return app;
	}
	
	public void onCreate() {
		super.onCreate();
		System.loadLibrary("X");
	}
	
	public abstract String getEntryPageName();
	
	public abstract Class getR();
}
