#pragma once

//移動方向
enum VEC
{
	RIGHT,
	UP,
	LEFT,
	DOWN,

};


//駒の位置情報
struct POS
{
	int x,y;
};

//移動先
struct Move_POS
{
	int x,y;

};


class SOLDIER //兵士のクラス
{
public:
	void soldier_move(int x, int y);//兵士の移動
	void soldier_Animation();
	void soldier_Select();


private:
	int soldier_imag;//兵士の画像データ　最後にこのクラスで絵を描画する。
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ

	
};


class ESPIONAGE //諜報員のクラス
{
public:
	void espionage_move(int x,int y);//
	void espionage_Animation();//

private:
	int imag;

	int espionagr_image();//最後にこのクラスで絵を描画する。


};

class SORCERER //魔導士のクラス
{
public:
	void sorcerer_move(int x,int y);//魔導士の移動
	void sorcerer_Animation();//魔導士のアニメーション


private:
	int sorcerer_image();//最後にこのクラスで絵を描画する。
};


class KNIGHT //騎士のクラス
{
public:
	void knight_move(int x,int y);//騎士の移動
	void knight_Animation();//騎士のアニメーション


private:
	int knight_image();//騎士の画像登録用変数 最後にこのクラスで絵を描画する。
};

class KING  //王のクラス
{
public:
	 KING(int x,int y);//王の移動
	void king_Animation();//王のアニメーション

private:
	int king_image;//王の画像登録用変数 最後にこのクラスで絵を描画する。
	int x, y;//王の位置

};