//王のステータス
#include"DxLib.h"
#include"Piece.h"

//コンストラクタ
KING::KING(int Kx, int Ky)
{
	king_image = LoadGraph("image\\King(64).png");
	x = Kx;
	y = Ky;


}

//王のアクション
int KING::Action(VEC vec)
{
	//王の移動
	switch (vec)
	{
	case 0:
		x += 5;//右に移動
		break;
	case 1:
		y -= 5;//上に移動
		break;
	case 2:
		x -= 5;//左に移動
		break;
	case 3:
		y += 5;//下に移動
		break;
	case 4:
		x += 5;
		y -= 5;//右上に移動
		break;

	
	
	}
	return vec;
}


//アニメーション
//void KING::king_Animation()
//{
//
//}

//

//王の描画
void KING::Draw()
{
	DrawGraphF(x+192, y, king_image, TRUE);
}

//王の情報取得
int KING::GetX() { return x; }
int KING::GetY() { return y; }
//int KING::