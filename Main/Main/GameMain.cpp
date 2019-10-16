#include "DxLib.h"

#define PI	3.1415926535897932384626433832795f

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
		{ 2,3,4,6,4,3,2 },
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
	//6.����̉�


	//�����Ɉړ���������I��������Map�𐶐�
	/*int SubMap[7][7]
	{
		{ 2,3,4,5,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1 },
		{ 2,3,4,5,4,3,2 },
	};*/




	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");
	

	int t_chara;//���L�����N�^�[�̕\���@1�̖�
	int t_chara2;//���L�����N�^�[�̕\���@2�̖�

	int Soldier=LoadGraph("image\\");//�����ɕ��m�̉摜
	int Sorcerer=LoadGraph("image\\");//�����ɖ����m�̉摜
	int Espionage =LoadGraph("image\\");//�����ɒ�����̉摜
	int Knight =LoadGraph("image\\");//�����ɋR�m�̉摜
	int King = LoadGraph("image\\King.png");//�����ɉ��̉摜
	int EKing = LoadGraph("image\\King.png");//�����ɉ��̉摜
	
	int SoldX = 1, SoldY = 1;//���m�̈ʒuX,Y
	int SorcX = 2, SorcY = 2;//�����m�̈ʒuX,Y
	int EspiX = 3, EspiY = 3;//������̈ʒuX,Y
	int KnigX = 4, KnigY = 4;//�R�m�̈ʒuX,Y
	int KingX = 5, KingY = 5;//���̈ʒuX,Y
	int EKingX = 6, EKingY = 6;//���̈ʒuX,Y


	t_chara = LoadGraph("image\\�L����1(��).png");
	t_chara2 = LoadGraph("image\\�L����2(��).png");

	//�w�i�̉摜�\��	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);

	//����int�ϊ��֐�
	//int bgm = LoadSoundMem("���y��");

	//�Q�[�����C���̉��y�Đ�
	int  Mainbgm = LoadSoundMem("sound\\");

	//DrawGraph(384, 0, King, TRUE);//���̕`��

	DrawGraph(0, 0, t_chara, TRUE);//�v���C���[1�̕`��
	DrawGraph(640, 0, t_chara2, TRUE);//�v���C���[2�̕`��


	int turn=0;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)
	

	//�o�b�N�o�b�t�@�ɕ`��
	//SetDrawScreen(DX_SCREEN_FRONT);

	//DX���C�u������������
	if (DxLib_Init() == -1)
	{
		return -1;//�G���[���o���狭���I��

	}

	//
	//�����ŃQ�[���̃��C�������\�z
	while (1)
	{
		

	//�I�����̈ړ�	
		if (CheckHitKey(KEY_INPUT_UP))
		{
			//�L�[�������ď�ɑI�����ړ�
			//if (MainMap[0][1] )
			KingX++;
		};

		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			//�L�[�������ĉ��ɑI�����ړ�
			//if(MainMap[0][2])
		};

		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			//�L�[�������ĉE�ɑI�����ړ�
		};

		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			//�L�[�������č��ɑI�����ړ�

		};

		//�����̋����̋�ɏd�Ȃ������̏���
		/*if (MainMap[][])
		{

		}*/

//----------�o�^������̈ړ��`��-----------

		//Swich����map�̕`��ƍX�V���s��
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				switch (MainMap[y][x])
				{

				case 0://�����Ȃ��ꏊ
					break;

				case 1://���m
				{
					DrawGraphF(x * 64 + 192, y * 64, Soldier, TRUE);//���m�̕`��
					break;
				}

				case 2://�����m
				{
					DrawGraphF(x * 64 + 192, y * 64, Sorcerer, TRUE);//�����m�̉摜
					break;
				}

				case 3://�����
				{
					DrawGraphF(x * 64 + 192, y * 64, Espionage, TRUE);//������̉摜
					break;
				}

				case 4://�R�m
				{
					DrawGraphF(x * 64 + 192, y * 64, Knight, TRUE);//�R�m�̉摜
					break;
				}

				case 5://��
				{
					DrawGraphF(x * 64 + 192, y * 64, King, TRUE);//�R�m�̉摜
					break;
				}

				case 6://����̉�
				{
					DrawRotaGraph3(x*64+256,y*64+64,0,0, 1.0f, 1.0f, PI, EKing, TRUE);//���̉摜
					break;
				}
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