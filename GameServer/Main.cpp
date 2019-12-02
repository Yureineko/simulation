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

//�v���C���[���
struct Player
{
	IPDATA IpAddress;
	bool connectnow;
	bool pairflg;
	int enemynumber;
	int NetUDPHandle;
	int NoConetime;
	int scenenumber;
	char RecvData[10];
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IPDATA Ip;//���M�pIP�A�h���X�f�[�^
	int port = -1; //�ڑ��|�[�g
	char StrBuf[256] = { 0,0,-1 };//�f�[�^�o�b�t�@
	int NetUDPHandleData;//�l�b�g���[�N�n���h��
	int NetUDPHandleConnect;//�l�b�g���[�N�n���h��
	int RecvHandle;//�ݒ�p
	char STR[256] = { NULL };//���M�f�[�^�p
	Player user[10];//�ʐM����IP�A�h���X��ۑ����Ă������߂̏ꏊ
	int pair[5][2];//���݂��̃y�A��ۑ����Ă���
	int connectmachine = 0;//�q�����}�V����
	int pearcount = 0;

	SetMainWindowText("��M��");//window�̖��O
	ChangeWindowMode(TRUE);//window���[�h
	SetGraphMode(640, 480, 32);//window�T�C�Y
	SetAlwaysRunFlag(TRUE);//�o�b�N�O���E���h�ł������悤�ɐݒ�


	if (DxLib_Init() == -1) return -1;//�G���[���N������I��

	for (int i = 0; i < 10; i++)
	{
		user[i].IpAddress.d1 = 0;
		user[i].IpAddress.d2 = 0;
		user[i].IpAddress.d3 = 0;
		user[i].IpAddress.d4 = 0;
		user[i].connectnow = false;
		user[i].pairflg = false;
		user[i].enemynumber = -1;
		user[i].NetUDPHandle = MakeUDPSocket(40 + i);
		user[i].NoConetime = 0;
		user[i].scenenumber = 0;
		for (int j = 0; j < 10; j++)
		{
			user[i].RecvData[j] = 0;
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	//UDP�ʐM�p�̃\�P�b�g�n���h���̐ݒ�
	NetUDPHandleData = MakeUDPSocket(50);
	NetUDPHandleConnect = MakeUDPSocket(30);

	while (ProcessMessage() != -1)
	{
		
		for (int i = 0; i < 10; i++)
		{
			//�q���ł���}�V���̐�������
			if (user[i].connectnow == true)
			{
				//��M����
				if (CheckNetWorkRecvUDP(user[i].NetUDPHandle) == TRUE)
				{
					char data[10] = { 0 };
					NetWorkRecvUDP(user[i].NetUDPHandle, &user[i].IpAddress, NULL, &data, sizeof(int), FALSE);

					if (user[i].pairflg == true)
					{
						for (int j = 0; j < 10; j++)
							user[user[i].enemynumber].RecvData[j] = data[j];

						user[i].RecvData[0] = 2;
						//�f�[�^�̑��M
						NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, user[i].RecvData, sizeof(user[i].RecvData));
					}
					else
					{
						user[i].RecvData[0] = 1;
						//�f�[�^�̑��M
						NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, user[i].RecvData, sizeof(user[i].RecvData));
					}
				}
				else
				{
					user[i].NoConetime++;
					if (user[i].connectnow = true)
					{
						for (int j = 0; j < 10; j++)
							user[user[i].enemynumber].RecvData[j] = 0;
					}

					if (user[i].NoConetime >= 60)
					{
						user[i].IpAddress.d1 = 0;
						user[i].IpAddress.d2 = 0;
						user[i].IpAddress.d3 = 0;
						user[i].IpAddress.d4 = 0;
						user[i].connectnow = false;
						if (user[i].pairflg == true)
						{
							user[i].pairflg = false;
							user[user[i].enemynumber].pairflg = false;
							user[user[i].enemynumber].enemynumber = -1;
							user[i].enemynumber = -1;
						}
						user[i].NoConetime = 0;
						for (int j = 0; j < 10; j++)
						{
							user[i].RecvData[j] = 0;
						}
					}
				}
				DrawString(0, 32 * i, "�}�V���Ɛڑ��ł��܂���", GetColor(255, 255, 255));
			}
		}

		//��M����
		if (CheckNetWorkRecvUDP(NetUDPHandleConnect) == TRUE)
		{
			for (int i = 0; i < 10; i++)
			{
				if (user[i].connectnow == false)
				{
					int data = 0;
					NetWorkRecvUDP(NetUDPHandleConnect, &user[i].IpAddress, NULL, &data, sizeof(int), FALSE);
					//�f�[�^�̑��M
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, &data, sizeof(int));
					user[i].connectnow = true;
					connectmachine++;
					break;
				}
			}
		}
		//�y�A�Â���
		for (int i = 0, count = 0, pairnum = -1; i < 10; i++)
		{
			if (user[i].connectnow == true && user[i].pairflg == false)
			{
				count++;
				if (count == 1)
				{
					pairnum = i;
				}
				else
				{
					user[pairnum].pairflg = true;
					user[i].pairflg = true;
					user[pairnum].enemynumber = i;
					user[i].enemynumber = pairnum;
					user[i].RecvData[0] = 1;
					break;
				}
			}
		}

		//��ʂ̍X�V
		ScreenFlip();
		ClearDrawScreen();
	}

	//�\�P�b�g�n���h���̍폜
	for(int i = 0; i < 10; i++)
		DeleteUDPSocket(user[i].NetUDPHandle);
	DeleteUDPSocket(NetUDPHandleData);
	DeleteUDPSocket(NetUDPHandleConnect);

	DxLib_End();//DX���C�u�����g�p�̏I������

	return 0;//�\�t�g�̏I��
}