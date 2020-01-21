#pragma once
//�g�p�w�b�_�[----------------------------------------
#include"DxLib.h"
#include<stdio.h>

//�萔��`--------------------------------------------
#define SCREEN_PIXWIDTH		832//��ʃT�C�Y�@X
#define SCREEN_PIXHEIGHT	448//��ʃT�C�Y�@Y

//MainMap�͈̔�
#define POPUP_X 192//�����̓_
#define POPUP_Y 0//�E���̓_
#define POPDOWN_X 64//�����̓_
#define POPDOWN_Y 64//�E���̓_

//�����̃L�����̔\�̓{�^���͈̔�
#define CLUP_X 40//���@�_
#define CLUP_Y 280//��@�_
#define CLDOWN_X 150//�E�@�_
#define CLDOWN_Y 380//���@�_



//������A�j���[�V�����̑�����`(�l������������Α����Ȃ�܂����Ȃ�ׂ�64������؂�鐔���ł��肢���܂�)
#define MOVESPEED 8

#define NAMEMAX 13

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
	int movelimit;//�ړ��l�̌��E
	int movefront;//�O�̈ړ�
	int moveback;//��̈ړ�
	int moveleft;//���̈ړ�
	int moveright;//�E�̈ړ�
	int dialu;//����̈ړ�
	int diald;//�����̈ړ�
	int diaru;//�E��̈ړ�
	int diard;//�E���̈ړ�
	int spicialmoverange[8][2];//������̈ړ��ꏊ
}Piece;

//�X�L���ݒ�
typedef struct Skill
{
	//Map�̑S���0�̕����𒲂ׂ�
	int skillposx;
	int skillposy;
	
	//0�̕��������p
	int zeroskill;

}skill;

//�V�[���ꗗ
enum Scenes
{
	TITLE,CONNECT,NAMESELECT,SELECT,GAME,GAMEEND,
};
//����f�[�^�ꗗ
enum SendDataTag
{
	ISCONNECT, SELECTCHARA, TURNFAST, MOVEBEFOREPOSX, MOVEBEFOREPOSY, LATEMOVEPOSX, LATEMOVEPOSY,PLAYERNAME,
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
