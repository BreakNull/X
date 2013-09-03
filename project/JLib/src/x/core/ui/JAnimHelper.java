package x.core.ui;

import java.lang.reflect.Field;
import java.util.*;

import android.util.Log;
import android.view.animation.*;
import android.widget.ViewFlipper;

/**
 * Note:
 * in和out必须成对出现，且in为奇数，out为偶数，且out = in + 1
 */
public class JAnimHelper {
	private static Map<Integer, Integer> anims = new HashMap<Integer,Integer>();
	private static Class s_R;
	private static Class s_Anim;
	
	public static int SLIDE_NONE = 0;
	public static int SLIDE_IN_BOTTOM = 1;
	public static int SLIDE_OUT_BOTTOM = 2;
	public static int SLIDE_IN_LEFT = 3;
	public static int SLIDE_OUT_LEFT = 4;
	public static int SLIDE_IN_RIGHT = 5;
	public static int SLIDE_OUT_RIGHT = 6;
	public static int SLIDE_IN_TOP = 7;
	public static int SLIDE_OUT_TOP = 8;
	
	public static void init(Class r) {
		Log.d("X", "JAnimHelper.init r="+r);
		s_R = r;
		try {
			anims.put(0, 0);
			s_Anim = Class.forName(s_R.getName() + "$anim");
			String[] names = {"slide_in_bottom", "slide_in_left", "slide_in_right", "slide_in_top", "slide_out_bottom", "slide_out_left", "slide_out_right", "slide_out_top"};
			for (int i = 0; i < names.length; ++i) {
				regist(i + 1, names[i]);
			}
		} catch (ClassNotFoundException e) {
			Log.e("X", "AnimHelper.init not find class anim in "+s_R.getName());
			//e.printStackTrace();
		}
	}
	
	public static void installAnim(JPageMgr mgr, ViewFlipper flip, int inAnim, int outAnim) {
		Integer in = null, out = null;
		try {
			in = anims.get(inAnim);
			out = anims.get(outAnim);
			if (in == null || out == null) {
				Log.d("X", "AnimHelper.installAnim not find in/out amin. in=" + in + ", out="+out);
			}
			int i = 0; //anims.get(SLIDE_IN_LEFT);
			int o = 0; //anims.get(SLIDE_OUT_LEFT);
			if (in != null && in.intValue() != 0) {
				i = in.intValue();
			}
			if (out != null && out.intValue() != 0) {
				o = out.intValue();
			}
			if (i != 0) {
				Animation a = AnimationUtils.loadAnimation(mgr, i);
				flip.setInAnimation(a);
			}
			if (o != 0) {
				Animation a = AnimationUtils.loadAnimation(mgr, o);
				flip.setOutAnimation(a);
			}
		} catch (Exception ex) {
			Log.e("X", "JAnimHelper.installAnim fail! in=" + in + ",out=" + in);
			//ex.printStackTrace();
		}
	}
	
	//get the reverse anim's id
	public static int getReverseAnim(int id) {
		if (id == 0) {
			return 0;
		}
		if ((id % 2) != 0) {
			return id + 1;
		}
		return id - 1;
	}
	
	private static void regist(int id, String name) {
		if (s_Anim == null) {
			Log.e("X", "AnimHelper.init R.anim is null");
			return;
		}
		try {
			Field f = s_Anim.getField(name);
			int v = f.getInt(null);
			anims.put(id, v);
		} catch (SecurityException e) {
			Log.e("X", "AnimHelper.regist can't access R.anim field "+ name);
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			Log.e("X", "AnimHelper.regist not find R.anim field "+ name);
			e.printStackTrace();
		} catch (Exception e) {
			Log.e("X", "AnimHelper.regist fail");
		}
	}
}
