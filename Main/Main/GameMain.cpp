#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//window���[�h�ŋN��
	ChangeWindowMode(TRUE);
	//Dx���C�u�����̏�����
	DxLib_Init();
	//�E�B���h�E���ݒ�
	SetMainWindowText("SimulatioN GamE");
	//�Q�[���E�C���h�E�T�C�Y
	SetGraphMode(832, 448, 32);
	//�t�H���g�m��
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	bool KeyFlag = false;

	//�����ɃX�e�[�W��


	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");

	//�w�i�̉摜�\��	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
	LoadGraphScreen(192, 64, "image\\King.png", TRUE);

	//����int�ϊ��֐�
	//int bgm = LoadSoundMem("���y��");

	//�o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//
	//

	while (1)
	{
		//aaaa


		//if()


		//������\��
		//DrawString(x, y, �\�����镶����(*char), �\������ۂ̕����̐F(GetColor(r,g,b)));

		//�摜�\��
		//DrawGraph(x, y, img�摜(int�^), TRUE);

		//�Q�[�����I���t���O�������Ă��������
		if (ProcessMessage() == -1)
			break;
	}

	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}