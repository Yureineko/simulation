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

	//ここにステージの


	//画像int変換関数
	//int img = LoadGraph("画像名");

	//音声int変換関数
	//int bgm = LoadSoundMem("音楽名");

	//バックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);

	//
	//

	while (1)
	{
		//aaaa


		//if()



		//文字列表示
		//DrawString(x, y, 表示する文字列(*char), 表示する際の文字の色(GetColor(r,g,b)));

		//画像表示
		//DrawGraph(x, y, img画像(int型), TRUE);

		//ゲームが終わるフラグが立っていたら閉じる
		if (ProcessMessage() == -1)
			break;
	}

	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}