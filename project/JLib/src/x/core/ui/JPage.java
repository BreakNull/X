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
	private static boolean hasInit;
	
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
		if (!hasInit) {
			hasInit = true;
			UiThread.init();
		}
		Intent it = this.getIntent();
		name = it.getStringExtra("pagename");
		id = ++curId;
		Log.d("X", "JPage() name="+name + ", id="+id);
		OnNew(name, id);
	}
	
	public JPage(String pageName) {
		if (!hasInit) {
			hasInit = true;
			UiThread.init();
		}
		name = pageName;
		id = ++curId;
		Log.d("X", "JPage() name="+name + ", id="+id);
		OnNew(name, id);
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
		if ("click".equals(name)) {
			v.setOnClickListener(this);
		}
		//TODO:
	}
	
	public static String[] getFields() {
		return null;
	}
	
	public static String[] getMethods() {
		return new String[] {
			"setListener", "(Ljava/lang/Object;Ljava/lang/String;)V", "N"	
		};
	}
	

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		View v = (View)OnCreate(id);
		LayoutParams params = new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT);
		this.setContentView(v, params);
	}
	
	protected void onDestroy() {
		OnDestroy(id);
		super.onDestroy();
	}
	
	protected void onStart() {
		OnStart(id);
		super.onStart();
	}
	
	protected void onStop() {
		OnStop(id);
		super.onStop();
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
