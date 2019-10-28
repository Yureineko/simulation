//������̃X�e�[�^�X
#include"DxLib.h"
#include"Piece.h"
#include<stdio.h>


//�R���X�g���N�^
ESPIONAGE::ESPIONAGE(int EX, int EY)
{
	espionagr_image = LoadGraph("image\\Espionage(64).png");
	pos.x = EX;
	pos.y = EY;
}

//������̃A�N�V����
int ESPIONAGE::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//�E�Ɉړ�
		break;
	}
	return vec;
}

void ESPIONAGE::Draw()
{
	DrawGraphF(pos.x + 192, pos.y, espionagr_image, TRUE);
}
int ESPIONAGE::GetX() { return pos.x; }
int ESPIONAGE::GetY() { return pos.y; }