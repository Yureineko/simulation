#pragma once
#include"DxLib.h"
#include<string.h>//文字列を使うのでstringをinclude
#include<string>
#include<stdio.h>

class PLAYER1
{
public:


	void Skill();//PLAYER1のスキルの処理など
};

class PLAYER2
{public:


	void Skill();
	

private:

	void Anim();//二人目のプレイヤーのアニメ処理
	int x,y;//二人目のプレイヤーの描画位置

	
};