#pragma once
#include <iostream>
using namespace std;

/// <summary>///////////
/// by ���2215 ##--##
/// ��װ�����ڶ�ȡ�ļ����ض��С�
/// ɾ���ض��е�һЩ����
/// ��Ҫʵ�����ļ����ж�д�Ĺ���
/// </summary>///////////

int ReadLineData(const char* fileName, int lineNum, char* data);
string CharToStr(const char* contentChar);
void DelLineData(const char* fileName, int lineNum);
void ModifyLineData(const char* fileName, int lineNum, char* lineData);