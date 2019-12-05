#pragma once
#include"DxLib.h"

//座標設定用
typedef struct PositionInfo
{
	//ポジション使う際に
	int posX;
	int posY;
}Pos;

//駒設定用
typedef struct PieceInfo
{
	int type;
	int posX;
	int posY;
	bool MeorEne;
	int movelimit;
	int movefront;
	int moveback;
	int moveleft;
	int moveright;
	int dialu;
	int diald;
	int diaru;
	int diard;
	int spicialmoverange[8][2];
}Piece;

//シーン一覧
enum Scenes
{
	TITLE,CONNECT,SELECT,GAME,GAMEEND,
};
//送るデータ一覧
enum SendDataTag
{
	ISCONNECT, SELECTCHARA, TURNFAST, MOVEBEFOREPOSX, MOVEBEFOREPOSY, LATEMOVEPOSX, LATEMOVEPOSY,
};
//駒の動けるMap
int CanMoveMap[7][7] =
{
	0
};

//壁を発生させれる場所
int DwallMap[7][7] =
{
	0
};

//相手に送信するデータ
struct DATA
{
	//駒の位置データ
	POS p;
	//自分の手番なのか相手の手番なのかのフラグ
	int trun;
	//自分の王が生きているかのフラグ
	int Myking;
};

//ベースクラス
class Base
{
private:

public:
	int ID;//デバッグ用
	int flg;
	virtual void Action() = 0;
	virtual void Draw() = 0;//
	virtual POS GetPos() = 0;//駒の位置
	virtual int GetID() = 0;//相手のIPアドレス





};

//壁設定
typedef struct Wall
{
	int type;
	int posx;
	int posy;
	bool MeorEne;
	int movelimit;
	int movefront;
	int moveback;
	int moveleft;
	int moveright;
	int dialu;
	int diald;
	int diaru;
	int diard;


}Walls;