package x.core.widget;

import android.content.Context;
import android.view.MotionEvent;
import android.widget.ImageButton;

public class ImgButton extends ImageButton {
	private int downResId = -1;
	private int defaultResId = -1;

	public ImgButton(Context context) {
		super(context);
	}
	
	public void setPressedResId(int id) {
		downResId = id;
	}
	
	public void setDefaultResId(int id) {
		defaultResId = id;
		setImageResource(defaultResId);
		setBackgroundResource(0);
	}

	public boolean onTouchEvent(MotionEvent evt) {
		if (evt.getAction() == MotionEvent.ACTION_DOWN) {
			if (downResId != -1) {
				this.setImageResource(downResId);
			}
		} else if (evt.getAction() == MotionEvent.ACTION_CANCEL ||
				evt.getAction() == MotionEvent.ACTION_OUTSIDE ||
				evt.getAction() == MotionEvent.ACTION_UP) {
			if (defaultResId != -1) {
				this.setImageResource(defaultResId);
			}
		}
		return super.onTouchEvent(evt);
	}
}
