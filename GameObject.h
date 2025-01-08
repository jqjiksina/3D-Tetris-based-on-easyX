#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#ifndef _RED_VALUE
#define _RED_VALUE		1
#endif

#include "CONSTANT_NAME_DEFINE.h"

/// <summary>////////////////
/// by ���2215 ##--##
/// Class Tetris
/// ���ԣ�
/// 1.��ɫ
/// 2.���з��������
/// 3.���ķ��������
/// 4.�Ƿ��Ծ
/// 5.״̬����״
/// 
/// ��Ϊ:
/// 1.����״̬/��״
/// 2.��������������
/// 3.�Ƴ�����������
/// 4.��ȡ�߽�
/// 5.����
/// 6.��ת
/// 7.ͶӰ
/// 8.ˮƽ�ƶ�
/// </summary>/////////////

struct Tetris
{
	//����
	int m_Arr[3 * TERRIS_MAX_SIZE];//һ������˹�����������������������������
	int isActive;//�Ƿ��Ծ�ı�־
	int m_ColorValue;//��ɫ
	int m_State;//״̬
	int centreBlockPosition[3] = { 0,0,Z_LENGTH - 2 };//���ķ�������
	//��Ϊ
	Tetris();//Ĭ�ϳ�ʼ��ΪO�ͷ���
	Tetris(int position_x, int position_y, int state = _BAR_VERTICAL, int color = _RED_VALUE);//����������ĳ�ʼ��
	int setState(int state);//����״̬
	int addToCubeArr(int***arr);//��������������
	int removeFromCubeArr(int*** arr);//�Ƴ����������飬����ͶӰ���ƶ�����ת�������ж�
	int getBoard(int mode);//��ȡ�߽�
	int move(ExMessage &msg,int***arr);//�ж��Ƿ���ƶ������ɣ����ƶ�
	int canRotate(int***arr);//�жϿɷ���ת
	int rotate();//Ԥ��ת���������Ƿ����ת
	int rotate(int*** arr);//��ת
	int fall(int***arr);//����
	int project_OnAxis(int***arr);//ͶӰ������ϵ
	int project_OnCube(int*** arr);//ͶӰ������
	int project_OffCube(int*** arr);//��������ͶӰ
};

//�����ײ������Ĳ�,����������
int killLayer(int*** arr, int* overArr, int delayTime = 0);
//��ת����ϵ
int rotateAxis(int***& arr);

#endif