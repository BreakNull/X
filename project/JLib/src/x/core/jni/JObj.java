package x.core.jni;

/**
 * ������C++�������ݵ��࣬����Ҫʵ����������������� ͬʱ������static��
 * 
 *
 */
public interface JObj {
	
	/*
	 * �����򣬸�ʽ��
	 *  {(fieldName, sig, info), (...),...}
	 *  info��ʽ��   "S"��ʾ��̬��    "N"��ʾ�Ǿ�̬�� , �����ִ�Сд��
	 */
	String[] getFields();
	
	/*
	 * ����getFields()
	 */
	String[] getMethods();
}
