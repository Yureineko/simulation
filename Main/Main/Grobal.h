#pragma once
#include"DxLib.h"

//���W�ݒ�p
typedef struct PositionInfo
{
	int posX;
	int posY;
}Pos;

//��ݒ�p
typedef struct PieceInfo
{
	int type;
	int posX;
	int posY;
	bool MeorEne;
	int movelimit;
	int moverange[12][2];
}Piece;