#ifndef _TEST_HPP
#define _TEST_HPP
#include "GameObject.h"
#include "paint.h"
#include <conio.h>
#include <iostream>
#include "toString.h"
#include "StartScene.h"
#include <thread>
#include <time.h>
#include <fstream>
#include "ReadLineData.h"
#include "MyData.h"
#include "ObjectBase.h"
#include "Button.h"
#include "Widget.h"
#include "CONSTANT_NAME_DEFINE.h"
// ���� Windows Multimedia API,��������
#pragma comment(lib,"Winmm.lib")

///test.hpp����Ҫ�Ĳ��Ժ�����������Ҫ�����������ļ�����ʹ�á�
//�����ô���Ҫ�ǰ����ҵ���ÿһ��ģ���Ƿ���������

using namespace std;

int test01()
{
	initgraph(640, 480);
	isPainting = 1;
	outtextxy(0, 0, "����BeginBatchDraw����");
	BeginBatchDraw();

	setlinecolor(WHITE);
	setfillcolor(RED);

	for (int i = 50; i < 600; i++)
	{
		cleardevice();
		circle(i, 100, 40);
		floodfill(i, 100, WHITE);
		FlushBatchDraw();
		Sleep(10);
	}

	EndBatchDraw();
	outtextxy(0, 0, "��������˳�");
	getchar();
	endPaint();

	return 1;
}

//���Լ��̵�����
int test02()
{
	startPaint();
	outtextxy(0, 0, "���Լ�������");
	ExMessage message;
	
	while (1)
	{
		static int i;
		getmessage(&message);
		if (message.vkcode == 0x41)
			outtextxy(12*i++,20,"A");
		if (message.vkcode == 0x44)
		{
			outtextxy(12 * i++, 20, "D");
		}
		if (message.vkcode == 0x57)
		{
			outtextxy(12 * i++, 20, "W");
		}
		if (message.vkcode == 0x53)
		{
			outtextxy(12 * i++, 20, "S");
		}
		if (message.vkcode == 0x51)
		{
			outtextxy(0, 0, "Q");
			break;
		}
	}
	outtextxy(0, 0, "��������˳�");
	getchar();
	closegraph();
	
	return 1;
}

//���Ի�ȡϵͳʱ��
int test03()
{
	initgraph(1000,600);
	long st = clock();
	while (1)
	{
		outtextxy(0, 0, numToString(clock() - st));
	}

	_getch();
	return 1;
}

//��������������д�ĺ������
//��Ϸ�Բ��Ժ���(���)
int test04()
{
	//��ʼ����,��Ϸ������ʼ����ʾһ��ͼ,�������Ϸ��ʼ��
	int flag = 0;
	while (flag == 0)
	{
		flag = MainMenu(gameStart);
	}
	endPaint();
	return 1;
}

//�������ж���˹�����״̬
int test05()
{
	startPaint();
	BeginBatchDraw();
	for (int i = 1; i <= 3; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _I_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	paint_Coordinate();
	Tetris tetris(3, 3, _TIAN);
	paint_Tetris(tetris);
	FlushBatchDraw();
	Sleep(1000);
	cleardevice();
	for (int i = 1; i <= 8; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _Z_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	for (int i = 1; i <= 8; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _L_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	for (int i = 1; i <= 4; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _T_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	for (int i = 1; i <= 4; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _Z_LAZY_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	for (int i = 1; i <= 4; i++) {
		paint_Coordinate();
		Tetris tetris(3, 3, _T_STATE(i));
		paint_Tetris(tetris);
		FlushBatchDraw();
		Sleep(1000);
		cleardevice();
	}
	outtextxy(0, 0, "�������");
	FlushBatchDraw();
	_getch();
	return 1;
}

//���������߼��������߼�
int test06()
{
	startPaint();
	BeginBatchDraw();
	int num = 0;
	int*** arr;
	arr = init_CubeArr();
	paint_Coordinate();


	while (1) {
		showScore(score);
		if (num <= 2) 
		{
			summonCube(arr, 64);
		}
		num++;
		fall(arr, 0);
		paint_Cube(arr);
		FlushBatchDraw();
		int* overArr = getOverflowedLayer(arr);
		if (overArr == NULL)
		{
			exit(-1);
		}
		else {
			score += 100 * killLayer(arr, overArr, 500);
		}
		
		Sleep(100);
		clear_Coordinate();
	}

	return 1;
}

//�������ֲ���
int test07()
{
	startPaint();
	mciSendString(_T("open " MUSIC_1),NULL,0,NULL);
	mciSendString(_T("play " MUSIC_1), NULL, 0, NULL);
	outtextxy(0, 0, "��������:" MUSIC_1);
	_getch();
	mciSendString(_T("stop " MUSIC_1), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_1), NULL, 0, NULL);

	mciSendString(_T("open " MUSIC_2), NULL, 0, NULL);
	mciSendString(_T("play " MUSIC_2), NULL, 0, NULL);
	outtextxy(0, 0, "��������:" MUSIC_2);
	_getch();
	mciSendString(_T("stop " MUSIC_2), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_2), NULL, 0, NULL);

	mciSendString(_T("open " MUSIC_3), NULL, 0, NULL);
	mciSendString(_T("play " MUSIC_3), NULL, 0, NULL);
	outtextxy(0, 0, "��������:" MUSIC_3);
	_getch();
	mciSendString(_T("stop " MUSIC_3), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_3), NULL, 0, NULL);

	return 1;
}

//�����ļ���д
int test08()
{
	/*fstream fs("test.txt",ios::out);
	fs << "yes" << endl << "no" << endl << "1" << endl;
	fs.close();
	char buf[1024] = { 0 };
	ReadLineData("test.txt", 2,buf);
	cout << buf << endl;
	DelLineData("test.txt", 2);
	memset(buf, 0, 1024);
	ReadLineData("test.txt", 2,buf);
	cout << buf;*/
	//for (int i = 0; i < 4; i++) {
	//	DelLineData(RECORD_FILE, i);
	//}
	//for (int i = 0; i < 4; i++) {
	//	char buf[1024] = { 0 };
	//	int ret = ReadLineData(RECORD_FILE, i, buf);
	//	if (ret != -1)
	//		cout << buf << endl;
	//	else
	//		cout << "wrong" << endl;
	//}
	startPaint();
	showRecord(WINDOW_WIDTH/2,200);
	_getch();



	return 1;
}

//���԰�ť�ؼ�
int test09()
{
	startPaint();
	//paint_Button();
	Button btn;
	btn.m_Text = "���ǰ�ť";
	btn.m_Font = "����";
	btn.show();
	btn.messageOn();
	while (1)
	{

	}

	return 1;
}

//����Widget�ؼ�
int test10()
{
	startPaint();
	setbkcolor(BLACK);
	setfillcolor(BLACK);
	RECT r = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	Widget wdt;
	//wdt.~Widget();
	//wdt.show();
	Button btn(&wdt);
	btn.show();
	btn.messageOn();

	_getch();
	return 1;
}

//1.���Թ�ȫ��ǽ.
//2.ѡһ����Ԫ����Ϊ�Թ���ͨ·(��һ��ѡ�����)��Ȼ���������ǽ���������ң������б�
//3.���б��ﻹ��ǽʱ
//��.���б������ѡһ��ǽ���������ǽ�ָ���������Ԫ��ֻ��һ����Ԫ�񱻷��ʹ�
//��a���Ǿʹ��б����Ƴ�����ǽ������ǽ��ͨ����δ���ʵĵ�Ԫ���Ϊ�Թ���ͨ·
//��b����������ӵ�ǽ�����б�
//��.���ǽ����ĵ�Ԫ���Ѿ������ʹ�������ͨ�ˣ����Ǿʹ��б����Ƴ�����ǽ

//#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <ctime>
using namespace std;
#define UNIT_LENGTH 20
#define MAX 20
#define WALL 1
#define ROAD 0
#define TRIGGER 2
class Maze
{
public:
	int gitmap[MAX][MAX];
	int row, col;

	void initMap()
	{
		for (int i = 0; i < row; i++)
		{
			memset(gitmap[i], WALL, col);
		}
	}
	void setMap()
	{
		srand((unsigned int)time(NULL));
		gitmap[0][0] = ROAD;//��ʼ������

	}
	void showMap()
	{
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				switch (gitmap[i][j])
				{
				case WALL:
					setfillcolor(WHITE);
					break;
				case ROAD:
					setfillcolor(MAGENTA);
					break;
				case TRIGGER:
					setfillcolor(CYAN);
				}
				fillrectangle(20 + UNIT_LENGTH * j, 20 + UNIT_LENGTH * i, 20 + UNIT_LENGTH * (j + 1), 20 + UNIT_LENGTH * (i + 1));
			}
		}
	}
};




//int main()
//{
//	initgraph(1280, 960);
//	Maze maze;
//	maze.initMap();
//	
//	_getch();
//	closegraph();
//}

#include <graphics.h>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define WIDTH 1080//�ֱ���
#define HEIGHT 720
#define BLOCK_XY 20//С����߳�
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������

#define kongqi COLORREF RGB(255,255,255)//������ɫ
#define qiangbi COLORREF RGB(50,50,50)//ǽ����ɫ
#define daixuan COLORREF RGB(0,255,0)//��ѡ��ɫ
#define xuanzhong COLORREF RGB(255,0,0)//ѡ����ɫ

#define ROAD 0//·��������
#define WALL 1//ǽ��
#define WAIT 2//��ѡ·��
#define Player 7
#define Des 8

struct block {
public:
	int x;
	int y;
	block(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//0���������1����ǽ�ڣ�2�����ѡ·�㣬3����ѡ��·�㣨���ǲ�û���õ���
vector<block*> openlist;//��ѡ�б�
vector<block*> list;

/*��������*/
void clearscreen(COLORREF RGB);//��յ�ͼΪRGB��ɫ(��������)
void gamedrawpixal(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void gamedrawResource(int x, int y, string img);
void init();//��ʼ��
void join(int x, int y);//��x,y������ǽ�ڵ�·������ѡ�б�
void display();//ˢ����Ļ
void prim_main();//prim��ѭ��
void through(int x, int y);//��x,y��������һ������Ѿ����·��·���ͨ
/*********/

void init() {
	openlist.clear();
	/*��ͼ��ʼ��Ϊǽ*/
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			map[x][y] = WALL;
		}
	}
	/*���ѡһ��·�㣬�������·*/
	map[BLOCK_WIDTH / 2][BLOCK_HEIGHT / 2] = ROAD;
	map[0][0] = Player;
	/*��·�����ܲ���·��·������ѡ�б�*/
	join(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
	prim_main();
}
void prim_main() {
	while (openlist.size() > 0) {
		/*�Ӵ�ѡ·�����ѡһ��·��A*/
		int AIndexea = rand() % openlist.size();
		block* A = openlist[AIndexea];
		/*��A��������һ������Ѿ����·��·���ͨ*/
		through(A->x, A->y);
		/*��A���·*/
		map[A->x][A->y] = ROAD;
		/*��A���ܲ���·��·������ѡ�б�*///(ע�⣬��Ҫ�ظ����·�㣡)
		join(A->x, A->y);
		/*�Ӵ�ѡ·�����Ƴ�A*/
		openlist.erase(openlist.begin() + AIndexea);

		gamedrawpixal(A->x, A->y, xuanzhong);
		FlushBatchDraw();
		display();
	}
	openlist.clear();
}
void through(int x, int y) {
	list.clear();
	//��
	if (y - 2 >= 0 && map[x][y - 2] == ROAD) {
		block* a = new block(x, y - 1);
		list.push_back(a);
	}
	//��
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == ROAD) {
		block* b = new block(x, y + 1);
		list.push_back(b);
	}
	//��
	if (x - 2 >= 0 && map[x - 2][y] == ROAD) {
		block* c = new block(x - 1, y);
		list.push_back(c);
	}
	//��
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == ROAD) {
		block* d = new block(x + 1, y);
		list.push_back(d);
	}
	int BIndexea = rand() % list.size();
	block* B = list[BIndexea];
	/*��x��y��B��ͨ*/
	map[B->x][B->y] = ROAD;
}
void join(int x, int y) {
	//��
	if (y - 2 >= 0 && map[x][y - 2] == WALL) {
		block* a = new block(x, y - 2);
		openlist.push_back(a);
		map[x][y - 2] = WAIT;
	}
	//��
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == WALL) {
		block* b = new block(x, y + 2);
		openlist.push_back(b);
		map[x][y + 2] = WAIT;
	}
	//��
	if (x - 2 >= 0 && map[x - 2][y] == WALL) {
		block* c = new block(x - 2, y);
		openlist.push_back(c);
		map[x - 2][y] = WAIT;
	}
	//��
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == WALL) {
		block* d = new block(x + 2, y);
		openlist.push_back(d);
		map[x + 2][y] = WAIT;
	}
}
void display() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (map[x][y] == WALL) {
				gamedrawpixal(x, y, qiangbi);
			}
			else if (map[x][y] == ROAD) {
				gamedrawpixal(x, y, kongqi);
			}
			else if (map[x][y] == WAIT) {
				gamedrawpixal(x, y, daixuan);
			}
			else if (map[x][y] == Player) {
				gamedrawpixal(x, y, kongqi);
				gamedrawResource(x, y, "player.png");
			}
		}
	}
	FlushBatchDraw();
}
void clearscreen(COLORREF RGB) {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			gamedrawpixal(x, y, RGB);
		}
	}
}
void gamedrawpixal(int x, int y, COLORREF RGB) {
	setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
	fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}
void gamedrawResource(int x, int y, string imgName)
{
	IMAGE img;
	string temp;
	temp = "Resource/Image/" + imgName;
	LPCTSTR str = (LPCTSTR)(temp.c_str());
	loadimage(&img, str, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
	putimage(x * BLOCK_XY, y * BLOCK_XY, &img);
}
int main01() {
	srand((unsigned)time(NULL));//���������
	initgraph(WIDTH, HEIGHT);//������ͼ����
	BeginBatchDraw();//��ʼ������ͼ
	cleardevice();//�����ʾ

	init();

	display();
	FlushBatchDraw();//�������������Ļ

	while (1);
}


#endif