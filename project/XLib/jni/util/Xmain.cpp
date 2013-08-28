#include <stdio.h>
#include "XDateTime.h"
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include "XLog.h"

using namespace std;

int main()
{
	XDate cur_date = XDate::CurrentDate();
	XDate tmp_date = cur_date.AddDays(18);
	
	tmp_date = XDate::FromString("2013/4/5", "yyyy/M/d");

	int year, month, day;
	char* buf = "2013-07-12";
	sscanf(buf, "%d-%d-%d", &year, &month, &day);

			
	printf("%04d-%02d-%02d\n", 33, 1, 2); 
	printf("it is ok \n");

	OUT_ERROR_LOG("Hello:%d,%s\n", 23, "baby");	
	OUT_DEBUG_LOG("Hello:%d,%s\n", 50, "love");	

	TiXmlDocument *myDocument = new TiXmlDocument("test.xml");
    myDocument->LoadFile();
    
    //获得根元素，即Persons。
    TiXmlElement *RootElement = myDocument->RootElement();

    //输出根元素名称，即输出Persons。
    cout << RootElement->Value() << endl;
    
    //获得第一个Person节点。
    TiXmlElement *FirstPerson = RootElement->FirstChildElement();
    //输出接点名Person

    cout << FirstPerson->Value() << endl;
    //获得第一个Person的name节点和age节点和ID属性。
    TiXmlElement *NameElement = FirstPerson->FirstChildElement();
    TiXmlElement *AgeElement = NameElement->NextSiblingElement();
    TiXmlAttribute *IDAttribute = FirstPerson->FirstAttribute();
    
    //输出第一个Person的name内容，即周星星；age内容，即20；ID属性，即1。
    cout << NameElement->FirstChild()->Value() << endl;
    cout << AgeElement->FirstChild()->Value() << endl;
    cout << IDAttribute->Value() << endl;
	return 0;
}
