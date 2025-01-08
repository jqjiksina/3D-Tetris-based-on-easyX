#pragma once
#include "ObjectBase.h"

/// <summary>
/// by 光电2215 ##--##
/// 随随便便写的窗口类，暂待实现
/// </summary>

class Widget : public ObjectBase
{
public:
	IMAGE m_Image;//背景图片

	void show() override;//重写,窗口类设置背景图片

	Widget();

};
