package x.core.ui;

import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;

public class AnimType {
	/**
	 * Anim type
	 * Note: anim type must pairs appear
	 */
	public static final int A_NONE = 0;
	public static final int A_LEFT_IN_RIGHT_OUT = 1;
	public static final int A_RIGHT_IN_LEFT_OUT = 2;
	public static final int A_BOTTOM_IN_TOP_OUT = 3;
	public static final int A_TOP_IN_BOTTOM_OUT = 4;
	
	
	//get the reverse anim's id
	public static int getReverseAnim(int an) {
		if (an == A_NONE) {
			return A_NONE;
		}
		if ((an % 2) == 0) {
			return an - 1;
		}
		return an + 1;
	}
	
	public static Animation createInAnim(int animType) {
		final int T = Animation.RELATIVE_TO_SELF;
		final int M = 500;
		int mask = getMask(animType);
		TranslateAnimation in = null;
		
		if ((mask & AnimType.MASK_LEFT_IN) != 0) {
			in = new TranslateAnimation(T, -1, T, 0, T, 0, T, 0);
		}
		if ((mask & AnimType.MASK_RIGHT_IN) != 0) {
			in = new TranslateAnimation(T, 1, T, 0, T, 0, T, 0);
		}
		if ((mask & AnimType.MASK_TOP_IN) != 0) {
			in = new TranslateAnimation(T, 0, T, 0, T, -1, T, 0);
		}
		if ((mask & AnimType.MASK_BOTTOM_IN) != 0) {
			in = new TranslateAnimation(T, 0, T, 0, T, 1, T, 0);
		}
		if (in != null) {
			in.setDuration(M);
		}
		return in;
	}
	
	public static Animation createOutAnim(int animType) {
		final int T = Animation.RELATIVE_TO_SELF;
		final int M = 500;
		int mask = getMask(animType);
		TranslateAnimation out = null;
		
		if ((mask & AnimType.MASK_LEFT_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, -1, T, 0, T, 0);
		}
		if ((mask & AnimType.MASK_RIGHT_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 1, T, 0, T, 0);
		}
		if ((mask & AnimType.MASK_TOP_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, -1);
		}
		if ((mask & AnimType.MASK_BOTTOM_OUT) != 0) {
			out = new TranslateAnimation(T, 0, T, 0, T, 0, T, 1);
		}
		if (out != null) {
			out.setDuration(M);
		}
		return out;
	}
	
	private static final int getMask(int anType) {
		switch (anType) {
		case A_LEFT_IN_RIGHT_OUT:
			return MASK_LEFT_IN|MASK_RIGHT_OUT;
		case A_RIGHT_IN_LEFT_OUT:
			return MASK_RIGHT_IN|MASK_LEFT_OUT;
		case A_BOTTOM_IN_TOP_OUT:
			return MASK_BOTTOM_IN|MASK_TOP_OUT;
		case A_TOP_IN_BOTTOM_OUT:
			return MASK_TOP_IN|MASK_BOTTOM_OUT;
		default:
			return A_NONE;
		}
	}
	
	//----------anim mask-----------------
	private static final int MASK_LEFT_IN = 1;
	private static final int MASK_LEFT_OUT = 2;
	private static final int MASK_RIGHT_IN = 4;
	private static final int MASK_RIGHT_OUT = 8;
	private static final int MASK_TOP_IN = 16;
	private static final int MASK_TOP_OUT = 32;
	private static final int MASK_BOTTOM_IN = 64;
	private static final int MASK_BOTTOM_OUT = 128;
}
