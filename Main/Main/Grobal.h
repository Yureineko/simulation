#pragma once
//�g�p�w�b�_�[----------------------------------------
#include"DxLib.h"
#include<stdio.h>

//�萔��`--------------------------------------------
#define SCREEN_PIXWIDTH		832//��ʃT�C�Y�@X
#define SCREEN_PIXHEIGHT	448//��ʃT�C�Y�@Y

//MainMap�͈̔�
#define POPUP_X 192//�����̓_
#define POPUP_Y 0//�E��
#define POPDOWN_X 64//
#define POPDOWN_Y 64

//�����̃L�����̔\�̓{�^���͈̔�
#define CLUP_X 40//���@�_
#define CLUP_Y 280//��@�_
#define CLDOWN_X 150//�E�@�_
#define CLDOWN_Y 380//���@�_

//������A�j���[�V�����̑�����`(�l������������Α����Ȃ�܂����Ȃ�ׂ�64������؂�鐔���ł��肢���܂�)
#define MOVESPEED 8;

#define PI	3.1415926535897932384626433832795f

//�\����---------------------------------------------
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

//�X�L���ݒ�
typedef struct Skill
{
	int type;
	int posx;
	int posy;
	bool MeorEne;
	

}skill;

//�V�[���ꗗ
enum Scenes
{
	TITLE,CONNECT,NAMESELECT,SELECT,GAME,GAMEEND,
};
//����f�[�^�ꗗ
enum SendDataTag
{
	ISCONNECT, SELECTCHARA, TURNFAST, MOVEBEFOREPOSX, MOVEBEFOREPOSY, LATEMOVEPOSX, LATEMOVEPOSY,
};

//�O���[�o���ϐ���`-------------------------------------
//��̓�����Map
int CanMoveMap[7][7] =
{
	0
};

//�ǂ𔭐��������ꏊ
int SkillMap[7][7] =
{
	0
};
