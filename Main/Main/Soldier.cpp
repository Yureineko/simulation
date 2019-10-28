#include"DxLib.h"
#include"Piece.h"



//コンストラクタ
SOLDIER::SOLDIER(int SolX, int SolY)
{

	soldier_imag = LoadGraph("image\\Soldier(64).png");
	pos.x = SolX;
	pos.y = SolY;


}

int SOLDIER::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//右に移動
		break;
	}
	return vec;
}


//兵士の描画
void SOLDIER ::Draw()
{
	DrawGraphF(pos.x + 192, pos.y, soldier_imag,TRUE);
}

int SOLDIER::GetX() { return pos.x; }
int SOLDIER::GetY() { return pos.y; }