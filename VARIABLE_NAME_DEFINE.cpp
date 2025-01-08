#pragma once
#include "MyData.h"
#include "CONSTANT_NAME_DEFINE.h"
#include "GameObject.h"

/////////////////���ڴ��ȫ�ֱ���////////////////////

int isBackgroundImageSet = 1;
int isPainting = 0;
int isCoordinateExit = 0;
int score = 0;
long startTime;
int record_amount;

//Settings
bool SoundEffectOn = true;
bool MusicOn = true;

//GameObject
int X_LENGTH = 6;
int Y_LENGTH = 6;
int difficulty = 1;//��Ϸ�Ѷ�
int INTER_TIME = 1000;//��������ʱ����
int SEED_NUM = 16;
int SURPRISE = 0;//�Ƿ�����ϲģʽ(����ģʽ)
int SURPRISE_TIME = 10000;//���õ��߳���ʱ����30s

 //int isPainting = 0;
 //int isCoordinateExit = 0;
 //int isBackgroundImageSet = 0;
 //int score = 0;
 //long startTime = 0;

//Datas
MyData cdata;//��ŵ�ǰ���ݣ����ڴ��
MyData datas[100];//��ȡ���������¼,ƪ������
Tetris t_t;
int*** t_a;

//�������
int RANDOM_STATE[36] = {
	_I_X_ORIENT,_I_Y_ORIENT,_I_Z_ORIENT,
	_TIAN,
	_Z_LAZY_STATE_1,_Z_LAZY_STATE_2,_Z_LAZY_STATE_3,_Z_LAZY_STATE_4,
	_L_LAZY_STATE_1,_L_LAZY_STATE_2,_L_LAZY_STATE_3,_L_LAZY_STATE_4,
	_T_LAZY_STATE_1,_T_LAZY_STATE_2,_T_LAZY_STATE_3,_T_LAZY_STATE_4,
	_Z_STATE_1,_Z_STATE_2,_Z_STATE_3,_Z_STATE_4,_Z_STATE_5,_Z_STATE_6,_Z_STATE_7,_Z_STATE_8,
	_L_STATE_1,_L_STATE_2,_L_STATE_3,_L_STATE_4,_L_STATE_5,_L_STATE_6,_L_STATE_7,_L_STATE_8,
	_T_STATE_1,_T_STATE_2,_T_STATE_3,_T_STATE_4
};
