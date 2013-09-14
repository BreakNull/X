package x.core.ui;

import android.os.Handler;
import android.os.Message;
import android.os.SystemClock;
import android.util.Log;
import android.view.animation.*;
import android.view.animation.Animation.AnimationListener;
import android.widget.ViewFlipper;

public class JAnimHelper {
	private static Animation in, out;
	private static AnimListener al = new AnimListener();
	
	private static void createAnim(int animType) {
		final int T = Animation.RELATIVE_TO_SELF;
		final int M = 500;
		int mask = AnimType.getMask(animType);
		in = null;
		out = null;
		
		if ((mask & AnimType.MASK_LEFT_IN) != 0) {
			in = new TranslateAnimation(T, -1, T, 0, T, 0, T, 0);
			in.setDuration(M);
		}
		if ((mask & AnimType.MASK_LEFT_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, -1, T, 0, T, 0);
			out.setDuration(M);
		}
		if ((mask & AnimType.MASK_RIGHT_IN) != 0) {
			in = new TranslateAnimation(T, 1, T, 0, T, 0, T, 0);
			in.setDuration(M);
		}
		if ((mask & AnimType.MASK_RIGHT_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 1.0f, T, 0, T, 0);
			out.setDuration(M);
		}
		if ((mask & AnimType.MASK_TOP_IN) != 0) {
			in = new TranslateAnimation(T, 0, T, 0, T, -1, T, 0);
			in.setDuration(M);
		}
		if ((mask & AnimType.MASK_TOP_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, -1);
			out.setDuration(M);
		}
		if ((mask & AnimType.MASK_BOTTOM_IN) != 0) {
			in = new TranslateAnimation(T, 0, T, 0, T, 1, T, 0);
			in.setDuration(M);
		}
		if ((mask & AnimType.MASK_BOTTOM_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, 1);
			out.setDuration(M);
		}
	}
	
	public static void installAnim(JPageMgr mgr, ViewFlipper flip, int animType) {
		createAnim(animType);
		flip.setInAnimation(in);
		flip.setOutAnimation(out);
		al.reset();
		if (in != null) {
			in.setAnimationListener(al);
			al.incAnimCount();
		}
		if (out != null) {
			out.setAnimationListener(al);
			al.incAnimCount();
		}
		if (in != null || out != null) {
			JPageMgr.instance().lockScreen(true);
		}
	}
	
	private static class AnimListener implements AnimationListener {
		private int animCount;
		
		public void reset() {
			animCount = 0;
		}
		
		public void incAnimCount() {
			++animCount;
		}
		
		public void onAnimationEnd(Animation animation) {
			--animCount;
			if (animCount == 0) {
				//after 50ms, unlock the screen
				Handler hd = UiThread.getHandler();
				long time = SystemClock.uptimeMillis() + 50;
				hd.sendEmptyMessageAtTime(UiThread.MSG_UNLOCK_SCREEN, time);
			}
		}

		@Override
		public void onAnimationRepeat(Animation animation) {
		}

		@Override
		public void onAnimationStart(Animation animation) {
		}
    }
}
