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

//�V�[���ꗗ
enum Scenes
{
	TITLE,CONNECT,SELECT,GAME,GAMEEND,
};
//����f�[�^�ꗗ
enum SendDataTag
{
	ISCONNECT, SELECTCHARA, TURNFAST, MOVEBEFOREPOSX, MOVEBEFOREPOSY, LATEMOVEPOSX, LATEMOVEPOSY,
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

//����ɑ��M����f�[�^
struct DATA
{
	//��̈ʒu�f�[�^
	POS p;
	//�����̎�ԂȂ̂�����̎�ԂȂ̂��̃t���O
	int trun;
	//�����̉��������Ă��邩�̃t���O
	int Myking;
};

//�x�[�X�N���X
class Base
{
private:

public:
	int ID;//�f�o�b�O�p
	int flg;
	virtual void Action() = 0;
	virtual void Draw() = 0;//
	virtual POS GetPos() = 0;//��̈ʒu
	virtual int GetID() = 0;//�����IP�A�h���X





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