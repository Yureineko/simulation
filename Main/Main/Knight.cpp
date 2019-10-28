//�R�m�̃X�e�[�^�X
#include"DxLib.h"
#include"Piece.h"


//�R���X�g���N�^
KNIGHT::KNIGHT(int KnX, int KnY)
{
	knight_image = LoadGraph("image\\Knight(64).png");
	pos.x = KnX;
	pos.y = KnY;

}



//�R�m�̃A�N�V����
int KNIGHT::Action(VEC vec)
{
	switch (vec)
	{
	case 0:
		pos.y -= 1;//�E�Ɉړ�
		break;
	}
	return vec;
}

//�R�m�̕`��
void KNIGHT::Draw()
{
	DrawGraphF(pos.x + 192, pos.y, knight_image, TRUE);
}

int KNIGHT::GetX() { return pos.x; }
int KNIGHT::GetY() { return pos.y; }


