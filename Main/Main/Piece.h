#pragma once

class SOLDIER //���m�̃N���X
{
public:
	void soldier_move();//���m�̈ړ�
	void soldier_Animation();
	void soldier_Select(int x,int y);


private:
	int soldier_imag;//���m�̉摜�f�[�^
	int SelectFlag;//�I�������Ƃ��̈ړ��͈͂�\��������t���O

	
};


class ESPIONAGE //������̃N���X
{
public:
	void espionage_move();
	void espionage_Animation();

private:
	int imag;

	int espionagr_image();


};

class SORCERER //�����m�̃N���X
{
public:
	void sorcerer_move();
	void sorcerer_Animation();


private:
	int sorcerer_image();
};


class KNIGHT //�R�m�̃N���X
{
public:
	void knight_move();
	void knight_Animation();


private:
	int knight_image();//�R�m�̉摜�o�^�p�ϐ�
};

class KING  //���̃N���X
{
public:
	void king_move();
	void king_Animation();

private:
	int king_image();//���̉摜�o�^�p�ϐ�

};