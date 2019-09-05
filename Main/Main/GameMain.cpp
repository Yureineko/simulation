#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//windowモードで起動
	ChangeWindowMode(TRUE);
	//Dxライブラリの初期化
	DxLib_Init();
	//ウィンドウ名設定
	SetMainWindowText("SimulatioN GamE");
	//ゲームウインドウサイズ
	SetGraphMode(800, 600, 32);
	//フォント確定
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	while (1)
	{











		//ゲームが終わるフラグが立っていたら閉じる
		if (ProcessMessage() == -1)
			break;
	}

	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}