#pragma once
#include <iostream>
using namespace std;

/// <summary>///////////
/// by 光电2215 ##--##
/// 封装了用于读取文件的特定行、
/// 删除特定行的一些函数
/// 主要实现了文件按行读写的功能
/// </summary>///////////

int ReadLineData(const char* fileName, int lineNum, char* data);
string CharToStr(const char* contentChar);
void DelLineData(const char* fileName, int lineNum);
void ModifyLineData(const char* fileName, int lineNum, char* lineData);