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

//送信データ用構造体
struct Data
{
	Pos p;
	int flg;
	int hp;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IPDATA Ip;//送信用IPアドレスデータ
	int port = -1; //接続ポート
	char StrBuf[256] = { 0,0,-1 };//データバッファ
	int NetUDPHandle;//ネットワークハンドル
	char STR[256] = { NULL };//送信データ用
	Data d;//送信データ用(構造体)

	SetMainWindowText("受信側");//windowの名前
	ChangeWindowMode(TRUE);//windowモード
	SetGraphMode(640, 480, 32);//windowサイズ
	SetAlwaysRunFlag(TRUE);//バックグラウンドでも動くように設定

	if (DxLib_Init() == -1) return -1;//エラーが起きたら終了

	SetDrawScreen(DX_SCREEN_BACK);

	//UDP通信用のソケットハンドルの設定
	NetUDPHandle = MakeUDPSocket(40);


	while (ProcessMessage() != -1)
	{


		//受信処理
		if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
		{
			
		}

		//画面の更新
		ScreenFlip();
		ClearDrawScreen();
	}

	//ソケットハンドルの削除
	DeleteUDPSocket(NetUDPHandle);

	DxLib_End();//DXライブラリ使用の終了処理

	return 0;//ソフトの終了
}