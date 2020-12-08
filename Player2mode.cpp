#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/////---**2Player mode**---/////

#define MAX1PlayerENEMY 40

#define MAXMAPX1 300
#define MAXMAPX2 610
#define MAXMAPYALL 360

#define NEXTKEYTIME2 60

/////**�G�@�p�֐�(�m�[�}��)**/////
class Mode2Enemy {
private:
	int epx, epy;//x���W,y���W
	bool existflag;//���݂��Ă��邩
	bool esflag;//�e���ł���Ă��邩
	int ekind;//���
	int eskind;//�_���ꏊ
	int esx, esy;//�e�̍��W
	int nextshotcount;//���̒e���˂܂ł̊Ԋu

public:
	void StartSet();//�ŏ��̏���������
	void AppearEnemy(int x, int y, int kind);//�G�o���p�֐�
	void NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int No);//�G�̓����Ɋւ��鏈��(�m�[�}���G)
																								 /*�G�@�̍��W�Ǝ��,�G�̒e�̍��W,���݃t���O��Ԃ�*/
	void EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag);
	void BreakEnemy();//�G��|�����Ƃ��̏���
	bool EnemyExistCheck() { return existflag; };//���݂��邩�ǂ���
	int EnemyKindCheck() { return ekind; };//��ނ͉���
	void EnemyShotFlagFALSE() { esflag = FALSE; };//�e��������Ă��Ȃ���Ԃɂ���
};


/////**�G�@�p�֐�(�{�X)**/////
class Mode2Boss {
private:
	int epx, epy;//�{�X���̂�x���W,y���W
	int ekind;//���(11:grad 12:cron 13:erec 14:rain 15:staga)*staga��2PlayerMode�ł̂ݏo������̂Ō���
	int esx[7], esy[7], eskind[7];//�e�̍��W�Ǝ��
	bool esflag[7];//�e�����݂��Ă��邩
	int move;//�������̎w��
	int bosscount, protectcount;//���Ԑ���,���G����
	int maxhp, nowhp;//�ő�A����HP(0�ŏ���)

public:
	void StartSet(int stage, int No);//�ŏ��̏����������Əo��
							 /*�G�̓����Ɋւ��鏈��(�{�X�G)*/
	void BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int No, Mode2Enemy NormalEnemy[]);
	int BossHP(int damage);//�{�X�̎c��HP(0�ŏ��ł�\��) 
						   /*�G�@�̍��W,�G�̎��,�G�̒e�̍��W,�e�̎��,���G���Ԃ�Ԃ�*/
	void BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect);
	void BossShotFlagFALSE(int n) { esflag[n] = FALSE; };//�e��������Ă��Ȃ���Ԃɂ���
};


/////**���@�p�֐�**/////
class Mode2Player {
private:
	int ppx, ppy;//x���W,y���W
	int php, damagetime;//���@HP,�_���[�W��̕��A����
	bool psflag[3][3];//�e���ł���Ă��邩
	int pskind[3];//���݂̒e�̎��(9:�����Ȃ�)
	int psx[3][3], psy[3][3];//���ꂼ��̒e�̍��W
	bool keyflag[3];//�L�[��������Ă��邩
	int keyflagcount[3];//�L�[��������Ă��Ȃ���ԂɂȂ�܂ł̎���
	int pscombocount[3], pscombotimes[3];//�R���{���Ɣ{��
	int point;//���_
	int PlayerNo;//Player1���A2��

public:
	void StartSet(int no);//�ŏ��̏���������
	int PlayerHP(int damage);//�v���C���[��HP�Ɋւ��鏈��
	void PlayerMove1(int *errorcheck, int MyGraphicint, int PlayerShotGraphic[]);//�v���C���[1�̓����Ɋւ��鏈��
	void PlayerMove2(int *errorcheck, int MyGraphicint, int PlayerShotGraphic[]);//�v���C���[2�̓����Ɋւ��鏈��
	void PlayerShotColor(int PlayerShotKind[]);//�e�̎�ނ�Ԃ��֐�
	void PlayerShotCombo(int ShotComboNum[]);//�R���{����Ԃ��֐�
	void NormalStage_CollisionDetection(int *errorcheck, Mode2Enemy Enemy[], int stage);//�����蔻��ƃ_���[�W
	void PointPlus(int plus) { point += plus; };//���_�ǉ�
	int GetPoint() { return point; };//���_��Ԃ�
	void PlayerPosition(int *x, int *y) { *x = ppx; *y = ppy; };//�ꏊ��Ԃ�
	void BossStage_CollisionDetection(int *errorcheck, Mode2Boss Boss[],int No);//�����蔻��ƃ_���[�W
};


/////**�֐��W**/////

 /*�Q�[�������p*/
void Mode2Player::StartSet(int no) {
	int i, j;
	PlayerNo = no;
	if (no == 1 || no == 3) {
		ppx = 140;
		if (no == 1) {
			php = 30;//HP�̏����l
			point = 0;
		}
	}
	else if (no == 2 || no == 4) {
		ppx = 450;
		if (no == 2) {
			php = 30;//HP�̏����l
			point = 0;
		}
	}
	ppy = 320;
	for (i = 0; i < 3; i++) {
		pskind[i] = 9;
		pscombocount[i] = 0;
		pscombotimes[i] = 1;
		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			keyflag[i] = FALSE;
			keyflagcount[i] = 0;
		}
		else {
			keyflag[i] = TRUE;
			keyflagcount[i] = NEXTKEYTIME2;
		}
		for (j = 0; j < 3; j++) {
			psflag[i][j] = FALSE;
			psx[i][j] = ppx + 12;
			psy[i][j] = ppy;
		}
	}
	damagetime = 0;

}//�ŏ��̏���

int Mode2Player::PlayerHP(int damage) {
	point -= damage;
	if (damage > 0) {//�_���[�W���󂯂Ă���
		damagetime = 60;
	}
	return point;
}//2Player Mode�ł�HP�̑���ɓ��_������

void Mode2Player::PlayerMove1(int *errorcheck, int MyGraphic, int PlayerShotGraphic[]) {
	int i, j;
	if (ppx > MAXMAPX1 + 100 || ppx < -100)*errorcheck = 2;//���E�֍s������

														  /*�e�̃L�[�`�F�b�N*/
	if (CheckHitKey(KEY_INPUT_Q) == 0) {
		keyflag[0] = FALSE;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_W) == 0) {
		keyflag[1] = FALSE;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_E) == 0) {
		keyflag[2] = FALSE;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == TRUE) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = FALSE;
		}
	}

	/*�{�^���ƑΉ����铮��*/
	if (php > 0) {//HP���s���Ă��Ȃ��Ȃ�
		if (CheckHitKey(KEY_INPUT_B) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX1 - 30)ppx = MAXMAPX1 - 30;
		}
		if (CheckHitKey(KEY_INPUT_C) == 1) {
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (CheckHitKey(KEY_INPUT_Q) == 1 && keyflag[0] == FALSE) {
			keyflag[0] = TRUE;
			keyflagcount[0] = NEXTKEYTIME2;
			if (psflag[0][0] == FALSE) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = TRUE;
			}
			else if (psflag[0][1] == FALSE) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = TRUE;
			}
			else if (psflag[0][2] == FALSE) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_W) == 1 && keyflag[1] == FALSE) {
			keyflag[1] = TRUE;
			keyflagcount[1] = NEXTKEYTIME2;
			if (psflag[1][0] == FALSE) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = TRUE;
			}
			else if (psflag[1][1] == FALSE) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = TRUE;
			}
			else if (psflag[1][2] == FALSE) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_E) == 1 && keyflag[2] == FALSE) {
			keyflag[2] = TRUE;
			keyflagcount[2] = NEXTKEYTIME2;
			if (psflag[2][0] == FALSE) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = TRUE;
			}
			else if (psflag[2][1] == FALSE) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = TRUE;
			}
			else if (psflag[2][2] == FALSE) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = TRUE;
			}
		}
	}

	/*�O���t�B�b�N�\��*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, TRUE);//�|����Ă��Ȃ��Ȃ�\��
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == TRUE) {
				psy[i][j] -= 5;//���@�̒e�̓���
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], TRUE);
				if (psy[i][j] < -50) {
					psflag[i][j] = FALSE;
				}
			}
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (damagetime >= -5)damagetime--;

}//�v���C���[1�̓����Ɋւ��鏈��(�e��)

void Mode2Player::PlayerMove2(int *errorcheck, int MyGraphic, int PlayerShotGraphic[]) {
	int i, j;
	if (ppx > MAXMAPX2 + 100 || ppx < -100)*errorcheck = 2;//���E�֍s������

														   /*�e�̃L�[�`�F�b�N*/
	if (CheckHitKey(KEY_INPUT_I) == 0) {
		keyflag[0] = FALSE;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_O) == 0) {
		keyflag[1] = FALSE;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_P) == 0) {
		keyflag[2] = FALSE;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == TRUE) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = FALSE;
		}
	}

	/*�{�^���ƑΉ����铮��*/
	if (php > 0) {//HP���s���Ă��Ȃ��Ȃ�
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX2 - 30)ppx = MAXMAPX2 - 30;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			ppx -= 3;
			if (ppx < MAXMAPX1 + 10)ppx = MAXMAPX1 + 10;
		}
		if (CheckHitKey(KEY_INPUT_I) == 1 && keyflag[0] == FALSE) {
			keyflag[0] = TRUE;
			keyflagcount[0] = NEXTKEYTIME2;
			if (psflag[0][0] == FALSE) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = TRUE;
			}
			else if (psflag[0][1] == FALSE) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = TRUE;
			}
			else if (psflag[0][2] == FALSE) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_O) == 1 && keyflag[1] == FALSE) {
			keyflag[1] = TRUE;
			keyflagcount[1] = NEXTKEYTIME2;
			if (psflag[1][0] == FALSE) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = TRUE;
			}
			else if (psflag[1][1] == FALSE) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = TRUE;
			}
			else if (psflag[1][2] == FALSE) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_P) == 1 && keyflag[2] == FALSE) {
			keyflag[2] = TRUE;
			keyflagcount[2] = NEXTKEYTIME2;
			if (psflag[2][0] == FALSE) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = TRUE;
			}
			else if (psflag[2][1] == FALSE) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = TRUE;
			}
			else if (psflag[2][2] == FALSE) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = TRUE;
			}
		}
	}

	/*�O���t�B�b�N�\��*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, TRUE);//�|����Ă��Ȃ��Ȃ�\��
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == TRUE) {
				psy[i][j] -= 5;//���@�̒e�̓���
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], TRUE);
				if (psy[i][j] < -50) {
					psflag[i][j] = FALSE;
				}
			}
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (damagetime >= -5)damagetime--;

}//�v���C���[2�̓����Ɋւ��鏈��(�e��)

void Mode2Player::PlayerShotColor(int PlayerShotKind[]) {
	for (int i = 0; i < 3; i++) {
		PlayerShotKind[i] = pskind[i];
	}
}//�e�̎�ނ�Ԃ��֐�

void Mode2Player::PlayerShotCombo(int ShotComboNum[]) {
	for (int i = 0; i < 3; i++) {
		ShotComboNum[i] = pscombocount[i];
	}
}//�R���{����Ԃ��֐�

 /*�����蔻��ƃ_���[�W*/
void Mode2Player::NormalStage_CollisionDetection(int *errorcheck, Mode2Enemy Enemy[], int stage) {
	int epx = 0, epy = 0, enemykind = 9;//�G�@�̍��W�Ǝ��
	int esx = 0, esy = 0;//�G�̒e�̍��W
	int enemyxnum = 0, enemyynum = 0;
	bool enemyflag = FALSE, enemyshotflag = FALSE;//���݃t���O
	int i, j, k;
	bool breakflag = FALSE;

	for (i = 0; i < MAX1PlayerENEMY; i++) {
		breakflag = FALSE;
		/*�G�@�̏��擾*/
		Enemy[i].EnemyInfoReturn(&epx, &epy, &enemykind, &esx, &esy, &enemyflag, &enemyshotflag);
		if (enemyflag == TRUE && enemykind == 9)*errorcheck = 4;//���݂��Ă���̂ɑ��݂��Ă��Ȃ�
		if (enemyflag == TRUE) {//�G�@�����݂��Ă���Ƃ�
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psx[j][k] + 5 < epx + 28 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 28 && psy[j][k] + 16>epy + 4) {
						/*�e������������*/
						if (pskind[j] == enemykind) {//�O��Ɠ���
							pscombocount[j] += 1;//�R���{����1���₷
							pscombotimes[j] *= 3;//�R���{�{�����グ��

						}
						else if (enemykind == 8) {//���i�R���{�ɉ��Z����Ȃ��j������
							point += 5;//�|�C���g���Z
						}
						else {//���ɓ���Ȃ��Ƃ͂Ȃ�����
							pskind[j] = enemykind;//�e��ς���
							pscombocount[j] = 1;//�R���{�����P�ɂ���
							pscombotimes[j] = 1;
						}

						/*���ʏ���*/
						Enemy[i].BreakEnemy();//�G��j��
						psflag[j][k] = FALSE;//�e������
						point += pscombotimes[j] + pscombocount[j];//�|�C���g���Z
						breakflag = TRUE;
					}
				}
				if (breakflag == TRUE)break;
			}
		}
		if (enemyshotflag == TRUE) {//�G�̒e�����݂��Ă���Ƃ�
			if (esx + 10 < ppx + 32 && esx + 22 > ppx + 8 && esy + 10 < ppy + 32 && esy + 22 > ppy + 4) {
				/*�G�̒e���Ԃ�����*/
				if (damagetime <= 0)PlayerHP(10);//�_���[�W
				Enemy[i].EnemyShotFlagFALSE();
			}
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (damagetime >= -5)damagetime--;

}//�����蔻��m�F�p�֐�

void Mode2Player::BossStage_CollisionDetection(int *errorcheck, Mode2Boss Boss[], int No) {
	int epx = 0, epy = 0, enemykind = 9;//�G�@�̍��W�Ǝ��
	int esx[5] = {}, esy[5] = {}, eskind[5] = {};//�G�̒e�̍��W
	int protecttime = 0;//���G����
	bool enemyshotflag[5] = {};//���݃t���O
	int i, j, k;
	No--;

	/*�G�@�̏��擾*/
	Boss[No].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
	if (Boss[No].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//���݂��Ă���̂ɑ��݂��Ă��Ȃ�
	if (Boss[No].BossHP(0) > 0) {//�G�@�����݂��Ă���Ƃ�
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (psflag[j][k] == TRUE) {//�e�����݂��Ă���Ƃ�
					if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
						/*�e������������*/
						if (protecttime <= 0) {
							Boss[No].BossHP(1);//1�_���[�W��^����
							point += 5;
							if (Boss[No].BossHP(0) == 0) {
								point += 1000;
							}
						}
						psflag[j][k] = FALSE;
					}
				}
			}
		}
	}
	for (i = 0; i < 5; i++) {
		if (enemyshotflag[i] == TRUE) {//�G�̒e�����݂��Ă���Ƃ�
			if (esx[i] + 10 < ppx + 32 && esx[i] + 22 > ppx + 8 && esy[i] + 10 < ppy + 32 && esy[i] + 22 > ppy + 4) {
				/*�G�̒e���Ԃ�����*/
				if (damagetime <= 0) {
					if (eskind[i] >= 20) {
						PlayerHP(10);//���_������
						Boss[No].BossShotFlagFALSE(i);
					}
					else {//�ʏ�̃_���[�W
						PlayerHP(10);//���_������
						Boss[No].BossShotFlagFALSE(i);
					}
				}
			}
		}
	}

}//�����蔻��m�F�p�֐�

void Mode2Enemy::StartSet() {//�ŏ��̏���
	epx = 0;
	epy = 0;
	existflag = FALSE;
	esflag = FALSE;
	ekind = 9;
	eskind = 0;
	esx = epx;
	esy = epy;
	nextshotcount = 90 + GetRand(180);
}

void Mode2Enemy::AppearEnemy(int x, int y, int kind) {//�o���ꏊ�Ǝ�ނ����߂ČĂяo��
	epx = x;
	epy = y;
	existflag = TRUE;
	esflag = FALSE;
	ekind = kind;
	eskind = 0;
	esx = epx;
	esy = epy;
}//�G�o���p�֐�

void Mode2Enemy::NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy,int No) {
	/*�O���t�B�b�N*/
	if (esflag == TRUE) {//�e�����݂���Ȃ�
		DrawGraph(esx, esy, NormalEnemyGraphic[11], TRUE);//�e
	}

	if (existflag == TRUE) {//�@�̂����݂���Ȃ�
		DrawGraph(epx, epy, NormalEnemyGraphic[ekind], TRUE);//�@��

		/*�ړ�*/
		if (count % 3 == 0) {
			if (count % 60 < 30) {
				epx += 1;
			}
			else {
				epx -= 1;
			}
		}

		/*�e����*/
		nextshotcount--;
		if (nextshotcount < 0) {//��莞�Ԃ��Ƃɔ���
			nextshotcount = 100 + GetRand(250);//���Ԃ̃��Z�b�g
			if (esflag == FALSE) {//�e��������Ă��Ȃ��Ȃ�
				esx = epx;
				esy = epy;
				if (ekind != 6)esflag = TRUE;//�e������
				 /*�_���ꏊ*/
				switch (ekind) {
				case 0://��
					eskind = 1;
					break;
				case 1://��
					if (ppx < epx - 150) {//150�ȏ㍶
						eskind = 8;
					}
					else if (ppx < epx - 100) {//100�ȏ㍶
						eskind = 6;
					}
					else if (ppx < epx - 50) {//50�ȏ㍶
						eskind = 4;
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
					if (ppx < epx - 150) {//150�ȏ㍶
						eskind = 4;
					}
					else if (ppx < epx - 100) {//100�ȏ㍶
						eskind = 2;
					}
					else if (ppx < epx - 50) {//50�ȏ㍶
						eskind = 1;
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
					if (ppx < epx - 150) {//150�ȏ㍶
						eskind = 6;
					}
					else if (ppx < epx - 80) {//80�ȏ㍶
						eskind = 4;
					}
					else if (ppx < epx - 30) {//30�ȏ㍶
						eskind = 2;
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
					if (No == 1) {
						if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_B) == 1) {
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
						else if (CheckHitKey(KEY_INPUT_B) == 1) {
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 1;
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
						else if (CheckHitKey(KEY_INPUT_C) == 1) {
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 4;
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
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
					}
					else if (No == 2) {
						if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1) {
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
						else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 1;
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
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 4;
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
							if (ppx < epx - 150) {//150�ȏ㍶
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100�ȏ㍶
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50�ȏ㍶
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150�ȏ�E
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100�ȏ�E
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50�ȏ�E
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
					}
					break;
				case 8://��
					if (ppx < epx - 150) {//150�ȏ㍶
						eskind = 6;
					}
					else if (ppx < epx - 80) {//80�ȏ㍶
						eskind = 4;
					}
					else if (ppx < epx - 30) {//30�ȏ㍶
						eskind = 2;
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
				}

				
			}
		}
	}

	if (esflag == TRUE) {//�e��������Ă���Ƃ�
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
		}
		
		if (No == 1) {
			if (esy > MAXMAPYALL - 30 || esx > MAXMAPX1 - 16 || esx < -10)esflag = FALSE;// �[�ɓ��B���ɏ�����
		}
		else if (No == 2) {
			if (esy > MAXMAPYALL - 30 || esx > MAXMAPX2 - 16 || esx < MAXMAPX1 + 10)esflag = FALSE;// �[�ɓ��B���ɏ�����
		}
		
	}

}//�G�̓����ƒe�Ɋւ��鏈��(�m�[�}���G) 

void Mode2Enemy::EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*shotx = esx;
	*eshoty = esy;
	*enemyflag = existflag;
	*shotflag = esflag;
}//�G�@�̍��W,�G�̒e�̍��W,���݃t���O��Ԃ�

void Mode2Enemy::BreakEnemy() {
	existflag = FALSE;
}//�G��|�����Ƃ��̏���

void Mode2Boss::StartSet(int stage,int No) {
	if (No == 1) {
		epx = 135;
	}
	else if (No == 2) {
		epx = 445;
	}
	epy = 30;
	move = 0;
	switch (stage) {
	case 5:
		ekind = 15;
		maxhp = 50;
		break;
	default://����ȊO���{�X�X�e�[�W�ɂȂ邱�Ƃ͂Ȃ�
		return;
	}
	nowhp = maxhp;
	for (int i = 0; i < 5; i++) {
		esx[i] = epx;
		esy[i] = epy;
		eskind[i] = 0;
		esflag[i] = FALSE;
	}
	bosscount = 150;//���Ԑ���
	protectcount = 120;//���G����
}//�ŏ��̏����������Əo��

void Mode2Boss::BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int No, Mode2Enemy NormalEnemy[]) {
	int i;
	//�F�쐬
	int Cr = GetColor(128, 128, 128);//�D(�����p)
	int HPCr = GetColor(15, 255, 15);//�΁iHP�p�j

	/*�X�e�[�W�`�F�b�N�Ɩ��O�\���A�G�̓����Ȃ�*/
	switch (ekind) {
	case 11://2PlayerMode�ł͂Ȃ�		
		break;
	case 12://2PlayerMode�ł͂Ȃ�		
		break;
	case 13://2PlayerMode�ł͂Ȃ�		
		break;
	case 14://2PlayerMode�ł͂Ȃ�	
		break;
	case 15:
		if (No == 1) {
			DrawFormatString(5, 3, Cr, "Staga:HP");
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				if (move == 0) {
					epx += 2;
					if (epx > 250) {
						move = 1;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 1) {
					epx -= 2;
					if (epx < 50) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 2) {
					if (epx < 130) {
						epx += 2;
					}
					else if (epx > 145) {
						epx -= 2;
					}
					else {
						move = 3;
						bosscount = 15;
					}
				}
				else if (move == 3) {
					bosscount--;
					if (bosscount < 0) {
						move = 4;
						bosscount = 30;
					}
				}
				else if (move == 4) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(55 + i * 40, 70, 8);
					}
					move = 5;
				}
				else if (move == 5) {
					epx += 1;
					if (epx > 250) {
						move = 6;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[1] = 1;
							}
							else {//�������E��
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[2] = 3;
							}
							else {//�������E��
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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
					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 6) {
					epx -= 1;
					if (epx < 50) {
						move = 5;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[1] = 1;
							}
							else {//�������E��
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[2] = 3;
							}
							else {//�������E��
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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

					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 7) {
					if (epx < 130) {
						epx += 2;
					}
					else if (epx > 145) {
						epx -= 2;
					}
					else {
						if (nowhp < 25) {
							move = 8;
						}
						else {
							move = 0;
						}
						bosscount = 90;
					}
				}
				else if (move == 8) {
					epx += 3;
					if (epx > 250) {
						move = 9;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 10;
						bosscount = 90;
					}
				}
				else if (move == 9) {
					epx -= 3;
					if (epx < 50) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}

						if (count % 600 == 0) {
							move = 10;
							bosscount = 90;
						}
					}
				}
				else if (move == 10) {
					if (epx < 130) {
						epx += 3;
					}
					else if (epx > 145) {
						epx -= 3;
					}
					else {
						move = 11;
						bosscount = 15;
					}
				}
				else if (move == 11) {
					bosscount--;
					if (bosscount < 0) {
						move = 12;
						bosscount = 30;
					}
				}
				else if (move == 12) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(55 + i * 40, 70, 8);
					}
					move = 13;
				}
				else if (move == 13) {
					esflag[5] = TRUE;
					eskind[5] = 12;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 14;
				}
				else if (move == 14) {
					bosscount--;
					if (bosscount < 0) {
						move = 15;
					}
				}
				else if (move == 15) {
					esflag[6] = TRUE;
					eskind[6] = 17;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 16;
				}
				else if (move == 16) {
					bosscount--;
					if (bosscount < 0) {
						move = 17;
					}
				}
				else if (move == 17) {
					esflag[0] = TRUE;
					eskind[0] = 14;
					esx[0] = epx + 3;
					esy[0] = epy;
					bosscount = 10;
					move = 18;
				}
				else if (move == 18) {
					bosscount--;
					if (bosscount < 0) {
						move = 19;
					}
				}
				else if (move == 19) {
					esflag[1] = TRUE;
					eskind[1] = 19;
					esx[1] = epx + 3;
					esy[1] = epy;
					bosscount = 10;
					move = 20;
				}
				else if (move == 20) {
					bosscount--;
					if (bosscount < 0) {
						move = 21;
					}
				}
				else if (move == 21) {
					esflag[2] = TRUE;
					eskind[2] = 5;
					esx[2] = epx + 3;
					esy[2] = epy;
					bosscount = 10;
					move = 22;
				}
				else if (move == 22) {
					bosscount--;
					if (bosscount < 0) {
						move = 23;
					}
				}
				else if (move == 23) {
					esflag[3] = TRUE;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
					bosscount = 10;
					move = 24;
				}
				else if (move == 24) {
					bosscount--;
					if (bosscount < 0) {
						move = 25;
					}
				}
				else if (move == 25) {
					esflag[4] = TRUE;
					eskind[4] = 13;
					esx[4] = epx + 3;
					esy[4] = epy;
					bosscount = 10;
					move = 26;
				}
				else if (move == 26) {
					bosscount--;
					if (bosscount < 0) {
						move = 27;
					}
				}
				else if (move == 27) {
					esflag[5] = TRUE;
					eskind[5] = 16;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 28;
				}
				else if (move == 28) {
					bosscount--;
					if (bosscount < 0) {
						move = 29;
					}
				}
				else if (move == 29) {
					esflag[6] = TRUE;
					eskind[6] = 11;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 30;
				}
				else if (move == 30) {
					epx += 3;
					if (epx > 250) {
						move = 31;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 31) {
					epx -= 3;
					if (epx < 50) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 32) {
					epx += 2;
					if (epx > 250) {
						move = 33;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}
				else if (move == 33) {
					epx -= 3;
					if (epx < 50) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}

			}
		}
		else if (No == 2) {
			DrawFormatString(320, 3, Cr, "Staga:HP");
			if (nowhp > 0) {//���݂���Ƃ��̂ݓ���
				if (move == 0) {
					epx += 2;
					if (epx > 570) {
						move = 1;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 1) {
					epx -= 2;
					if (epx < 365) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 2) {
					if (epx < 440) {
						epx += 2;
					}
					else if (epx > 455) {
						epx -= 2;
					}
					else {
						move = 3;
						bosscount = 15;
					}
				}
				else if (move == 3) {
					bosscount--;
					if (bosscount < 0) {
						move = 4;
						bosscount = 30;
					}
				}
				else if (move == 4) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(365 + i * 40, 70, 8);
					}
					move = 5;
				}
				else if (move == 5) {
					epx += 1;
					if (epx > 570) {
						move = 6;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[1] = 1;
							}
							else {//�������E��
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[2] = 3;
							}
							else {//�������E��
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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
					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 6) {
					epx -= 1;
					if (epx < 365) {
						move = 5;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[1] = 1;
							}
							else {//�������E��
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//�����ɂ���
								eskind[2] = 3;
							}
							else {//�������E��
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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

					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 7) {
					if (epx < 440) {
						epx += 2;
					}
					else if (epx > 455) {
						epx -= 2;
					}
					else {
						if (nowhp < 25) {
							move = 8;
						}
						else {
							move = 0;
						}
						bosscount = 90;
					}
				}
				else if (move == 8) {
					epx += 3;
					if (epx > 570) {
						move = 9;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 10;
						bosscount = 90;
					}
				}
				else if (move == 9) {
					epx -= 3;
					if (epx < 365) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}

						if (count % 600 == 0) {
							move = 10;
							bosscount = 90;
						}
					}
				}
				else if (move == 10) {
					if (epx < 440) {
						epx += 3;
					}
					else if (epx > 455) {
						epx -= 3;
					}
					else {
						move = 11;
						bosscount = 15;
					}
				}
				else if (move == 11) {
					bosscount--;
					if (bosscount < 0) {
						move = 12;
						bosscount = 30;
					}
				}
				else if (move == 12) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(365 + i * 40, 70, 8);
					}
					move = 13;
				}
				else if (move == 13) {
					esflag[5] = TRUE;
					eskind[5] = 12;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 14;
				}
				else if (move == 14) {
					bosscount--;
					if (bosscount < 0) {
						move = 15;
					}
				}
				else if (move == 15) {
					esflag[6] = TRUE;
					eskind[6] = 17;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 16;
				}
				else if (move == 16) {
					bosscount--;
					if (bosscount < 0) {
						move = 17;
					}
				}
				else if (move == 17) {
					esflag[0] = TRUE;
					eskind[0] = 14;
					esx[0] = epx + 3;
					esy[0] = epy;
					bosscount = 10;
					move = 18;
				}
				else if (move == 18) {
					bosscount--;
					if (bosscount < 0) {
						move = 19;
					}
				}
				else if (move == 19) {
					esflag[1] = TRUE;
					eskind[1] = 19;
					esx[1] = epx + 3;
					esy[1] = epy;
					bosscount = 10;
					move = 20;
				}
				else if (move == 20) {
					bosscount--;
					if (bosscount < 0) {
						move = 21;
					}
				}
				else if (move == 21) {
					esflag[2] = TRUE;
					eskind[2] = 5;
					esx[2] = epx + 3;
					esy[2] = epy;
					bosscount = 10;
					move = 22;
				}
				else if (move == 22) {
					bosscount--;
					if (bosscount < 0) {
						move = 23;
					}
				}
				else if (move == 23) {
					esflag[3] = TRUE;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
					bosscount = 10;
					move = 24;
				}
				else if (move == 24) {
					bosscount--;
					if (bosscount < 0) {
						move = 25;
					}
				}
				else if (move == 25) {
					esflag[4] = TRUE;
					eskind[4] = 13;
					esx[4] = epx + 3;
					esy[4] = epy;
					bosscount = 10;
					move = 26;
				}
				else if (move == 26) {
					bosscount--;
					if (bosscount < 0) {
						move = 27;
					}
				}
				else if (move == 27) {
					esflag[5] = TRUE;
					eskind[5] = 16;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 28;
				}
				else if (move == 28) {
					bosscount--;
					if (bosscount < 0) {
						move = 29;
					}
				}
				else if (move == 29) {
					esflag[6] = TRUE;
					eskind[6] = 11;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 30;
				}
				else if (move == 30) {
					epx += 3;
					if (epx > 570) {
						move = 31;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 31) {
					epx -= 3;
					if (epx < 365) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 32) {
					epx += 2;
					if (epx > 570) {
						move = 33;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}
				else if (move == 33) {
					epx -= 3;
					if (epx < 365) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}

			}
		}	
		break;
	case 99://2PlayerMode�ł͂Ȃ�
		break;
	default:
		*errorcheck = 6;//�Ăяo����Ȃ��͂�
		break;
	}

	/*HP�\���Ƌ@�̕\��*/
	if (nowhp > 0) {
		if (No == 1) {
			DrawBox(80, 6, 91 + 200 * nowhp / maxhp, 14, HPCr, TRUE);// HP��`��
		}
		else if (No == 2) {
			DrawBox(390, 6, 402 + 200 * nowhp / maxhp, 14, HPCr, TRUE);// HP��`��
		}
		if (protectcount <= 0 || count % 5 < 3)DrawGraph(epx, epy, BossGraphic[ekind - 11], TRUE);//�@��
	}
	/*�e�̓����ƕ`��*/
	for (i = 0; i < 7; i++) {
		if (esflag[i] == TRUE) {
			switch (eskind[i]) {
			case 0://��
				esy[i] += 3;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 1://������
				esy[i] += 3;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 2://�����E
				esy[i] += 3;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 3://��
				esy[i] += 3;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 4://�E
				esy[i] += 3;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 5://���i�����j
				esy[i] += 5;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 6://���Ȃ荶
				esy[i] += 3;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 7://���Ȃ�E
				esy[i] += 3;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 8://��������
				esy[i] += 3;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 9://�������E
				esy[i] += 3;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 10://��
				esy[i] += 5;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 11://��������
				esy[i] += 5;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 12://�������E
				esy[i] += 5;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 13://��
				esy[i] += 5;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 14://�E
				esy[i] += 5;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 15://���i�����j
				esy[i] += 8;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 16://���Ȃ荶
				esy[i] += 5;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 17://���Ȃ�E
				esy[i] += 5;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 18://������
				esy[i] += 5;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 19://�����E
				esy[i] += 5;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//�e
				break;
			case 30://Staga�̋Z
				break;
			default:
				break;
			}
			if (No == 1) {
				if (esy[i] > MAXMAPYALL - 30 || esx[i] > MAXMAPX1 - 16 || esx[i] < -10)esflag[i] = FALSE;// �[�ɓ��B���ɏ�����
			}
			else if (No == 2) {
				if (esy[i] > MAXMAPYALL - 30 || esx[i] > MAXMAPX2 - 16 || esx[i] < MAXMAPX1 + 10)esflag[i] = FALSE;// �[�ɓ��B���ɏ�����
			}
			
		}
	}

	/*���Ԍo�߂ɂ�鏈��*/
	if (protectcount > -5)protectcount--;


}//�{�X�̓����Ɋւ��鏈��

int Mode2Boss::BossHP(int damage) {
	nowhp -= damage;
	if (nowhp < 0)nowhp = 0;
	if (damage > 0) {//�_���[�W���󂯂Ă���
		protectcount = 15;
	}
	return nowhp;
}

void Mode2Boss::BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*protect = protectcount;
	for (int i = 0; i < 5; i++) {
		shotx[i] = esx[i];
		shoty[i] = esy[i];
		shotkind[i] = eskind[i];
		shotflag[i] = esflag[i];
	}
}

/*�X�e�[�W���߂̍ۂ̓G�o���p�֐�*/
void NormalStage_StartPrepare(int stage, int *errorcheck, Mode2Enemy Enemy[],int No) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	int i, j;
	int enemyxnum = 0, enemyynum = 0;//���ɕ��ԑ����A�c�ɕ��ԑ���
	int Enemypx[MAX1PlayerENEMY] = {}, Enemypy[MAX1PlayerENEMY] = {};//�G�@�̍��W�w��
	int Enemykindr[MAX1PlayerENEMY] = {};//�G�@�̎��
	int startx;//�G��x�̒[�̍��W
	int stageenkind = 0;//�X�e�[�W�ɂ��G�@�̎�ސ�
						/*�X�e�[�W���̓G��*/
	switch (stage) {
	case 1:
		enemyxnum = 5;
		enemyynum = 3;
		if (No == 1) {
			startx = 55;
		}
		else if (No == 2) {
			startx = 365;
		}
		stageenkind = 5;
		break;
	case 2:
		enemyxnum = 5;
		enemyynum = 4;
		if (No == 1) {
			startx = 55;
		}
		else if (No == 2) {
			startx = 365;
		}
		stageenkind = 6;
		break;
	case 3:
		enemyxnum = 7;
		enemyynum = 4;
		if (No == 1) {
			startx = 15;
		}
		else if (No == 2) {
			startx = 325;
		}
		stageenkind = 6;
		break;
	case 4:
		enemyxnum = 7;
		enemyynum = 5;
		if (No == 1) {
			startx = 15;
		}
		else if (No == 2) {
			startx = 325;
		}
		stageenkind = 7;
		break;
	default://stage5�̓{�X
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

/*�ŏI���*/
void Mode2RESULT(int *ErrorCheck, int gameflag, int point1, int point2) {
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

	//�t�H���g���쐬���쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	int FontHandle = CreateFontToHandle(NULL, 15, 6);

	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/result.mp3");

	bool Key = TRUE;

	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y

	do {
		if (CheckHitKeyAll() == 0)Key = FALSE;//�L�[����P���𗣂�����

		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 && Key == FALSE) {
			ESCGameEnd(ErrorCheck);//�����I��
			Key = TRUE;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);
			return;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
			break;
		}

		/*��ʕ\��*/
		SetFontSize(32);
		DrawFormatString(150, 20, Cr[6], "2Player Mode Finish!!");
		SetFontSize(16);
		DrawFormatString(100, 70, Cr[2], "Player1");
		DrawFormatString(400, 70, Cr[2], "Player2");
		if (gameflag == 1) {//Player1�̂݃N���A
			DrawFormatString(100, 90, Cr[3], "Clear!");
			DrawFormatString(400, 90, Cr[0], "Not Clear...");
		}
		else if (gameflag == 2) {//Player2�̂݃N���A
			DrawFormatString(400, 90, Cr[3], "Clear!");
			DrawFormatString(100, 90, Cr[0], "Not Clear...");
		}
		else if (gameflag == 3) {//�����Ƃ��N���A
			DrawFormatString(100, 90, Cr[3], "Clear!");
			DrawFormatString(400, 90, Cr[3], "Clear!");
		}
		DrawFormatString(100, 150, Cr[8], "Get Points : %d", point1);
		DrawFormatString(400, 150, Cr[8], "Get Points : %d", point2);
		DrawFormatString(200, 400, Cr[5], "Please SPACE or ENTER Key...");
		SetFontSize(24);
		if (point1 > point2) {
			DrawFormatString(200, 200, Cr[7], "Player1 Win!!");
		}
		else if (point1 < point2) {
			DrawFormatString(200, 200, Cr[7], "Player2 Win!!");
		}
		else {
			if (gameflag == 1) {
				DrawFormatString(200, 200, Cr[7], "Player1 Win!!");
			}
			else if (gameflag == 2) {
				DrawFormatString(200, 200, Cr[7], "Player2 Win!!");
			}
			else if (gameflag == 3) {
				DrawFormatString(220, 200, Cr[7], "Draw...");
			}
		}

		/*���̑��̏���*/

		ScreenFlip();

	} while (1);//�I�����Ȃ�����

	SetFontSize(16);
	ClearDrawScreen(); // ��ʂ�����
	ScreenFlip();
	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);
}

//////////////////////////////////////////////////////////////////
//     2Player mode�@main�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@   //
//////////////////////////////////////////////////////////////////
int Player2mode(int *ErrorCheck) {//2Player mode�@main

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
	DrawString(200, 300, "�G", Cr[8]);
	DrawString(200, 330, "�G�̓�����,�F���ƂɌ��܂��Ă���.", Cr[8]);
	DrawString(200, 350, "�^�C�g����ʂ�Contents�Ŋm�F�ł���.", Cr[8]);
	ScreenFlip();

	Mode2Player Player1, Player2;
	Mode2Enemy NormalEnemy1[MAX1PlayerENEMY], NormalEnemy2[MAX1PlayerENEMY];
	Mode2Boss Boss[2];
	Fps fps;
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic[2], BossGraphic[6];
	// PNG�摜�̃������ւ̕����ǂݍ���
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);//�ēǂݍ���
	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);//�ēǂݍ���
	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);//�ēǂݍ���
	i = LoadDivGraph("../exe/package/paint/Player2.png", 2, 2, 1, 40, 40, MyGraphic);
	if (i == -1)LoadDivGraph("./package/paint/Player2.png", 2, 2, 1, 40, 40, MyGraphic);//�ēǂݍ���
	int FontHandle = CreateFontToHandle(NULL, 16, 3);

	int gameflag = 0;//0:�X�^�[�g�� 1�`�R:�Q�[���I�� -1:�G���[
	int stage[2] = {};//���݃X�e�[�W
	int gamecount = 1;//�Q�[��������
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind[2] = {};//�X�e�[�W�̎�� 1:�m�[�}���X�e�[�W 2:�{�X�X�e�[�W 3:�Q�[���N���A 4:�Q�l�Ƃ��N���A 5:���̑� (0:�G���[)
	int playerpoint[2] = {};
	bool clearflag[2] = {};//�X�e�[�W�N���A
	bool clearcheckflag[2] = {};//�X�e�[�W�N���A����p
	int clearcount[2] = {};//�X�e�[�W�N���A���玟�̃X�e�[�W�̏����܂ł̎���
	int ppx[2] = {}, ppy[2] = {};//���@��x���W��y���W

	//�t�H���g���쐬���쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle�ɕۑ�����
	int FontHandle2 = CreateFontToHandle(NULL, 30, 8);//�傫������
	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/battle.mp3");
	if (SHandle == -1) SHandle = LoadSoundMem("./package/bgm/battle.mp3");//�ēǂݍ���

	i = 0;
	/////**2Player Mode Start**/////
	SetFontSize(14);
	/*�r�������I������*/
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		ESCGameEnd(ErrorCheck);//�����I��
	}

	if (*ErrorCheck > 0 || *ErrorCheck == -1) {
		// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
		for (i = 0; i < 10; i++) {
			DeleteGraph(PlayerShotGraphic[i]);
		}
		for (i = 0; i < 12; i++) {
			DeleteGraph(NormalEnemyGraphic[i]);
		}
		for (i = 0; i < 6; i++) {
			DeleteGraph(BossGraphic[i]);
		}
		for (i = 0; i < 2; i++) {
			DeleteGraph(MyGraphic[i]);
		}
		// �T�E���h�n���h���̍폜
		DeleteSoundMem(SHandle);
		return -1;//error�Ȃ狭���I��
	}

	if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
		*ErrorCheck = 1;
		// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
		for (i = 0; i < 10; i++) {
			DeleteGraph(PlayerShotGraphic[i]);
		}
		for (i = 0; i < 12; i++) {
			DeleteGraph(NormalEnemyGraphic[i]);
		}
		for (i = 0; i < 6; i++) {
			DeleteGraph(BossGraphic[i]);
		}
		for (i = 0; i < 2; i++) {
			DeleteGraph(MyGraphic[i]);
		}
		// �T�E���h�n���h���̍폜
		DeleteSoundMem(SHandle);
		return -1;        // �G���[���N�����烋�[�v�𔲂���
	}

	/*����������*/
	Player1.StartSet(1);
	Player2.StartSet(2);
	for (i = 0; i < MAX1PlayerENEMY; i++) {
		NormalEnemy1[i].StartSet();
		NormalEnemy2[i].StartSet();
	}
	stage[0] = 0;
	stage[1] = 0;
	clearcheckflag[0] = TRUE;
	clearcheckflag[1] = TRUE;
	clearcount[0] = 300;
	clearcount[1] = 300;
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y

	while (gameflag == 0) {

		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}
		/*�r�������I������*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
		}
		fps.Update();	//�X�V
		fps.Wait();		//�ҋ@

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
			for (i = 0; i < 10; i++) {
				DeleteGraph(PlayerShotGraphic[i]);
			}
			for (i = 0; i < 12; i++) {
				DeleteGraph(NormalEnemyGraphic[i]);
			}
			for (i = 0; i < 6; i++) {
				DeleteGraph(BossGraphic[i]);
			}
			for (i = 0; i < 2; i++) {
				DeleteGraph(MyGraphic[i]);
			}
			return -1;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}

		ClearDrawScreen(); // ��ʂ�����
		/*���ꂼ��̃v���C���[�̃X�e�[�W�J�n������*/
		/*Player1*/
		if (clearflag[0] == TRUE) {
			/*�X�e�[�W�N���A������*/
			stage[0]++;
			clearcount[0] = 120;
			clearflag[0] = FALSE;
			clearcheckflag[0] = FALSE;
			if (stage[0] < 5) {
				Player1.PointPlus(100);
				stagekind[0] = 1;//�m�[�}���X�e�[�W
				NormalStage_StartPrepare(stage[0], ErrorCheck, NormalEnemy1, 1);
			}
			else if (stage[0] == 5) {
				Player1.PointPlus(100);
				stagekind[0] = 2;//�{�X�X�e�[�W
				for (i = 0; i < MAX1PlayerENEMY; i++) {
					NormalEnemy1[i].StartSet();
				}
				Boss[0].StartSet(stage[0], 1);
				for (i = 0; i < 5; i++) {
					NormalEnemy1[i].AppearEnemy(55 + i * 40, 70, 8);
				}
			}
			else if (stage[0] == 6) {
				stagekind[0] = 3;//�S�X�e�[�W�N���A
				clearcount[0] = 3600;
			}
			Player1.StartSet(3);
		}

		/*Player2*/
		if (clearflag[1] == TRUE) {
			/*�X�e�[�W�N���A������*/
			stage[1]++;
			clearcount[1] = 120;
			clearflag[1] = FALSE;
			clearcheckflag[1] = FALSE;
			if (stage[1] < 5) {
				Player2.PointPlus(100);
				stagekind[1] = 1;//�m�[�}���X�e�[�W
				NormalStage_StartPrepare(stage[1], ErrorCheck, NormalEnemy2, 2);
			}
			else if (stage[1] == 5) {
				Player2.PointPlus(100);
				stagekind[1] = 2;//�{�X�X�e�[�W
				for (i = 0; i < MAX1PlayerENEMY; i++) {
					NormalEnemy2[i].StartSet();
				}
				Boss[1].StartSet(stage[1], 2);
				for (i = 0; i < 5; i++) {
					NormalEnemy2[i].AppearEnemy(365 + i * 40, 70, 8);
				}
			}
			else if (stage[1] == 6) {
				stagekind[1] = 3;//�S�X�e�[�W�N���A
				clearcount[1] = 3600;
			}
			Player2.StartSet(4);
		}

		/*�X�e�[�W�N���A����*/
		if (stagekind[0] == 1) {//�m�[�}���X�e�[�W
			clearcheckflag[0] = TRUE;
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				if (NormalEnemy1[i].EnemyExistCheck() == TRUE) {
					clearcheckflag[0] = FALSE;
				}
			}
		}
		else if (stagekind[0] == 2) {//�{�X�X�e�[�W
			if (Boss[0].BossHP(0) == 0) {
				clearcheckflag[0] = TRUE;
			}
		}

		if (stagekind[1] == 1) {//�m�[�}���X�e�[�W
			clearcheckflag[1] = TRUE;
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				if (NormalEnemy2[i].EnemyExistCheck() == TRUE) {
					clearcheckflag[1] = FALSE;
				}
			}
		}
		else if (stagekind[1] == 2) {//�{�X�X�e�[�W
			if (Boss[1].BossHP(0) == 0) {
				clearcheckflag[1] = TRUE;
			}
		}

		for (i = 0; i < 2; i++) {
			if (clearcheckflag[i] == TRUE) {
				clearcount[i]--;
				if (clearcount[i] < 0) {
					clearflag[i] = TRUE;
				}
			}
		}

		/*�e�v���C���[�̓����ƕ`��*/
		if (stagekind[0] < 3) {
			Player1.PlayerMove1(ErrorCheck, MyGraphic[0], PlayerShotGraphic);
			Player1.PlayerPosition(&ppx[0], &ppy[0]);
		}
		if (stagekind[1] < 3) {
			Player2.PlayerMove2(ErrorCheck, MyGraphic[1], PlayerShotGraphic);
			Player2.PlayerPosition(&ppx[1], &ppy[1]);
		}

		/*�G�@�̓����ƕ`��,�����蔻��*/
		//*Player1*/
		if (stagekind[0] < 3) {
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				NormalEnemy1[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx[0], ppy[0], 1);
			}
			Player1.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy1, stage[0]);
			if (stagekind[0] == 2) {//�{�X�X�e�[�W
				Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx[0], ppy[0], 1, NormalEnemy1);
				Player1.BossStage_CollisionDetection(ErrorCheck, Boss, 1);
			}
		}
	
		//*Player2*/
		if (stagekind[1] < 3) {
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				NormalEnemy2[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx[1], ppy[1], 2);
			}
			Player2.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy2, stage[1]);
			if (stagekind[1] == 2) {//�{�X�X�e�[�W
				Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx[1], ppy[1], 2, NormalEnemy2);
				Player2.BossStage_CollisionDetection(ErrorCheck, Boss, 2);
			}
		}
		

		/////**���**/////
		/*Player1*/
		DrawBox(0, 0, MAXMAPX1 + 5, MAXMAPYALL, Cr[9], FALSE);// �l�p�`��`��
		if (stagekind[0] < 3) {
			Player1.PlayerShotColor(PlayerShotKind);
			Player1.PlayerShotCombo(ShotCombonum);
			DrawFormatString(0, 370, Cr[9], "Player1 : Stage %d : Total Points %d", stage[0], Player1.GetPoint());
			DrawString(0, 387, "C�L�[:�� B�L�[:�E", Cr[9]);
			DrawFormatString(0, 404, Cr[9], "Q:�V���b�g |    |");
			DrawStringToHandle(0, 421, "W", Cr[9], FontHandle);
			DrawFormatString(8, 421, Cr[9], ":�V���b�g |    |");
			DrawFormatString(0, 438, Cr[9], "E:�V���b�g |    |");
			for (i = 0; i < 3; i++) {
				DrawFormatString(130, 404 + i * 17, Cr[PlayerShotKind[i]], "�R���{:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(99, 404 + i * 17, "��", Cr[0]);
					break;
				case 1:
					DrawString(99, 404 + i * 17, "��", Cr[1]);
					break;
				case 2:
					DrawString(99, 404 + i * 17, "��", Cr[2]);
					break;
				case 3:
					DrawString(99, 404 + i * 17, "��", Cr[3]);
					break;
				case 4:
					DrawString(99, 404 + i * 17, "��", Cr[4]);
					break;
				case 5:
					DrawString(99, 404 + i * 17, "��", Cr[5]);
					break;
				case 6:
					DrawString(92, 404 + i * 17, "�Ԏ�", Cr[6]);
					break;
				case 7:
					DrawString(99, 404 + i * 17, "��", Cr[7]);
					break;
				default:
					DrawString(99, 404 + i * 17, "��", Cr[9]);
					break;
				}
			}

			if (stage[0] == 0) {//�J�n�O��ʕ\��
				if (clearcount[0] > 180) {
					DrawStringToHandle(20, 50, "Player 1", Cr[6], FontHandle2);
					DrawStringToHandle(20, 100, "Please Wait...", Cr[6], FontHandle2);
				}
				else if (clearcount[0] > 120) {
					DrawStringToHandle(140, 70, "3", Cr[0], FontHandle2);
				}
				else if (clearcount[0] > 60) {
					DrawStringToHandle(140, 70, "2", Cr[2], FontHandle2);
				}
				else {
					DrawStringToHandle(140, 70, "1", Cr[3], FontHandle2);
				}
			}
		}
		else if (stagekind[0] == 3) {
			DrawStringToHandle(15, 50, "Player1 Clear!", Cr[0], FontHandle2);
			DrawStringToHandle(15, 90, "Please wait by Player2 end...", Cr[4], FontHandle);
			DrawFormatString(15, 150, Cr[7], "Player1 Total Points:%d", Player1.GetPoint());
			DrawFormatString(15, 220, Cr[8], "Player2 Time Out:");
			if (clearcount[0] > 1200) {
				DrawFormatString(155, 220, Cr[3], "%d", clearcount[0] / 60);
			}
			else {
				DrawFormatString(155, 220, Cr[2], "%d", clearcount[0] / 60);
			}	
			clearcount[0]--;
		}

		/*Player2*/
		DrawBox(MAXMAPX1 + 15, 0, MAXMAPX2 + 5, MAXMAPYALL, Cr[9], FALSE);// �l�p�`��`��
		if (stagekind[1] < 3) {
			Player2.PlayerShotColor(PlayerShotKind);
			Player2.PlayerShotCombo(ShotCombonum);
			DrawFormatString(320, 370, Cr[9], "Player2 : Stage %d : Total Points %d", stage[1], Player2.GetPoint());
			DrawString(320, 387, "LEFT�L�[:�� RIGHT�L�[:�E", Cr[9]);
			DrawFormatString(320, 404, Cr[9], "I:�V���b�g |    |");
			DrawFormatString(320, 421, Cr[9], "O:�V���b�g |    |");
			DrawFormatString(320, 438, Cr[9], "P:�V���b�g |    |");
			for (i = 0; i < 3; i++) {
				DrawFormatString(450, 404 + i * 17, Cr[PlayerShotKind[i]], "�R���{:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(419, 404 + i * 17, "��", Cr[0]);
					break;
				case 1:
					DrawString(419, 404 + i * 17, "��", Cr[1]);
					break;
				case 2:
					DrawString(419, 404 + i * 17, "��", Cr[2]);
					break;
				case 3:
					DrawString(419, 404 + i * 17, "��", Cr[3]);
					break;
				case 4:
					DrawString(419, 404 + i * 17, "��", Cr[4]);
					break;
				case 5:
					DrawString(419, 404 + i * 17, "��", Cr[5]);
					break;
				case 6:
					DrawString(412, 404 + i * 17, "�Ԏ�", Cr[6]);
					break;
				case 7:
					DrawString(419, 404 + i * 17, "��", Cr[7]);
					break;
				default:
					DrawString(419, 404 + i * 17, "��", Cr[9]);
					break;
				}
			}

			if (stage[1] == 0) {//�J�n�O��ʕ\��
				if (clearcount[1] > 180) {
					DrawStringToHandle(370, 50, "Player 2", Cr[6], FontHandle2);
					DrawStringToHandle(370, 100, "Please Wait...", Cr[6], FontHandle2);
				}
				else if (clearcount[1] > 120) {
					DrawStringToHandle(460, 70, "3", Cr[0], FontHandle2);
				}
				else if (clearcount[1] > 60) {
					DrawStringToHandle(460, 70, "2", Cr[2], FontHandle2);
				}
				else {
					DrawStringToHandle(460, 70, "1", Cr[3], FontHandle2);
				}
			}
		}
		else if (stagekind[1] == 3) {
			DrawStringToHandle(330, 50, "Player2 Clear!", Cr[1], FontHandle2);
			DrawStringToHandle(330, 90, "Please wait by Player1 end...", Cr[4], FontHandle);
			DrawFormatString(330, 150, Cr[7], "Player2 Total Points:%d", Player2.GetPoint());
			DrawFormatString(330, 220, Cr[8], "Player1 Time Out:");
			if (clearcount[1] > 1200) {
				DrawFormatString(470, 220, Cr[3], "%d", clearcount[1] / 60);
			}
			else {
				DrawFormatString(470, 220, Cr[2], "%d", clearcount[1] / 60);
			}
			clearcount[1]--;
		}

		gamecount++;//���Ԍo��
		if (gamecount > 100000000)gamecount = 0;//�o�O�̖h�~
		if (gamecount > 150000000)*ErrorCheck = 4;//���Ԍo�߂�����

		/*�S�X�e�[�W�N���A����*/
		if (stagekind[0] == 3 && stagekind[1] == 3) {
			gameflag = 3;//����I��
		}
		if (stagekind[0] == 3) {
			if (clearcount[0] < 0 && stagekind[1] != 3) {//���Ԍo�߂����̂�Player2���N���A���Ă��Ȃ�
				gameflag = 1;//Player1�̂݃N���A,Player2�͋����I��
			}
		}
		if (stagekind[1] == 3) {
			if (clearcount[1] < 0 && stagekind[0] != 3) {//���Ԍo�߂����̂�Player1���N���A���Ă��Ȃ�
				gameflag = 2;//Player2�̂݃N���A,Player1�͋����I��
			}
		}

		ScreenFlip();
	}//���[�v�����܂�

	if (gameflag > 0) {//�N���A�������Ƃɂ���ďI��
		Mode2RESULT(ErrorCheck, gameflag, Player1.GetPoint(), Player2.GetPoint());
	}

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	for (i = 0; i < 10; i++) {
		DeleteGraph(PlayerShotGraphic[i]);
	}
	for (i = 0; i < 12; i++) {
		DeleteGraph(NormalEnemyGraphic[i]);
	}
	for (i = 0; i < 6; i++) {
		DeleteGraph(BossGraphic[i]);
	}
	for (i = 0; i < 2; i++) {
		DeleteGraph(MyGraphic[i]);
	}
	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);

	return 0;

}
