#include "paint.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include "toString.h"
#include "StartScene.h"
#include "MyData.h"
using namespace std;

extern MyData cdata;

int outtextxy(int x, int y, std::string text)
{
	LPCTSTR text1 = LPCTSTR(text.c_str());
	outtextxy(x, y, text1);
	return 1;
}

int showImage(LPCTSTR path)
{
	if (!isPainting)
	{
		startPaint();
		isPainting = 1;
	}
	IMAGE img;

	loadimage(&img,path, WINDOW_WIDTH, WINDOW_HEIGHT,true);
	putimage(0, 0, &img);
	return 1;
}

int showImage(string path)
{
	LPCTSTR s_path = (LPCTSTR)path.c_str();
	return showImage(s_path);
}

int showScore(int score)
{
	cdata.score = score;
	std::string str = "分数: ";
	str += numToString(score);
	LPCTSTR text = LPCTSTR(str.c_str());
	outtextxy(WINDOW_WIDTH - 100,0,text);
	return score;
}

int startPaint(int bkColor,int penColor)
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	isPainting = 1;
	startTime = getRunTime_Seconds();
	//设置背景颜色
	setbkcolor(bkColor);
	//设置画笔颜色
	setcolor(penColor);
	cleardevice();

	return 1;
}

int paint_Coordinate()
{
	if (!isPainting)
	{
		startPaint();
		outtextxy(0, 20, _T("Start Paint by Auto!"));
		isPainting = 1;
	}
	isCoordinateExit = 1;

	if (isBackgroundImageSet)
		showImage(BACKGROUND_IMAGE);

	//画边框
	paint_Rect(INIT_POINT_X - DELTA * (X_LENGTH + 1), INIT_POINT_Y - UNIT_LENGTH * Z_LENGTH - UNIT_LENGTH / 2,
		INIT_POINT_X + UNIT_LENGTH * Y_LENGTH + UNIT_LENGTH / 2, INIT_POINT_Y + DELTA * (X_LENGTH+1));
	
	//画YOZ面
	for (int i = 0; i <= Y_LENGTH; i++)
	{
		line(INIT_POINT_X + i * UNIT_LENGTH, INIT_POINT_Y,
			INIT_POINT_X + i * UNIT_LENGTH, INIT_POINT_Y - UNIT_LENGTH * Z_LENGTH);
	}
	for (int i = 0; i <= Z_LENGTH; i++)
	{
		line(INIT_POINT_X, INIT_POINT_Y - i * UNIT_LENGTH,
			INIT_POINT_X + UNIT_LENGTH * Y_LENGTH, INIT_POINT_Y - i * UNIT_LENGTH);
	}
	//画XOZ面
	for (int i = 1; i <= X_LENGTH; i++)
	{
		line(INIT_POINT_X - i * DELTA, INIT_POINT_Y + i * DELTA,
			INIT_POINT_X - i * DELTA, INIT_POINT_Y + i * DELTA - Z_LENGTH * UNIT_LENGTH);
	}
	for (int i = 0; i <= Z_LENGTH; i++)
	{
		line(INIT_POINT_X, INIT_POINT_Y - i * UNIT_LENGTH,
			INIT_POINT_X - X_LENGTH * DELTA, INIT_POINT_Y - i * UNIT_LENGTH + X_LENGTH * DELTA);
	}
	//画XOY面
	for (int i = 1; i <= X_LENGTH; i++)
	{
		line(INIT_POINT_X - i * DELTA, INIT_POINT_Y + i * DELTA,
			INIT_POINT_X - i * DELTA + Y_LENGTH * UNIT_LENGTH, INIT_POINT_Y + i * DELTA);
	}
	for (int i = 1; i <= Y_LENGTH; i++)
	{
		line(INIT_POINT_X + i * UNIT_LENGTH, INIT_POINT_Y,
			INIT_POINT_X + i * UNIT_LENGTH - X_LENGTH * DELTA, INIT_POINT_Y + DELTA * X_LENGTH);
	}
	return 1;
}

int clear_Coordinate()
{
	cleardevice();
	if (isCoordinateExit)
		paint_Coordinate();
	return 1;
}

int paint_Rect(int left, int up, int right, int down, int RectColor)
{
	if (!isPainting) return -1;
	setcolor(RectColor);
	LINESTYLE lstyle;
	lstyle.thickness = 2;
	setlinestyle(&lstyle);
	rectangle(left, up, right, down);

	setcolor(PEN_COLOR);
	lstyle.thickness = 1;
	setlinestyle(&lstyle);
	return 1;
}

int paint_Cube(int stx, int sty, int length, int CubeColor,int projectedFace)
{
	if (!isPainting)
	{
		startPaint();
		outtextxy(0, 60, _T("Start Paint by Auto!"));
		isPainting = 1;
	}
	if (CubeColor == PEN_COLOR)
	{
		outtext(_T("Error: Color Overlapped!"));
		return -1;
	}

	//设置填充色
	setfillcolor(CubeColor);

	//计算正面左下点
	int delta = (double)length / 2 / sqrt(2);
	int px = stx - delta;
	int py = sty + delta;

	//开始画立方体
	rectangle(px, py, px + length, py - length);
	moveto(px + length, py);
	lineto(px + length + delta, py - delta);
	lineto(px + length + delta, py - delta - length);
	lineto(px + delta, py - delta - length);
	lineto(px, py - length);
	moveto(px + length, py - length);
	lineto(px + length + delta, py - length - delta);

	//填充颜色
	if (projectedFace != _YOZ_FACE)
	{
		//填充正面
		fillrectangle(px, py, px + length, py - length);
	}

	if (projectedFace != _XOY_FACE)
	{
		//填充上面
		int point1[8] =
		{
			px,py - length,
			px + delta,py - length - delta,
			px + delta + length,py - length - delta,
			px + length,py - length
		};
		fillpoly(4, point1);
	}

	if (projectedFace != _XOZ_FACE)
	{
		//填充右面
		int point2[8] =
		{
			px + length,py - length,
			px + length + delta,py - length - delta,
			px + length + delta,py - delta,
			px + length,py
		};
		fillpoly(4, point2);
	}


	return 1;
}

int*** init_CubeArr(int xLength, int yLength, int zLength)
{
	int*** arr;
	if ((arr = (int***)malloc(sizeof(int**) * xLength)) == NULL)
	{
		outtext(_T("初始化立方体数组错误！"));
		exit(-1);
	}
	for (int i = 0; i < xLength; i++)
	{
		if ((arr[i] = (int**)malloc(sizeof(int*) * yLength)) == NULL)
		{
			outtext(_T("初始化立方体数组错误！"));
			exit(-1);
		}
			for (int j = 0; j < yLength; j++)
			{
				if ((arr[i][j] = (int*)malloc(sizeof(int) * zLength)) == NULL)
				{
					outtext(_T("初始化立方体数组错误！"));
					exit(-1);
				}
			}
	}

	for (int i = 0; i < xLength; i++)
		for (int j = 0; j < yLength; j++)
			for (int k = 0; k < zLength; k++)
				arr[i][j][k] = 0;


	return arr;
}

void free_CubeArr(int*** cubeArr,int xLength, int yLength)
{
	for (int i = 0; i < xLength; i++)
	{
		for (int j = 0; j < yLength; j++)
		{
			free(cubeArr[i][j]);
		}
		free(cubeArr[i]);
	}
	free(cubeArr);
	outtextxy(0,WINDOW_HEIGHT-20,_T("释放cubeArr成功!"));
	return;
}

int summonCube(int*** arr, int num, int colorValue)
{
	//生成num个不与其他地方重合的立方体(不相连)
	for (int i = 0; i < num; i++)
	{
		while (1)
		{
			int x = rand() % X_LENGTH;
			int y = rand() % Y_LENGTH;
			if (!arr[x][y][Z_LENGTH - 1])
			{
				arr[x][y][Z_LENGTH - 1] = colorValue;
				break;
			}
		}
	}
	
	return 1;
}

int fall(int*** arr,int bottom)
{
	if (bottom < 0 || bottom >= Z_LENGTH)
	{
		outtextxy(0, 40, "error:bottom wrong!");
		getchar();
		exit(-1);
	}

	//bottom上的方块下落，不影响bottom本身
	for (int i = bottom+1; i < Z_LENGTH; i++)
	{
		for (int j = 0; j < X_LENGTH; j++)
		{
			for (int k = 0; k < Y_LENGTH; k++)
			{
				if (arr[j][k][i] && !arr[j][k][i - 1])
				{
					arr[j][k][i - 1] = arr[j][k][i];
					arr[j][k][i] = 0;
				}
			}
		}
	}

	return 1;
}

int fall(int*** arr, int x, int y, int z)
{
	arr[x][y][z - 1] = arr[x][y][z];
	return 1;
}

int isLayerOverflowed(int***arr,int z)
{
	for (int i = 0; i < X_LENGTH; i++)
	{
		for (int j = 0; j < Y_LENGTH; j++)
		{
			if (!arr[i][j][z])
			return 0;
		}
	}
	return 1;
}

int* getOverflowedLayer(int*** arr)
{
	int* overArr = (int*)calloc(Z_LENGTH,sizeof(int));
	for (int i = 0; i < Z_LENGTH; i++)
	{
		if (isLayerOverflowed(arr, i)) overArr[i] = 1;
		else break;
	}
	return overArr;
}

int paint_Cube(int*** arr, int length)
{
	if (!isPainting)
	{
		startPaint();
		outtextxy(0, 40, _T("Start Paint by Auto!"));
		isPainting = 1;
	}
	if (arr == NULL || *arr == NULL || **arr == NULL)
	{
		outtext(_T("立方体数组传入有误！"));
		exit(-1);
	}
	for (int x = 0; x < X_LENGTH; x++)
	{
		for (int y = 0; y < Y_LENGTH; y++)
		{
			for (int z = 0; z < Z_LENGTH; z++)
			{
				if (!arr[x][y][z]) continue;
				int point_x = INIT_POINT_X - x * DELTA + y * UNIT_LENGTH;
				int point_y = INIT_POINT_Y + x * DELTA - z * UNIT_LENGTH;
				switch (arr[x][y][z]%10)
				{
				default:
				case _RED_VALUE:
					paint_Cube(point_x, point_y, length, RED);
					break;
				case _BLUE_VALUE:
					paint_Cube(point_x, point_y, length, BLUE);
					break;
				case _GREEN_VALUE:
					paint_Cube(point_x, point_y, length, GREEN);
					break;
				case _MAGENTA_VALUE:
					paint_Cube(point_x, point_y, length, MAGENTA);
					break;
				case _BROWN_VALUE:

					paint_Cube(point_x, point_y, length, BROWN);
					break;
				case _YELLOW_VALUE:
					paint_Cube(point_x, point_y, length, YELLOW);
					break;
				case _PROJECT_COLOR_VALUE:
					paint_Cube(point_x, point_y, length, _PROJECT_COLOR);
				}

				if (arr[x][y][z] / 10)
					setfillcolor(RGB(50,50,50));//较深一点的青色
				if (arr[x][y][z] / 10 == 1)//正面被投影到
				{
					int p_a_1[8] = {
						point_x - DELTA,point_y + DELTA,
						point_x - DELTA + UNIT_LENGTH,point_y + DELTA,
						point_x - DELTA + UNIT_LENGTH, point_y + DELTA - UNIT_LENGTH,
						point_x - DELTA, point_y + DELTA - UNIT_LENGTH
					};
					fillpoly(4, p_a_1);
				}

				if (arr[x][y][z] / 100 == 1)//侧面被投影到
				{
					int p_a_2[8] = {
						point_x + UNIT_LENGTH - DELTA,point_y + DELTA,
						point_x + UNIT_LENGTH,point_y,
						point_x + UNIT_LENGTH, point_y - UNIT_LENGTH,
						point_x + UNIT_LENGTH - DELTA, point_y - UNIT_LENGTH + DELTA
					};
					fillpoly(4, p_a_2);
				}

				if (arr[x][y][z] / 1000 == 1)//上面
				{
					int p_a_3[8] = {
						point_x , point_y - UNIT_LENGTH,
						point_x + UNIT_LENGTH, point_y - UNIT_LENGTH,
						point_x + UNIT_LENGTH -DELTA, point_y - UNIT_LENGTH + DELTA,
						point_x -DELTA, point_y - UNIT_LENGTH + DELTA
					};
					fillpoly(4, p_a_3);
				}
			}
		}
	}
	return 1;
}

int paint_Tetris(Tetris& tetris)
{
	int num = 0;
	for (int i = 0; tetris.m_Arr[i] != -1; i += 3)
	{
		int _x = tetris.m_Arr[i];
		int _y = tetris.m_Arr[i + 1];
		int _z = tetris.m_Arr[i + 2];
		int stx = INIT_POINT_X - _x * DELTA + _y * UNIT_LENGTH;
		int sty = INIT_POINT_Y - _z * UNIT_LENGTH + _x * DELTA;
		int color;
		switch (tetris.m_ColorValue)
		{
		case _RED_VALUE:
			color = RED;
			break;
		case _BROWN_VALUE:
			color = BROWN;
			break;
		case _BLUE_VALUE:
			color = BLUE;
			break;
		case _MAGENTA_VALUE:
			color = MAGENTA;
			break;
		case _YELLOW_VALUE:
			color = YELLOW;
			break;
		case _GREEN_VALUE:
			color = GREEN;
			break;
		}
		paint_Cube(stx, sty,UNIT_LENGTH,color);
		num++;
	}
	return num;
}

int paint_Tetris(Tetris& tetris, int x, int y)
{
	int num = 0;
	for (int i = 0; tetris.m_Arr[i] != -1; i += 3)
	{
		int color;
		int stx = x - (tetris.m_Arr[i] - tetris.centreBlockPosition[0]) * DELTA + (tetris.m_Arr[i + 1] - tetris.centreBlockPosition[1])*UNIT_LENGTH;
		int sty = y + (tetris.m_Arr[i] - tetris.centreBlockPosition[0]) * DELTA - (tetris.m_Arr[i+2] - tetris.centreBlockPosition[2]) * UNIT_LENGTH;
		switch (tetris.m_ColorValue)
		{
		case _RED_VALUE:
			color = RED;
			break;
		case _BROWN_VALUE:
			color = BROWN;
			break;
		case _BLUE_VALUE:
			color = BLUE;
			break;
		case _MAGENTA_VALUE:
			color = MAGENTA;
			break;
		case _YELLOW_VALUE:
			color = YELLOW;
			break;
		case _GREEN_VALUE:
			color = GREEN;
			break;
		}
		paint_Cube(stx, sty, UNIT_LENGTH, color);
		num++;
	}
	return num;
}

int paint_Test()
{
	if (!isPainting)
	{
		startPaint();
		outtextxy(0, 20, _T("Start Paint by Auto!     penColor:CYAN      backgroundColor:BLACK"));
	}
	int*** arr = init_CubeArr();
	outtextxy(0, 0, _T("测试z轴方向paint"));
	for (int k = 0; k < Z_LENGTH; k++)
	{
		arr[0][0][k] = _RED_VALUE;
	}
	paint_Cube(arr);
	free_CubeArr(arr);
	getchar();
	clear_Coordinate();

	arr = init_CubeArr();
	outtextxy(0, 0, _T("测试x轴方向paint"));
	for (int i = 0; i < X_LENGTH; i++)
	{
		arr[i][0][0] = _RED_VALUE;
	}
	paint_Cube(arr);
	free_CubeArr(arr);
	getchar();
	clear_Coordinate();

	arr = init_CubeArr();
	outtextxy(0, 0, _T("测试y轴方向paint"));
	for (int j = 0; j < Y_LENGTH; j++)
	{
		arr[0][j][0] = _RED_VALUE;
	}
	paint_Cube(arr);
	free_CubeArr(arr);
	getchar();
	isCoordinateExit = 0;
	clear_Coordinate();

	return 1;
}

int image_Test()
{
	isBackgroundImageSet = 1;
	showImage(_T(BASE_PATH "01.jpg"));
	outtextxy(0, 0, _T("Image Output Successfully!"));
	return 1;
}

int endPaint(int***arr)
{
	if (isPainting)
	{
		closegraph();
		isPainting = 0;
	}
	else
	{
		outtextxy(0, 0, "error!");
	}
	isCoordinateExit = 0;
	isBackgroundImageSet = 0;
	//释放立方体数组
	if (arr != NULL)
	{
		for (int i = 0; i < X_LENGTH; i++)
		{
			for (int j = 0; j < Y_LENGTH; j++)
			{
				free(arr[i][j]);
			}
			free(arr[i]);
		}
		free(arr);
	}

	return 1;
}

int showTime(int x,int y)
{
	cdata.time_T = getRunTime_HMS();
	outtextxy(x, y, "系统时间:" + cdata.time_T);
	return 1;
}

int showRunTime(int x, int y)
{
	cdata.time_R = getRunTime_R();
	outtextxy(x, y, "用时:"+ cdata.time_R);
	return 1;
}

int update(int***arr,int score,Tetris& tetris, Tetris* pre_tetris)
{
	outtextxy(0, 40, "中心方块坐标:"+numToString(tetris.centreBlockPosition[0]) + " "
		+ numToString(tetris.centreBlockPosition[1]) + " "
		+ numToString(tetris.centreBlockPosition[2]));//对中心方块的坐标指示
	putInstructions();//提示说明
	tetris.removeFromCubeArr(arr);//Tetris移出坐标系，以便于做接下来的操作
	tetris.project_OnAxis(arr);//画上投影
	tetris.project_OffCube(arr);//重置投影
	tetris.project_OnCube(arr);//投影至方块
	tetris.addToCubeArr(arr);//Tetris添加至坐标系
	paint_Cube(arr);//画坐标系内的所有方块

	/*绘制示意图*/
	outtextxy(30, 100, "当前方块: ");
	setfillcolor(CYAN);
	fillrectangle(155, 75, 350, 220);
	paint_Tetris(tetris, 250, 150);//绘制Tetris示意图
	if (pre_tetris)
	{
		outtextxy(30, 275, "下一个方块:");
		setfillcolor(CYAN);
		fillrectangle(155, 250, 350, 400);
		paint_Tetris(*pre_tetris, 250, 330);
	}

	showTime(0,0);//显示系统时间
	showRunTime(200, 0);//显示运行时间
	showScore(score);//显示分数
	FlushBatchDraw();//从缓冲区输出到屏幕
	return 1;
}
