//騎士のステータス
#include"DxLib.h"
#include"Piece.h"


//コンストラクタ
KNIGHT::KNIGHT(int KnX, int KnY)
{
	knight_image = LoadGraph("image\\Knight(64).png");
	pos.x = KnX;
	pos.y = KnY;

}



//騎士のアクション
int KNIGHT::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//右に移動
		break;
	}
	return vec;
}

//騎士の描画
void KNIGHT::Draw()
{
	DrawGraphF(pos.x + 192, pos.y, knight_image, TRUE);
}

int KNIGHT::GetX() { return pos.x; }
int KNIGHT::GetY() { return pos.y; }


