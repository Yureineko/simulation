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
	//IP�A�h���X���ꂼ��i�[���邽�߂̕ϐ�
	IPDATA IpAddress;
	//���q�����Ă����Ԃ��ǂ���
	bool connectnow;
	//�y�A�ɂȂ��Ă邩�ǂ���
	bool pairflg;
	//�y�A������ꍇ���̃i���o�[�͉�����
	int enemynumber;
	//�l�b�g�n���h��(��{40 * i�̐��l)
	int NetUDPHandle;
	//�q����Ȃ��Ƃ��̗P�\����(1�b���x�q����Ȃ���΃f�[�^��������)
	int NoConetime;
	int scenenumber;
	char RecvData[10];
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int NetUDPHandleConnect;//�l�b�g���[�N�n���h��
	Player user[10];//�ʐM����IP�A�h���X��ۑ����Ă������߂̏ꏊ

	SetMainWindowText("�T�[�o�[�p");//window�̖��O
	ChangeWindowMode(TRUE);//window���[�h
	SetGraphMode(640, 480, 32);//window�T�C�Y
	SetAlwaysRunFlag(TRUE);//�o�b�N�O���E���h�ł������悤�ɐݒ�

	if (DxLib_Init() == -1) return -1;//�G���[���N������I��

	//���[�U�[���̏�����
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

	//�`��ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//UDP�ʐM�p�̃\�P�b�g�n���h���̐ݒ�
	NetUDPHandleConnect = MakeUDPSocket(30);

	//�E�C���h�E���Ȃ����葱�s
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
					user[i].NoConetime = 0;
					NetWorkRecvUDP(user[i].NetUDPHandle, &user[i].IpAddress, NULL, data, sizeof(data), FALSE);

					//�y�A�ł��邩�ǂ����ŕԐM��ς���
					if (user[i].pairflg == true)
					{
						for (int j = 0; j < 10; j++)
						{
							user[user[i].enemynumber].RecvData[j] = data[j];
						}
					}
					else
					{
						user[i].RecvData[0] = 1;
					}
				}
				else
				{
					//�q�����ĂȂ��Ƃ��͗P�\���Ԃ܂ŃJ�E���g����
					user[i].NoConetime++;
					if (user[i].pairflg == true)
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
							//�y�A�ɂȂ��Ă����ꍇ����̃y�A��������
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
				//������₷�����邽�߂ɕ�����`��
				DrawString(0, 32 * i, "�}�V���Ɛڑ��ł��܂���", GetColor(255, 255, 255));

				//�f�[�^�̑��M
				if (user[i].connectnow == true)
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, user[i].RecvData, sizeof(user[i].RecvData));
			}
		}

		//�ڑ�����
		if (CheckNetWorkRecvUDP(NetUDPHandleConnect) == TRUE)
		{
			//�ڑ�����}�V��������΂��̏����擾����
			for (int i = 0; i < 10; i++)
			{
				if (user[i].connectnow == false)
				{
					//��f�[�^���󂯎��
					char data[10] = { 0 };
					NetWorkRecvUDP(NetUDPHandleConnect, &user[i].IpAddress, NULL, data, sizeof(data), FALSE);
					//�f�[�^�̑��M
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, data, sizeof(data));
					//�q�����Ă�t���O�𗧂Ă�
					user[i].connectnow = true;
					break;
				}
			}
		}
		//�y�A�Â���
		for (int i = 0, count = 0, pairnum = -1; i < 10; i++)
		{
			//�y�A�����Ȃ��}�V����2����ꍇ
			if (user[i].connectnow == true && user[i].pairflg == false)
			{
				//�J�E���g
				count++;
				//���ڂ̃J�E���g�̏ꍇ
				if (count == 1)
				{
					//���̃i���o�[����x�ۑ�
					pairnum = i;
				}
				else
				{
					//�Q�䌩�������ꍇ���̃}�V�����m�Ńy�A��g�܂���
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
	DeleteUDPSocket(NetUDPHandleConnect);

	DxLib_End();//DX���C�u�����g�p�̏I������

	return 0;//�\�t�g�̏I��
}