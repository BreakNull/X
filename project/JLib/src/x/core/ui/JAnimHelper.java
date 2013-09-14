package x.core.ui;

import android.os.Handler;
import android.os.SystemClock;
import android.view.animation.*;
import android.view.animation.Animation.AnimationListener;
import android.widget.ViewFlipper;

public class JAnimHelper {
	private static AnimListener al = new AnimListener();
	
	public static void installAnim(JPageMgr mgr, ViewFlipper flip, int animType) {
		Animation in = AnimType.createInAnim(animType);
		Animation out = AnimType.createOutAnim(animType);;
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
