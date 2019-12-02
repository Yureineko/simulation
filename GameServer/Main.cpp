#pragma once
#include "DxLib.h"
#include <string.h>
#include <string>
#include <stdio.h>
#include <list>

using namespace std;

//位置情報
struct Pos
{
	int x, y;
};

//プレイヤー情報
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
	IPDATA Ip;//送信用IPアドレスデータ
	int port = -1; //接続ポート
	char StrBuf[256] = { 0,0,-1 };//データバッファ
	int NetUDPHandleData;//ネットワークハンドル
	int NetUDPHandleConnect;//ネットワークハンドル
	int RecvHandle;//設定用
	char STR[256] = { NULL };//送信データ用
	Player user[10];//通信するIPアドレスを保存しておくための場所
	int pair[5][2];//お互いのペアを保存しておく
	int connectmachine = 0;//繋げたマシン数
	int pearcount = 0;

	SetMainWindowText("受信側");//windowの名前
	ChangeWindowMode(TRUE);//windowモード
	SetGraphMode(640, 480, 32);//windowサイズ
	SetAlwaysRunFlag(TRUE);//バックグラウンドでも動くように設定


	if (DxLib_Init() == -1) return -1;//エラーが起きたら終了

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

	//UDP通信用のソケットハンドルの設定
	NetUDPHandleData = MakeUDPSocket(50);
	NetUDPHandleConnect = MakeUDPSocket(30);

	while (ProcessMessage() != -1)
	{
		
		for (int i = 0; i < 10; i++)
		{
			//繋いでいるマシンの数だけ回す
			if (user[i].connectnow == true)
			{
				//受信処理
				if (CheckNetWorkRecvUDP(user[i].NetUDPHandle) == TRUE)
				{
					char data[10] = { 0 };
					NetWorkRecvUDP(user[i].NetUDPHandle, &user[i].IpAddress, NULL, &data, sizeof(int), FALSE);

					if (user[i].pairflg == true)
					{
						for (int j = 0; j < 10; j++)
							user[user[i].enemynumber].RecvData[j] = data[j];

						user[i].RecvData[0] = 2;
						//データの送信
						NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, user[i].RecvData, sizeof(user[i].RecvData));
					}
					else
					{
						user[i].RecvData[0] = 1;
						//データの送信
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
				DrawString(0, 32 * i, "マシンと接続できました", GetColor(255, 255, 255));
			}
		}

		//受信処理
		if (CheckNetWorkRecvUDP(NetUDPHandleConnect) == TRUE)
		{
			for (int i = 0; i < 10; i++)
			{
				if (user[i].connectnow == false)
				{
					int data = 0;
					NetWorkRecvUDP(NetUDPHandleConnect, &user[i].IpAddress, NULL, &data, sizeof(int), FALSE);
					//データの送信
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, &data, sizeof(int));
					user[i].connectnow = true;
					connectmachine++;
					break;
				}
			}
		}
		//ペアづくり
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

		//画面の更新
		ScreenFlip();
		ClearDrawScreen();
	}

	//ソケットハンドルの削除
	for(int i = 0; i < 10; i++)
		DeleteUDPSocket(user[i].NetUDPHandle);
	DeleteUDPSocket(NetUDPHandleData);
	DeleteUDPSocket(NetUDPHandleConnect);

	DxLib_End();//DXライブラリ使用の終了処理

	return 0;//ソフトの終了
}