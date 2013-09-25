package x.core.ui;

import android.content.Intent;
import android.util.Log;

public class JPageMgr {
	private static Intent it;
	private static boolean chagingPage;//是否正在切换页面
	private static native void LockScreen(boolean lock);
	private static native boolean IsScreenLocked();
	
	public static void lockScreen(boolean lock) {
		LockScreen(lock);
	}
	
	public static boolean isScreenLocked() {
		return IsScreenLocked();
	}
	
	public static boolean isChagingPage() {
		return chagingPage;
	}
	
	public static void SetChagingPage(boolean chaging) {
		chagingPage = chaging;
	}
	
	public static Intent getIntent() {
		return it;
	}
	
	public static void loadNewPage(Object page, String pageName, int animType) {
		SetChagingPage(true);
		JPage prev = (JPage)page;
		it  = new Intent(prev, JPage.class);
		it.setFlags(Intent.FLAG_ACTIVITY_NO_HISTORY|Intent.FLAG_ACTIVITY_CLEAR_TOP);
		it.putExtra("_page_name_", pageName);
		prev.startActivity(it);
		
		int in = AnimType.getInAnim(animType);
		int out = AnimType.getOutAnim(animType);
		prev.overridePendingTransition(in, out);
		prev.finish();
	}
	
	public static void loadExistPage(Object page, String pageName, int pageId, int animType) {
		SetChagingPage(true);
		JPage prev = (JPage)page;
		it  = new Intent(prev, JPage.class);
		it.setFlags(Intent.FLAG_ACTIVITY_NO_HISTORY|Intent.FLAG_ACTIVITY_CLEAR_TOP);
		it.putExtra("_page_name_", pageName);
		it.putExtra("_page_id_", String.valueOf(pageId));
		prev.startActivity(it);
		
		int in = AnimType.getInAnim(animType);
		int out = AnimType.getOutAnim(animType);
		prev.overridePendingTransition(in, out);
		prev.finish();
	}
}
