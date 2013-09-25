package x.core.ui;

import android.os.Bundle;
import android.util.Log;

public class JEntryPage extends JPage {
	private native static void CopyOmlDbFile();
	
	public JEntryPage() {
		super(JApplication.instance().getEntryPageName());
	}
	
	protected void onCreate(Bundle savedInstanceState) {
		CopyOmlDbFile();
		super.onCreate(savedInstanceState);
	}
}
