package x.core.ui;

import java.lang.reflect.Field;

import android.util.Log;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;

public class AnimType {
	//----------anim-----------------
	public static final int A_NONE = 0;
	public static final int A_LEFT_IN = 	1 << 0;
	public static final int A_LEFT_OUT = 	1 << 1;
	public static final int A_RIGHT_IN = 	1 << 2;
	public static final int A_RIGHT_OUT = 	1 << 3;
	public static final int A_TOP_IN = 		1 << 4;
	public static final int A_TOP_OUT = 	1 << 5;
	public static final int A_BOTTOM_IN = 	1 << 6;
	public static final int A_BOTTOM_OUT = 	1 << 7;
	public static final int A_FADE_IN = 	1 << 8;
	public static final int A_FADE_OUT = 	1 << 9;
	
	
	//get the reverse anim's id
	public static int getReverseAnim(int animType) {
		if (animType == A_NONE) {
			return A_NONE;
		}
		int r = 0;
		for (int i = 0; i < 30; ++i) {
			if ((animType & (1 << i)) != 0) {
				r |= (i % 2) == 0 ? (1<<i+1) : (1<<i-1);
			}
		}
		return r;
	}
	
	private static int getRField(String name) {
		int i = 0;
		try {
			if (animClass == null) {
				Class r = JApplication.instance().getR();
				String an = r.getName() + "$anim";
				animClass = Class.forName(an);
			}
			Field f = animClass.getField(name);
			i = f.getInt(null);
		} catch (Exception e) {
			Log.e("X", "AnimType.getRField fail, name='" + name + "'");
			e.printStackTrace();
		}
		return i;
	}
	
	public static int getInAnim(int animType) {
		int i = 0;
		if ((animType & AnimType.A_LEFT_IN) != 0) {
			i = getRField("slide_in_left");
		}
		else if ((animType & AnimType.A_RIGHT_IN) != 0) {
			i = getRField("slide_in_right");
		}
		else if ((animType & AnimType.A_TOP_IN) != 0) {
			i = getRField("slide_in_top");
		}
		else if ((animType & AnimType.A_BOTTOM_IN) != 0) {
			i = getRField("slide_in_bottom");
		}
		else if ((animType & AnimType.A_FADE_IN) != 0) {
			i = android.R.anim.fade_in; 
		}
		return i;
	}
	
	public static int getOutAnim(int animType) {
		int i = 0;
		
		if ((animType & AnimType.A_LEFT_OUT) != 0) {
			i = getRField("slide_out_left");
		}
		else if ((animType & AnimType.A_RIGHT_OUT) != 0) {
			i = getRField("slide_out_right");
		}
		else if ((animType & AnimType.A_TOP_OUT) != 0) {
			i = getRField("slide_out_top");
		}
		else if ((animType & AnimType.A_BOTTOM_OUT) != 0) {
			i = getRField("slide_out_bottom");
		}
		else if ((animType & AnimType.A_FADE_OUT) != 0) {
			i = android.R.anim.fade_out; 
		}
		return i;
	}
	
	private static Class animClass; 
}
