#pragma once
#include"DxLib.h"
#include<string.h>//文字列を使うのでstringをinclude
#include<string>

class PLAYER1
{
public:


	

private:

	bool Deadly;

	void PL1_skill();//PLAYER1のスキルの処理
	void Draw();//PLAYER1の描画
};

class PLAYER2
{
public:


	void PL2_skill();//PLAYER2のスキル処理
	

private:

	//void Anim();//PLAYER2のアニメ処理
	int x,y;//PLAYER2の描画位置

	
};

class PLAYER3
{
public:

	void Skill();

private:

	
	void Draw();//三人目のプレイヤーの描画位置

};