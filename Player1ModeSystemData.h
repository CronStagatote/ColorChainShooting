#pragma once
#include "DxLib.h"

#define MAXENEMY 70
#define MAXMAPX 500
#define MAXMAPY 395 
#define AFTERGAMEOVERCOUNT 300

#define NEXTKEYTIME1 60

/////---**1Player mode**---/////
/////**�G�@�p�֐�(�m�[�}��)**/////
class Mode1Enemy {
private:
	int epx, epy;//x���W,y���W
	bool existflag;//���݂��Ă��邩
	bool esflag;//�e���ł���Ă��邩
	int ekind;//���
	int eax, eay, eskind;//�_���ꏊ
	int esx, esy;//�e�̍��W
	int nextshotcount;//���̒e���˂܂ł̊Ԋu

public:
	void StartSet(int gamemode);//�ŏ��̏���������
	void AppearEnemy(int x, int y, int kind);//�G�o���p�֐�
	void NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime);//�G�̓����Ɋւ��鏈��(�m�[�}���G)
	/*�G�@�̍��W�Ǝ��,�G�̒e�̍��W,���݃t���O��Ԃ�*/
	void EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag);
	void BreakEnemy();//�G��|�����Ƃ��̏���
	bool EnemyExistCheck() { return existflag; };//���݂��邩�ǂ���
	int EnemyKindCheck() { return ekind; };//��ނ͉���
	void EnemyShotFlagFALSE() { esflag = false; };//�e��������Ă��Ȃ���Ԃɂ���
	void NormalEnemyGraphicDrawing(int *errorcheck, int NormalEnemyGraphic[]);//�O���t�B�b�N�̂ݕ\��
};


/////**�G�@�p�֐�(�{�X)**/////
class Mode1Boss {
private:
	int epx, epy;//�{�X���̂�x���W,y���W
	int ekind;//���(11:grad 12:cron 13:erec 14:rain 15:staga)*staga��2PlayerMode�ł̂ݏo������̂Ō���
	int esx[10], esy[10], eskind[10];//�e�̍��W�Ǝ��
	bool esflag[10];//�e�����݂��Ă��邩
	bool existflag;//�{�X���̂����݂��Ă��邩
	int move, bosscolor;//�������̎w��A�F�̎w��
	int bosscount, protectcount;//���Ԑ���,���G����
	int maxhp, nowhp;//�ő�A����HP

	void Boss_Grad_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Cron_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Erec_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Rain_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS);
	void Boss_StagatoteSP_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS);

public:
	void StartSet(int stage, int gamemode);//�ŏ��̏����������Əo��
	/*�G�̓����Ɋւ��鏈��(�{�X�G)*/
	void BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime, int SEbreak, int SElaser);
	int BossHP(int damage);//�{�X�̎c��HP
	/*�G�@�̍��W,�G�̎��,�G�̒e�̍��W,�e�̎��,���G���Ԃ�Ԃ�*/
	void BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect);
	void BossShotFlagFALSE(int n);//�e��������Ă��Ȃ���Ԃɂ���
	int BossMoveSet(int n, bool changeflag);//false�Ȃ�n=0(�ω��Ȃ�)��1�`4(���]������)
	int BossColorCheck() { return bosscolor; };//�{�X�̐F��Ԃ�
	int BossPositionCheck(int *enemyx, int *enemyy);//�{�X�̈ʒu�Ɠ���Z�̎�ގ擾
	void BossPositionMove(int movex, int movey);//�ʒu�̋����ړ�
};


/////**���@�p�֐�**/////
class Mode1Player {
private:
	int ppx, ppy;//x���W,y���W
	int php, damagetime;//���@HP,�_���[�W��̕��A����
	bool psflag[3][3];//�e���ł���Ă��邩
	int pskind[3];//���݂̒e�̎��(9:�����Ȃ�)
	int psx[3][3], psy[3][3];//���ꂼ��̒e�̍��W
	bool keyflag[3];//�L�[��������Ă��邩
	int keyflagcount[3];//�L�[��������Ă��Ȃ���ԂɂȂ�܂ł̎���
	int pscombocount[3], pscombotimes[3];//�R���{���Ɣ{��
	int point, totalcombonum;//���_�ƃR���{��

public:
	void DebagColorSet();//�f�o�b�O�p�e�̐F�ݒ�֐�
	void StartSet();//�ŏ��̏���������
	int PlayerHP(int damage);//�v���C���[��HP�Ɋւ��鏈��
	void PlayerMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE);//�v���C���[�̓����Ɋւ��鏈��
	void PlayerShotColor(int PlayerShotKind[]);//�e�̎�ނ�Ԃ��֐�
	void PlayerShotCombo(int ShotComboNum[]);//�R���{����Ԃ��֐�
	void NormalStage_CollisionDetection(int *errorcheck, Mode1Enemy Enemy[], int *itemnum);//�����蔻��ƃ_���[�W
	int GetPoint() { return point; };//���_��Ԃ�
	void PlayerPosition(int *x, int *y) { *x = ppx; *y = ppy; };//�ꏊ��Ԃ�
	void BossStage_CollisionDetection(int *errorcheck, Mode1Boss Boss[], int stage, int gamemode);//�����蔻��ƃ_���[�W
	void ColorSet(int key, int color) { pskind[key] = color; };//�A�C�e��:�F�ւ�
	int TotalComboNum() { return totalcombonum; };
	/*�f����ʗp�v���[���[�̃����_���ȓ���(�����w��p�̐��l�͊O�Ŏw��)*/
	void PlayerDemoRandamMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE, int MoveSelect);
};


/////**�֐��W**/////
/*�f�o�b�O�p*/
void Mode1Player::DebagColorSet() {
	if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[0] = 0;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[0] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[0] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[0] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[0] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[0] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[0] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[0] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[0] = 9;
	}

	if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[1] = 0;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[1] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[1] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[1] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[1] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[1] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[1] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[1] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[1] = 9;
	}

	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[2] = 0;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[2] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[2] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[2] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[2] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[2] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[2] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[2] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[2] = 9;
	}

}//�f�o�b�O�p


/*�Q�[�������p*/
int InductionShotMotion(int count) {
	int n = 14;
	if (count % 48 < 6) {
		n = 14;
	}
	else if (count % 48 < 12) {
		n = 16;
	}
	else if (count % 48 < 18) {
		n = 17;
	}
	else if (count % 48 < 24) {
		n = 16;
	}
	else if (count % 48 < 30) {
		n = 14;
	}
	else if (count % 48 < 36) {
		n = 18;
	}
	else if (count % 48 < 42) {
		n = 19;
	}
	else {
		n = 18;
	}

	return n;
}

void Mode1Player::StartSet() {
	int i, j;
	ppx = 250;
	ppy = 355;
	php = 30;//HP�̏����l
	point = 0;
	for (i = 0; i < 3; i++) {
		pskind[i] = 9;
		pscombocount[i] = 0;
		pscombotimes[i] = 1;
		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			keyflag[i] = false;
			keyflagcount[i] = 0;
		}
		else {
			keyflag[i] = true;
			keyflagcount[i] = NEXTKEYTIME1;
		}
		for (j = 0; j < 3; j++) {
			psflag[i][j] = false;
			psx[i][j] = ppx + 12;
			psy[i][j] = ppy;
		}
	}
	totalcombonum = 0;
	damagetime = 0;
}//�ŏ��̏���

int Mode1Player::PlayerHP(int damage) {
	php -= damage;
	if (php < 0) {
		php = 0;
	}
	else if (php > 30) {
		php = 30;
	}

	if (damage > 0) {//�_���[�W���󂯂Ă���
		damagetime = 45;
	}
	else if (damage < -1) {//�A�C�e��:HP��
		damagetime = 15;
	}
	return php;
}//�v���C���[��HP�Ɋւ��鏈��

void Mode1Player::PlayerMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE) {
	int i, j;
	if (ppx > MAXMAPX + 100 || ppx < -100)*errorcheck = 2;//���E�֍s������

	/*�e�̃L�[�`�F�b�N*/
	if (CheckHitKey(KEY_INPUT_Z) == 0) {
		keyflag[0] = false;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_X) == 0) {
		keyflag[1] = false;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_C) == 0) {
		keyflag[2] = false;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == true) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = false;
		}
	}

	/*�{�^���ƑΉ����铮��*/
	if (php > 0) {//HP���s���Ă��Ȃ��Ȃ�
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX - 30)ppx = MAXMAPX - 30;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_A) == 1) {
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (CheckHitKey(KEY_INPUT_Z) == 1 && keyflag[0] == false) {
			keyflag[0] = true;
			keyflagcount[0] = NEXTKEYTIME1;
			if (psflag[0][0] == false) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][1] == false) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][2] == false) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (CheckHitKey(KEY_INPUT_X) == 1 && keyflag[1] == false) {
			keyflag[1] = true;
			keyflagcount[1] = NEXTKEYTIME1;
			if (psflag[1][0] == false) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][1] == false) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][2] == false) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (CheckHitKey(KEY_INPUT_C) == 1 && keyflag[2] == false) {
			keyflag[2] = true;
			keyflagcount[2] = NEXTKEYTIME1;
			if (psflag[2][0] == false) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][1] == false) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][2] == false) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
	}

	/*�O���t�B�b�N�\��*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, true);//�|����Ă��Ȃ��Ȃ�\��
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == true) {
				psy[i][j] -= 5;//���@�̒e�̓���
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], true);
				if (psy[i][j] < -50) {
					psflag[i][j] = false;
				}
			}
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (damagetime >= -5) {
		if (damagetime > 30 && gamemode == 3) {//HARD
			damagetime = 30;
		}
		else if (damagetime > 15 && gamemode == 4) {//UNKNOWN
			damagetime = 15;
		}
		damagetime--;
	}

}//�v���C���[�̓����Ɋւ��鏈��(�e��)

void Mode1Player::PlayerShotColor(int PlayerShotKind[]) {
	for (int i = 0; i < 3; i++) {
		PlayerShotKind[i] = pskind[i];
	}
}//�e�̎�ނ�Ԃ��֐�

void Mode1Player::PlayerShotCombo(int ShotComboNum[]) {
	for (int i = 0; i < 3; i++) {
		ShotComboNum[i] = pscombocount[i];
	}
}//�R���{����Ԃ��֐�

 /*�����蔻��ƃ_���[�W*/
void Mode1Player::NormalStage_CollisionDetection(int *errorcheck, Mode1Enemy Enemy[], int *itemnum) {
	int epx = 0, epy = 0, enemykind = 9;//�G�@�̍��W�Ǝ��
	int esx = 0, esy = 0;//�G�̒e�̍��W
	bool enemyflag = false, enemyshotflag = false;//���݃t���O
	int i, j, k;
	bool breakflag = false;

	for (i = 0; i < MAXENEMY; i++) {
		breakflag = false;
		/*�G�@�̏��擾*/
		Enemy[i].EnemyInfoReturn(&epx, &epy, &enemykind, &esx, &esy, &enemyflag, &enemyshotflag);
		if (enemyflag == true && enemykind == 9)*errorcheck = 4;//���݂��Ă���̂ɑ��݂��Ă��Ȃ�
		if (enemyflag == true) {//�G�@�����݂��Ă���Ƃ�
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psflag[j][k] == true) {//�e�����݂��Ă���Ƃ�
						if (psx[j][k] + 5 < epx + 28 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 28 && psy[j][k] + 16>epy + 4) {
							/*�e������������*/
							if (enemykind < 10) {//�o���A�V���b�g�ȊO
								if (pskind[j] == enemykind) {//�O��Ɠ���
									totalcombonum += 1;//�R���{���ɉ��Z
									pscombocount[j] += 1;//�R���{����1���₷
									pscombotimes[j] *= 2;//�R���{�{�����グ��
									if (pscombotimes[j] > 999999999)pscombotimes[j] = 999999999;//�G���[�h�~
									if (pscombocount[j] % 5 == 0 && pscombocount[j] > 0) {
										*itemnum += 1;
									}
								}
								else if (enemykind == 8) {//���i�R���{�ɉ��Z����Ȃ��j������
									point += 5;
								}
								else {//���ɓ���Ȃ��Ƃ͂Ȃ�����
									pskind[j] = enemykind;//�e��ς���
									pscombocount[j] = 1;//�R���{�����P�ɂ���
									pscombotimes[j] = 1;
								}

								/*���ʏ���*/
								Enemy[i].BreakEnemy();//�G��j��
								point += pscombotimes[j];//�|�C���g���Z
								if (point > 999999999)point = 999999999;//�G���[�h�~
							}
							psflag[j][k] = false;//�e������
							breakflag = true;
						}
					}
				}
				if (breakflag == true)break;
			}

			if (ppx + 8 < epx + 30 && ppx + 32 > epx + 2 && ppy + 20 < epy + 30 && ppy + 35 > epy + 2) {
				/*�G�@������������(�o���A�V���b�g�̂�)*/
				if (damagetime < 1)PlayerHP(3);//�_���[�W
				Enemy[i].BreakEnemy();//�G�@������
			}

		}
		if (enemyshotflag == true) {//�G�̒e�����݂��Ă���Ƃ�
			if (esx + 12 < ppx + 30 && esx + 20 > ppx + 10 && esy + 12 < ppy + 30 && esy + 20 > ppy + 6) {
				/*�G�̒e���Ԃ�����*/
				if (damagetime < 1)PlayerHP(1);//�_���[�W
				Enemy[i].EnemyShotFlagFALSE();
			}
		}
	}

}//�����蔻��m�F�p�֐�

void Mode1Player::BossStage_CollisionDetection(int *errorcheck, Mode1Boss Boss[], int stage, int gamemode) {
	int epx = 0, epy = 0, enemykind = 9;//�G�@�̍��W�Ǝ��
	int esx[10] = {}, esy[10] = {}, eskind[10] = {};//�G�̒e�̍��W
	int protecttime = 0;//���G����
	bool enemyshotflag[10] = {};//���݃t���O
	int i, j, k;
	int tmp = 0;//���u���p

	/*�G�@�̏��擾*/
	Boss[0].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
	if (Boss[0].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//���݂��Ă���̂ɑ��݂��Ă��Ȃ�
	if (Boss[0].BossHP(0) > 0) {//�G�@�����݂��Ă���Ƃ�
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (psflag[j][k] == true) {//�e�����݂��Ă���Ƃ�
					if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
						/*�e������������*/
						if (protecttime <= 0) {
							Boss[0].BossHP(1);//1�_���[�W��^����
							point += 3;

							if (Boss[0].BossColorCheck() >= 9 || Boss[0].BossColorCheck() < 0) {
								/*���ɉ����Ȃ�*/
							}
							else if (pskind[j] == Boss[0].BossColorCheck()) {//�O��Ɠ����F
								pscombocount[j] += 1;//�R���{����1���₷
							}
							else {//�O��ƈႤ�F
								pskind[j] = Boss[0].BossColorCheck();//�e��ς���
								pscombocount[j] = 1;//�R���{�����P�ɂ���
								pscombotimes[j] = 1;
							}

							point += pscombocount[j];//�{�[�i�X�|�C���g
							if (Boss[0].BossHP(0) == 0) {
								if (stage != 11)point += 100 * gamemode;
								else if (stage == 11)point += 1000 * gamemode;
							}
						}
						psflag[j][k] = false;
					}
				}
			}
		}
	}
	for (i = 0; i < 10; i++) {
		if (enemyshotflag[i] == true) {//�G�̒e�����݂��Ă���Ƃ�
			if (esx[i] + 12 < ppx + 30 && esx[i] + 20 > ppx + 10 && esy[i] + 12 < ppy + 30 && esy[i] + 20 > ppy + 6) {
				/*�G�̒e���Ԃ�����*/
				if (damagetime <= 0) {
					if (eskind[i] >= 20 && eskind[i] < 50) {
						PlayerHP(3);//3�_���[�W
						Boss[0].BossShotFlagFALSE(i);
					}
					else {//�ʏ�̃_���[�W
						PlayerHP(1);//�_���[�W
						Boss[0].BossShotFlagFALSE(i);
					}
				}
			}
		}
	}

	/*���g�ɂ���*/
	if (stage == 11 || stage == 16) {
		Boss[1].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
		if (Boss[1].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//���݂��Ă���̂ɑ��݂��Ă��Ȃ�
		if (Boss[1].BossHP(0) > 0) {//�G�@�����݂��Ă���Ƃ�
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psflag[j][k] == true) {//�e�����݂��Ă���Ƃ�
						if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
							/*�e������������*/
							if (stage == 11)Boss[1].BossMoveSet(gamemode, false);
							psflag[j][k] = false;
						}
					}
				}
			}
		}
		for (i = 0; i < 10; i++) {
			if (enemyshotflag[i] == true) {//�G�̒e�����݂��Ă���Ƃ�
				if (esx[i] + 12 < ppx + 30 && esx[i] + 20 > ppx + 10 && esy[i] + 12 < ppy + 30 && esy[i] + 20 > ppy + 6) {
					/*�G�̒e���Ԃ�����*/
					if (damagetime <= 0) {
						if (eskind[i] >= 20 && eskind[i] < 50) {
							PlayerHP(3);//3�_���[�W
							Boss[1].BossShotFlagFALSE(i);
						}
						else {//�ʏ�̃_���[�W
							PlayerHP(1);//�_���[�W
							Boss[1].BossShotFlagFALSE(i);
						}
					}
				}
			}
		}
	}

}//�����蔻��m�F�p�֐�

void Mode1Player::PlayerDemoRandamMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE, int MoveSelect) {
	int i, j;
	if (ppx > MAXMAPX + 100 || ppx < -100)*errorcheck = 2;//���E�֍s������

	/*�V���b�g�̌���*/
	bool Zshot = false, Xshot = false, Cshot = false;
	int tmprandam = 0;
	tmprandam = GetRand(100);
	if (tmprandam  < 2) {
		Zshot = true;
	}
	tmprandam = GetRand(100);
	if (tmprandam < 20 && tmprandam  >= 18) {
		Xshot = true;
	}
	tmprandam = GetRand(100);
	if (tmprandam < 56 && tmprandam >= 54) {
		Cshot = true;
	}

	/*����*/
	if (php > 0) {//HP���s���Ă��Ȃ��Ȃ�
		if (MoveSelect == 1) {//�E
			ppx += 3;
			if (ppx > MAXMAPX - 30)ppx = MAXMAPX - 30;
		}
		if (MoveSelect == 2) {//��
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (Zshot = true) {
			keyflag[0] = true;
			keyflagcount[0] = NEXTKEYTIME1;
			if (psflag[0][0] == false) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][1] == false) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][2] == false) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (Xshot = true) {
			keyflag[1] = true;
			keyflagcount[1] = NEXTKEYTIME1;
			if (psflag[1][0] == false) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][1] == false) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][2] == false) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (Cshot = true) {
			keyflag[2] = true;
			keyflagcount[2] = NEXTKEYTIME1;
			if (psflag[2][0] == false) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][1] == false) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][2] == false) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
	}

	/*�O���t�B�b�N�\��*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, true);//�|����Ă��Ȃ��Ȃ�\��
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == true) {
				psy[i][j] -= 5;//���@�̒e�̓���
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], true);
				if (psy[i][j] < -50) {
					psflag[i][j] = false;
				}
			}
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (damagetime >= -5) {
		if (damagetime > 30 && gamemode == 3) {//HARD
			damagetime = 30;
		}
		else if (damagetime > 15 && gamemode == 4) {//UNKNOWN
			damagetime = 15;
		}
		damagetime--;
	}
}

void Mode1Enemy::StartSet(int gamemode) {//�ŏ��̏���
	epx = 0;
	epy = 0;
	eskind = 0;
	existflag = false;
	esflag = false;
	ekind = 9;
	eax = epx;
	eay = epy;
	esx = epx;
	esy = epy;
	if (gamemode == 1) {//EASY
		nextshotcount = 540 + GetRand(1200);
	}
	else if (gamemode = 2) {//NORMAL
		nextshotcount = 135 + GetRand(600);
	}
	else if (gamemode == 3) {//HARD
		nextshotcount = 45 + GetRand(300);
	}
	else if (gamemode == 4) {//UNKNOWN
		nextshotcount = 15 + GetRand(150);
	}
}

void Mode1Enemy::AppearEnemy(int x, int y, int kind) {//�o���ꏊ�Ǝ�ނ����߂ČĂяo��
	if (existflag == false) {
		epx = x;
		epy = y;
		existflag = true;
		esflag = false;
		ekind = kind;
		eax = epx;
		eay = epy;
		esx = epx;
		esy = epy;
	}
}//�G�o���p�֐�

void Mode1Enemy::BreakEnemy() {
	existflag = false;
}//�G��|�����Ƃ��̏���

void Mode1Enemy::NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime) {
	/*�O���t�B�b�N*/
	if (esflag == true) {//�e�����݂���Ȃ�
		DrawGraph(esx, esy, NormalEnemyGraphic[11], true);//�e
	}

	if (existflag == true) {//�@�̂����݂���Ȃ�
		NormalEnemyGraphicDrawing(errorcheck, NormalEnemyGraphic);

		if (itemtime < 1) {
			/*�ړ�*/
			if (ekind == 10) {//�o���A�V���b�g
				epy += 1;
				if (epy > MAXMAPY - 28) {
					BreakEnemy();//���[���B���ɏ���
				}
			}
			else if (ekind == 11) {//�o���A
				/*�����Ȃ�*/
			}
			else if (count % 3 == 0) {
				if (gamemode >= 3) {//HARD�ȏ�
					if (count % 120 < 60) {
						epx += 1;
					}
					else {
						epx -= 1;
					}
				}
				else if (gamemode == 1) {
					if (count % 120 >= 30 && count % 120 < 90) {
						if (count % 6 == 0)
							epx += 1;
					}
					else {
						if (count % 6 == 0) {
							epx -= 1;
						}
					}
				}
				else if (gamemode == 2) {//Normal(������蓮��)
					if (count % 360 >= 90 && count % 360 < 270) {
						if (count % 6 == 0) {
							epx += 1;
						}
					}
					else {
						if (count % 6 == 0) {
							epx -= 1;
						}
					}
				}
			}


			if (gamemode == 20 || ekind >= 10) {//�e�������Ȃ�
				return;
			}

			/*�e����*/
			nextshotcount--;
			if (nextshotcount < 0) {//��莞�Ԃ��Ƃɔ���
				if (gamemode <= 1) {//EASY
					nextshotcount = 420 + GetRand(900);//���Ԃ̃��Z�b�g
				}
				else if (gamemode == 2) {//NORMAL
					nextshotcount = 270 + GetRand(540);//���Ԃ̃��Z�b�g
				}
				else if (gamemode == 3) {//HARD
					if (esflag == false) {
						nextshotcount = 60 + GetRand(360);
					}
				}
				else if (gamemode == 4) {//UNKNOWN
					nextshotcount = GetRand(180);
				}

				if (esflag == false) {//�e��������Ă��Ȃ��Ȃ�
					esx = epx;
					esy = epy;
					eax = ppx;
					eay = ppy;
					if (gamemode == 4 && ekind != 8) {//UNKNOWN
						esflag = true;
						eskind = GetRand(9) + 1;
						if (eskind == 10) {
							eax = 3 * (eax - esx) / (eay - esy);
							eskind = 99;
						}
					}
					else {
						if (ekind != 6)esflag = true;//�e������
					}

					if (gamemode <= 3 || ekind == 8) {//EASY || NORMAL || HARD
						/*�_���ꏊ*/
						switch (ekind) {
						case 0://��
							eskind = 1;
							break;
						case 1://��
							if (ppx < epx - 200) {
								eax -= 30;
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 4;
							}
							else if (ppx > epx + 200) {
								eax -= 30;
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 3;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 1;
							}
							else {
								eskind = 2;
							}
							break;
						case 2://��
							if (ppx < epx - 200) {
								eax += 30;
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 1;
							}
							else if (ppx > epx + 200) {
								eax += 30;
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 9;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 5;
							}
							else {
								eskind = 3;
							}
							break;
						case 3://��
							if (ppx < epx - 200) {
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 80) {//80�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 30) {//30�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 200) {
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 80) {//80�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 30) {//30�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
							break;
						case 4://��
							eskind = 2;
							break;
						case 5://��
							eskind = 3;
							break;
						case 6://�Ԏ�
							break;
						case 7://��
							if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1) {
								if (ppx < epx - 200) {
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150�ȏ㍶
									eskind = 6;
								}
								else if (ppx < epx - 80) {//80�ȏ㍶
									eskind = 4;
								}
								else if (ppx < epx - 30) {//30�ȏ㍶
									eskind = 2;
								}
								else if (ppx > epx + 200) {
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150�ȏ�E
									eskind = 7;
								}
								else if (ppx > epx + 80) {//80�ȏ�E
									eskind = 5;
								}
								else if (ppx > epx + 30) {//30�ȏ�E
									eskind = 3;
								}
								else {
									eskind = 1;
								}
							}
							else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
								if (ppx < epx - 200) {
									eax += 30;
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150�ȏ㍶
									eskind = 4;
								}
								else if (ppx < epx - 100) {//100�ȏ㍶
									eskind = 2;
								}
								else if (ppx < epx - 50) {//50�ȏ㍶
									eskind = 1;
								}
								else if (ppx > epx + 200) {
									eax += 30;
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150�ȏ�E
									eskind = 9;
								}
								else if (ppx > epx + 100) {//100�ȏ�E
									eskind = 7;
								}
								else if (ppx > epx + 50) {//50�ȏ�E
									eskind = 5;
								}
								else {
									eskind = 3;
								}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
								if (ppx < epx - 200) {
									eax -= 30;
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150�ȏ㍶
									eskind = 8;
								}
								else if (ppx < epx - 100) {//100�ȏ㍶
									eskind = 6;
								}
								else if (ppx < epx - 50) {//50�ȏ㍶
									eskind = 4;
								}
								else if (ppx > epx + 200) {
									eax -= 30;
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150�ȏ�E
									eskind = 5;
								}
								else if (ppx > epx + 100) {//100�ȏ�E
									eskind = 3;
								}
								else if (ppx > epx + 50) {//50�ȏ�E
									eskind = 1;
								}
								else {
									eskind = 2;
								}
							}
							else {
								if (ppx < epx - 200) {
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150�ȏ㍶
									eskind = 6;
								}
								else if (ppx < epx - 80) {//80�ȏ㍶
									eskind = 4;
								}
								else if (ppx < epx - 30) {//30�ȏ㍶
									eskind = 2;
								}
								else if (ppx > epx + 200) {
									eskind = 99;
									if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150�ȏ�E
									eskind = 7;
								}
								else if (ppx > epx + 80) {//80�ȏ�E
									eskind = 5;
								}
								else if (ppx > epx + 30) {//30�ȏ�E
									eskind = 3;
								}
								else {
									eskind = 1;
								}
							}
							break;
						case 8://��
							if (ppx < epx - 200) {
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 80) {//80�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 30) {//30�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 200) {
								eskind = 99;
								if (eay != esy) {//�_���ꏊ�����e�������E,����0���Z��h��
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 80) {//80�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 30) {//30�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
							break;
						case 9://�D
							break;
						case 10://�o���A�V���b�g
							break;
						}
					}
				}
			}
		}
	}

	if (esflag == true) {//�e��������Ă���Ƃ�
		switch (eskind) {
		case 0://�e�������Ȃ�
			break;
		case 1://�^��
			esy += 3;
			break;
		case 2://0.5��
			esy += 3;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 3://0.5�E
			esy += 3;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 4://1��
			esy += 3;
			esx -= 1;
			break;
		case 5://1�E
			esy += 3;
			esx += 1;
			break;
		case 6://1.5��
			esy += 3;
			esx -= 1;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 7://1.5�E
			esy += 3;
			esx += 1;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 8://2��
			esy += 3;
			esx -= 2;
			break;
		case 9://2�E
			esy += 3;
			esx += 2;
			break;
		case 10://2.5��
			esy += 3;
			esx -= 2;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 11://2.5�E
			esy += 3;
			esx += 2;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 99://�_��
			esy += 3;
			esx += eax;
			break;
		}


		if (esy > MAXMAPY - 30 || esx > MAXMAPX - 15 || esx < -10)esflag = false;// �[�ɓ��B���ɏ�����
	}

}//�G�̓����ƒe�Ɋւ��鏈��(�m�[�}���G) 

void Mode1Enemy::EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*shotx = esx;
	*eshoty = esy;
	*enemyflag = existflag;
	*shotflag = esflag;
}//�G�@�̍��W,�G�̒e�̍��W,���݃t���O��Ԃ�

void Mode1Enemy::NormalEnemyGraphicDrawing(int *errorcheck, int NormalEnemyGraphic[]) {
	if (existflag == true) {//�@�̂����݂���Ȃ�
		if (ekind == 11) {
			DrawGraph(epx, epy, NormalEnemyGraphic[10], true);//�@��
		}
		else if (ekind < 11) {
			DrawGraph(epx, epy, NormalEnemyGraphic[ekind], true);//�@��
		}
		else {
			*errorcheck = -9;
		}
	}
}

void Mode1Boss::StartSet(int stage, int gamemode) {
	existflag = true;
	epx = 250;
	epy = 30;
	move = 0;
	bosscolor = 9;//�G���[�h�~(�F�Ȃ�)
	maxhp = 1;//�G���[�h�~(HP1)
	bosscount = 150;//���Ԑ���
	protectcount = 90;//���G����
	switch (stage) {
	case 0://�o�����Ȃ�
		maxhp = 0;
		existflag = false;
		break;
	case 3:
		ekind = 11;
		bosscolor = 4;
		if (gamemode == 1) {//EASY
			maxhp = 20;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 25;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 30;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 33;
		}
		break;
	case 6:
		ekind = 12;
		bosscolor = 3;
		if (gamemode == 1) {//EASY
			maxhp = 28;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 35;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 42;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 45;
		}
		break;
	case 9:
		ekind = 13;
		bosscolor = 2;
		if (gamemode == 1) {//EASY
			maxhp = 38;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 48;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 58;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 62;
		}
		break;
	case 11:
		ekind = 14;
		epy = 70;
		bosscolor = GetRand(7);
		if (gamemode == 1) {//EASY
			maxhp = 56;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 70;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 84;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 100;
		}
		break;
	case 16://HARD�ȏ�  SP�X�e�[�W(������̓X�e�[�W16)
		ekind = 16;
		bosscolor = 9;//���F
		if (gamemode == 3) {//HARD
			maxhp = 66;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 80;
		}
		break;
	case 99://�X�e�[�W11�̕��g
		ekind = 99;
		bosscolor = 10;//���F���F�ω��Ȃ�
		maxhp = 10;
		move = 100;
		epy = 70;
		protectcount = 180;
		break;
	case 100://SP�X�e�[�W�̕⏕�p�[�c
		ekind = 100;
		bosscolor = 10;//���F���F�ω��Ȃ�
		maxhp = 7;
		move = 0;
		epy = 15;
		protectcount = 10;
		break;
	default://����ȊO���{�X�X�e�[�W�ɂȂ邱�Ƃ͂Ȃ�
		return;
	}
	nowhp = maxhp;
	for (int i = 0; i < 10; i++) {
		esx[i] = epx;
		esy[i] = epy;
		eskind[i] = 0;
		esflag[i] = false;
	}
}//�ŏ��̏����������Əo��

void Mode1Boss::BossShotFlagFALSE(int n) {
	eskind[n] = 0;
	esflag[n] = false;
}

void Mode1Boss::BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime, int SEbreak, int SElaser) {
	int i;
	//�F�쐬
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//��
	Cr[1] = GetColor(15, 15, 255);//��
	Cr[2] = GetColor(255, 255, 15);//��
	Cr[3] = GetColor(15, 255, 15);//��
	Cr[4] = GetColor(255, 156, 0);//��
	Cr[5] = GetColor(159, 15, 255);//��
	Cr[6] = GetColor(218, 0, 224);//�Ԏ�
	Cr[7] = GetColor(35, 255, 255);//��
	Cr[8] = GetColor(240, 240, 240);//��
	Cr[9] = GetColor(128, 128, 128);//�D

	/*�X�e�[�W�`�F�b�N�Ɩ��O�\���A�G�̓����Ȃ�*/
	switch (ekind) {
	case 11:
		DrawFormatString(5, 3, Cr[bosscolor], "Grad:HP");//�ԁA���A��
		/*�G�̓���*/
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_Grad_Move(errorcheck, count, ppx, ppy, gamemode);//Grad�̓���
			}
		}
		break;
	case 12:
		DrawFormatString(5, 3, Cr[bosscolor], "Cron:HP");//���A��A��
		/*�G�̓���*/
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_Cron_Move(errorcheck, count, ppx, ppy, gamemode);//Cron�̓���
			}
		}
		break;
	case 13:
		DrawFormatString(5, 3, Cr[bosscolor], "Erec:HP");//�A���A��
		/*�G�̓���*/
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_Erec_Move(errorcheck, count, ppx, ppy, gamemode);//Erec�̓���
			}
		}
		break;
	case 14:
		DrawFormatString(5, 3, Cr[bosscolor], "Rain:HP");//�S�F
		/*�G�̓���*/
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_Rain_Move(errorcheck, count, ppx, ppy, gamemode, true);//Rain�̓���
			}
		}
		break;
	case 15://1PlayerMode�ł͂Ȃ�
		break;
	case 16://BOSSRUSH�̂� Stagatote_SP
		DrawFormatString(5, 3, Cr[9], "Stagatote_SP:HP");//���F
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_StagatoteSP_Move(errorcheck, count, ppx, ppy, gamemode, true);//Stagatote_SP�̓���
			}
		}

		break;
	case 99://ekind=14:Rain�̕��g
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_Rain_Move(errorcheck, count, ppx, ppy, gamemode, false);//Rain�̕��g�̓���
			}
		}
		break;
	case 100://BOSSRUSH�̂� Stagatote_SP�̕⏕�p�[�c
		if (itemtime < 1) {
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				Boss_StagatoteSP_Move(errorcheck, count, ppx, ppy, gamemode, false);//Stagatote_SP�⏕�̓���
			}
		}
		break;
	default:
		*errorcheck = 6;//�Ăяo����Ȃ��͂�
		break;
	}

	/*HP�\���Ƌ@�̕\��*/
	if (ekind == 99) {
		if (nowhp > 0) {
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[5], true);//�@��
		}
		else {
			existflag = false;
		}
	}
	else if (ekind == 16) {
		if (nowhp > 0) {
			DrawBox(142, 7, 142 + 350 * nowhp / maxhp, 15, Cr[3], true);// HP��`��
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[4], true);//�@��
		}
		else {
			if (existflag == true) {
				protectcount = 20;//�����G�t�F�N�g�̎���
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (protectcount > 0) {
				DrawGraph(epx, epy, NormalEnemyGraphic[15], true);//�j��
			}
			existflag = false;
		}
	}
	else if (ekind == 100) {
		if (nowhp > 0) {
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, NormalEnemyGraphic[9], true);//�@��
		}
		else {
			existflag = false;
		}
	}
	else {
		if (nowhp > 0) {
			if (bosscolor < 9) {
				DrawBox(72, 7, 71 + 400 * nowhp / maxhp, 15, Cr[bosscolor], true);// HP��`��
			}
			else {
				DrawBox(72, 7, 71 + 400 * nowhp / maxhp, 15, Cr[3], true);// HP��`��
			}
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[ekind - 11], true);//�@��
		}
		else {
			if (existflag == true) {
				protectcount = 20;//�����G�t�F�N�g�̎���
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (protectcount > 0) {
				DrawGraph(epx, epy, NormalEnemyGraphic[15], true);//�j��
			}
			existflag = false;
		}
	}

	/*�e�̓����ƕ`��*/
	for (i = 0; i < 10; i++) {
		if (esflag[i] == true) {
			switch (eskind[i]) {
			case 0://��
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 1://������
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 2://�����E
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 3://��
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 4://�E
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 5://���i�����j
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 6://���Ȃ荶
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 7://���Ȃ�E
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 8://��������
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 9://�������E
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//�e
				break;
			case 10://��
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 18://������
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 19://�����E
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 13://��
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 14://�E
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 15://���i�����j
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 16://���Ȃ荶
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 17://���Ȃ�E
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 11://��������
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 12://�������E
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//�e
				break;
			case 20://�U�����e
				esy[i] += 2;
				if (esx[i] < ppx)esx[i] += 2;
				else if (esx[i] > ppx)esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[InductionShotMotion(count)], true);//�e
				break;
			case 21://�����r�[��
				DrawBox(esx[i] + 2, epy + 30, esx[i] + 12, MAXMAPY, Cr[7], true);
				PlaySoundMem(SElaser, DX_PLAYTYPE_BACK);//SE
				break;
			case 22://�̓�����
				break;
			case 23://�U�����e
				esy[i] += 2;
				if (esx[i] < ppx)esx[i] += 1;
				else if (esx[i] > ppx)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[InductionShotMotion(count)], true);//�e
				break;
			case 24://�m�[�}���G
				break;
			case 25://�o���A�V���b�g
				break;
			case 51://��
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 52://0.5��
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 53://0.5�E
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 54://1��
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 55://1�E
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 56://1.5��
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 57://1.5�E
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 58://2��
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 59://2�E
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 60://��������
				esy[i] += 10;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 61://������
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 62://����0.5��
				esy[i] += 7;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 63://����0.5�E
				esy[i] += 7;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 64://����1��
				esy[i] += 7;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 65://����1�E
				esy[i] += 7;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 66://����1.5��
				esy[i] += 7;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 67://����1.5�E
				esy[i] += 7;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 68://����2��
				esy[i] += 7;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			case 69://����2�E
				esy[i] += 7;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//�e
				break;
			default:
				break;
			}
			if (esy[i] > MAXMAPY - 30 || esx[i] > MAXMAPX || esx[i] < -10)esflag[i] = false;// �[�ɓ��B���ɏ�����
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (protectcount > -5)protectcount--;


}//�{�X�̓����Ɋւ��鏈��

/*�{�X�̓���(BossMove ���֐�)*/
void Mode1Boss::Boss_Grad_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	/*�F�ւ�*/
	if (count % 400 == 0) {
		if (bosscolor == 4) {//��>��
			bosscolor = 0;
		}
		else if (bosscolor == 0) {//��>��
			bosscolor = 2;
		}
		else {//��>��
			bosscolor = 4;
		}
	}

	/*�����̋L�q*/
	if (move == 0) {
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			move = 1;
		}

		if (count % 80 < 35) {
			if (epx < MAXMAPX - 30)epx += 5;
			if (gamemode == 1) {//EASY
				epx -= 2;
			}
		}
		else {
			if (epx > 0)epx -= 5;
			if (gamemode == 1) {//EASY
				epx += 2;
			}
		}
	}
	else if (move == 1) {
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 2;
		}
	}
	else if (move == 2) {//�ʏ�U��1
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 12;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 0;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 0;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 0;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 0;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 0;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 0;
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 0;
				esx[6] = epx + 3;
				esy[6] = epy;
			}

			if (gamemode >= 3) {//HARD�ȏ�
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 1;
					esx[7] = epx;
					esy[7] = epy;
				}
				if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx;
					esy[8] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 3;
			if (gamemode == 4) {//UNKNOWN
				move = 7;
			}
			bosscount = 90;
		}
	}
	else if (move == 3) {//�ʏ�U��2
		if (epx < MAXMAPX - 30 && count % 2 == 0)epx += 1;
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 15;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 1;
				esx[0] = epx;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 1;
				esx[1] = epx;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 1;
				esx[2] = epx;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 1;
				esx[3] = epx;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 1;
				esx[4] = epx;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 1;
				esx[5] = epx;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 1;
				esx[6] = epx;
				esy[6] = epy;
			}

			if (gamemode == 4) {//UNKNOWN
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 0;
					esx[7] = epx;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = 4;
					esx[9] = epx;
					esy[9] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 4;
			bosscount = 90;
		}
	}
	else if (move == 4) {//�ʏ�U��3
		if (epx > 0 && count % 2 == 0)epx -= 1;
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 15;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 2;
				esx[0] = epx;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 2;
				esx[1] = epx;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 2;
				esx[2] = epx;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 2;
				esx[3] = epx;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 2;
				esx[4] = epx;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 2;
				esx[5] = epx;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 2;
				esx[6] = epx;
				esy[6] = epy;
			}

			if (gamemode == 4) {//UNKNOWN
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 0;
					esx[7] = epx;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 1;
					esx[8] = epx;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = 3;
					esx[9] = epx;
					esy[9] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 5;
			bosscount = 90;
		}
	}
	else if (move == 5) {
		bosscount--;
		if (bosscount < 0) {
			bosscount = 300;
			move = 6;
		}

		if (count % 50 < 25) {
			if (epx < MAXMAPX - 30)epx += 4;
		}
		else {
			if (epx > 0)epx -= 4;
		}
	}
	else if (move == 6) {//�U���e
		esflag[0] = true;
		eskind[0] = 20;
		esx[0] = epx;
		esy[0] = epy;
		bosscount = 120;
		move = 0;
	}
	else if (move == 7) {
		esflag[9] = true;
		eskind[9] = 20;
		esx[9] = epx;
		esy[9] = epy;
		bosscount = 120;
		move = 3;
	}
}

void Mode1Boss::Boss_Cron_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	int i, Cr = GetColor(35, 255, 255);//���[�U�[���ߗp

	/*�F�ւ�*/
	if (count % 400 == 0) {
		if (bosscolor == 3) {//��>��
			bosscolor = 5;
		}
		else if (bosscolor == 5) {//��>��
			bosscolor = 7;
		}
		else {//��>��
			bosscolor = 3;
		}
	}

	/*�����̋L�q*/
	if (move < 10) {
		if (gamemode == 4 && nowhp < maxhp * 3 / 5) {//UNKNOWN && HP60%����
			move = 10;
		}
	}

	if (move == 0) {//�ʏ�1 ���ɘA��
		if (ppx < epx - 3) {
			if (epx > 0)epx -= 1;
		}
		else if (ppx > epx - 3) {
			if (epx < MAXMAPX - 30)epx += 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 5;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 5;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 5;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 5;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 5;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 1;
			bosscount = 90;
		}
	}
	else if (move == 1) {//�ʏ�2 ������
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			if (gamemode == 1) {//EASY
				bosscount = 150;
			}
			for (i = 0; i < 5; i++) {
				if (gamemode == 1) {//EASY
					if (i == 3)break;
				}
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (gamemode >= 3 && bosscount == 45) {//HARD�ȏ�
			for (i = 5; i < 10; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					if (i == 5) {
						eskind[i] = 0;
					}
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
	}
	else if (move == 2) {//���[�U�[�O����
		if (epx + 5 < ppx) {
			epx += 2;
			if (gamemode >= 3) {//HARD�ȏ�
				epx += 1;
			}
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
			if (gamemode >= 3) {//HARD�ȏ�
				epx -= 1;
			}
		}
		else {
			move = 3;
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD�ȏ�
				bosscount = 15;
			}
		}
	}
	else if (move == 3) {//���[�U�[�O����
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 4;
		}
	}
	else if (move == 4) {//���[�U�[
		bosscount--;
		esflag[0] = true;
		eskind[0] = 21;
		esx[0] = epx + 10;
		esy[0] = ppy;
		if (bosscount < 0) {
			esflag[0] = false;
			move = 5;
		}
	}
	else if (move == 5) {//�^�񒆂ɖ߂�
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 0;
		}
	}
	else if (move == 10) {//UNKNOWN�@�ʏ�2 ������
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;

			for (i = 0; i < 5; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}

		if (bosscount == 45) {
			for (i = 6; i < 10; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i - 5;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 11;
			bosscount = 90;
		}
	}
	else if (move == 11) {//UNKNOWN�@���[�U�[�O����
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 12;
			bosscount = 12;
		}
	}
	else if (move == 12) {//UNKNOWN ���[�U�[�O����
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 13;
		}
	}
	else if (move == 13) {//UNKNOWN ���[�U�[
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 14;
		}
	}
	else if (move == 14) {//UNKNOWN �ʏ�1 ����
		if (ppx < epx - 3) {
			if (epx > 0)epx -= 1;
		}
		else if (ppx > epx - 3) {
			if (epx < MAXMAPX - 30)epx += 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 5;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 5;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 5;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 5;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 5;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 15;
			bosscount = 90;
		}
	}
	else if (move == 15) {//UNKNOWN�@���[�U�[�O����
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 16;
			bosscount = 12;
		}
	}
	else if (move == 16) {//UNKNOWN ���[�U�[�O����
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 17;
		}
	}
	else if (move == 17) {//UNKNOWN ���[�U�[
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 18;
		}
	}
	else if (move == 18) {//UNKNOWN �ʏ�3 9����
		if (1) {}
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0 && esflag[0] == false) {
			bosscount = 180;

			for (i = 0; i < 10; i++) {
				if (esflag[i] == false && i != 5) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
	}
	else if (move == 19) {//UNKNOWN�@���[�U�[�O����
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 20;
			bosscount = 12;
		}
	}
	else if (move == 20) {//UNKNOWN ���[�U�[�O����
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 21;
		}
	}
	else if (move == 21) {//UNKNOWN ���[�U�[
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 10;
		}
	}
}

void Mode1Boss::Boss_Erec_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	int i;
	/*�F�ւ�*/
	if (count % 400 == 0) {
		if (bosscolor == 2) {//��>��
			bosscolor = 1;
		}
		else if (bosscolor == 1) {//��>��
			bosscolor = 5;
		}
		else {//��>��
			bosscolor = 2;
		}
	}

	/*�����̋L�q*/
	if (move < 3) {
		if (gamemode == 4 && nowhp < maxhp / 2) {//UNKNOWN && HP50%����
			move = 10;
		}
	}
	switch (move) {
	case 0://�ʏ�1 �����_���U�� �E�ړ�
		epx += 2;
		if (gamemode == 1) {//EASY
			epx -= 1;
		}
		if (epx > 400) {
			move = 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD�ȏ�
				bosscount = 15;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[9] = true;
				eskind[9] = GetRand(7);
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
		break;
	case 1://�ʏ�1 �����_���U�� ���ړ�
		epx -= 2;
		if (gamemode == 1) {//EASY
			epx += 1;
		}
		if (epx < 100) {
			move = 0;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD�ȏ�
				bosscount = 15;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false && gamemode >= 3) {//HARD�ȏ�
				esflag[9] = true;
				eskind[9] = GetRand(7);
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
		break;
	case 2://�ʏ�2 ������ �E�ړ�
		epx += 1;
		if (epx > 350) {
			move = 3;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			if (gamemode == 1) {//EASY
				bosscount = 120;
			}

			if (gamemode < 3) {//EASY || NORMAL
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 0;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[1] = 1;
					}
					else {//�������E��
						eskind[1] = 2;
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[2] = 3;
					}
					else {//�������E��
						eskind[2] = 4;
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[3] = 6;
					}
					else if (ppx - 5 > epx) {//�E���ɂ���
						eskind[3] = 7;
					}
					else {//����
						eskind[3] = 1;
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[4] = 8;
					}
					else if (ppx - 5 > epx) {//�E���ɂ���
						eskind[4] = 9;
					}
					else {//����
						eskind[4] = 3;
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}
			else {//HARD�ȏ�
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
		}
		if (count % 600 == 0) {
			move = 4;
			bosscount = 90;
		}
		break;
	case 3://�ʏ�2 ������ ���ړ�
		epx -= 1;
		if (epx < 150) {
			move = 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			if (gamemode == 1) {//EASY
				bosscount = 120;
			}

			if (gamemode < 3) {//EASY || NORMAL
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 0;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[1] = 1;
					}
					else {//�������E��
						eskind[1] = 2;
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[2] = 3;
					}
					else {//�������E��
						eskind[2] = 4;
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[3] = 6;
					}
					else if (ppx - 5 > epx) {//�E���ɂ���
						eskind[3] = 7;
					}
					else {//����
						eskind[3] = 1;
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					if (ppx + 5 < epx) {//�����ɂ���
						eskind[4] = 8;
					}
					else if (ppx - 5 > epx) {//�E���ɂ���
						eskind[4] = 9;
					}
					else {//����
						eskind[4] = 3;
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}
			else {//HARD�ȏ�
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

		}
		if (count % 600 == 0) {
			move = 4;
			bosscount = 90;
		}
		break;
	case 4://�ːi�O����			
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 8;
			bosscount = 25;
		}
		if (gamemode == 4) {//UNKNOWN 
			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
		}

		break;
	case 5://�ːi	
		epy += 5;
		if (gamemode == 2) {//NORMAL
			epy += 3;
		}
		else if (gamemode >= 3) {//HARD || UNKNOWN
			epy += 7;
		}
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 6;
		}
		break;
	case 6://�ːi�߂�
		epy -= 3;
		if (gamemode >= 3) {//HARD�ȏ�
			epy -= 5;
		}
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 7;
		}
		break;
	case 7://�����ɖ߂�
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 0;
		}
		break;
	case 8:
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 5;
		}
		break;
	case 10://UNKNOWN �ʏ�2 ������ �E�ړ�
		epx += 1;
		if (epx > 350) {
			move = 11;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 12;
			bosscount = 90;
		}
		break;
	case 11://UNKNOWN �ʏ�2 ������ ���ړ�
		epx -= 1;
		if (epx < 150) {
			move = 10;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 12;
			bosscount = 90;
		}
		break;
	case 12://UNKNOWN �ʏ�2 ������ �ːi�O����	
		if (epx + 5 < ppx) {
			epx += 1;
		}
		else if (epx - 5 > ppx) {
			epx -= 1;
		}
		else {
			move = 13;
			bosscount = 15;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		break;
	case 13://UNKNOWN �ːi�O����
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 14;
		}
		break;
	case 14://UNKNOWN �ːi
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 15;
		}
		break;
	case 15://UNKNOWN �ːi�߂�
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 16;
		}
		break;
	case 16://UNKNOWN �����ɖ߂�
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 17;
		}
		break;
	case 17://UNKNOWN �ʏ�1 �����_���U�� �E�ړ�
		epx += 2;
		if (epx > 400) {
			move = 18;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
		break;
	case 18://UNKNOWN �ʏ�1 �����_���U�� ���ړ�
		epx -= 2;
		if (epx < 100) {
			move = 17;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
		break;
	case 19://UNKNOWN �ʏ�1 �����_���U�� �ːi�O����	
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 20;
			bosscount = 15;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		break;
	case 20://UNKNOWN �ːi�O����
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 21;
		}
		break;
	case 21://UNKNOWN �ːi
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 22;
		}
		break;
	case 22://UNKNOWN �ːi�߂�
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 23;
		}
		break;
	case 23://UNKNOWN �����ɖ߂�
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 24;
		}
		break;
	case 24://UNKNOWN �ʏ�3 �����_��+4���� �E�ړ�
		epx += 1;
		if (epx > 400) {
			move = 25;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 26;
			bosscount = 90;
		}
		break;
	case 25://UNKNOWN �ʏ�3 �����_��+4���� ���ړ�
		epx -= 1;
		if (epx < 150) {
			move = 24;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 26;
			bosscount = 90;
		}
		break;
	case 26://UNKNOWN �ʏ�3 �����_��+4���� �ːi�O����	
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 27;
			bosscount = 15;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		break;
	case 27://UNKNOWN �ːi�O����
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 28;
		}
		break;
	case 28://UNKNOWN �ːi
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 29;
		}
		break;
	case 29://UNKNOWN �ːi�߂�
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 30;
		}
		break;
	case 30://UNKNOWN �����ɖ߂�
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 10;
		}
		break;
	default:
		move = 0;
		break;
	}
}

void Mode1Boss::Boss_Rain_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS) {
	int i, Cr = GetColor(35, 255, 255);//���[�U�[���ߗp

	if (trueBOSS == true) {//�{��
		/*�F�ւ�*/
		if (count % 250 == 0) {
			bosscolor = GetRand(7);//�����_��
		}

		/*�����̋L�q*/
		switch (move) {
		case 0:

			if (gamemode == 4) {//UNKNOWN
				move = 20;
			}

			epx += 2;
			if (gamemode == 1) {//EASY
				epx -= 1;
			}

			if (epx > 350) {
				move = 1;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				if (gamemode == 1) {//EASY
					bosscount = 100;
				}

				if (gamemode < 3) {//EASY || NORMAL
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 0;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					if (esflag[1] == false) {
						esflag[1] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[1] = 1;
						}
						else {//�������E��
							eskind[1] = 2;
						}
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					if (esflag[2] == false) {
						esflag[2] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[2] = 3;
						}
						else {//�������E��
							eskind[2] = 4;
						}
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					if (esflag[3] == false) {
						esflag[3] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[3] = 6;
						}
						else if (ppx - 5 > epx) {//�E���ɂ���
							eskind[3] = 7;
						}
						else {//����
							eskind[3] = 1;
						}
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					if (esflag[4] == false) {
						esflag[4] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[4] = 8;
						}
						else if (ppx - 5 > epx) {//�E���ɂ���
							eskind[4] = 9;
						}
						else {//����
							eskind[4] = 3;
						}
						esx[4] = epx + 3;
						esy[4] = epy;
					}
				}
				else {//HARD�ȏ�
					for (i = 0; i < 7; i++) {
						if (esflag[i] == false) {
							esflag[i] = true;
							if (i == 5) {
								eskind[i] = 9;
							}
							else if (i == 6) {
								eskind[i] = 8;
							}
							else {
								eskind[i] = i;
							}
							esx[i] = epx + 3;
							esy[i] = epy;
						}
					}
				}

			}
			if (count % 600 == 0) {
				move = 2;
				bosscount = 90;
			}
			break;
		case 1:
			epx -= 2;
			if (gamemode == 1) {//EASY
				epx += 1;
			}

			if (epx < 150) {
				move = 0;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				if (gamemode == 1) {//EASY
					bosscount = 100;
				}

				if (gamemode < 3) {//EASY || NORMAL
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 0;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					if (esflag[1] == false) {
						esflag[1] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[1] = 1;
						}
						else {//�������E��
							eskind[1] = 2;
						}
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					if (esflag[2] == false) {
						esflag[2] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[2] = 3;
						}
						else {//�������E��
							eskind[2] = 4;
						}
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					if (esflag[3] == false) {
						esflag[3] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[3] = 6;
						}
						else if (ppx - 5 > epx) {//�E���ɂ���
							eskind[3] = 7;
						}
						else {//����
							eskind[3] = 1;
						}
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					if (esflag[4] == false) {
						esflag[4] = true;
						if (ppx + 5 < epx) {//�����ɂ���
							eskind[4] = 8;
						}
						else if (ppx - 5 > epx) {//�E���ɂ���
							eskind[4] = 9;
						}
						else {//����
							eskind[4] = 3;
						}
						esx[4] = epx + 3;
						esy[4] = epy;
					}
				}
				else {//HARD�ȏ�
					for (i = 0; i < 7; i++) {
						if (esflag[i] == false) {
							esflag[i] = true;
							if (i == 5) {
								eskind[i] = 9;
							}
							else if (i == 6) {
								eskind[i] = 8;
							}
							else {
								eskind[i] = i;
							}
							esx[i] = epx + 3;
							esy[i] = epy;
						}
					}
				}

			}

			if (count % 600 == 0) {
				move = 2;
				bosscount = 90;
			}
			break;
		case 2:
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 3;
				bosscount = 25;
			}
			break;
		case 3:
			bosscount--;
			if (bosscount < 0) {
				move = 4;
				bosscount = 60;
			}
			break;
		case 4:
			esflag[0] = true;
			eskind[0] = 20;
			esx[0] = epx;
			esy[0] = epy;
			bosscount = 90;
			move = 5;
			break;
		case 5:
			bosscount--;
			if (bosscount < 0) {
				move = 6;
				bosscount = 60;
			}
			break;
		case 6://���[�U�[����
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 7;
				bosscount = 50;
				if (gamemode >= 3) {//HARD�ȏ�
					bosscount = 25;
				}
			}
			break;
		case 7:
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 8;
			}
			break;
		case 8:
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 9;
				bosscount = 30;
			}
			break;
		case 9://�ːi����
			bosscount--;
			if (bosscount < 0) {
				if (epx + 5 < ppx) {
					epx += 2;
				}
				else if (epx - 5 > ppx) {
					epx -= 2;
				}
				else {
					move = 10;
					bosscount = 25;
				}
			}
			break;
		case 10:
			if (gamemode == 1) {//EASY
				epy += 5;
			}
			else if (gamemode == 2) {//NORMAL
				epy += 8;
			}
			else if (gamemode == 3) {//HARD
				epy += 12;
			}
			else if (gamemode == 4) {//UNKNOWN
				epy += 15;
			}
			esflag[0] = true;
			eskind[0] = 22;
			esx[0] = epx + 10;
			esy[0] = epy + 10;
			if (epy > MAXMAPY) {
				move = 11;
			}
			break;
		case 11:
			epy -= 5;
			if (gamemode != 1) {//NORMAL || HARD || UNKNOWN
				epy -= 3;
			}
			esflag[0] = true;
			eskind[0] = 22;
			esx[0] = epx + 10;
			esy[0] = epy + 10;
			if (epy < 71) {
				esflag[0] = false;
				epy = 70;
				move = 12;
			}
			break;
		case 12:
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 13;
			}
			break;
		case 13:
			epx += 2;
			if (epx > 400) {
				move = 14;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 70;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 15;
				bosscount = 60;
			}
			break;
		case 14:
			epx -= 2;
			if (epx < 100) {
				move = 13;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 70;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 15;
				bosscount = 60;
			}
			break;
		case 15:
			move = 0;
			break;
		case 20://UNKNOWN 7�����@�E�ړ�
			if (nowhp < 60) {
				move = 39;
			}
			epx += 2;
			if (epx > 400) {
				move = 21;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 22;
				bosscount = 60;
			}
			break;
		case 21://UNKNOWN 7�����@���ړ�
			if (nowhp < 60) {
				move = 39;
			}
			epx -= 2;
			if (epx < 100) {
				move = 20;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 22;
				bosscount = 60;
			}
			break;
		case 22://UNKNOWN 7�����@�ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 23;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			break;
		case 23://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 24;
			}
			break;
		case 24://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 25;
			}
			break;
		case 25://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 26;
			}
			break;
		case 26://UNKNOWN �����ɖ߂�
			if (nowhp < 60) {
				move = 39;
			}
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 27;
			}
			break;
		case 27://UNKNOWN ���E����A��
			if (nowhp < 60) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 8;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 6;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 3;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 1;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}

				if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 9;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 7;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 4;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 28;
				bosscount = 60;
			}
			break;
		case 28://UNKNOWN �ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 29;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 29://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 30;
			}
			break;
		case 30://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 31;
			}
			break;
		case 31://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 32;
			}
			break;
		case 32://UNKNOWN �����ɖ߂�
			if (nowhp < 60) {
				move = 39;
			}
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 33;
			}
			break;
		case 33://UNKNOWN �������獶�E�֘A��
			if (nowhp < 60) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 5;
					esx[0] = epx + 3;
					esy[0] = epy;
				}

				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 2;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 4;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 7;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 9;
					esx[4] = epx + 3;
					esy[4] = epy;
				}

				if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 1;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 3;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 6;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 8;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 34;
				bosscount = 60;
			}
			break;
		case 34://UNKNOWN �ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 35;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 35://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 36;
			}
			break;
		case 36://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 37;
			}
			break;
		case 37://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 38;
			}
			break;
		case 38://UNKNOWN �����ɖ߂�
			if (nowhp < 60) {
				move = 39;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 20;
			}
			break;
		case 39://UNKNOWN �����ɖ߂�
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 40;
			}
			break;
		case 40://UNKNOWN 4���� �E�ړ�
			if (nowhp < 25) {
				move = 60;
			}

			epx += 2;
			if (epx > 400) {
				move = 41;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 42;
				bosscount = 60;
			}
			break;
		case 41://UNKNOWN 4���� ���ړ�
			if (nowhp < 25) {
				move = 60;
			}

			epx -= 2;
			if (epx < 100) {
				move = 40;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 42;
				bosscount = 60;
			}
			break;
		case 42://UNKNOWN 4���� ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 1;
			}
			else if (epx - 5 > ppx) {
				epx -= 1;
			}
			else {
				move = 43;
				bosscount = 10;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			break;
		case 43://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 44;
			}
			break;
		case 44://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 45;
				bosscount = 30;
			}
			break;
		case 45://UNKNOWN �����ɖ߂�
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 46;
			}
			break;
		case 46://UNKNOWN �����_���U��
			if (nowhp < 25) {
				move = 60;
			}

			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 23;//�U���e
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 23;//�U���e
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 23;//�U���e
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 23;//�U���e
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 23;//�U���e
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 23;//�U���e
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 23;//�U���e
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 23;//�U���e
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 23;//�U���e
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 47;
				bosscount = 60;
			}
			break;
		case 47://UNKNOWN �����_���U�� ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 1;
			}
			else if (epx - 5 > ppx) {
				epx -= 1;
			}
			else {
				move = 48;
				bosscount = 10;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 23;//�U���e
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 23;//�U���e
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 23;//�U���e
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 23;//�U���e
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 23;//�U���e
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 23;//�U���e
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 23;//�U���e
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 23;//�U���e
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 23;//�U���e
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 48://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 49;
			}
			break;
		case 49://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 50;
				bosscount = 30;
			}
			break;
		case 50://UNKNOWN �����ɖ߂�
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 51;
			}
			break;
		case 51://UNKNOWN ���@�����_���A��
			if (nowhp < 25) {
				move = 60;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 8;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 6;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 3;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 8;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 6;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 3;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 8;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 6;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 3;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 9;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 7;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 4;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 9;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 7;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 4;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 9;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 7;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 4;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 10;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4);
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4);
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4);
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4);
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4);
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4);
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4);
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4);
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4);
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}
			if (count % 600 == 0) {
				move = 52;
				bosscount = 60;
			}
			break;
		case 52://UNKNOWN ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 53;
				bosscount = 10;
			}
			break;
		case 53://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 54;
			}
			break;
		case 54://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 55;
				bosscount = 30;
			}
			break;
		case 55://UNKNOWN �����ɖ߂�
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 40;
			}
			break;
		case 60://UNKNOWN 7�����@�E�ړ�
			epx += 2;
			if (epx > 400) {
				move = 61;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 5) {
							eskind[5] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 62;
				bosscount = 60;
			}
			break;
		case 61://UNKNOWN 7�����@���ړ�
			epx -= 2;
			if (epx < 100) {
				move = 60;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 5) {
							eskind[5] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 62;
				bosscount = 60;
			}
			break;
		case 62://UNKNOWN ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 63;
				bosscount = 6;
			}
			break;
		case 63://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 64;
			}
			break;
		case 64://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 65;
				bosscount = 30;
			}
			break;
		case 65://UNKNOWN �����_���U�� �E�ړ�
			epx += 2;
			if (epx > 400) {
				move = 66;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 20;//�U���e
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 20;//�U���e
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 20;//�U���e
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 20;//�U���e
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 20;//�U���e
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 20;//�U���e
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 20;//�U���e
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 20;//�U���e
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 20;//�U���e
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 67;
				bosscount = 60;
			}
			break;
		case 66://UNKNOWN �����_���U�� ���ړ�
			epx -= 2;
			if (epx < 100) {
				move = 65;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 20;//�U���e
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 20;//�U���e
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 20;//�U���e
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 20;//�U���e
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 20;//�U���e
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 20;//�U���e
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 20;//�U���e
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 20;//�U���e
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 20;//�U���e
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 67;
				bosscount = 60;
			}
			break;
		case 67://UNKNOWN �ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 68;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 68://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 69;
			}
			break;
		case 69://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 70;
			}
			break;
		case 70://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 71;
			}
			break;
		case 71://UNKNOWN �����ɖ߂�
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 72;
			}
			break;
		case 72://UNKNOWN 3�����A��
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 30;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 3;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 3;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 3;
					esx[2] = epx + 3;
					esy[2] = epy;
				}

				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 0;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 0;
					esx[5] = epx + 3;
					esy[5] = epy;
				}

				if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 4;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 4;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 4;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 73;
				bosscount = 60;
			}
			break;
		case 73://UNKNOWN ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 74;
				bosscount = 6;
			}
			break;
		case 74://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 75;
			}
			break;
		case 75://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 76;
				bosscount = 30;
			}
			break;
		case 76://UNKNOWN 8����+�U���e
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0 && esflag[5] == false) {
				bosscount = 90;
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 9;
						}
						else if (i == 5) {
							eskind[5] = 20;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 77;
				bosscount = 60;
			}
			break;
		case 77://UNKNOWN �ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 78;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 78://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 79;
			}
			break;
		case 79://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 80;
			}
			break;
		case 80://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 81;
			}
			break;
		case 81://UNKNOWN �����ɖ߂�
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 82;
			}
			break;
		case 82://UNKNOWN ���@�����_���A��
			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 8;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 6;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 3;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 8;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 6;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 3;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 8;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 6;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 3;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 9;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 7;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 4;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 9;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 7;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 4;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 9;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 7;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 4;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 10;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4);
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4);
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4);
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4);
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4);
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4);
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4);
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4);
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4);
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}
			if (count % 600 == 0) {
				move = 83;
				bosscount = 60;
			}
			break;
		case 83://UNKNOWN ���[�U�[�O�ړ�
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 84;
				bosscount = 6;
			}
			break;
		case 84://UNKNOWN ���[�U�[�O����
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 54;
			}
			break;
		case 85://UNKNOWN ���[�U�[
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 86;
				bosscount = 30;
			}
			break;
		case 86://UNKNOWN �ːi�O�ړ�
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 87;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 87://UNKNOWN �ːi�O����
			bosscount--;
			if (bosscount < 0) {
				move = 88;
			}
			break;
		case 88://UNKNOWN �ːi
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 89;
			}
			break;
		case 89://UNKNOWN �ːi�߂�
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 81;
			}
			break;
		case 90://UNKNOWN �����ɖ߂�
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 60;
			}
			break;
		default:
			move = 0;
			break;
		}
	}
	else {//���g
		switch (move) {
		case 100://�o��
			epy -= 2;
			if (epy < 30) {
				epy = 30;
				move = 1;
			}
			break;
		case 1://5���� �E�ړ�
			epx += 2;
			if (epx > 400) {
				move = 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 150;
				if (gamemode == 1) {//EASY
					bosscount = 210;
				}
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 75 && gamemode >= 3) {//HARD || UNKNOWN
				for (i = 5; i < 10; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 5;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 700 == 0) {
				move = 3;
				bosscount = 90;
			}
			break;
		case 2://5���� ���ړ�
			epx -= 2;
			if (epx < 100) {
				move = 1;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 150;
				if (gamemode == 1 || gamemode == 3) {//EASY || HARD
					bosscount = 210;
				}

				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 75 && gamemode >= 3) {//HARD || UNKNOWN
				for (i = 5; i < 10; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 5;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 700 == 0) {
				move = 3;
				bosscount = 90;
			}
			break;
		case 3://�����_��
			bosscount--;
			if (bosscount < 0) {
				bosscount = 30;
				if (gamemode == 1) {//EASY
					bosscount = 90;
				}
				else if (gamemode >= 3) {//HARD�ȏ�
					bosscount = 20;
				}

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 10;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 10;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 10;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 10;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false && gamemode >= 3) {//HARD�ȏ�
					esflag[5] = true;
					eskind[5] = GetRand(9) + 10;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false && gamemode >= 3) {//HARD�ȏ�
					esflag[6] = true;
					eskind[6] = GetRand(9) + 10;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false && gamemode >= 3) {//HARD�ȏ�
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false && gamemode >= 3) {//HARD�ȏ�
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false && gamemode >= 3) {//HARD�ȏ�
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 1;
				bosscount = 90;
			}
			break;
		case 10://UNKNOWN 7���� �E�ړ�
			epx += 2;
			if (count % 700 == 0) {
				move = 12;
				bosscount = 90;
			}

			if (epx > 400) {
				move = 11;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 200;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						if (i == 5) {
							eskind[i] = 17;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 100) {
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}
			break;
		case 11://UNKNOWN 7���� ���ړ�
			epx -= 2;
			if (count % 700 == 0) {
				move = 12;
				bosscount = 90;
			}

			if (epx < 100) {
				move = 10;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 200;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						if (i == 5) {
							eskind[i] = 17;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 100) {
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}
			break;
		case 12://UNKNOWN �E����A��
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 12;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 17;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 14;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 19;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 18;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 13;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 16;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 11;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 13;
				bosscount = 90;
			}
			break;
		case 13://UNKNOWN ������A��
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 11;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 16;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 13;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 19;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 14;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 17;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 12;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 14://UNKNOWN �����_��	
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 3;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 10;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 10;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 10;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 10;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 10;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 10;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 10;
				bosscount = 90;
			}
			break;
		case -1:
		case -2:
		case -3:
		case -10:
		case -11:
		case -12:
		case -13:
		case -14:
			bosscount--;
			if (bosscount < 0) {
				move *= -1;//�߂�
			}
			break;
		default:
			move = 1;
			break;
		}
	}
}

void Mode1Boss::Boss_StagatoteSP_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS) {
	int i;
	int Cr = GetColor(240, 240, 240);
	if (trueBOSS == true) {//�{��
		if (nowhp < maxhp / 2 && move < 20) {//HP������؂�ƍs�����ς��
			move = 20;
		}

		switch (move) {

			/*HP1/2�ȏ�*/
		case 0://���[�v �E
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 400;
				move = 1;
			}
			break;
		case 1://���[�v ��
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 100;
				move = 2;
			}
			break;
		case 2://���[�v ����
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 250;
				move = 3;
			}
			break;
		case 3://5�����e �E�ړ�
			epx += 2;
			if (epx > 400) {
				move = 4;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 5;
				bosscount = 90;
			}
			break;
		case 4://5�����e ���ړ�
			epx -= 2;
			if (epx < 100) {
				move = 3;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 5;
				bosscount = 90;
			}
			break;
		case 5://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 6;
			break;
		case 6://���@�_�������_��(���E����)
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//�{�X���E��
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 7;
				bosscount = 90;
			}
			break;
		case 7://�o���A�V���b�g
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 8;
			break;
		case 8://�����ɖ߂�
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				move = 9;
			}
			break;
		case 9://�E����A��
			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 59;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 57;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 55;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 53;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 52;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 54;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 56;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 58;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 300 == 0) {
				move = 10;
				bosscount = 90;
			}
			break;
		case 10://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 11;
			break;
		case 11://������A��
			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 58;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 56;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 54;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 52;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 53;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 55;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 57;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 59;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 300 == 0) {
				move = 12;
				bosscount = 90;
			}
			break;
		case 12://�ᑬ�����_�� ���ړ�
			epx -= 2;
			if (epx < 100) {
				move = 13;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(8) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(8) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(8) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(8) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(8) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(8) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(8) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(8) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(8) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 13://�ᑬ�����_�� �E�ړ�
			epx += 2;
			if (epx > 400) {
				move = 12;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(8) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(8) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(8) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(8) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(8) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(8) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(8) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(8) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(8) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 14://�o���A�V���b�g
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 0;
			break;
			/*HP1/2��؂������Ɉ��̂ݎg�p(�S�Ă̓�Փx)*/
		case 20://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 21;
			break;
		case 21://�o���A�V���b�g��
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 22;
				bosscount = 10;
			}
			break;
		case 22://�o���A�V���b�g�E
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 23;
				bosscount = 10;
			}
		case 23://�o���A�V���b�g���@
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 24;
				bosscount = 10;
			}
			break;
		case 24://��Փx�ɂ��s���`�F���W
			if (gamemode == 3) {//HARD
				move = 30;
				bosscount = 15;
			}
			else if (gamemode == 4) {//UNKNOUN
				move = 50;
				bosscount = 15;
			}
			else {
				move = -1;//�G���[
			}
			break;
			/*HARD HP1/2����*/
		case 30://���@�_�������_��(���E�ړ�)
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//�{�X���E��
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 31;
				bosscount = 90;
			}
			break;
		case 31://�o���A�V���b�g
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 32;
			break;
		case 32://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 33;
			break;
		case 33://���@�_����
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 61;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 61;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 61;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 61;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 61;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 61;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
			}
			if (count % 360 == 0) {
				move = 34;
				bosscount = 90;
			}
			break;
		case 34://�o���A�V���b�g
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 35;
			break;
		case 35://�󂫍���5�����e ��
			epx -= 2;
			if (epx < 150) {
				move = 36;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 64;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 65;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 68;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 69;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 37;
				bosscount = 90;
			}
			break;
		case 36://�󂫍���5�����e �E
			epx += 2;
			if (epx > 350) {
				move = 35;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 64;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 65;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 68;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 69;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 37;
				bosscount = 90;
			}
			break;
		case 37://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 38;
			break;
		case 38://�����_���V���b�g �E
			epx += 2;
			if (epx > 400) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(18) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(18) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(18) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(18) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(18) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(18) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(18) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(18) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(18) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 1800 == 0) {
				move = 40;
				bosscount = 90;
			}
			break;
		case 39://�����_���V���b�g ��
			epx -= 2;
			if (epx < 100) {
				move = 38;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(18) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(18) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(18) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(18) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(18) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(18) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(18) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(18) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(18) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 1800 == 0) {
				move = 40;
				bosscount = 90;
			}
			break;
		case 40://�o���A�V���b�g
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 30;
			break;
			/*UNKNOWN HP1/2����*/
		case 50://7�����e �E
			epx += 2;
			if (epx > 400) {
				move = 51;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 52;
				bosscount = 5;
			}
			break;
		case 51://7�����e ��
			epx -= 2;
			if (epx < 100) {
				move = 50;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 52;
				bosscount = 5;
			}
			break;
		case 52://�o���A�V���b�g ����
			bosscount--;
			if (bosscount < 0) {
				epx = 250;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 53;
			}
			break;
		case 53://�o���A�V���b�g ���@
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 54;
			}
			break;
		case 54://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 55;
			break;
		case 55://���������_�� ��
			epx -= 2;
			if (epx < 100) {
				move = 56;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 60;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 60;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 60;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 60;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 60;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 60;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 60;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 60;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 60;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 57;
				bosscount = 90;
			}
			break;
		case 56://���������_�� �E
			epx += 2;
			if (epx > 400) {
				move = 55;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 60;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 60;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 60;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 60;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 60;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 60;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 60;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 60;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 60;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 57;
				bosscount = 90;
			}
			break;
		case 57://�o���A�V���b�g ��
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 58;
			}
			break;
		case 58://�o���A�V���b�g �E
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 59;
			}
			break;
		case 59://�o���A�V���b�g ���@
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 60;
			}
			break;
		case 60://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 61;
			break;
		case 61://���@�_�������_��
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//�{�X���E��
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 62;
				bosscount = 90;
			}
			break;
		case 62://�o���A�V���b�g �E
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 63;
			}
			break;
		case 63://�o���A�V���b�g ��
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 64;
			}
			break;
		case 64://�o���A�V���b�g ���@
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 65;
			}
			break;
		case 65://�m�[�}���G�o��
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 50;
			break;
		default:
			bosscount = 10;
			move = 0;
			break;
		}
	}
	else {//�⏕�p�[�c
		bosscount--;
		if (bosscount < 0) {
			bosscount = 15;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(18) + 51;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(18) + 51;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(18) + 51;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(18) + 51;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(18) + 51;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(18) + 51;
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(18) + 51;
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(18) + 51;
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(18) + 51;
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false) {
				esflag[9] = true;
				eskind[9] = GetRand(18) + 51;
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
	}
}
/*�{�X�̓��������܂�*/

int Mode1Boss::BossHP(int damage) {
	nowhp -= damage;
	if (nowhp < 0)nowhp = 0;
	if (damage > 0) {//�_���[�W���󂯂Ă���
		protectcount = 12;
	}
	return nowhp;
}

void Mode1Boss::BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*protect = protectcount;
	for (int i = 0; i < 10; i++) {
		shotx[i] = esx[i];
		shoty[i] = esy[i];
		shotkind[i] = eskind[i];
		shotflag[i] = esflag[i];
	}
}

int Mode1Boss::BossMoveSet(int n, bool changeflag) {
	if (changeflag == true) {
		move = n;
	}
	else {
		if (n >= 1) {//���]������(���g�̂ݓK�p)
			move *= -1;
			switch (n) {
			case 1://EASY
			case 2://NORMAL
				bosscount = 90;//�~�߂Ă��鎞��
				protectcount = 90;
				break;
			case 3://HARD
				bosscount = 60;//�~�߂Ă��鎞��
				protectcount = 60;
				break;
			case 4://UNKNOWN
				bosscount = 45;//�~�߂Ă��鎞��
				protectcount = 45;
				break;
			default:
				break;
			}
		}
	}
	return move;
}

int Mode1Boss::BossPositionCheck(int *enemyx, int *enemyy) {
	*enemyx = epx;
	*enemyy = epy;
	return eskind[9];
}

void Mode1Boss::BossPositionMove(int movex, int movey) {
	epx = movex;
	epy = movey;
}

/*�X�e�[�W16(�{�X���b�V��:Stagatote_SP�X�e�[�W)�̓G�o���p�֐��ƕ⏕�p�[�c�̖{�̓����ړ�*/
void BossStage_NormalEnemyAppear(int *errorcheck, Mode1Enemy Enemy[], Mode1Boss Boss[]) {
	int epx = 0, epy = 0, eskind = 0;
	eskind = Boss[0].BossPositionCheck(&epx, &epy);
	Boss[1].BossPositionMove(epx + 3, epy);//�⏕�p�[�c�̈ړ�
	if (eskind == 24) {//�m�[�}���G�o��
		for (int i = 0; i < 7; i++) {
			Enemy[i].AppearEnemy(100 + i * 50, 70, 8);
		}
	}
	else if (eskind == 25) {//�o���A�V���b�g
		if (Enemy[10].EnemyExistCheck() == false) {
			Enemy[10].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[11].EnemyExistCheck() == false) {
			Enemy[11].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[12].EnemyExistCheck() == false) {
			Enemy[12].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[13].EnemyExistCheck() == false) {
			Enemy[13].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[14].EnemyExistCheck() == false) {
			Enemy[14].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[15].EnemyExistCheck() == false) {
			Enemy[15].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[16].EnemyExistCheck() == false) {
			Enemy[16].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[17].EnemyExistCheck() == false) {
			Enemy[17].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[18].EnemyExistCheck() == false) {
			Enemy[18].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[19].EnemyExistCheck() == false) {
			Enemy[19].AppearEnemy(epx + 10, epy + 35, 10);
		}
	}
	else {//����ȊO�͊֌W�Ȃ�
		return;
	}

	Boss[0].BossShotFlagFALSE(9);//���̂݌��悤�ɂ���
}

void NormalStage_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]);

unsigned int StageClear(int *ErrorCheck, int stage, unsigned int point, Mode1Player Player, int gameflag, int gamecount, int gamemode, int itemnum);

int Player1mode(int *ErrorCheck, int gamemode);

void Tutoreal_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]);

int Tutoreal(int *ErrorCheck);



