package x.core.ui;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.app.ActivityGroup;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.view.ViewGroup.LayoutParams;
import android.widget.*;
import android.view.animation.*;

//Animation.AnimationListener
public class JPageMgr extends ActivityGroup {
	private static JPageMgr ins;
	private ViewFlipper fliper;
	private List<JPageInfo> pages;
	private List<JPageInfo> noUsedPages;
	private int keyDisable;
	private int touchDisable;
	private int screenDisable;
	
	public JPageMgr() {
		pages = new ArrayList<JPageInfo>();
		noUsedPages = new ArrayList<JPageInfo>();
		ins = this;
	}
	
	public static JPageMgr instance() {
		return ins;
	}
	
	public void lockKey(boolean locked) {
		if (locked) {
			++keyDisable;
		} else {
			if (keyDisable > 0)
				--keyDisable;
		}
	}
	
	public void lockTouch(boolean locked) {
		if (locked) {
			++touchDisable;
		} else {
			if (touchDisable > 0)
				--touchDisable;
		}
	}
	
	public void lockScreen(boolean locked) {
		if (locked) {
			++screenDisable;
		} else {
			if (screenDisable > 0)
				--screenDisable;
			else
				Log.e("X", "lockScreen the lock num < 0");
		}
	}
	
	public boolean isKeyLocked() {
		return keyDisable > 0;
	}
	
	public boolean isTouchLocked() {
		return touchDisable > 0;
	}
	
	public boolean isScreenLocked() {
		return screenDisable > 0;
	}

	public void onCreate(Bundle savedInstanceState) {
		lockScreen(true);
		super.onCreate(savedInstanceState);
		fliper = new ViewFlipper(this);
		setContentView(fliper);
		JApplication app = (JApplication) this.getApplication();
		String name = app.getFirstPageName();
		loadNewPage(name, JAnimHelper.AnimType.S_NONE);
		lockScreen(false);
	}
	
	public boolean dispatchKeyEvent(KeyEvent ev) {
		//TODO: if key locked return true
		if ((ev.getKeyCode() == KeyEvent.KEYCODE_BACK) && 
				((ev.getFlags() & KeyEvent.FLAG_LONG_PRESS) != 0)) {
			return true;
		}
		if (isScreenLocked() || isKeyLocked()) {
			Log.i("X", "====ignore key evt==" + ev);
			return true;
		}
		Log.i("X", "key evt=" + ev);
		Activity cur = getCurPage();
		if(null != cur) {
			if (cur.dispatchKeyEvent(ev)) {
				return true;
			}
		}
		return super.dispatchKeyEvent(ev);
	}
	
	public boolean dispatchTouchEvent(MotionEvent ev) {
		//TODO:
		return super.dispatchTouchEvent(ev);	
	}
	
	public boolean dispatchTrackballEvent(MotionEvent ev) {
		//TODO:
		return super.dispatchTrackballEvent(ev);
	}
	
	public final JPage getCurPage() {
		return (JPage)getLocalActivityManager().getCurrentActivity();
	}
	
	public JPage getPageById(int id) {
		return (JPage)getLocalActivityManager().getActivity(String.valueOf(id));
	}
	
	private void installWindow(Window win, int animType) {
		ViewGroup vg = (ViewGroup)win.getDecorView().getParent();
//		if (vg != null) {
//			vg.removeView(win.getDecorView());
//		}
		for (int i = fliper.getChildCount() - 1; i >= 0; --i) {
			if (fliper.getChildAt(i) != fliper.getCurrentView()) {
				fliper.removeViewAt(i);
			}
		}
		LayoutParams params = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
		fliper.addView(win.getDecorView(), params);
		JAnimHelper.installAnim(this, fliper, animType);
		fliper.showNext();
	}
	
	public void loadNewPage(String pageName, int animType) {
		if (pageName == null || pageName.length() == 0) {
			return;
		}
		lockScreen(true);
		Intent it  = new Intent(this, JPage.class);
		//it.putExtra("pagename", pageName);
		JPage.setCurPageName(pageName);
		int id = JPage.getNextId();
		Window win = getLocalActivityManager().startActivity(String.valueOf(id), it);
		if (win == null) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadNewPage pageName=" + pageName + " start activity fail");
			return;
		}
		JPage cur = getPageById(id);
		Log.d("X", "JPageMgr.loadNewPage cur=" + cur);
		JPageInfo pi = new JPageInfo(cur, animType, cur.getId(), cur.getName());
		pages.add(pi);
		installWindow(win, animType);
		lockScreen(false);
	}
	
	public void loadExistPage(String pageName, int animType) {
		lockScreen(true);
		int i = 0;
		for (; i < pages.size(); ++i) {
			JPageInfo p = pages.get(i);
			if (p.pageName.equals(pageName)) {
				break;
			}
		}
		if (i == pages.size()) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadExisPage not find page '" + pageName + "'");
			return;
		}
		int id = pages.get(i).pageId;
		loadExistPage(id, animType);
		lockScreen(false);
	}
	
	public void loadExistPage(int pageId, int animType) {
		lockScreen(true);
		int i = 0;
		for (; i < pages.size(); ++i) {
			if (pages.get(i).pageId == pageId) {
				break;
			}
		}
		if (i == pages.size()) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadExisPage not find page id=" + pageId);
			return;
		}
		
		JPageInfo p = pages.get(i);
		Intent it  = new Intent(this, JPage.class);
		it.putExtra("pagename", p.pageName);
		JPage.setCurPageName(p.pageName);
		Window win = getLocalActivityManager().startActivity(String.valueOf(p.pageId), it);
		if (win == null) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadNewPage pageName=" + p.pageName + ",pageId=" +p.pageId + " start activity fail");
			return;
		}
		installWindow(win, animType);
		
		for (++i; i < pages.size(); ++i) {
			JPageInfo px = pages.remove(i);
			destroyPage(px);
		}
		lockScreen(false);
	}
	
	private void destroyPage(JPageInfo pi) {
		long curTime = System.currentTimeMillis();
		noUsedPages.add(pi);
		pi.destroyTime = curTime;
		for (int i = 0; i < noUsedPages.size(); ++i) {
			JPageInfo px = noUsedPages.get(i);
			if (px.page.canDestroy()/* && (curTime - px.destroyTime) > 3000*/) {
				noUsedPages.remove(i);
				getLocalActivityManager().destroyActivity(String.valueOf(px.pageId), true);
				--i;
			}
		}
	}
	
	public void goBack() {
		if (pages.size() < 2) {
			//finish
			int id = pages.get(0).pageId;
			getLocalActivityManager().destroyActivity(String.valueOf(id), true);
			System.exit(0);
			return;
		}
		
		JPageInfo p1 = pages.get(pages.size() - 1);
		JPageInfo p2 = pages.get(pages.size() - 2);
		int at = JAnimHelper.getReverseAnim(p1.aminType);
		loadExistPage(p2.pageId, at);
	}
	
	public void removePage(int pageId) {
		int curPageId = this.getCurPage().getId();
		if (pageId == curPageId) {
			Log.e("X", "JPageMgr.removePage can't remove current page, pageId=" + pageId);
			return;
		}
		for (int i = 0; i < pages.size(); ++i) {
			JPageInfo p = pages.get(i);
			if (p.pageId == pageId) {
				pages.remove(i);
				destroyPage(p);
				break;
			}
		}
	}
	
	public void removeFirstPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = 0; i < pages.size(); ++i) {
			JPageInfo p = pages.get(i);
			if (curPageId != p.pageId && p.pageName.equals(pageName)) {
				pages.remove(i);
				destroyPage(p);
				break;
			}
		}
	}
	
	public void removeLastPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = pages.size() - 1; i >= 0; --i) {
			JPageInfo p = pages.get(i);
			if (curPageId != p.pageId && p.pageName.equals(pageName)) {
				pages.remove(i);
				destroyPage(p);
				break;
			}
		}
	}
	
	public void removeAllPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = pages.size() - 1; i >= 0; --i) {
			JPageInfo p = pages.get(i);
			if (curPageId != p.pageId && p.pageName.equals(pageName)) {
				pages.remove(i);
				destroyPage(p);
			}
		}
	}
	
	private static final class JPageInfo {
		public JPage page;
		public int aminType;
		public int pageId;
		public String pageName;
		public long destroyTime;
		
		public JPageInfo(JPage p, int at, int id, String name) {
			page = p;
			aminType = at;
			pageId = id;
			pageName = name;
		}
	}
}
