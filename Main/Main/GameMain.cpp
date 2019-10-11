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
	SetGraphMode(832, 448, 32);
	//フォント確定
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);


	

	//ここに盤上を設定
	//駒の種類は最大5種類
	int MainMap[7][7]
	{
		{ 2,3,4,5,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1 },
		{ 2,3,4,5,4,3,2 },
	};
	//1.兵士(歩)
	//2.魔導士(角)
	//3.諜報員(チェス:ナイト)
	//4.騎士(飛車)
	//5.王


	//ここに移動させる駒を選択させるMapを生成
	int SubMap[7][7]
	{
		{ 2,3,4,5,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1 },
		{ 2,3,4,5,4,3,2 },
	};




	//画像int変換関数
	//int img = LoadGraph("画像名");
	int map;//盤の画像登録

	int t_chara;//仮キャラクターの表示　1体目
	int t_chara2;//仮キャラクターの表示　2体目

	 //MainMap[1]=LoadGraph("image\\");//ここに兵士の画像
	 //MainMap[2]=LoadGraph("image\\");//ここに魔導士の画像
	 //MainMap[3]=LoadGraph("image\\");//ここに諜報員の画像
	 //MainMap[4]=LoadGraph("image\\");//ここに騎士の画像
	 //MainMap[5]=LoadGraph("image\\");//ここに王の画像



	 t_chara = LoadGraph("image\\201401231944448d7.png");
	 t_chara2 = LoadGraph("image\\p-wakana-24.png");

	//背景の画像表示	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
	LoadGraphScreen(192, 64, "image\\King.png", TRUE);

	//音声int変換関数
	//int bgm = LoadSoundMem("音楽名");

	 DrawGraph(164, 0, t_chara, TRUE);//プレイヤー1の描画

	 DrawGraph(0, 0, t_chara2, TRUE);//プレイヤー2の描画


	 int turn=0;//ターン変数....0:自分のターン　1:相手のターン
	 int movepointX;//駒の移動の変数(MainMapと照らし合わせて使用する。)


	//バックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);

	//DXライブラリを初期化
	if (DxLib_Init() == -1)
	{
		return -1;//エラーが出たら強制終了

	}

	//
	//

	while (1)
	{
		

	//選択肢の移動	
		if (CheckHitKey(KEY_INPUT_UP))
		{
			//キーを押して上に選択肢移動
			//if (MainMap[0][1] )
		};




//----------登録した駒の移動描画-----------

		//Swich文でmapの描画と更新を行う
		for (int y = 0; y< 7; y++)
		{
			for (int x=0;x<7;x++)
			{
				switch (MainMap[y][x])
				{
				
				case 0://何もない場所
					break;

				case 1://兵士
					//DrawGraphF(x*64,y*64,)//兵士の描画
					break;

				case 2://魔導士
					//DrawGraphF(x*64,y*64,)//魔導士の画像
					break;

				case 3://諜報員
					//DrawGraphF(x*64,y*64,)//諜報員の画像
					break;

				case 4://騎士
					//DrawGraphF(x*64,y*64,)//騎士の画像
					break;

				case 5://王
					//DrawGraphF(x*64,y*64)//王の画像
					break;
				}
			}
		}




		//文字列表示
		//DrawString(x, y, 表示する文字列(*char), 表示する際の文字の色(GetColor(r,g,b)));

		//画像表示
		//DrawGraph(x, y, img画像(int型), TRUE);

		
		//この辺り?で勝敗判定を行ってbreakでwhile文を抜ける。


		//ゲームが終わるフラグが立っていたら閉じる
		if (ProcessMessage() == -1)
			break;
	}

	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}