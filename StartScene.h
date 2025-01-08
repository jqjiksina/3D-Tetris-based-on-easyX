#ifndef _START_SCENE_H
#define _START_SCENE_H

#include<stdio.h>
#include<easyx.h>
#include <string>
#include "MyData.h"
using namespace std;

extern class Tetris;

///////////summry/////////////////////
///by:光电2215 ##--##
///控制游戏进程的一些函数的封装
/// 主要实现了界面的显示、记录的保存
/////////////////////////////////////

//开始界面显示,启动游戏
int MainMenu(int(*func)(void));
//开始游戏
int gameStart();
//游戏主进程函数
int Thread_Main(Tetris& tetris1, int*** arr);
//结束界面显示
int gameOver();
//暂停界面显示
int pause();
//设置界面
int settings();
//游戏说明
int putInstructions();
//保存记录至文件
int save();
//读取记录至文件
int read();
//显示记录
int showRecord(int x, int y);
//删除记录
int deleteRecord(int index);
//清空记录
int emptyRecord();
//获取游戏运行时间/00:00:00
string getRunTime_R();
//获取游戏时间/s
long getRunTime_Seconds();
//获取游戏时间/ms
long long getRunTime_Millis();
//获取系统时间/00:00:00
string getRunTime_HMS();
#endif // !_START_SCENE_H

