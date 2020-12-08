#include "DxLib.h"
#include"Color_Chain_Shooting.h"
#include"Player1ModeSystemData.h"

#define MAXENEMY 70
#define MAXMAPX 500
#define MAXMAPY 395 
#define AFTERGAMEOVERCOUNT 300

#define NEXTKEYTIME1 60

/////---**1Player mode**---/////

/*�X�e�[�W���߂̍ۂ̓G�o���p�֐�*/
void NormalStage_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	int i, j;
	int enemyxnum = 0, enemyynum = 0;//���ɕ��ԑ����A�c�ɕ��ԑ���
	int Enemypx[MAXENEMY] = {}, Enemypy[MAXENEMY] = {};//�G�@�̍��W�w��
	int Enemykindr[MAXENEMY] = {};//�G�@�̎��
	int startx;//�G��x�̒[�̍��W
	int stageenkind = 0;//�X�e�[�W�ɂ��G�@�̎�ސ�
	/*�X�e�[�W���̓G��*/
	switch (stage) {
	case 1:
		enemyxnum = 8;
		enemyynum = 2;
		startx = 90;
		stageenkind = 5;
		break;
	case 2:
		enemyxnum = 10;
		enemyynum = 2;
		startx = 50;
		stageenkind = 5;
		break;
	case 4:
		enemyxnum = 10;
		enemyynum = 3;
		startx = 50;
		stageenkind = 6;
		break;
	case 5:
		enemyxnum = 12;
		enemyynum = 3;
		startx = 10;
		stageenkind = 6;
		break;
	case 7:
		enemyxnum = 10;
		enemyynum = 4;
		startx = 50;
		stageenkind = 7;
		break;
	case 8:
		enemyxnum = 12;
		enemyynum = 4;
		startx = 10;
		stageenkind = 7;
		break;
	case 10:
		enemyxnum = 12;
		enemyynum = 5;
		startx = 10;
		stageenkind = 7;
		break;
	default://stage3,6,9,11�̓{�X
		return;
	}

	for (i = 0; i < enemyynum; i++) {
		for (j = 0; j < enemyxnum; j++) {
			Enemypx[i*enemyxnum + j] = startx + j * 40;
			Enemypy[i*enemyxnum + j] = 10 + i * 40;
			Enemykindr[i*enemyxnum + j] = GetRand(stageenkind);//0�`5,6,7�܂ł̗������擾
		}
	}

	for (i = 0; i < enemyxnum*enemyynum; i++) {
		Enemy[i].AppearEnemy(Enemypx[i], Enemypy[i], Enemykindr[i]);
	}//�o������

}//�X�e�[�W���߂̏���(�m�[�}���X�e�[�W�̂�)

/*�X�e�[�W�N���A���*/
unsigned int StageClear(int *ErrorCheck,int stage, unsigned int point, Mode1Player Player, int gameflag, int gamecount,int gamemode,int itemnum) {
	//�F�쐬
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//��
	Cr[1] = GetColor(15, 15, 255);//��
	Cr[2] = GetColor(255, 255, 15);//��
	Cr[3] = GetColor(15, 255, 15);//��
	Cr[4] = GetColor(255, 156, 0);//��
	Cr[5] = GetColor(159, 15, 255);//��
	Cr[6] = GetColor(218, 0, 224);//�Ԏ�
	Cr[7] = GetColor(76, 255, 255);//��
	Cr[8] = GetColor(240, 240, 240);//��
	Cr[9] = GetColor(128, 128, 128);//�D

	int ComboNum[3] = {};
	Player.PlayerShotCombo(ComboNum);
	int truepoints = 0, a = 1, b = 0, c = 0;
	int times;
	bool KeyCheck = true, QEndflag = false;
	a = Player.GetPoint();

	if (gameflag < 10) {//�ʏ탂�[�h
		if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {//�{�X�X�e�[�W
			b += 5 * stage*(itemnum + 1);
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (ComboNum[i] == 0) {
					b += 5 * stage;
				}
				else {
					b += (ComboNum[i] - 1) * (ComboNum[i] + stage);
				}
			}
		}
		b += itemnum * 50;
		c = Player.PlayerHP(0) * 5 * gamemode;
		if (Player.PlayerHP(0) == 30) {//HP�ő�ŃN���A
			c += 50;
		}
		times = gamemode * 2 + stage + 5;
		a = a * times / 5;
		if (gamemode == 3) {
			a *= 1.5;
		}
		else if (gamemode == 4) {
			a *= 2;
		}

		if (a > 999999999 || (Player.GetPoint() > 10000 && a < 10000))a = 999999999;//�I�[�o�[�t���[���G���[�h�~
		if (Player.GetPoint() >= 999999999)a = 999999999;//�I�[�o�[�t���[�G���[�h�~
		if (stage == 3 || stage == 6 || stage == 9) {
			a *= 0.75;//�{�X�̔{�����߂ɂ���
		}

		if (gameflag == 3) {//GameOver
			b = 0;
			c = 0;
		}//�{�[�i�X�_�Ȃ�

		b += Player.TotalComboNum()*gamemode;//2�ȏ�̃R���{�B����*��Փx�{�[�i�X�����Z

		/*�{�[�i�X�_�ϓ�*/
		if (gamemode == 1) {//EASY
			b *= 0.75;
			c *= 0.375;
		}
		else if (gamemode == 3) {//HARD
			b *= 1.5;
			c *= 2;
		}
		else if (gamemode == 4) {//UNKNOWN
			b *= 3;
			c *= 5;
		}
		
		b *= 0.5;//�����p
		c *= 0.5;//�����p
		truepoints = a + b + c;//���v���_(�ŏI�I�ȃX�e�[�W���_)
		if (truepoints > 999999999)truepoints = 999999999;//�I�[�o�[�t���[�G���[�h�~
		if (point > 1000000000) {//�I�[�o�[�t���[�G���[�h�~
			unsigned int pointtmp = point;
			point += truepoints;
			if (pointtmp > point) {//�I�[�o�[�t���[����
				point = UINT_MAX;
			}
		}
		else {
			point += truepoints;
		}
		
	}

	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/result.mp3");
	if (SHandle == -1) {
		SHandle = LoadSoundMem("./package/bgm/result.mp3");//�ēǂݍ���
	}
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
	

	do {
		ClearDrawScreen(); // ��ʂ�����
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		if (CheckHitKeyAll() == 0) {
			KeyCheck = false;
		}

		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
			KeyCheck = true;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);
			return -1;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);
			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}

		if ((CheckHitKey(KEY_INPUT_SPACE) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && KeyCheck == false) {
			break;
		}

		if (CheckHitKey(KEY_INPUT_Q) == 1 && gamemode < 10 && KeyCheck == false) {
			if (QEndflag == false) {
				QEndflag = true;
				KeyCheck = true;
			}
			else {
				*ErrorCheck = -2;
				break;
			}
		}


		if (gamemode < 10) {//�ʏ탂�[�h
		/*��ʕ\��*/
			SetFontSize(30);
			if (gameflag == 1) {
				DrawFormatString(100, 50, Cr[0], "Stage %d Clear!!", stage);
			}
			else if (gameflag == 2) {
				DrawFormatString(100, 50, Cr[7], "1Player Mode Clear!!");
			}
			else if (gameflag == 3) {
				DrawFormatString(100, 50, Cr[1], "Stage %d", stage);
			}
			SetFontSize(15);
			if (gameflag == 1) {
				if (stage == 2 || stage == 5 || stage == 8) {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:%d(BOSS STAGE)", stage + 1);
				}
				else if (stage == 10) {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:LAST(Boss)");
				}
				else {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:%d", stage + 1);
				}

				if (QEndflag == false) {
					DrawFormatString(100, 440, Cr[4], "Q -->Game End(back Title)");
				}
				else {
					DrawFormatString(100, 440, Cr[4], "�{���ɖ߂��Ă���낵���ł���?");
					DrawFormatString(100, 455, Cr[4], "�͂�>Q  �߂炸�ɑ��s����>SPACE or ENTER");
				}
			}
			else if (gameflag == 2) {
				DrawFormatString(200, 85, Cr[2], "Thank You For Playing!!");
				if (gamemode == 3) {
					DrawFormatString(200, 105, Cr[8], "��Փx�I����ʂŉ��L�[��A�ł����...?");
				}
				DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Ranking");
			}
			else if (gameflag == 3) {
				DrawFormatString(100, 80, Cr[1], "Game Over...");
				DrawFormatString(100, 110, Cr[2], "Thank You For Playing!!");
				DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Ranking");
			}
			DrawFormatString(50, 150, Cr[5], "Stage Points:%d", Player.GetPoint());
			DrawFormatString(50, 180, Cr[3], "Rest HP:%d", Player.PlayerHP(0));
			if (gamemode == 1) {//EASY
				if (gameflag == 1 && Player.PlayerHP(0) < 30)DrawFormatString(50, 200, Cr[3], ">Heal 30HP(MAX:30)");
			}
			else if (gamemode == 2) {//NORMAL
				if (gameflag == 1 && Player.PlayerHP(0) < 30)DrawFormatString(50, 200, Cr[3], ">Heal 5HP(MAX:30)");
			}
			else {
				if (gameflag == 1 && Player.PlayerHP(0) == 0)DrawFormatString(50, 200, Cr[3], ">Heal 1HP");
			}

			DrawFormatString(50, 240, Cr[6], "Last Combo(Z):%d", ComboNum[0]);
			DrawFormatString(50, 260, Cr[6], "Last Combo(X):%d", ComboNum[1]);
			DrawFormatString(50, 280, Cr[6], "Last Combo(C):%d", ComboNum[2]);
			DrawFormatString(50, 330, Cr[8], "RESULT");
			DrawFormatString(50, 350, Cr[0], "Stage %d Skill Points(Stage Points + Bonus points):%d", stage, truepoints);
			DrawFormatString(50, 370, Cr[3], "Total Points:%u", point);
		}
		else {//���ꃂ�[�h
			SetFontSize(35);
			if (gameflag == 1 || gameflag == 2) {//�N���A��
				if (gamemode == 20) {
					DrawFormatString(100, 100, Cr[3], "PUZZLE Mode CLEAR!");
				}
				else {
					if (stage == 11 && gamemode >= 13) {
						DrawFormatString(100, 100, Cr[3], "Boss Rush CLEAR.");
					}
					else {
						DrawFormatString(100, 100, Cr[3], "Boss Rush CLEAR!");
					}
				}
			}
			else {
				DrawFormatString(100, 100, Cr[1], "Game Over...");
			}

			if (gamemode == 11) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:EASY");
			}
			else if (gamemode == 12) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:NORMAL");
			}
			else if (gamemode == 13) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:HARD");
			}
			else if (gamemode == 14) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:UNKNOWN");
			}

			if (gamemode == 20) {
				DrawFormatString(100, 200, Cr[4], "Points:%d", Player.GetPoint());
			}
			SetFontSize(15);
			if (stage == 16 && gamemode == 13) {
				if (gamemode == 13) {
					DrawFormatString(100, 300, Cr[8], "��Փx�I����ʂŉ��L�[��A�ł����...?");
				}
				else if (gamemode == 14) {
					DrawFormatString(100, 300, Cr[2], "���߂łƂ�! BossRush���S�N���A!");
				}
			}
			DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Back");
		}

		/*���̑��̏���*/
		
		ScreenFlip();

	} while (1);//�I�����Ȃ�����


	SetFontSize(16);
	ClearDrawScreen(); // ��ʂ�����
	ScreenFlip();
	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);

	return point;
}

//////////////////////////////////////////////////////////////////
//     1Player mode�@main�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@   //
//////////////////////////////////////////////////////////////////
int Player1mode(int *ErrorCheck,int gamemode) {

	//�F�쐬
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//��
	Cr[1] = GetColor(15, 15, 255);//��
	Cr[2] = GetColor(255, 255, 15);//��
	Cr[3] = GetColor(15, 255, 15);//��
	Cr[4] = GetColor(255, 156, 0);//��
	Cr[5] = GetColor(159, 15, 255);//��
	Cr[6] = GetColor(218, 0, 224);//�Ԏ�
	Cr[7] = GetColor(76, 255, 255);//��
	Cr[8] = GetColor(240, 240, 240);//��
	Cr[9] = GetColor(128, 128, 128);//�D

	/*���[�h*/
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����
	DrawString(250, 250, "Now Lording...", Cr[8]);
	switch (gamemode){
	case 1:
		DrawString(50, 350, "���_", Cr[8]);
		DrawString(50, 380, "�����F�̓G��A���œ|���Ɠ��_���{�X�ɂȂ��Ă���.", Cr[8]);
		DrawString(50, 400, "�ŏI�R���{��,�c��HP,�A�C�e�������{�[�i�X�_�̑ΏۂɂȂ邼.", Cr[8]);
		break;
	case 2:
		DrawString(50, 350, "�X�e�[�W", Cr[8]);
		DrawString(50, 380, "�X�e�[�W�͑S����11�X�e�[�W.", Cr[8]);
		DrawString(50, 400, "�X�e�[�W3,6,9,11�̓{�X�킾.", Cr[8]);
		break;
	case 3:
		DrawString(50, 350, "�A�C�e��", Cr[8]);
		DrawString(50, 380, "5�R���{���ƂɃA�C�e����1���܂�.", Cr[8]);
		DrawString(50, 400, "3��̃A�C�e�����g���ėL���ɐi�߂悤.", Cr[8]);
		DrawString(50, 420, "���Ȃ݂�,�Q�[���J�n����1��,�{�X��|���Ă�1���܂�.", Cr[8]);
		break;
	case 4:
		DrawString(50, 350, "��Փx", Cr[8]);
		DrawString(50, 380, "��Փx�͑S����4���.", Cr[8]);
		DrawString(50, 400, "����قǓG�̍U�����������Ȃ邪,�{�[�i�X�_�����Z�����.", Cr[8]);
		break;
	case 11:
		DrawString(50, 350, "�{�X Grad ����Z:�U���e", Cr[8]);
		DrawString(50, 380, "���@��ǔ�����Ԃ��e.", Cr[8]);
		DrawString(50, 400, "�Ђ����Ă��獶�E�ǂ��炩�ɔ����悤.", Cr[8]);
		break;
	case 12:
		DrawString(50, 350, "�{�X Cron ����Z:���[�U�[", Cr[8]);
		DrawString(50, 380, "��������т����̓��[�U�[.", Cr[8]);
		DrawString(50, 400, "�U���������̂ŕs���R�ɋ߂Â��Ă����瓦���悤.", Cr[8]);
		break;
	case 13:
		DrawString(50, 350, "�{�X Erec ����Z:�ːi", Cr[8]);
		DrawString(50, 380, "���@�Ɍ������ċ@�̂��Ɠ˂�����ł���.", Cr[8]);
		DrawString(50, 400, "��Փx���オ��Ƒ��x���オ��.", Cr[8]);
		break;
	case 14:
		DrawString(50, 350, "��������", Cr[8]);
		DrawString(50, 380, "���̃Q�[���ɐ������Ԃ͂Ȃ�.", Cr[8]);
		DrawString(50, 400, "���ɂ͓G�̓��������ɂ߂邱�Ƃ��K�v��.", Cr[8]);
		break;
	case 20:
		DrawString(50, 350, "�p�Y�����[�h", Cr[8]);
		DrawString(50, 380, "�G�͍U�����Ă��Ȃ����[�h.", Cr[8]);
		DrawString(50, 400, "���m�ɑ_���ē��_���҂�!", Cr[8]);
		break;
	default:
		break;
	}
	ScreenFlip();

	bool SPflag = false, OneBossflag = false;//����ȃ��[�h���ǂ���
	if (gamemode > 10) {//11�`14,20
		SPflag = true;//���ꃂ�[�h
		if (gamemode == 11) {
			gamemode = 1;//EASY
		}
		else if (gamemode == 12) {
			gamemode = 2;//NORMAL
		}
		else if (gamemode == 13) {
			gamemode = 3;//HARD
		}
		else if (gamemode == 14) {
			gamemode = 4;//UNKNOWN
		}
		else if (gamemode == 40) {
			gamemode = 4;
			OneBossflag = TRUE;
		}
	}

	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	Fps fps;
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG�摜�̃������ւ̕����ǂݍ���
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	
	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	
	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	
	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//�ēǂݍ���
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:�X�^�[�g�� 1:�X�e�[�W�N���A 2:�S�X�e�[�W�N���A 3:�Q�[���I�[�o�[ 4:�Q�[���I�� 5:�G���[
	int gameovercount = AFTERGAMEOVERCOUNT;//�߂�܂ł̕b��(1/60 s)
	int stage = 0;//���݃X�e�[�W
	int gamecount = 1;//�Q�[��������
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind = 0;//�X�e�[�W�̎�� 1:�m�[�}���X�e�[�W 2:�{�X�X�e�[�W 3:�Q�[���N���A 4:���̑� (0:�G���[)
	unsigned int playerpoint = 0;//���_�̍��v�l
	bool clearflag = false;//�X�e�[�W�N���A
	int ppx = 0, ppy = 0;//���@��x���W��y���W
	int NextHPdamage = 0;//HP���p���p
	int itemnum = 1, itemtime = 0, command = 0;//�A�C�e����,���ʎ���
	bool itemmenu = false, Key = false;//�A�C�e�����j���[���J���Ă��邩
	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/stage.mp3");
	//�ēǂݍ���
	if(SHandle==-1)SHandle = LoadSoundMem("./package/bgm/stage.mp3");

	int SHandle2 = LoadSoundMem("../exe/package/bgm/boss.mp3");
	//�ēǂݍ���
	if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/boss.mp3");

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//�ēǂݍ���
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//�ēǂݍ���
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	int SElaser = LoadSoundMem("../exe/package/bgm/laser.wav");
	//�ēǂݍ���
	if (SElaser == -1)SElaser = LoadSoundMem("./package/bgm/laser.wav");

	i = 0;
	do {
		if (stage != 0) {
			ClearDrawScreen(); // ��ʂ�����
			DrawString(250, 250, "Now Lording...", Cr[8]);
			ScreenFlip();
		}

		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return -1;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}
		
		if (stage > 100)*ErrorCheck = 5;//���炩�ȃG���[

		/*�X�e�[�W���߂̏���*/
		ClearDrawScreen(); // ��ʂ�����
		stage++;//�X�e�[�W����1���₷
		if (SPflag == true) {//���ꃂ�[�h����
			if (stage == 1 && gamemode==20) {//�p�Y�� �n��
				stage = 10;
			}
			else if (stage == 1) {//�{�X���b�V�� �n��
				stage = 3;//1
			}
			else if (stage == 11) {//�p�Y�� �I��
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//�N���A���
				return 0;//�߂�
			}
			else if (stage == 4) {
				stage = 6;//2
			}
			else if (stage == 7) {
				stage = 9;//3
			}
			else if (stage == 10) {
				stage = 11;//4
			}
			else if (stage == 12) {//�{�X���b�V�� �I��(?)
				if (NextHPdamage < 16 && gamemode >= 3) {//HP�����ȏォ��HARD�ȏ�
					stage = 16;
					ClearDrawScreen(); // ��ʂ�����
					DrawString(250, 250, "Last One.", Cr[0]);
					ScreenFlip();
					WaitTimer(2000);// ������2�b�܂�
				}
				else {
					gamemode += 10;
					StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//�N���A���
					gamemode -= 10;
					return 0;//�߂�
				}	
			}
			else if (stage == 17 && OneBossflag == false) {
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//�N���A���
				gamemode -= 10;
				return 0;//�߂�
			}
			else {
				*ErrorCheck = -15;
			}

			if (OneBossflag == true) {
				if (stage == 16) {
					return 0;//�߂�
				}
				SHandle2 = LoadSoundMem("../exe/package/bgm/lastboss.mp3");//���X�{�X
		    	//�ēǂݍ���
				if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/lastboss.mp3");
				stage = 16;
			}
		}
		gamecount = 0;//�o�ߎ��Ԃ�0�Ƀ��Z�b�g
		gameovercount = AFTERGAMEOVERCOUNT;//�I���܂ł̎��������Z�b�g
		gameflag = 0;//�X�e�[�W�N���A���Ă��Ȃ���Ԃɂ���
		clearflag = false;
		Player.StartSet();//���@�̏���������
		for (i = 0; i < MAXENEMY; i++) {
			NormalEnemy[i].StartSet(gamemode);
		}//�G�@�̏���������
		Boss[0].StartSet(0, gamemode);//�{�X�̏�����
		Boss[1].StartSet(0, gamemode);//�{�X�̏�����

		/*�X�e�[�W�J�n����*/
		switch (stage){
		case 7://�m�[�}���X�e�[�W
			SHandle = LoadSoundMem("../exe/package/bgm/stage2.mp3");//�ȑւ�
			//�ēǂݍ���
			if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/stage2.mp3");
		case 1:
		case 2:
		case 4:
		case 5:
		case 8:
		case 10:
			stagekind = 1;
			break;
		case 11://�{�X�X�e�[�W
			SHandle2 = LoadSoundMem("../exe/package/bgm/lastboss.mp3");//���X�{�X
			//�ēǂݍ���
			if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/lastboss.mp3");
		case 3:
		case 6:
		case 9:
		case 16:
			stagekind = 2;
			break;
		case 12://�S�N���A
			stagekind = 3;
			gameflag = 2;
			break;
		default:
			*ErrorCheck = 3;
			break;
		}

		if (stagekind == 0) {//�G���[
			*ErrorCheck = 3;
			return -1;
		}
		else if (stagekind == 1) {//�m�[�}���X�e�[�W
			NormalStage_StartPrepare(stage, ErrorCheck, NormalEnemy);//�m�[�}���X�e�[�W�p����
		}
		else if (stagekind == 2) {//�{�X�X�e�[�W
			Boss[0].StartSet(stage, gamemode);//�{�X�̃Z�b�g
			if (stage == 11)Boss[1].StartSet(99, gamemode);//���g�̃Z�b�g
			else if (stage == 16)Boss[1].StartSet(100, gamemode);//�p�[�c�̃Z�b�g
		}

		Player.PlayerHP(NextHPdamage);//�O�X�e�[�W�Ŏ󂯂��_���[�W��

		if (stagekind == 2) {
			PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//���y
		}
		else {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		command = 50;
		Key = true;
		itemmenu = false;
		itemtime = 0;
		while(gameflag == 0) {
			/////**�X�e�[�W������**/////
			ClearDrawScreen(); // ��ʂ�����

			if (stagekind == 2) {
				if (CheckSoundMem(SHandle2) == 0) {
					PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//���y
				}
			}
			else {
				if (CheckSoundMem(SHandle) == 0) {
					PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
				}
			}

			/*�r�������I������*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				Key = true;
				if (*ErrorCheck == 0) {//����Ȃ��Ƃ̊m�F
					*ErrorCheck = -999;
				}
				ESCGameEnd(ErrorCheck);//�����I��
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				// �T�E���h�n���h���̍폜
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;//error�Ȃ狭���I��
			}

			if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
				*ErrorCheck = 1;
				// �T�E���h�n���h���̍폜
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;        // �G���[���N�����烋�[�v�𔲂���
			}


			if (itemmenu == false) {//�A�C�e�����j���[���J����Ă���Ώ�����~
			/*�Q�[���I�[�o�[����*/
				if (Player.PlayerHP(0) == 0) {
					if (gameovercount == AFTERGAMEOVERCOUNT) {
						PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
					}
					else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
						DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//�j��
					}
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 3;
						break;
					}
				}
				if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0�����ɂ͂Ȃ�Ȃ�

				/*�X�e�[�W�N���A*/
				if (stagekind == 1) {//�m�[�}���X�e�[�W
					if (gameflag == 3) {//�Q�[���I�[�o�[�ɂȂ�Ȃ�N���A�͂��Ȃ�
						clearflag = false;
					}
					else {
						clearflag = true;
					}
					for (i = 0; i < MAXENEMY; i++) {
						if (NormalEnemy[i].EnemyExistCheck() == true) {
							clearflag = false;
						}
					}
				}
				else if (stagekind == 2) {//�{�X�X�e�[�W
					if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//�������Q�[���I�[�o�[�łȂ��A���{�X��HP��0�ŃN���A
						clearflag = true;
					}
				}

				if (clearflag == true) {
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 1;
						if (stagekind == 2) {//�{�X�X�e�[�W
							itemnum += 1;
						}
						break;
					}
				}

				///////�X�e�[�W���C������///////
				/*�v���C���[*/
				Player.PlayerMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot);

				/*�G�@*/
				Player.PlayerPosition(&ppx, &ppy);
				if (stagekind == 1) {//�m�[�}���X�e�[�W
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}
				else if (stagekind == 2) {//�{�X�X�e�[�W
					if (stage == 11) {//���g�̕�����
						Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak,SElaser);
						if (Boss[0].BossHP(0) < 25 && Boss[1].BossMoveSet(0, false) < 10 && gamemode >= 3)Boss[1].BossMoveSet(10, true);//Rain��HP��30��؂�ƕ��g�̍s���ω�
						if (Boss[0].BossHP(0) == 0)Boss[1].BossHP(99);//�{�̂�������Ε��g��������
					}
					Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, SElaser);
					if (stage == 16) {//�p�[�c�̕�����
						Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, SElaser);
						if (Boss[0].BossHP(0) == 0)Boss[1].BossHP(99);//�{�̂�������΃p�[�c��������
						BossStage_NormalEnemyAppear(ErrorCheck, NormalEnemy, Boss);
					}
					Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
					for (i = 0; i < 20; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}

			}

			/////**���**/////
			DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[9], false);// �l�p�`��`��

			/*�A�C�e��*/
			if (itemmenu == true) {//�A�C�e�� ���j���[
				if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_X) == 1) {
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyGraphicDrawing(ErrorCheck, NormalEnemyGraphic);
					}
				}
				else {
					DrawBox(80, 50, 440, 345, Cr[1], false);// �l�p�`��`��
					if (command < 10) {

						if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {
							itemmenu = false;
							Key = true;
						}
						DrawString(100, 70, "�A�C�e�� ���j���[", Cr[8]);
						if (itemnum == 0) {
							DrawString(120, 100, "�F�ւ�(ITEM:1)", Cr[9]);
							DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[9]);
							DrawString(120, 150, "HP��(ITEM:2)", Cr[9]);
						}
						else {
							DrawString(120, 100, "�F�ւ�(ITEM:1)", Cr[8]);
							if (itemtime > 0 || itemnum == 1) {
								DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[8]);
							}
							if (Player.PlayerHP(0) == 30 || itemnum == 1) {
								DrawString(120, 150, "HP��(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 150, "HP��(ITEM:2)", Cr[8]);
							}
						}
						DrawString(120, 175, "���j���[�����", Cr[8]);
						DrawString(100, 270, "�㉺�L�[�őI���AENTER�Ō���", Cr[8]);
						DrawString(100, 290, "X�������Ă����,�G��\��", Cr[8]);
					}
					else if (command < 40) {
						if (command < 20) {
							DrawString(100, 70, "�F�ւ�: Z �V���b�g", Cr[8]);
						}
						else if (command < 30) {
							DrawString(100, 70, "�F�ւ�: X �V���b�g", Cr[8]);
							DrawString(120, 260, "1�߂�(Z�V���b�g)", Cr[8]);
						}
						else {
							DrawString(100, 70, "�F�ւ�: C �V���b�g", Cr[8]);
							DrawString(120, 260, "1�߂�(X�V���b�g)", Cr[8]);
						}
						DrawString(120, 100, "��", Cr[0]);
						DrawString(120, 120, "��", Cr[1]);
						DrawString(120, 140, "��", Cr[2]);
						DrawString(120, 160, "��", Cr[3]);
						DrawString(120, 180, "��", Cr[4]);
						DrawString(120, 200, "��", Cr[5]);
						DrawString(120, 220, "�Ԏ�", Cr[6]);
						DrawString(120, 240, "��", Cr[7]);
						DrawString(100, 300, "�㉺�L�[�őI���AENTER�Ō���", Cr[8]);
						DrawString(100, 320, "X�������Ă����,�G��\��", Cr[8]);
					}

					switch (command) {
					case 0:
						DrawCircle(100, 107, 5, Cr[6], true);
						DrawString(100, 215, "3�̃V���b�g�̐F��,\n�R���{����ۂ����܂ܔC�ӂ̐F�ɕς��܂�.", Cr[3]);
						break;
					case 1:
						DrawCircle(100, 132, 5, Cr[6], true);
						DrawString(100, 215, "�G�̒e�����������,\n�G�̓����������̊Ԏ~�߂܂�.", Cr[3]);
						break;
					case 2:
						DrawCircle(100, 157, 5, Cr[6], true);
						DrawString(100, 215, "HP��10�񕜂��܂�(�ő�l:30).\n�����,��u�������G�ɂȂ�܂�.", Cr[3]);
						break;
					case 3:
						DrawCircle(100, 182, 5, Cr[6], true);
						if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {
							DrawString(100, 215, "�A�C�e���̓{�X��ł͓���ł��܂��񂪁A\n�����Ă���Ύg�����Ƃ͂ł��܂�", Cr[2]);
						}
						else {
							DrawString(100, 215, "�A�C�e����5�R���{���Ƃ�1�����܂�.\n�\������������Ďg�p�\�ł�.", Cr[2]);
						}
						break;
					case 10:
					case 20:
					case 30:
						DrawCircle(100, 107, 5, Cr[0], true);
						break;
					case 11:
					case 21:
					case 31:
						DrawCircle(100, 127, 5, Cr[1], true);
						break;
					case 12:
					case 22:
					case 32:
						DrawCircle(100, 147, 5, Cr[2], true);
						break;
					case 13:
					case 23:
					case 33:
						DrawCircle(100, 167, 5, Cr[3], true);
						break;
					case 14:
					case 24:
					case 34:
						DrawCircle(100, 187, 5, Cr[4], true);
						break;
					case 15:
					case 25:
					case 35:
						DrawCircle(100, 207, 5, Cr[5], true);
						break;
					case 16:
					case 26:
					case 36:
						DrawCircle(100, 227, 5, Cr[6], true);
						break;
					case 17:
					case 27:
					case 37:
						DrawCircle(100, 247, 5, Cr[7], true);
						break;
					case 28:
					case 38:
						DrawCircle(100, 267, 5, Cr[8], true);
						break;
					case 50:
						break;
					default:
						*ErrorCheck = 11;
						break;
					}

					if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == false) {
						if (command == 0) {//�F�ւ�
							if (itemnum > 0) {
								itemnum -= 1;
								command = 10;
							}
						}
						else if (command == 1) {//�X�g�b�v
							if (itemnum > 1 && itemtime <= 0) {
								itemnum -= 2;
								if (stagekind == 1) {//�m�[�}���X�e�[�W
									itemtime = 300;
								}
								else if (stagekind == 2) {//�{�X�X�e�[�W
									itemtime = 180;
								}
								for (i = 0; i < MAXENEMY; i++) {
									NormalEnemy[i].EnemyShotFlagFALSE();//�e������
								}
								for (i = 0; i < 2; i++) {
									for (int j = 0; j < 10; j++) {
										Boss[i].BossShotFlagFALSE(j);//�e������
									}
								}
								itemmenu = false;
							}
						}
						else if (command == 2) {//HP��
							if (Player.PlayerHP(0) != 30 && itemnum > 1) {
								itemnum -= 2;
								Player.PlayerHP(-10);
								itemmenu = false;
							}
						}
						else if (command == 3) {
							itemmenu = false;
						}
						else if (10 <= command && command <= 17) {//Z
							Player.ColorSet(0, command - 10);
							command = 20;
						}
						else if (20 <= command && command <= 27) {//X
							Player.ColorSet(1, command - 20);
							command = 30;
						}
						else if (command == 28) {//�߂�
							command = 10;
						}
						else if (30 <= command && command <= 37) {//C
							Player.ColorSet(2, command - 30);
							command = 50;//�ǂ̃R�}���h�ł��Ȃ�
							itemmenu = false;
						}
						else if (command == 38) {//�߂�
							command = 20;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W) == 1) && Key == false) {
						if (command == 0) {
							command = 3;
						}
						else if (command == 10) {
							command = 17;
						}
						else if (command == 20) {
							command = 28;
						}
						else if (command == 30) {
							command = 38;
						}
						else {
							command--;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S) == 1) && Key == false) {
						if (command == 3) {
							command = 0;
						}
						else if (command == 17) {
							command = 10;
						}
						else if (command == 28) {
							command = 20;
						}
						else if (command == 38) {
							command = 30;
						}
						else {
							command++;
						}
						Key = true;
					}
				}
			}			
			/*�A�C�e�������܂�*/

			Player.PlayerShotColor(PlayerShotKind);
			Player.PlayerShotCombo(ShotCombonum);

			DrawString(515, 210, "���݂̒e�̎��", Cr[9]);
			DrawString(515, 250, "Z�V���b�g:\n\n\nX�V���b�g:\n\n\nC�V���b�g:", Cr[8]);
			for (i = 0; i < 3; i++) {
				DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "�R���{:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(605, 250 + i * 54, "��", Cr[0]);
					break;
				case 1:
					DrawString(605, 250 + i * 54, "��", Cr[1]);
					break;
				case 2:
					DrawString(605, 250 + i * 54, "��", Cr[2]);
					break;
				case 3:
					DrawString(605, 250 + i * 54, "��", Cr[3]);
					break;
				case 4:
					DrawString(605, 250 + i * 54, "��", Cr[4]);
					break;
				case 5:
					DrawString(605, 250 + i * 54, "��", Cr[5]);
					break;
				case 6:
					DrawString(605, 250 + i * 54, "�Ԏ�", Cr[6]);
					break;
				case 7:
					DrawString(605, 250 + i * 54, "��", Cr[7]);
					break;
				default:
					DrawString(605, 250 + i * 54, "��", Cr[9]);
					break;
				}
			}

			if (SPflag == true) {//���ꃂ�[�h
				DrawString(0, 420, "LEFT�L�[:�� RIGHT�L�[:�E Z,X,C:�V���b�g", Cr[9]);
			}
			else {//�ʏ�
				DrawString(0, 420, "LEFT�L�[:�� RIGHT�L�[:�E Z,X,C:�V���b�g SPACE:�A�C�e��", Cr[9]);
				if (stage == 11) {
					DrawFormatString(515, 30, Cr[8], "Stage:LAST");
				}
				else {
					DrawFormatString(515, 30, Cr[8], "Stage:%d", stage);
				}
				if (itemnum == 0) {
					DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
				}
				else {
					DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
				}
			}

			if (Player.PlayerHP(0) > 15) {
				DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HP��`��
			}
			else if (Player.PlayerHP(0) > 7) {
				DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HP��`��
			}
			else {
				DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HP��`��
			}

			DrawString(0, 440, "ESCAPE:�Q�[�������I��", Cr[9]);
			DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

			if (gamemode == 1) {//EASY
				DrawString(530, 60, "EASY", Cr[8]);
			}
			else if (gamemode == 2) {//NORMAL
				DrawString(530, 60, "NORMAL", Cr[8]);
			}
			else if (gamemode == 3) {//HARD
				DrawString(530, 60, "HARD", Cr[8]);
			}
			else if (gamemode == 4) {//UNKNOWN
				DrawString(530, 60, "UNKNOWN", Cr[8]);
			}

			/*���̑��̏���*/
			/*Player.DebagColorSet();//�f�o�b�O�p
			if (CheckHitKey(KEY_INPUT_P) == 1) {
				gameflag = 1;
			}
			/**/

			if (itemmenu == false) {//�A�C�e�����j���[���J����Ă��Ȃ��Ƃ�
				gamecount++;//���Ԍo��
				if (itemtime > -1)itemtime--;
				if (CheckHitKey(KEY_INPUT_SPACE) == 0) {
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false && SPflag == false) {//�A�C�e�����j���[
					itemmenu = true;
					command = 3;
					Key = true;
				}
			}
			if (gamecount > 100000000)gamecount = 0;//�o�O�̖h�~
			if (gamecount > 150000000)*ErrorCheck = 4;//���Ԍo�߂�����
			fps.Update();	//�X�V
			fps.Wait();		//�ҋ@
			//fps.Draw();		//�`��
			ScreenFlip();

		}//�N���A����܂�

		ClearDrawScreen(); // ��ʂ�����
		if (gameflag == 1 && stage >= 11) {//�ŏI�X�e�[�W�N���A
			gameflag = 2;
			if (stage == 11 && SPflag == TRUE && gamemode >= 3 && NextHPdamage < 16) {
				gameflag = 1;
			}
		}
		// �Đ����~�߂܂�
		StopSoundMem(SHandle);
		StopSoundMem(SHandle2);

		if (SPflag == false) {
			playerpoint = StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//�X�e�[�W�N���A���
		}
		else {
			if (OneBossflag == true) {
				return 0;//�߂�
			}

			if (gameflag == 3) {//�{�X���b�V���̃Q�[���I�[�o�[
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);
				gamemode -= 10;
			}
			else if (gameflag == 2) {//�{�X���b�V���̃N���A
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);
				gamemode -= 10;
			}
		}


		if (SPflag == false) {
			if (*ErrorCheck == -2) {//�r���I���̏ꍇ
				*ErrorCheck = 0;//����ɖ߂�
				gameflag = 3;//�Q�[���I�[�o�[�ɂ���
				stage += 1;
			}
			if (gameflag == 2 || gameflag == 3) {//�N���A���Q�[���I�[�o�[(���_�\���Ă�)
				if (gameflag == 2)stage = 12;
				RankingFileCheck(ErrorCheck, playerpoint, gamemode, stage);
				break;
			}
		}

		ScreenFlip();

		if (SPflag == true) {//�{�X���b�V��
			NextHPdamage = 30 - Player.PlayerHP(0);//�񕜂Ȃ�
			if (Player.PlayerHP(0) == 0) {//0�̂Ƃ��̂�
				NextHPdamage = 29;
			}
		}
		else if (gamemode == 1) {//EASY
			NextHPdamage = 0;//�X�e�[�W�N���A���ƂɑS��
		}
		else if (gamemode == 2) {//NORMAL
			NextHPdamage = 25 - Player.PlayerHP(0);//�X�e�[�W�N���A���Ƃ�5��
			if (NextHPdamage < 0)NextHPdamage = 0;
		}
		else if (gamemode == 3 || gamemode == 4) {//HARD || UNKNOWN
			NextHPdamage = 30 - Player.PlayerHP(0);//�񕜂Ȃ�
			if (Player.PlayerHP(0) == 0) {//0�̂Ƃ��̂�
				NextHPdamage = 29;
			}
		}
		
	} while (gameflag <= 1);//�Q�[�����I�����Ȃ�����

	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);
	DeleteSoundMem(SHandle2);

	return 0;
}


//////////////////////////////////
/////---**�`���[�g���A��**---/////
/////////////////////////////////

/*�`���[�g���A���p�X�e�[�W�X�^�[�g���̓G�z�u*/
void Tutoreal_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	/*�X�e�[�W1*/
	if (stage == 1) {
		Enemy[0].AppearEnemy(90, 10, 0);
		Enemy[1].AppearEnemy(130, 10, 0);
		Enemy[2].AppearEnemy(170, 10, 0);
		Enemy[3].AppearEnemy(210, 10, 2);
		Enemy[4].AppearEnemy(250, 10, 3);
		Enemy[5].AppearEnemy(290, 10, 2);
		Enemy[6].AppearEnemy(330, 10, 1);
		Enemy[7].AppearEnemy(370, 10, 2);
		Enemy[8].AppearEnemy(90, 50, 0);
		Enemy[9].AppearEnemy(130, 50, 0);
		Enemy[10].AppearEnemy(170, 50, 1);
		Enemy[11].AppearEnemy(210, 50, 3);
		Enemy[12].AppearEnemy(250, 50, 2);
		Enemy[13].AppearEnemy(290, 50, 3);
		Enemy[14].AppearEnemy(330, 50, 1);
		Enemy[15].AppearEnemy(370, 50, 2);
		for (int i = 16; i < 24; i++) {
			Enemy[i].AppearEnemy(90 + (i - 16) * 40, 80, 11);
		}
	}

	/*�X�e�[�W2*/
	if (stage == 2) {
		Enemy[0].AppearEnemy(50, 10, 0);
		Enemy[1].AppearEnemy(90, 10, 0);
		Enemy[2].AppearEnemy(130, 10, 1);
		Enemy[3].AppearEnemy(170, 10, 2);
		Enemy[4].AppearEnemy(210, 10, 0);
		Enemy[5].AppearEnemy(250, 10, 0);
		Enemy[6].AppearEnemy(290, 10, 3);
		Enemy[7].AppearEnemy(330, 10, 3);
		Enemy[8].AppearEnemy(370, 10, 4);
		Enemy[9].AppearEnemy(410, 10, 4);
		Enemy[10].AppearEnemy(50, 50, 1);
		Enemy[11].AppearEnemy(90, 50, 1);
		Enemy[12].AppearEnemy(130, 50, 0);
		Enemy[13].AppearEnemy(170, 50, 2);
		Enemy[14].AppearEnemy(210, 50, 2);
		Enemy[15].AppearEnemy(250, 50, 2);
		Enemy[16].AppearEnemy(290, 50, 3);
		Enemy[17].AppearEnemy(330, 50, 3);
		Enemy[18].AppearEnemy(370, 50, 5);
		Enemy[19].AppearEnemy(410, 50, 5);
		for (int i = 20; i < 30; i++) {
			Enemy[i].AppearEnemy(50 + (i - 20) * 40, 80, 11);
		}
	}
}

/*�`���[�g���A���̃��C��*/
int Tutoreal(int *ErrorCheck) {
	//�F�쐬
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//��
	Cr[1] = GetColor(15, 15, 255);//��
	Cr[2] = GetColor(255, 255, 15);//��
	Cr[3] = GetColor(15, 255, 15);//��
	Cr[4] = GetColor(255, 156, 0);//��
	Cr[5] = GetColor(159, 15, 255);//��
	Cr[6] = GetColor(218, 0, 224);//�Ԏ�
	Cr[7] = GetColor(76, 255, 255);//��
	Cr[8] = GetColor(240, 240, 240);//��
	Cr[9] = GetColor(128, 128, 128);//�D

	/*���[�h*/
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����
	DrawString(250, 250, "Now Lording...", Cr[8]);
	ScreenFlip();

	int gamemode = 1;//EASY
	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG�摜�̃������ւ̕����ǂݍ���
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);

	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//�ēǂݍ���
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:�X�^�[�g�� 1:�X�e�[�W�N���A 2:�S�X�e�[�W�N���A 3:�Q�[���I�[�o�[ 4:�Q�[���I�� 5:�G���[
	int gameovercount = 300;//�߂�܂ł̕b��(1/60 s)
	int stage = 0;//���݃X�e�[�W
	int gamecount = 1;//�Q�[��������
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	unsigned int playerpoint = 0;//���_�̍��v�l
	bool clearflag = false;//�X�e�[�W�N���A
	int ppx = 0, ppy = 0;//���@��x���W��y���W
	int itemnum = 0, itemtime = 0, command = 0;//�A�C�e����,���ʎ���
	bool itemmenu = false, Key = false;//�A�C�e�����j���[���J���Ă��邩
	int Tutorealcount = 120, TutorealNo = 1;//�`���[�g���A���p�ϐ�
	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/stage.mp3");
	//�ēǂݍ���
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/stage.mp3");

	int SHandle2 = LoadSoundMem("../exe/package/bgm/boss.mp3");
	//�ēǂݍ���
	if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/boss.mp3");

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//�ēǂݍ���
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//�ēǂݍ���
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	i = 0;
	do {
		ClearDrawScreen(); // ��ʂ�����
		DrawString(250, 250, "Now Lording...", Cr[8]);
		ScreenFlip();

		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return -1;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (stage > 100)*ErrorCheck = 5;//���炩�ȃG���[

		/*�X�e�[�W���߂̏���*/
		ClearDrawScreen(); // ��ʂ�����
		stage++;//�X�e�[�W����1���₷
		gamecount = 0;//�o�ߎ��Ԃ�0�Ƀ��Z�b�g
		gameovercount = AFTERGAMEOVERCOUNT;//�I���܂ł̎��������Z�b�g
		gameflag = 0;//�X�e�[�W�N���A���Ă��Ȃ���Ԃɂ���
		clearflag = false;
		Player.StartSet();//���@�̏���������
		for (i = 0; i < MAXENEMY; i++) {
			NormalEnemy[i].StartSet(gamemode);
		}//�G�@�̏���������
		Boss[0].StartSet(0, gamemode);//�{�X�̏�����
		Boss[1].StartSet(0, gamemode);//�{�X�̏�����

		/*�`���[�g���A���I������*/
		if (stage >= 4) {
			break;//�I��
		}

		/*�X�e�[�W�J�n����*/
		if (stage != 3) {//�m�[�}���X�e�[�W
			Tutoreal_StartPrepare(stage, ErrorCheck, NormalEnemy);//�m�[�}���X�e�[�W�p����
		}
		else if (stage == 3) {//�{�X�X�e�[�W
			Boss[0].StartSet(stage, gamemode);//�{�X�̃Z�b�g
		}

		if (stage == 3) {
			PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//���y
		}
		else {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		command = 50;
		Key = true;
		itemmenu = false;
		itemtime = 0;
		if (stage == 1) {
			Tutorealcount = 120;
			TutorealNo = 1;
			itemnum = 0;
		}
		else if (stage == 2) {
			Tutorealcount = 120;
			TutorealNo = 11;
			itemnum = 0;
		}
		else if (stage == 3) {
			Tutorealcount = 120;
			TutorealNo = 21;
		}

		while (gameflag == 0) {
			/////**�X�e�[�W������**/////
			ClearDrawScreen(); // ��ʂ�����

			if (stage == 3) {
				if (CheckSoundMem(SHandle2) == 0) {
					PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//���y
				}
			}
			else {
				if (CheckSoundMem(SHandle) == 0) {
					PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
				}
			}

			/*�r�������I������*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				Key = true;
				if (*ErrorCheck == 0) {//����Ȃ��Ƃ̊m�F
					*ErrorCheck = -999;
				}
				ESCGameEnd(ErrorCheck);//�����I��
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				// �T�E���h�n���h���̍폜
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;//error�Ȃ狭���I��
			}

			if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
				*ErrorCheck = 1;
				// �T�E���h�n���h���̍폜
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;        // �G���[���N�����烋�[�v�𔲂���
			}


			if (itemmenu == false) {//�A�C�e�����j���[���J����Ă���Ώ�����~
			/*�Q�[���I�[�o�[����*/
				if (Player.PlayerHP(0) == 0) {
					if (gameovercount == AFTERGAMEOVERCOUNT) {
						PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
					}
					else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
						DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//�j��
					}
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 3;
						break;
					}
				}
				if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0�����ɂ͂Ȃ�Ȃ�

				/*�X�e�[�W�N���A*/
				if (stage != 3) {//�m�[�}���X�e�[�W
					if (gameflag == 3) {//�Q�[���I�[�o�[�ɂȂ�Ȃ�N���A�͂��Ȃ�
						clearflag = false;
					}
					else {
						clearflag = true;
					}
					for (i = 0; i < MAXENEMY; i++) {
						if (NormalEnemy[i].EnemyExistCheck() == true) {
							clearflag = false;
						}
					}
				}
				else if (stage == 3) {//�{�X�X�e�[�W
					if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//�������Q�[���I�[�o�[�łȂ��A���{�X��HP��0�ŃN���A
						clearflag = true;
					}
				}

				if (clearflag == true) {
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 1;
						break;
					}
				}

				///////�X�e�[�W���C������///////
				/*�`���[�g���A�� ����*/
				DrawBox(40, 110, 460, 350, Cr[9], false);// �l�p�`��`��

				switch (TutorealNo){
					/*stage1*/
				case 1:
					DrawString(50, 120, "�`���[�g���A���ւ悤����!", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 180;
						TutorealNo = 2;
					}
					break;
				case 2:
					DrawString(50, 120, "���̃Q�[����,�G����̍U���������", Cr[8]);
					DrawString(50, 140, "�G��|���ē��_���҂��̂��ړI�ł�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 3;
					}
					break;
				case 3:
					DrawString(50, 120, "�܂���,��{�I�ȓ�������ł�.", Cr[8]);
					DrawString(50, 140, "�E�L�[�ŉE��,���L�[�ō��ɓ����܂�.", Cr[8]);
					DrawString(50, 160, "�v���C���[��,���E�ɂ����������Ƃ͂ł��܂���.", Cr[8]);
					DrawString(50, 180, "�G���e�������Ă���̂�,�����Ĕ����܂��傤.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 720;
						TutorealNo = 4;
					}
					break;
				case 4:
					DrawString(50, 120, "����,�V���b�g�ɂ��Ăł�.", Cr[8]);
					DrawString(50, 140, "�V���b�g��,Z,X,C�Ō����Ƃ��ł��܂�.", Cr[8]);
					DrawString(50, 160, "�����̃V���b�g�͑S��", Cr[8]);
					DrawString(50, 180, "�Ɨ������e�ɂȂ��Ă��܂�.", Cr[8]);
					DrawString(50, 200, "1�̃V���b�g�ɂ�,��ʏ�ɂ͍ő�3���܂�", Cr[8]);
					DrawString(50, 220, "�����Ƃ��ł��܂�.", Cr[8]);
					DrawString(50, 240, "�Ȍ�,Z,X,C�L�[�ɂ��V���b�g�����ꂼ��", Cr[8]);
					DrawString(50, 260, "Z�V���b�g,X�V���b�g,C�V���b�g�ƌĂт܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 480;
						TutorealNo = 5;
					}
					break;
				case 5:
					DrawString(50, 120, "�e�V���b�g�ɂ�,���O�ɓ|����(�U������)�G�ɂ��", Cr[8]);
					DrawString(50, 140, "���ꂼ��F���ۑ�����܂�.", Cr[8]);
					DrawString(50, 160, "�Ⴆ��,Z�V���b�g�ŐԂ̓G��|����,", Cr[8]);
					DrawString(50, 180, "Z�V���b�g�ɐԂ��ۑ�����܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 720;
						TutorealNo = 6;
						NormalEnemy[16].BreakEnemy();
						NormalEnemy[17].BreakEnemy();
					}
					break;
				case 6:
					DrawString(50, 120, "�ł�,���ۂɍ�����4�̂̐Ԃ̓G��", Cr[8]);
					DrawString(50, 140, "Z�V���b�g�œ|���Ă݂܂��傤.", Cr[8]);
					DrawString(50, 160, "�����,��ʉE����Z�V���b�g�̗���", Cr[8]);
					DrawString(50, 180, "Z�V���b�g:�� 4�R���{ �ƕ\�������͂��ł�.", Cr[8]);
					DrawString(50, 200, "����͂��Ȃ킿,Z�V���b�g�ŐԂ̓G��", Cr[8]);
					DrawString(50, 220, "�A����4�̓|�������Ƃ��Ӗ����܂�.", Cr[8]);
					if (NormalEnemy[0].EnemyExistCheck() == false && NormalEnemy[1].EnemyExistCheck() == false) {
						TutorealNo = 7;
						NormalEnemy[18].BreakEnemy();
					}
					break;
				case 7:
					DrawString(50, 120, "����,�����̐ƐԂ̓G��|���Ă݂܂��傤.", Cr[8]);
					DrawString(50, 140, "X�V���b�g�Ő̓G��|���Ă���Z�V���b�g��", Cr[8]);
					DrawString(50, 160, "�Ԃ̓G��|����,Z�V���b�g�̃R���{��", Cr[8]);
					DrawString(50, 180, "�����邱�Ƃ��ł��܂�.", Cr[8]);
					if (NormalEnemy[2].EnemyExistCheck() == false) {
						TutorealNo = 8;
					}
					break;
				case 8:
					DrawString(50, 120, "�����܂�,�w���ʂ�̍s�������Ă����,", Cr[8]);
					DrawString(50, 140, "��ʉE���ɂ� Z�V���b�g:�� 5�R���{,", Cr[8]);
					DrawString(50, 160, "X�V���b�g:�� 1�R���{�ƂȂ��Ă���͂��ł�.", Cr[8]);
					DrawString(50, 180, "������,�Ⴆ��Z�V���b�g:��:4�R���{�̏�Ԃ�", Cr[8]);
					DrawString(50, 200, "Z�V���b�g�Ő̓G��|���Ă��܂���,", Cr[8]);
					DrawString(50, 220, "Z�V���b�g�͐�1�R���{�ɂȂ��Ă��܂�,", Cr[8]);
					DrawString(50, 240, "��������Z�V���b�g�ŐԂ̓G��|���Ă�,", Cr[8]);
					DrawString(50, 260, "Z�V���b�g:��:1�R���{�ƂȂ��Ă��܂��܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 9;
						for (i = 19; i < 24; i++) {
							NormalEnemy[i].BreakEnemy();
						}
					}
					break;
				case 9:
					DrawString(50, 120, "�ł�,���܂��R���{���҂���,", Cr[8]);
					DrawString(50, 140, "�G��S�ł����Ă�������.", Cr[8]);
					DrawString(50, 160, "1�R���{��1�_,2�R���{��2�_,3�R���{��4�_...", Cr[8]);
					DrawString(50, 180, "�Ƃ����悤��,���_�̓R���{���ɉ����Ĕ{�X��", Cr[8]);
					DrawString(50, 200, "�����Ă����܂�.", Cr[8]);
					DrawString(50, 220, "�e�̎�ނ�3��ނɑ΂�,�G��4��ނ��܂�.", Cr[8]);
					DrawString(50, 240, "�{�҂ł͍ŏI�R���{�����{�[�i�X�_�ƂȂ�̂�,", Cr[8]);
					DrawString(50, 260, "�R���{�����Ȃ��V���b�g�̃R���{��؂�,4��ޖڂ�", Cr[8]);
					DrawString(50, 280, "�|���Ƃ悢�ł��傤.", Cr[8]);
					break;
					/*stage2*/
				case 11:
					DrawString(60, 120, "�����ł�,�A�C�e���ɂ��Đ������܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 12;
					}
					break;
				case 12:
					DrawString(50, 120, "item�͍ŏ���1�����Ă��܂�.", Cr[8]);
					DrawString(50, 140, "(���݂̓`���[�g���A���Ȃ̂Ŏ����Ă��܂���.)", Cr[8]);
					DrawString(50, 160, "�܂�,�m�[�}���X�e�[�W�ł�,", Cr[8]);
					DrawString(50, 180, "5�R���{���Ƃ�1��,", Cr[8]);
					DrawString(50, 200, "�{�X�X�e�[�W�ł�,�{�X��|����1��", Cr[8]);
					DrawString(50, 220, "item�̗ʂ������܂�.", Cr[8]);
					DrawString(50, 240, "item�̌���,", Cr[8]);
					DrawString(50, 260, "��ʉE���ł��ł��m�F�ł��܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 13;
					}
					break;
				case 13:
					DrawString(50, 120, "�A�C�e����3��ނ���,����item�������", Cr[8]);
					DrawString(50, 140, "�g�����Ƃ��ł��܂�.", Cr[8]);
					DrawString(50, 160, "1.�F�ւ�", Cr[8]);
					DrawString(50, 180, "item��1�����,Z,X,C�S�ẴV���b�g��", Cr[8]);
					DrawString(50, 200, "�ۑ�����Ă���F��,���ꂼ��C�ӂ�", Cr[8]);
					DrawString(50, 220, "�ς��邱�Ƃ��ł��܂�.", Cr[8]);
					DrawString(50, 240, "�F��ς��Ă��R���{�͓r�؂�Ȃ��̂�,", Cr[8]);
					DrawString(50, 260, "�Ⴆ�ΐ�4�R���{�̌�ɐɕς���,�̓G��|����", Cr[8]);
					DrawString(50, 280, "��5�R���{�Ƃ��Ĉ����܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 14;
					}
					break;
				case 14:
					DrawString(50, 120, "2.�X�g�b�v", Cr[8]);
					DrawString(50, 140, "item��2�����,���΂炭�G�̓������~�߂�������,", Cr[8]);
					DrawString(50, 160, "���ł���e�����ׂď����܂�.", Cr[8]);
					DrawString(50, 180, "�G�̒e�������Ƃ��ȂǂɗL���ł��傤.", Cr[8]);
					DrawString(50, 220, "3.HP��", Cr[8]);
					DrawString(50, 240, "item��2�����,HP��10�񕜂��܂�.", Cr[8]);
					DrawString(50, 260, "�ő�HP��30�Ȃ̂�,����ȏ�͉񕜂��܂���.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 420;
						TutorealNo = 15;
					}
					break;
				case 15:
					DrawString(50, 120, "�����̃A�C�e����,�S��SPACE�L�[�ŊJ��", Cr[8]);
					DrawString(50, 140, "�A�C�e�����j���[����g�����Ƃ��ł��܂�.", Cr[8]);
					DrawString(50, 160, "�����������Ō��邱�Ƃ��\�ł�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 16;
						for (i = 20; i < 30; i++) {
							NormalEnemy[i].BreakEnemy();
						}
						itemnum = 3;
					}
					break;
				case 16:
					DrawString(50, 120, "�ł�,item��3�n���܂��̂�,", Cr[8]);
					DrawString(50, 140, "�F�ւ����g��,�S��Z�V���b�g�œ|����", Cr[8]);
					DrawString(50, 160, "20�R���{��_���Ă݂܂��傤", Cr[8]);
					DrawString(50, 180, "(�������_��Ȃ��Ă��\���܂���)", Cr[8]);
					DrawString(50, 200, "�G��S�ł������,���̃X�e�[�W�ɐi�݂܂�.", Cr[8]);
					break;
					/*stage3*/
				case 21:
					DrawString(50, 120, "stage3,6,9,11�ł�,�{�X�킪����܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 240;
						TutorealNo = 22;
					}
					break;
				case 22:
					DrawString(50, 120, "�{�X��HP�������Ă���,0�ɂ��邱�Ƃ�", Cr[8]);
					DrawString(50, 140, "�|�����Ƃ��ł��܂�", Cr[8]);
					DrawString(50, 160, "�|���΃X�e�[�W�N���A�ł�.", Cr[8]);
					DrawString(50, 180, "�{�X��HP��,�㕔�ɕ\������Ă��܂�.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 23;
					}
					break;
				case 23:
					DrawString(50, 120, "�{�X�ɂ��F���ݒ肳��Ă���,", Cr[8]);
					DrawString(50, 140, "���Ԍo�߂ŕς��܂�.", Cr[8]);
					DrawString(50, 160, "���݂̃{�X�̐F��,HP�o�[�Ɠ����ł�.", Cr[8]);
					DrawString(50, 180, "�{�X�̓��_��,�_���[�W��^���邽�т�", Cr[8]);
					DrawString(50, 200, "3+(�R���{��)�_,", Cr[8]);
					DrawString(50, 220, "�|����EASY:100,NORMAL:200,HARD:300�_��", Cr[8]);
					DrawString(50, 240, "���Z����܂�.", Cr[8]);
					DrawString(50, 260, "���̃{�X��|����,�`���[�g���A���I���ł�!", Cr[8]);
				default:
					break;
				}


				/*�v���C���[*/
				Player.PlayerMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot);

				/*�G�@*/
				Player.PlayerPosition(&ppx, &ppy);
				if (stage != 3) {//�m�[�}���X�e�[�W
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, 0, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}
				else if (stage == 3) {//�{�X�X�e�[�W
					Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, 0);
					Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
				}

			}

			/////**���**/////
			DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[8], false);// �l�p�`��`��

			/*�A�C�e��*/
			if (itemmenu == true) {//�A�C�e�� ���j���[
				if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_X) == 1) {
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyGraphicDrawing(ErrorCheck, NormalEnemyGraphic);
					}
				}
				else {
					DrawBox(80, 50, 440, 345, Cr[1], false);// �l�p�`��`��
					if (command < 10) {

						if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {
							itemmenu = false;
							Key = true;
						}
						DrawString(100, 70, "�A�C�e�� ���j���[", Cr[8]);
						if (itemnum == 0) {
							DrawString(120, 100, "�F�ւ�(ITEM:1)", Cr[9]);
							DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[9]);
							DrawString(120, 150, "HP��(ITEM:2)", Cr[9]);
						}
						else {
							DrawString(120, 100, "�F�ւ�(ITEM:1)", Cr[8]);
							if (itemtime > 0 || itemnum == 1) {
								DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 125, "�X�g�b�v(ITEM:2)", Cr[8]);
							}
							if (Player.PlayerHP(0) == 30 || itemnum == 1) {
								DrawString(120, 150, "HP��(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 150, "HP��(ITEM:2)", Cr[8]);
							}
						}
						DrawString(120, 175, "���j���[�����", Cr[8]);
						DrawString(100, 270, "�㉺�L�[�őI���AENTER�Ō���", Cr[8]);
						DrawString(100, 290, "X�������Ă����,�G��\��", Cr[8]);
					}
					else if (command < 40) {
						if (command < 20) {
							DrawString(100, 70, "�F�ւ�: Z �V���b�g", Cr[8]);
						}
						else if (command < 30) {
							DrawString(100, 70, "�F�ւ�: X �V���b�g", Cr[8]);
							DrawString(120, 260, "1�߂�(Z�V���b�g)", Cr[8]);
						}
						else {
							DrawString(100, 70, "�F�ւ�: C �V���b�g", Cr[8]);
							DrawString(120, 260, "1�߂�(X�V���b�g)", Cr[8]);
						}
						DrawString(120, 100, "��", Cr[0]);
						DrawString(120, 120, "��", Cr[1]);
						DrawString(120, 140, "��", Cr[2]);
						DrawString(120, 160, "��", Cr[3]);
						DrawString(120, 180, "��", Cr[4]);
						DrawString(120, 200, "��", Cr[5]);
						DrawString(120, 220, "�Ԏ�", Cr[6]);
						DrawString(120, 240, "��", Cr[7]);
						DrawString(100, 300, "�㉺�L�[�őI���AENTER�Ō���", Cr[8]);
						DrawString(100, 320, "X�������Ă����,�G��\��", Cr[8]);
					}

					switch (command) {
					case 0:
						DrawCircle(100, 107, 5, Cr[6], true);
						DrawString(100, 215, "3�̃V���b�g�̐F��,\n�R���{����ۂ����܂ܔC�ӂ̐F�ɕς��܂�.", Cr[3]);
						break;
					case 1:
						DrawCircle(100, 132, 5, Cr[6], true);
						DrawString(100, 215, "�G�̒e�����������,\n�G�̓����������̊Ԏ~�߂܂�.", Cr[3]);
						break;
					case 2:
						DrawCircle(100, 157, 5, Cr[6], true);
						DrawString(100, 215, "HP��10�񕜂��܂�(�ő�l:30).\n�����,��u�������G�ɂȂ�܂�.", Cr[3]);
						break;
					case 3:
						DrawCircle(100, 182, 5, Cr[6], true);
						if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {
							DrawString(100, 215, "�A�C�e���̓{�X��ł͓���ł��܂��񂪁A\n�����Ă���Ύg�����Ƃ͂ł��܂�", Cr[2]);
						}
						else {
							DrawString(100, 215, "�A�C�e����5�R���{���Ƃ�1�����܂�.\n�\������������Ďg�p�\�ł�.", Cr[2]);
						}
						break;
					case 10:
					case 20:
					case 30:
						DrawCircle(100, 107, 5, Cr[0], true);
						break;
					case 11:
					case 21:
					case 31:
						DrawCircle(100, 127, 5, Cr[1], true);
						break;
					case 12:
					case 22:
					case 32:
						DrawCircle(100, 147, 5, Cr[2], true);
						break;
					case 13:
					case 23:
					case 33:
						DrawCircle(100, 167, 5, Cr[3], true);
						break;
					case 14:
					case 24:
					case 34:
						DrawCircle(100, 187, 5, Cr[4], true);
						break;
					case 15:
					case 25:
					case 35:
						DrawCircle(100, 207, 5, Cr[5], true);
						break;
					case 16:
					case 26:
					case 36:
						DrawCircle(100, 227, 5, Cr[6], true);
						break;
					case 17:
					case 27:
					case 37:
						DrawCircle(100, 247, 5, Cr[7], true);
						break;
					case 28:
					case 38:
						DrawCircle(100, 267, 5, Cr[8], true);
						break;
					case 50:
						break;
					default:
						*ErrorCheck = 11;
						break;
					}

					if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == false) {
						if (command == 0) {//�F�ւ�
							if (itemnum > 0) {
								itemnum -= 1;
								command = 10;
							}
						}
						else if (command == 1) {//�X�g�b�v
							if (itemnum > 1 && itemtime <= 0) {
								itemnum -= 2;
								itemtime = 240;
								for (i = 0; i < MAXENEMY; i++) {
									NormalEnemy[i].EnemyShotFlagFALSE();//�e������
								}
								for (i = 0; i < 2; i++) {
									for (int j = 0; j < 10; j++) {
										Boss[i].BossShotFlagFALSE(j);//�e������
									}
								}
								itemmenu = false;
							}
						}
						else if (command == 2) {//HP��
							if (Player.PlayerHP(0) != 30 && itemnum > 1) {
								itemnum -= 2;
								Player.PlayerHP(-10);
								itemmenu = false;
							}
						}
						else if (command == 3) {
							itemmenu = false;
						}
						else if (10 <= command && command <= 17) {//Z
							Player.ColorSet(0, command - 10);
							command = 20;
						}
						else if (20 <= command && command <= 27) {//X
							Player.ColorSet(1, command - 20);
							command = 30;
						}
						else if (command == 28) {//�߂�
							command = 10;
						}
						else if (30 <= command && command <= 37) {//C
							Player.ColorSet(2, command - 30);
							command = 50;//�ǂ̃R�}���h�ł��Ȃ�
							itemmenu = false;
						}
						else if (command == 38) {//�߂�
							command = 20;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W) == 1) && Key == false) {
						if (command == 0) {
							command = 3;
						}
						else if (command == 10) {
							command = 17;
						}
						else if (command == 20) {
							command = 28;
						}
						else if (command == 30) {
							command = 38;
						}
						else {
							command--;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S) == 1) && Key == false) {
						if (command == 3) {
							command = 0;
						}
						else if (command == 17) {
							command = 10;
						}
						else if (command == 28) {
							command = 20;
						}
						else if (command == 38) {
							command = 30;
						}
						else {
							command++;
						}
						Key = true;
					}
				}
			}
			/*�A�C�e�������܂�*/

			Player.PlayerShotColor(PlayerShotKind);
			Player.PlayerShotCombo(ShotCombonum);

			DrawString(515, 210, "���݂̒e�̎��", Cr[9]);
			DrawString(515, 250, "Z�V���b�g:\n\n\nX�V���b�g:\n\n\nC�V���b�g:", Cr[8]);
			for (i = 0; i < 3; i++) {
				DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "�R���{:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(605, 250 + i * 54, "��", Cr[0]);
					break;
				case 1:
					DrawString(605, 250 + i * 54, "��", Cr[1]);
					break;
				case 2:
					DrawString(605, 250 + i * 54, "��", Cr[2]);
					break;
				case 3:
					DrawString(605, 250 + i * 54, "��", Cr[3]);
					break;
				case 4:
					DrawString(605, 250 + i * 54, "��", Cr[4]);
					break;
				case 5:
					DrawString(605, 250 + i * 54, "��", Cr[5]);
					break;
				case 6:
					DrawString(605, 250 + i * 54, "�Ԏ�", Cr[6]);
					break;
				case 7:
					DrawString(605, 250 + i * 54, "��", Cr[7]);
					break;
				default:
					DrawString(605, 250 + i * 54, "��", Cr[9]);
					break;
				}
			}

			DrawString(0, 420, "LEFT�L�[:�� RIGHT�L�[:�E Z,X,C:�V���b�g SPACE:�A�C�e��", Cr[9]);
			DrawFormatString(515, 30, Cr[8], "Stage:%d", stage);
			if (itemnum == 0) {
				DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
			}
			else {
				DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
			}

			if (Player.PlayerHP(0) > 15) {
				DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HP��`��
			}
			else if (Player.PlayerHP(0) > 7) {
				DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HP��`��
			}
			else {
				DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HP��`��
			}

			DrawString(0, 440, "ESCAPE:�Q�[�������I��", Cr[9]);
			DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

			DrawString(530, 60, "Tutoreal", Cr[8]);

			if (itemmenu == false) {//�A�C�e�����j���[���J����Ă��Ȃ��Ƃ�
				gamecount++;//���Ԍo��
				if (itemtime > -1)itemtime--;
				if (CheckHitKey(KEY_INPUT_SPACE) == 0) {
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {//�A�C�e�����j���[
					itemmenu = true;
					command = 3;
					Key = true;
				}
			}
			if (gamecount > 100000000)gamecount = 0;//�o�O�̖h�~
			if (gamecount > 150000000)*ErrorCheck = 4;//���Ԍo�߂�����
			ScreenFlip();

		}//�N���A����܂�

		ClearDrawScreen(); // ��ʂ�����
		if (gameflag == 1 && stage >= 3) {//�ŏI�X�e�[�W�N���A
			gameflag = 2;
		}
		// �Đ����~�߂܂�
		StopSoundMem(SHandle);
		StopSoundMem(SHandle2);

		if (*ErrorCheck == -2) {//�r���I���̏ꍇ
			*ErrorCheck = 0;//����ɖ߂�
			gameflag = 3;//�Q�[���I�[�o�[�ɂ���
		}

	} while (gameflag <= 1);//�Q�[�����I�����Ȃ�����

	DrawString(0, 200, "����Ń`���[�g���A���͏I���ł�.", Cr[8]);
	DrawString(0, 250, "�{�҂̓X�e�[�W11�܂ł���܂�.", Cr[8]);
	DrawString(0, 300, "���ЍŌ�܂ł��y���݂�������.", Cr[8]);
	ScreenFlip();
	WaitTimer(2000);//������2�b�܂�

	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);
	DeleteSoundMem(SHandle2);

	return 0;
}

/*�f�����*/
void Demonstration(int *ErrorCheck) {
	int demoselect = GetRand(2) + 1;//�ǂ̃f�����Đ����邩(1�`3)
	int demotimecount = 3600;//1�f���̍ő�Đ�����
	int BGM;

	//�F�쐬
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//��
	Cr[1] = GetColor(15, 15, 255);//��
	Cr[2] = GetColor(255, 255, 15);//��
	Cr[3] = GetColor(15, 255, 15);//��
	Cr[4] = GetColor(255, 156, 0);//��
	Cr[5] = GetColor(159, 15, 255);//��
	Cr[6] = GetColor(218, 0, 224);//�Ԏ�
	Cr[7] = GetColor(76, 255, 255);//��
	Cr[8] = GetColor(240, 240, 240);//��
	Cr[9] = GetColor(128, 128, 128);//�D

	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG�摜�̃������ւ̕����ǂݍ���
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//�ēǂݍ���
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);

	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//�ēǂݍ���
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:�X�^�[�g�� 1:�X�e�[�W�N���A 2:�S�X�e�[�W�N���A 3:�Q�[���I�[�o�[ 4:�Q�[���I�� 5:�G���[
	int gameovercount = AFTERGAMEOVERCOUNT;//�߂�܂ł̕b��(1/60 s)
	int stage = 0;//���݃X�e�[�W
	int gamecount = 1;//�Q�[��������
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind = 0;//�X�e�[�W�̎�� 1:�m�[�}���X�e�[�W 2:�{�X�X�e�[�W 3:�Q�[���N���A 4:���̑� (0:�G���[)
	unsigned int playerpoint = 0;//���_�̍��v�l
	bool clearflag = false;//�X�e�[�W�N���A
	int ppx = 0, ppy = 0;//���@��x���W��y���W
	int itemnum = 0;//�A�C�e����
	int gamemode = 0;
	int moveselect = 0, movetime = 0;//�����̌���Ɠ����̎���

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//�ēǂݍ���
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//�ēǂݍ���
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	int SElaser = LoadSoundMem("../exe/package/bgm/laser.wav");
	//�ēǂݍ���
	if (SElaser == -1)SElaser = LoadSoundMem("./package/bgm/laser.wav");

	i = 0;
	if (demoselect == 1) {
		demotimecount = 1800;
		stage = 4;
		stagekind = 1;
		gamemode = 1;
		BGM = LoadSoundMem("../exe/package/bgm/stage.mp3");
		//�ēǂݍ���
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/stage.mp3");
	}
	else if (demoselect == 2) {
		stage = 6;
		stagekind = 2;
		gamemode = 3;
		BGM = LoadSoundMem("../exe/package/bgm/boss.mp3");
		//�ēǂݍ���
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/boss.mp3");
	}
	else if (demoselect == 3) {
		demotimecount = 1800;
		stage = 7;
		stagekind = 1;
		gamemode = 2;
		BGM = LoadSoundMem("../exe/package/bgm/stage2.mp3");
		//�ēǂݍ���
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/stage2.mp3");
	}
	else {
		*ErrorCheck = -9;
	}
	itemnum = GetRand(5);

	if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
		*ErrorCheck = 1;
		return;        // �G���[���N�����烋�[�v�𔲂���
	}

	if (stage > 100)*ErrorCheck = 5;//���炩�ȃG���[

	if (*ErrorCheck != 0) {
		return;//error�Ȃ狭���I��
	}

	/*�X�e�[�W���߂̏���*/
	ClearDrawScreen(); // ��ʂ�����
	gamecount = 0;//�o�ߎ��Ԃ�0�Ƀ��Z�b�g
	gameovercount = AFTERGAMEOVERCOUNT;//�I���܂ł̎��������Z�b�g
	gameflag = 0;//�X�e�[�W�N���A���Ă��Ȃ���Ԃɂ���
	clearflag = false;
	Player.StartSet();//���@�̏���������
	for (i = 0; i < MAXENEMY; i++) {
		NormalEnemy[i].StartSet(gamemode);
	}//�G�@�̏���������
	Boss[0].StartSet(0, gamemode);//�{�X�̏�����
	Boss[1].StartSet(0, gamemode);//�{�X�̏�����

	if (stagekind == 0) {//�G���[
		*ErrorCheck = 3;
		return;
	}
	else if (stagekind == 1) {//�m�[�}���X�e�[�W
		NormalStage_StartPrepare(stage, ErrorCheck, NormalEnemy);//�m�[�}���X�e�[�W�p����
	}
	else if (stagekind == 2) {//�{�X�X�e�[�W
		Boss[0].StartSet(stage, gamemode);//�{�X�̃Z�b�g
	}

	while (gameflag == 0) {
		/////**�X�e�[�W������**/////
		ClearDrawScreen(); // ��ʂ�����

		if (CheckSoundMem(BGM) == 0) {
			PlaySoundMem(BGM, DX_PLAYTYPE_BACK);//���y
		}

		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			if (*ErrorCheck == 0) {//����Ȃ��Ƃ̊m�F
				*ErrorCheck = -999;
			}
			ESCGameEnd(ErrorCheck);//�����I��
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(BGM);
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		/*�I������*/
		if (CheckHitKey(KEY_INPUT_RETURN) == 1) {//�f���I��
			gameflag = 4;
			break;
		}

		if (demotimecount < 0) {
			gameflag = 4;
			break;
		}


		/*�Q�[���I�[�o�[����*/
		if (Player.PlayerHP(0) == 0) {
			if (gameovercount == AFTERGAMEOVERCOUNT) {
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
				DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//�j��
			}
			gameovercount--;
			if (gameovercount <= 0) {
				gameflag = 3;
				break;
			}
		}
		if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0�����ɂ͂Ȃ�Ȃ�

		/*�X�e�[�W�N���A*/
		if (stagekind == 1) {//�m�[�}���X�e�[�W
			if (gameflag == 3) {//�Q�[���I�[�o�[�ɂȂ�Ȃ�N���A�͂��Ȃ�
				clearflag = false;
			}
			else {
				clearflag = true;
			}
			for (i = 0; i < MAXENEMY; i++) {
				if (NormalEnemy[i].EnemyExistCheck() == true) {
					clearflag = false;
				}
			}
		}
		else if (stagekind == 2) {//�{�X�X�e�[�W
			if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//�������Q�[���I�[�o�[�łȂ��A���{�X��HP��0�ŃN���A
				clearflag = true;
			}
		}

		if (clearflag == true) {
			gameovercount--;
			if (gameovercount <= 0) {
				gameflag = 1;
				if (stagekind == 2) {//�{�X�X�e�[�W
					itemnum += 1;
				}
				break;
			}
		}

		///////�X�e�[�W���C������///////
		/*�v���C���[�̓����̌���*/
		if (movetime < 0) {
			demoselect = GetRand(99);
			if (demoselect < 25) {//�E����
				moveselect = 1;
				movetime = 60;
			}
			else if (demoselect < 50) {//������
				moveselect = 2;
				movetime = 60;
			}
			else if (demoselect < 70) {//�E�Z��
				moveselect = 1;
				movetime = 30;
			}
			else if (demoselect < 90) {//���Z��
				moveselect = 2;
				movetime = 30;
			}
			else {//�Î~
				moveselect = 0;
				movetime = 30;
			}
		}
		/*�v���C���[�̎��ۂ̓���*/
		Player.PlayerDemoRandamMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot, moveselect);

		/*�G�@*/
		Player.PlayerPosition(&ppx, &ppy);
		if (stagekind == 1) {//�m�[�}���X�e�[�W
			for (i = 0; i < MAXENEMY; i++) {
				NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, 0);
			}
			Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
		}
		else if (stagekind == 2) {//�{�X�X�e�[�W
			Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, 0, SEbreak, SElaser);
			Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
		}

		/////**���**/////
		DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[9], false);// �l�p�`��`��

		Player.PlayerShotColor(PlayerShotKind);
		Player.PlayerShotCombo(ShotCombonum);

		DrawString(515, 210, "���݂̒e�̎��", Cr[9]);
		DrawString(515, 250, "Z�V���b�g:\n\n\nX�V���b�g:\n\n\nC�V���b�g:", Cr[8]);
		for (i = 0; i < 3; i++) {
			DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "�R���{:%d", ShotCombonum[i]);
			switch (PlayerShotKind[i]) {
			case 0:
				DrawString(605, 250 + i * 54, "��", Cr[0]);
				break;
			case 1:
				DrawString(605, 250 + i * 54, "��", Cr[1]);
				break;
			case 2:
				DrawString(605, 250 + i * 54, "��", Cr[2]);
				break;
			case 3:
				DrawString(605, 250 + i * 54, "��", Cr[3]);
				break;
			case 4:
				DrawString(605, 250 + i * 54, "��", Cr[4]);
				break;
			case 5:
				DrawString(605, 250 + i * 54, "��", Cr[5]);
				break;
			case 6:
				DrawString(605, 250 + i * 54, "�Ԏ�", Cr[6]);
				break;
			case 7:
				DrawString(605, 250 + i * 54, "��", Cr[7]);
				break;
			default:
				DrawString(605, 250 + i * 54, "��", Cr[9]);
				break;
			}
		}

		DrawString(0, 420, "ESC�L�[:�Q�[���I��\nENTER�L�[:�f����ʂ��I�����ă^�C�g���ɖ߂�", Cr[9]);
		DrawFormatString(515, 30, Cr[8], "Demo");
		if (itemnum == 0) {
			DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
		}
		else {
			DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
		}

		if (Player.PlayerHP(0) > 15) {
			DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HP��`��
		}
		else if (Player.PlayerHP(0) > 7) {
			DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HP��`��
		}
		else {
			DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HP��`��
		}

		DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

		if (gamemode == 1) {//EASY
			DrawString(530, 60, "EASY", Cr[8]);
		}
		else if (gamemode == 2) {//NORMAL
			DrawString(530, 60, "NORMAL", Cr[8]);
		}
		else if (gamemode == 3) {//HARD
			DrawString(530, 60, "HARD", Cr[8]);
		}
		else if (gamemode == 4) {//UNKNOWN
			DrawString(530, 60, "UNKNOWN", Cr[8]);
		}

		/*���Ԍo��*/
		gamecount++;
		demotimecount--;
		movetime--;

		if (gamecount > 100000000)gamecount = 0;//�o�O�̖h�~
		if (gamecount > 150000000)*ErrorCheck = 4;//���Ԍo�߂�����
		ScreenFlip();

	}//�N���A����܂�

	// �T�E���h�n���h���̍폜
	DeleteSoundMem(BGM);

	return;
}

