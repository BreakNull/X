package x.core.ui;

import android.view.animation.*;
import android.view.animation.Animation.AnimationListener;
import android.widget.ViewFlipper;

public class JAnimHelper {
	private static Animation in, out;
	private static AnimListener al = new AnimListener();
	
	public static interface AnimType {
		public static int S_NONE = 0;
		public static int S_IN_LEFT = 1;
		public static int S_IN_RIGHT = 2;
		public static int S_IN_BOTTOM = 3;
		public static int S_IN_TOP = 4;
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
}
