//魔導士のステータス
#include"DxLib.h"
#include"Piece.h"

//コンストラクタ
SORCERER::SORCERER(int SorX, int SorY)
{
	sorcerer_image = LoadGraph("image\\Sorcerer(64).png");
	pos.x = SorX;
	pos.y = SorY;
}

//魔導士のアクション
int SORCERER::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//右に移動
		break;
	}
	return vec;
}

void SORCERER::Draw()
{
	DrawGraphF(pos.x + 192, pos.y, sorcerer_image, TRUE);
}

int SORCERER::GetX() { return pos.x; }
int SORCERER::GetY() { return pos.y; }
