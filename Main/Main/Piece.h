#pragma once

//移動方向
enum VEC
{
	RIGHT,
	UP,
	LEFT,
	DOWN,
	N,
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
	 SOLDIER(int SolX, int SolY);//兵士の移動

	 int Action(VEC vec);
	 int GetX();
	 int GetY();
	 void Draw();

	void soldier_Animation();//兵士のアニメーション
	void soldier_Select();//移動範囲の選択


private:

	POS pos;//兵士の現在位置
	int soldier_imag;//兵士の画像データの登録
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ

	
};


class ESPIONAGE //諜報員のクラス
{
public:
	ESPIONAGE(int EX, int EY);

	int Action(VEC vec);
	void Draw();//描画
	int GetX();
	int GetY();


	//void espionage_move(int x,int y);//
	//void espionage_Animation();//

private:
	POS pos;//諜報員の位置
	int espionagr_image;//最後にこのクラスで絵を描画する。
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ

};

class SORCERER //魔導士のクラス
{
public:
	SORCERER(int SorX, int SorY);
	
	int Action(VEC vec);
	void Draw();//描画
	int GetX();
	int GetY();

	//void sorcerer_move(int x,int y);//魔導士の移動
	//void sorcerer_Animation();//魔導士のアニメーション


private:
	POS pos;//魔導士の位置
	int sorcerer_image;//最後にこのクラスで絵を描画する。
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ
};


class KNIGHT //騎士のクラス
{
public:
	KNIGHT(int KnX, int KnY);
	int Action(VEC vec);//騎士の移動
	void Draw();//描画
	int GetX();
	int GetY();

	//void knight_move(int x,int y);//騎士の移動
	//void knight_Animation();//騎士のアニメーション


private:
	POS pos;//騎士の位置
	int knight_image;//騎士の画像登録用変数 最後にこのクラスで絵を描画する。
	int x, y;//騎士の位置
};

class KING  //王のクラス
{
public:
	 KING(int Kx,int Ky);//王の移動
	 int Action(VEC vec);//移動の処理
	 void Draw();//描画
	 int GetX();
	 int GetY();

	//void king_Animation();//王のアニメーション

private:
	POS pos;//王の位置
	int SelectFlag;//選択したときの移動範囲を表示させるフラグ
	int king_image;//王の画像登録用変数 最後にこのクラスで絵を描画する。
	int x, y;//王の位置

};