#pragma once
#include"DxLib.h"
#include<string.h>//��������g���̂�string��include
#include<string>

class PLAYER1
{
public:


	

private:

	bool Deadly;

	void PL1_skill();//PLAYER1�̃X�L���̏���
	void Draw();//PLAYER1�̕`��
};

class PLAYER2
{
public:


	void PL2_skill();//PLAYER2�̃X�L������
	

private:

	//void Anim();//PLAYER2�̃A�j������
	int x,y;//PLAYER2�̕`��ʒu

	
};

class PLAYER3
{
public:

	void Skill();

private:

	
	void Draw();//�O�l�ڂ̃v���C���[�̕`��ʒu

};