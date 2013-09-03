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
	private static int curId = 0;
	
	private static final int S_NO_TITLE = (1 << 0);
	private static final int S_FULL_SCREEN = (1 << 1);
	
	private native int GetStyle(int id);
	private native void OnNew(String pageName, int id);
	private native Object OnCreate(int id);
	private native void OnDestroy(int id);
	private native void OnStart(int id);
	private native void OnStop(int id);
	
	private native void OnClick(int id, String widgetId);
	private native void OnTimeChanged(int id, String widgetId, int hourOfDay, int minute);
	private native void OnDateChanged(int id, String widgetId, int y, int m, int d);
	
	private native boolean OnCreateOptionsMenu(int id, Object menu);
	private native void OnOptionsItemSelected(int id, int menuId);
	
	public JPage() {
		Intent it = this.getIntent();
		name = it.getStringExtra("pagename");
		id = ++curId;
		OnNew(name, id);
	}
	
	public JPage(String pageName) {
		name = pageName;
		id = ++curId;
		OnNew(name, id);
	}
	
	public int getId() {
		return id;
	}
	
	public String getName() {
		return name;
	}
	
	public static int getNextId() {
		return curId + 1;
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
	
	public static String[] getFields() {
		return null;
	}
	
	public static String[] getMethods() {
		return null;
	}
	

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		View v = (View)OnCreate(id);
		applyStyle();
		LayoutParams params = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
		this.setContentView(v, params);
	}
	
	protected void onDestroy() {
		OnDestroy(id);
		super.onDestroy();
	}
	
	protected void onStart() {
		super.onStart();
		OnStart(id);
	}
	
	protected void onStop() {
		OnStop(id);
		super.onStop();
	}
	
	public boolean dispatchKeyEvent(KeyEvent ev){
		if (JPageMgr.instance().isKeyLocked() || JPageMgr.instance().isScreenLocked()) {
			return true;
		}
		return super.dispatchKeyEvent(ev);
	}
	
	public boolean dispatchTouchEvent(MotionEvent ev) {
		if (JPageMgr.instance().isTouchLocked() || JPageMgr.instance().isScreenLocked()) {
			return true;
		}
		return super.dispatchTouchEvent(ev);	
	}
	
	public boolean dispatchTrackballEvent(MotionEvent ev) {
		if (JPageMgr.instance().isScreenLocked()) {
			return true;
		}
		return super.dispatchTrackballEvent(ev);
	}
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (JPageMgr.instance().isKeyLocked() || JPageMgr.instance().isScreenLocked()) {
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			if (event.getRepeatCount() == 0) {
				JPageMgr.instance().goBack();
			}
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}
	
	public boolean onTouchEvent(MotionEvent event) {
		if (JPageMgr.instance().isTouchLocked() || JPageMgr.instance().isScreenLocked()) {
			return true;
		}
		return super.onTouchEvent(event);
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
}
