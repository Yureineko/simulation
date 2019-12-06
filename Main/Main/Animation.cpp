#include <DxLib.h>
#include "Animation.h"

Animation::Animation(bool Isloop)
{
	animationlimit = 0;
	time = 0;
	timelimit = 0;
	nowanimation = 0;
	repeat = Isloop;

	for (int i = 0; i < 99; i++)
		animationgraph[i] = 0;
}

void Animation::SetPosition(int x, int y)
{
	DrawposX = x;
	DrawposY = y;
}

void Animation::Draw()
{
	DrawGraphF(DrawposX, DrawposY, animationgraph[animationlimit], TRUE);
	time++;
	if (time >= timelimit)
	{
		time = 0;
		nowanimation++;
		if (animationlimit == nowanimation)
		{
			//åªç›ìríÜ
		}
	}
}

void Animation::Add(const char Graphname[])
{
	animationgraph[animationlimit] = LoadGraph(Graphname);
	animationlimit++;
}