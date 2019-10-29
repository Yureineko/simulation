//王のステータス
#include"DxLib.h"
#include"Piece.h"

#define PI 3.14f

//コンストラクタ
EnemyKING::EnemyKING(int EKx, int EKy)
{
	Enemyking_image = LoadGraph("image\\King(64).png");
	x = EKx;
	y = EKy;


}

//王のアクション
int EnemyKING::Action(VEC vec)
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
void EnemyKING::Draw()
{
	DrawRotaGraph(x + 192, y,1.5f,PI/2, Enemyking_image, TRUE);
}

//王の情報取得
int EnemyKING::GetX() { return x; }
int EnemyKING::GetY() { return y; }