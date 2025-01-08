#ifndef _CONSTANT_NAME_DEFINE_H
#define _CONSTANT_NAME_DEFINE_H

#include "easyX.h"
#include "MyData.h"

///////////////<summry>/////////////
// by 光电2215 ##--##
// 涵盖整个程序的宏定义以及全局变量的声明
// 便于后期的维护
///////////////////////////////////

//结构体声明
extern struct Tetris;

#pragma region	全局变量
extern int X_LENGTH;
extern int Y_LENGTH;
extern MyData cdata;
extern MyData datas[100];
extern int difficulty;
extern int INTER_TIME;
extern int RANDOM_STATE[36];
extern int SEED_NUM;
extern int SURPRISE;
extern int SURPRISE_TIME;
extern int isBackgroundImageSet;
extern int isPainting;
extern int isCoordinateExit;
extern int score;
extern int record_amount;
extern long startTime;

//游戏全局设置
extern bool SoundEffectOn;
extern bool MusicOn;

extern Tetris t_t;
extern int*** t_a;
#pragma endregion

#pragma region GameObject

#define UNIT_LENGTH				38
//#define X_LENGTH				6
//#define Y_LENGTH				6
#define Z_LENGTH				16
#define INIT_POINT_X			600
#define INIT_POINT_Y			660
#define DELTA					UNIT_LENGTH/2/sqrt(2)
#define TERRIS_MAX_SIZE			10

#define _BAR_VERTICAL			1
#define _BAR_Z_ORIENT			1
#define _BAR_X_ORIENT			2
#define _BAR_Y_ORIENT			3
#define _I_Z_ORIENT				1
#define _I_X_ORIENT				2
#define _I_Y_ORIENT				3
#define _I_STATE(state)			(state)
#define _TIAN					11
#define _Z_STATE_1				21
#define _Z_STATE_2				22
#define _Z_STATE_3				23
#define _Z_STATE_4				24
#define _Z_STATE_5				25
#define _Z_STATE_6				26
#define _Z_STATE_7				27
#define _Z_STATE_8				28
#define _Z_STATE(state)			(20+state)
#define _L_STATE_1				31
#define _L_STATE_2				32
#define _L_STATE_3				33
#define _L_STATE_4				34
#define _L_STATE_5				35
#define _L_STATE_6				36
#define _L_STATE_7				37
#define _L_STATE_8				38
#define _L_STATE(state)			(30+state)
#define _T_STATE_1				41
#define _T_STATE_2				42
#define _T_STATE_3				43
#define _T_STATE_4				44
#define _T_STATE(state)			(40+state)

#define _Z_LAZY_STATE_1			51
#define _Z_LAZY_STATE_2			52
#define _Z_LAZY_STATE_3			53
#define _Z_LAZY_STATE_4			54
#define _Z_LAZY_STATE(state)	(50+state)
#define _L_LAZY_STATE_1			61
#define	_L_LAZY_STATE_2			62
#define	_L_LAZY_STATE_3			63
#define	_L_LAZY_STATE_4			64
#define _L_LAZY_STATE(state)	(60+state)
#define _T_LAZY_STATE_1			71
#define _T_LAZY_STATE_2			72
#define _T_LAZY_STATE_3			73
#define _T_LAZY_STATE_4			74
#define _T_LAZY_STATE(state)	(70+state)

#define _I2_X_ORIENT			81
#define _I2_Y_ORIENT			82
#define _I2

#define _A_KEY					0x41
#define _D_KEY					0x44
#define _W_KEY					0x57
#define _S_KEY					0x53
#define _P_KEY					0x50//暂停
#define _Q_KEY					0x51//旋转Tetris
#define _E_KEY					0x45//旋转坐标系
#define _Y_KEY					0x59//是
#define _N_KEY					0x4E//否
#define _F_KEY					0x46//使用道具
#define _SHIFT_KEY				0x10//加速

#define _GET_X_MIN				1
#define _GET_X_MAX				2
#define _GET_Y_MIN				3
#define _GET_Y_MAX				4

#define _GET_MIN(a,b) (a < b ? a : b)
#define _GET_MAX(a,b) (a > b ? a : b)

#pragma endregion

#pragma region paint

#define WINDOW_WIDTH				1300
#define WINDOW_HEIGHT				800

#define BACKGROUND_COLOR            BLACK
#define PEN_COLOR					CYAN
#define BRUSH_COLOR					RED
#define RECT_COLOR					BLUE
#define _PROJECT_COLOR				CYAN

#define _RED_VALUE					1
#define _BLUE_VALUE					2
#define _GREEN_VALUE				3
#define _MAGENTA_VALUE				4
#define _BROWN_VALUE				5
#define _YELLOW_VALUE				6
#define _PROJECTED_V(colorvalue)	colorvalue+10
#define _PROJECTED_W(colorvalue)	colorvalue+20
#define _PROJECTED_H(colorvalue)	colorvalue+30

#define _PROJECT_COLOR_VALUE		7

#define _YOZ_FACE					1
#define _XOZ_FACE					2
#define _XOY_FACE					3

#pragma endregion

#define MUSIC_1						"resource/BGM/01.mp3"
#define MUSIC_2						"resource/BGM/02.mp3"
#define MUSIC_3						"resource/BGM/03.mp3"

#define SOUND_EFFECT_1				"resource/SoundEffect/01.mp3"//移动音效
#define SOUND_EFFECT_2				"resource/SoundEffect/02.mp3"//落下音效
#define SOUND_EFFECT_3				"resource/SoundEffect/03.mp3"//得分音效
#define SOUND_EFFECT_4				"resource/SoundEffect/04.mp3"//失败音效
#define SOUND_EFFECT_5				"resource/SoundEffect/05.mp3"//旋转碰壁/使用道具失败音效
#define SOUND_EFFECT_6				"resource/SoundEffect/06.mp3"//使用道具提示音

#define BASE_PATH					"resource/Image/"
#define IMAGE_1						"resource/IMAGE/06.jpg"
#define GAMEOVER_IMAGE				"resource/IMAGE/07.jpg"
#define BACKGROUND_IMAGE			"resource/IMAGE/08.jpg"

#define RECORD_FILE					"Tetris_record.txt"

#endif 

