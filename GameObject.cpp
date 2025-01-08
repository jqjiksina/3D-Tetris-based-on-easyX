#include "GameObject.h"
#include "paint.h"

//初始化俄罗斯立方体
Tetris::Tetris(int position_x, int position_y, int state, int color)
{
	this->isActive = 1;
	for (int i = 0; i < 3 * TERRIS_MAX_SIZE; i++)
	{
		this->m_Arr[i] = -1;
	}
	this->centreBlockPosition[0] = position_x;
	this->centreBlockPosition[1] = position_y;
	this->setState(state);
	switch (color)
	{
	case RED:
	case _RED_VALUE:
		this->m_ColorValue = _RED_VALUE;
		break;
	case BLUE:
	case _BLUE_VALUE:
		this->m_ColorValue = _BLUE_VALUE;
		break;
	case GREEN:
	case _GREEN_VALUE:
		this->m_ColorValue = _GREEN_VALUE;
		break;
	case BROWN:
	case _BROWN_VALUE:
		this->m_ColorValue = _BROWN_VALUE;
		break;
	case _MAGENTA_VALUE:
	case MAGENTA:
		this->m_ColorValue = _MAGENTA_VALUE;
		break;
	case YELLOW:
	case _YELLOW_VALUE:
		this->m_ColorValue = _YELLOW_VALUE;
		break;
	}
}

//旋转时切换状态及初始化时需要设置状态
int Tetris::setState(int state)
{
	this->m_State = state;//存储当前状态，作为转换依据
	int x = this->centreBlockPosition[0];
	int y = this->centreBlockPosition[1];
	int z = this->centreBlockPosition[2];
	int num = 0;
	//要注意判断是否越界
	//柱状(I型)
	switch (state)
	{
	case _BAR_VERTICAL:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 2;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _BAR_X_ORIENT:
		this->m_Arr[num++] = x - 2;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _BAR_Y_ORIENT:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 2;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z;
		break;
	}
	//田型(O型)
	switch (state)
	{
	case _TIAN:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	}
	//Z型
	switch (state)
	{
	case _Z_STATE_1:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z;
		break;
	case _Z_STATE_2:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;
		break;
	case _Z_STATE_3:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z - 1;
		break;
	case _Z_STATE_4:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _Z_STATE_5:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z + 1;
		break;
	case _Z_STATE_6:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _Z_STATE_7:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _Z_STATE_8:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	}
	//LAZY_Z型
	switch (state) 
	{
	case _Z_LAZY_STATE_1:
		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _Z_LAZY_STATE_2:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _Z_LAZY_STATE_3:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;
		break;
	case _Z_LAZY_STATE_4:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;
		break;
	}
	//L型
	switch (state)
	{
	case _L_STATE_1:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_2:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_3:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_4:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_5:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_6:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_7:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _L_STATE_8:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	}
	//LAZY_L型
	switch (state)
	{
	case _L_LAZY_STATE_1:
		this->m_Arr[num++] = x-2;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;
		break;
	case _L_LAZY_STATE_2:
		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-2;
		this->m_Arr[num++] = z ;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y -1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _L_LAZY_STATE_3:
		this->m_Arr[num++] = x-1 ;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;
		break;
	case _L_LAZY_STATE_4:

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;
		break;
	}
	//T型
	switch (state)
	{
	case _T_STATE_1:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _T_STATE_2:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	case _T_STATE_3:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z + 1;
		break;
	case _T_STATE_4:
		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z - 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z + 1;
		break;
	}
	//LAZY_T型
	switch (state)
	{
	case _T_LAZY_STATE_1:
		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y + 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z ;
		break;
	case _T_LAZY_STATE_2:
		this->m_Arr[num++] = x-1;
		this->m_Arr[num++] = y - 1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x + 1;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;
		break;
	case _T_LAZY_STATE_3:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y +1;
		this->m_Arr[num++] = z;
		break;
	case _T_LAZY_STATE_4:
		this->m_Arr[num++] = x - 1;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y-1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x;
		this->m_Arr[num++] = y+1;
		this->m_Arr[num++] = z;

		this->m_Arr[num++] = x+1;
		this->m_Arr[num++] = y +1;
		this->m_Arr[num++] = z;
		break;
	}

	return 1;
}

int Tetris::addToCubeArr(int***arr)
{
	removeFromCubeArr(arr);
	int i;
	for (i = 0; this->m_Arr[i] != -1 && i < 3 * TERRIS_MAX_SIZE; i+=3)
	{
		if (arr[this->m_Arr[i]][this->m_Arr[i+1]][this->m_Arr[i+2]])
		{
			outtextxy(80, 0, _T("Tetris addToCubeArr error!"));
			//system("pause");
			return -1;
		}
		arr[this->m_Arr[i]][this->m_Arr[i + 1]][this->m_Arr[i + 2]] = this->m_ColorValue;
	}
	//返回填充的个数
	return i/3;
}

int Tetris::removeFromCubeArr(int*** arr)
{
	int i;
	for (i = 0; this->m_Arr[i] != -1 && i < 3 * TERRIS_MAX_SIZE; i += 3)
	{
		arr[this->m_Arr[i]][this->m_Arr[i + 1]][this->m_Arr[i + 2]] = 0;
	}
	//返回填充的个数
	return i / 3;
}

int killLayer(int*** arr, int* overarr, int delayTime)
{
	int count = 0;
	for (int i = 0; i < Z_LENGTH; i++) {
		if (overarr[i]) {
			count++;
			//播放音效
			mciSendString("stop " SOUND_EFFECT_3, 0, 0, 0);
			mciSendString("close " SOUND_EFFECT_3, 0, 0, 0);
			mciSendString("open " SOUND_EFFECT_3, 0, 0, 0);
			mciSendString("play " SOUND_EFFECT_3, 0, 0, 0);
			FlushBatchDraw();
			Sleep(delayTime);
			//清空i层
			for (int j = 0; j < X_LENGTH; j++) {
				for (int k = 0; k < Y_LENGTH; k++) {
					arr[j][k][i] = 0;
				}
			}
			fall(arr, i);
		}
	}
	return count;
}

int rotateAxis(int***& arr)
{
	if (X_LENGTH != Y_LENGTH)
	{
		outtextxy(0, 80, "fail to rotate!");
		FlushBatchDraw();
		return -1;
	}
	int*** temp = init_CubeArr();
	for (int k = 0; k < Z_LENGTH; k++) {//先把每一层转好
		for (int i = 0; i < X_LENGTH; i++) {
			for (int j = 0; j < Y_LENGTH; j++) {
				temp[i][j][k] = arr[X_LENGTH - 1 - j][i][k];
			}
		}
	}
	free(arr);
	arr = temp;//重新建立指向
	return 1;
}

int Tetris::getBoard(int mode)
{
	int x_max = 0;
	int x_min = X_LENGTH - 1;
	int y_max = 0;
	int y_min = Y_LENGTH - 1;
	switch (mode)
	{
	case _GET_X_MIN:

		for (int i = 0; this->m_Arr[i] != -1; i+=3)
		{
			x_min = _GET_MIN(x_min, this->m_Arr[i]);
		}
		return x_min;
		break;
	case _GET_X_MAX:

		for (int i = 0; this->m_Arr[i] != -1; i += 3)
		{
			x_max = _GET_MAX(x_max, this->m_Arr[i]);
		}
		return x_max;
		break;
	case _GET_Y_MIN:
		for (int i = 1; this->m_Arr[i] != -1; i += 3)
		{
			y_min = _GET_MIN(y_min, this->m_Arr[i]);
		}
		return y_min;
		break;
	case _GET_Y_MAX:

		for (int i = 1; this->m_Arr[i] != -1; i += 3)
		{
			y_max = _GET_MAX(y_max, this->m_Arr[i]);
		}
		return y_max;
		break;
	}
	return -1;
}

int Tetris::move(ExMessage &msg,int***arr)
{
	outtextxy(0, 80, msg.vkcode);
	switch (msg.vkcode)
	{
	case _A_KEY:
		//判断是否能左移
		if (this->getBoard(_GET_Y_MIN) <= 0) return 0;
		this->removeFromCubeArr(arr);
		for (int i = 1; m_Arr[i] != -1;  i += 3)
		{
			if (arr[m_Arr[i - 1]][m_Arr[i] - 1][m_Arr[i + 1]])
			{
				this->addToCubeArr(arr);
				return 0;
			}
		}
		this->centreBlockPosition[1]--;
		for (int i = 1; this->m_Arr[i] != -1; i += 3)
		{
			this->m_Arr[i]--;
		}
		this->addToCubeArr(arr);
		return 1;
		break;
	case _D_KEY:
	
		if (this->getBoard(_GET_Y_MAX) >= Y_LENGTH - 1) return 0;
		this->removeFromCubeArr(arr);
		
		for (int i = 1; m_Arr[i] != -1; i+=3)
		{
			//判断能否移动逻辑！
			if (arr[m_Arr[i - 1]][m_Arr[i] + 1][m_Arr[i + 1]])
			{
				this->addToCubeArr(arr);
				return 0;
			}
		}
		this->centreBlockPosition[1]++;
		for (int i = 1; this->m_Arr[i] != -1; i += 3)
		{
			this->m_Arr[i]++;
		}
		this->addToCubeArr(arr);
		return 2;
		break;
	case _W_KEY:
		if (this->getBoard(_GET_X_MIN) <= 0) return 0;
		this->removeFromCubeArr(arr);
		
		for (int i = 1; m_Arr[i] != -1;  i += 3)
		{
			if (arr[m_Arr[i - 1] - 1][m_Arr[i]][m_Arr[i + 1]])
			{
				this->addToCubeArr(arr);
				return 0;
			}
		}
		this->centreBlockPosition[0]--;
		for (int i = 0; this->m_Arr[i] != -1; i += 3)
		{
			this->m_Arr[i]--;
		}
		this->addToCubeArr(arr);
		return 3;
		break;
	case _S_KEY:

		if (this->getBoard(_GET_X_MAX) >= X_LENGTH - 1) return 0;
		this->removeFromCubeArr(arr);
		
		for (int i = 1; m_Arr[i] != -1;  i += 3)
		{
			if (arr[m_Arr[i - 1] + 1][m_Arr[i]][m_Arr[i + 1]])
			{
				this->addToCubeArr(arr);
				return 0;
			}
		}
		this->centreBlockPosition[0]++;
		for (int i = 0; this->m_Arr[i] != -1; i += 3)
		{
			this->m_Arr[i]++;
		}
		this->addToCubeArr(arr);
		return 4;
		break;
	default:
		this->addToCubeArr(arr);
		return -1;
	}
}

int Tetris::fall(int***arr)
{
	if (this->isActive == 0)return 0;

	//下落前判断
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		if (arr[this->m_Arr[i]][this->m_Arr[i + 1]][this->m_Arr[i + 2] - 1])
		{
			this->isActive = 0;
			return 0;
		}
	}
	

	for (int i = 2; this->m_Arr[i] != -1; i += 3)
	{
		this->m_Arr[i]--;
	}
	this->centreBlockPosition[2]--;
	return 1;
}

//调用投影前记得removeFromArr
int Tetris::project_OnAxis(int***arr)
{
	//设置填充色为线的颜色
	setfillcolor(PEN_COLOR);
	//向XOZ投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-Y方向遍历
		for (int j = y; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[x][j][z])
			{
				goto project_YOZ;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				point[index++] = INIT_POINT_X + j * UNIT_LENGTH - x * DELTA;
				point[index++] = INIT_POINT_Y - z * UNIT_LENGTH + x * DELTA;
			}
		}
		//根据基点推出其他三点
		point[index++] = point[0];
		point[index++] = point[1] - UNIT_LENGTH;
		point[index++] = point[0] - DELTA;
		point[index++] = point[1] - UNIT_LENGTH + DELTA;
		point[index++] = point[0] - DELTA;
		point[index++] = point[1] + DELTA;
		fillpoly(4, point);
	project_YOZ:;
	}
	//向YOZ投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-X方向遍历
		for (int j = x; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[j][y][z])
			{
				goto project_XOY;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				point[index++] = INIT_POINT_X + y * UNIT_LENGTH - j * DELTA;
				point[index++] = INIT_POINT_Y - z * UNIT_LENGTH + j * DELTA;
			}
		}
		point[index++] = point[0];
		point[index++] = point[1] - UNIT_LENGTH;
		point[index++] = point[0] + UNIT_LENGTH;
		point[index++] = point[1] - UNIT_LENGTH;
		point[index++] = point[0] + UNIT_LENGTH;
		point[index++] = point[1];
		fillpoly(4, point);
	project_XOY:;
	}
	//向XOY投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-Z方向遍历
		for (int j = z; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[x][y][j])
			{
				goto end;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				point[index++] = INIT_POINT_X + y * UNIT_LENGTH - x * DELTA;
				point[index++] = INIT_POINT_Y - j * UNIT_LENGTH + x * DELTA;
			}
		}
		point[index++] = point[0] + UNIT_LENGTH;
		point[index++] = point[1];
		point[index++] = point[0] + UNIT_LENGTH - DELTA;
		point[index++] = point[1] + DELTA;
		point[index++] = point[0] - DELTA;
		point[index++] = point[1] + DELTA;
		fillpoly(4, point);
	end:;
	}
	return 3;
}

int Tetris::project_OffCube(int*** arr)
{
	//先消除先前的投影
	for (int i = 0; i < X_LENGTH; i++) {
		for (int j = 0; j < Y_LENGTH; j++) {
			for (int k = 0; k < Z_LENGTH; k++) {
				arr[i][j][k] %= 10;
			}
		}
	}
	return 1;
}

int Tetris::project_OnCube(int*** arr)
{
	//向XOZ投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)//对每一个所含方块投影
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-Y方向遍历
		for (int j = y - 1; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[x][j][z])
			{
				arr[x][j][z] = arr[x][j][z] % 10 + 100;//向侧面投影的值
				break;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				break;
			}
		}
	}

	//向YOZ投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-X方向遍历
		for (int j = x - 1; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[j][y][z])
			{
				arr[j][y][z] = arr[j][y][z] % 10 + 10;//向正面投影的值
				break;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				break;
			}
		}
	}
	//向XOY投影
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int index = 0;
		int point[8];
		int x = this->m_Arr[i];
		int y = this->m_Arr[i + 1];
		int z = this->m_Arr[i + 2];
		//向-Z方向遍历
		for (int j = z - 1; j >= 0; j--)
		{
			//检测到第一个方块，停止遍历
			if (arr[x][y][j])
			{
				arr[x][y][j] = arr[x][y][j] % 10 + 1000;//向上面投影的值
				break;
			}
			//检测到坐标平面，停止遍历
			if (j == 0)
			{
				break;
			}
		}
	}
	return 3;
}

Tetris::Tetris()
{
}

int Tetris::canRotate(int***arr)
{
	Tetris temp = *this;
	this->removeFromCubeArr(arr);
	temp.rotate();//临时变量判断旋转后是否合法
	for (int i = 0; this->m_Arr[i] != -1; i += 3)
	{
		int x = temp.m_Arr[i];
		int y = temp.m_Arr[i + 1];
		if (x < 0 || x >= X_LENGTH || y < 0 || y >= Y_LENGTH || temp.m_Arr[i+2] < 0)
		{
			this->addToCubeArr(arr);
			return 0;
		}
		if (arr[temp.m_Arr[i]][temp.m_Arr[i + 1]][temp.m_Arr[i + 2]])
		{
			this->addToCubeArr(arr);
			return 0;
		}

	}
	return 1;
}

int Tetris::rotate()
{

	int r1 = this->m_State / 10;
	int r2 = this->m_State % 10;
	switch (r1)
	{
	case 0://I形
		setState(this->m_State = r1 * 10 + (r2) % 3+1);
		break;
	case 1://O型
		break;
	case 2://Z型
		setState(this->m_State = r1 * 10 + (r2) % 8 + 1);
		break;
	case 3://L型
		setState(this->m_State = r1 * 10 + (r2 ) % 8 + 1);
		break;
	case 4://T型
		setState(this->m_State = r1 * 10 + (r2 ) % 4 + 1);
		break;
	case 5://LAZY_Z型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	case 6://LAZY_L型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	case 7://LAZY_T型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	}
	return 1;
}

int Tetris::rotate(int*** arr)
{
	this->removeFromCubeArr(arr);
	int r1 = this->m_State / 10;
	int r2 = this->m_State % 10;
	switch (r1)
	{
	case 0://I形
		setState(this->m_State = r1 * 10 + (r2) % 3 + 1);
		break;
	case 1://O型
		break;
	case 2://Z型
		setState(this->m_State = r1 * 10 + (r2 ) % 8 + 1);
		break;
	case 3://L型
		setState(this->m_State = r1 * 10 + (r2 ) % 8 + 1);
		break;
	case 4://T型
		setState(this->m_State = r1 * 10 + (r2 ) % 4 + 1);
		break;
	case 5://LAZY_Z型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	case 6://LAZY_L型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	case 7://LAZY_T型
		setState(this->m_State = r1 * 10 + (r2) % 4 + 1);
		break;
	}
	this->addToCubeArr(arr);
	return 1;
}