#pragma once
#include "DxLib.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <list>

using namespace std;

//�ʒu���
struct Pos
{
	int x, y;
};

//���M�f�[�^�p�\����
struct Data
{
	Pos p;
	int flg;
	int hp;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IPDATA Ip;//���M�pIP�A�h���X�f�[�^
	int port = -1; //�ڑ��|�[�g
	char StrBuf[256] = { 0,0,-1 };//�f�[�^�o�b�t�@
	int NetUDPHandle;//�l�b�g���[�N�n���h��
	char STR[256] = { NULL };//���M�f�[�^�p
	Data d;//���M�f�[�^�p(�\����)

	SetMainWindowText("��M��");//window�̖��O
	ChangeWindowMode(TRUE);//window���[�h
	SetGraphMode(640, 480, 32);//window�T�C�Y
	SetAlwaysRunFlag(TRUE);//�o�b�N�O���E���h�ł������悤�ɐݒ�

	if (DxLib_Init() == -1) return -1;//�G���[���N������I��

	SetDrawScreen(DX_SCREEN_BACK);

	//UDP�ʐM�p�̃\�P�b�g�n���h���̐ݒ�
	NetUDPHandle = MakeUDPSocket(40);


	while (ProcessMessage() != -1)
	{


		//��M����
		if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
		{
			
		}

		//��ʂ̍X�V
		ScreenFlip();
		ClearDrawScreen();
	}

	//�\�P�b�g�n���h���̍폜
	DeleteUDPSocket(NetUDPHandle);

	DxLib_End();//DX���C�u�����g�p�̏I������

	return 0;//�\�t�g�̏I��
}