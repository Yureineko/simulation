#pragma once
#include"DxLib.h"

//À•Wİ’è—p
typedef struct PositionInfo
{
	int posX;
	int posY;
}Pos;

//‹îİ’è—p
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

enum Scenes
{
	TITLE,SELECT,GAME,
};

int CanMoveMap[7][7] =
{
	0
};