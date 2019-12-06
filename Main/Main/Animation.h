#pragma once

class Animation
{
public :
	Animation(bool Isloop);
	~Animation() {};
	void SetPosition(int x, int y);
	void Settimelimit(int time) { timelimit = time; }
	void Draw();
	void Add(const char Graphname[]);
private :
	int animationlimit;//アニメーション終了限度
	int animationgraph[99];
	int time;
	int timelimit;//コマ送りするフレーム
	int nowanimation;//現在表示している画像

	int DrawposX;//表示するポジションX
	int DrawposY;//表示するポジションY

	bool repeat;//リピート再生するかどうか
};