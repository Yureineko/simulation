#pragma once

//�ړ�����
enum VEC
{
	RIGHT,
	UP,
	LEFT,
	DOWN,

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
	void soldier_move(int x, int y);//���m�̈ړ�
	void soldier_Animation();
	void soldier_Select();


private:
	int soldier_imag;//���m�̉摜�f�[�^�@�Ō�ɂ��̃N���X�ŊG��`�悷��B
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O

	
};


class ESPIONAGE //������̃N���X
{
public:
	void espionage_move(int x,int y);//
	void espionage_Animation();//

private:
	int imag;

	int espionagr_image();//�Ō�ɂ��̃N���X�ŊG��`�悷��B


};

class SORCERER //�����m�̃N���X
{
public:
	void sorcerer_move(int x,int y);//�����m�̈ړ�
	void sorcerer_Animation();//�����m�̃A�j���[�V����


private:
	int sorcerer_image();//�Ō�ɂ��̃N���X�ŊG��`�悷��B
};


class KNIGHT //�R�m�̃N���X
{
public:
	void knight_move(int x,int y);//�R�m�̈ړ�
	void knight_Animation();//�R�m�̃A�j���[�V����


private:
	int knight_image();//�R�m�̉摜�o�^�p�ϐ� �Ō�ɂ��̃N���X�ŊG��`�悷��B
};

class KING  //���̃N���X
{
public:
	 KING(int x,int y);//���̈ړ�
	void king_Animation();//���̃A�j���[�V����

private:
	int king_image;//���̉摜�o�^�p�ϐ� �Ō�ɂ��̃N���X�ŊG��`�悷��B
	int x, y;//���̈ʒu

};