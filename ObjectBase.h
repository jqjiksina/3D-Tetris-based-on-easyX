#pragma once
#include <iostream>
#include <string>
#include <graphics.h>
#include "ChildrenList.h"
using namespace std;

////////////summry/////////
// by ���2215 ##--##
//��Ҫ����ͷ�ļ�:graphics/easyX
//���ļ���װ�˺ܶ�ʵ�ÿؼ����ݴ���չ��
// Button
/////////////////////////////////

//��ť��ĸ���
class ObjectBase
{
public:
	//�ı�����
	struct
	{
		string m_Text;
		int m_Color_text;
		int m_Height_text;
		int m_Color_bk;
		string m_Font;
		
	};
	//��������
	struct
	{
		int m_Color_rect;
		RECT m_Rect;
	};
	//��Ϣ��������
	int flag_Message;
	////�洢�����ָ��
	//ObjectBase* parent;
	////�洢���������
	//ChildrenList m_ChidrenList;
	ObjectBase();
	//����ʱ��Ҫ�Ȱ�����������������Ӹ����������ɾ������
	~ObjectBase();
	virtual void show();
	void show(int);//��������ʾ���ȴ�FlushBatchDraw
	virtual void hide();
	virtual void messageOn();
	virtual void messageOff();
	virtual bool isIn(short, short);
	virtual void captureMessage();

	LPCTSTR toLPCTSTR(const string&);
};
bool operator==(const ObjectBase& obj1, const ObjectBase& obj2);
bool operator!=(const ObjectBase& obj1, const ObjectBase& obj2);