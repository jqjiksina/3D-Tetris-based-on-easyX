#pragma once
#include "ObjectBase.h"

/// <summary>
/// by ���2215 ##--##
/// ������д�Ĵ����࣬�ݴ�ʵ��
/// </summary>

class Widget : public ObjectBase
{
public:
	IMAGE m_Image;//����ͼƬ

	void show() override;//��д,���������ñ���ͼƬ

	Widget();

};
