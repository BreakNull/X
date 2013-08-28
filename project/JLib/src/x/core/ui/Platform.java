package x.core.ui;

import java.lang.reflect.Field;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;
import android.app.*;

public class Platform {
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
    	/*
    	View v = (View)obj;
    	if (v == null || r == null)
    		return;
    	Class<drawable> c = R.drawable.class;
    	try {
			Field f = c.getField(r);
			int val = f.getInt(null);
			v.setBackgroundResource(val);
		} catch (Exception e) {
			e.printStackTrace();
		}
		*/
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
    
    public static void addChild(Object obj, Object obj2, int idx) {
		if (obj != null && obj2 != null) {
    		ViewGroup vg = (ViewGroup)obj;
    		View v = (View)obj2;
    		if (idx < 0)
    			vg.addView(v);
    		else
    			vg.addView(v, idx);
    	}
    }
    
    
    public static String[] getFields() {
    	return null;
    }
    
    public static String[] getMethods() {
    	return new String[] {
    			"newButton", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			"newLabel", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			"newLineLayout", "(Landroid/content/Context;)Ljava/lang/Object;", "S",
    			
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
    			"setButtonText", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"getButtonText", "(Ljava/lang/Object;)Ljava/lang/String;", "S",
    			"setTitle", "(Ljava/lang/Object;Ljava/lang/String;)V", "S",
    			"setOrientation", "(Ljava/lang/Object;Z)V", "S",
    			"addChild", "(Ljava/lang/Object;Ljava/lang/Object;I)V", "S"
    	};
    }
}
