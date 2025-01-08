#ifndef _PAINT_H
#define _PAINT_H

#include <graphics.h>
#include "GameObject.h"
#include <string>
#include "CONSTANT_NAME_DEFINE.h"
using namespace std;

//////summry//////////////////////
// by ���2215 ##--##
// ��װ��һЩ���ڻ�ͼ�ĺ���
// ��Ҫ��Ϊ�ײ㺯����ӿں���
// �ײ㺯����easyX��һЩ���������˷�װ��
// �ӿں������ײ㺯��������ͳ�ϣ�
// ��������������ĵ����߼�
///////////////////////////////////

#pragma region ���Ժ���
int paint_Test();
int image_Test();
#pragma endregion

#pragma region �ײ㺯��

//���ĳ���Ƿ��Ƿ�ȫ��
int isLayerOverflowed(int*** arr, int z);
//������Ĳ���
int* getOverflowedLayer(int*** arr);
//�ڶ�άƽ���ϻ�������������ͼ
int paint_Cube(int stx, int sty, int CubeColor = BRUSH_COLOR, int length = UNIT_LENGTH,int projectedFace = 0);
//�����߽��
int paint_Rect(int left, int up, int right, int down, int RectColor = RECT_COLOR);
//����ͶӰ(ƽ���ı���)
//int paint_Project_OnAxis(int x1, int y1, int x2, int y2, int x3, int y3);

#pragma endregion

#pragma region �ӿں���
//ÿ֡����Ҫ���õĺ���
int update(int*** arr, int score, Tetris& tetris, Tetris* pre_tetris = nullptr);
//�������ά�����е����ִ������ɫ��1 = RED	2 = BLUE
int paint_Cube(int*** arr, int length = UNIT_LENGTH);
int paint_Tetris(Tetris& tetris);
//��ʼ������,�����ñ�����ɫ�ͻ�����ɫ
int startPaint(int bkColor = BACKGROUND_COLOR, int penColor = PEN_COLOR);
//��ʾ����
int outtextxy(int x, int y, std::string text);
//��ʾһ��ͼƬ
int showImage(LPCTSTR path);
//��ʾʱ��
int showTime(int x, int y);
int showRunTime(int x = WINDOW_WIDTH/2, int y = 0);
//��ʾ����
int showScore(int score);
//��������ϵ
int paint_Coordinate();
//�������ϵ������
int clear_Coordinate();
#pragma endregion

//��ʼ�����������飨Ĭ��ȫ��Ԫ��Ϊ0,��ɫ)
int*** init_CubeArr(int xLength = X_LENGTH, int yLength = Y_LENGTH, int zLength = Z_LENGTH);
void free_CubeArr(int***cubeArr,int xLength = X_LENGTH, int yLength = Y_LENGTH);
//��������������ڶ���
int summonCube(int*** arr, int num = 1, int colorValue = _RED_VALUE);
//������������������һ��(����һ������)
int fall(int*** arr,int bottom = 0);
//ĳһ������һ��
int fall(int*** arr, int x, int y, int z);
//��������
int endPaint(int***arr= NULL);
#endif