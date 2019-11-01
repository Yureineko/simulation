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

void CheckMoveRange(Piece piece, Piece AllPiece[]);

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
	int MainMap[7][7] =
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

	//��ۑ��p
	//�����ŋ�̈ړ�������N���X�̏��������s��
	Piece piecetable[28];
	//MainMap����l���擾���A���̈ʒu�ł��̖�E�̏��𓾂�
	for (int i = 0, count = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			//0����Ȃ�(�����ɋ����)�ꍇ
			if (MainMap[i][j] >= 1)
			{
				//posX,posY�ɂ��ꂼ��l������
				piecetable[count].posX = j;
				piecetable[count].posY = i;
				//�}�b�v�i���o�[�����E����肷��
				piecetable[count].type = MainMap[i][j];
				//��������Ȃ�G��A���Ȃ玩�w�̋�Ƃ������ɐݒ肷��
				if (i < 4)
				{
					piecetable[count].MeorEne = false;
				}
				else
				{
					piecetable[count].MeorEne = true;
				}
				//��E�����ƂɈړ��ݒ�����Ă���(�N���X���\�肠��)
				//���m
				if (MainMap[i][j] == 1)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 1;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//�����m
				if (MainMap[i][j] == 2)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 0;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 3;
					piecetable[count].diald = 3;
					piecetable[count].diaru = 3;
					piecetable[count].diard = 3;
				}
				//�����
				if (MainMap[i][j] == 3)
				{
					piecetable[count].movelimit = 8;
					piecetable[count].spicialmoverange[0][0] = -2; piecetable[count].spicialmoverange[0][1] = 1;
					piecetable[count].spicialmoverange[1][0] = -2; piecetable[count].spicialmoverange[1][1] = -1;
					piecetable[count].spicialmoverange[2][0] = -1; piecetable[count].spicialmoverange[2][1] = 2;
					piecetable[count].spicialmoverange[3][0] = -1; piecetable[count].spicialmoverange[3][1] = -2;
					piecetable[count].spicialmoverange[4][0] = 1;  piecetable[count].spicialmoverange[4][1] = 2;
					piecetable[count].spicialmoverange[5][0] = 1;  piecetable[count].spicialmoverange[5][1] = -2;
					piecetable[count].spicialmoverange[6][0] = 2;  piecetable[count].spicialmoverange[6][1] = 1;
					piecetable[count].spicialmoverange[7][0] = 2;  piecetable[count].spicialmoverange[7][1] = -1;
					piecetable[count].moveleft = 0;
					piecetable[count].moveright = 0;
					piecetable[count].movefront = 0;
					piecetable[count].moveback = 0;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//�R�m
				if (MainMap[i][j] == 4)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 3;
					piecetable[count].moveright = 3;
					piecetable[count].movefront = 3;
					piecetable[count].moveback = 3;
					piecetable[count].dialu = 0;
					piecetable[count].diald = 0;
					piecetable[count].diaru = 0;
					piecetable[count].diard = 0;
				}
				//���w��
				if (MainMap[i][j] == 5)
				{
					piecetable[count].movelimit = 0;
					piecetable[count].moveleft = 1;
					piecetable[count].moveright = 1;
					piecetable[count].movefront = 1;
					piecetable[count].moveback = 1;
					piecetable[count].dialu = 1;
					piecetable[count].diald = 1;
					piecetable[count].diaru = 1;
					piecetable[count].diard = 1;
				}
				count++;
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
	bool saveclickflag;//�N���b�N�|�W�V�����擾�̐�����s���ׂ̃t���O
	bool clickflag;    //�N���b�N������s���ׂ̃t���O
	//������
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;
	clickflag = false;

	POS movePos = {0,0}; //������̃|�W�V����
	int movepiece = -1;  //��������̃i���o�[��ۑ����Ă����p
	bool moveflag = false;//���������I�Ԃ̂��A�����Ăق����ꏊ��I�Ԃ̂�

	int EKingX = 6, EKingY = 6;//�G�̉��̈ʒuX,Y


	//int King = LoadGraph("image\\King.png");
	Scenes scene = TITLE;
	
	t_chara = LoadGraph("image\\�L�����N�^�[C(��).png");
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

	
	
	bool turn=true;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)
	int Mx, My;//�}�E�X�̈ʒu




	bool win_flag = false;//���������̃t���O
	bool lose_flag = false;//���������̃t���O
	bool gameend_flag = false;//�Q�[���I������ۂɎg���t���O



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

	while (ProcessMessage() != -1)
	{
		switch (scene)
		{
		case TITLE:
			SetFontSize(16);
			DrawString(0, 32, "�^�C�g��(��)", GetColor(255, 255, 255));
			DrawString(0, 48, "�\���L�[��Ŏn�߂�", GetColor(255, 255, 255));
			DrawString(0, 64, "�\���L�[���ŏI���", GetColor(255, 255, 255));
			DrawString(0, 256, "�A���ăx���Z���A��肽��", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_UP))
			{
				scene = SELECT;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN))
			{
				gameend_flag = true;
				break;
			}
			break;

		case SELECT:
			//�������^�C�~���O
			DrawString(0, 48, "�\���L�[�E�Ŏn�߂�", GetColor(255, 255, 255));
			DrawString(0, 64, "�\���L�[���ŏI���", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				scene = GAME;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT))
			{
				gameend_flag = true;
				break;
			}
			break;

		case GAME:

			//�����ŃQ�[���̃��C�������\�z
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
		if (turn == true)
		{
			//�N���b�N�����Ƃ�
			if (clickflag == false && saveclickflag == true)
			{
				//�L������I�����ΐF�̃}�X(�s���ł���͈�)��`��
				if (moveflag == false)
				{
					//�N���b�N�����}�X���擾�����̃}�X�ɊY��������T��
					POS SavePos = HitPos(clickpos.posX, clickpos.posY);
					for (int i = 0; i < 28; i++)
					{
						//�Y����������A���̋�����Ă����
						if (SavePos.x == piecetable[i].posX && SavePos.y == piecetable[i].posY && piecetable[i].type != 0)
						{
							//���̋�̑Ή��i���o�[���ꎞ�ۑ�����
							movepiece = i;
							//�s���ꏊ��I�Ԃ悤�ɂ���
							moveflag = true;
							clickflag = true;
							//�ړ��ł���͈͂�ΐF�Ŏw�肷��
							CheckMoveRange(piecetable[i], piecetable);
						}
					}
				}
				//�ΐF�̃}�X��I������L�őI�񂾋�����̏ꏊ�Ɉړ�
				else
				{
					//�I�񂾃}�X���擾
					movePos = HitPos(clickpos.posX, clickpos.posY);
					//���̃}�X���͈͓�
					if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7 && CanMoveMap[movePos.y][movePos.x] == 1)
					{
						int latemove = -1;
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
								if (piecetable[latemove].type == 6)
									win_flag = true;
								if (piecetable[latemove].type == 5)
									lose_flag = true;
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

							turn = false;

							for (int i = 0; i < 7; i++)
							{
								for (int j = 0; j < 7; j++)
								{
									CanMoveMap[i][j] = 0;
								}
							}
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



			}


			//Z�L�[�������Ǝ�Ԃ������ɖ߂��B
			if (CheckHitKey(KEY_INPUT_Z))
			{
				turn = true;
			}
			
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
					DrawRotaGraph(piecetable[i].posX * 64 + 224, piecetable[i].posY * 64 + 32, 1.0f, PI, EKing, TRUE);
					break;
				}
				if (CanMoveMap[piecetable[i].posY][piecetable[i].posX] == 1)
				{
					//�΂̈ړ��͈͕`��
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, GreenFilter, TRUE);
				}
			}
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (CanMoveMap[i][j] == 1)
					{
						DrawGraphF(j * 64 + 192, i * 64, GreenFilter, TRUE);
					}
				}
			}




			if (win_flag == true)
			{
				SetFontSize(40);
				//LoadGraphScreen(64, 0, "image\\��.png", TRUE);
				DrawString(350, 250, "YOU WIN", GetColor(255, 0, 0));
				DrawString(250, 300, "�\���L�[�E�Ń^�C�g����", GetColor(255, 0, 0));
				DrawString(250, 350, "�\���L�[���ŏI��", GetColor(255, 0, 0));
			}
			else if (lose_flag == true)
			{
				SetFontSize(40);
				DrawString(350, 250, "YOU LOSE", GetColor(255, 0, 0));
				DrawString(250, 300, "�\���L�[�E�Ń^�C�g����", GetColor(255, 0, 0));
				DrawString(250, 350, "�\���L�[���ŏI��", GetColor(255, 0, 0));
			}

			if (CheckHitKey(KEY_INPUT_UP) && (win_flag == true || lose_flag == true))
			{
				scene = TITLE;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) && (win_flag == true || lose_flag == true))
			{
				gameend_flag = true;
				break;
			}
			//king->Draw();







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



			break;
		}

		ScreenFlip();//�摜�̃t���b�v(�؂�ւ�)
		ClearDrawScreen();//�摜�̃N���A

		if (gameend_flag == true)
		{
			break;
		}
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

//�s���͈͗̈攻��
void CheckMoveRange(Piece piece, Piece AllPiece[])
{
	//�O����
	for (int i = 1; i <= piece.movefront; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX && AllPiece[j].posY == piece.posY - i && AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0)
						CanMoveMap[piece.posY - i][piece.posX] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0)
				CanMoveMap[piece.posY - i][piece.posX] = 1;
		}
	}
	//��딻��
	for (int i = 1; i <= piece.moveback; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i <= 6)
						CanMoveMap[piece.posY + i][piece.posX] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i <= 6)
				CanMoveMap[piece.posY + i][piece.posX] = 1;
		}
	}
	//������
	for (int i = 1; i <= piece.moveleft; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posX - i >= 0)
						CanMoveMap[piece.posY][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posX - i >= 0)
				CanMoveMap[piece.posY][piece.posX - i] = 1;
		}
	}
	//�E����
	for (int i = 1; i <= piece.moveright; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posX + i <= 6)
						CanMoveMap[piece.posY][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posX + i <= 6)
				CanMoveMap[piece.posY][piece.posX + i] = 1;
		}
	}
	//���΂ߏ㔻��
	for (int i = 1; i <= piece.dialu; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY - i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0 && piece.posX - i >= 0)
						CanMoveMap[piece.posY - i][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0 && piece.posX - i >= 0)
				CanMoveMap[piece.posY - i][piece.posX - i] = 1;
		}
	}
	//���΂߉�����
	for (int i = 1; i <= piece.diald; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX - i && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + i <= 6 && piece.posX - i >= 0)
						CanMoveMap[piece.posY + i][piece.posX - i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY + i <= 6 && piece.posX - i >= 0)
				CanMoveMap[piece.posY + i][piece.posX - i] = 1;
		}
	}
	//�E�΂ߏ㔻��
	for (int i = 1; i <= piece.diaru; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY - i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY - i >= 0 && piece.posX + i <= 6)
						CanMoveMap[piece.posY - i][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY - i >= 0 && piece.posX + i <= 6)
				CanMoveMap[piece.posY - i][piece.posX + i] = 1;
		}
	}
	//�E�΂߉�����
	for (int i = 1; i <= piece.diard; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + i && AllPiece[j].posY == piece.posY + i&& AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + i <= 6 && piece.posX + i <= 6)
						CanMoveMap[piece.posY + i][piece.posX + i] = 1;
					breakflag = true;
				}
			}
		}

		if (breakflag == true)
		{
			break;
		}
		else
		{
			if (piece.posY + i <= 6 && piece.posX + i <= 6)
				CanMoveMap[piece.posY + i][piece.posX + i] = 1;
		}
	}
	//����ʒu�ړ�����
	for (int i = 0; i < piece.movelimit; i++)
	{
		bool breakflag = false;

		for (int j = 0; j < 28; j++)
		{
			if (AllPiece[j].posX == piece.posX + piece.spicialmoverange[i][0] && AllPiece[j].posY == piece.posY + piece.spicialmoverange[i][1] && AllPiece[j].type != 0)
			{
				if (AllPiece[j].MeorEne == piece.MeorEne)
				{
					breakflag = true;
				}
				else
				{
					if (piece.posY + piece.spicialmoverange[i][1] >= 0 && piece.posY + piece.spicialmoverange[i][1] <= 6 &&
						piece.posX + piece.spicialmoverange[i][0] >= 0 && piece.posX + piece.spicialmoverange[i][0] <= 6)
						CanMoveMap[piece.posY + piece.spicialmoverange[i][1]][piece.posX + piece.spicialmoverange[i][0]] = 1;
					breakflag = true;
				}
			}
		}
		if (breakflag == false)
		{
			if (piece.posY + piece.spicialmoverange[i][1] >= 0 && piece.posY + piece.spicialmoverange[i][1] <= 6 &&
				piece.posX + piece.spicialmoverange[i][0] >= 0 && piece.posX + piece.spicialmoverange[i][0] <= 6)
				CanMoveMap[piece.posY + piece.spicialmoverange[i][1]][piece.posX + piece.spicialmoverange[i][0]] = 1;
		}
	}
}