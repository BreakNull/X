package x.core.jni;

/**
 * 所有与C++传递数据的类，都需要实现下面的两个函数， 同时必需是static的
 * 
 *
 */
public interface JObj {
	
	/*
	 * 返回域，格式：
	 *  {(fieldName, sig, info), (...),...}
	 *  info格式：   "S"表示静态域    "N"表示非静态域 , 不区分大小写的
	 */
	String[] getFields();
	
	/*
	 * 参照getFields()
	 */
	String[] getMethods();
}
