#include "DxLib.h"
#include"Color_Chain_Shooting.h"


int Title(int *ErrorCheck, int *gamemode) {//�^�C�g�����
	//�Q�[���X�^�[�g���̉�ʗp
	int checktmp = -1;
	int gameflag = 0, command = 0, commandtime = 0;
	bool Key;
	int Handle[12], G;
	int veryhardcount = 0;
	int FontHandle = CreateFontToHandle(NULL, 15, 3);
	int FontHandle2 = CreateFontToHandle(NULL, 30, 5);
	int titlewaittime = 0;

	// �F�̒l���擾
	int Cr = GetColor(240, 240, 240);
	int CrG = GetColor(0, 240, 0);//��
	int CrY = GetColor(240, 240, 0);//��
	int CrR = GetColor(240, 0, 0);//��
	int CrP = GetColor(150, 30, 240);//��
	int CrB = GetColor(0, 0, 0);//��

	// PNG�摜�̃������ւ̕����ǂݍ���
	checktmp = LoadDivGraph("../exe/package/paint/Select.png", 12, 4, 3, 32, 32, Handle);
	if (checktmp == -1)LoadDivGraph("./package/paint/Select.png", 12, 4, 3, 32, 32, Handle);//�ēǂݍ���
	G = LoadGraph("../exe/package/paint/Title.png");
	if (G == -1)G = LoadGraph("./package/paint/Title.png");//�ēǂݍ���

	//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
	int SHandle = LoadSoundMem("../exe/package/bgm/title.mp3");
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/title.mp3");//�ēǂݍ���
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
	int SE = LoadSoundMem("../exe/package/bgm/select.mp3");
	if (SE == -1)SE = LoadSoundMem("./package/bgm/select.mp3");//�ēǂݍ���
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	Key = true;//�{�^����������Ă��邱�Ƃɂ��Ă���
	while (gameflag != 1) {
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			Key = true;
			ESCGameEnd(ErrorCheck);//�����I��
			if (command == 4) {
				SetBackgroundColor(240, 240, 240);
			}
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

		if (gameflag != 10) {
			DrawGraph(0, 0, G, true);//�^�C�g�����

			DrawString(280, 270, "1Player mode:1", Cr);
			DrawString(280, 300, "2Player mode:2", Cr);
			DrawString(280, 330, "contents:3", Cr);
			DrawString(280, 360, "�Q�[���I��:4", Cr);
			DrawStringToHandle(100, 420, "�㉺�L�[�������͐����L�[(1�`4)�őI���AENTER��������z�L�[�Ō���", Cr, FontHandle);


			if (command == 0) {
				DrawGraph(240, 260, Handle[5], true);
			}
			else if (command == 1) {
				DrawGraph(240, 290, Handle[5], true);
			}
			else if (command == 2) {
				DrawGraph(240, 320, Handle[5], true);
			}
			else if (command == 3) {
				DrawGraph(240, 350, Handle[5], true);
			}

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_1) == 1)command = 0;
			if (CheckHitKey(KEY_INPUT_2) == 1)command = 1;
			if (CheckHitKey(KEY_INPUT_3) == 1)command = 2;
			if (CheckHitKey(KEY_INPUT_4) == 1)command = 3;

			if ((CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && Key == FALSE) {
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				if (command == 0) {
					gameflag = 10;
					command = 1;
				}
				else if (command == 1) {
					gameflag = 2;
				}
				else if (command == 2) {
					gameflag = 3;
				}
				else if (command == 3) {//�Q�[���I��
					gameflag = 0;
					// �쐬�����t�H���g�f�[�^���폜����
					DeleteFontToHandle(FontHandle);
					// �T�E���h�n���h���̍폜
					DeleteSoundMem(SHandle);
					return gameflag;//1:1Player 2:2Player 3:Contents 0:end
				}
				Key = true;
				if (gameflag != 10)break;//Z�L�[�������ꂽ�烋�[�v�𔲂���
			}
			else if (CheckHitKey(KEY_INPUT_UP) == 1 && Key == FALSE) {
				if (command <= 0) {
					command = 0;
				}
				else {
					command--;
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
				Key = true;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Key == FALSE) {
				if (command >= 3) {
					command = 3;	
				}
				else {
					command++;
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
				Key = true;
			}

			/*���Ԍo�߂ƃf�����*/
			titlewaittime++;
			if (titlewaittime > 3600) {
				StopSoundMem(SHandle);
				Demonstration(ErrorCheck);
				titlewaittime = 0;
				Key = true;
			}
		}
		else {//gameflag=10:�Q�[�����[�h�I��
			if (command == 0) {
				DrawStringToHandle(250, 80, "��Փx�I��", CrG, FontHandle2);
			}
			else if (command == 1) {
				DrawStringToHandle(250, 80, "��Փx�I��", CrY, FontHandle2);
			}
			else if (command == 2) {
				DrawStringToHandle(250, 80, "��Փx�I��", CrR, FontHandle2);
			}
			else if (command == 4) {
				DrawStringToHandle(250, 80, "��Փx�I��", CrB, FontHandle2);
			}
			else {
				DrawStringToHandle(250, 80, "��Փx�I��", Cr, FontHandle2);
			}
			DrawString(280, 150, "Tutoreal:0", Cr);
			DrawString(280, 180, "EASY:1", Cr);
			DrawString(280, 210, "NORMAL:2", Cr);
			DrawString(280, 240, "HARD:3", Cr);
			DrawString(280, 270, "�߂�:4", Cr);
			DrawStringToHandle(100, 420, "�㉺�L�[�������͐����L�[(1�`4)�őI���AENTER��������z�L�[�Ō���", Cr, FontHandle);

			if (command == -1) {
				DrawGraph(240, 140, Handle[5], true);
				DrawStringToHandle(100, 320, "�`���[�g���A�����[�h�ł�.", Cr, FontHandle);
				DrawStringToHandle(100, 338, "�G�̔z�u�͌Œ��,�X�e�[�W3�܂łƂȂ��Ă��܂�.", Cr, FontHandle);
				DrawStringToHandle(100, 356, "�����p�̃��[�h��,�L�^�͈�ؕۑ�����܂���.", Cr, FontHandle);
			}
			else if (command == 0) {
				DrawGraph(240, 170, Handle[5], true);
				DrawStringToHandle(100, 320, "EASY", CrG, FontHandle);
				DrawStringToHandle(100, 338, "HP�����X�e�[�W�S�񕜂��܂�(HP:30).", CrG, FontHandle);
				DrawStringToHandle(100, 356, "NORMAL�Ɣ��,�G�̍U���Ԋu������,�e��������܂�.", CrG, FontHandle);
				DrawStringToHandle(100, 374, "�����,�{�X��HP��NORMAL�Ɣ�׌������܂��B", CrG, FontHandle);
				DrawStringToHandle(100, 392, "������,�{�[�i�X���_��NORMAL�Ɣ�׌������܂�.", CrG, FontHandle);
			}
			else if (command == 1) {
				DrawGraph(240, 200, Handle[5], true);
				DrawStringToHandle(100, 320, "NORMAL", CrY, FontHandle);
				DrawStringToHandle(100, 338, "HP�����X�e�[�W5�񕜂��܂�(�ő�l:30).", CrY, FontHandle);
				DrawStringToHandle(100, 356, "������Փx�ł�.", CrY, FontHandle);
				DrawStringToHandle(100, 374, "���p�Y�������߂�Ȃ�EASY��,", CrY, FontHandle);
				DrawStringToHandle(100, 392, "���V���[�e�B���O�����߂�Ȃ�HARD��I��ł�������.", CrY, FontHandle);
			}
			else if (command == 2) {
				DrawGraph(240, 230, Handle[5], true);
				DrawStringToHandle(100, 320, "HARD", CrR, FontHandle);
				DrawStringToHandle(100, 338, "HP�͎��X�e�[�W�Ɏ����z���ɂȂ�܂�(�X�e�[�W���̉񕜂Ȃ�).", CrR, FontHandle);
				DrawStringToHandle(100, 356, "Normal�Ɣ��,�G�̍U���Ԋu���Z���Ȃ�܂�.", CrR, FontHandle);
				DrawStringToHandle(100, 374, "�����,�{�X��HP��NORMAL�Ɣ�ב������܂�.", CrR, FontHandle);
				DrawStringToHandle(100, 392, "������,�{�[�i�X���_��NORMAL�Ɣ�ב������܂�.", CrR, FontHandle);
			}
			else if (command == 3) {
				DrawGraph(240, 260, Handle[5], true);
			}
			else if (command == 4) {//�B���R�}���h
				DrawGraph(240, 290, Handle[5], true);
				//DrawBox(90, 330, 500, 410, CrY, true);
				DrawString(280, 300, "UNKNOWN", CrR);
				DrawStringToHandle(100, 338, "��{��HARD�Ɠ���.", CrP, FontHandle);
				DrawStringToHandle(100, 356, "�{�X�̍U������,�m�[�}���G�͑S�ă����_���U��.", CrP, FontHandle);
				DrawStringToHandle(100, 374, "�{�X��HP��HARD��������.", CrP, FontHandle);
				DrawStringToHandle(100, 392, "�{�[�i�X���_��HARD��������.", CrP, FontHandle);
			}

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_0) == 1)command = -1;
			if (CheckHitKey(KEY_INPUT_1) == 1)command = 0;
			if (CheckHitKey(KEY_INPUT_2) == 1)command = 1;
			if (CheckHitKey(KEY_INPUT_3) == 1)command = 2;
			if (CheckHitKey(KEY_INPUT_4) == 1)command = 3;

			if ((CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && Key == FALSE) {

				if (command == 0) {
					gameflag = 1;
					*gamemode = 1;//EASY
				}
				else if (command == 1) {
					gameflag = 1;
					*gamemode = 2;//NORMAL
				}
				else if (command == 2) {
					gameflag = 1;
					*gamemode = 3;//HARD
				}
				else if (command == 3) {
					gameflag = 0;
					command = 0;
					veryhardcount = 0;
				}
				else if (command == 4) {
					gameflag = 1;
					SetBackgroundColor(0, 0, 0);
					*gamemode = 4;//VERY HARD
				}
				else if (command == -1) {
					gameflag = 1;
					*gamemode = 0;
				}

				Key = true;
				if (gameflag != 0)break;//Z�L�[�������ꂽ�烋�[�v�𔲂���
			}
			else if (CheckHitKey(KEY_INPUT_UP) == 1 && Key == FALSE) {
				if (command <= -1) {
					command = -1;
				}
				else {
					command--;
					SetBackgroundColor(0, 0, 0);
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
				Key = true;
			}
			else if (CheckHitKey(KEY_INPUT_DOWN) == 1 && Key == FALSE) {
				if (command == 3) {
					command = 3;
					veryhardcount++;
					if (veryhardcount >= 10) {//�B���R�}���h
						command = 4;
						SetBackgroundColor(240, 240, 240);
						PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
					}
				}
				else if (command >= 4) {
					command = 4;
				}
				else {
					command++;
					PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
				}
				Key = true;
			}
		}

	}

	while (Key == true) {//�L�[�������ꖳ���Ȃ�܂ő҂�
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			// �쐬�����t�H���g�f�[�^���폜����
			DeleteFontToHandle(FontHandle);
			return -9;        // �G���[���N�����烋�[�v�𔲂���
		}

		if (CheckHitKeyAll() == 0) {//�L�[��������Ă��Ȃ�
			Key = FALSE;
		}
	}

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(FontHandle);

	// �T�E���h�n���h���̍폜
	DeleteSoundMem(SHandle);

	command = 0;

	return gameflag;//1:1Player 2:2Player 3:Contents 0:end
}
