#include "Widget.h"
#include "CONSTANT_NAME_DEFINE.h"

void Widget::show()
{
	setbkcolor(this->m_Color_bk);
	setfillcolor(this->m_Color_rect);
	fillrectangle(this->m_Rect.left, this->m_Rect.top, this->m_Rect.right, this->m_Rect.bottom);
	settextstyle(this->m_Height_text, 0, toLPCTSTR(this->m_Font));
	settextcolor(this->m_Color_text);
	RECT r = this->m_Rect;
	r.top += 5;
	drawtext(toLPCTSTR(this->m_Text), &r,DT_TOP|DT_CENTER);//窗口标题文本居上
	FlushBatchDraw();
}

Widget::Widget()
{
	this->flag_Message = 0;
	this->m_Text = "Widget";
	LOGFONT ft, * font = &ft;
	gettextstyle(font);
	this->m_Height_text = font->lfHeight;

	this->m_Color_bk = getbkcolor();
	this->m_Color_rect = getfillcolor();
	this->m_Color_text = gettextcolor();
	this->m_Font = font->lfFaceName;
	RECT r = { 300,100,WINDOW_WIDTH -300,WINDOW_HEIGHT -100 };
	this->m_Rect = r;
}
