#include "DxLib.h"
#include "Piece.h"
#include "Grobal.h"

#define SCREEN_PIXWIDTH		832
#define SCREEN_PIXHEIGHT	448
#define POPUP_X 192//�����̓_
#define POPUP_Y 0
#define POPDOWN_X 64
#define POPDOWN_Y 64

#define PI	3.1415926535897932384626433832795f

//�N���b�N�̗̈���`�F�b�N����֐�
bool HitClick(int Cx, int Cy, int x1, int y1);

bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey);

POS HitPos(int PosX, int PosY);

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
	int CanMoveMap[7][7] = {0};

	//��ۑ��p
	Piece piecetable[28];
	for (int i = 0, count = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (MainMap[i][j] >= 1)
			{
				piecetable[count].posX = j;
				piecetable[count].posY = i;
				piecetable[count].type = MainMap[i][j];
				if (i < 4)
				{
					piecetable[count].MeorEne = false;
				}
				else
				{
					piecetable[count].MeorEne = true;
				}
				count++;

				if (MainMap[i][j] == 1)
				{
					piecetable[count].movelimit = 1;
					piecetable[count].moverange[0][0] = 0; piecetable[count].moverange[0][1] = -1;
				}
				if (MainMap[i][j] == 2)
				{
					piecetable[count].movelimit = 12;
					piecetable[count].moverange[0][0] = -3;  piecetable[count].moverange[0][1] = 3;
					piecetable[count].moverange[1][0] = -3;  piecetable[count].moverange[1][1] = -3;
					piecetable[count].moverange[2][0] = -2;  piecetable[count].moverange[2][1] = 2;
					piecetable[count].moverange[3][0] = -2;  piecetable[count].moverange[3][1] = -2;
					piecetable[count].moverange[4][0] = -1;  piecetable[count].moverange[4][1] = 1;
					piecetable[count].moverange[5][0] = -1;  piecetable[count].moverange[5][1] = -1;
					piecetable[count].moverange[6][0] = 1;   piecetable[count].moverange[6][1] = 1;
					piecetable[count].moverange[7][0] = 1;   piecetable[count].moverange[7][1] = -1;
					piecetable[count].moverange[8][0] = 2;   piecetable[count].moverange[8][1] = 2;
					piecetable[count].moverange[9][0] = 2;   piecetable[count].moverange[9][1] = -2;
					piecetable[count].moverange[10][0] = 3;  piecetable[count].moverange[10][1] = 3;
					piecetable[count].moverange[11][0] = 3;  piecetable[count].moverange[11][1] = -3;
				}
				if (MainMap[i][j] == 3)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].moverange[0][0] = -3; piecetable[count].moverange[0][1] = 1;
					piecetable[count].moverange[1][0] = -3; piecetable[count].moverange[1][1] = -1;
					piecetable[count].moverange[2][0] = -1; piecetable[count].moverange[2][1] = 3;
					piecetable[count].moverange[3][0] = -1; piecetable[count].moverange[3][1] = -3;
					piecetable[count].moverange[4][0] = 1;  piecetable[count].moverange[4][1] = 3;
					piecetable[count].moverange[5][0] = 1;  piecetable[count].moverange[5][1] = -3;
					piecetable[count].moverange[6][0] = 3;  piecetable[count].moverange[6][1] = 1;
					piecetable[count].moverange[7][0] = 3;  piecetable[count].moverange[7][1] = -1;
				}
				if (MainMap[i][j] == 4)
				{
					piecetable[count].movelimit = 12;
					piecetable[count].moverange[0][0] = -3;  piecetable[count].moverange[0][1] = 0;
					piecetable[count].moverange[1][0] = -2;  piecetable[count].moverange[1][1] = 0;
					piecetable[count].moverange[2][0] = -1;  piecetable[count].moverange[2][1] = 0;
					piecetable[count].moverange[3][0] = 0;   piecetable[count].moverange[3][1] = 3;
					piecetable[count].moverange[4][0] = 0;   piecetable[count].moverange[4][1] = 2;
					piecetable[count].moverange[5][0] = 0;   piecetable[count].moverange[5][1] = 1;
					piecetable[count].moverange[6][0] = 0;   piecetable[count].moverange[6][1] = -1;
					piecetable[count].moverange[7][0] = 0;   piecetable[count].moverange[7][1] = -2;
					piecetable[count].moverange[8][0] = 0;   piecetable[count].moverange[8][1] = -3;
					piecetable[count].moverange[9][0] = 1;   piecetable[count].moverange[9][1] = 0;
					piecetable[count].moverange[10][0] = 2;  piecetable[count].moverange[10][1] = 0;
					piecetable[count].moverange[11][0] = 3;  piecetable[count].moverange[11][1] = 0;
				}
				if (MainMap[i][j] == 5)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].moverange[0][0] = -1; piecetable[count].moverange[0][1] = 1;
					piecetable[count].moverange[1][0] = -1; piecetable[count].moverange[1][1] = 0;
					piecetable[count].moverange[2][0] = -1; piecetable[count].moverange[2][1] = -1;
					piecetable[count].moverange[3][0] = 0;  piecetable[count].moverange[3][1] = 1;
					piecetable[count].moverange[4][0] = 0;  piecetable[count].moverange[4][1] = -1;
					piecetable[count].moverange[5][0] = 1;  piecetable[count].moverange[5][1] = 1;
					piecetable[count].moverange[6][0] = 1;  piecetable[count].moverange[6][1] = 0;
					piecetable[count].moverange[7][0] = 1;  piecetable[count].moverange[7][1] = -1;
				}
			}
		}
	}

	SORCERER*sorcerer;//�����m�̖{��
	enum VEC Sor_vec;//�����m�̈ړ�����

	ESPIONAGE*espionage;//������̖{��
	enum VEC Es_Vec;//������̈ړ�����

	KNIGHT*knight;//�R�m�̖{��
	enum VEC Kn_vec;//�R�m�̈ړ�����

	SOLDIER*soldier;//���m�̖{��
	enum VEC Sol_vec;//���m�̈ړ�����

	KING* king;//���̖{��
	enum VEC Kin_vec;//���̈ړ�����

	EnemyKING*enemyking;//�G���̖{��
	enum VEC EKin_vec;//�G���̈ړ�����

	//�摜int�ϊ��֐�
	//int img = LoadGraph("�摜��");
	

	int t_chara;//���L�����N�^�[�̕\���@1�̖�
	int t_chara2;//���L�����N�^�[�̕\���@2�̖�

	int Soldier=LoadGraph("image\\Soldier(64).png");//�����ɕ��m�̉摜
	int Sorcerer=LoadGraph("image\\Sorcerer(64).png");//�����ɖ����m�̉摜
	int Espionage =LoadGraph("image\\Espionage(64).png");//�����ɒ�����̉摜
	int Knight =LoadGraph("image\\Knight(64).png");//�����ɋR�m�̉摜
	int King =LoadGraph("image\\King(64).png");//�����ɉ��̉摜
	int EKing = LoadGraph("image\\King(64).png");//�����ɉ��̉摜

	int GreenFilter = LoadGraph("image\\greenfilter.png");

	//��U�����ňʒu�ړ�����B��ŏ��������B
	int SoldX = 1, SoldY = 1;//���m�̈ʒuX,Y
	int SorcX = 2, SorcY = 2;//�����m�̈ʒuX,Y
	int EspiX = 3, EspiY = 3;//������̈ʒuX,Y
	int KnightX = 4, KnightY = 4;//�R�m�̈ʒuX,Y
	int KingX = 5, KingY = 5;//���̈ʒuX,Y	

	//�{�^���Ǘ����W�p
	Pos clickpos;     //�N���b�N�ʒu�ۑ��p
	Pos outclickpos;  //�N���b�N�������ʒu�ۑ��p
	bool saveclickflag;
	bool clickflag;
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;
	clickflag = false;
	//[][0]�ɋ�̎�ށA[][1]�ɐ����󋵁A[][2]��x���W�A[][3]��y���W
	int MyPieceInfo[14][4]
	{
		{1,1,1,1},{1,1,1,2}
	};

	POS movePos = {0,0};
	int movepiece = -1;
	bool moveflag = false;

	int EKingX = 6, EKingY = 6;//�G�̉��̈ʒuX,Y


	//int King = LoadGraph("image\\King.png");

	
	t_chara = LoadGraph("image\\�L����1(��).png");
	t_chara2 = LoadGraph("image\\�L����2(��).png");
	

	int sc = LoadGraph("image\\BackGround.png");

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

	
	
	int turn=0;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)
	int Mx, My;//�}�E�X�̈ʒu




	int win_flag = false;//���������̃t���O
	int lose_flag = false;//���������̃t���O



	//---------�}�E�X����̕ϐ�--------
	
	

	 //GetMousePoint(&Mx,&My);//�}�E�X�̌��݈ʒu�擾

	//�}�E�X��window��ɕ\��������B
	//SetMouseDispFlag(TRUE);

	//�o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	int cx, cy;
	bool Click_flag = 0;


	//DX���C�u������������
	if (DxLib_Init() == -1)
	{
		return -1;//�G���[���o���狭���I��

	}


	//while(�����)



	//�����ŃQ�[���̃��C�������\�z
	while (ProcessMessage() != -1)
	{
		ScreenFlip();//�摜�̃t���b�v(�؂�ւ�)
		ClearDrawScreen();//�摜�̃N���A

		//�}�E�X�̏�Ԃ��m�F����
		if (GetMouseInput() & MOUSE_INPUT_LEFT)
		{
			//���N���b�N�������ꂽ�Ƃ��A�������ꏊ���m�F����
			if (saveclickflag == false)
			{
				saveclickflag = true;
				GetMousePoint(&clickpos.posX, &clickpos.posY);
			}
		}
		else
		{
			//���N���b�N�������ꂽ�Ƃ��A�������ꏊ���m�F����
			if (saveclickflag == true)
			{
				saveclickflag = false;
				GetMousePoint(&outclickpos.posX, &outclickpos.posY);
			}
		}

		//�����̃^�[���ȊO�͑����s�\�ɂ���
		if (turn == 0)
		{
			if (clickflag == false && saveclickflag == true)
			{
				if (moveflag == false)
				{
					POS SavePos = HitPos(clickpos.posX, clickpos.posY);
					for (int i = 0; i < 28; i++)
					{
						if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0)
						{
							movepiece = i;
							moveflag = true;
							clickflag = true;
							/*for (int j = 0; j < piecetable[i].movelimit; j++)
							{

							}*/
						}
					}
				}
				else
				{
					if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7)
					{
						int latemove = -1;
						movePos = HitPos(clickpos.posX, clickpos.posY);
						for (int i = 0; i < 28; i++)
						{
							if (movePos.x == piecetable[i].posX && movePos.y == piecetable[i].posY && i != movepiece)
							{
								latemove = i;
							}
						}
						if (latemove != -1)
						{
							if (piecetable[movepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
							{
								piecetable[movepiece].posX = movePos.x;
								piecetable[movepiece].posY = movePos.y;
								piecetable[latemove].type = 0;
								movepiece = -1;
							}
						}
						else
						{
							piecetable[movepiece].posX = movePos.x;
							piecetable[movepiece].posY = movePos.y;
							movepiece = -1;
						}
						clickflag = true;
						moveflag = false;
						/*
						if(piecetable[movepiece].MeorEne)
								movepiece = i;
								moveflag = true;
						*/
					}
				}
			}
			else if (saveclickflag == false)
			{
				clickflag = false;
			}

			

			GetMousePoint(&Mx, &My);




			//�}�E�X�̍��N���b�N��������Ă��邩
			//�}�E�X��������Ă��Ȃ��Ƃ�
			//�����ŃN���b�N�ł���̈��ݒ�
			//�N���b�N�����悪0�Ȃ炻���ɕ`��
			/*
			for (int y = 0; y < 7; y++)
			{
				for (int x = 0; x < 7; x++)
				{
					switch (MainMap[y][x])
					{
					case 1:
						//���m�̐���
						soldier = new SOLDIER(x * 64, y * 64);
						MainMap[y][x] = 1;
						soldier->Draw();
						break;
					case 2:
						//�����m�̐���
						sorcerer = new SORCERER(x * 64, y * 64);
						MainMap[y][x] = 2;
						sorcerer->Draw();
						break;
					case 3:
						//������̐���
						espionage = new ESPIONAGE(x * 64, y * 64);
						MainMap[y][x] = 3;
						espionage->Draw();
						break;

					case 4:
						//�R�m�̐���
						knight = new KNIGHT(x * 64, y * 64);
						MainMap[y][x] = 4;
						knight->Draw();
						break;

					case 5:
						   //���̐���
						   king = new KING(x * 64, y * 64);
						   MainMap[y][x] = 5;
						   king->Draw();
						break;
					}
					
				}
			}*/
			//�w�i�̉摜�\��	
			LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
			DrawGraph(0, 0, t_chara, TRUE);//�v���C���[1�̕`��
			DrawGraph(640, 0, t_chara2, TRUE);//�v���C���[2�̕`��
			for (int i = 0; i < 28; i++)
			{
				switch (piecetable[i].type)
				{
				case 1:
					//���m�̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Soldier, TRUE);
					break;
				case 2:
					//�����m�̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Sorcerer, TRUE);
					break;
				case 3:
					//������̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Espionage, TRUE);
					break;

				case 4:
					//�R�m�̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Knight, TRUE);
					break;

				case 5:
					//���̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, King, TRUE);
					break;

				case 6:
					//�G���̐���
					DrawRotaGraph(piecetable[i].posX * 64 + 224, piecetable[i].posY * 64+32,1.0f,PI, EKing, TRUE);
					break;
				}
				if (i == movepiece)
				{
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, GreenFilter, TRUE);
				}
			}

			//king->Draw();
			
		


		
		}
		
		//���̕ӂ�?�ŏ��s������s����break��while���𔲂���B

		

		//outpos��-1�ȊO�̏ꍇ���l��-1�ɂ���
		if (outclickpos.posX != -1 && outclickpos.posY != -1)
		{
			clickpos.posX = -1;
			clickpos.posY = -1;
			outclickpos.posX = -1;
			outclickpos.posY = -1;
		}

//----------�o�^������̈ړ��`��-----------

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

//�{�^���`�F�b�N�p�֐�
bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey)
{
	if (pushclick.posX >= button.posX && pushclick.posX <= button.posX + sizex &&
		pushclick.posY >= button.posY && pushclick.posY <= button.posY + sizey &&
		outclick.posX >= button.posX && outclick.posX <= button.posX + sizex &&
		outclick.posY >= button.posY && outclick.posY <= button.posY + sizey)
	{
		//�������ʒu�A���N���b�N��b�����ʒu�����Ƀ{�^�����ł����
		//true��Ԃ�
		return true;
	}
	else
	{
		//�����łȂ����false
		return false;
	}
}

//�N���b�N�����Ƃ��낪���̋�̏ꏊ���𒲂ׂ�B
POS HitPos(int PosX, int PosY)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (HitClick(PosX, PosY, POPUP_X + POPDOWN_X * i, POPUP_Y + POPDOWN_Y * j) == true)
			{
				POS pos;
				pos.x = i;
				pos.y = j;

				return pos;
			}
		}
	}
	POS nullpos = {-1,-1};

	return nullpos;
}