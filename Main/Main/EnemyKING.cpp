//���̃X�e�[�^�X
#include"DxLib.h"
#include"Piece.h"

#define PI 3.14f

//�R���X�g���N�^
EnemyKING::EnemyKING(int EKx, int EKy)
{
	Enemyking_image = LoadGraph("image\\King(64).png");
	x = EKx;
	y = EKy;


}

//���̃A�N�V����
int EnemyKING::Action(VEC vec)
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
void EnemyKING::Draw()
{
	DrawRotaGraph(x + 192, y,1.5f,PI/2, Enemyking_image, TRUE);
}

//���̏��擾
int EnemyKING::GetX() { return x; }
int EnemyKING::GetY() { return y; }