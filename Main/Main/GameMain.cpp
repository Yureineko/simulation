#include "Grobal.h"

//クリックの領域をチェックする関数
bool HitClick(int Cx, int Cy, int x1, int y1);

bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey);

POS HitPos(int PosX, int PosY);//位置を取得

POS ZeroPos(int ZposX, int ZposY);//位置を取得

void CheckMoveRange(Piece piece, Piece AllPiece[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//IPアドレス設定用
	IPDATA Ip;
	//接続ポート
	int port = -1;
	char Strbuf[256] = { 0,0,-1 };//データバッファ
	char STR[256] = { NULL };
	DATA d;//送信用データ(構造体)

	//windowモードで起動
	ChangeWindowMode(TRUE);
	//Dxライブラリの初期化
	DxLib_Init();
	//ウィンドウ名設定
	SetMainWindowText("SimulatioN GamE");
	//バックグラウンドでも動くように設定
	SetAlwaysRunFlag(TRUE);
	//ゲームウインドウサイズ
	SetGraphMode(832, 448, 32);
	//フォント確定
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	//UDP通信用のソケットハンドルの設定
	int NetUDPHandle = MakeUDPSocket(99);//配列で作るソケットハンドル

	//先攻後攻の判定(仮置き　一旦コメントアウト中)
	int Random[1];
	int Green = GetColor(0, 255, 0);
	
	//バックグラウンドの再生
	SetAlwaysRunFlag(TRUE);

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
	//7.壁

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
	
	int title = LoadGraph("image\\タイトル画面(仮候補).png");//タイトル画面読み込み
	int textbox = LoadGraph("image\\hakkou1.png");//テキストボックスの表示
	int t_charaB;//仮背景(プレイヤー1)の表示	
	int t_charaB2;//仮背景(プレイヤー2)の表示
	int t_chara,t_charawin,t_charalose,t_charaskill;//仮キャラクター(プレイヤー1)の表示　1体目
	int t_chara2, t_chara2win, t_chara2lose, t_chara2skill;//仮キャラクター(プレイヤー2)の表示　2体目
	int t_chara3, t_chara3win, t_chara3lose, t_chara3skill;//仮キャラクター(プレイヤー3)の表示　3体目



	unsigned int DeadlyButton;//キャラの必殺技のボタンの表示
	DeadlyButton = GetColor(0, 0, 255);//ボタンの青色を取得
	int Skillbotton = LoadGraph("image\\能力発動！ボタン.png");//能力発動ボタンを表示
	int Skillwaite = LoadGraph("image\\能力待機.png");//能力発動待機ボタンを表示


	int Soldier=LoadGraph("image\\ユニット\\Soldier(64).png");//ここに兵士の画像
	int Sorcerer=LoadGraph("image\\ユニット\\Sorcerer(64).png");//ここに魔導士の画像
	int Espionage =LoadGraph("image\\ユニット\\Espionage(64).png");//ここに諜報員の画像
	int Knight =LoadGraph("image\\ユニット\\Knight(64).png");//ここに騎士の画像
	int King =LoadGraph("image\\ユニット\\King(64).png");//ここに王の画像
	int EKing = LoadGraph("image\\ユニット\\King(64).png");//ここに王の画像
	int BB = LoadGraph("image\\BB.png");//自軍下敷き
	int RB = LoadGraph("image\\RB.png");//敵軍下敷き
	int Turn = LoadGraph("image\\ユニット\\TURN WINDOW.png");//ターンプレイヤーをわかりやすくするための画像

	//駒が通行できない壁
	//int wall;//切り取った壁
	int Wall = LoadGraph("image\\ユニット\\King(仮).png");//ここに必殺技(壁)の画像登録
	//wall=DerivationGraph(0,0, 64, 64, Wall);//壁の画像の切り取り


	//移動範囲の読み込み
	int GreenFilter = LoadGraph("image\\greenfilter.png");//駒の移動範囲の描画
	int RedFilter = LoadGraph("image\\redfilter.png");//壁の出現範囲の描画


	//一旦ここで位置移動する。後で消すかも。
	int SoldX = 1, SoldY = 1;//兵士の位置X,Y
	int SorcX = 2, SorcY = 2;//魔導士の位置X,Y
	int EspiX = 3, EspiY = 3;//諜報員の位置X,Y
	int KnightX = 4, KnightY = 4;//騎士の位置X,Y
	int KingX = 5, KingY = 5;//王の位置X,Y
	int WallX = 7, WallY = 7;//壁の位置X,Y
	//キャラ選択用変数
	int charaselect = 0;
	int enemychara = 0;

	//ボタン管理座標用
	Pos clickpos;     //クリック位置保存用
	Pos outclickpos;  //クリック離した位置保存用
	bool saveclickflag;//クリックポジション取得の制御を行う為のフラグ
	bool clickflag;    //クリック制御を行う為のフラグ

	//能力使用時保存配列
	//[0][]に自軍の情報を、[1][]に敵軍の情報を入れる
	//[][0] = スキル発動のX位置情報、[][1] = スキル発動のY位置情報
	//[][2] = スキルの種類情報(1には地雷を入れてます)
	int abilityinfo[2][3] = { {0}, {0} };

	//壁と地雷の能力ボタン
	Pos skillpos;//クリックした能力ボタン部分
	Pos outskillpos;//クリック離した能力ボタン部分
	bool saveskillflag;//クリックポジション取得の制御を行う為のフラグ スキル
	bool Sclickflag;    //クリック制御を行う為のフラグ

	//初期化
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;

	//壁
	skillpos.posX = -1;
	skillpos.posY = -1;
	outskillpos.posX = -1;
	outskillpos.posY = -1;
	saveskillflag = false;
	Sclickflag = false;


	bool skillclickflag;//必殺ボタンをクリックしたときのフラグ
	skillclickflag = false;

	bool skillbuttonflag;//スキルのボタンの制御
	skillbuttonflag = false;
	
	bool skillflagremove;//スキル待機中状態でMap以外をクリックしたときのフラグ
	skillflagremove = false;


	bool skillredflag;//壁の表示可能フラグ
	skillredflag = false;

	bool wallskill1;//キャラ1の壁の描画フラグ
	wallskill1 = false;

	POS movePos = {0,0}; //動く先のポジション
	POS wallPos = { 0,0 };//壁を表示出来る場所

	int movepiece = -1;  //動かす駒のナンバーを保存しておく用
	int Enemovepiece = -1; //敵の動かす駒のナンバーを保存しておく用
	bool moveflag = false;//動かす駒を選ぶのか、動いてほしい場所を選ぶのか


	int appearanceWall = -1;//出現
	bool appearanceflag = false;//出現する場所を選ぶ

	int EKingX = 6, EKingY = 6;//敵の王の位置X,Y


	//int King = LoadGraph("image\\King.png");
	Scenes scene = TITLE;
	
	t_charaB = LoadGraph("image\\キャラ背景候補1.png");
	t_charaB2 = LoadGraph("image\\キャラ背景候補3.png");	

	int sc = LoadGraph("image\\BackGround.png");

	//音声int変換関数
	//int bgm = LoadSoundMem("音楽名");

	//ゲームメインの音楽再生
	int  Mainbgm = LoadSoundMem("sound\\");

	//駒が動いた場合の効果音
	int  Movebgm = LoadSoundMem("sound\\nc184661.mp3");

	//アニメーション登録サンプル
	int MovieGraphHandle;

	MovieGraphHandle=LoadGraph("image\\nc157304.mp4");
	PlayMovieToGraph(MovieGraphHandle);


	//test用サウンド
	int se=LoadSoundMem("sound\\test.mp3");
	
	
	bool turn;//ターン変数....0:自分のターン　1:相手のターン

	int movepointX;//駒の移動の変数(MainMapと照らし合わせて使用する。)
	int mx, my;//マウスの位置
	int Mx, My;

	bool win_flag;//勝った時のフラグ
	bool lose_flag;//負けた時のフラグ

	bool gameend_flag = false;//ゲーム終了する際に使うフラグ
	bool time = false;//タイムラグ発生用フラグ

	unsigned int cr;//辺り範囲の描画の


	//---------マウス操作の変数--------
	 //GetMousePoint(&Mx,&My);//マウスの現在位置取得

	//バックバッファに描画
	SetDrawScreen(DX_SCREEN_BACK);

	bool Click_flag = 0;

	//IPAdress取得
	FILE *fp;
	char ipstr[256] = {0};

	fopen_s(&fp, "IPAdress.txt", "r");

	fgets(ipstr, 255, fp);
	Ip.d1 = atoi(ipstr);
	fgets(ipstr, 255, fp);
	Ip.d2 = atoi(ipstr);
	fgets(ipstr, 255, fp);
	Ip.d3 = atoi(ipstr);
	fgets(ipstr, 255, fp);
	Ip.d4 = atoi(ipstr);

	fclose(fp);

	char RecvData[10] = {0};
	char SendData[10] = {0};
	int Data = 0;
	int UserNum = -1;
	int connecttime = 0;

	//DXライブラリを初期化
	if (DxLib_Init() == -1)
	{
		return -1;//エラーが出たら強制終了

	}

	//仮置きここから
	char StrBuf[256] = { 0,0,-1 };//データバッファ

	//初回データ送信	16 416 4 10
	sprintf_s(STR, 256, "%d,%d,%d,%d,%d,%d"
	);
	//ここまで

	while (ProcessMessage() != -1)
	{
		switch (scene)
		{
		case TITLE:
			//勝敗・ターンフラグ初期化
			saveclickflag = false;
			clickflag = false;
			win_flag = false;//勝った時のフラグ
			lose_flag = false;//負けた時のフラグ
			turn = true;//先行後攻のフラグ
			time = false;

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
			}//ここまでクリックの処理
			

			//駒保存用
			//ここで駒の移動距離やクラスの初期化を行う
			Piece piecetable[28];

			//壁保存用
			Walls wall[49];
			//MainMapから値を取得し、その位置でその役職の情報を得る
			for (int i = 0, count = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					//0じゃない(そこに駒がある)場合
					if (MainMap[i][j] >= 1 && MainMap[i][j] <= 6)
					{
						//posX,posYにそれぞれ値を入れる
						piecetable[count].posX = j;
						piecetable[count].posY = i;
						//マップナンバーから役職を特定する
						piecetable[count].type = MainMap[i][j];
						//半分より上なら敵駒、下なら自陣の駒という風に設定する
						if (i < 4)
						{
							//敵軍
							piecetable[count].MeorEne = false;
							
						}
						else
						{
							//自軍
							piecetable[count].MeorEne = true;
							
						}
						//移動
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
						//自陣王
						if (MainMap[i][j] == 6)
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
						//敵の兵士
						/*if (MainMap[i][j] == 7)
						{
							piecetable[count].movelimit = 0;
							piecetable[count].moveleft = 0;
							piecetable[count].moveright = 0;
							piecetable[count].movefront = 0;
							piecetable[count].moveback = 1;
							piecetable[count].dialu = 0;
							piecetable[count].diald = 0;
							piecetable[count].diaru = 0;
							piecetable[count].diard = 0;
						}*/

						count++;
					}
				}
			}

			SetFontSize(16);
			DrawExtendGraphF(-50, -50, 882, 498, title, TRUE);//タイトルの描画
			DrawExtendGraphF(300, 200, 500, 250, textbox, TRUE);//テキストボックスの描画
			DrawExtendGraphF(300, 300, 500, 350, textbox, TRUE);//テキストボックスの描画
			DrawString(250, 165, "BATTLE・OF・WARGAMES", GetColor(255, 255, 255));
			DrawString(375, 215, "始める", GetColor(255, 255, 255));
			DrawString(375, 315, "終わる", GetColor(255, 255, 255));

			//確認用の画像表示
			//t_chara = LoadGraph("image\\キャラクター1\\キャラクター1リサイズ透過.png");
			//t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2メイン.png");
			//t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3立ち絵.png");
			//DrawGraph(0, 0, t_charaB, TRUE);//プレイヤー1の背景の描画
			//DrawGraph(640, 0, t_charaB2, TRUE);//プレイヤー2の背景の描画
			//DrawGraph(0, 0, t_chara3, TRUE);//プレイヤー1の描画
			//DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
			//DrawExtendGraphF(20, 260, 170, 330, Turn, TRUE);
			//DrawExtendGraphF(662, 260, 812, 330, Turn, TRUE);

			if (saveclickflag == true)
			{
				if (clickflag == false)
				{
					if (300 <= clickpos.posX&&clickpos.posX <= 500 && 200 <= clickpos.posY&&clickpos.posY <= 250)
					{
						SendData[ISCONNECT] = 1;
						NetWorkSendUDP(NetUDPHandle, Ip, 30, SendData, sizeof(SendData));
						//デバッグなう
						scene = GAME;
						abilityinfo[0][0] = 2;
						abilityinfo[0][1] = 2;
						abilityinfo[0][2] = 1;
						abilityinfo[1][0] = 5;
						abilityinfo[1][1] = 3;
						abilityinfo[1][2] = 1;
					}
					else if (300 <= clickpos.posX&&clickpos.posX <= 500 && 300 <= clickpos.posY&&clickpos.posY <= 350)
					{
						gameend_flag = true;
					}
				}
			}
			break;
			//ネットワークのシーン
		case CONNECT:

			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
			}

			//通信確認用
			if (UserNum != -1)
			{
				SendData[ISCONNECT] = 2;
				NetWorkSendUDP(NetUDPHandle, Ip, UserNum, SendData, sizeof(SendData));
				for (int i = 0; i < 10; i++)
					SendData[i] = 0;
			}

			if (RecvData[ISCONNECT] >= 1)
			{
				if (RecvData[ISCONNECT] == 1)
				{
					DrawString(0, 32, "対戦相手募集中...", GetColor(255, 255, 255));
					connecttime = 0;
				}
				else
				{
					DrawString(0, 32, "接続確認中...", GetColor(255, 255, 255));
					connecttime++;
				}
			}
			else
			{
				DrawString(0, 32, "サーバー接続にゃう...", GetColor(255, 255, 255));
			}

			if (connecttime == 60)
			{
				connecttime = 0;
				scene = SELECT;
			}
			break;
			//キャラセレクト画面
		case SELECT:
			//初期化
			GetMousePoint(&Mx, &My);//カーソルの現在位置を取得
			clickpos.posX = -1;
			clickpos.posY = -1;
			outclickpos.posX = -1;
			outclickpos.posY = -1;
			t_chara = LoadGraph("image\\キャラクター1\\キャラクター1リサイズ透過.png");
			t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2メイン.png");
			t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3立ち絵.png");

			//初期化タイミング
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
			DrawExtendGraphF(0, 50, 416, 498, t_charaB, TRUE);//プレイヤー1の背景の描画
			DrawGraph(115, 50, t_chara, TRUE);//プレイヤー1の描画
			DrawExtendGraphF(0, 183, 416, 631, t_charaB2, TRUE);//プレイヤー2の背景の描画
			DrawGraph(115, 183, t_chara2, TRUE);//プレイヤー2の描画
			DrawExtendGraphF(0, 316, 416, 764, t_charaB, TRUE);//プレイヤー3の背景の描画
			DrawGraph(115, 316, t_chara3, TRUE);//プレイヤー3の描画

			DrawGraph(0, 0, textbox, TRUE);//テキストボックスの描画
			DrawExtendGraphF(416, 50, 832, 448, textbox, TRUE);//テキストボックスの描画

			if (charaselect == 0)
			{
				DrawString(32, 16, "キャラを選択してください", GetColor(255, 255, 255));
			}
			else
			{
				DrawString(32, 16, "相手キャラ選択中..", GetColor(255, 255, 255));
			}


			if (0 <= Mx && Mx <= 416 && 50 <= My && My <= 183)
			{
				DrawString(480, 180, "光星羅", GetColor(255, 255, 255));
				DrawString(480, 250, "ボードゲーム同好会初代会長", GetColor(255, 255, 255));
				//DrawString(480, 266, "ユニットが侵入できない", GetColor(255, 255, 255));
				//DrawString(480, 282, "縦に1列横に3列の防壁を設置する", GetColor(255, 255, 255));
			}
			else if (0 <= Mx && Mx <= 416 && 183 < My && My <= 316)
			{
				DrawString(480, 180, "不知火火燐", GetColor(255, 255, 255));
				DrawString(480, 250, "ボードゲームエンジョイ勢", GetColor(255, 255, 255));
				//DrawString(480, 266, "地雷を設置する", GetColor(255, 255, 255));
				//DrawString(480, 282, "地雷を踏んだユニットは即座に退場する", GetColor(255, 255, 255));
			}
			else if (0 <= Mx && Mx <= 416 && My > 316)
			{
				DrawString(480, 180, "藤堂氷華", GetColor(255, 255, 255));
				DrawString(480, 250, "ボードゲーム初心者", GetColor(255, 255, 255));
			}

			if (saveclickflag == true)
			{
				if (clickflag == false)
				{
					if (charaselect == 0)
					{
						if (clickpos.posX <= 416 && 50 <= clickpos.posY&&clickpos.posY <= 183)
						{
							charaselect = 1;
							clickflag = true;
						}
						if (clickpos.posX <= 416 && 183 < clickpos.posY&&clickpos.posY <= 316)
						{
							charaselect = 2;
							clickflag = true;
						}
						if (clickpos.posX <= 416 && clickpos.posY > 316)
						{
							charaselect = 3;
							clickflag = true;
						}
					}
				}
				else
				{
					clickflag = false;
				}
			}

			//通信確認用
			if (UserNum != -1)
			{
				SendData[ISCONNECT] = 1;
				SendData[SELECTCHARA] = charaselect;
				NetWorkSendUDP(NetUDPHandle, Ip, UserNum, SendData, sizeof(SendData));
			}

			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
				if (RecvData[ISCONNECT] != 0)
				{
					enemychara = RecvData[SELECTCHARA];
					if (charaselect != 0 && enemychara != 0)
					{
						if (RecvData[TURNFAST] == 1)
							turn = true;
						else
							turn = false;
						scene = GAME;
					}
					connecttime = 0;
				}
				else
				{
					connecttime++;
					if (connecttime == 60)
					{
						//対戦相手が消えたため接続に戻る
						//初期化は任せた
						scene = CONNECT;
					}
				}
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
							if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0 && piecetable[i].MeorEne == true)
							{
								//その駒の対応ナンバーを一時保存する
								movepiece = i;
								//行動場所を選ぶようにする
								moveflag = true;
								clickflag = true;
								//移動できる範囲を緑色で指定する
								//マスに触れる所
								CheckMoveRange(piecetable[i], piecetable);
							}
						}
					}
					//緑色のマスを選択し上記で選んだ駒をその場所に移動
					else
					{
						//選んだマスを取得
						movePos = HitPos(clickpos.posX, clickpos.posY);
						////データ送る用保存
						SendData[2] = (6 - piecetable[movepiece].posX);
						SendData[3] = (6 - piecetable[movepiece].posY);
						//そのマスが範囲内
						//クリックした場所と駒の位置があっていれば
						if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7 && CanMoveMap[movePos.y][movePos.x] == 1)
						{
							//データ送る用保存
							SendData[MOVEBEFOREPOSX] = 6 - piecetable[movepiece].posX;
							SendData[MOVEBEFOREPOSY] = 6 - piecetable[movepiece].posY;
							int latemove = -1;//駒の配列番号の保存
							Pos latemovepos = { movePos.x ,movePos.y };
							for (int i = 0; i < 28; i++)
							{
								if (movePos.x == piecetable[i].posX && movePos.y == piecetable[i].posY && i != movepiece && piecetable[i].type != 0)
								{									
									latemove = i;
								}
							}
							//地雷チェック
							//移動方向を保存(x方向に-2,xに-1yに-1等々)
							int movex = latemovepos.posX - piecetable[movepiece].posX;
							int movey = latemovepos.posY - piecetable[movepiece].posY;
							//途中で地雷があったらその場所で止まるようにする
							for (; movex != 0 || movey != 0;)
							{
								//相手の地雷も自分の地雷も踏んだら死なので二回回す
								for (int i = 0; i < 2; i++)
								{
									//そこに地雷があればそこで強制的に止まるようにする
									if (abilityinfo[i][0] == piecetable[movepiece].posX + movex && abilityinfo[i][1] == piecetable[movepiece].posY + movey && abilityinfo[i][2] == 1)
									{
										latemove = -1;
										latemovepos.posX = piecetable[movepiece].posX + movex;
										latemovepos.posY = piecetable[movepiece].posY + movey;
									}
								}

								//for終わらせるための減少増加
								if (movex > 0)
									movex--;
								else if (movex < 0)
									movex++;

								if (movey > 0)
									movey--;
								else if (movey < 0)
									movey++;
							}
							if (latemove != -1)
							{//駒同士が重なったときの処理
								if (piecetable[movepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
								{
									piecetable[movepiece].posX = latemovepos.posX;
									piecetable[movepiece].posY = latemovepos.posY;
									if (piecetable[latemove].type == 6)//相手の王を取ったら勝ちのフラグをtrueに
										win_flag = true;
									if (piecetable[latemove].type == 5)//自分の王を取られたら負けのフラグをtrueに
										lose_flag = true;
									//if (piecetable[latemove].type == 7)//壁には通れなくさせる。
									//	movepiece = -1;
									//王以外の駒全部取られた場合も負けの為ここで判定
									int Ene = 0;
									int Me = 0;
									for (int i = 0; i < 28; i++)
									{
										//自軍敵軍の駒数カウント
										if (piecetable[i].MeorEne == true)
											Me++;
										else
											Ene++;
									}

									piecetable[latemove].type = 0;//何もない場所には空白
									//movepiece = -1;//移動前の駒は非表示に

									//データ送る用保存
									SendData[LATEMOVEPOSX] = (6 - piecetable[movepiece].posX);
									SendData[LATEMOVEPOSY] = (6 - piecetable[movepiece].posY);
								}
								
							}
							//重ならなかったとき
							else
							{
								piecetable[movepiece].posX = latemovepos.posX;
								piecetable[movepiece].posY = latemovepos.posY;

								for (int i = 0; i < 2; i++)
								{
									if (abilityinfo[i][0] == piecetable[movepiece].posX && abilityinfo[i][1] == piecetable[movepiece].posY && abilityinfo[i][2] == 1)
									{
										piecetable[movepiece].type = 0;
										abilityinfo[i][2] = -1;
									}
								}

								//データ送る用保存
								SendData[LATEMOVEPOSX] = (6 - piecetable[movepiece].posX);
								SendData[LATEMOVEPOSY] = (6 - piecetable[movepiece].posY);
							}



							clickflag = true;
							moveflag = false;
							movepiece = -1;//移動前の駒は非表示に

							turn = false;
							//クリックした後の緑範囲を消す
							for (int i = 0; i < 7; i++)
							{
								for (int j = 0; j < 7; j++)
								{
									CanMoveMap[i][j] = 0;
								}
							}

						}
						//駒の場所とあっていなければ
						else
						{
							clickflag = true;
							moveflag = false;

							//緑範囲を消す
							for (int i = 0; i < 7; i++)
							{
								for (int j = 0; j < 7; j++)
								{
									CanMoveMap[i][j] = 0;
								}
							}
						}
					}
				}
				//クリックしなかったとき
				else if (saveclickflag == false)
				{
					clickflag = false;
				}

				GetMousePoint(&mx, &my);


			}//ここまでが自分の手番

			//デバッグ用ターンの引き渡し
			turn = true;

			 //データ受け取り
			 //通信確認用
			if (UserNum != -1)
			{
				SendData[ISCONNECT] = 1;
				SendData[SELECTCHARA] = charaselect;
				NetWorkSendUDP(NetUDPHandle, Ip, UserNum, SendData, sizeof(SendData));
				for (int i = 0; i < 10; i++)
					SendData[i] = 0;
			}

			//データ受信部分
			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
				if (RecvData[ISCONNECT] != 0)
				{//相手のターンの時相手の処理が終わったらそのデータを受け取る。
					if (turn == false && (RecvData[MOVEBEFOREPOSX] + RecvData[MOVEBEFOREPOSY] + RecvData[LATEMOVEPOSX] + RecvData[LATEMOVEPOSY]) != 0)
					{
						int latemove = -1;//駒の配列番号の保存
						Pos latemovepos = { RecvData[LATEMOVEPOSX] ,RecvData[LATEMOVEPOSY] };
						for (int i = 0; i < 28; i++)
						{
							if (RecvData[MOVEBEFOREPOSX] == piecetable[i].posX && RecvData[MOVEBEFOREPOSY] == piecetable[i].posY&& piecetable[i].type != 0)
							{
								Enemovepiece = i;
							}
							if (RecvData[LATEMOVEPOSX] == piecetable[i].posX && RecvData[LATEMOVEPOSY] == piecetable[i].posY && piecetable[i].type != 0)
							{
								latemove = i;
							}
						}
						//地雷チェック
						//移動方向を保存(x方向に-2,xに-1yに-1等々)
						int movex = latemovepos.posX - piecetable[Enemovepiece].posX;
						int movey = latemovepos.posY - piecetable[Enemovepiece].posY;
						//途中で地雷があったらその場所で止まるようにする
						for (; movex != 0 || movey != 0;)
						{
							//相手の地雷も自分の地雷も踏んだら死なので二回回す
							for (int i = 0; i < 2; i++)
							{
								//そこに地雷があればそこで強制的に止まるようにする
								if (abilityinfo[i][0] == piecetable[Enemovepiece].posX + movex && abilityinfo[i][1] == piecetable[Enemovepiece].posY + movey && abilityinfo[i][2] == 1)
								{
									latemove = -1;
									latemovepos.posX = piecetable[Enemovepiece].posX + movex;
									latemovepos.posY = piecetable[Enemovepiece].posY + movey;
								}
							}

							//for終わらせるための減少増加
							if (movex > 0)
								movex--;
							else if (movex < 0)
								movex++;

							if (movey > 0)
								movey--;
							else if (movey < 0)
								movey++;
						}

						if (latemove != -1 && (piecetable[Enemovepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0))
						{
							//駒同士が重なったときの処理
							piecetable[Enemovepiece].posX = latemovepos.posX;
							piecetable[Enemovepiece].posY = latemovepos.posY;
							if (piecetable[latemove].type == 6)//相手の王を取ったら勝ちのフラグをtrueに
								win_flag = true;
							if (piecetable[latemove].type == 5)//自分の王を取られたら負けのフラグをtrueに
								lose_flag = true;
							//if (piecetable[latemove].type == 7)//壁には通れなくさせる。
							//	movepiece = -1;
							//王以外の駒全部取られた場合も負けの為ここで判定
							int Ene = 0; 
							int Me = 0;
							for (int i = 0; i < 28; i++)
							{
								//自軍敵軍の駒数カウント
								if (piecetable[i].MeorEne == true)
									Me++;
								else
									Ene++;
							}
							//抜けた時にMeもしくはEneが1なら王しかいないということなので
							if (Me == 1)
								lose_flag = true;
							if (Ene == 1)
								win_flag = true;

							piecetable[latemove].type = 0;//何もない場所には空白
														  //移動先が壁なら進めない
														  //else if(piecetable[])
						}
						//重ならなかったとき
						else
						{
							piecetable[Enemovepiece].posX = latemovepos.posX;
							piecetable[Enemovepiece].posY = latemovepos.posY;
							for (int i = 0; i < 2; i++)
							{
								if (abilityinfo[i][0] == piecetable[Enemovepiece].posX && abilityinfo[i][1] == piecetable[Enemovepiece].posY && abilityinfo[i][2] == 1)
									piecetable[latemove].type = 0;
							}
						}

						turn = true;

					}
					connecttime = 0;
				}
				else
				{
					connecttime++;
					if (connecttime == 60)
					{
						//対戦相手が消えたため接続に戻る
						//初期化は任せた
						//scene = CONNECT;
					}
				}
			}

			//相手の手番の場合
			//相手のターン以外は操作を不可能にする
			//if (turn == false)
			//{
			//	//クリックしたとき
			//	if (clickflag == false && saveclickflag == true)
			//	{
			//		//キャラを選択し緑色のマス(行動できる範囲)を描画
			//		if (moveflag == false)
			//		{
			//			//クリックしたマスを取得しそのマスに該当する駒を探す
			//			POS SavePos = HitPos(clickpos.posX, clickpos.posY);
			//			for (int i = 0; i < 28; i++)
			//			{
			//				//該当する駒があり、その駒が生きていれば
			//				if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0)
			//				{
			//					//その駒の対応ナンバーを一時保存する
			//					movepiece = i;
			//					//行動場所を選ぶようにする
			//					moveflag = true;
			//					clickflag = true;
			//					//移動できる範囲を緑色で指定する
			//					//マスに触れる所
			//					CheckMoveRange(piecetable[i], piecetable);
			//				}
			//			}
			//		}
			//		//緑色のマスを選択し上記で選んだ駒をその場所に移動
			//		else
			//		{
			//			//選んだマスを取得
			//			movePos = HitPos(clickpos.posX, clickpos.posY);
			//			//そのマスが範囲内
			//			//クリックした場所と駒の位置があっていれば
			//			if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7 && CanMoveMap[movePos.y][movePos.x] == 1)
			//			{
			//				int latemove = -1;//駒の配列番号の保存
			//				for (int i = 0; i < 28; i++)
			//				{
			//					if (movePos.x == piecetable[i].posX && movePos.y == piecetable[i].posY && i != movepiece)
			//					{
			//						latemove = i;
			//					}
			//				}
			//				if (latemove != -1)
			//				{//駒同士が重なったときの処理
			//					if (piecetable[movepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
			//					{
			//						piecetable[movepiece].posX = movePos.x;
			//						piecetable[movepiece].posY = movePos.y;
			//						if (piecetable[latemove].type == 6)//相手の王を取ったら勝ちのフラグをtrueに
			//							win_flag = true;
			//						if (piecetable[latemove].type == 5)//自分の王を取られたら負けのフラグをtrueに
			//							lose_flag = true;
			//						//if (piecetable[latemove].type == 7)//壁には通れなくさせる。
			//						//	movepiece = -1;

			//						piecetable[latemove].type = 0;//何もない場所には空白
			//						movepiece = -1;//移動前の駒は非表示に
			//						turn = true;
			//					}
			//					//移動先が壁なら進めない
			//					//else if(piecetable[])
			//				}
			//				//重ならなかったとき
			//				else
			//				{
			//					piecetable[movepiece].posX = movePos.x;
			//					piecetable[movepiece].posY = movePos.y;
			//					movepiece = -1;
			//					turn = true;
			//				}
			//				clickflag = true;
			//				moveflag = false;

			//				turn = true;
			//				//クリックした後の緑範囲を消す
			//				for (int i = 0; i < 7; i++)
			//				{
			//					for (int j = 0; j < 7; j++)
			//					{
			//						CanMoveMap[i][j] = 0;

			//						DwallMap[i][j]=0;
			//						
			//					}
			//				}
			//				
			//			}
			//		}
			//	}
			//	else if (saveclickflag == false)
			//	{
			//		clickflag = false;
			//	}
				//ここまでが相手の手番
			
				//---------------壁の生成処理----------------------------------
				//キャラの必殺ボタンをクリックしたとき


				//int Mouse;//クリックしたときの制御をするための変数
				//必殺技の箇所にマウスがあるとき
				//ボタンの領域内でかつ
				//if (mx <CLDOWN_X&&mx>CLUP_X&&my<CLDOWN_Y&&my>CLUP_Y)
				//{
				//	GetMousePoint(&mx, &my);
				//	//マウスの左クリックをすると
				//	if (GetMouseInput()&MOUSE_INPUT_LEFT)
				//	{
				//		//押して増えたrigitの分を0にリセットする
				//		if (Mouse > 0)
				//		{
				//			Mouse = -1;
				//		}
				//		else//押してなければ増えない
				//		{
				//			Mouse = 0;

				//		}
				//	}
				//	else
				//	{
				//		//押されている
				//		Mouse++;
				//	}

				//	if (Mouse == 1) 
				//	{
				//		if (skillclickflag == false && skillflagremove == false)
				//		{
				//			//スキル待機中のボタンとキャラを描画するflagをtrueに
				//			skillclickflag = true;
				//			skillflagremove = false;

				//			PlaySoundMem(se, DX_PLAYTYPE_BACK);
				//		}
				//	}

				//	//もう一度
				//	//右クリックをすると能力発動ボタンに戻る
				//	if (Mouse == 1)
				//	{
				//		if (skillbuttonflag==true)
				//		{
				//			skillclickflag = false;
				//			skillflagremove = true;
				//			//PlaySoundMem(se, DX_PLAYTYPE_BACK);
				//		}
				//	}
				//	//赤い範囲をクリックすると
				//	if (Mouse==1&&wallskill1 == true)
				//	{
				//		//クリックしたとき
				//		//キャラを選択し緑色のマス(行動できる範囲)を描画
				//		if (appearanceflag == false)
				//		{
				//			//クリックしたマスを取得しそのマスに該当する駒を探す
				//			POS WallPos = ZeroPos(clickpos.posX, clickpos.posY);
				//			for (int i = 0; i < 49; i++)
				//			{
				//				//該当する駒があり、その駒が生きていれば
				//				if (WallPos.x == wall[i].posx && WallPos.y == wall[i].posy && wall[i].type == 0)
				//				{
				//					//その駒の対応ナンバーを一時保存する
				//					appearanceWall = i;
				//					//行動場所を選ぶようにする
				//					appearanceflag = true;
				//					clickflag = true;
				//					//出現できる範囲を赤色で指定する
				//					//CheckMoveRange(wall[i], wall);
				//				}
				//			}
				//		}

			//				turn = true;
			//				//クリックした後の緑範囲を消す
			//				for (int i = 0; i < 7; i++)
			//				{
			//					for (int j = 0; j < 7; j++)
			//					{
			//						CanMoveMap[i][j] = 0;

			//						DwallMap[i][j]=0;
			//						
			//					}
			//				}
			//				
			//			}
			//		}
			//	}
			//	else if (saveclickflag == false)
			//	{
			//		clickflag = false;
			//	}
			//	//ここまでが相手の手番
			//
			//	//---------------壁の生成処理----------------------------------
			//	//キャラの必殺ボタンをクリックしたとき


			//	int Mouse;//クリックしたときの制御をするための変数
			//	//必殺技の箇所にマウスがあるとき
			//	//ボタンの領域内でかつ
			//	//if (mx <CLDOWN_X&&mx>CLUP_X&&my<CLDOWN_Y&&my>CLUP_Y)
			//	//{
			//	//	GetMousePoint(&mx, &my);
			//	//	//マウスの左クリックをすると
			//	//	if (GetMouseInput()&MOUSE_INPUT_LEFT)
			//	//	{
			//	//		//押して増えたrigitの分を0にリセットする
			//	//		if (Mouse > 0)
			//	//		{
			//	//			Mouse = -1;
			//	//		}
			//	//		else//押してなければ増えない
			//	//		{
			//	//			Mouse = 0;

			//	//		}
			//	//	}
			//	//	else
			//	//	{
			//	//		//押されている
			//	//		Mouse++;
			//	//	}

			//	//	if (Mouse == 1) 
			//	//	{
			//	//		if (skillclickflag == false && skillflagremove == false)
			//	//		{
			//	//			//スキル待機中のボタンとキャラを描画するflagをtrueに
			//	//			skillclickflag = true;
			//	//			skillflagremove = false;

			//	//			PlaySoundMem(se, DX_PLAYTYPE_BACK);
			//	//		}
			//	//	}

			//	//	//もう一度
			//	//	//右クリックをすると能力発動ボタンに戻る
			//	//	if (Mouse == 1)
			//	//	{
			//	//		if (skillbuttonflag==true)
			//	//		{
			//	//			skillclickflag = false;
			//	//			skillflagremove = true;
			//	//			//PlaySoundMem(se, DX_PLAYTYPE_BACK);
			//	//		}
			//	//	}
			//	//	//赤い範囲をクリックすると
			//	//	if (Mouse==1&&wallskill1 == true)
			//	//	{
			//	//		//クリックしたとき
			//	//		//キャラを選択し緑色のマス(行動できる範囲)を描画
			//	//		if (appearanceflag == false)
			//	//		{
			//	//			//クリックしたマスを取得しそのマスに該当する駒を探す
			//	//			POS WallPos = ZeroPos(clickpos.posX, clickpos.posY);
			//	//			for (int i = 0; i < 49; i++)
			//	//			{
			//	//				//該当する駒があり、その駒が生きていれば
			//	//				if (WallPos.x == wall[i].posx && WallPos.y == wall[i].posy && wall[i].type == 0)
			//	//				{
			//	//					//その駒の対応ナンバーを一時保存する
			//	//					appearanceWall = i;
			//	//					//行動場所を選ぶようにする
			//	//					appearanceflag = true;
			//	//					clickflag = true;
			//	//					//出現できる範囲を赤色で指定する
			//	//					//CheckMoveRange(wall[i], wall);
			//	//				}
			//	//			}
			//	//		}


			//	//	}



			//	//	//ここでMainMapを更新
			//	//	for (int i = 0; i < 7; i++)
			//	//	{
			//	//		for (int j = 0; j < 7; j++)
			//	//		{
			//	//			DwallMap[i][j] = 0;
			//	//		}
			//	//	}
			//	//	

			//	//}
			//	//

			//	//-----------ここから赤い範囲の処理-------------
			//	//赤いマス
			//	if (skillredflag == true)
			//	{
			//		//MainMapの0の部分を探す


			//	}
			/*}
			else
			{
				
			}*/
	
		//Zキーを押すと手番を自分に戻す。
		if (CheckHitKey(KEY_INPUT_Z))
		{
			turn = false;
		}

	
		cr = GetColor(0, 255, 0);//緑色を取得
		
			//背景の画像表示	
			LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
			DrawGraph(0, 0, t_charaB, TRUE);//プレイヤー1の背景の描画
			DrawGraph(640, 0, t_charaB2, TRUE);//プレイヤー2の背景の描画

			if (charaselect == 1)
			{
				DrawGraph(0, 0, t_chara, TRUE);//プレイヤー1の描画
			}
			else if (charaselect == 2)
			{
				DrawGraph(0, 0, t_chara2, TRUE);//プレイヤー1の描画
			}
			else if (charaselect == 3)
			{
				DrawGraph(0, 0, t_chara3, TRUE);//プレイヤー1の描画
			}
			if (enemychara == 1)
			{
				DrawGraph(640, 0, t_chara, TRUE);//プレイヤー2の描画
			}
			else if (enemychara == 2)
			{
				DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
			}
			else if (enemychara == 3)
			{
				DrawGraph(640, 0, t_chara3, TRUE);//プレイヤー2の描画
			}

			//ターンプレイヤーをわかりやすくするための画像表示
			if (turn == true)
			{
				DrawExtendGraphF(20, 260, 170, 330, Turn, TRUE);
			}
			else
			{
				DrawExtendGraphF(662, 260, 812, 330, Turn, TRUE);
			}
			
			DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//能力発動ボタンの描画
			//駒の描画ひとしきり
			//上2行と下2行
			for (int i = 0; i < 28; i++)
			{
				if (piecetable[i].type != 0)
				{
					if (piecetable[i].MeorEne == true)
					{
						DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, BB, TRUE);
					}
					else
					{
						DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, RB, TRUE);
					}
				}
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

				case 7:
					//敵兵士の生成
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Soldier, TRUE);
					break;
				}

			}
			//緑の範囲描画
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

	//-------------能力ボタン描画---------
			//能力ボタンの場所を待機中にする
			if (skillclickflag == true&&skillflagremove==false)
			{
				//それぞれのキャラの描画と能力内容処理
				//キャラ1の場合
				if (charaselect == 1)
				{
					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//能力待機中の描画
					t_chara = LoadGraph("image\\キャラクター1\\キャラクター1スキル透過.PNG");//スキル待機中のキャラ1
					skillbuttonflag = true;
					//駒が通れない壁を作る(横向き)
					//赤い範囲を描画する
					//MainMapの中にある0の場所を探す
					for (int i = 0; i < 7; i++)
					{
						for (int j = 0; j < 7; j++)
						{
							if (CanMoveMap[i][j] == 0)
							{
								DrawGraphF(j * 64 + 192, i * 64, RedFilter, TRUE);
							}
						}
					}
				}
				//キャラ2の場合
				else if (charaselect == 2)
				{
					//敵に見えない地雷を設定する

					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//能力待機中の描画
					t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2スキル.PNG");//スキル待機中のキャラ2
					skillbuttonflag = true;
					for (int x = 0; x < 7; x++)
					{
						for (int y = 0; y < 7; y++)
						{
							if (MainMap[x][y] == 0)
							{

								//赤い範囲を描画する
								DrawGraphF(y * 64 + 192, x * 64, RedFilter, TRUE);

							}
						}
					}



				}
				//キャラ3の場合
				else if (charaselect == 3)
				{

					//駒が通れない壁を作る(縦向き)

					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//能力待機中の描画
					t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3スキル.PNG");//スキル待機中のキャラ3
					skillbuttonflag = true;

					//MainMapの中にある0の場所を探す
					for (int x = 0; x < 7; x++)
					{
						for (int y = 0; y < 7; y++)
						{
							if (MainMap[x][y] == 0)
							{

								//赤い範囲を描画する
								DrawGraphF(y * 64 + 192, x * 64, RedFilter, TRUE);

							}
						}
					}


				}
			}
			//待機中に再度ボタンをクリックすると能力発動可能状態に戻る
			else
			{
				if (skillbuttonflag == true)
				{
					if (charaselect == 1)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//能力発動ボタンの描画
						t_chara = LoadGraph("image\\キャラクター1\\キャラクター1リサイズ透過.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;
					}
					else if (charaselect == 2)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//能力発動ボタンの描画
						t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2メイン.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;
					}
					else if (charaselect == 3)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//能力発動ボタンの描画
						t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3立ち絵.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;

					}
				}
			}

			if (win_flag == true)
			{
				scene = GAMEEND;
			}
			else if (lose_flag == true)
			{
				scene = GAMEEND;
			}
			break;


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

			
			case GAMEEND:
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

				//勝利時勝利画面表示
				if (win_flag == true)
				{
					if (time == false)
					{
						WaitTimer(500);
					}
					time = true;

					SetFontSize(40);

					DrawGraph(0, 0, t_charaB, TRUE);//プレイヤー1の背景の描画
					DrawGraph(640, 0, t_charaB2, TRUE);//プレイヤー2の背景の描画
					//DrawExtendGraphF(194, 398, 416, 448, textbox, TRUE);//テキストボックスの描画
					//DrawExtendGraphF(417, 398, 639, 448, textbox, TRUE);//テキストボックスの描画
					DrawExtendGraphF(194, 398, 639, 448, textbox, TRUE);//テキストボックスの描画

					DrawString(340, 50, "YOU WIN", GetColor(255, 0, 0));
					/*DrawString(200, 403, "タイトルへ", GetColor(255, 0, 0));*/
					/*DrawString(490, 403, "終了", GetColor(255, 0, 0));*/
					DrawString(365, 403, "終了", GetColor(255, 0, 0));

					if (charaselect == 1)
					{
						t_chara = LoadGraph("image\\キャラクター1\\キャラクター1勝利透過.png");
						DrawGraph(0, 0, t_chara, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					else if (charaselect == 2)
					{
						t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2勝利.png");
						DrawGraph(0, 0, t_chara2, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					else if (charaselect == 3)
					{
						t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3勝利.png");
						DrawGraph(0, 0, t_chara3, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					if (enemychara == 1)
					{
						t_chara = LoadGraph("image\\キャラクター1\\キャラクター1敗北透過.png");
						DrawGraph(640, 0, t_chara, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}
					else if (enemychara == 2)
					{
						t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2敗北.png");
						DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}
					else if (enemychara == 3)
					{
						t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3敗北.png");
						DrawGraph(640, 0, t_chara3, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}
					
					if (saveclickflag == true)
					{
						if (clickflag == false)
						{
							/*if (194 <= clickpos.posX && clickpos.posX <= 416 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								scene = TITLE;
								clickflag = true;
							}
							else if (417 <= clickpos.posX && clickpos.posX <= 639 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								gameend_flag = true;
								clickflag = true;
							}*/
							if (194 <= clickpos.posX && clickpos.posX <= 639 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								gameend_flag = true;
								clickflag = true;
							}
						}
						else
						{
							clickflag = false;
						}
					}
					break;
				}
				//敗北時敗北画面表示
				else if (lose_flag == true)
				{
					if (time == false)
					{
						WaitTimer(500);
					}
					time = true;

					SetFontSize(40);

					DrawGraph(0, 0, t_charaB, TRUE);//プレイヤー1の背景の描画
					DrawGraph(640, 0, t_charaB2, TRUE);//プレイヤー2の背景の描画
					//DrawExtendGraphF(194, 398, 416, 448, textbox, TRUE);//テキストボックスの描画
					//DrawExtendGraphF(417, 398, 639, 448, textbox, TRUE);//テキストボックスの描画
					DrawExtendGraphF(194, 398, 639, 448, textbox, TRUE);//テキストボックスの描画

					DrawString(340, 50, "YOU LOSE", GetColor(255, 0, 0));
					/*DrawString(200, 403, "タイトルへ", GetColor(255, 0, 0));*/
					/*DrawString(490, 403, "終了", GetColor(255, 0, 0));*/
					DrawString(365, 403, "終了", GetColor(255, 0, 0));

					if (charaselect == 1)
					{
						t_chara = LoadGraph("image\\キャラクター1\\キャラクター1敗北透過.png");
						DrawGraph(0, 0, t_chara, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					else if (charaselect == 2)
					{
						t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2敗北.png");
						DrawGraph(0, 0, t_chara2, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					else if (charaselect == 3)
					{
						t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3敗北.png");
						DrawGraph(0, 0, t_chara3, TRUE);//プレイヤー1の描画
						skillredflag = true;
					}
					if (enemychara == 1)
					{
						t_chara = LoadGraph("image\\キャラクター1\\キャラクター1勝利透過.png");
						DrawGraph(640, 0, t_chara, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}
					else if (enemychara == 2)
					{
						t_chara2 = LoadGraph("image\\キャラクター2\\キャラクター2勝利.png");
						DrawGraph(640, 0, t_chara2, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}
					else if (enemychara == 3)
					{
						t_chara3 = LoadGraph("image\\キャラクター3\\キャラクター3勝利.png");
						DrawGraph(640, 0, t_chara3, TRUE);//プレイヤー2の描画
						skillredflag = true;
					}

					if (saveclickflag == true)
					{
						if (clickflag == false)
						{
							/*if (194 <= clickpos.posX && clickpos.posX <= 416 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
							scene = TITLE;
							clickflag = true;
							}
							else if (417 <= clickpos.posX && clickpos.posX <= 639 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
							gameend_flag = true;
							clickflag = true;
							}*/
							if (194 <= clickpos.posX && clickpos.posX <= 639 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								gameend_flag = true;
								clickflag = true;
							}
						}
						else
						{
							clickflag = false;
						}
					}
					break;
				}
			break;
		}


		ScreenFlip();//画像のフリップ(切り替え)
		ClearDrawScreen();//画像のクリア
		//ゲームを終わる
		if (gameend_flag == true)
		{
			break;
		}
	}
	//ソケットハンドルの削除
	DeleteUDPSocket(NetUDPHandle);

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

//能力ボタンを押したとき0の場所を調べる
POS ZeroPos(int ZposX, int ZposY)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (HitClick(ZposX, ZposY, POPUP_X + POPDOWN_X * i, POPUP_Y + POPDOWN_Y * j) == 0)
			{
				//ここで壁の出現位置を返す
				POS pos;
				pos.x = i;
				pos.y = j;

				return pos;
			}
		}
	}
	POS nullpos = { -1,-1 };

	return nullpos;
}


//

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