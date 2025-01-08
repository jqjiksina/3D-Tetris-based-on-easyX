#include "ReadLineData.h"
/********************************************************
Description:	�ļ���������ȡָ���У�ɾ��ָ���У��޸�ָ����
********************************************************/
#include <iostream>
#include <fstream>
#include <string>

int ReadLineData(const char* fileName, int lineNum, char* data)
{
	ifstream in;
	in.open(fileName);

	int line = 1;
	while (in.getline(data, 1024))
	{
		if (lineNum == line)
		{
			break;
		}
		if (in.peek()==EOF) return -1;
		line++;
	}

	in.close();
	return 1;
}

string CharToStr(char* contentChar)
{
	string tempStr;
	for (int i = 0; contentChar[i] != '\0'; i++)
	{
		tempStr += contentChar[i];
	}
	return tempStr;
}


void DelLineData(const char* fileName, int lineNum)
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char lineData[1024] = { 0 };
	while (in.getline(lineData, sizeof(lineData)))
	{
		if (line == lineNum)
		{
			strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(lineData);
			//strFileData += "\n";
		}
		line++;
	}
	in.close();

	//д���ļ�
	ofstream out;
	out.open(fileName);
	out.flush();
	out << strFileData;
	out.close();
}

void ModifyLineData(const char* fileName, int lineNum, char* lineData)
{
	ifstream in;
	in.open(fileName);

	string strFileData = "";
	int line = 1;
	char tmpLineData[1024] = { 0 };
	while (in.getline(tmpLineData, sizeof(tmpLineData)))
	{
		if (line == lineNum)
		{
			strFileData += CharToStr(lineData);
			strFileData += "\n";
		}
		else
		{
			strFileData += CharToStr(tmpLineData);
			strFileData += "\n";
		}
		line++;
	}
	in.close();

	//д���ļ�
	ofstream out;
	out.open(fileName);
	out.flush();
	out << strFileData;
	out.close();
}