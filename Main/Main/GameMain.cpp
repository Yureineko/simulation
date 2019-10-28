#include "DxLib.h"

#define SCREEN_PIXWIDTH		832
#define SCREEN_PIXHEIGHT	448
#define POPUP_X 64
#define POPUP_Y 64

#define PI	3.1415926535897932384626433832795f

//�N���b�N�̗̈���`�F�b�N����֐�
bool HitClick(int Cx, int Cy, int x1, int y1);

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

	//��U��U�̔���(���u���@��U�R�����g�A�E�g��)
	int Random[1];
	int Green = GetColor(0, 255, 0);
	
	//�����̏����l��123456�ɐݒ肷��
	SRand(123456);

	//�����ɔՏ��ݒ�
	//��̎�ނ͍ő�5���
	int MainMap[7][7]=
	{
		{ 2,3,4,6,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,5,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 1,1,1,0,1,1,1 },
		{ 2,3,4,0,4,3,2 },
	};
	//1.���m(��)
	//2.�����m(�p)
	//3.�����(�`�F�X:�i�C�g)
	//4.�R�m(���)
	//5.��
	//6.����̉�




	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");
	

	int t_chara;//���L�����N�^�[�̕\���@1�̖�
	int t_chara2;//���L�����N�^�[�̕\���@2�̖�

	int Soldier=LoadGraph("image\\");//�����ɕ��m�̉摜
	int Sorcerer=LoadGraph("image\\");//�����ɖ����m�̉摜
	int Espionage =LoadGraph("image\\");//�����ɒ�����̉摜
	int Knight =LoadGraph("image\\");//�����ɋR�m�̉摜
	int King =LoadGraph("image\\King(64).png");//�����ɉ��̉摜
	int EKing = LoadGraph("image\\King(64).png");//�����ɉ��̉摜

	//��U�����ňʒu�ړ�����B��ŏ��������B
	int SoldX = 1, SoldY = 1;//���m�̈ʒuX,Y
	int SorcX = 2, SorcY = 2;//�����m�̈ʒuX,Y
	int EspiX = 3, EspiY = 3;//������̈ʒuX,Y
	int KnigX = 4, KnigY = 4;//�R�m�̈ʒuX,Y
	int KingX = 5, KingY = 5;//���̈ʒuX,Y	
	int EKingX = 6, EKingY = 6;//���̈ʒuX,Y


	//int King = LoadGraph("image\\King.png");

	t_chara = LoadGraph("image\\�L����1(��).png");
	t_chara2 = LoadGraph("image\\�L����2(��).png");

	//�w�i�̉摜�\��	
	LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);

	//����int�ϊ��֐�
	//int bgm = LoadSoundMem("���y��");

	//�Q�[�����C���̉��y�Đ�
	int  Mainbgm = LoadSoundMem("sound\\");

	//�A�j���[�V�����o�^�T���v��
	int MovieGraphHandle;

	MovieGraphHandle=LoadGraph("image\\nc157304.mp4");
	PlayMovieToGraph(MovieGraphHandle);



	//test�p�T�E���h
	int se=LoadSoundMem("sound\\test.mp3");

	
	//DrawGraph(384, 0, King, TRUE);//���̕`��

	DrawGraph(0, 0, t_chara, TRUE);//�v���C���[1�̕`��
	DrawGraph(640, 0, t_chara2, TRUE);//�v���C���[2�̕`��
	
	int turn=0;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)
	

	int win_flag = false;//���������̃t���O
	int lose_flag = false;//���������̃t���O



	//---------�}�E�X����̕ϐ�--------
	
	

	 //GetMousePoint(&Mx,&My);//�}�E�X�̌��݈ʒu�擾

	//�}�E�X��window��ɕ\��������B
	//SetMouseDispFlag(TRUE);


	//�����ŕ`����\��ʂɂ���B
	SetDrawScreen(DX_SCREEN_FRONT);

	int cx, cy;
	bool Click_flag = 0;


	//DX���C�u������������
	if (DxLib_Init() == -1)
	{
		return -1;//�G���[���o���狭���I��

	}


	//while(�����)



	//�����ŃQ�[���̃��C�������\�z
	while (ProcessMessage() == -1)
	{
		//�����̃^�[���ȊO�͑����s�\�ɂ���
		if (turn == 0)
		{
			int Mx, My,

				Mbutton = false;//�}�E�X�ʒuX,Y �}�E�X���������Ƃ��̃{�^��


			GetMousePoint(&Mx, &My);

			//�}�E�X�̍��N���b�N��������Ă��邩
			//�}�E�X��������Ă��Ȃ��Ƃ�
			//�����ŃN���b�N�ł���̈��ݒ�


			//if (Mx <=MainMap[KingY][KingX])//
			//{
			//	//int x,y;

			//	//�}�E�X���������Ƃ��̏���
			//	//���N���b�N�����Ƃ��̏���
			//		if (GetMouseInput() != 0&&MOUSE_INPUT_LEFT!=0)
			//		{
			//			Mbutton = TRUE;

			//			if (Mbutton==TRUE)
			//			{
			//			
			//				//������Ă���
			//				PlaySoundMem(se, DX_PLAYTYPE_BACK);
			//			}

			//		}


			//		
			//		else
			//		{
			//			//������Ă��Ȃ�
			//			

			//		}

			//}

			//�N���b�N�����悪0�Ȃ炻���ɕ`��


				//�}�E�X���������Ƃ��̏���
				//���N���b�N�����Ƃ��̏���
			while (GetMouseInput() != 0 & MOUSE_INPUT_LEFT != 0)
			{
				Mbutton = false;

				if (MainMap[KingY][KingX + 1] == 0)
				{

					//������Ă���
					PlaySoundMem(se, DX_PLAYTYPE_BACK);
					MainMap[KingY][KingX - 1] = 5;

					MainMap[KingY][KingX] = 0;
					//Mbutton=true;

				}
			}

			//
			//{
			//	//������Ă��Ȃ�

			//	//MainMap[KingY][KingX] = 5;
			//	Mbutton = false;
			//}





			DrawBox(0, 0, 192, SCREEN_PIXHEIGHT, GetColor(0, 255, 255), 1);
			DrawBox(640, 0, SCREEN_PIXWIDTH, SCREEN_PIXHEIGHT, GetColor(255, 0, 255), 1);
			//�I�����̈ړ�	
			if (CheckHitKey(KEY_INPUT_UP))
			{
				//�L�[�������ď�ɑI�����ړ�
				//if (MainMap[0][1] )
				//KingX++;
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
			/*if (MainMap[kx][ky])
			{

			}*/
		}
		//else
		//{

		//	turn = 1;//����̃^�[����Ԃ��ďI��
		//};


		//���̕ӂ�?�ŏ��s������s����break��while���𔲂���B

		//�����̉����Ƃ�ꂽ�ꍇ
		if (MainMap[KingY][KingX]==0)
		{
			//���s����
			lose_flag = true;
			//break;

		};

//----------�o�^������̈ړ��`��-----------

		//Swich����map�̕`��ƍX�V���s��
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				switch (MainMap[y][x])
				{
				
				case 0:
				{
					//�����Ȃ��ꏊ
					break;
				}

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
				DrawGraphF(x * 64 + 192, y * 64, Knight, TRUE);//�R�m�̉摜
					{
					break;
				}

				case 5://��
				{
					DrawGraphF(x * 64 + 192, y * 64, King, TRUE);//�R�m�̉摜
					KingX = x;
					KingY = y;
					break;
				}

				case 6://����̉�
				{
					DrawRotaGraph3(x*64+256,y*64+65,0,0, 1.0f, 1.0f, PI, EKing, TRUE);//���̉摜
					EKingX = x;
					EKingY = y;
					break;
				}


				}
			}
		}

		//�A�j���[�V�����Đ��T���v��
		/*while (ProcessMessage() == 0)
		{
			DrawGraph(0, 0, MovieGraphHandle, FALSE);
			WaitTimer(10);
		}*/

		//������\��
		//DrawString(x, y, �\�����镶����(*char), �\������ۂ̕����̐F(GetColor(r,g,b)));

		//�摜�\��
		//DrawGraph(x, y, img�摜(int�^), TRUE);

	}

	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}

//�N���b�N����̈�̔���
bool HitClick(int Cx,int Cy,int x1,int y1)
{
	if (Cx < x1 + 64 && x1 < Cx + 64 && Cy < y1 + 64 && y1 < Cy + 64)
	{
		return TRUE;
	}
	return FALSE;
}