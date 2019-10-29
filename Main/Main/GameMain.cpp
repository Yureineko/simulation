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
	int CanMoveMap[7][7] = {0};

	//駒保存用
	Piece piecetable[28];
	for (int i = 0, count = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (MainMap[i][j] >= 1)
			{
				piecetable[count].posX = j;
				piecetable[count].posY = i;
				piecetable[count].type = MainMap[i][j];
				if (i < 4)
				{
					piecetable[count].MeorEne = false;
				}
				else
				{
					piecetable[count].MeorEne = true;
				}
				count++;

				if (MainMap[i][j] == 1)
				{
					piecetable[count].movelimit = 1;
					piecetable[count].moverange[0][0] = 0; piecetable[count].moverange[0][1] = -1;
				}
				if (MainMap[i][j] == 2)
				{
					piecetable[count].movelimit = 12;
					piecetable[count].moverange[0][0] = -3;  piecetable[count].moverange[0][1] = 3;
					piecetable[count].moverange[1][0] = -3;  piecetable[count].moverange[1][1] = -3;
					piecetable[count].moverange[2][0] = -2;  piecetable[count].moverange[2][1] = 2;
					piecetable[count].moverange[3][0] = -2;  piecetable[count].moverange[3][1] = -2;
					piecetable[count].moverange[4][0] = -1;  piecetable[count].moverange[4][1] = 1;
					piecetable[count].moverange[5][0] = -1;  piecetable[count].moverange[5][1] = -1;
					piecetable[count].moverange[6][0] = 1;   piecetable[count].moverange[6][1] = 1;
					piecetable[count].moverange[7][0] = 1;   piecetable[count].moverange[7][1] = -1;
					piecetable[count].moverange[8][0] = 2;   piecetable[count].moverange[8][1] = 2;
					piecetable[count].moverange[9][0] = 2;   piecetable[count].moverange[9][1] = -2;
					piecetable[count].moverange[10][0] = 3;  piecetable[count].moverange[10][1] = 3;
					piecetable[count].moverange[11][0] = 3;  piecetable[count].moverange[11][1] = -3;
				}
				if (MainMap[i][j] == 3)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].moverange[0][0] = -3; piecetable[count].moverange[0][1] = 1;
					piecetable[count].moverange[1][0] = -3; piecetable[count].moverange[1][1] = -1;
					piecetable[count].moverange[2][0] = -1; piecetable[count].moverange[2][1] = 3;
					piecetable[count].moverange[3][0] = -1; piecetable[count].moverange[3][1] = -3;
					piecetable[count].moverange[4][0] = 1;  piecetable[count].moverange[4][1] = 3;
					piecetable[count].moverange[5][0] = 1;  piecetable[count].moverange[5][1] = -3;
					piecetable[count].moverange[6][0] = 3;  piecetable[count].moverange[6][1] = 1;
					piecetable[count].moverange[7][0] = 3;  piecetable[count].moverange[7][1] = -1;
				}
				if (MainMap[i][j] == 4)
				{
					piecetable[count].movelimit = 12;
					piecetable[count].moverange[0][0] = -3;  piecetable[count].moverange[0][1] = 0;
					piecetable[count].moverange[1][0] = -2;  piecetable[count].moverange[1][1] = 0;
					piecetable[count].moverange[2][0] = -1;  piecetable[count].moverange[2][1] = 0;
					piecetable[count].moverange[3][0] = 0;   piecetable[count].moverange[3][1] = 3;
					piecetable[count].moverange[4][0] = 0;   piecetable[count].moverange[4][1] = 2;
					piecetable[count].moverange[5][0] = 0;   piecetable[count].moverange[5][1] = 1;
					piecetable[count].moverange[6][0] = 0;   piecetable[count].moverange[6][1] = -1;
					piecetable[count].moverange[7][0] = 0;   piecetable[count].moverange[7][1] = -2;
					piecetable[count].moverange[8][0] = 0;   piecetable[count].moverange[8][1] = -3;
					piecetable[count].moverange[9][0] = 1;   piecetable[count].moverange[9][1] = 0;
					piecetable[count].moverange[10][0] = 2;  piecetable[count].moverange[10][1] = 0;
					piecetable[count].moverange[11][0] = 3;  piecetable[count].moverange[11][1] = 0;
				}
				if (MainMap[i][j] == 5)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].moverange[0][0] = -1; piecetable[count].moverange[0][1] = 1;
					piecetable[count].moverange[1][0] = -1; piecetable[count].moverange[1][1] = 0;
					piecetable[count].moverange[2][0] = -1; piecetable[count].moverange[2][1] = -1;
					piecetable[count].moverange[3][0] = 0;  piecetable[count].moverange[3][1] = 1;
					piecetable[count].moverange[4][0] = 0;  piecetable[count].moverange[4][1] = -1;
					piecetable[count].moverange[5][0] = 1;  piecetable[count].moverange[5][1] = 1;
					piecetable[count].moverange[6][0] = 1;  piecetable[count].moverange[6][1] = 0;
					piecetable[count].moverange[7][0] = 1;  piecetable[count].moverange[7][1] = -1;
				}
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
	bool saveclickflag;
	bool clickflag;
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;
	clickflag = false;
	//[][0]に駒の種類、[][1]に生存状況、[][2]にx座標、[][3]にy座標
	int MyPieceInfo[14][4]
	{
		{1,1,1,1},{1,1,1,2}
	};

	POS movePos = {0,0};
	int movepiece = -1;
	bool moveflag = false;

	int EKingX = 6, EKingY = 6;//敵の王の位置X,Y


	//int King = LoadGraph("image\\King.png");

	
	t_chara = LoadGraph("image\\キャラ1(仮).png");
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

	
	
	int turn=0;//ターン変数....0:自分のターン　1:相手のターン
	int movepointX;//駒の移動の変数(MainMapと照らし合わせて使用する。)
	int Mx, My;//マウスの位置




	int win_flag = false;//勝った時のフラグ
	int lose_flag = false;//負けた時のフラグ



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


	//while(裏画面)



	//ここでゲームのメイン部分構築
	while (ProcessMessage() != -1)
	{
		ScreenFlip();//画像のフリップ(切り替え)
		ClearDrawScreen();//画像のクリア

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
		if (turn == 0)
		{
			if (clickflag == false && saveclickflag == true)
			{
				if (moveflag == false)
				{
					POS SavePos = HitPos(clickpos.posX, clickpos.posY);
					for (int i = 0; i < 28; i++)
					{
						if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0)
						{
							movepiece = i;
							moveflag = true;
							clickflag = true;
							/*for (int j = 0; j < piecetable[i].movelimit; j++)
							{

							}*/
						}
					}
				}
				else
				{
					if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7)
					{
						int latemove = -1;
						movePos = HitPos(clickpos.posX, clickpos.posY);
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




			//マウスの左クリックが押されているか
			//マウスが押されていないとき
			//ここでクリックできる領域を設定
			//クリックした先が0ならそこに描画
			/*
			for (int y = 0; y < 7; y++)
			{
				for (int x = 0; x < 7; x++)
				{
					switch (MainMap[y][x])
					{
					case 1:
						//兵士の生成
						soldier = new SOLDIER(x * 64, y * 64);
						MainMap[y][x] = 1;
						soldier->Draw();
						break;
					case 2:
						//魔導士の生成
						sorcerer = new SORCERER(x * 64, y * 64);
						MainMap[y][x] = 2;
						sorcerer->Draw();
						break;
					case 3:
						//諜報員の生成
						espionage = new ESPIONAGE(x * 64, y * 64);
						MainMap[y][x] = 3;
						espionage->Draw();
						break;

					case 4:
						//騎士の生成
						knight = new KNIGHT(x * 64, y * 64);
						MainMap[y][x] = 4;
						knight->Draw();
						break;

					case 5:
						   //王の生成
						   king = new KING(x * 64, y * 64);
						   MainMap[y][x] = 5;
						   king->Draw();
						break;
					}
					
				}
			}*/
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
					DrawRotaGraph(piecetable[i].posX * 64 + 224, piecetable[i].posY * 64+32,1.0f,PI, EKing, TRUE);
					break;
				}
				if (i == movepiece)
				{
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, GreenFilter, TRUE);
				}
			}

			//king->Draw();
			
		


		
		}
		
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