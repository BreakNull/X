package x.core.ui;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

public class UiThread {
	private static long uiThreadId;
	private static UiHandler handler = new UiHandler();
	
	public static boolean post(long addr, long r2) {
		if (addr == 0) {
			return false;
		}
		UiThreadRunnable rx = new UiThreadRunnable(addr, r2);
		return handler.post(rx);
	}
	
	public static boolean post2(long addr, long r2, int delayMs) {
		if (addr == 0) {
			return false;
		}
		UiThreadRunnable rx = new UiThreadRunnable(addr, r2);
		return handler.postDelayed(rx, delayMs);
	}
	
	public static String[] getFields() {
    	return null;
    }
    
    public static String[] getMethods() {
    	return new String[] {
    			"post", "(JJ)Z", "S",
    			"post2", "(JJI)Z", "S"
    	};
    }
	
	private static class UiHandler extends Handler {
		public UiHandler() {
			super(Looper.getMainLooper());
		}
		
		public void handleMessage(Message msg) {
			switch (msg.what) {
			}
		}
	}
}
