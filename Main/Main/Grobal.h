#pragma once
#include"DxLib.h"

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

int CanMoveMap[7][7] =
{
	0
};