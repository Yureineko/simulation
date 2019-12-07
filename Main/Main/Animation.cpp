#include <DxLib.h>
#include "Animation.h"

//�A�j���[�V����������
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

//���쒆�̓���
void Animation::Update()
{
	//activeflag��true�ł���Ε`��
	if (activeflag == true)
	{
		Draw();
	}
}

//�`�悷��ʒu�̐ݒ�p
void Animation::SetPosition(int x, int y)
{
	DrawposX = x;
	DrawposY = y;
}

//�`��p
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

//�`��J�n�p
void Animation::Active(bool Isloop)
{
	repeat = Isloop;
	activeflag = true;
}

//�`���~�p
void Animation::Stop()
{
	activeflag = false;
	repeat = false;
	time = 0;
	timelimit = 0;
	nowanimation = 0;
}

//�`��A�j���[�V�����ǉ��p
void Animation::Add(const char Graphname[])
{
	animationgraph[animationlimit] = LoadGraph(Graphname);
	animationlimit++;
}