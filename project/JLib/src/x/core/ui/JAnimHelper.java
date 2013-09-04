package x.core.ui;

import java.lang.reflect.Field;
import java.util.*;
import android.util.Log;
import android.view.animation.*;
import android.view.animation.Animation.AnimationListener;
import android.widget.ViewFlipper;

public class JAnimHelper {
	private static int[] anims = new int[20];
	private static Class s_R;
	private static Class s_Anim;
	private static Animation in, out;
	private static AnimListener al = new AnimListener();
	
	public static interface AnimType {
		public static int S_NONE = 0;
		public static int S_IN_LEFT = 1;
		public static int S_IN_RIGHT = 2;
		public static int S_IN_BOTTOM = 3;
		public static int S_IN_TOP = 4;
	}
	
	public static void init(Class r) {
		s_R = r;
		try {
			s_Anim = Class.forName(s_R.getName() + "$anim");
			String[] names = {"slide_none", "slide_in_left", "slide_out_right", 
					"slide_in_right", "slide_out_left", "slide_in_top", 
					"slide_out_bottom", "slide_in_bottom", "slide_out_top"};
			for (int i = 0; i < names.length; ++i) {
				regist(i, names[i]);
			}
		} catch (ClassNotFoundException e) {
			Log.e("X", "AnimHelper.init not find class anim in "+s_R.getName());
			//e.printStackTrace();
		}
	}
	
	private static void createAnim(int animType) {
		final int T = Animation.RELATIVE_TO_SELF;
		final int M = 200;
		
		switch (animType) {
		case AnimType.S_IN_LEFT:
			in = new TranslateAnimation(T, -1, T, 0, T, 0, T, 0);
			in.setDuration(M);
			out = new TranslateAnimation(T, 0, T, 1.0f, T, 0, T, 0);
			out.setDuration(M);
			break;
		case AnimType.S_IN_RIGHT:
			in = new TranslateAnimation(T, 1, T, 0, T, 0, T, 0);
			in.setDuration(M);
			out = new TranslateAnimation(T, 0, T, -1, T, 0, T, 0);
			out.setDuration(M);
			break;
		case AnimType.S_IN_BOTTOM:
			in = new TranslateAnimation(T, 0, T, 0, T, 1, T, 0);
			in.setDuration(M);
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, -1);
			out.setDuration(M);
			break;
		case AnimType.S_IN_TOP:
			in = new TranslateAnimation(T, 0, T, 0, T, -1, T, 0);
			in.setDuration(M);
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, 1);
			out.setDuration(M);
			break;
		default:
			in = null;
			out = null;
			break;
		}
	}
	
	public static void installAnim(JPageMgr mgr, ViewFlipper flip, int animType) {
		createAnim(animType);
		flip.setInAnimation(in);
		flip.setOutAnimation(out);
		if (in != null) {
			in.setAnimationListener(al);
		}
		if (out != null) {
			out.setAnimationListener(al);
		}
	}
	
	//get the reverse anim's id
	public static int getReverseAnim(int an) {
		switch (an) {
		case AnimType.S_IN_LEFT:
			return AnimType.S_IN_RIGHT;
		case AnimType.S_IN_RIGHT:
			return AnimType.S_IN_LEFT;
		case AnimType.S_IN_BOTTOM:
			return AnimType.S_IN_TOP;
		case AnimType.S_IN_TOP:
			return AnimType.S_IN_BOTTOM;
		default:
			return AnimType.S_NONE;
		}
	}
	
	private static class AnimListener implements AnimationListener {
		
		public void increaseAnim() {
			JPageMgr.instance().lockScreen(true);
		}
		
		public void onAnimationEnd(Animation animation) {
			JPageMgr.instance().lockScreen(false);
		}

		@Override
		public void onAnimationRepeat(Animation animation) {
		}

		@Override
		public void onAnimationStart(Animation animation) {
			JPageMgr.instance().lockScreen(true);
		}
    }
	
	private static void regist(int id, String name) {
		if (s_Anim == null) {
			Log.e("X", "AnimHelper.init R.anim is null");
			return;
		}
		try {
			Field f = s_Anim.getField(name);
			int v = f.getInt(null);
			anims[id] = v;
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
