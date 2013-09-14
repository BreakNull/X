package x.core.ui;

public class AnimType {
	//----------anim mask-----------------
	public static final int MASK_LEFT_IN = 1;
	public static final int MASK_LEFT_OUT = 2;
	public static final int MASK_RIGHT_IN = 4;
	public static final int MASK_RIGHT_OUT = 8;
	public static final int MASK_TOP_IN = 16;
	public static final int MASK_TOP_OUT = 32;
	public static final int MASK_BOTTOM_IN = 64;
	public static final int MASK_BOTTOM_OUT = 128;
	
	//----------anim type----------------------
	public static final int A_NONE = 0;
	public static final int A_LEFT_IN_RIGHT_OUT = 1;
	public static final int A_RIGHT_IN_LEFT_OUT = 2;
	public static final int A_BOTTOM_IN_TOP_OUT = 3;
	public static final int A_TOP_IN_BOTTOM_OUT = 4;
	
	
	public static final int getMask(int anType) {
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
	
	//get the reverse anim's id
	public static int getReverseAnim(int an) {
		switch (an) {
		case A_LEFT_IN_RIGHT_OUT:
			return A_RIGHT_IN_LEFT_OUT;
		case A_RIGHT_IN_LEFT_OUT:
			return A_LEFT_IN_RIGHT_OUT;
		case A_BOTTOM_IN_TOP_OUT:
			return A_TOP_IN_BOTTOM_OUT;
		case A_TOP_IN_BOTTOM_OUT:
			return A_BOTTOM_IN_TOP_OUT;
		default:
			return A_NONE;
		}
	}
}
