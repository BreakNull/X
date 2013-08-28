package x.core.ui;

public class UiThreadRunnable implements Runnable {
	private long params1;
	private long params2;
	
	private native static void Run(long params1, long params2);
	
	public UiThreadRunnable(long params1, long params2) {
		this.params1 = params1;
		this.params2 = params2;
	}
	
	public void run() {
		Run(params1, params2);
	}
}
