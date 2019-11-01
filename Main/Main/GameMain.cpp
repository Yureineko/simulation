#include "DxLib.h"
#include "Piece.h"
#include "Grobal.h"

#define SCREEN_PIXWIDTH		832
#define SCREEN_PIXHEIGHT	448
#define POPUP_X 192//左↑の点
#define POPUP_Y 0
#define POPDOWN_X 64
#define POPDOWN_Y 64

#define PI	3.1415926535897932384626433832795f

//クリックの領域をチェックする関数
bool HitClick(int Cx, int Cy, int x1, int y1);

bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey);

POS HitPos(int PosX, int PosY);

void CheckMoveRange(Piece piece, Piece AllPiece[]);

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
	int MainMap[7][7] =
	{
		{ 2,3,4,6,4,3,2 },
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
	//6.相手の王

	//駒保存用
	//ここで駒の移動距離やクラスの初期化を行う
	Piece piecetable[28];
	//MainMapから値を取得し、その位置でその役職の情報を得る
	for (int i = 0, count = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			//0じゃない(そこに駒がある)場合
			if (MainMap[i][j] >= 1)
			{
				//posX,posYにそれぞれ値を入れる
				piecetable[count].posX = j;
				piecetable[count].posY = i;
				//マップナンバーから役職を特定する
				piecetable[count].type = MainMap[i][j];
				//半分より上なら敵駒、下なら自陣の駒という風に設定する
				if (i < 4)
				{
					piecetable[count].MeorEne = false;
				}
				else
				{
					piecetable[count].MeorEne = true;
				}
				//役職をもとに移動設定を入れていく(クラス化予定あり)
				//兵士
				if (MainMap[i][j] == 1)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 1;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//魔導士
				if (MainMap[i][j] == 2)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 0;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 3;
					piecetable[count].diald = 3;
					piecetable[count].diaru = 3;
					piecetable[count].diard = 3;
				}
				//諜報員
				if (MainMap[i][j] == 3)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].spicialmoverange[0][0] = -2; piecetable[count].spicialmoverange[0][1] = 1;
					piecetable[count].spicialmoverange[1][0] = -2; piecetable[count].spicialmoverange[1][1] = -1;
					piecetable[count].spicialmoverange[2][0] = -1; piecetable[count].spicialmoverange[2][1] = 2;
					piecetable[count].spicialmoverange[3][0] = -1; piecetable[count].spicialmoverange[3][1] = -2;
					piecetable[count].spicialmoverange[4][0] = 1;  piecetable[count].spicialmoverange[4][1] = 2;
					piecetable[count].spicialmoverange[5][0] = 1;  piecetable[count].spicialmoverange[5][1] = -2;
					piecetable[count].spicialmoverange[6][0] = 2;  piecetable[count].spicialmoverange[6][1] = 1;
					piecetable[count].spicialmoverange[7][0] = 2;  piecetable[count].spicialmoverange[7][1] = -1;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 0;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//騎士
				if (MainMap[i][j] == 4)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 3;
					piecetable[count].moveright = 3;
					piecetable[count].movefront = 3;
					piecetable[count].moveback = 3;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//自陣王
				if (MainMap[i][j] == 5)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 1;
					piecetable[count].moveright = 1;
					piecetable[count].movefront = 1;
					piecetable[count].moveback = 1;
					piecetable[count].dialu = 1;
					piecetable[count].diald = 1;
					piecetable[count].diaru = 1;
					piecetable[count].diard = 1;
				}
				count++;
			}
		}
	}

	SORCERER*sorcerer;//魔導士の本体
	enum VEC Sor_vec;//魔導士の移動方向

	ESPIONAGE*espionage;//諜報員の本体
	enum VEC Es_Vec;//諜報員の移動方向

	KNIGHT*knight;//騎士の本体
	enum VEC Kn_vec;//騎士の移動方向

	SOLDIER*soldier;//兵士の本体
	enum VEC Sol_vec;//兵士の移動方向

	KING* king;//王の本体
	enum VEC Kin_vec;//王の移動方向

	EnemyKING*enemyking;//敵王の本体
	enum VEC EKin_vec;//敵王の移動方向

	//画像int変換関数
	//int img = LoadGraph("画像名");
	

	int t_chara;//仮キャラクターの表示　1体目
	int t_chara2;//仮キャラクターの表示　2体目

	int Soldier=LoadGraph("image\\Soldier(64).png");//ここに兵士の画像
	int Sorcerer=LoadGraph("image\\Sorcerer(64).png");//ここに魔導士の画像
	int Espionage =LoadGraph("image\\Espionage(64).png");//ここに諜報員の画像
	int Knight =LoadGraph("image\\Knight(64).png");//ここに騎士の画像
	int King =LoadGraph("image\\King(64).png");//ここに王の画像
	int EKing = LoadGraph("image\\King(64).png");//ここに王の画像

	int GreenFilter = LoadGraph("image\\greenfilter.png");

	//一旦ここで位置移動する。後で消すかも。
	int SoldX = 1, SoldY = 1;//兵士の位置X,Y
	int SorcX = 2, SorcY = 2;//魔導士の位置X,Y
	int EspiX = 3, EspiY = 3;//諜報員の位置X,Y
	int KnightX = 4, KnightY = 4;//騎士の位置X,Y
	int KingX = 5, KingY = 5;//王の位置X,Y	

	//ボタン管理座標用
	Pos clickpos;     //クリック位置保存用
	Pos outclickpos;  //クリック離した位置保存用
	bool saveclickflag;//クリックポジション取得の制御を行う為のフラグ
	bool clickflag;    //クリック制御を行う為のフラグ
	//初期化
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;
	clickflag = false;

	POS movePos = {0,0}; //動く先のポジション
	int movepiece = -1;  //動かす駒のナンバーを保存しておく用
	bool moveflag = false;//動かす駒を選ぶのか、動いてほしい場所を選ぶのか

	int EKingX = 6, EKingY = 6;//敵の王の位置X,Y


	//int King = LoadGraph("image\\King.png");
	Scenes scene = TITLE;
	
	t_chara = LoadGraph("image\\キャラクターC(仮).png");
	t_chara2 = LoadGraph("image\\キャラ2(仮).png");
	

	int sc = LoadGraph("image\\BackGround.png");

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

	
	
	bool turn=true;//ターン変数....0:自分のターン　1:相手のターン
	int movepointX;//駒の移動の変数(MainMapと照らし合わせて使用する。)
	int Mx, My;//マウスの位置




	bool win_flag = false;//勝った時のフラグ
	bool lose_flag = false;//負けた時のフラグ
	bool gameend_flag = false;//ゲーム終了する際に使うフラグ



	//---------マウス操作の変数--------
	
	

	 //GetMousePoint(&Mx,&My);//マウスの現在位置取得

	//マウスをwindow上に表示させる。
	//SetMouseDispFlag(TRUE);

	//バックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);

	int cx, cy;
	bool Click_flag = 0;


	//DXライブラリを初期化
	if (DxLib_Init() == -1)
	{
		return -1;//エラーが出たら強制終了

	}

	while (ProcessMessage() != -1)
	{
		switch (scene)
		{
		case TITLE:
			SetFontSize(16);
			DrawString(0, 32, "タイトル(仮)", GetColor(255, 255, 255));
			DrawString(0, 48, "十字キー上で始める", GetColor(255, 255, 255));
			DrawString(0, 64, "十字キー下で終わる", GetColor(255, 255, 255));
			DrawString(0, 256, "帰ってベルセリアやりたい", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_UP))
			{
				scene = SELECT;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN))
			{
				gameend_flag = true;
				break;
			}
			break;

		case SELECT:
			//初期化タイミング
			DrawString(0, 48, "十字キー右で始める", GetColor(255, 255, 255));
			DrawString(0, 64, "十字キー左で終わる", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				scene = GAME;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT))
			{
				gameend_flag = true;
				break;
			}
			break;

		case GAME:

			//ここでゲームのメイン部分構築
			//マウスの状態を確認する
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				//左クリックが押されたとき、押した場所を確認する
				if (saveclickflag == false)
				{
					saveclickflag = true;
					GetMousePoint(&clickpos.posX, &clickpos.posY);
				}
			}
			else
			{
				//左クリックが離されたとき、離した場所を確認する
				if (saveclickflag == true)
				{
					saveclickflag = false;
					GetMousePoint(&outclickpos.posX, &outclickpos.posY);
				}
			}

		//自分のターン以外は操作を不可能にする
		if (turn == true)
		{
			//クリックしたとき
			if (clickflag == false && saveclickflag == true)
			{
				//キャラを選択し緑色のマス(行動できる範囲)を描画
				if (moveflag == false)
				{
					//クリックしたマスを取得しそのマスに該当する駒を探す
					POS SavePos = HitPos(clickpos.posX, clickpos.posY);
					for (int i = 0; i < 28; i++)
					{
						//該当する駒があり、その駒が生きていれば
						if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0)
						{
							//その駒の対応ナンバーを一時保存する
							movepiece = i;
							//行動場所を選ぶようにする
							moveflag = true;
							clickflag = true;
							//移動できる範囲を緑色で指定する
							CheckMoveRange(piecetable[i], piecetable);
						}
					}
				}
				//緑色のマスを選択し上記で選んだ駒をその場所に移動
				else
				{
					//選んだマスを取得
					movePos = HitPos(clickpos.posX, clickpos.posY);
					//そのマスが範囲内
					if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7 && CanMoveMap[movePos.y][movePos.x] == 1)
					{
						int latemove = -1;
						for (int i = 0; i < 28; i++)
						{
							if (movePos.x == piecetable[i].posX && movePos.y == piecetable[i].posY && i != movepiece)
							{
								latemove = i;
							}
						}
						if (latemove != -1)
						{
							if (piecetable[movepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
							{
								piecetable[movepiece].posX = movePos.x;
								piecetable[movepiece].posY = movePos.y;
								if (piecetable[latemove].type == 6)
									win_flag = true;
								if (piecetable[latemove].type == 5)
									lose_flag = true;
								piecetable[latemove].type = 0;
								movepiece = -1;
							}
						}
						else
						{
							piecetable[movepiece].posX = movePos.x;
							piecetable[movepiece].posY = movePos.y;
							movepiece = -1;
						}
						clickflag = true;
						moveflag = false;

							turn = false;

							for (int i = 0; i < 7; i++)
							{
								for (int j = 0; j < 7; j++)
								{
									CanMoveMap[i][j] = 0;
								}
							}
							/*
							if(piecetable[movepiece].MeorEne)
							movepiece = i;
							moveflag = true;
							*/
						}
					}
				}
				else if (saveclickflag == false)
				{
					clickflag = false;
				}



				GetMousePoint(&Mx, &My);



			}


			//Zキーを押すと手番を自分に戻す。
			if (CheckHitKey(KEY_INPUT_Z))
			{
				turn = true;
			}
			
			//背景の画像表示	
			LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
			DrawGraph(0, 0, t_chara, TRUE);//プレイヤー1の描画
			DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
			for (int i = 0; i < 28; i++)
			{
				switch (piecetable[i].type)
				{
				case 1:
					//兵士の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Soldier, TRUE);
					break;
				case 2:
					//魔導士の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Sorcerer, TRUE);
					break;
				case 3:
					//諜報員の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Espionage, TRUE);
					break;

				case 4:
					//騎士の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Knight, TRUE);
					break;

				case 5:
					//王の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, King, TRUE);
					break;

				case 6:
					//敵王の生成
					DrawRotaGraph(piecetable[i].posX * 64 + 224, piecetable[i].posY * 64 + 32, 1.0f, PI, EKing, TRUE);
					break;
				}
				if (CanMoveMap[piecetable[i].posY][piecetable[i].posX] == 1)
				{
					//緑の移動範囲描画
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, GreenFilter, TRUE);
				}
			}
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (CanMoveMap[i][j] == 1)
					{
						DrawGraphF(j * 64 + 192, i * 64, GreenFilter, TRUE);
					}
				}
			}




			if (win_flag == true)
			{
				SetFontSize(40);
				//LoadGraphScreen(64, 0, "image\\駒.png", TRUE);
				DrawString(350, 250, "YOU WIN", GetColor(255, 0, 0));
				DrawString(250, 300, "十字キー右でタイトルへ", GetColor(255, 0, 0));
				DrawString(250, 350, "十字キー左で終了", GetColor(255, 0, 0));
			}
			else if (lose_flag == true)
			{
				SetFontSize(40);
				DrawString(350, 250, "YOU LOSE", GetColor(255, 0, 0));
				DrawString(250, 300, "十字キー右でタイトルへ", GetColor(255, 0, 0));
				DrawString(250, 350, "十字キー左で終了", GetColor(255, 0, 0));
			}

			if (CheckHitKey(KEY_INPUT_UP) && (win_flag == true || lose_flag == true))
			{
				scene = TITLE;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) && (win_flag == true || lose_flag == true))
			{
				gameend_flag = true;
				break;
			}
			//king->Draw();







			//この辺り?で勝敗判定を行ってbreakでwhile文を抜ける。



			//outposが-1以外の場合数値を-1にする
			if (outclickpos.posX != -1 && outclickpos.posY != -1)
			{
				clickpos.posX = -1;
				clickpos.posY = -1;
				outclickpos.posX = -1;
				outclickpos.posY = -1;
			}

			//----------登録した駒の移動描画-----------

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



			break;
		}

		ScreenFlip();//画像のフリップ(切り替え)
		ClearDrawScreen();//画像のクリア

		if (gameend_flag == true)
		{
			break;
		}
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

//ボタンチェック用関数
bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey)
{
	if (pushclick.posX >= button.posX && pushclick.posX <= button.posX + sizex &&
		pushclick.posY >= button.posY && pushclick.posY <= button.posY + sizey &&
		outclick.posX >= button.posX && outclick.posX <= button.posX + sizex &&
		outclick.posY >= button.posY && outclick.posY <= button.posY + sizey)
	{
		//押した位置、左クリックを話した位置が共にボタン内であれば
		//trueを返す
		return true;
	}
	else
	{
		//そうでなければfalse
		return false;
	}
}

//クリックしたところが何の駒の場所かを調べる。
POS HitPos(int PosX, int PosY)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (HitClick(PosX, PosY, POPUP_X + POPDOWN_X * i, POPUP_Y + POPDOWN_Y * j) == true)
			{
				POS pos;
				pos.x = i;
				pos.y = j;

				return pos;
			}
		}
	}
	POS nullpos = {-1,-1};

	return nullpos;
}

//行動範囲領域判定
void CheckMoveRange(Piece piece, Piece AllPiece[])
{
	//前判定
	for (int i = 1; i <= piece.movefront; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX && AllPiece[j].posY == piece.posY - i && AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0)
						CanMoveMap[piece.posY - i][piece.posX] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0)
				CanMoveMap[piece.posY - i][piece.posX] = 1;
		}
	}
	//後ろ判定
	for (int i = 1; i <= piece.moveback; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i <= 6)
						CanMoveMap[piece.posY + i][piece.posX] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i <= 6)
				CanMoveMap[piece.posY + i][piece.posX] = 1;
		}
	}
	//左判定
	for (int i = 1; i <= piece.moveleft; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posX - i >= 0)
						CanMoveMap[piece.posY][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posX - i >= 0)
				CanMoveMap[piece.posY][piece.posX - i] = 1;
		}
	}
	//右判定
	for (int i = 1; i <= piece.moveright; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posX + i <= 6)
						CanMoveMap[piece.posY][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posX + i <= 6)
				CanMoveMap[piece.posY][piece.posX + i] = 1;
		}
	}
	//左斜め上判定
	for (int i = 1; i <= piece.dialu; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY - i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0 && piece.posX - i >= 0)
						CanMoveMap[piece.posY - i][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0 && piece.posX - i >= 0)
				CanMoveMap[piece.posY - i][piece.posX - i] = 1;
		}
	}
	//左斜め下判定
	for (int i = 1; i <= piece.diald; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + i <= 6 && piece.posX - i >= 0)
						CanMoveMap[piece.posY + i][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY + i <= 6 && piece.posX - i >= 0)
				CanMoveMap[piece.posY + i][piece.posX - i] = 1;
		}
	}
	//右斜め上判定
	for (int i = 1; i <= piece.diaru; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY - i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0 && piece.posX + i <= 6)
						CanMoveMap[piece.posY - i][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0 && piece.posX + i <= 6)
				CanMoveMap[piece.posY - i][piece.posX + i] = 1;
		}
	}
	//右斜め下判定
	for (int i = 1; i <= piece.diard; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + i <= 6 && piece.posX + i <= 6)
						CanMoveMap[piece.posY + i][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY + i <= 6 && piece.posX + i <= 6)
				CanMoveMap[piece.posY + i][piece.posX + i] = 1;
		}
	}
	//特殊位置移動判定
	for (int i = 0; i < piece.movelimit; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + piece.spicialmoverange[i][0] && AllPiece[j].posY == piece.posY + piece.spicialmoverange[i][1] && AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + piece.spicialmoverange[i][1] >= 0 && piece.posY + piece.spicialmoverange[i][1] <= 6 &&
						piece.posX + piece.spicialmoverange[i][0] >= 0 && piece.posX + piece.spicialmoverange[i][0] <= 6)
						CanMoveMap[piece.posY + piece.spicialmoverange[i][1]][piece.posX + piece.spicialmoverange[i][0]] = 1;
					breakflag = true;
				}
			}
		}
		if (breakflag == false)
		{
			if (piece.posY + piece.spicialmoverange[i][1] >= 0 && piece.posY + piece.spicialmoverange[i][1] <= 6 &&
				piece.posX + piece.spicialmoverange[i][0] >= 0 && piece.posX + piece.spicialmoverange[i][0] <= 6)
				CanMoveMap[piece.posY + piece.spicialmoverange[i][1]][piece.posX + piece.spicialmoverange[i][0]] = 1;
		}
	}
}