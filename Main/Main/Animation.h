#pragma once

class Animation
{
public :
	Animation();
	~Animation() {};

	void Update();

	void SetPosition(int x, int y);
	void Settimelimit(int time) { timelimit = time; }
	void Draw();
	void Active(bool Isloop);
	void Stop();
	void Add(const char Graphname[]);
private :
	int animationlimit;//アニメーション終了限度
	int animationgraph[99];
	int time;
	int timelimit;//コマ送りするフレーム
	int nowanimation;//現在表示している画像

	int DrawposX;//表示するポジションX
	int DrawposY;//表示するポジションY

	bool activeflag;//動かすためのフラグ
	bool repeat;//リピート再生するかどうか
};