#ifndef _PAINT_H
#define _PAINT_H

#include <graphics.h>
#include "GameObject.h"
#include <string>
#include "CONSTANT_NAME_DEFINE.h"
using namespace std;

//////summry//////////////////////
// by 光电2215 ##--##
// 封装了一些用于画图的函数
// 主要分为底层函数与接口函数
// 底层函数将easyX的一些函数进行了封装。
// 接口函数将底层函数进行了统合，
// 以适用于主程序的调用逻辑
///////////////////////////////////

#pragma region 测试函数
int paint_Test();
int image_Test();
#pragma endregion

#pragma region 底层函数

//检测某层是否是否全满
int isLayerOverflowed(int*** arr, int z);
//检测满的层数
int* getOverflowedLayer(int*** arr);
//在二维平面上画出立方体的轴测图
int paint_Cube(int stx, int sty, int CubeColor = BRUSH_COLOR, int length = UNIT_LENGTH,int projectedFace = 0);
//画出边界框
int paint_Rect(int left, int up, int right, int down, int RectColor = RECT_COLOR);
//画出投影(平行四边形)
//int paint_Project_OnAxis(int x1, int y1, int x2, int y2, int x3, int y3);

#pragma endregion

#pragma region 接口函数
//每帧都需要调用的函数
int update(int*** arr, int score, Tetris& tetris, Tetris* pre_tetris = nullptr);
//输入的三维数组中的数字代表的颜色：1 = RED	2 = BLUE
int paint_Cube(int*** arr, int length = UNIT_LENGTH);
int paint_Tetris(Tetris& tetris);
//初始化窗口,并设置背景颜色和画笔颜色
int startPaint(int bkColor = BACKGROUND_COLOR, int penColor = PEN_COLOR);
//显示文字
int outtextxy(int x, int y, std::string text);
//显示一张图片
int showImage(LPCTSTR path);
//显示时间
int showTime(int x, int y);
int showRunTime(int x = WINDOW_WIDTH/2, int y = 0);
//显示分数
int showScore(int score);
//绘制坐标系
int paint_Coordinate();
//清空坐标系的内容
int clear_Coordinate();
#pragma endregion

//初始化立方体数组（默认全部元素为0,无色)
int*** init_CubeArr(int xLength = X_LENGTH, int yLength = Y_LENGTH, int zLength = Z_LENGTH);
void free_CubeArr(int***cubeArr,int xLength = X_LENGTH, int yLength = Y_LENGTH);
//随机生成立方体于顶部
int summonCube(int*** arr, int num = 1, int colorValue = _RED_VALUE);
//立方体数组整体下落一格(消除一层后调用)
int fall(int*** arr,int bottom = 0);
//某一点下落一格
int fall(int*** arr, int x, int y, int z);
//结束画画
int endPaint(int***arr= NULL);
#endif