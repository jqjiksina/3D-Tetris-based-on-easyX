#pragma once
#include "ObjectBase.h"

/////////summry//////////
// by 光电2215 ##--##
//class Button,inherited by class ObjectBase
//属性：
// 1.按钮位置、按钮框的颜色
// 2.文本的字体、颜色、大小、内容
// 3.是否开启消息监听
// 行为:
// 1.按钮的显示
// 2.按钮的凹陷特效
// 3.开启消息监听
// 4.关闭消息监听
// 5.消息处理
// 6.将文本类型从string转换为
// 
// 
// 7.判断鼠标点击时是否处于框内
///////

//按钮类的封装
class Button :public ObjectBase
{
public:
	void clicked();//点击特效

	Button();//默认初始化
	Button(ObjectBase* parent);
	Button(const RECT& r, const string& text);//用户自定义按钮位置与显示文本

	void captureMessage() override;//消息处理(暂时无用)
};

