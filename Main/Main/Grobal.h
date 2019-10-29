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
	int moverange[12][2];
}Piece;