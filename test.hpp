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
// 引用 Windows Multimedia API,播放音乐
#pragma comment(lib,"Winmm.lib")

///test.hpp是主要的测试函数，它不需要被其他隶属文件包含使用。
//它的用处主要是帮助我调试每一个模块是否正常工作

using namespace std;

int test01()
{
	initgraph(640, 480);
	isPainting = 1;
	outtextxy(0, 0, "测试BeginBatchDraw函数");
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
	outtextxy(0, 0, "按任意键退出");
	getchar();
	endPaint();

	return 1;
}

//测试键盘的输入
int test02()
{
	startPaint();
	outtextxy(0, 0, "测试键盘输入");
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
	outtextxy(0, 0, "按任意键退出");
	getchar();
	closegraph();
	
	return 1;
}

//测试获取系统时间
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

//测试与王本立编写的函数配合
//游戏性测试函数(入口)
int test04()
{
	//开始场景,游戏即将开始（显示一张图,点击后游戏开始）
	int flag = 0;
	while (flag == 0)
	{
		flag = MainMenu(gameStart);
	}
	endPaint();
	return 1;
}

//测试所有俄罗斯方块的状态
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
	outtextxy(0, 0, "测试完毕");
	FlushBatchDraw();
	_getch();
	return 1;
}

//测试下落逻辑和消除逻辑
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

//测试音乐播放
int test07()
{
	startPaint();
	mciSendString(_T("open " MUSIC_1),NULL,0,NULL);
	mciSendString(_T("play " MUSIC_1), NULL, 0, NULL);
	outtextxy(0, 0, "播放音乐:" MUSIC_1);
	_getch();
	mciSendString(_T("stop " MUSIC_1), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_1), NULL, 0, NULL);

	mciSendString(_T("open " MUSIC_2), NULL, 0, NULL);
	mciSendString(_T("play " MUSIC_2), NULL, 0, NULL);
	outtextxy(0, 0, "播放音乐:" MUSIC_2);
	_getch();
	mciSendString(_T("stop " MUSIC_2), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_2), NULL, 0, NULL);

	mciSendString(_T("open " MUSIC_3), NULL, 0, NULL);
	mciSendString(_T("play " MUSIC_3), NULL, 0, NULL);
	outtextxy(0, 0, "播放音乐:" MUSIC_3);
	_getch();
	mciSendString(_T("stop " MUSIC_3), NULL, 0, NULL);
	mciSendString(_T("close " MUSIC_3), NULL, 0, NULL);

	return 1;
}

//测试文件读写
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

//测试按钮控件
int test09()
{
	startPaint();
	//paint_Button();
	Button btn;
	btn.m_Text = "我是按钮";
	btn.m_Font = "隶书";
	btn.show();
	btn.messageOn();
	while (1)
	{

	}

	return 1;
}

//测试Widget控件
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

//1.让迷宫全是墙.
//2.选一个单元格作为迷宫的通路(我一般选择起点)，然后把它的邻墙（上下左右）放入列表
//3.当列表里还有墙时
//①.从列表里随机选一个墙，如果这面墙分隔的两个单元格只有一个单元格被访问过
//（a）那就从列表里移除这面墙，即把墙打通，让未访问的单元格成为迷宫的通路
//（b）把这个格子的墙加入列表
//②.如果墙两面的单元格都已经被访问过（都打通了），那就从列表里移除这面墙

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
		gitmap[0][0] = ROAD;//起始点设置

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

#define WIDTH 1080//分辨率
#define HEIGHT 720
#define BLOCK_XY 20//小方格边长
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//小方格x轴数量
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//小方格y轴数量

#define kongqi COLORREF RGB(255,255,255)//空气颜色
#define qiangbi COLORREF RGB(50,50,50)//墙壁颜色
#define daixuan COLORREF RGB(0,255,0)//待选颜色
#define xuanzhong COLORREF RGB(255,0,0)//选中颜色

#define ROAD 0//路（空气）
#define WALL 1//墙壁
#define WAIT 2//待选路点
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

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//0代表空气，1代表墙壁，2代表待选路点，3代表选中路点（但是并没有用到）
vector<block*> openlist;//待选列表
vector<block*> list;

/*函数声明*/
void clearscreen(COLORREF RGB);//清空地图为RGB颜色(带有网格)
void gamedrawpixal(int x, int y, COLORREF RGB);//在x，y位置画颜色为RGB的方格
void gamedrawResource(int x, int y, string img);
void init();//初始化
void join(int x, int y);//将x,y四周是墙壁的路点加入待选列表
void display();//刷新屏幕
void prim_main();//prim主循环
void through(int x, int y);//将x,y与它四周一个随机已经变成路的路点打通
/*********/

void init() {
	openlist.clear();
	/*地图初始化为墙*/
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			map[x][y] = WALL;
		}
	}
	/*随机选一个路点，将它变成路*/
	map[BLOCK_WIDTH / 2][BLOCK_HEIGHT / 2] = ROAD;
	map[0][0] = Player;
	/*将路点四周不是路的路点加入待选列表*/
	join(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
	prim_main();
}
void prim_main() {
	while (openlist.size() > 0) {
		/*从待选路点随机选一个路点A*/
		int AIndexea = rand() % openlist.size();
		block* A = openlist[AIndexea];
		/*将A与它四周一个随机已经变成路的路点打通*/
		through(A->x, A->y);
		/*将A变成路*/
		map[A->x][A->y] = ROAD;
		/*将A四周不是路的路点加入待选列表*///(注意，不要重复添加路点！)
		join(A->x, A->y);
		/*从待选路点中移除A*/
		openlist.erase(openlist.begin() + AIndexea);

		gamedrawpixal(A->x, A->y, xuanzhong);
		FlushBatchDraw();
		display();
	}
	openlist.clear();
}
void through(int x, int y) {
	list.clear();
	//上
	if (y - 2 >= 0 && map[x][y - 2] == ROAD) {
		block* a = new block(x, y - 1);
		list.push_back(a);
	}
	//下
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == ROAD) {
		block* b = new block(x, y + 1);
		list.push_back(b);
	}
	//左
	if (x - 2 >= 0 && map[x - 2][y] == ROAD) {
		block* c = new block(x - 1, y);
		list.push_back(c);
	}
	//右
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == ROAD) {
		block* d = new block(x + 1, y);
		list.push_back(d);
	}
	int BIndexea = rand() % list.size();
	block* B = list[BIndexea];
	/*将x，y与B打通*/
	map[B->x][B->y] = ROAD;
}
void join(int x, int y) {
	//上
	if (y - 2 >= 0 && map[x][y - 2] == WALL) {
		block* a = new block(x, y - 2);
		openlist.push_back(a);
		map[x][y - 2] = WAIT;
	}
	//下
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == WALL) {
		block* b = new block(x, y + 2);
		openlist.push_back(b);
		map[x][y + 2] = WAIT;
	}
	//左
	if (x - 2 >= 0 && map[x - 2][y] == WALL) {
		block* c = new block(x - 2, y);
		openlist.push_back(c);
		map[x - 2][y] = WAIT;
	}
	//右
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
	srand((unsigned)time(NULL));//随机数种子
	initgraph(WIDTH, HEIGHT);//创建绘图窗口
	BeginBatchDraw();//开始批量绘图
	cleardevice();//清空显示

	init();

	display();
	FlushBatchDraw();//将缓冲输出到屏幕

	while (1);
}


#endif