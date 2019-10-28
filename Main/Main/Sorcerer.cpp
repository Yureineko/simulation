//�����m�̃X�e�[�^�X
#include"DxLib.h"
#include"Piece.h"

//�R���X�g���N�^
SORCERER::SORCERER(int SorX, int SorY)
{
	sorcerer_image = LoadGraph("image\\Sorcerer(64).png");
	pos.x = SorX;
	pos.y = SorY;
}

//�����m�̃A�N�V����
int SORCERER::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//�E�Ɉړ�
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
