package x.core.ui;

import java.lang.reflect.Field;

import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;
import android.app.*;

public class JPlatform {
	private static Class s_R;
	private static Class s_drawable = null;
	
	/**
	 * init the R class
	 */
	public static void init(Class r) {
		s_R = r;
	}
	
	private static int getRid(String rid) {
		try {
    		if (s_drawable == null) {
    			String d = s_R.getName() + "$drawable";
    			s_drawable = Class.forName(d);
    		}
    		
			Field f = s_drawable.getField(rid);
			int val = f.getInt(null);
			return val;
		} catch (Exception e) {
			Log.e("X", "Platform.setBgImg there is no image named '" + rid + "'");
		}
		return -1;
	}
	
	//----------------------New widgets-----------------------------
	
	public static Object newButton(Context c) {
		return new Button(c);
	}
	
	public static Object newLabel(Context c) {
		return new TextView(c);
	}
	
	public static Object newLineLayout(Context c) {
		return new LinearLayout(c);
	}
	
	public static Object newImageButton(Context c) {
		return new ImageButton(c);
	}
	
	//---------------------------------------------------------
	public static String getId(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		Object tag = v.getTag();
    		return (tag != null) ? tag.toString() : null;
    	}
    	return null;
    }
	
	public static void setId(Object obj, String id) {
		View v = (View)obj;
		if (null != v) {
			v.setTag(id);
		}
	}
    
    public static void setBgImg(Object obj, String r) {
    	View v = (View)obj;
    	if (v == null || r == null) {
    		return;
    	}
    	int rid = getRid(r);
    	if (rid != -1) {
    		v.setBackgroundResource(rid);
    	}
    }
    
    public static void setBgColor(Object obj, int color) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setBackgroundColor(color);
    	}
    }
    
    public static boolean isClickable(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.isClickable();
    	}
    	return false;
    }
    
    public static void setClickable(Object obj, boolean b) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setClickable(b);
    	}
    }
    
    public static boolean isFocusable(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.isFocusable();
    	}
    	return false;
    }
    
    public static void setFocusable(Object obj, boolean b) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setFocusable(b);
    	}
    }
    
    public static int getPaddingLeft(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getPaddingLeft();
    	}
    	return 0;
    }
    
    public static int getPaddingRight(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getPaddingRight();
    	}
    	return 0;
    }
    
    public static int getPaddingTop(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getPaddingTop();
    	}
    	return 0;
    }
    
    public static int getPaddingBottom(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getPaddingBottom();
    	}
    	return 0;
    }
    
    public static void setPadding(Object obj, int left, int top, int right, int bottom) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setPadding(left, top, right, bottom);
    	}
    }
    
    public static boolean isVisible(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getVisibility() == View.VISIBLE;
    	}
    	return false;
    }
    
    public static void setVisible(Object obj, boolean b) {
    	View v = (View)obj;
    	if (v != null) {
    		//注意，可能需要修改为 View.INVISIBLE
    		v.setVisibility(b ? View.VISIBLE : View.GONE);
    	}
    }
    
    public static void setMinWidth(Object obj, int w) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setMinimumWidth(w);
    	}
    }
    
    public static void setMinHeight(Object obj, int h) {
    	View v = (View)obj;
    	if (v != null) {
    		v.setMinimumWidth(h);
    	}
    }

    public static int getWidth(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getWidth();
    	}
    	return 0;
    }
    
    public static int getHeight(Object obj) {
    	View v = (View)obj;
    	if (v != null) {
    		return v.getHeight();
    	}
    	return 0;
    }
    
    public static int getChildCount(Object obj) {
    	ViewGroup v = (ViewGroup)obj;
    	if (v != null) {
    		return v.getChildCount();
    	}
    	return 0;
    }
    
    public static Object getChildAt(Object obj, int idx) {
    	ViewGroup v = (ViewGroup)obj;
    	if (v != null && idx >= 0 && idx < v.getChildCount()) {
    		return v.getChildAt(idx);
    	}
    	return null;
    }
    
    public static Object getChild(Object obj, String id) {
    	ViewGroup v = (ViewGroup)obj;
    	if (v == null || id == null) {
    		return null;
    	}
    	for (int i = 0; i < v.getChildCount(); ++i) {
			View vv = v.getChildAt(i);
			if (id.trim().equals(getId(vv))) {
				return vv;
			}
		}
    	return null;
    }
    
    private static Object findByIdHelp(String id, ViewGroup v) {
    	for (int i = 0; i < v.getChildCount(); ++i) {
			View vv = v.getChildAt(i);
			if (id.equals(getId(vv))) {
				return vv;
			} else if (vv instanceof ViewGroup) {
				return findById(id, (ViewGroup)vv);
			}
		}
    	return null;
    }
    
    public static Object findById(String id, Object obj) {
    	String sid = id;
    	if (id == null || id.trim().equals("") || obj == null) {
    		return null;
    	}
    	sid = id.trim();
    	ViewGroup v = (ViewGroup)obj;
    	if (sid.equals(getId(v))) {
    		return v;
    	}
    	return findByIdHelp(sid, v);
    }
    
    //--------------------------------------------------------------------
    public static void setButtonText(Object obj, String txt) {
		Button b = (Button)obj;
    	if (b != null) {
    		b.setText(txt);
    	}
    }
    
    public static String getButtonText(Object obj) {
    	Button b = (Button)obj;
    	if (b != null) {
    		return b.getText().toString();
    	}
    	return null;
    }
    
    public static void setLabelText(Object obj, String txt) {
		TextView b = (TextView)obj;
    	if (b != null) {
    		b.setText(txt);
    	}
    }
    
    public static void setTitle(Object obj, String txt) {
    	Activity a = (Activity)obj;
		if (a != null) {
			a.setTitle(txt);
		}
    }
    
    public static void setOrientation(Object obj, boolean b) {
		LinearLayout l = (LinearLayout)obj;
    	if (l != null) {
    		l.setOrientation(b ? LinearLayout.VERTICAL : LinearLayout.HORIZONTAL);
    	}
    }
    
    public static boolean addChild(Object obj, Object obj2, int idx) {
		if (obj != null && obj2 != null) {
    		ViewGroup vg = (ViewGroup)obj;
    		View v = (View)obj2;
    		if (idx < 0)
    			vg.addView(v);
    		else
    			vg.addView(v, idx);
    		return true;
    	}
		return false;
    }
    
    public static void setListener(Object obj1, Object obj2, String name) {
    	//Log.d("X", "Platform.setListener obj1=" + obj1 + ", obj2=" + obj2 + ",name=" + name);
    	JPage p = (JPage)obj1;
    	if (p != null) {
    		p.setListener(obj2, name);
    	}
    }
    
    public static void clearListener(Object obj1, Object obj2, String name) {
    	//Log.d("X", "Platform.setListener obj1=" + obj1 + ", obj2=" + obj2 + ",name=" + name);
    	JPage p = (JPage)obj1;
    	if (p != null) {
    		p.clearListener(obj2, name);
    	}
    }
    
    public static boolean post(long addr, long r2) {
		return UiThread.post(addr, r2);
	}
	
	public static boolean post2(long addr, long r2, int delayMs) {
		return UiThread.post2(addr, r2, delayMs);
	}
	
	public static void setImgButtonSrc(Object obj, String rid) {
		ImageButton b = (ImageButton)obj;
    	if (b != null) {
    		int r = getRid(rid);
        	if (r != -1) {
        		b.setImageResource(r);
        	}
    	}
	}
	
	public static void loadNewPage(String pageName, int inAnim, int outAnim) {
		JPageMgr.instance().loadNewPage(pageName, inAnim, outAnim);
	}
	
	public static void loadExistPage(String pageName, int inAnim, int outAnim) {
		JPageMgr.instance().loadExistPage(pageName, inAnim, outAnim);
	}
	
	public static void loadExistPage2(int pageId, int inAnim, int outAnim) {
		JPageMgr.instance().loadExistPage(pageId, inAnim, outAnim);
	}
	
	public static void goBack() {
		JPageMgr.instance().goBack();
	}
	
    public static String[] getFields() {
    	return null;
    }
    
    public static String[] getMethods() {
    	return new String[] {
    			"newButton", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			"newLabel", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			"newLineLayout", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			"newImageButton", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			
    			"getId", "(Ljava/lang/Object;)Ljava/lang/String;", "S",
    			"setId", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"setBgImg", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"setBgColor", "(Ljava/lang/Object;I)V", "S",
    			"isClickable", "(Ljava/lang/Object;)Z", "S",
    			"setClickable", "(Ljava/lang/Object;Z)V", "S",
    			"isFocusable", "(Ljava/lang/Object;)Z", "S",
    			"setFocusable", "(Ljava/lang/Object;Z)V", "S",
    			"getPaddingLeft", "(Ljava/lang/Object;)I", "S",
    			"getPaddingRight", "(Ljava/lang/Object;)I", "S",
    			"getPaddingTop", "(Ljava/lang/Object;)I", "S",
    			"getPaddingBottom", "(Ljava/lang/Object;)I", "S",
    			"setPadding", "(Ljava/lang/Object;IIII)V", "S",
    			"isVisible", "(Ljava/lang/Object;)Z", "S",
    			"setVisible", "(Ljava/lang/Object;Z)V", "S",
    			"setMinWidth", "(Ljava/lang/Object;I)V", "S",
    			"setMinHeight", "(Ljava/lang/Object;I)V", "S",
    			"getWidth", "(Ljava/lang/Object;)I", "S",
    			"getHeight", "(Ljava/lang/Object;)I", "S",
    			"getChildCount", "(Ljava/lang/Object;)I", "S",
    			"getChildAt", "(Ljava/lang/Object;I)Ljava/lang/Object;", "S",
    			"getChild", "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;", "S",
    			"findById", "(Ljava/lang/String;Ljava/lang/Object;)Ljava/lang/Object;", "S",
    			
    			"setButtonText", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"getButtonText", "(Ljava/lang/Object;)Ljava/lang/String;", "S",
    			"setLabelText", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"setTitle", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"setOrientation", "(Ljava/lang/Object;Z)V", "S",
    			"addChild", "(Ljava/lang/Object;Ljava/lang/Object;I)Z", "S",
    			"setListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"clearListener", "(Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"post", "(JJ)Z", "S",
    			"post2", "(JJI)Z", "S",
    			"setImgButtonSrc", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"loadNewPage", "(Ljava/lang/String;II)V", "S",
    			"loadExistPage", "(Ljava/lang/String;II)V", "S",
    			"loadExistPage2", "(III)V", "S",
    			"goBack", "()V", "S"
    	};
    }
}
