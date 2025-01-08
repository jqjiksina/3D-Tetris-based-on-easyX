#pragma once
#include <iostream>
#include <string>
#include <graphics.h>
#include "ChildrenList.h"
using namespace std;

////////////summry/////////
// by 光电2215 ##--##
//需要包含头文件:graphics/easyX
//该文件封装了很多实用控件（暂待拓展）
// Button
/////////////////////////////////

//按钮类的父类
class ObjectBase
{
public:
	//文本部分
	struct
	{
		string m_Text;
		int m_Color_text;
		int m_Height_text;
		int m_Color_bk;
		string m_Font;
		
	};
	//矩形区域
	struct
	{
		int m_Color_rect;
		RECT m_Rect;
	};
	//信息监听部分
	int flag_Message;
	////存储父类的指针
	//ObjectBase* parent;
	////存储子类的链表
	//ChildrenList m_ChidrenList;
	ObjectBase();
	//析构时，要先把子类对象析构，并从父类的链表中删除自身
	~ObjectBase();
	virtual void show();
	void show(int);//不立刻显示，等待FlushBatchDraw
	virtual void hide();
	virtual void messageOn();
	virtual void messageOff();
	virtual bool isIn(short, short);
	virtual void captureMessage();

	LPCTSTR toLPCTSTR(const string&);
};
bool operator==(const ObjectBase& obj1, const ObjectBase& obj2);
bool operator!=(const ObjectBase& obj1, const ObjectBase& obj2);