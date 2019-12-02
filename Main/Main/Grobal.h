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

enum Scenes
{
	TITLE,CONNECT,SELECT,GAME,GAMEEND,
};
//��̓�����Map
int CanMoveMap[7][7] =
{
	0
};

//�ǂ𔭐��������ꏊ
int DwallMap[7][7] =
{
	0
};

//�T�[�o�[�ɑ��M����f�[�^
struct Data 
{
	//��̈ʒu�f�[�^
	POS p;
	//�����̎�ԂȂ̂��̃t���O
	int trun;
	//�����̉��������Ă��邩�̃t���O
	int Myking;
};

//�ǐݒ�
typedef struct Wall
{
	int type;
	int posx;
	int posy;
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


}Walls;