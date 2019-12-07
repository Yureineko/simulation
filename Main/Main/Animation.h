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
	int animationlimit;//�A�j���[�V�����I�����x
	int animationgraph[99];
	int time;
	int timelimit;//�R�}���肷��t���[��
	int nowanimation;//���ݕ\�����Ă���摜

	int DrawposX;//�\������|�W�V����X
	int DrawposY;//�\������|�W�V����Y

	bool activeflag;//���������߂̃t���O
	bool repeat;//���s�[�g�Đ����邩�ǂ���
};