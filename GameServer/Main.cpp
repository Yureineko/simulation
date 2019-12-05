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
	//IPアドレスそれぞれ格納するための変数
	IPDATA IpAddress;
	//今繋がっている状態かどうか
	bool connectnow;
	//ペアになってるかどうか
	bool pairflg;
	//ペアがいる場合そのナンバーは何処か
	int enemynumber;
	//ネットハンドル(基本40 * iの数値)
	int NetUDPHandle;
	//繋がらないときの猶予時間(1秒程度繋がらなければデータを初期化)
	int NoConetime;
	int scenenumber;
	char RecvData[10];
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int NetUDPHandleConnect;//ネットワークハンドル
	Player user[10];//通信するIPアドレスを保存しておくための場所

	SetMainWindowText("サーバー用");//windowの名前
	ChangeWindowMode(TRUE);//windowモード
	SetGraphMode(640, 480, 32);//windowサイズ
	SetAlwaysRunFlag(TRUE);//バックグラウンドでも動くように設定

	if (DxLib_Init() == -1) return -1;//エラーが起きたら終了

	//ユーザー情報の初期化
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

	//描画設定
	SetDrawScreen(DX_SCREEN_BACK);

	//UDP通信用のソケットハンドルの設定
	NetUDPHandleConnect = MakeUDPSocket(30);

	//ウインドウ閉じない限り続行
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
					user[i].NoConetime = 0;
					NetWorkRecvUDP(user[i].NetUDPHandle, &user[i].IpAddress, NULL, data, sizeof(data), FALSE);

					//ペアであるかどうかで返信を変える
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
					//繋がってないときは猶予時間までカウントする
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
							//ペアになっていた場合相手のペア情報も消す
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
				//分かりやすくするために文字列描画
				DrawString(0, 32 * i, "マシンと接続できました", GetColor(255, 255, 255));

				//データの送信
				if (user[i].connectnow == true)
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, user[i].RecvData, sizeof(user[i].RecvData));
			}
		}

		//接続処理
		if (CheckNetWorkRecvUDP(NetUDPHandleConnect) == TRUE)
		{
			//接続するマシンがあればその情報を取得する
			for (int i = 0; i < 10; i++)
			{
				if (user[i].connectnow == false)
				{
					//空データを受け取る
					char data[10] = { 0 };
					NetWorkRecvUDP(NetUDPHandleConnect, &user[i].IpAddress, NULL, data, sizeof(data), FALSE);
					//データの送信
					NetWorkSendUDP(user[i].NetUDPHandle, user[i].IpAddress, 99, data, sizeof(data));
					//繋がってるフラグを立てる
					user[i].connectnow = true;
					break;
				}
			}
		}
		//ペアづくり
		for (int i = 0, count = 0, pairnum = -1; i < 10; i++)
		{
			//ペアがいないマシンが2つある場合
			if (user[i].connectnow == true && user[i].pairflg == false)
			{
				//カウント
				count++;
				//一回目のカウントの場合
				if (count == 1)
				{
					//そのナンバーを一度保存
					pairnum = i;
				}
				else
				{
					//２台見つかった場合そのマシン同士でペアを組ませる
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
	DeleteUDPSocket(NetUDPHandleConnect);

	DxLib_End();//DXライブラリ使用の終了処理

	return 0;//ソフトの終了
}