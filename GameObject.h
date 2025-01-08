#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#ifndef _RED_VALUE
#define _RED_VALUE		1
#endif

#include "CONSTANT_NAME_DEFINE.h"

/// <summary>////////////////
/// by 光电2215 ##--##
/// Class Tetris
/// 属性：
/// 1.颜色
/// 2.所有方块的坐标
/// 3.中心方块的坐标
/// 4.是否活跃
/// 5.状态、形状
/// 
/// 行为:
/// 1.设置状态/形状
/// 2.加入立方体数组
/// 3.移出立方体数组
/// 4.获取边界
/// 5.下落
/// 6.旋转
/// 7.投影
/// 8.水平移动
/// </summary>/////////////

struct Tetris
{
	//属性
	int m_Arr[3 * TERRIS_MAX_SIZE];//一个俄罗斯方块中所包括的所有立方体的坐标
	int isActive;//是否活跃的标志
	int m_ColorValue;//颜色
	int m_State;//状态
	int centreBlockPosition[3] = { 0,0,Z_LENGTH - 2 };//中心方块坐标
	//行为
	Tetris();//默认初始化为O型方块
	Tetris(int position_x, int position_y, int state = _BAR_VERTICAL, int color = _RED_VALUE);//带参数坐标的初始化
	int setState(int state);//设置状态
	int addToCubeArr(int***arr);//加入立方体数组
	int removeFromCubeArr(int*** arr);//移出立方体数组，便于投影、移动、旋转操作的判定
	int getBoard(int mode);//获取边界
	int move(ExMessage &msg,int***arr);//判断是否可移动，若可，则移动
	int canRotate(int***arr);//判断可否旋转
	int rotate();//预旋转，方便检测是否可旋转
	int rotate(int*** arr);//旋转
	int fall(int***arr);//下落
	int project_OnAxis(int***arr);//投影至坐标系
	int project_OnCube(int*** arr);//投影至方块
	int project_OffCube(int*** arr);//解除方块的投影
};

//消除底部填满的层,并整体下移
int killLayer(int*** arr, int* overArr, int delayTime = 0);
//旋转坐标系
int rotateAxis(int***& arr);

#endif