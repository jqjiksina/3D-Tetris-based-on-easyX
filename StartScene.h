#ifndef _START_SCENE_H
#define _START_SCENE_H

#include<stdio.h>
#include<easyx.h>
#include <string>
#include "MyData.h"
using namespace std;

extern class Tetris;

///////////summry/////////////////////
///by:���2215 ##--##
///������Ϸ���̵�һЩ�����ķ�װ
/// ��Ҫʵ���˽������ʾ����¼�ı���
/////////////////////////////////////

//��ʼ������ʾ,������Ϸ
int MainMenu(int(*func)(void));
//��ʼ��Ϸ
int gameStart();
//��Ϸ�����̺���
int Thread_Main(Tetris& tetris1, int*** arr);
//����������ʾ
int gameOver();
//��ͣ������ʾ
int pause();
//���ý���
int settings();
//��Ϸ˵��
int putInstructions();
//�����¼���ļ�
int save();
//��ȡ��¼���ļ�
int read();
//��ʾ��¼
int showRecord(int x, int y);
//ɾ����¼
int deleteRecord(int index);
//��ռ�¼
int emptyRecord();
//��ȡ��Ϸ����ʱ��/00:00:00
string getRunTime_R();
//��ȡ��Ϸʱ��/s
long getRunTime_Seconds();
//��ȡ��Ϸʱ��/ms
long long getRunTime_Millis();
//��ȡϵͳʱ��/00:00:00
string getRunTime_HMS();
#endif // !_START_SCENE_H

