#pragma once
#include"DxLib.h"

//���W�ݒ�p
typedef struct PositionInfo
{
	//�|�W�V�����g���ۂ�
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