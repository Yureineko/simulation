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
	int animationlimit;//�A�j���[�V�����I�����x
	int animationgraph[99];
	int time;
	int timelimit;//�R�}���肷��t���[��
	int nowanimation;//���ݕ\�����Ă���摜

	int DrawposX;//�\������|�W�V����X
	int DrawposY;//�\������|�W�V����Y

	bool repeat;//���s�[�g�Đ����邩�ǂ���
};