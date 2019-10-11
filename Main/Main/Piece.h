#pragma once

class SOLDIER //兵士のクラス
{
public:
	void soldier_move();//兵士の移動
	void soldier_Animation();
	void soldier_Select(int x,int y);


private:
	int soldier_imag;//兵士の画像データ
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ

	
};


class ESPIONAGE //諜報員のクラス
{
public:
	void espionage_move();
	void espionage_Animation();

private:
	int imag;

	int espionagr_image();


};

class SORCERER //魔導士のクラス
{
public:
	void sorcerer_move();
	void sorcerer_Animation();


private:
	int sorcerer_image();
};


class KNIGHT //騎士のクラス
{
public:
	void knight_move();
	void knight_Animation();


private:
	int knight_image();//騎士の画像登録用変数
};

class KING  //王のクラス
{
public:
	void king_move();
	void king_Animation();

private:
	int king_image();//王の画像登録用変数

};