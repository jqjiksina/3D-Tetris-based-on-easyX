#include "Button.h"
#include <thread>
#include "CONSTANT_NAME_DEFINE.h"

//extern int flag_Message;

using namespace std;

Button::Button()
{
	/*this->parent = NULL;
	ChildrenList* clist = new ChildrenList();
	this->m_ChidrenList = *clist;*/
	this->flag_Message = 0;
	this->m_Text = "Button";
	LOGFONT ft,* font = &ft;
	gettextstyle(font);
	this->m_Height_text = font->lfHeight;
	
	this->m_Color_bk = getbkcolor();
	this->m_Color_rect = getfillcolor();
	this->m_Color_text = gettextcolor();
	this->m_Font = font->lfFaceName;
	RECT r = { WINDOW_WIDTH / 2-200,WINDOW_HEIGHT / 2-15,WINDOW_WIDTH / 2+200,WINDOW_HEIGHT / 2+15 };
	this->m_Rect = r;
}

Button::Button(ObjectBase* parent)
{
	/*this->parent = parent;
	ChildrenList* clist = new ChildrenList();
	this->m_ChidrenList = *clist;*/
	/*this->parent->m_ChidrenList.addNode(this);*/
	this->flag_Message = 0;
	this->m_Text = "Button";
	LOGFONT ft, * font = &ft;
	gettextstyle(font);
	this->m_Height_text = font->lfHeight;

	this->m_Color_bk = getbkcolor();
	this->m_Color_rect = getfillcolor();
	this->m_Color_text = gettextcolor();
	this->m_Font = font->lfFaceName;
	RECT r = { WINDOW_WIDTH / 2 - 200,WINDOW_HEIGHT / 2 - 15,WINDOW_WIDTH / 2 + 200,WINDOW_HEIGHT / 2 + 15 };
	this->m_Rect = r;
}

Button::Button(const RECT& r, const string& text)
{
	//this->parent = NULL;
	//ChildrenList* clist = new ChildrenList();
	//this->m_ChidrenList = *clist;
	this->flag_Message = 0;
	this->m_Text = text;
	LOGFONT ft, *font = &ft;
	gettextstyle(font);
	this->m_Height_text = font->lfHeight;
	this->m_Color_bk = getbkcolor();
	this->m_Color_rect = getfillcolor();
	this->m_Color_text = gettextcolor();
	this->m_Font = font->lfFaceName;
	this->m_Rect = r;

	//this->func_1 = NULL;
}


void Button::clicked()
{
	this->m_Rect.top += 5;
	this->m_Rect.bottom -= 5;
	this->show();
	Sleep(100);
	this->m_Rect.top -= 5;
	this->m_Rect.bottom += 5;
	this->show();
}

//监听事件
void Button::captureMessage()
{
	ExMessage msg;
	string text;
	LPCTSTR str;
	while (flag_Message)
	{
		getmessage(&msg);
		flushmessage();
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
		case WM_LBUTTONDOWN:
			//判断按钮是否按到
			if (this->isIn(msg.x, msg.y))
			{
				this->clicked();
				//this->func_1();
			}
			break;
		case WM_RBUTTONDOWN:
			break;
		case WM_LBUTTONUP:
			break;
		case WM_RBUTTONUP:
			break;
		}
		FlushBatchDraw();
	}
}