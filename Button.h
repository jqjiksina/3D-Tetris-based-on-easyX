#pragma once
#include "ObjectBase.h"

/////////summry//////////
// by ���2215 ##--##
//class Button,inherited by class ObjectBase
//���ԣ�
// 1.��ťλ�á���ť�����ɫ
// 2.�ı������塢��ɫ����С������
// 3.�Ƿ�����Ϣ����
// ��Ϊ:
// 1.��ť����ʾ
// 2.��ť�İ�����Ч
// 3.������Ϣ����
// 4.�ر���Ϣ����
// 5.��Ϣ����
// 6.���ı����ʹ�stringת��Ϊ
// 
// 
// 7.�ж������ʱ�Ƿ��ڿ���
///////

//��ť��ķ�װ
class Button :public ObjectBase
{
public:
	void clicked();//�����Ч

	Button();//Ĭ�ϳ�ʼ��
	Button(ObjectBase* parent);
	Button(const RECT& r, const string& text);//�û��Զ��尴ťλ������ʾ�ı�

	void captureMessage() override;//��Ϣ����(��ʱ����)
};

