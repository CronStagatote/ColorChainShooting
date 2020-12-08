#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/*Contents*/

void Contents1_ScoreBoard(int *ErrorCheck, int SE,int Handle);
void Contents2_Enemy(int *ErrorCheck);
void Contents3_Operation(int *ErrorCheck);

int Contents(int *ErrorCheck) {//�I�v�V�����Ƒ�������Ȃ�
    //�R���e���c���j���[
	int gameflag = -1, command = 0, commandtime = 0;
	bool Key = TRUE;
	int veryhardcount = 0;
	int Cr,Cr2;
	int Handle[12];
	int SE = LoadSoundMem("../exe/package/bgm/select.mp3");
	if (SE == -1)SE = LoadSoundMem("./package/bgm/select.mp3");

	// �@�f�t�H���g�̃t�H���g�ŁA�t�H���g���쐬��
	// �쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	int FontHandle = CreateFontToHandle(NULL, 15, 3);
	int FontHandle2 = CreateFontToHandle(NULL, 30, 3);

	// �F�̒l���擾
	Cr = GetColor(240, 240, 240);
	Cr2 = GetColor(240, 30, 30);
	int Cr3 = GetColor(255, 150, 30);

	/*���[�h*/
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	ClearDrawScreen(); // ��ʂ�����
	DrawString(250, 250, "Now Lording...", Cr);
	DrawString(50, 320, "Contents Mode", Cr);
	DrawString(50, 340, "���̃��[�h�ł͗l�X�ȏ������邱�Ƃ��ł���ق�,", Cr);
	DrawString(50, 360, "�m�[�}���G���U�����Ă��Ȃ��X�e�[�W10�ŗV�ׂ�p�Y�����[�h,", Cr);
	DrawString(50, 380, "�{�X�G�݂̂Ɛ킦��{�X���b�V���Ƃ��������[�h������.", Cr);
	DrawString(50, 400, "�����̃��[�h�ŗ��K��,Player1 Mode�ō����_��ڎw����!", Cr);
	ScreenFlip();

	// PNG�摜�̃������ւ̕����ǂݍ���
	veryhardcount = LoadDivGraph("../exe/package/paint/Select.png", 12, 4, 3, 32, 32, Handle);
	//�ēǂݍ���
	if (veryhardcount == -1)LoadDivGraph("./package/paint/Select.png", 12, 4, 3, 32, 32, Handle);

	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
	//�ēǂݍ���
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y

	veryhardcount = 0;
	Key = TRUE;//�{�^����������Ă��邱�Ƃɂ��Ă���
	do{
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
			Key = TRUE;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// �쐬�����t�H���g�f�[�^���폜����
			DeleteFontToHandle(FontHandle);
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);
			return -1;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �쐬�����t�H���g�f�[�^���폜����
			DeleteFontToHandle(FontHandle);
			// �T�E���h�n���h���̍폜
			DeleteSoundMem(SHandle);

			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			Key = FALSE;
		}
		else {//�L�[��������Ă���
			commandtime++;
			if (commandtime > 1000) {
				commandtime = 0;
				Key = FALSE;
			}
		}

		ClearDrawScreen(); // ��ʂ�����

		if (command < 10) {
			DrawStringToHandle(200, 100, "Contents", Cr2, FontHandle2);
			DrawString(240, 170, "1Player mode ���_�\:1", Cr);
			DrawString(240, 200, "�G�̎�ނƓ���:2", Cr);
			DrawString(240, 230, "��������ƃ��[��:3", Cr);
			DrawString(240, 260, "�p�Y�����[�h:4", Cr);
			DrawString(240, 290, "�{�X���b�V��:5", Cr);
			DrawString(240, 320, "�^�C�g���ɖ߂�:6", Cr);
			DrawStringToHandle(100, 410, "�㉺�L�[�������͐����L�[(1�`4)�őI���AENTER��������z�L�[�Ō���", Cr, FontHandle);

			if (command == 0) {
				DrawGraph(200, 160, Handle[0], TRUE);
			}
			else if (command == 1) {
				DrawGraph(200, 190, Handle[0], TRUE);
			}
			else if (command == 2) {
				DrawGraph(200, 220, Handle[0], TRUE);
			}
			else if (command == 3) {
				DrawGraph(200, 250, Handle[0], TRUE);
			}
			else if (command == 4) {
				DrawGraph(200, 280, Handle[0], TRUE);
			}
			else if (command == 5) {
				DrawGraph(200, 310, Handle[0], TRUE);
			}

			if (CheckHitKey(KEY_INPUT_1) == 1)command = 0;
			if (CheckHitKey(KEY_INPUT_2) == 1)command = 1;
			if (CheckHitKey(KEY_INPUT_3) == 1)command = 2;
			if (CheckHitKey(KEY_INPUT_4) == 1)command = 3;
			if (CheckHitKey(KEY_INPUT_5) == 1)command = 4;
			if (CheckHitKey(KEY_INPUT_6) == 1)command = 5;
		}
		else {
			DrawString(200, 100, "��Փx�I��\n(�{�X���b�V��)", Cr);
			DrawString(240, 200, "EASY", Cr);
			DrawString(240, 230, "NORMAL", Cr);
			DrawString(240, 260, "HARD", Cr);
			DrawString(240, 290, "Contents�ꗗ�ɖ߂�", Cr);
			if (command == 15) {
				DrawString(240, 320, "UNKNOWN", Cr2);
				DrawStringToHandle(100, 450, "S�������Ȃ��牺�L�[�������ƕʃ��[�h�ɕύX.", Cr3, FontHandle);
			}
			else if (command == 16) {
				DrawString(240, 320, "Stagatote_SP UNKNOWN", Cr2);
			}

			if (command != 16) {
				if (command == 13 || command == 15) {
					DrawStringToHandle(100, 355, "�{�X���b�V����1PlayerMode�ɓo�ꂷ��{�X4��(?)�ƘA�킷�郂�[�h�ł�.", Cr3, FontHandle);
				}
				else {
					DrawStringToHandle(100, 355, "�{�X���b�V����1PlayerMode�ɓo�ꂷ��{�X4�̂ƘA�킷�郂�[�h�ł�.", Cr3, FontHandle);
				}
				DrawStringToHandle(100, 370, "��Փx�ɂ�����炸,�A�C�e���g�p�s��,\n�X�e�[�W�N���A����HP�񕜂Ȃ��ƂȂ��Ă��܂�.", Cr3, FontHandle);
			}
			else {
				DrawStringToHandle(100, 370, "��Փx:UNKNOWN�ŗ��{�X�Ɛ킦�郂�[�h�ł�.\n���ʂ͈�ؕ\������܂���.", Cr3, FontHandle);
			}
			DrawStringToHandle(100, 430, "�㉺�L�[�������͐����L�[(1�`4)�őI���AENTER��������z�L�[�Ō���", Cr, FontHandle);

			if (command == 11) {
				DrawGraph(200, 190, Handle[0], TRUE);
			}
			else if (command == 12) {
				DrawGraph(200, 220, Handle[0], TRUE);
			}
			else if (command == 13) {
				DrawGraph(200, 250, Handle[0], TRUE);
			}
			else if (command == 14) {
				DrawGraph(200, 280, Handle[0], TRUE);
			}
			else if (command == 15 || command == 16) {
				DrawGraph(200, 310, Handle[0], TRUE);
			}
		}

		ScreenFlip();

		if ((CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && Key == FALSE) {
			PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			if (command == 0) {//1Player mode ���_�\
				Contents1_ScoreBoard(ErrorCheck, SE, Handle[0]);
				gameflag = 1;
			}
			else if (command == 1) {//�G�̎�ނƓ���
				Contents2_Enemy(ErrorCheck);
				gameflag = 2;
			}
			else if (command == 2) {//��������ƃ��[��
				Contents3_Operation(ErrorCheck);
				gameflag = 3;
			}
			else if (command == 3) {//�p�Y�����[�h
				DeleteSoundMem(SHandle);
				/*���[�h*/
				ClearDrawScreen(); // ��ʂ�����
				DrawString(250, 250, "Now Lording...", Cr);
				ScreenFlip();
				Player1mode(ErrorCheck, 20);
				SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
				//�ēǂݍ���
				if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
			}
			else if (command == 4) {//�{�X���b�V��
				command = 11;
			}
			else if (command == 5) {//�^�C�g���ɖ߂�
				gameflag = 0;
			}
			else if (command >= 11 && command != 14) {
				DeleteSoundMem(SHandle);
				SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
				//�ēǂݍ���
				if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
				/*���[�h*/
				ClearDrawScreen(); // ��ʂ�����
				DrawString(250, 250, "Now Lording...", Cr);
				ScreenFlip();
				if (command == 11) {
					Player1mode(ErrorCheck, 11);
				}
				else if (command == 12) {
					Player1mode(ErrorCheck, 12);
				}
				else if (command == 13) {
					Player1mode(ErrorCheck, 13);
				}
				else if (command == 15) {
					Player1mode(ErrorCheck, 14);
				}
				else if (command == 16) {
					Player1mode(ErrorCheck, 40);
				}
				command = 4;
			}
			else if (command == 14) {//�߂�
				command = 5;
				veryhardcount = 0;
			}

			Key = TRUE;
		}
		else if (CheckHitKey(KEY_INPUT_UP) == 1 && Key == FALSE) {
			if (command <= 0) {
				command = 0;
			}
			else if (command == 11) {
				command = 11;
			}
			else if (command == 16) {
				command = 14;
			}
			else {
				command--;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			Key = TRUE;
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Key == FALSE) {
			if (command == 5) {
				command = 5;
			}
			else if (command == 14) {
				command = 14;
				veryhardcount++;
				if (veryhardcount >= 5) {//�B���R�}���h
					command = 15;
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
			}
			else if (command == 15) {
				if (CheckHitKey(KEY_INPUT_S) == 1) {
					command = 16;
				}
			}
			else if (command >= 16) {
				command = 16;
			}
			else {
				command++;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			Key = TRUE;
		}
	} while (gameflag != 0);

	while (Key == TRUE) {//�L�[��������Ȃ��Ȃ�܂ő҂�
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �쐬�����t�H���g�f�[�^���폜����
			DeleteFontToHandle(FontHandle);
			return -1;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			Key = FALSE;
		}
	}

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle);
	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);

	return 0;
}//Contents Menu


void Contents1_ScoreBoard(int *ErrorCheck,int SE,int Handle) {
	/*���_�\*/
	bool KeyCheck = TRUE;//�L�[�{�[�h��������Ă��邩
	int Cr = GetColor(240, 240, 240);
	int commandtime = 0;
	int veryhardcount = 0;
	int command = 0;
	bool Key = TRUE;//�{�^����������Ă��邱�Ƃɂ��Ă���
	do {
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
			Key = TRUE;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//error�Ȃ狭���I��
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			Key = FALSE;
		}
		else {//�L�[��������Ă���
			commandtime++;
			if (commandtime > 1000) {
				commandtime = 0;
				Key = FALSE;
			}
		}

		ClearDrawScreen(); // ��ʂ�����

		DrawString(240, 100, "1Player mode ���_�\", Cr);
		DrawString(240, 170, "ALL", Cr);
		DrawString(240, 200, "EASY�̂�", Cr);
		DrawString(240, 230, "NORMAL�̂�", Cr);
		DrawString(240, 260, "HARD�̂�", Cr);
		DrawString(240, 290, "�߂�", Cr);
		if (command == 5)DrawString(240, 320, "UNKNOWN�̂�", Cr);
		DrawString(50, 400, "�㉺�L�[�������͐����L�[(1�`4)�őI���A\nENTER��������z�L�[�Ō���", Cr);

		if (command == 0) {
			DrawGraph(200, 160, Handle, TRUE);
		}
		else if (command == 1) {
			DrawGraph(200, 190, Handle, TRUE);
		}
		else if (command == 2) {
			DrawGraph(200, 220, Handle, TRUE);
		}
		else if (command == 3) {
			DrawGraph(200, 250, Handle, TRUE);
		}
		else if (command == 4) {
			DrawGraph(200, 280, Handle, TRUE);
		}
		else if (command == 5) {
			DrawGraph(200, 310, Handle, TRUE);
		}

		ScreenFlip();

		if ((CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && Key == FALSE) {
			PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			if (command == 0) {
				RankingFileCheck(ErrorCheck, 0, 100, 0);//���_�\���Ă�(callflag==10*�œǂݎ��̂�)
			}
			else if (command == 1) {
				RankingFileCheck(ErrorCheck, 0, 101, 0);//���_�\���Ă�(callflag==10*�œǂݎ��̂�)
			}
			else if (command == 2) {
				RankingFileCheck(ErrorCheck, 0, 102, 0);//���_�\���Ă�(callflag==10*�œǂݎ��̂�)
			}
			else if (command == 3) {
				RankingFileCheck(ErrorCheck, 0, 103, 0);//���_�\���Ă�(callflag==10*�œǂݎ��̂�)
			}
			else if (command == 4) {
				break;
			}
			else if (command == 5) {
				RankingFileCheck(ErrorCheck, 0, 104, 0);//���_�\���Ă�(callflag==10*�œǂݎ��̂�)
			}
			Key = TRUE;
		}
		else if (CheckHitKey(KEY_INPUT_UP) == 1 && Key == FALSE) {
			if (command <= 0) {
				command = 0;
			}
			else {
				command--;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			Key = TRUE;
		}
		else if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Key == FALSE) {
			if (command == 5) {
				command = 5;
			}
			else if (command == 4) {
				command = 4;
				veryhardcount++;
				if (veryhardcount >= 5) {//�B���R�}���h
					command = 5;
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
			}
			else {
				command++;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			Key = TRUE;
		}
	} while (1);

	while (KeyCheck == TRUE) {//�L�[��������Ȃ��Ȃ�܂ő҂�
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			KeyCheck = FALSE;
		}
	}
	
}//Contents1_ScoreBoard


void Contents2_Enemy(int *ErrorCheck) {
	/*�G�̎�ނƓ���*/
	bool KeyCheck = TRUE;//�L�[�{�[�h��������Ă��邩
	int Cr = GetColor(240, 240, 240);
	int NormalEnemyGraphic[20], BossGraphic[6];
	int page = -1;
	// PNG�摜�̃������ւ̕����ǂݍ���
	page = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//�ēǂݍ���
	if (page == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	page = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//�ēǂݍ���
	if (page == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	page = 0;
	do {

		ClearDrawScreen(); // ��ʂ�����
		/*���[�v�����p����*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//error�Ȃ狭���I��
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			KeyCheck = FALSE;
		}

		if (KeyCheck == FALSE) {//�L�[����񗣂��ꂽ
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				KeyCheck = TRUE;
				page++;
				if (page >= 3)break;//Z�L�[�������ꂽ�烋�[�v�𔲂���
			}
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		/*�����{��*/
		if (page == 0) {
			DrawString(230, 10, "Normal Enemy", Cr);
			DrawGraph(30, 50, NormalEnemyGraphic[0], TRUE);
			DrawString(30, 90, "�F:��\n�_���ꏊ:�^��", Cr);
			DrawGraph(230, 50, NormalEnemyGraphic[1], TRUE);
			DrawString(230, 90, "�F:��\n�_���ꏊ:���@��", Cr);
			DrawGraph(430, 50, NormalEnemyGraphic[2], TRUE);
			DrawString(430, 90, "�F:��\n�_���ꏊ:���@�E", Cr);

			DrawGraph(30, 150, NormalEnemyGraphic[3], TRUE);
			DrawString(30, 190, "�F:��\n�_���ꏊ:���@", Cr);
			DrawGraph(230, 150, NormalEnemyGraphic[4], TRUE);
			DrawString(230, 190, "�F:��\n�_���ꏊ:��", Cr);
			DrawGraph(430, 150, NormalEnemyGraphic[5], TRUE);
			DrawString(430, 190, "�F:��\n�_���ꏊ:�E", Cr);

			DrawGraph(30, 250, NormalEnemyGraphic[6], TRUE);
			DrawString(30, 290, "�F:�Ԏ�\n�U�����Ȃ�", Cr);
			DrawGraph(230, 250, NormalEnemyGraphic[7], TRUE);
			DrawString(230, 290, "�F:��\n���@�̓������_��", Cr);
			DrawGraph(430, 250, NormalEnemyGraphic[8], TRUE);
			DrawString(430, 290, "�F:��\n�_���ꏊ:���@\n", Cr);
			DrawString(20, 350, "���@�͓̂|���Ă��R���{�ɉ��Z���ꂸ�A�F���ς��Ȃ��B�ꗥ3�_.", Cr);

			DrawString(20, 400, "*Z�L�[�܂���ENTER�L�[�Ŏ��̃y�[�W��.", Cr);
		}
		else if (page == 1) {
			DrawString(230, 10, "Boss Enemy1", Cr);
			DrawGraph(30, 40, BossGraphic[0], TRUE);
			DrawString(100, 40, "����:Grad(�O���h)  �o���X�e�[�W:3", Cr);
			DrawString(100, 60, "HP > EASY:20 Normal:25 Hard:30", Cr);
			DrawString(100, 80, "����Z:�U���e  �F:��,��,��", Cr);

			DrawGraph(30, 120, BossGraphic[1], TRUE);
			DrawString(100, 120, "����:Cron(�N����)  �o���X�e�[�W:6", Cr);
			DrawString(100, 140, "HP > EASY:28 Normal:35 Hard:42", Cr);
			DrawString(100, 160, "����Z:���[�U�[  �F:��,��,��", Cr);

			DrawGraph(30, 220, BossGraphic[2], TRUE);
			DrawString(100, 220, "����:Erec(�G���N)  �o���X�e�[�W:9", Cr);
			DrawString(100, 240, "HP > EASY:38 Normal:48 Hard:58", Cr);
			DrawString(100, 260, "����Z:�ːi  �F:��,��,��", Cr);

			DrawGraph(30, 300, BossGraphic[3], TRUE);
			DrawString(100, 300, "����:Rain(���C��)  �o���X�e�[�W:11(LAST)", Cr);
			DrawString(100, 320, "HP > EASY:56 Normal:70 Hard:84", Cr);
			DrawString(100, 340, "����Z:�U���e,���[�U�[,�ːi  �F:�S", Cr);
			DrawGraph(30, 370, BossGraphic[5], TRUE);
			DrawString(100, 370, "(Rain�̕��g)", Cr);
			DrawString(100, 390, "HP: -  �_���[�W���󂯂�,Rain��HP��0�ɂȂ�Ɠ����ɏ���.", Cr);
			DrawString(100, 410, "������,�U�������1�b���x(��Փx�ɂ��ϓ�)�������~�܂�.", Cr);

			DrawString(20, 440, "*Z�L�[�܂���ENTER�L�[�Ŏ��̃y�[�W��.", Cr);
		}
		else if (page == 2) {
			DrawString(230, 10, "Boss Enemy2", Cr);

			DrawGraph(30, 40, BossGraphic[4], TRUE);
			DrawString(100, 40, "����:Staga(�X�^�K)  �o���X�e�[�W:5(2Player Mode)", Cr);
			DrawString(100, 60, "HP:50  ����Z:�m�[�}���G�i��)����", Cr);

			DrawGraph(30, 120, BossGraphic[4], TRUE);
			DrawGraph(34, 123, NormalEnemyGraphic[9], TRUE);
			DrawString(100, 120, "����:Stagatote_SP(�X�^�K�g�e�E�X�y�V����)", Cr);
			DrawString(100, 140, "Boss Rush�ɂĎc��HP15�ȏ��Rain��|���Əo��", Cr);
			DrawString(100, 160, "HP(HARD):66 (EASY,NORMAL�ł͏o�����Ȃ�)", Cr);
			DrawString(100, 180, "����Z:�m�[�}���G�i��)����,�o���A�V���b�g", Cr);
			DrawString(100, 200, "*����Z�O�Ƀ��[�v����\�͂�����*    �F:��", Cr);

			DrawString(230, 250, "�G�̒e�ɂ���", Cr);
			DrawGraph(30, 280, NormalEnemyGraphic[11], TRUE);
			DrawGraph(65, 280, NormalEnemyGraphic[12], TRUE);
			DrawGraph(100, 280, NormalEnemyGraphic[13], TRUE);
			DrawString(150, 280, "�ʏ�e.�������1�_���[�W.", Cr);
			DrawString(150, 300, "��ѕ��͗l�X.", Cr);

			DrawGraph(30, 330, NormalEnemyGraphic[14], TRUE);
			DrawString(70, 330, "�U���e.�������3�_���[�W.", Cr);
			DrawString(70, 350, "���@�Ɍ������Ă���.", Cr);

			DrawGraph(30, 380, NormalEnemyGraphic[10], TRUE);
			DrawString(70, 380, "�o���A�V���b�g.�������3�_���[�W.", Cr);
			DrawString(70, 400, "���@�̍U�����K�[�h����e(�ʏ�e�͎��@�̍U�������蔲����).", Cr);

			DrawString(20, 440, "*Z�L�[�܂���ENTER�L�[�Ŗ߂�.", Cr);
		}


		ScreenFlip();
	} while (1);

	while (KeyCheck == TRUE) {//�L�[��������Ȃ��Ȃ�܂ő҂�
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			KeyCheck = FALSE;
		}
	}

}//Contents2_Enemy


void Contents3_Operation(int *ErrorCheck) {
	/*������@�Ɠ��_�v�Z�Ȃ�*/
	bool KeyCheck = TRUE;//�L�[�{�[�h��������Ă��邩
	int Cr = GetColor(240, 240, 240);
	int page = 0;
	SetFontSize(12);
	SetFontThickness(4);

	do {

		ClearDrawScreen(); // ��ʂ�����
		/*���[�v�����p����*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//�����I��
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			SetFontSize(16);
			SetFontThickness(6);
			return;//error�Ȃ狭���I��
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			KeyCheck = FALSE;
		}

		if (KeyCheck == FALSE) {//�L�[����񗣂��ꂽ
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				KeyCheck = TRUE;
				page++;
				if (page >= 4)break;//Z�L�[�������ꂽ�烋�[�v�𔲂���
			}
		}

		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		/*�����{��*/
		if (page == 0) {
			DrawString(200, 20, "�������", Cr);
			DrawString(200, 40, "-1Player Mode-", Cr);
			DrawString(200, 60, "�ELEFT�L�[:���Ɉړ�", Cr);
			DrawString(200, 80, "�ERIGHT�L�[:�E�Ɉړ�", Cr);
			DrawString(200, 100, "�EZ�L�[:�V���b�g1", Cr);
			DrawString(200, 120, "�EX�L�[:�V���b�g2", Cr);
			DrawString(200, 140, "�EC�L�[:�V���b�g3", Cr);
			DrawString(200, 200, "-2Player Mode-", Cr);
			DrawString(50, 230, "<Player1>", Cr);
			DrawString(50, 250, "�EC�L�[:���Ɉړ�", Cr);
			DrawString(50, 270, "�EB�L�[:�E�Ɉړ�", Cr);
			DrawString(50, 290, "�EQ�L�[:�V���b�g1", Cr);
			DrawString(50, 310, "�EW�L�[:�V���b�g2", Cr);
			DrawString(50, 330, "�EE�L�[:�V���b�g3", Cr);
			DrawString(300, 230, "<Player2>", Cr);
			DrawString(300, 250, "�ELEFT�L�[:���Ɉړ�", Cr);
			DrawString(300, 270, "�ERIGHT�L�[:�E�Ɉړ�", Cr);
			DrawString(300, 290, "�EI�L�[:�V���b�g1", Cr);
			DrawString(300, 310, "�EO�L�[:�V���b�g2", Cr);
			DrawString(300, 330, "�EP�L�[:�V���b�g3", Cr);

			DrawString(100, 400, "*Z�L�[�܂���ENTER�L�[�Ŏ��̃y�[�W��.", Cr);
		}
		else if (page == 1) {
			DrawString(200, 20, "���_�ɂ���", Cr);
			DrawString(200, 40, "*1Player Mode", Cr);
			DrawString(100, 60, "<�m�[�}���X�e�[�W>", Cr);
			DrawString(50, 80,"��{,��̓|�����Ƃ�1�_.�������A�|�����Ƃ���\n�V���b�g�̃R���{(-����-)���ɂ���Ĉȉ��̂悤�ɕω�����.", Cr);
			DrawString(50, 110, "�E1�R���{�ɂ�,�|�����Ƃ��̓��_��2�{�ɂȂ�.", Cr);
			DrawString(50, 125, "�E�R���{���r�؂���,�܂�1�_�ɖ߂�.", Cr);
			DrawString(50, 140, "��", Cr);
			DrawString(50, 160, "1.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1)�_=1�_�@�v1�_", Cr);
			DrawString(50, 180, "2.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1*2)�_=2�_�@�v3�_", Cr);
			DrawString(50, 200, "3.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1*2*2)�_=4�_�@�v7�_", Cr);
			DrawString(50, 220, "4.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1*2*2*2)�_=8�_�@�v15�_", Cr);
			DrawString(50, 240, "5.X�V���b�g�ŐԂ̋@�̂�|��:(��{�_1)�_=1�_�@�v16�_", Cr);
			DrawString(50, 260, "6.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1*2*2*2*2)�_=16�_�@�v32�_", Cr);
			DrawString(50, 280, "7.Z�V���b�g�Ő̋@�̂�|��:(��{�_1)�_=1�_�@�v33�_", Cr);
			DrawString(50, 300, "8.Z�V���b�g�ŐԂ̋@�̂�|��:(��{�_1)�_=1�_�@�v34�_", Cr);
			DrawString(50, 325, "-��-  �R���{:�����V���b�g�ŁA����A���œ����F�̋@�̂�|������", Cr);
			DrawString(50, 355, "<�{�X�X�e�[�W>", Cr);
			DrawString(50, 375, "1��U����^����x��3�_,�|����EASY:100,NORMAL:200,HARD:300�_", Cr);
			DrawString(50, 392, "(LAST�X�e�[�W�ł�EASY:1000,NORMAL:2000,HARD:3000�_)", Cr);
			DrawString(50, 410, "�X�e�[�W11�ȊO�͓G�̕��ʂɂ���ăV���b�g�ɐF����.", Cr);
			DrawString(50, 430, "�������ʂ��U������ƃR���{�ɂȂ�.�R���{�����̓��_�����Z�����.", Cr);
			DrawString(100, 450, "*Z�L�[�܂���ENTER�L�[�Ŏ��̃y�[�W��.", Cr);
		}
		else if (page == 2) {
			DrawString(200, 20, "���_�ɂ���", Cr);
			DrawString(200, 40, "*2Player Mode", Cr);
			DrawString(100, 60, "<�m�[�}���X�e�[�W>", Cr);
			DrawString(50, 80, "��{,��̓|�����Ƃ�1�_.�������A�|�����Ƃ���\n�V���b�g�̃R���{���ɂ���Ĉȉ��̂悤�ɕω�����.", Cr);
			DrawString(50, 120, "�E1�R���{�ɂ�,�|�����Ƃ��̓��_��3�{�ɂȂ�.", Cr);
			DrawString(50, 135, "�E�R���{���Ɠ��������{�[�i�X�_������", Cr);
			DrawString(50, 160, "<�{�X�X�e�[�W>", Cr);
			DrawString(50, 180, "1��U����^����x��3�_,�|����1000�_", Cr);
			DrawString(50, 200, "�{�X�̏o��������G�͈�̓|�����Ƃ�5�_(�R���{���͑�����,�V���b�g�̐F�����̂܂�)", Cr);

			DrawString(50, 300, ":��:2Player Mode�ł�,�e�v���C���[��HP���Ȃ�����,\n�G�̒e�ɓ�����Ɠ��_��10������", Cr);

			DrawString(100, 400, "*Z�L�[�܂���ENTER�L�[�Ŏ��̃y�[�W��.", Cr);
		}
		else if (page == 3) {
			DrawString(200, 20, "�A�C�e���ɂ���", Cr);
			DrawString(50, 60, "�A�C�e����1Player Mode�ł�������ł��Ȃ�.", Cr);
			DrawString(50, 75, "���g�̎g�p�\�A�C�e������HP�̉���ITEM�ɕ\��.", Cr);
			DrawString(50, 90, "�A�C�e����������,�Q�[���J�n����1����,�����ꂩ�̃V���b�g��(5�̔{��)�R���{��", Cr);
			DrawString(50, 105, "�Ȃ邽�т�1������.�܂�,�{�X��|���Ă�1������.", Cr);
			DrawString(50, 120, "SPACE�L�[��������,�A�C�e�����j���[���J��.", Cr);
			DrawString(50, 135, "�����ł�,�ȉ��̂R�̃A�C�e����I��Ŏg�����Ƃ��ł���.", Cr);
			DrawString(50, 150, "(�g�p����ƃA�C�e�����������J�b�R���̕���������.)", Cr);
			DrawString(50, 180, "1:�F�ւ�(ITEM1����)", Cr);
			DrawString(120, 200, "���̃A�C�e�����g���ƁAZ,X,C�S�ẴV���b�g�̐F��", Cr);
			DrawString(120, 215, "�C�ӂ̐F�ɕς��邱�Ƃ��ł���B", Cr);
			DrawString(120, 230, "���̐F��I�����āA�ς��Ȃ����Ƃ��\.", Cr);
			DrawString(120, 245, "�R���{���ɕω��͂Ȃ����߁A�Ⴆ�ΐԂ�5�R���{����Z�V���b�g", Cr);
			DrawString(120, 260, "��ɕς�,��|����6�R���{�ɂȂ�.", Cr);
			DrawString(50, 290, "2:�X�g�b�v(ITEM2����)", Cr);
			DrawString(120, 310, "���̃A�C�e�����g���ƁA���ݑ��ݒ��̓G�̒e�����ׂď���,", Cr);
			DrawString(120, 325, "�����5�b���x(�{�X��3�b���x)�������~�߂邱�Ƃ��ł���.", Cr);
			DrawString(50, 355, "3:HP��(ITEM2����)", Cr);
			DrawString(120, 375, "���̃A�C�e�����g���ƁA������HP��10�񕜂�,��햳�G�ɂȂ�.", Cr);
			DrawString(120, 390, "HP�̍ő�l��30�Ȃ̂�,30�܂ł����񕜂��Ȃ��̂Œ���.", Cr);
			DrawString(120, 405, "�Ȃ�,����HP��30�̏ꍇ,�g�p�ł��Ȃ�(�D�F�ɂȂ��Ă���).", Cr);

			DrawString(100, 430, "*Z�L�[�܂���ENTER�L�[�Ŗ߂�.", Cr);
		}

		ScreenFlip();
	} while (1);

	SetFontSize(16);
	SetFontThickness(6);

	while (KeyCheck == TRUE) {//�L�[��������Ȃ��Ȃ�܂ő҂�
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			KeyCheck = FALSE;
		}
	}

}//Contents3_Operation