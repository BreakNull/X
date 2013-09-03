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

public class JPageMgr extends ActivityGroup implements Animation.AnimationListener {
	private static JPageMgr ins;
	private ViewFlipper fliper;
	private List<JPage> pages;
	private int keyDisable;
	private int touchDisable;
	private int screenDisable;
	
	public JPageMgr() {
		pages = new ArrayList<JPage>();
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
		fliper.setLayoutAnimationListener(this);
		setContentView(fliper);
		JApplication app = (JApplication) this.getApplication();
		String name = app.getFirstPageName();
		loadNewPage(name, 0, 0);
		lockScreen(false);
	}
	
	public boolean dispatchKeyEvent(KeyEvent ev) {
		//TODO: if key locked return true
		if ((ev.getKeyCode() == KeyEvent.KEYCODE_BACK) && 
				((ev.getFlags() & KeyEvent.FLAG_LONG_PRESS) != 0)) {
			return true;
		}
		
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
	
	private void installWindow(Window win, int inAnim, int outAnim) {
		ViewGroup vg = (ViewGroup)win.getDecorView().getParent();
		if (vg != null) {
			vg.removeView(win.getDecorView());
		}
		for (int i = fliper.getChildCount() - 1; i >= 0; --i) {
			if (fliper.getChildAt(i) != fliper.getCurrentView()) {
				fliper.removeViewAt(i);
			}
		}
		LayoutParams params = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
		fliper.addView(win.getDecorView(), params);
		JAnimHelper.installAnim(this, fliper, inAnim, outAnim);
		fliper.showNext();
	}
	
	public void loadNewPage(String pageName, int inAnim, int outAnim) {
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
		pages.add(cur);
		installWindow(win, inAnim, outAnim);
		lockScreen(false);
	}
	
	public void loadExistPage(String pageName, int inAnim, int outAnim) {
		lockScreen(true);
		int i = 0;
		for (; i < pages.size(); ++i) {
			JPage p = pages.get(i);
			if (p.getName().equals(pageName)) {
				break;
			}
		}
		if (i == pages.size()) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadExisPage not find page '" + pageName + "'");
			return;
		}
		int id = pages.get(i).getId();
		loadExistPage(id, inAnim, outAnim);
		lockScreen(false);
	}
	
	public void loadExistPage(int pageId, int inAnim, int outAnim) {
		lockScreen(true);
		int i = 0;
		for (; i < pages.size(); ++i) {
			JPage p = pages.get(i);
			if (p.getId() == pageId) {
				break;
			}
		}
		if (i == pages.size()) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadExisPage not find page id=" + pageId);
			return;
		}
		
		JPage p = pages.get(i);
		Intent it  = new Intent(this, JPage.class);
		it.putExtra("pagename", p.getName());
		JPage.setCurPageName(p.getName());
		Window win = getLocalActivityManager().startActivity(String.valueOf(p.getId()), it);
		if (win == null) {
			lockScreen(false);
			Log.e("X", "JPageMgr.loadNewPage pageName=" + p.getName() + ",pageId=" +p.getId() + " start activity fail");
			return;
		}
		installWindow(win, inAnim, outAnim);
		
		for (++i; i < pages.size(); ++i) {
			JPage px = pages.remove(i);
			getLocalActivityManager().destroyActivity(String.valueOf(px.getId()), true);
		}
		lockScreen(false);
	}
	
	public void goBack() {
		if (pages.size() < 2) {
			return;
		}
		JPage p = pages.get(pages.size() - 2);
		loadExistPage(p.getId(), 0, 0);
	}
	
	public void removePage(int pageId) {
		int curPageId = this.getCurPage().getId();
		if (pageId == curPageId) {
			Log.e("X", "JPageMgr.removePage can't remove current page, pageId=" + pageId);
			return;
		}
		for (int i = 0; i < pages.size(); ++i) {
			JPage p = pages.get(i);
			if (p.getId() == pageId) {
				pages.remove(i);
				getLocalActivityManager().destroyActivity(String.valueOf(pageId), true);
				break;
			}
		}
	}
	
	public void removeFirstPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = 0; i < pages.size(); ++i) {
			JPage p = pages.get(i);
			if (curPageId != p.getId() && p.getName().equals(pageName)) {
				pages.remove(i);
				getLocalActivityManager().destroyActivity(String.valueOf(p.getId()), true);
				break;
			}
		}
	}
	
	public void removeLastPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = pages.size() - 1; i >= 0; --i) {
			JPage p = pages.get(i);
			if (curPageId != p.getId() && p.getName().equals(pageName)) {
				pages.remove(i);
				getLocalActivityManager().destroyActivity(String.valueOf(p.getId()), true);
				break;
			}
		}
	}
	
	public void removeAllPage(String pageName) {
		int curPageId = this.getCurPage().getId();
		for (int i = pages.size() - 1; i >= 0; --i) {
			JPage p = pages.get(i);
			if (curPageId != p.getId() && p.getName().equals(pageName)) {
				pages.remove(i);
				getLocalActivityManager().destroyActivity(String.valueOf(p.getId()), true);
			}
		}
	}
	
	public void onConfigurationChanged(Configuration newConfig) {
    	super.onConfigurationChanged(newConfig);
	}

	@Override
	public void onAnimationEnd(Animation animation) {
		// TODO Auto-generated method stub
		lockScreen(false);
	}

	@Override
	public void onAnimationRepeat(Animation animation) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onAnimationStart(Animation animation) {
		// TODO Auto-generated method stub
		
	}
}
