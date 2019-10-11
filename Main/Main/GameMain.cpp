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


	

	//�����ɔՏ��ݒ�
	//��̎�ނ͍ő�5���
	int MainMap[7][7]
	{
		{ 2,3,4,5,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1 },
		{ 2,3,4,5,4,3,2 },
	};
	//1.���m(��)
	//2.�����m(�p)
	//3.�����(�`�F�X:�i�C�g)
	//4.�R�m(���)
	//5.��


	//�����Ɉړ���������I��������Map�𐶐�
	int SubMap[7][7]
	{
		{ 2,3,4,5,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1 },
		{ 2,3,4,5,4,3,2 },
	};




	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");
	int map;//�Ղ̉摜�o�^

	int t_chara;//���L�����N�^�[�̕\���@1�̖�
	int t_chara2;//���L�����N�^�[�̕\���@2�̖�

	 //MainMap[1]=LoadGraph("image\\");//�����ɕ��m�̉摜
	 //MainMap[2]=LoadGraph("image\\");//�����ɖ����m�̉摜
	 //MainMap[3]=LoadGraph("image\\");//�����ɒ�����̉摜
	 //MainMap[4]=LoadGraph("image\\");//�����ɋR�m�̉摜
	 //MainMap[5]=LoadGraph("image\\");//�����ɉ��̉摜



	 t_chara = LoadGraph("image\\201401231944448d7.png");
	 t_chara2 = LoadGraph("image\\p-wakana-24.png");

	//�w�i�̉摜�\��	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
	LoadGraphScreen(192, 64, "image\\King.png", TRUE);

	//����int�ϊ��֐�
	//int bgm = LoadSoundMem("���y��");

	 DrawGraph(164, 0, t_chara, TRUE);//�v���C���[1�̕`��

	 DrawGraph(0, 0, t_chara2, TRUE);//�v���C���[2�̕`��


	 int turn=0;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	 int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)


	//�o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//DX���C�u������������
	if (DxLib_Init() == -1)
	{
		return -1;//�G���[���o���狭���I��

	}

	//
	//

	while (1)
	{
		

	//�I�����̈ړ�	
		if (CheckHitKey(KEY_INPUT_UP))
		{
			//�L�[�������ď�ɑI�����ړ�
			//if (MainMap[0][1] )
		};




//----------�o�^������̈ړ��`��-----------

		//Swich����map�̕`��ƍX�V���s��
		for (int y = 0; y< 7; y++)
		{
			for (int x=0;x<7;x++)
			{
				switch (MainMap[y][x])
				{
				
				case 0://�����Ȃ��ꏊ
					break;

				case 1://���m
					//DrawGraphF(x*64,y*64,)//���m�̕`��
					break;

				case 2://�����m
					//DrawGraphF(x*64,y*64,)//�����m�̉摜
					break;

				case 3://�����
					//DrawGraphF(x*64,y*64,)//������̉摜
					break;

				case 4://�R�m
					//DrawGraphF(x*64,y*64,)//�R�m�̉摜
					break;

				case 5://��
					//DrawGraphF(x*64,y*64)//���̉摜
					break;
				}
			}
		}




		//������\��
		//DrawString(x, y, �\�����镶����(*char), �\������ۂ̕����̐F(GetColor(r,g,b)));

		//�摜�\��
		//DrawGraph(x, y, img�摜(int�^), TRUE);

		
		//���̕ӂ�?�ŏ��s������s����break��while���𔲂���B


		//�Q�[�����I���t���O�������Ă��������
		if (ProcessMessage() == -1)
			break;
	}

	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}