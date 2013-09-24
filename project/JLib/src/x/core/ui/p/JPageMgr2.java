package x.core.ui.p;

import android.content.Intent;
import android.util.Log;

public class JPageMgr2 {
	private static Intent it;
	private static int lockNum;
	
	public static void lockScreen(boolean lock) {
		if (lock) {
			++lockNum;
		} else {
			if (lockNum > 0) {
				--lockNum;
			} else {
				Log.e("X", "JPageMgr2.lockScreen lock num is error");
			}
		}
	}
	
	public static boolean isScreenLocked() {
		return lockNum > 0;
	}
	
	public static Intent getIntent() {
		return it;
	}
	
	public static void loadNewPage(Object page, String pageName, int animType) {
		lockScreen(true);
		JPage2 prev = (JPage2)page;
		it  = new Intent(prev, JPage2.class);
		it.setFlags(Intent.FLAG_ACTIVITY_NO_HISTORY|Intent.FLAG_ACTIVITY_CLEAR_TOP);
		it.putExtra("_page_name_", pageName);
		prev.startActivity(it);
		
		int in = AnimType2.getInAnim(animType);
		int out = AnimType2.getOutAnim(animType);
		prev.overridePendingTransition(in, out);
		prev.finish();
		lockScreen(false);
	}
	
	public static void loadExistPage(Object page, String pageName, int pageId, int animType) {
		lockScreen(true);
		JPage2 prev = (JPage2)page;
		it  = new Intent(prev, JPage2.class);
		it.setFlags(Intent.FLAG_ACTIVITY_NO_HISTORY|Intent.FLAG_ACTIVITY_CLEAR_TOP);
		it.putExtra("_page_name_", pageName);
		it.putExtra("_page_id_", String.valueOf(pageId));
		prev.startActivity(it);
		
		int in = AnimType2.getInAnim(animType);
		int out = AnimType2.getOutAnim(animType);
		prev.overridePendingTransition(in, out);
		prev.finish();
		lockScreen(false);
	}
}
