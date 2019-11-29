//���̃X�e�[�^�X
#include"DxLib.h"
#include"Piece.h"

//�R���X�g���N�^
KING::KING(int Kx, int Ky)
{
	king_image = LoadGraph("image\\King(64).png");
	x = Kx;
	y = Ky;


}

//���̃A�N�V����
int KING::Action(VEC vec)
{
	//���̈ړ�
	switch (vec)
	{
	case 0:
		x += 5;//�E�Ɉړ�
		break;
	case 1:
		y -= 5;//��Ɉړ�
		break;
	case 2:
		x -= 5;//���Ɉړ�
		break;
	case 3:
		y += 5;//���Ɉړ�
		break;
	case 4:
		x += 5;
		y -= 5;//�E��Ɉړ�
		break;

	
	
	}
	return vec;
}


//�A�j���[�V����
//void KING::king_Animation()
//{
//
//}

//

//���̕`��
void KING::Draw()
{
	DrawGraphF(x+192, y, king_image, TRUE);
}

//���̏��擾
int KING::GetX() { return x; }
int KING::GetY() { return y; }
//int KING::