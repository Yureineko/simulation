#pragma once

//�ړ�����
enum VEC
{
	RIGHT,
	UP,
	LEFT,
	DOWN,
	N,
};


//��̈ʒu���
struct POS
{
	int x,y;
};

//�ړ���
struct Move_POS
{
	int x,y;

};


class SOLDIER //���m�̃N���X
{
public:
	 SOLDIER(int SolX, int SolY);//���m�̈ړ�

	 int Action(VEC vec);
	 int GetX();
	 int GetY();
	 void Draw();

	void soldier_Animation();//���m�̃A�j���[�V����
	void soldier_Select();//�ړ��͈͂̑I��


private:

	POS pos;//���m�̌��݈ʒu
	int soldier_imag;//���m�̉摜�f�[�^�̓o�^
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O

	
};


class ESPIONAGE //������̃N���X
{
public:
	ESPIONAGE(int EX, int EY);

	int Action(VEC vec);
	void Draw();//�`��
	int GetX();
	int GetY();


	//void espionage_move(int x,int y);//
	//void espionage_Animation();//

private:
	POS pos;//������̈ʒu
	int espionagr_image;//�Ō�ɂ��̃N���X�ŊG��`�悷��B
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O

};

class SORCERER //�����m�̃N���X
{
public:
	SORCERER(int SorX, int SorY);
	
	int Action(VEC vec);
	void Draw();//�`��
	int GetX();
	int GetY();

	//void sorcerer_move(int x,int y);//�����m�̈ړ�
	//void sorcerer_Animation();//�����m�̃A�j���[�V����


private:
	POS pos;//�����m�̈ʒu
	int sorcerer_image;//�Ō�ɂ��̃N���X�ŊG��`�悷��B
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O
};


class KNIGHT //�R�m�̃N���X
{
public:
	KNIGHT(int KnX, int KnY);
	int Action(VEC vec);//�R�m�̈ړ�
	void Draw();//�`��
	int GetX();
	int GetY();

	//void knight_move(int x,int y);//�R�m�̈ړ�
	//void knight_Animation();//�R�m�̃A�j���[�V����


private:
	POS pos;//�R�m�̈ʒu
	int knight_image;//�R�m�̉摜�o�^�p�ϐ� �Ō�ɂ��̃N���X�ŊG��`�悷��B
	int x, y;//�R�m�̈ʒu
};

class KING  //���̃N���X
{
public:
	 KING(int Kx,int Ky);//���̈ړ�
	 int Action(VEC vec);//�ړ��̏���
	 void Draw();//�`��
	 int GetX();
	 int GetY();

	//void king_Animation();//���̃A�j���[�V����

private:
	POS pos;//���̈ʒu
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O
	int king_image;//���̉摜�o�^�p�ϐ� �Ō�ɂ��̃N���X�ŊG��`�悷��B
	int x, y;//���̈ʒu

};