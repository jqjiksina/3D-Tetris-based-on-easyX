#include "ObjectBase.h"
#include <graphics.h>
#include <thread>
#include "CONSTANT_NAME_DEFINE.h"

ObjectBase::ObjectBase()
{
	/*this->parent = NULL;
	ChildrenList* clist = new ChildrenList();
	this->m_ChidrenList = *clist;
	this->m_ChidrenList = ChildrenList();*/
	this->flag_Message = 0;
}

ObjectBase::~ObjectBase()
{
	this->flag_Message = 0;
}

void ObjectBase::show()
{
	/*if (this->parent != NULL)
	{
		this->parent->show();
	}*/
	setbkcolor(this->m_Color_bk);
	setfillcolor(this->m_Color_rect);
	fillrectangle(this->m_Rect.left, this->m_Rect.top, this->m_Rect.right, this->m_Rect.bottom);
	settextstyle(this->m_Height_text, 0, toLPCTSTR(this->m_Font));
	settextcolor(this->m_Color_text);
	RECT r = this->m_Rect;
	r.top += 5;
	drawtext(toLPCTSTR(this->m_Text), &r, DT_CENTER);
	FlushBatchDraw();
}

void ObjectBase::show(int)
{
	/*if (this->parent != NULL)
	{
		this->parent->show(0);
	}*/
	setbkcolor(this->m_Color_bk);
	setfillcolor(this->m_Color_rect);
	fillrectangle(this->m_Rect.left, this->m_Rect.top, this->m_Rect.right, this->m_Rect.bottom);
	settextstyle(this->m_Height_text, 0, toLPCTSTR(this->m_Font));
	settextcolor(this->m_Color_text);
	RECT r = this->m_Rect;
	r.top += 5;
	drawtext(toLPCTSTR(this->m_Text), &r, DT_CENTER);
	//FlushBatchDraw();
}

void ObjectBase::hide()
{
	int color = getbkcolor();
	setfillcolor(color);
	fillrectangle(this->m_Rect.left, this->m_Rect.top, this->m_Rect.right, this->m_Rect.bottom);
}

LPCTSTR ObjectBase::toLPCTSTR(const string& text)
{
	LPCTSTR str = (LPCTSTR)(text.c_str());
	return str;
}

bool ObjectBase::isIn(short x, short y)
{
	return (x > this->m_Rect.left && x < this->m_Rect.right&&
		y > this->m_Rect.top && y < this->m_Rect.bottom);
}

//监听事件
void ObjectBase::captureMessage()
{
	ExMessage msg;
	string text;
	LPCTSTR str;
	while (this->flag_Message)
	{
		getmessage(&msg);
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case _A_KEY:
				text = "A";
				str = (LPCTSTR)(text.c_str());
				outtextxy(0, 20, str);
				break;
			case _W_KEY:
				text = "W";
				str = (LPCTSTR)(text.c_str());
				outtextxy(0, 20, str);
				break;
			case _S_KEY:
				text = "S";
				str = (LPCTSTR)(text.c_str());
				outtextxy(0, 20, str);
				break;
			case _D_KEY:
				text = "D";
				str = (LPCTSTR)(text.c_str());
				outtextxy(0, 20, str);
				break;
			}
		}
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			text = "                      ";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			text = "鼠标移动!";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			break;
		case WM_LBUTTONDOWN:
			text = "                      ";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			text = "鼠标左键按下!";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			break;
		case WM_RBUTTONDOWN:
			text = "                      ";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			text = "鼠标右键按下!";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			break;
		case WM_LBUTTONUP:
			text = "                      ";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			text = "鼠标左键松开!";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			break;
		case WM_RBUTTONUP:
			text = "                      ";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			text = "鼠标右键松开!";
			str = (LPCTSTR)(text.c_str());
			outtextxy(0, 20, str);
			break;
		}
		FlushBatchDraw();
	}
}

void ObjectBase::messageOn()
{
	this->flag_Message = 1;
	//string text = "消息循环已启动!";
	//LPCTSTR str = (LPCTSTR)(text.c_str());
	//outtextxy(0, 0, str);
	thread* th1;
	th1 = new thread(&ObjectBase::captureMessage, this);
}

void ObjectBase::messageOff()
{
	this->flag_Message = 0;
}

bool operator==(const ObjectBase& obj1, const ObjectBase& obj2)
{
	return(obj1.m_Rect.left == obj2.m_Rect.left && obj1.m_Rect.top == obj2.m_Rect.top &&
		obj1.m_Rect.right == obj2.m_Rect.right && obj1.m_Rect.bottom == obj2.m_Rect.bottom &&
		obj1.m_Text == obj2.m_Text);
}

bool operator!=(const ObjectBase& obj1, const ObjectBase& obj2)
{
	return!(obj1.m_Rect.left == obj2.m_Rect.left && obj1.m_Rect.top == obj2.m_Rect.top &&
		obj1.m_Rect.right == obj2.m_Rect.right && obj1.m_Rect.bottom == obj2.m_Rect.bottom &&
		obj1.m_Text == obj2.m_Text);
}