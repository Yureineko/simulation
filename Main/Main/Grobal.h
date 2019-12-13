#pragma once
//使用ヘッダー----------------------------------------
#include"DxLib.h"
#include<stdio.h>

//定数定義--------------------------------------------
#define SCREEN_PIXWIDTH		832//画面サイズ　X
#define SCREEN_PIXHEIGHT	448//画面サイズ　Y

//MainMapの範囲
#define POPUP_X 192//左↑の点
#define POPUP_Y 0//右↑
#define POPDOWN_X 64//
#define POPDOWN_Y 64

//左側のキャラの能力ボタンの範囲
#define CLUP_X 40//左　点
#define CLUP_Y 280//上　点
#define CLDOWN_X 150//右　点
#define CLDOWN_Y 380//下　点

//駒動かすアニメーションの早さ定義(値を小さくすれば早くなりますがなるべく64を割り切れる数字でお願いします)
#define MOVESPEED 8;

#define PI	3.1415926535897932384626433832795f

//構造体---------------------------------------------
//座標設定用
typedef struct PositionInfo
{
	//ポジション使う際に
	int posX;
	int posY;
}Pos;

//駒設定用
typedef struct PieceInfo
{
	int type;
	int posX;
	int posY;
	bool MeorEne;
	int movelimit;
	int movefront;
	int moveback;
	int moveleft;
	int moveright;
	int dialu;
	int diald;
	int diaru;
	int diard;
	int spicialmoverange[8][2];
}Piece;

//スキル設定
typedef struct Skill
{
	int type;
	int posx;
	int posy;
	bool MeorEne;
	

}skill;

//シーン一覧
enum Scenes
{
	TITLE,CONNECT,NAMESELECT,SELECT,GAME,GAMEEND,
};
//送るデータ一覧
enum SendDataTag
{
	ISCONNECT, SELECTCHARA, TURNFAST, MOVEBEFOREPOSX, MOVEBEFOREPOSY, LATEMOVEPOSX, LATEMOVEPOSY,
};

//グローバル変数定義-------------------------------------
//駒の動けるMap
int CanMoveMap[7][7] =
{
	0
};

//壁を発生させれる場所
int SkillMap[7][7] =
{
	0
};
