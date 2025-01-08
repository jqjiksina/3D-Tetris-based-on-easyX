#include "StartScene.h"
#include "paint.h"
#include "toString.h"
#include <fstream>
#include <conio.h>
#include "MyData.h"
#include "ReadLineData.h"
#include "GameObject.h"
#include "Button.h"
#include <iostream>
#pragma comment(lib,"Winmm.lib")
#include "CONSTANT_NAME_DEFINE.h"
using namespace std;

//显示主菜单
int MainMenu(int(*func)(void)) {
	////创建窗口
	if (!isPainting)
		startPaint();
	
	//播放音乐
	mciSendString(_T("open " MUSIC_1), NULL, 0, NULL);
	mciSendString(_T("play " MUSIC_1), NULL, 0, NULL);
	outtextxy(0, 0, "播放BGM:" MUSIC_1);

	int ret = 0;
	BeginBatchDraw();

	settextcolor(YELLOW);
	setfillcolor(BROWN);
	setbkcolor(BROWN);
	settextstyle(50, 0, _T("Bernard MT Condensed"));

	RECT r = { 280,WINDOW_HEIGHT * 2 / 3 + 20,1000,WINDOW_HEIGHT * 2 / 3 + 50 + 20 };
	Button btn1(r, "Press Here To Start The Game...");

	RECT r2 = { 566, 620,800 ,670 };
	Button btn2(r2, "Records");

	RECT r3 = { 566, 680,800 ,730 };
	Button btn3(r3, "Settings");

	RECT r4 = { 566,740,800,790 };
	Button btn4(r4, "Exit");

	ExMessage message;
	while (1)
	{
		//贴图操作
		showImage(IMAGE_1);
		//开始游戏
		btn1.show(0);
		//记录
		btn2.show(0);
		//设置
		btn3.show(0);
		//退出
		btn4.show(0);
		
		FlushBatchDraw();
		message = getmessage(EX_MOUSE);
		if (message.message == WM_LBUTTONDOWN)
		{
			//鼠标左键点击特定区域切换画面，并停止主界面音乐
			if (message.x > r.left && message.y > r.top && message.x < r.right && message.y < r.bottom)
			{
				mciSendString(_T("stop " MUSIC_1), NULL, 0, NULL);
				mciSendString(_T("close " MUSIC_1), NULL, 0, NULL);
				btn1.clicked();//显示按钮凹陷特效
				ret = func();//进入游戏主进程控制函数func
				break;
			}
			//点击特定区域进入记录页面
			if (btn2.isIn(message.x,message.y))
			{
				btn2.clicked();//显示按钮凹陷特效
				showRecord(WINDOW_WIDTH / 2-300,30);
			}
			//点击特定区域进入设置页面
			if (btn3.isIn(message.x,message.y))
			{
				btn3.clicked();
				settings();
			}
			//点击退出
			if (btn4.isIn(message.x, message.y))
			{
				btn4.clicked();
				exit(0);
			}
		}
		flushmessage();
	}
	
	
	return ret;
}

//开始游戏函数
int gameStart()
{
	srand((unsigned int)time(NULL));//初始化随机数种子
	int*** arr = init_CubeArr();//初始化立方体数组
	Tetris tetris1(rand() % (X_LENGTH - 3) + 2, rand() % (Y_LENGTH - 3) + 2, _TIAN, rand() % 6 + 1);//初始化俄罗斯方块
	int ret = 1;
	score = 0;
	while (ret)
	{
		if (!isPainting)
			startPaint();
		setbkcolor(BLACK);
		cleardevice();
		paint_Coordinate();
		tetris1.addToCubeArr(arr);
		BeginBatchDraw();
		FlushBatchDraw();
		Sleep(1000);//缓冲一会
		//播放BGM
		if (MusicOn)
		{
			mciSendString(_T("open " MUSIC_2), NULL, 0, NULL);
			mciSendString(_T("play " MUSIC_2 " repeat"), NULL, 0, NULL);
			outtextxy(0, 0, "播放音乐:" MUSIC_2);
		}
		//运行游戏主进程
		int isOver = Thread_Main(tetris1, arr);
		//停止播放BGM
		mciSendString(_T("stop " MUSIC_2), NULL, 0, NULL);
		mciSendString(_T("close " MUSIC_2), NULL, 0, NULL);
		//结束游戏，弹出窗口-返回主界面/重新开始
		if (isOver == 1)//因为GameOver而退出，显示结算界面
			ret = gameOver();//ret-1重新开始;ret-0返回主界面
		else if (isOver == 0)
			ret = 0;//因为暂停而直接退出，不显示结算界面

		tetris1 = Tetris(rand() % (X_LENGTH - 4) + 2, rand() % (Y_LENGTH - 4) + 2, _TIAN, rand() % 6 + 1);//初始化俄罗斯方块
		arr = init_CubeArr();
	}


	EndBatchDraw();
	free_CubeArr(arr);//释放空间


	return ret;
}

//游戏主进程函数
int Thread_Main(Tetris& tetris1, int*** arr)
{
	settextstyle(20, 0, "黑体");
	int cultimate = 0;
	int inter_time = INTER_TIME;
	bool isOver = false;
	startTime = clock() / 1000;
	string pos;
	long suprise_time = clock();
	Tetris tetris_tmp = Tetris(rand() % (X_LENGTH - 3) + 2, rand() % (Y_LENGTH - 3) + 2, RANDOM_STATE[rand() % SEED_NUM], rand() % 6 + 1);
	while (1)
	{
		//清空屏幕，但保留坐标系与背景图片
		clear_Coordinate();
		//重绘立方体数组
		update(arr, score, tetris1, &tetris_tmp);
		//玩家控制Tetris实现移动、旋转功能
		//开始等待键盘输入（不会阻塞程序的运行)
		tetris1.removeFromCubeArr(arr);
		ExMessage msg;
		long st = clock();
		while (clock() - st < inter_time)
		{
			static long st_1 = st - inter_time;
			//只有当Tetris活跃时才能进行移动
			if (tetris1.isActive)
			{
				if (peekmessage(&msg, EX_KEY)) {
					flushmessage();//清空消息缓存区，提高响应流畅度
					//旋转坐标系逻辑
					if (msg.message == WM_KEYDOWN && msg.vkcode == _E_KEY)
					{
						tetris1.removeFromCubeArr(arr);
						//tetris1.rotateWithAxis();
						rotateAxis(arr);
						tetris1.addToCubeArr(arr);
						clear_Coordinate();
						update(arr, score, tetris1, &tetris_tmp);
						flushmessage();
						continue;
					}
					//加速逻辑
					if (msg.message == WM_KEYDOWN && msg.vkcode == _SHIFT_KEY)
					{
						inter_time = 0;
						flushmessage();
					}
					//暂停逻辑
					if (msg.message == WM_KEYDOWN && msg.vkcode == _P_KEY)
					{
						if (!pause())//Return返回主界面！
						{
							save();
							return 0;
						}
						clear_Coordinate();					//暂停后恢复
						update(arr, score, tetris1, &tetris_tmp);
						flushmessage();
					}
					//移动逻辑
					if (msg.message == WM_KEYDOWN && (msg.vkcode == _A_KEY || msg.vkcode == _D_KEY || msg.vkcode == _W_KEY || msg.vkcode == _S_KEY))
					{

						if (tetris1.move(msg, arr))
						{
							if (SoundEffectOn)
							{
								//移动成功，则播放音效
								mciSendString(_T("stop " SOUND_EFFECT_1), NULL, 0, NULL);
								mciSendString(_T("close " SOUND_EFFECT_1), NULL, 0, NULL);
								mciSendString(_T("open " SOUND_EFFECT_1), NULL, 0, NULL);
								mciSendString(_T("play " SOUND_EFFECT_1), NULL, 0, NULL);
							}
						}
							
						else
						{
							if (SoundEffectOn)
							{
								//移动失败，播放失败音效
								mciSendString(_T("stop " SOUND_EFFECT_5), NULL, 0, NULL);
								mciSendString(_T("close " SOUND_EFFECT_5), NULL, 0, NULL);
								mciSendString(_T("open " SOUND_EFFECT_5), NULL, 0, NULL);
								mciSendString(_T("play " SOUND_EFFECT_5), NULL, 0, NULL);
							}
						}
						
						
						pos = numToString(tetris1.centreBlockPosition[0]) + " "
							+ numToString(tetris1.centreBlockPosition[1]) + " "
							+ numToString(tetris1.centreBlockPosition[2]);
						clear_Coordinate();
						update(arr, score, tetris1, &tetris_tmp);
						flushmessage();//清空消息缓存区
						continue;
					}
					//转换状态逻辑,注意两次旋转要有充分缓冲时间(因为旋转要的时间很大)
					if (clock() - st_1 >= 0 && msg.message == WM_KEYDOWN && msg.vkcode == _Q_KEY)
					{
						if (tetris1.canRotate(arr))
						{
							tetris1.rotate(arr);
						}
						else
						{
							if (SoundEffectOn)
							{
								mciSendString("stop " SOUND_EFFECT_5, 0, 0, 0);
								mciSendString("close " SOUND_EFFECT_5, 0, 0, 0);
								//旋转失败，应该有提示
								mciSendString("open " SOUND_EFFECT_5, 0, 0, 0);
								mciSendString("play " SOUND_EFFECT_5, 0, 0, 0);
							}
						}
						//刷新中心方块坐标
						pos = numToString(tetris1.centreBlockPosition[0]) + " "
							+ numToString(tetris1.centreBlockPosition[1]) + " "
							+ numToString(tetris1.centreBlockPosition[2]);
						st_1 = clock();//重置计时器
						clear_Coordinate();
						update(arr, score, tetris1, &tetris_tmp);
						flushmessage();
						continue;
					}
					//使用道具逻辑
					if (msg.message == WM_KEYDOWN && msg.vkcode == _F_KEY)
					{
						if (clock() - suprise_time > SURPRISE_TIME)
						{
							suprise_time = clock();//重置计时器
							if (SoundEffectOn)
							{
								mciSendString("stop " SOUND_EFFECT_6, 0, 0, 0);
								mciSendString("close " SOUND_EFFECT_6, 0, 0, 0);
								//播放提示音
								mciSendString("open " SOUND_EFFECT_6, 0, 0, 0);
								mciSendString("play " SOUND_EFFECT_6, 0, 0, 0);
							}
							tetris1.removeFromCubeArr(arr);
							int count = 0;
							//消除最底层
							for (int i = 0; i < X_LENGTH; i++) {
								for (int j = 0; j < Y_LENGTH; j++) {
									if (arr[i][j][0])
									{
										count++;
										arr[i][j][0] = 0;
									}
								}
							}
							//若没有消除，则播放失败提示音
							if (SoundEffectOn)
							{
								if (!count)
								{
									mciSendString("stop " SOUND_EFFECT_5, 0, 0, 0);
									mciSendString("close " SOUND_EFFECT_5, 0, 0, 0);
									mciSendString("open " SOUND_EFFECT_5, 0, 0, 0);
									mciSendString("play " SOUND_EFFECT_5, 0, 0, 0);
								}
							}
							fall(arr, 0);
							tetris1.addToCubeArr(arr);
							outtextxy(WINDOW_WIDTH / 2 - 50, 0, "使用道具成功!");
							FlushBatchDraw();
							Sleep(500);//短暂的时停
							score += 50;
						}
						else
						{
							if (SoundEffectOn)
							{
								mciSendString("stop " SOUND_EFFECT_5, 0, 0, 0);
								mciSendString("close " SOUND_EFFECT_5, 0, 0, 0);
								//使用道具失败，应该有提示
								mciSendString("open " SOUND_EFFECT_5, 0, 0, 0);
								mciSendString("play " SOUND_EFFECT_5, 0, 0, 0);
							}
							outtextxy(WINDOW_WIDTH / 2 - 50, 0, "道具冷却未完毕!");
							FlushBatchDraw();
						}
					}
				}
			}
			else break;
			//outtextxy(0, 70, numToString(clock() - st));
		}
		inter_time = INTER_TIME;

		tetris1.addToCubeArr(arr);

		//俄罗斯方块是活动状态时下落一格
		if (tetris1.isActive)
		{
			//先移除
			tetris1.removeFromCubeArr(arr);
			//根据纵坐标判断是否触底，触底则停止活跃，并不再下落，后将生成新的Tetris/
			//优化：触底时允许用户再进行一帧的操作
			for (int i = 2; tetris1.m_Arr[i] != -1; i += 3)
			{
				if (!tetris1.m_Arr[i] || arr[tetris1.m_Arr[i - 2]][tetris1.m_Arr[i - 1]][tetris1.m_Arr[i] - 1])
				{

					tetris1.isActive = 0;
					break;
				}
			}

			if (tetris1.fall(arr));


			//前面移除了Tetris,下落后再次加上来
			tetris1.addToCubeArr(arr);
		}
		//俄罗斯方块落地时，判断是否启用消除逻辑,并生成新的Tetris
		if (!tetris1.isActive)
		{
			int* overArr = getOverflowedLayer(arr);
			if (overArr == NULL)
			{
				exit(-1);
			}
			else {
				int count = killLayer(arr, overArr, 500);//获取消除的层数
				score += count * 100;//每消除一层得分100
			}
			tetris1.isActive = 0;
			tetris1.addToCubeArr(arr);
			//生成随机俄罗斯方块, 预生成一个
			tetris1 = tetris_tmp;
			tetris_tmp = Tetris(rand() % (X_LENGTH - 3) + 2, rand() % (Y_LENGTH - 3) + 2, RANDOM_STATE[rand() % SEED_NUM], rand() % 6 + 1);
			for (int i = 0; tetris1.m_Arr[i] != -1; i += 3)
			{
				//生成的Tetris与原有方块重合，游戏结束
				if (arr[tetris1.m_Arr[i]][tetris1.m_Arr[i + 1]][tetris1.m_Arr[i + 2]])
				{
					//保存用时与得分至文件
					free(arr);
					save();

					return 1;
				}
			}
		}
	}
}

//游戏结束
int gameOver()
{
	//播放失败音效
	mciSendString(_T("open " SOUND_EFFECT_4), NULL, 0, NULL);
	mciSendString(_T("play " SOUND_EFFECT_4), NULL, 0, NULL);
	cleardevice();
	showImage(_T(BASE_PATH "07.jpg"));
	settextstyle(80,0,_T("Bernard MT Condensed"));
	outtextxy(500, 300, "GAME OVER");
	settextstyle(40, 0, _T("方正舒体"));
	RECT r = { 480,400,800,800 };
	string str = "您的分数为:" + to_string(score);
	LPCTSTR text = (LPCTSTR)(str.c_str());
	drawtext(text, &r, DT_CENTER);
	RECT r2 = { 480,450,800,850 };
	str = "用时为:" + cdata.time_R;
	text = (LPCTSTR)(str.c_str());
	drawtext(text, &r2, DT_CENTER);
	RECT r1 = { 480,500,800,900 };
	drawtext("是否继续?Y or N", &r1, DT_CENTER);

	setbkcolor(BLACK);
	setfillcolor(BLACK);

	RECT r3 = { 500,550,600,600 };
	Button btn_R(r3, "重玩");
	btn_R.show(0);

	RECT r4 = { 650,550,850,600 };
	Button btn_C(r4, "返回主菜单");
	btn_C.show(0);

	FlushBatchDraw();
	Sleep(3000);//缓冲3s，给用户反应时间
	ExMessage msg;
	while (1) {//返回1代表重新开始,返回0代表返回主界面
		getmessage(&msg);
		flushmessage();
		if (msg.message == WM_KEYDOWN && msg.vkcode == _Y_KEY)
		{
			mciSendString(_T("stop " SOUND_EFFECT_4), NULL, 0, NULL);
			mciSendString(_T("close " SOUND_EFFECT_4), NULL, 0, NULL);
			return 1;
		}
		if (msg.message == WM_KEYDOWN && msg.vkcode == _N_KEY)
		{
			mciSendString(_T("stop " SOUND_EFFECT_4), NULL, 0, NULL);
			mciSendString(_T("close " SOUND_EFFECT_4), NULL, 0, NULL);
			return 0;
		}
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (btn_R.isIn(msg.x, msg.y))
			{
				mciSendString(_T("stop " SOUND_EFFECT_4), NULL, 0, NULL);
				mciSendString(_T("close " SOUND_EFFECT_4), NULL, 0, NULL);
				btn_R.clicked();
				return 1;
			}
			if (btn_C.isIn(msg.x, msg.y))
			{
				mciSendString(_T("stop " SOUND_EFFECT_4), NULL, 0, NULL);
				mciSendString(_T("close " SOUND_EFFECT_4), NULL, 0, NULL);
				btn_C.clicked();
				return 0;
			}
		}
	}
	
}

int pause()
{
	//显示界面
	RECT r = { 400,20,WINDOW_WIDTH - 400,WINDOW_HEIGHT - 50 };
	setfillcolor(RGB(0, 200, 255));
	fillrectangle(r.left, r.top + 30, r.right, r.bottom);
	setbkcolor(BLACK);
	settextcolor(BROWN);
	settextstyle(20, 0, _T("黑体"));
	drawtext(_T("游戏暂停..."), &r, DT_CENTER);

	int x1 = WINDOW_WIDTH / 2 - 220;
	int y1 = WINDOW_HEIGHT /4;
	int x2 = WINDOW_WIDTH / 2 + 220;
	int y2 = WINDOW_HEIGHT / 4 + 200;
	settextcolor(RGB(255, 0, 0));
	setbkcolor(RGB(0,100,178));
	setfillcolor(RGB(0,100,178));
	fillrectangle(x1, y1, x2, y2);
	//继续按钮
	RECT r1 = { x1,y1,x2,y2 };
	settextstyle(20, 0, _T("隶书"));
	Button btn_Resume(r1, "Resume");
	btn_Resume.show(0);
	//返回按钮
	RECT r2 = { x1, y1+250,x2,y2+250 };
	Button btn_Return(r2, "Return");
	btn_Return.show(0);

	long st_time = clock();
	long end_time;
	while (1)
	{
		//计时
		FlushBatchDraw();
		ExMessage msg;
		if(peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (btn_Resume.isIn(msg.x,msg.y))
				{
					btn_Resume.clicked();
					end_time = clock();
					startTime += (end_time - st_time)/1000;
					break;//退出界面
				}
				if (btn_Return.isIn(msg.x, msg.y))
				{
					btn_Return.clicked();
					btn_Return.m_Text = "Return(Saving Datas...)";//提示用户保存数据中
					btn_Return.show(0);
					FlushBatchDraw();
					Sleep(500);
					return 0;//返回主界面
				}
			}
		}
	}
	//恢复默认值
	setbkcolor(BACKGROUND_COLOR);
	setfillcolor(BRUSH_COLOR);
	return 1;
}

int settings()
{
	//显示界面
	RECT r = { 400,20,WINDOW_WIDTH - 400,WINDOW_HEIGHT - 50 };
	setfillcolor(BLACK);
	fillrectangle(r.left, r.top + 30, r.right, r.bottom);
	setbkcolor(BLACK);
	settextcolor(BROWN);
	settextstyle(20, 0, _T("黑体"));
	drawtext(_T("Settings"), &r, DT_CENTER);

	int x1 = WINDOW_WIDTH / 2 - 50;
	int y1 = WINDOW_HEIGHT * 2 / 3+120;
	int x2 = WINDOW_WIDTH / 2 + 50;
	int y2 = WINDOW_HEIGHT * 2 / 3 + 30+120;
	settextcolor(RGB(255, 0, 0));
	setbkcolor(RGB(0, 100, 178));//界面颜色
	setfillcolor(RGB(0, 100, 178));//cancel框颜色
	settextstyle(20, 0, _T("隶书"));
	//fillrectangle(x1, y1, x2, y2);
	RECT r1 = { x1,y1,x2,y2};
	Button btn_Cancel(r1, "Cancel");
	btn_Cancel.show(0);

	int dif_x1 = WINDOW_WIDTH / 2 - 50;
	int dif_y1 = WINDOW_HEIGHT /5;
	int dif_x2 = WINDOW_WIDTH / 2 + 50;
	int dif_y2 = WINDOW_HEIGHT /5+30;

	RECT r2 = { dif_x1-20,dif_y1,dif_x2+20,dif_y2 };
	Button btn_Dif(r2, "Diffculty:"+to_string(difficulty));
	btn_Dif.show(0);

	RECT r3 = { dif_x1-20,dif_y1+50,dif_x2+20,dif_y2+50 };
	Button btn_More;
	if (SEED_NUM == 36)
	{
		btn_More = Button(r3, "More Cube(ON)");
	}
	else
		btn_More = Button(r3, "More Cube(OFF)");
	btn_More.show(0);

	RECT r4 = { dif_x1-20,dif_y1 + 100,dif_x2+20,dif_y2 + 100 };
	Button btn_Speed(r4, "Speed:" + to_string((1200 - INTER_TIME) / 200));//1~5的速度
	btn_Speed.show(0);

	RECT r5 = { dif_x1 - 50,dif_y1 + 150,dif_x2 + 50,dif_y2 + 150 };
	Button btn_Bk(r5, "BackgroundImage(ON)" );//1~5的速度
	btn_Bk.show(0);

	RECT r6 = { dif_x1 - 50,dif_y1 + 200,dif_x2 + 50,dif_y2 + 200 };
	Button btn_SdE(r6, "SoundEffect(ON)");
	btn_SdE.show(0);

	RECT r7 = { dif_x1 - 50,dif_y1 + 250,dif_x2 + 50,dif_y2 + 250 };
	Button btn_Msc(r7, "Music(ON)");
	btn_Msc.show(0);

	while (1)
	{
		FlushBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				//跳出逻辑
				if (btn_Cancel.isIn(msg.x,msg.y))
				{
					btn_Cancel.clicked();
					break;
				}
				//设置难度
				if (btn_Dif.isIn(msg.x, msg.y))
				{
					btn_Dif.clicked();
					difficulty = difficulty % 3 + 1;
					btn_Dif.m_Text = "Diffculty:" + to_string(difficulty);
					btn_Dif.show();
				}
				//设置更多方块:On/Off
				if (btn_More.isIn(msg.x, msg.y))
				{
					btn_More.clicked();
					if (SEED_NUM == 16)
					{
						SEED_NUM = 36;
						btn_More.m_Text = "More Cube(ON)";
						btn_More.show();
						continue;
					}
					if (SEED_NUM == 36)
					{
						SEED_NUM = 16;
						btn_More.m_Text = "More Cube(OFF)";
						btn_More.show();
						continue;
					}
				}
				//设置速度
				if (btn_Speed.isIn(msg.x, msg.y))
				{
					btn_Speed.clicked();
					INTER_TIME = INTER_TIME - 200 > 0 ? INTER_TIME-200:1000;//设置下落间隔在200~1000内循环设置
					btn_Speed.m_Text = "Speed:" + to_string((1200 - INTER_TIME)/200);
					btn_Speed.show();
					continue;
				}
				//设置背景图片
				if (btn_Bk.isIn(msg.x, msg.y))
				{
					btn_Bk.clicked();
					btn_Bk.m_Text = btn_Bk.m_Text == "BackgroundImage(ON)" ? "BackgroundImage(OFF)" : "BackgroundImage(ON)";
					btn_Bk.show();
					isBackgroundImageSet = isBackgroundImageSet ^ 1;
					continue;
				}

				//设置音效开关
				if (btn_SdE.isIn(msg.x, msg.y))
				{
					btn_SdE.clicked();
					SoundEffectOn = SoundEffectOn ^ 1;
					btn_SdE.m_Text = SoundEffectOn ? "SoundEffect(ON)" : "SoundEffect(OFF)";
					btn_SdE.show();
					continue;
				}

				//设置音乐开关
				if (btn_Msc.isIn(msg.x, msg.y))
				{
					btn_Msc.clicked();
					MusicOn = MusicOn ^ 1;
					btn_Msc.m_Text = MusicOn ? "Music(ON)" : "Music(OFF)";
					btn_Msc.show();
					if (MusicOn)
					{
						mciSendString(_T("open " MUSIC_1), NULL, 0, NULL);
						mciSendString(_T("play " MUSIC_1), NULL, 0, NULL);
					}
					else
					{
						mciSendString(_T("stop " MUSIC_1), NULL, 0, NULL);
						mciSendString(_T("close " MUSIC_1), NULL, 0, NULL);
					}
					continue;
				}
			}
		}
	}
	
	//设置界面消失后，应用设置
	switch (difficulty)
	{
	case 1:
		::X_LENGTH = 6;
		::Y_LENGTH = 6;
		break;
	case 2:
		::X_LENGTH = 8;
		::Y_LENGTH = 8;
		break;
	case 3:
		::X_LENGTH = 10;
		::Y_LENGTH = 10;
		break;
	}

	//恢复默认值
	setbkcolor(BACKGROUND_COLOR);
	setfillcolor(BRUSH_COLOR);
	return 1;
}

int showRecord(int x, int y)
{
	int page = 1;
	read();
	while (1)
	{
		setfillcolor(BLACK);
		fillrectangle(200, 50, WINDOW_WIDTH - 200, WINDOW_HEIGHT - 50);
		setfillcolor(BRUSH_COLOR);
		settextcolor(CYAN);
		setbkcolor(BLACK);
		settextstyle(20, 0, _T("黑体"));
		outtextxy(210, 60, "游戏记录:");

		//Cacel键显示
		int x1 = WINDOW_WIDTH / 2 - 50;
		int y1 = WINDOW_HEIGHT * 2 / 3 + 120;
		int x2 = WINDOW_WIDTH / 2 + 50;
		int y2 = WINDOW_HEIGHT * 2 / 3 + 30 + 120;
		settextcolor(RGB(255, 0, 0));
		setbkcolor(RGB(0, 100, 178));
		setfillcolor(RGB(0, 100, 178));

		settextstyle(20, 0, _T("隶书"));
		RECT r1 = { x1,y1,x2,y2 };
		Button btn_Cancel(r1, "Cancel");
		btn_Cancel.show(0);

		RECT r2 = { x1-50,y1 + 40,x2+50,y2 + 40 };
		Button btn_Empty(r2, "Empty Records");
		btn_Empty.show(0);

		RECT r3 = { x1 +150,y1,x2 + 150,y2};
		Button btn_Next(r3, "Next");
		btn_Next.show(0);

		RECT r4 = { x1 - 150,y1,x2 - 150,y2};
		Button btn_Before(r4, "Before");
		btn_Before.show(0);

		RECT r5 = { x1,y1 - 40,x2,y2 - 40 };
		Button btn_Page(r5, "Page: " + to_string(page) + "/" + to_string((record_amount-1)/7 + 1));
		btn_Page.show(0);

		int max = 0;
		int i;
		for (i = 1; datas[i].score != -1; i++) 
		{
			max = max(datas[i].score, max);
		}
		for (i = 1; datas[i + (page-1)*7].score != -1 && i <= 7; i++) {
			outtextxy(x, i * 70 + y, "系统时间:         " + datas[i + (page - 1) * 7].time_T);
			outtextxy(x, i * 70 + y + 20, "游戏用时:         " + datas[i + (page - 1) * 7].time_R);
			outtextxy(x, i * 70 + y + 40, "分数:             " + numToString(datas[i + (page - 1) * 7].score));
			
		}
		if (i == 1)
		{
			outtextxy(x, i * 70 + y, " 空 ");
		}
		outtextxy(210, 80, "最高分:" + numToString(max));
		FlushBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (btn_Cancel.isIn(msg.x,msg.y))
				{
					btn_Cancel.clicked();
					break;
				}
				if (btn_Empty.isIn(msg.x, msg.y))
				{
					btn_Empty.clicked();
					outtextxy(210, 110, "记录清除成功!");
					FlushBatchDraw();
					Sleep(500);
					emptyRecord();//记录清空
					read();//重新读取
					break;//读取后返回主页面
				}
				if (btn_Next.isIn(msg.x, msg.y))
				{
					btn_Next.clicked();
					if (i != 1)
						++page;
					continue;
				}
				if (btn_Before.isIn(msg.x, msg.y))
				{
					btn_Before.clicked();
					if (page != 1)
						--page;
					continue;
				}
			}
		}
	}
	return 1;
}

int putInstructions()
{
	int x = WINDOW_WIDTH - 350;
	int y = 50;
	RECT r = { x+50,y,WINDOW_WIDTH - 20+50 ,WINDOW_HEIGHT-20};
	settextcolor(RGB(0, 100, 200));
	settextstyle(30, 0, "黑体");
	drawtext(_T("操作说明:"), &r, DT_LEFT);
	settextstyle(20, 0, "黑体");
	r.top += 50;
	drawtext(_T("1.WSAD控制水平方向的移动"), &r, DT_LEFT | DT_WORDBREAK);
	r.top += 25;
	drawtext(_T("2.Q切换俄罗斯方块的状态"), &r, DT_LEFT | DT_WORDBREAK);
	r.top += 25;
	drawtext(_T("3.E旋转坐标系"), &r, DT_LEFT | DT_WORDBREAK);
	r.top += 25;
	drawtext(_T("4.按住Shift加速下落"), &r, DT_LEFT | DT_WORDBREAK);
	r.top += 25;
	drawtext(_T("5.P暂停游戏"), &r, DT_LEFT | DT_WORDBREAK);
	r.top += 25;
	drawtext(_T("6.作弊F使用道具直接消除底层(30s冷却时间)"), &r, DT_LEFT | DT_WORDBREAK);

	settextcolor(PEN_COLOR);
	return 1;
}

//保存分数、时间记录
int save()
{
	ofstream ofs(RECORD_FILE,ios::out|ios::app);
	ofs << cdata.time_T << endl;
	ofs << cdata.time_R << endl;
	ofs << cdata.score << endl<<endl;
	ofs.close();
	return 1;
}

//读取分数、时间记录
int read()
{
	//读取前清空datas
	for (int i = 0; i < 10; i++) {
		datas[i].score = -1;
	}
	ifstream ifs(RECORD_FILE, ios::in);
	if (!ifs.is_open()) {
		outtextxy(0, WINDOW_HEIGHT - 30, "fail to read!");
		system("pause");
		return -1;
	}
	string text;
	char buf[1024];
	int row = 0;
	for (int i = 0; ifs.getline(buf, 1024); i++) {
		row++;//统计行数
	}
	int j = 0,i = row+1;
	//memset(buf, 0, 1024);
	for (; i >= 0 && j < 100; i--)
	{
		memset(buf, 0, 1024);
		ReadLineData(RECORD_FILE, i, buf);//从后往前读, 以保持最新记录在前
		text = buf;

		switch (i % 4)
		{
		case 1:
			datas[j].time_T = text;
			break;
		case 2:
			datas[j].time_R = text;
			break;
		case 3:
			datas[j].score = stringToNum(text);
			break;
		case 0:
			j++;
			break;
		}
	}
	record_amount = j;

	ifs.close();
	//outtextxy(WINDOW_WIDTH / 2, WINDOW_HIGHT / 2,text);
	return 1;
}

std::string getRunTime_R()
{

	long deltaTime = clock()/1000 - startTime;
	int s = deltaTime % 60;
	deltaTime /= 60;
	int m = deltaTime % 60;
	deltaTime /= 60;
	int h = deltaTime;
	std::string timeText;
	timeText = numToString(h) + ":" + numToString(m) + ":" + numToString(s);
	return timeText;
}



long getRunTime_Seconds()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	long timeValue;
	timeValue = time.wHour * 3600 + time.wMinute * 60 + time.wSecond;
	return timeValue;
}

std::string getRunTime_HMS()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::string timeText;
	timeText = timeText + numToString(time.wHour) + ":" + numToString(time.wMinute) + ":" + numToString(time.wSecond);
	return timeText;
}

long long getRunTime_Millis()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	long long timeValue;
	timeValue = (long long)time.wHour * 360000 + (long long)time.wMinute * 60000 + (long long)time.wSecond * 1000 + (long long)time.wMilliseconds;
	if (timeValue < 0 || timeValue > 3e8)
	{
		outtextxy(0, 0, "time overwhelmed!");
		getchar();
		exit(-1);
	}
	return timeValue;
}

//删除记录
int deleteRecord(int index)
{
	for (int i = 1; i <= 4; i++) {
		DelLineData(RECORD_FILE, 4 * index + i);
	}
	return 1;
}
//清空记录
int emptyRecord()
{
	ofstream ofs(RECORD_FILE, ios::trunc);
	ofs.close();
	return 1;
}