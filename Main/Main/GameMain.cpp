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
	SetGraphMode(800, 600, 32);
	//�t�H���g�m��
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	//�����ɃX�e�[�W��


	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");

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