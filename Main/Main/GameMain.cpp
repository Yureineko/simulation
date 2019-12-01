#include "DxLib.h"
#include "Piece.h"
#include "Grobal.h"
#include<stdio.h>

#define SCREEN_PIXWIDTH		832//��ʃT�C�Y�@X
#define SCREEN_PIXHEIGHT	448//��ʃT�C�Y�@Y

//MainMap�͈̔�
#define POPUP_X 192//�����̓_
#define POPUP_Y 0//�E��
#define POPDOWN_X 64//
#define POPDOWN_Y 64

//�����̃L�����̔\�̓{�^���͈̔�
#define CLUP_X 40//���@�_
#define CLUP_Y 280//��@�_
#define CLDOWN_X 150//�E�@�_
#define CLDOWN_Y 380//���@�_


#define PI	3.1415926535897932384626433832795f

//�N���b�N�̗̈���`�F�b�N����֐�
bool HitClick(int Cx, int Cy, int x1, int y1);

bool CheckButton(Pos pushclick, Pos outclick, Pos button, int sizex, int sizey);

POS HitPos(int PosX, int PosY);//�ʒu���擾

POS ZeroPos(int ZposX, int ZposY);//�ʒu���擾

void CheckMoveRange(Piece piece, Piece AllPiece[]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	//IP�A�h���X�ݒ�p
	IPDATA Ip;
	//�ڑ��|�[�g
	int port = -1;
	//�l�b�g���[�N�n���h��
	int NetUDPHandle;

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
	
	//�o�b�N�O���E���h�̍Đ�
	SetAlwaysRunFlag(TRUE);

	//�����̏����l��123456�ɐݒ肷��
	SRand(123456);

	//�����ɔՏ��ݒ�
	//��̎�ނ͍ő�5���
	int MainMap[7][7] =
	{
		{ 2,3,4,6,4,3,2 },
		{ 1,1,1,1,1,1,1 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,7,0,0,0,0 },
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
	//7.��

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
	
	int title = LoadGraph("image\\�^�C�g�����(�����).png");//�^�C�g����ʓǂݍ���
	int textbox = LoadGraph("image\\hakkou1.png");//�e�L�X�g�{�b�N�X�̕\��
	int t_charaB;//���w�i(�v���C���[1)�̕\��	
	int t_charaB2;//���w�i(�v���C���[2)�̕\��
	int t_chara,t_charawin,t_charalose,t_charaskill;//���L�����N�^�[(�v���C���[1)�̕\���@1�̖�
	int t_chara2, t_chara2win, t_chara2lose, t_chara2skill;//���L�����N�^�[(�v���C���[2)�̕\���@2�̖�
	int t_chara3, t_chara3win, t_chara3lose, t_chara3skill;//���L�����N�^�[(�v���C���[3)�̕\���@3�̖�



	unsigned int DeadlyButton;//�L�����̕K�E�Z�̃{�^���̕\��
	DeadlyButton = GetColor(0, 0, 255);//�{�^���̐F���擾
	int Skillbotton = LoadGraph("image\\�\�͔����I�{�^��.png");//�\�͔����{�^����\��
	int Skillwaite = LoadGraph("image\\�\�͑ҋ@.png");//�\�͔����ҋ@�{�^����\��


	int Soldier=LoadGraph("image\\Soldier(64).png");//�����ɕ��m�̉摜
	int Sorcerer=LoadGraph("image\\Sorcerer(64).png");//�����ɖ����m�̉摜
	int Espionage =LoadGraph("image\\Espionage(64).png");//�����ɒ�����̉摜
	int Knight =LoadGraph("image\\Knight(64).png");//�����ɋR�m�̉摜
	int King =LoadGraph("image\\King(64).png");//�����ɉ��̉摜
	int EKing = LoadGraph("image\\King(64).png");//�����ɉ��̉摜

	//��ʍs�ł��Ȃ���
	//int wall;//�؂�������
	int Wall = LoadGraph("image\\King(��).png");//�����ɕK�E�Z(��)�̉摜�o�^
	//wall=DerivationGraph(0,0, 64, 64, Wall);//�ǂ̉摜�̐؂���



	int GreenFilter = LoadGraph("image\\greenfilter.png");//��̈ړ��͈͂̕`��
	int RedFilter = LoadGraph("image\\redfilter.png");//�ǂ̏o���͈͂̕`��


	//��U�����ňʒu�ړ�����B��ŏ��������B
	int SoldX = 1, SoldY = 1;//���m�̈ʒuX,Y
	int SorcX = 2, SorcY = 2;//�����m�̈ʒuX,Y
	int EspiX = 3, EspiY = 3;//������̈ʒuX,Y
	int KnightX = 4, KnightY = 4;//�R�m�̈ʒuX,Y
	int KingX = 5, KingY = 5;//���̈ʒuX,Y
	int WallX = 7, WallY = 7;//�ǂ̈ʒuX,Y
	//�L�����I��p�ϐ�
	int charaselect = 0;
	int enemychara = 0;

	//�{�^���Ǘ����W�p
	Pos clickpos;     //�N���b�N�ʒu�ۑ��p
	Pos outclickpos;  //�N���b�N�������ʒu�ۑ��p
	bool saveclickflag;//�N���b�N�|�W�V�����擾�̐�����s���ׂ̃t���O
	bool clickflag;    //�N���b�N������s���ׂ̃t���O

	//�ǂƒn���̔\�̓{�^��
	Pos skillpos;//�N���b�N�����\�̓{�^������
	Pos outskillpos;//�N���b�N�������\�̓{�^������
	bool saveskillflag;//�N���b�N�|�W�V�����擾�̐�����s���ׂ̃t���O �X�L��
	bool Sclickflag;    //�N���b�N������s���ׂ̃t���O

	//������
	clickpos.posX = -1;
	clickpos.posY = -1;
	outclickpos.posX = -1;
	outclickpos.posY = -1;
	saveclickflag = false;
	clickflag = false;

	//��
	skillpos.posX = -1;
	skillpos.posY = -1;
	outskillpos.posX = -1;
	outskillpos.posY = -1;
	saveskillflag = false;
	Sclickflag = false;


	bool skillclickflag;//�K�E�{�^�����N���b�N�����Ƃ��̃t���O
	skillclickflag = false;

	bool skillbuttonflag;//�X�L���̃{�^���̐���
	skillbuttonflag = false;
	
	bool skillflagremove;//�X�L���ҋ@����Ԃ�Map�ȊO���N���b�N�����Ƃ��̃t���O
	skillflagremove = false;


	bool skillredflag;//�ǂ̕\���\�t���O
	skillredflag = false;

	bool wallskill1;//�L����1�̕ǂ̕`��t���O
	wallskill1 = false;

	POS movePos = {0,0}; //������̃|�W�V����
	POS wallPos = { 0,0 };//�ǂ�\���o����ꏊ

	int movepiece = -1;  //��������̃i���o�[��ۑ����Ă����p
	bool moveflag = false;//���������I�Ԃ̂��A�����Ăق����ꏊ��I�Ԃ̂�


	int appearanceWall = -1;//�o��
	bool appearanceflag = false;//�o������ꏊ��I��

	int EKingX = 6, EKingY = 6;//�G�̉��̈ʒuX,Y


	//int King = LoadGraph("image\\King.png");
	Scenes scene = TITLE;
	
	t_charaB = LoadGraph("image\\�L�����w�i���1.png");
	t_charaB2 = LoadGraph("image\\�L�����w�i���3.png");	

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
	
	
	bool turn=true;//�^�[���ϐ�....0:�����̃^�[���@1:����̃^�[��
	int movepointX;//��̈ړ��̕ϐ�(MainMap�ƏƂ炵���킹�Ďg�p����B)
	int mx, my;//�}�E�X�̈ʒu
	int Mx, My;

	bool win_flag = false;//���������̃t���O
	bool lose_flag = false;//���������̃t���O
	bool gameend_flag = false;//�Q�[���I������ۂɎg���t���O
	bool time = false;//�^�C�����O�����p�t���O

	unsigned int cr;//�ӂ�͈͂̕`���


	//---------�}�E�X����̕ϐ�--------
	 //GetMousePoint(&Mx,&My);//�}�E�X�̌��݈ʒu�擾

	//�}�E�X��window��ɕ\��������B
	//SetMouseDispFlag(TRUE);

	//�o�b�N�o�b�t�@�ɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	int cx, cy;
	bool Click_flag = 0;

	Ip.d1 = 172;
	Ip.d2 = 17;
	Ip.d3 = 60;
	Ip.d4 = 122;

	NetUDPHandle = MakeUDPSocket(99);

	char RecvData[10] = {0};
	char SendData[10] = {0};
	int UserNum = -1;
	int connecttime = 0;

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
			//���s�E�^�[���t���O������
			saveclickflag = false;
			clickflag = false;
			win_flag = false;//���������̃t���O
			lose_flag = false;//���������̃t���O
			turn = true;
			time = false;

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

			//��ۑ��p
			//�����ŋ�̈ړ�������N���X�̏��������s��
			Piece piecetable[28];

			//�Ǖۑ��p
			Walls wall[49];
			//MainMap����l���擾���A���̈ʒu�ł��̖�E�̏��𓾂�
			for (int i = 0, count = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					

					//0����Ȃ�(�����ɋ����)�ꍇ
					if (MainMap[i][j] >= 1 && MainMap[i][j] <= 6)
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
						//�ړ�
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
						//��
						if (MainMap[i][j] == 7)
						{
							piecetable[count].movelimit = 0;
							piecetable[count].moveleft = 0;
							piecetable[count].moveright = 0;
							piecetable[count].movefront = 0;
							piecetable[count].moveback = 0;
							piecetable[count].dialu = 0;
							piecetable[count].diald = 0;
							piecetable[count].diaru = 0;
							piecetable[count].diard = 0;
						}

						////�����ɋ�Ȃ��ꍇ
						//if (MainMap[i][j] == 0)
						//{
						//	//�ǂ̏��ɂ��ꂼ��̒l������
						//	wall[count].posx = j;
						//	wall[count].posy = i;

						//	//�����̕��ł���
						//	count++;
						//}
						count++;
					}
				}
			}

			SetFontSize(16);
			DrawExtendGraphF(-50, -50, 882, 498, title, TRUE);//�^�C�g���̕`��
			DrawExtendGraphF(300, 200, 500, 250, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��
			DrawExtendGraphF(300, 300, 500, 350, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��
			DrawString(0, 32, "�^�C�g��(��)", GetColor(255, 255, 255));
			DrawString(375, 215, "�n�߂�", GetColor(255, 255, 255));
			DrawString(375, 315, "�I���", GetColor(255, 255, 255));

			if (saveclickflag == true)
			{
				if (clickflag == false)
				{
					if (300 <= clickpos.posX&&clickpos.posX <= 500 && 200 <= clickpos.posY&&clickpos.posY <= 250)
					{
						SendData[0] = 1;
						NetWorkSendUDP(NetUDPHandle, Ip, 30, SendData, sizeof(SendData));
						scene = CONNECT;
					}
					else if (300 <= clickpos.posX&&clickpos.posX <= 500 && 300 <= clickpos.posY&&clickpos.posY <= 350)
					{
						gameend_flag = true;
					}
				}
			}
			break;

		case CONNECT:

			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
			}

			if (RecvData[0] >= 1)
			{
				if (RecvData[0] == 1)
				{
					DrawString(0, 32, "�ΐ푊���W��...", GetColor(255, 255, 255));
					connecttime = 0;
				}
				else
				{
					DrawString(0, 32, "�ڑ��m�F��...", GetColor(255, 255, 255));
					connecttime++;
				}
			}
			else
			{
				DrawString(0, 32, "�T�[�o�[�ڑ��ɂႤ...", GetColor(255, 255, 255));
			}

			if (connecttime == 60)
			{
				connecttime = 0;
				scene = SELECT;
			}
			break;

		case SELECT:
			//������
			GetMousePoint(&Mx, &My);//�J�[�\���̌��݈ʒu���擾
			clickpos.posX = -1;
			clickpos.posY = -1;
			outclickpos.posX = -1;
			outclickpos.posY = -1;
			t_chara = LoadGraph("image\\�L�����N�^�[1\\�L�����N�^�[1���T�C�Y����.png");
			t_chara2 = LoadGraph("image\\�L�����N�^�[2\\�L�����N�^�[2���C��.png");
			t_chara3 = LoadGraph("image\\�L�����N�^�[3\\�L�����N�^�[3�����G.png");			

			//�������^�C�~���O
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
			DrawExtendGraphF(0, 50, 416, 498, t_charaB, TRUE);//�v���C���[1�̔w�i�̕`��
			DrawGraph(115, 50, t_chara, TRUE);//�v���C���[1�̕`��
			DrawExtendGraphF(0, 183, 416, 631, t_charaB2, TRUE);//�v���C���[2�̔w�i�̕`��
			DrawGraph(115, 183, t_chara2, TRUE);//�v���C���[2�̕`��
			DrawExtendGraphF(0, 316, 416, 764, t_charaB, TRUE);//�v���C���[3�̔w�i�̕`��
			DrawGraph(115, 316, t_chara3, TRUE);//�v���C���[3�̕`��

			DrawGraph(0, 0, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��
			DrawExtendGraphF(416, 50, 832, 448, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��

			if (charaselect == 0)
			{
				DrawString(32, 16, "�L������I�����Ă�������", GetColor(255, 255, 255));
			}
			else
			{
				DrawString(32, 16, "����L�����I��..", GetColor(255, 255, 255));
			}


			if (0 <= Mx && Mx <= 416 && 50 <= My && My <= 183)
			{
				DrawString(480, 180, "�t�F���X�E�I�u�E�K�C�A", GetColor(255, 255, 255));
				DrawString(480, 250, "�C�ӂ̃}�X�𒆐S��", GetColor(255, 255, 255));
				DrawString(480, 266, "���j�b�g���N���ł��Ȃ�", GetColor(255, 255, 255));
				DrawString(480, 282, "�c��1�񉡂�3��̖h�ǂ�ݒu����", GetColor(255, 255, 255));
			}
			else if (0 <= Mx && Mx <= 416 && 183 < My && My <= 316)
			{
				DrawString(480, 180, "�}�C���E�I�u�E�t�@�C�A", GetColor(255, 255, 255));
				DrawString(480, 250, "�C�ӂ̃}�X�ɑ��肩��͌����Ȃ�", GetColor(255, 255, 255));
				DrawString(480, 266, "�n����ݒu����", GetColor(255, 255, 255));
				DrawString(480, 282, "�n���𓥂񂾃��j�b�g�͑����ɑޏꂷ��", GetColor(255, 255, 255));
			}
			else if (0 <= Mx && Mx <= 416 && My > 316)
			{
				DrawString(480, 180, "�G�^�[�i���t�H�[�X�u���U�[�h", GetColor(255, 255, 255));
				DrawString(480, 250, "����v���C���[�͎���", GetColor(255, 255, 255));
			}

			if (saveclickflag == true)
			{
				if (clickflag == false)
				{
					if (charaselect == 0)
					{
						if (clickpos.posX <= 416 && 50 <= clickpos.posY&&clickpos.posY <= 183)
						{
							charaselect = 1;
							clickflag = true;
						}
						else if (clickpos.posX <= 416 && 183 < clickpos.posY&&clickpos.posY <= 316)
						{
							charaselect = 2;
							clickflag = true;
						}
						else if (clickpos.posX <= 416 && clickpos.posY > 316)
						{
							charaselect = 3;
							clickflag = true;
						}
					}
				}
				else
				{
					clickflag = false;
				}
			}

			//�ʐM�m�F�p
			if (UserNum != -1)
			{
				SendData[0] = 1;
				SendData[1] = charaselect;
				NetWorkSendUDP(NetUDPHandle, Ip, UserNum, SendData, sizeof(SendData));
			}

			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
				if (RecvData[0] != 0)
				{
					enemychara = RecvData[1];
					if (charaselect != 0 && enemychara != 0)
					{
						scene = GAME;
					}
					connecttime = 0;
				}
				else
				{
					connecttime++;
					if (connecttime == 60)
					{
						//�ΐ푊�肪���������ߐڑ��ɖ߂�
						//�������͔C����
						scene = CONNECT;
					}
				}
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
								//�}�X�ɐG��鏊
								CheckMoveRange(piecetable[i], piecetable);
							}
						}
					}
					//�ΐF�̃}�X��I������L�őI�񂾋�����̏ꏊ�Ɉړ�
					else
					{
						//�I�񂾃}�X���擾
						movePos = HitPos(clickpos.posX, clickpos.posY);
						//�f�[�^����p�ۑ�
						SendData[2] = 6 - piecetable[movepiece].posX;
						SendData[3] = 6 - piecetable[movepiece].posY;
						//���̃}�X���͈͓�
						//�N���b�N�����ꏊ�Ƌ�̈ʒu�������Ă����
						if (clickpos.posX >= POPUP_X && clickpos.posX <= POPUP_X + 64 * 7 && CanMoveMap[movePos.y][movePos.x] == 1)
						{
							int latemove = -1;//��̔z��ԍ��̕ۑ�
							for (int i = 0; i < 28; i++)
							{
								if (movePos.x == piecetable[i].posX && movePos.y == piecetable[i].posY && i != movepiece)
								{
									latemove = i;
								}
							}
							if (latemove != -1)
							{//��m���d�Ȃ����Ƃ��̏���
								if (piecetable[movepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
								{
									piecetable[movepiece].posX = movePos.x;
									piecetable[movepiece].posY = movePos.y;
									if (piecetable[latemove].type == 6)//����̉���������珟���̃t���O��true��
										win_flag = true;
									if (piecetable[latemove].type == 5)//�����̉������ꂽ�畉���̃t���O��true��
										lose_flag = true;
									//if (piecetable[latemove].type == 7)//�ǂɂ͒ʂ�Ȃ�������B
									//	movepiece = -1;

									piecetable[latemove].type = 0;//�����Ȃ��ꏊ�ɂ͋�
									movepiece = -1;//�ړ��O�̋�͔�\����

									//�f�[�^����p�ۑ�
									SendData[4] = 6 - piecetable[latemove].posX;
									SendData[5] = 6 - piecetable[latemove].posY;
								}
								//�ړ��悪�ǂȂ�i�߂Ȃ�
								//else if(piecetable[])
							}
							//�d�Ȃ�Ȃ������Ƃ�
							else
							{
								piecetable[movepiece].posX = movePos.x;
								piecetable[movepiece].posY = movePos.y;
								movepiece = -1;
							}
							clickflag = true;
							moveflag = false;

							turn = false;
							//�N���b�N������̗Δ͈͂�����
							for (int i = 0; i < 7; i++)
							{
								for (int j = 0; j < 7; j++)
								{
									CanMoveMap[i][j] = 0;

									DwallMap[i][j]=0;
									
								}
							}
							
						}
					}
				}
				else if (saveclickflag == false)
				{
					clickflag = false;
				}



				GetMousePoint(&mx, &my);

				//---------------�ǂ̐�������----------------------------------
				//�L�����̕K�E�{�^�����N���b�N�����Ƃ�


				int Mouse;//�N���b�N�����Ƃ��̐�������邽�߂̕ϐ�
				//�K�E�Z�̉ӏ��Ƀ}�E�X������Ƃ�
				//�{�^���̗̈���ł���
				if (mx <CLDOWN_X&&mx>CLUP_X&&my<CLDOWN_Y&&my>CLUP_Y)
				{
					//�}�E�X�̍��N���b�N�������
					if (GetMouseInput()&MOUSE_INPUT_LEFT)
					{
						//�����đ�����rigit�̕���0�Ƀ��Z�b�g����
						if (Mouse > 0)
						{
							Mouse = -1;
						}
						else//�����ĂȂ���Α����Ȃ�
						{
							Mouse = 0;

						}
					}
					else
					{
						//������Ă���
						Mouse++;
					}

					if (Mouse == 1) 
					{
						if (skillclickflag == false && skillflagremove == false)
						{
							//�X�L���ҋ@���̃{�^���ƃL������`�悷��flag��true��
							skillclickflag = true;
							skillflagremove = false;

							PlaySoundMem(se, DX_PLAYTYPE_BACK);
						}
					}

					//������x
					//�E�N���b�N������Ɣ\�͔����{�^���ɖ߂�
					if (Mouse == 1)
					{
						if (skillbuttonflag==true)
						{
							skillclickflag = false;
							skillflagremove = true;
							//PlaySoundMem(se, DX_PLAYTYPE_BACK);
						}
					}
					//�Ԃ��͈͂��N���b�N�����
					if (Mouse==1&&wallskill1 == true)
					{
						//�N���b�N�����Ƃ�
						//�L������I�����ΐF�̃}�X(�s���ł���͈�)��`��
						if (appearanceflag == false)
						{
							//�N���b�N�����}�X���擾�����̃}�X�ɊY��������T��
							POS WallPos = ZeroPos(clickpos.posX, clickpos.posY);
							for (int i = 0; i < 49; i++)
							{
								//�Y����������A���̋�����Ă����
								if (WallPos.x == wall[i].posx && WallPos.y == wall[i].posy && wall[i].type == 0)
								{
									//���̋�̑Ή��i���o�[���ꎞ�ۑ�����
									appearanceWall = i;
									//�s���ꏊ��I�Ԃ悤�ɂ���
									appearanceflag = true;
									clickflag = true;
									//�o���ł���͈͂�ԐF�Ŏw�肷��
									//CheckMoveRange(wall[i], wall);
								}
							}
						}


					}



					//������MainMap���X�V
					for (int i = 0; i < 7; i++)
					{
						for (int j = 0; j < 7; j++)
						{
							DwallMap[i][j] = 0;
						}
					}
					

				}
				

				//-----------��������Ԃ��͈͂̏���-------------
				//�Ԃ��}�X
				if (skillredflag == true)
				{
					//MainMap��0�̕�����T��


				}
			}
			else
			{
				
			}
	
		//Z�L�[�������Ǝ�Ԃ������ɖ߂��B
		if (CheckHitKey(KEY_INPUT_Z))
		{
			turn = true;
		}

	
		cr = GetColor(0, 255, 0);//�ΐF���擾
		
			//�w�i�̉摜�\��	
			LoadGraphScreen(0, 0, "image\\BackGround.png", TRUE);
			DrawGraph(0, 0, t_charaB, TRUE);//�v���C���[1�̔w�i�̕`��
			DrawGraph(640, 0, t_charaB2, TRUE);//�v���C���[2�̔w�i�̕`��

			if (charaselect == 1)
			{
				DrawGraph(0, 0, t_chara, TRUE);//�v���C���[1�̕`��
			}
			else if (charaselect == 2)
			{
				DrawGraph(0, 0, t_chara2, TRUE);//�v���C���[1�̕`��
			}
			else if (charaselect == 3)
			{
				DrawGraph(0, 0, t_chara3, TRUE);//�v���C���[1�̕`��
			}
			if (enemychara == 1)
			{
				DrawGraph(640, 0, t_chara, TRUE);//�v���C���[2�̕`��
			}
			else if (enemychara == 2)
			{
				DrawGraph(640, 0, t_chara2, TRUE);//�v���C���[2�̕`��
			}
			else if (enemychara == 3)
			{
				DrawGraph(640, 0, t_chara3, TRUE);//�v���C���[2�̕`��
			}
			
			DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//�\�͔����{�^���̕`��
			//��̕`��ЂƂ�����
			//��2�s�Ɖ�2�s
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

				case 7:
					//�ǂ̐���
					DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, Wall, TRUE);
					break;
				}
				//�N���b�N�����Ƃ��̗΂̕`��
				//if (CanMoveMap[piecetable[i].posY][piecetable[i].posX] == 1)
				//{
				//	//�΂̈ړ��͈͕`��
				//	DrawGraphF(piecetable[i].posX * 64 + 192, piecetable[i].posY * 64, GreenFilter, TRUE);
				//}
				
			}
			//�΂͈͕̔`��
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

		
			
			/*if (DwallMap[i][j] == 1)
			{
				DrawGraphF(j * 64 + 192, i * 64, RedFilter, TRUE);
			}*/
	//-------------�\�̓{�^���`��---------
			//�\�̓{�^���̏ꏊ��ҋ@���ɂ���
			if (skillclickflag == true&&skillflagremove==false)
			{
				//���ꂼ��̃L�����̕`��Ɣ\�͓��e����
				//�L����1�̏ꍇ
				if (charaselect == 1)
				{
					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//�\�͑ҋ@���̕`��
					t_chara = LoadGraph("image\\�L�����N�^�[1\\�L�����N�^�[1�X�L������.PNG");//�X�L���ҋ@���̃L����1
					skillbuttonflag = true;
					//��ʂ�Ȃ��ǂ����(������)
					//�Ԃ��͈͂�`�悷��
					//MainMap�̒��ɂ���0�̏ꏊ��T��
					for (int x=0; x < 7; x++)
					{
						for (int y=0; y < 7; y++)
						{
							//�`�悵�Ă���A�܂��͂������Map����
							if (DwallMap[x][y]==1)
							{

							//�Ԃ��͈͂�`�悷��
							DrawGraphF(y * 64 + 192, x* 64, RedFilter, TRUE);
							wallskill1 = true;
							}
						}
					}
				}
				//�L����2�̏ꍇ
				else if (charaselect == 2)
				{
					//�G�Ɍ����Ȃ��n����ݒ肷��

					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//�\�͑ҋ@���̕`��
					t_chara2 = LoadGraph("image\\�L�����N�^�[2\\�L�����N�^�[2�X�L��.PNG");//�X�L���ҋ@���̃L����2
					skillbuttonflag = true;
					for (int x = 0; x < 7; x++)
					{
						for (int y = 0; y < 7; y++)
						{
							if (MainMap[x][y] == 0)
							{

								//�Ԃ��͈͂�`�悷��
								DrawGraphF(y * 64 + 192, x * 64, RedFilter, TRUE);

							}
						}
					}



				}
				//�L����3�̏ꍇ
				else if (charaselect == 3)
				{

					//��ʂ�Ȃ��ǂ����(�c����)

					DrawExtendGraphF(0, 230, 200, 430, Skillwaite, TRUE);//�\�͑ҋ@���̕`��
					t_chara3 = LoadGraph("image\\�L�����N�^�[3\\�L�����N�^�[3�X�L��.PNG");//�X�L���ҋ@���̃L����3
					skillbuttonflag = true;

					//MainMap�̒��ɂ���0�̏ꏊ��T��
					for (int x = 0; x < 7; x++)
					{
						for (int y = 0; y < 7; y++)
						{
							if (MainMap[x][y] == 0)
							{

								//�Ԃ��͈͂�`�悷��
								DrawGraphF(y * 64 + 192, x * 64, RedFilter, TRUE);

							}
						}
					}


				}
			}
			//�ҋ@���ɍēx�{�^�����N���b�N����Ɣ\�͔����\��Ԃɖ߂�
			else
			{
				if (skillbuttonflag == true)
				{
					if (charaselect == 1)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//�\�͔����{�^���̕`��
						t_chara = LoadGraph("image\\�L�����N�^�[1\\�L�����N�^�[1���T�C�Y����.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;
					}
					else if (charaselect == 2)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//�\�͔����{�^���̕`��
						t_chara2 = LoadGraph("image\\�L�����N�^�[2\\�L�����N�^�[2���C��.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;
					}
					else if (charaselect == 3)
					{
						DrawExtendGraphF(40, 280, 150, 380, Skillbotton, TRUE);//�\�͔����{�^���̕`��
						t_chara3 = LoadGraph("image\\�L�����N�^�[3\\�L�����N�^�[3�����G.png");
						skillclickflag = false;
						skillflagremove = false;
						skillbuttonflag = false;

					}
				}
			}

			//�f�[�^�󂯎��
			//�ʐM�m�F�p
			if (UserNum != -1)
			{
				SendData[0] = 1;
				SendData[1] = charaselect;
				NetWorkSendUDP(NetUDPHandle, Ip, UserNum, SendData, sizeof(SendData));
				for (int i = 0; i < 10; i++)
					SendData[i] = 0;
			}

			//�f�[�^��M����
			if (CheckNetWorkRecvUDP(NetUDPHandle) == TRUE)
			{
				NetWorkRecvUDP(NetUDPHandle, &Ip, &UserNum, RecvData, sizeof(RecvData), FALSE);
				if (RecvData[0] != 0)
				{
					if (turn == false && (RecvData[2] + RecvData[3] + RecvData[4] + RecvData[5]) != 0)
					{
						int movebepiece = -1;
						int latemove = -1;//��̔z��ԍ��̕ۑ�
						for (int i = 0; i < 28; i++)
						{
							if (RecvData[2] == piecetable[i].posX && RecvData[3] == piecetable[i].posY)
							{
								movebepiece = i;
							}
							if (RecvData[4] == piecetable[i].posX && RecvData[5] == piecetable[i].posY)
							{
								latemove = i;
							}
						}
						if (latemove != -1)
						{//��m���d�Ȃ����Ƃ��̏���
							if (piecetable[movebepiece].MeorEne != piecetable[latemove].MeorEne || piecetable[latemove].type == 0)
							{
								piecetable[movebepiece].posX = movePos.x;
								piecetable[movebepiece].posY = movePos.y;
								if (piecetable[latemove].type == 6)//����̉���������珟���̃t���O��true��
									win_flag = true;
								if (piecetable[latemove].type == 5)//�����̉������ꂽ�畉���̃t���O��true��
									lose_flag = true;
								//if (piecetable[latemove].type == 7)//�ǂɂ͒ʂ�Ȃ�������B
								//	movepiece = -1;

								piecetable[latemove].type = 0;//�����Ȃ��ꏊ�ɂ͋�
								movepiece = -1;//�ړ��O�̋�͔�\����
							}
							//�ړ��悪�ǂȂ�i�߂Ȃ�
							//else if(piecetable[])
						}
						//�d�Ȃ�Ȃ������Ƃ�
						else
						{
							piecetable[movebepiece].posX = movePos.x;
							piecetable[movebepiece].posY = movePos.y;
							movepiece = -1;
						}

						turn = true;

					}
					connecttime = 0;
				}
				else
				{
					connecttime++;
					if (connecttime == 60)
					{
						//�ΐ푊�肪���������ߐڑ��ɖ߂�
						//�������͔C����
						scene = CONNECT;
					}
				}
			}

			if (win_flag == true)
			{
				scene = GAMEEND;
			}
			else if (lose_flag == true)
			{
				scene = GAMEEND;
			}
			break;


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

			
			case GAMEEND:
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

				//������������ʕ\��
				if (win_flag == true)
				{
					if (time == false)
					{
						WaitTimer(500);
					}
					time = true;

					SetFontSize(40);

					DrawGraph(0, 0, t_charaB, TRUE);//�v���C���[1�̔w�i�̕`��
					DrawGraph(640, 0, t_charaB2, TRUE);//�v���C���[2�̔w�i�̕`��
					DrawExtendGraphF(194, 398, 416, 448, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��
					DrawExtendGraphF(417, 398, 639, 448, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��

					DrawString(340, 50, "YOU WIN", GetColor(255, 0, 0));
					DrawString(200, 403, "�^�C�g����", GetColor(255, 0, 0));
					DrawString(490, 403, "�I��", GetColor(255, 0, 0));

					if (charaselect == 1)
					{
						t_chara = LoadGraph("image\\�L�����N�^�[1\\�L�����N�^�[1��������.png");
						t_chara2 = LoadGraph("image\\�L�����N�^�[2\\�L�����N�^�[2�s�k.png");
						DrawGraph(0, 0, t_chara, TRUE);//�v���C���[1�̕`��
						DrawGraph(640, 0, t_chara2, TRUE);//�v���C���[2�̕`��
						skillredflag = true;
					}
					if (charaselect == 2)
					{
						t_chara2 = LoadGraph("image\\�L�����N�^�[2\\�L�����N�^�[2����.png");
						t_chara3 = LoadGraph("image\\�L�����N�^�[3\\�L�����N�^�[3�s�k.png");
						DrawGraph(0, 0, t_chara2, TRUE);//�v���C���[1�̕`��
						DrawGraph(640, 0, t_chara3, TRUE);//�v���C���[2�̕`��
						skillredflag = true;
					}
					if (charaselect == 3)
					{
						t_chara = LoadGraph("image\\�L�����N�^�[1\\�L�����N�^�[1�s�k����.png");
						t_chara3 = LoadGraph("image\\�L�����N�^�[3\\�L�����N�^�[3����.png");
						DrawGraph(0, 0, t_chara3, TRUE);//�v���C���[1�̕`��
						DrawGraph(640, 0, t_chara, TRUE);//�v���C���[2�̕`��
						skillredflag = true;
					}
					
					if (saveclickflag == true)
					{
						if (clickflag == false)
						{
							if (194 <= clickpos.posX && clickpos.posX <= 416 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								scene = TITLE;
								clickflag = true;
							}
							else if (417 <= clickpos.posX && clickpos.posX <= 639 && 398 <= clickpos.posY && clickpos.posY <= 448)
							{
								gameend_flag = true;
								clickflag = true;
							}
						}
						else
						{
							clickflag = false;
						}
					}
					break;
				}
				//�s�k���s�k��ʕ\��
				else if (lose_flag == true)
				{
					WaitTimer(500);

					SetFontSize(40);
					DrawExtendGraphF(200, 200, 500, 300, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��
					DrawExtendGraphF(200, 350, 500, 450, textbox, TRUE);//�e�L�X�g�{�b�N�X�̕`��

					DrawString(330, 50, "YOU WIN", GetColor(255, 0, 0));
					DrawString(250, 250, "�^�C�g����", GetColor(255, 0, 0));
					DrawString(250, 400, "�I��", GetColor(255, 0, 0));
				}

				if (CheckHitKey(KEY_INPUT_RIGHT) && (win_flag == true || lose_flag == true))
				{
					scene = TITLE;
					break;
				}
				else if (CheckHitKey(KEY_INPUT_LEFT) && (win_flag == true || lose_flag == true))
				{
					gameend_flag = true;
					break;
				}
			break;
		}


		ScreenFlip();//�摜�̃t���b�v(�؂�ւ�)
		ClearDrawScreen();//�摜�̃N���A
		//�Q�[�����I���
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

//�\�̓{�^�����������Ƃ�0�̏ꏊ�𒲂ׂ�
POS ZeroPos(int ZposX, int ZposY)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (HitClick(ZposX, ZposY, POPUP_X + POPDOWN_X * i, POPUP_Y + POPDOWN_Y * j) == 0)
			{
				//�����ŕǂ̏o���ʒu��Ԃ�
				POS pos;
				pos.x = i;
				pos.y = j;

				return pos;
			}
		}
	}
	POS nullpos = { -1,-1 };

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