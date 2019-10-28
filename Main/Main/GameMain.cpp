#include "DxLib.h"

#define SCREEN_PIXWIDTH		832
#define SCREEN_PIXHEIGHT	448
#define POPUP_X 64
#define POPUP_Y 64

#define PI	3.1415926535897932384626433832795f

//クリックの領域をチェックする関数
bool HitClick(int Cx, int Cy, int x1, int y1);

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

	//先攻後攻の判定(仮置き　一旦コメントアウト中)
	int Random[1];
	int Green = GetColor(0, 255, 0);
	
	//乱数の初期値を123456に設定する
	SRand(123456);

	//ここに盤上を設定
	//駒の種類は最大5種類
	int MainMap[7][7]=
	{
		{ 2,3,4,6,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,5,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,0,1,1,1 },
		{ 2,3,4,0,4,3,2 },
	};
	//1.兵士(歩)
	//2.魔導士(角)
	//3.諜報員(チェス:ナイト)
	//4.騎士(飛車)
	//5.王
	//6.相手の王




	//画像int変換関数
	//int img = LoadGraph("画像名");
	

	int t_chara;//仮キャラクターの表示　1体目
	int t_chara2;//仮キャラクターの表示　2体目

	int Soldier=LoadGraph("image\\");//ここに兵士の画像
	int Sorcerer=LoadGraph("image\\");//ここに魔導士の画像
	int Espionage =LoadGraph("image\\");//ここに諜報員の画像
	int Knight =LoadGraph("image\\");//ここに騎士の画像
	int King =LoadGraph("image\\King(64).png");//ここに王の画像
	int EKing = LoadGraph("image\\King(64).png");//ここに王の画像

	//一旦ここで位置移動する。後で消すかも。
	int SoldX = 1, SoldY = 1;//兵士の位置X,Y
	int SorcX = 2, SorcY = 2;//魔導士の位置X,Y
	int EspiX = 3, EspiY = 3;//諜報員の位置X,Y
	int KnigX = 4, KnigY = 4;//騎士の位置X,Y
	int KingX = 5, KingY = 5;//王の位置X,Y	
	int EKingX = 6, EKingY = 6;//王の位置X,Y


	//int King = LoadGraph("image\\King.png");

	t_chara = LoadGraph("image\\キャラ1(仮).png");
	t_chara2 = LoadGraph("image\\キャラ2(仮).png");

	//背景の画像表示	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);

	//音声int変換関数
	//int bgm = LoadSoundMem("音楽名");

	//ゲームメインの音楽再生
	int  Mainbgm = LoadSoundMem("sound\\");

	//アニメーション登録サンプル
	int MovieGraphHandle;

	MovieGraphHandle=LoadGraph("image\\nc157304.mp4");
	PlayMovieToGraph(MovieGraphHandle);



	//test用サウンド
	int se=LoadSoundMem("sound\\test.mp3");

	
	//DrawGraph(384, 0, King, TRUE);//王の描画

	DrawGraph(0, 0, t_chara, TRUE);//プレイヤー1の描画
	DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
	
	int turn=0;//ターン変数....0:自分のターン　1:相手のターン
	int movepointX;//駒の移動の変数(MainMapと照らし合わせて使用する。)
	

	int win_flag = false;//勝った時のフラグ
	int lose_flag = false;//負けた時のフラグ



	//---------マウス操作の変数--------
	
	

	 //GetMousePoint(&Mx,&My);//マウスの現在位置取得

	//マウスをwindow上に表示させる。
	//SetMouseDispFlag(TRUE);


	//ここで描画先を表画面にする。
	SetDrawScreen(DX_SCREEN_FRONT);

	int cx, cy;
	bool Click_flag = 0;


	//DXライブラリを初期化
	if (DxLib_Init() == -1)
	{
		return -1;//エラーが出たら強制終了

	}


	//while(裏画面)



	//ここでゲームのメイン部分構築
	while (ProcessMessage() == -1)
	{
		//自分のターン以外は操作を不可能にする
		if (turn == 0)
		{
			int Mx, My,

				Mbutton = false;//マウス位置X,Y マウスを押したときのボタン


			GetMousePoint(&Mx, &My);

			//マウスの左クリックが押されているか
			//マウスが押されていないとき
			//ここでクリックできる領域を設定


			//if (Mx <=MainMap[KingY][KingX])//
			//{
			//	//int x,y;

			//	//マウスを押したときの処理
			//	//左クリックしたときの処理
			//		if (GetMouseInput() != 0&&MOUSE_INPUT_LEFT!=0)
			//		{
			//			Mbutton = TRUE;

			//			if (Mbutton==TRUE)
			//			{
			//			
			//				//押されている
			//				PlaySoundMem(se, DX_PLAYTYPE_BACK);
			//			}

			//		}


			//		
			//		else
			//		{
			//			//押されていない
			//			

			//		}

			//}

			//クリックした先が0ならそこに描画


				//マウスを押したときの処理
				//左クリックしたときの処理
			while (GetMouseInput() != 0 & MOUSE_INPUT_LEFT != 0)
			{
				Mbutton = false;

				if (MainMap[KingY][KingX + 1] == 0)
				{

					//押されている
					PlaySoundMem(se, DX_PLAYTYPE_BACK);
					MainMap[KingY][KingX - 1] = 5;

					MainMap[KingY][KingX] = 0;
					//Mbutton=true;

				}
			}

			//
			//{
			//	//押されていない

			//	//MainMap[KingY][KingX] = 5;
			//	Mbutton = false;
			//}





			DrawBox(0, 0, 192, SCREEN_PIXHEIGHT, GetColor(0, 255, 255), 1);
			DrawBox(640, 0, SCREEN_PIXWIDTH, SCREEN_PIXHEIGHT, GetColor(255, 0, 255), 1);
			//選択肢の移動	
			if (CheckHitKey(KEY_INPUT_UP))
			{
				//キーを押して上に選択肢移動
				//if (MainMap[0][1] )
				//KingX++;
			};

			if (CheckHitKey(KEY_INPUT_DOWN))
			{
				//キーを押して下に選択肢移動
				//if(MainMap[0][2])
			};

			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				//キーを押して右に選択肢移動
			};

			if (CheckHitKey(KEY_INPUT_LEFT))
			{
				//キーを押して左に選択肢移動

			};

			//自分の駒が相手の駒に重なった時の処理
			/*if (MainMap[kx][ky])
			{

			}*/
		}
		//else
		//{

		//	turn = 1;//相手のターンを返して終了
		//};


		//この辺り?で勝敗判定を行ってbreakでwhile文を抜ける。

		//自分の王がとられた場合
		if (MainMap[KingY][KingX]==0)
		{
			//勝敗判定
			lose_flag = true;
			//break;

		};

//----------登録した駒の移動描画-----------

		//Swich文でmapの描画と更新を行う
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				switch (MainMap[y][x])
				{
				
				case 0:
				{
					//何もない場所
					break;
				}

				case 1://兵士
				{
					DrawGraphF(x * 64 + 192, y * 64, Soldier, TRUE);//兵士の描画
					break;
				}

				case 2://魔導士
				{
					DrawGraphF(x * 64 + 192, y * 64, Sorcerer, TRUE);//魔導士の画像
					break;
				}

				case 3://諜報員
				{
					DrawGraphF(x * 64 + 192, y * 64, Espionage, TRUE);//諜報員の画像
					break;
				}

				case 4://騎士
				DrawGraphF(x * 64 + 192, y * 64, Knight, TRUE);//騎士の画像
					{
					break;
				}

				case 5://王
				{
					DrawGraphF(x * 64 + 192, y * 64, King, TRUE);//騎士の画像
					KingX = x;
					KingY = y;
					break;
				}

				case 6://相手の王
				{
					DrawRotaGraph3(x*64+256,y*64+65,0,0, 1.0f, 1.0f, PI, EKing, TRUE);//王の画像
					EKingX = x;
					EKingY = y;
					break;
				}


				}
			}
		}

		//アニメーション再生サンプル
		/*while (ProcessMessage() == 0)
		{
			DrawGraph(0, 0, MovieGraphHandle, FALSE);
			WaitTimer(10);
		}*/

		//文字列表示
		//DrawString(x, y, 表示する文字列(*char), 表示する際の文字の色(GetColor(r,g,b)));

		//画像表示
		//DrawGraph(x, y, img画像(int型), TRUE);

	}

	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}

//クリックする領域の判定
bool HitClick(int Cx,int Cy,int x1,int y1)
{
	if (Cx < x1 + 64 && x1 < Cx + 64 && Cy < y1 + 64 && y1 < Cy + 64)
	{
		return TRUE;
	}
	return FALSE;
}