package x.core.ui;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.view.ViewGroup.LayoutParams;
import android.widget.*;;

public class JPage extends Activity implements View.OnClickListener,
		DatePicker.OnDateChangedListener, TimePicker.OnTimeChangedListener {
	protected int id;
	protected String name;
	protected static int curId = 0;
	
	protected native void OnNew(String pageName, int id);
	protected native Object OnCreate(int id);
	protected native Object OnReload(int id);
	protected native void OnDestroy(int id);
	protected native void OnStart(int id);
	protected native void OnStop(int id);
	protected native void OnBackPressed(int id);
	protected native int GetStyle(int id);
	
	protected native void OnClick(int id, String widgetId);
	protected native void OnTimeChanged(int id, String widgetId, int hourOfDay, int minute);
	protected native void OnDateChanged(int id, String widgetId, int y, int m, int d);
	
	protected native boolean OnCreateOptionsMenu(int id, Object menu);
	protected native void OnOptionsItemSelected(int id, int menuId);
	
	private static final int S_NO_TITLE = (1 << 0);
	private static final int S_FULL_SCREEN = (1 << 1);
	protected boolean exists;
	
	public JPage() {
		Intent it = JPageMgr.getIntent();
		name = it.getStringExtra("_page_name_");
		String strId = it.getStringExtra("_page_id_");
		Log.d("X", "JPage2() name='" + name+"' strId="+strId);
		
		if (strId != null) {
			id = Integer.parseInt(strId);
			exists = true;
		} else {
			exists = false;
			id = ++curId;
			OnNew(name, id);
		}
	}
	
	public JPage(String name) {
		Log.d("X", "JPage2('" + name + "')");
		this.name = name;
		id = ++curId;
		OnNew(name, id);
	}
	
	private void applyStyle() {
		int style = GetStyle(id);
		if ((style & S_NO_TITLE) != 0) {
			this.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
		}
		if ((style & S_FULL_SCREEN) != 0) {
			getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN); 
		} else {
			WindowManager.LayoutParams attrs = getWindow().getAttributes(); 
			attrs.flags &= (~WindowManager.LayoutParams.FLAG_FULLSCREEN); 
			getWindow().setAttributes(attrs); 
			getWindow().clearFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS); 
		}
	}

	protected void onCreate(Bundle savedInstanceState) {
		Log.d("X", "onCreate() "+this);
		super.onCreate(savedInstanceState);
		View v = null;
		if (exists) {
			v = (View)OnReload(id);
		} else {
			v = (View)OnCreate(id);
		}
		applyStyle();
		LayoutParams params = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
		this.setContentView(v, params);
	}
	
	protected void onDestroy() {
		Log.d("X", "onDestroy() "+this);
		//Note: can't call OnDestroy
		//OnDestroy(id);
		//only used for clear its content view
		setContentView(new View(this));
		super.onDestroy();		
		JPageMgr.SetChagingPage(false);
	}
	
	protected void onStart() {
		Log.d("X", "onStart() "+this);
		super.onStart();
		OnStart(id);
	}
	
	protected void onStop() {
		Log.d("X", "onStop() "+this);
		OnStop(id);
		super.onStop();
	}
	
	protected void onResume() {
		Log.d("X", "onResume() "+this);
		super.onResume();
	}
	
	protected void onPause() {
		Log.d("X", "onPause() "+this);
		super.onPause();
	}
	
	public boolean dispatchKeyEvent(KeyEvent ev) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		return super.dispatchKeyEvent(ev);
	}
	
	public boolean dispatchTouchEvent(MotionEvent ev) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		return super.dispatchTouchEvent(ev);	
	}
	
	public boolean dispatchTrackballEvent(MotionEvent ev) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		return super.dispatchTrackballEvent(ev);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			if (event.getRepeatCount() == 0 && event.getAction() == KeyEvent.ACTION_DOWN) {
				OnBackPressed(id);
			}
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}
	
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			return true;
		}
		return super.onKeyUp(keyCode, event);
	}
	
	public boolean onTouchEvent(MotionEvent event) {
		if (JPageMgr.isScreenLocked() || JPageMgr.isChagingPage()) {
			return true;
		}
		return super.onTouchEvent(event);
	}
	
	/**
	 * 设置事件监听器
	 * @param name 事件名称 
	 */
	public void setListener(Object vd, String name) {
		View v = (View)vd;
		if ((v == null) || (name == null)) {
			Log.e("X", "JPage.setListner widget=" + v + ", name="+name + ", page id="+id);
			return;
		}
		String[] sl = name.split("\\|");
		for (int i = 0; sl != null && i < sl.length; ++i) {
			if (sl[i].trim().equals("click")) {
				v.setOnClickListener(this);
			}
		}
	}
	
	public void clearListener(Object vd, String name) {
		View v = (View)vd;
		if ((v == null) || (name == null)) {
			Log.e("X", "JPage.clearListener widget=" + v + ", name="+name + ", page id="+id);
			return;
		}
		String[] sl = name.split("\\|");
		for (int i = 0; sl != null && i < sl.length; ++i) {
			if (sl[i].trim().equals("click")) {
				v.setOnClickListener(null);
			}
		}
	}
	
	protected String getWidgetId(View v) {
		if (v.getTag() == null) {
			return null;
		}
		return v.getTag().toString();
	}
	
	public boolean onCreateOptionsMenu(Menu m) {
		super.onCreateOptionsMenu(m);
		return OnCreateOptionsMenu(id, m);
	}
	
	public boolean onOptionsItemSelected(MenuItem mi) {
		OnOptionsItemSelected(id, mi.getItemId());
		return super.onOptionsItemSelected(mi);
	}

	@Override
	public void onClick(View v) {
		//Log.d("X", "JPage.onClick widget id=" + getWidgetId(v));
		OnClick(id, getWidgetId(v));
	}
	
	@Override
	public void onTimeChanged(TimePicker view, int hourOfDay, int minute) {
		OnTimeChanged(id, getWidgetId(view), hourOfDay, minute);
	}
	
	@Override
	public void onDateChanged(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
		OnDateChanged(id, getWidgetId(view), year, monthOfYear, dayOfMonth);
	}
	
	public String toString() {
		return super.toString() + ", name=" + name + ", id=" + id;
	}
}
