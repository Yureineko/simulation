#include <DxLib.h>
#include "Animation.h"

//アニメーション初期化
Animation::Animation()
{
	animationlimit = 0;
	time = 0;
	timelimit = 0;
	nowanimation = 0;
	activeflag = false;
	repeat = false;

	DrawposX = 0;
	DrawposY = 0;

	for (int i = 0; i < 99; i++)
		animationgraph[i] = 0;
}

//動作中の動き
void Animation::Update()
{
	//activeflagがtrueであれば描画
	if (activeflag == true)
	{
		Draw();
	}
}

//描画する位置の設定用
void Animation::SetPosition(int x, int y)
{
	DrawposX = x;
	DrawposY = y;
}

//描画用
void Animation::Draw()
{
	DrawGraphF(DrawposX, DrawposY, animationgraph[nowanimation], TRUE);
	time++;
	if (time >= timelimit)
	{
		time = 0;
		nowanimation++;
		if (animationlimit == nowanimation)
		{
			if (repeat == false)
				activeflag = false;
			nowanimation = 0;
		}
	}
}

//描画開始用
void Animation::Active(bool Isloop)
{
	repeat = Isloop;
	activeflag = true;
}

//描画停止用
void Animation::Stop()
{
	activeflag = false;
	repeat = false;
	time = 0;
	timelimit = 0;
	nowanimation = 0;
}

//描画アニメーション追加用
void Animation::Add(const char Graphname[])
{
	animationgraph[animationlimit] = LoadGraph(Graphname);
	animationlimit++;
}