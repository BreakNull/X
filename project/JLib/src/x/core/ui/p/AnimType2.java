package x.core.ui.p;

import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;

public class AnimType2 {
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
	
	public static int getInAnim(int animType) {
		int i = 0;
		if ((animType & AnimType2.A_LEFT_IN) != 0) {
			i = android.R.anim.slide_in_left;
		}
		else if ((animType & AnimType2.A_RIGHT_IN) != 0) {
			i = 0;
		}
		else if ((animType & AnimType2.A_TOP_IN) != 0) {
			i = 0;
		}
		else if ((animType & AnimType2.A_BOTTOM_IN) != 0) {
			i = 0; 
		}
		else if ((animType & AnimType2.A_FADE_IN) != 0) {
			i = android.R.anim.fade_in; 
		}
		return i;
	}
	
	public static int getOutAnim(int animType) {
		int i = 0;
		
		if ((animType & AnimType2.A_LEFT_OUT) != 0) {
			
		}
		else if ((animType & AnimType2.A_RIGHT_OUT) != 0) {
			i = android.R.anim.slide_out_right;
		}
		else if ((animType & AnimType2.A_TOP_OUT) != 0) {
			
		}
		else if ((animType & AnimType2.A_BOTTOM_OUT) != 0) {
			
		}
		else if ((animType & AnimType2.A_FADE_OUT) != 0) {
			i = android.R.anim.fade_out; 
		}
		return i;
	}
}
