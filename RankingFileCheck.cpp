#pragma warning(disable:4996)
#include <stdio.h>
#include "DxLib.h"
#include "Color_Chain_Shooting.h"
#define GETPOINT_RANK_NUM 10

struct FileReadData {
	int readrank;//1�`10
	unsigned int readpoint;//���_
	int readdifficult;//��Փx
	int readstage;//�X�e�[�W
	void ErrorSet(int i);
};

void FileReadData::ErrorSet(int i) {
	/*i��readrank-1*/
	if (i > 10)i = 0;
	readrank = i + 1;
	readpoint = 1000 - i * 100;
	readdifficult = 0;
	readstage = 0;
}

int RankCheck(struct FileReadData ReadDataPut[], unsigned int getpoint, int stage, int difficult) {
	int i, j;

	for (i = 0; i < GETPOINT_RANK_NUM; i++) {
		if (getpoint > ReadDataPut[i].readpoint) {//�l���|�C���g���O�̃|�C���g�����������
			for (j = GETPOINT_RANK_NUM; j > i; j--) {//����ւ�
				ReadDataPut[j] = ReadDataPut[j - 1];
			}
			/*���*/
			ReadDataPut[i].readpoint = getpoint;//�l���|�C���g
			ReadDataPut[i].readstage = stage;//���B�X�e�[�W
			ReadDataPut[i].readdifficult = difficult;//��Փx
			for (j = 0; j < 10; j++) {
				ReadDataPut[j].readrank = j + 1;//�����N�𒼂�
			}
			return i + 1;
		}
	}

	return 99;
}

int ReadFile(int *errorcheck,int readflag,struct FileReadData ReadDataPut[]) {
	/*readflag�̊T�v
	10:�ǂݎ��
	20:��������
	0:ALL
	1:EASY
	2:NORMAL
	3:HARD
	4:UNKNOWN
	readflag�̊T�v�����܂�*/

	FILE *filepointer = 0;
	int Cr = GetColor(150, 150, 150);// �D�F�̒l���擾

	///*�t�@�C���ǂݎ��Ə�������*///
	switch (readflag) {
	case 10:
		filepointer = fopen("../exe/package/1PlayerModeApoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeApoints.dat", "rb");//�ēǂݍ���
			/*if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}*/
		}
		break;
	case 11:
		filepointer = fopen("../exe/package/1PlayerModeEpoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeEpoints.dat", "rb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 12:
		filepointer = fopen("../exe/package/1PlayerModeNpoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeNpoints.dat", "rb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 13:
		filepointer = fopen("../exe/package/1PlayerModeHpoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeHpoints.dat", "rb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 14:
		filepointer = fopen("../exe/package/1PlayerModeUpoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeUpoints.dat", "rb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 20:
		filepointer = fopen("../exe/package/1PlayerModeApoints.dat", "wb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeApoints.dat", "wb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 21:
		filepointer = fopen("../exe/package/1PlayerModeEpoints.dat", "wb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeEpoints.dat", "wb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 22:
		filepointer = fopen("../exe/package/1PlayerModeNpoints.dat", "wb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeNpoints.dat", "wb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 23:
		filepointer = fopen("../exe/package/1PlayerModeHpoints.dat", "wb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeHpoints.dat", "wb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	case 24:
		filepointer = fopen("../exe/package/1PlayerModeUpoints.dat", "wb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeUpoints.dat", "wb");//�ēǂݍ���
			if (filepointer == NULL) {
				DrawFormatString(100, 100, Cr, "File open error!\n");
				*errorcheck = 9;
				return -1;
			}
		}
		break;
	default:
		break;
	}
	/*�ǂݎ��*/
	if (readflag / 10 == 1) {
		for (int i = 0; i < GETPOINT_RANK_NUM; i++) {
			fscanf(filepointer, "%d,%u,%d,%d", &ReadDataPut[i].readrank, &ReadDataPut[i].readpoint, &ReadDataPut[i].readstage, &ReadDataPut[i].readdifficult);
		}
	}

	/*��������*/
	if (readflag / 10 == 2) {
		for (int i = 0; i < GETPOINT_RANK_NUM; i++) {
			fprintf(filepointer, "%d,%u,%d,%d\n", ReadDataPut[i].readrank, ReadDataPut[i].readpoint, ReadDataPut[i].readstage, ReadDataPut[i].readdifficult);
		}
	}

	fclose(filepointer);
	/*�t�@�C���ǂݎ��Ə������݂����܂�*/

	return 0;
}

void FALSEErrorCheck(struct FileReadData ReadDataPut[]) {
	bool RightCheck = TRUE;
	int i = 0;

	for (i = 0; i < GETPOINT_RANK_NUM; i++) {
		if (ReadDataPut[i].readrank != i + 1) {//�����N��1�`10�����Ԃɕ���
			RightCheck = FALSE;
		}
	}
	if (RightCheck == FALSE) {
		for (i = 0; i < GETPOINT_RANK_NUM; i++) {
			ReadDataPut[i].ErrorSet(i);
		}//���Z�b�g
		RightCheck = TRUE;
	}

}

int ColorAssign(int ReadDifficult) {
	switch (ReadDifficult) {
	case 1:
		return 3;//��
	case 2:
		return 2;//��
	case 3:
		return 1;//��
	case 4:
		return 4;//���F
	default:
		return 5;//��
	}//�F�w��
	return 5;//��
}

void PointPrint(struct FileReadData ReadDataPut[],int Cr[],int rank,int point,int count) {
	int i = 0;
	/*rank=100�ȍ~�œǂݎ��̂�*/
	if (rank < 100) {
		DrawFormatString(100, 50, Cr[1], "Ranking");
		/*�P�`�R��*/
		if (rank == 1) {
			if (count % 20 < 10)DrawFormatString(100, 100, Cr[4], "1st:%upoints", ReadDataPut[0].readpoint);
		}
		else {
			DrawFormatString(100, 100, Cr[2], "1st:%upoints", ReadDataPut[0].readpoint);
		}
		if (rank == 2) {
			if (count % 20 < 10)DrawFormatString(100, 125, Cr[4], "2nd:%upoints", ReadDataPut[1].readpoint);
		}
		else {
			DrawFormatString(100, 125, Cr[3], "2nd:%upoints", ReadDataPut[1].readpoint);
		}
		if (rank == 3) {
			if (count % 20 < 10)DrawFormatString(100, 150, Cr[4], "3rd:%upoints", ReadDataPut[2].readpoint);
		}
		else {
			DrawFormatString(100, 150, Cr[3], "3rd:%upoints", ReadDataPut[2].readpoint);
		}
		/*4�ʈȍ~*/
		for (i = 3; i < GETPOINT_RANK_NUM; i++) {
			if (rank == i + 1) {
				if (count % 20 < 10)DrawFormatString(100, 100 + i * 25, Cr[4], "%dth:%upoints", i + 1, ReadDataPut[i].readpoint);
			}
			else {
				DrawFormatString(100, 100 + i * 25, Cr[0], "%dth:%upoints", i + 1, ReadDataPut[i].readpoint);
			}
		}
		/*�����N�O*/
		if (rank == 99)DrawFormatString(300, 100, Cr[4], "Now Get Points:%upoints", point);
	}
	else {
		/*�����L���O�\��*/
		switch (rank) {
		case 100:
			DrawFormatString(200, 40, Cr[5], "1Player Mode Ranking:ALL");
			break;
		case 101:
			DrawFormatString(200, 40, Cr[3], "1Player Mode Ranking:EASY");
			break;
		case 102:
			DrawFormatString(200, 40, Cr[2], "1Player Mode Ranking:NORMAL");
			break;
		case 103:
			DrawFormatString(200, 40, Cr[1], "1Player Mode Ranking:HARD");
			break;
		case 104:
			DrawFormatString(200, 40, Cr[4], "1Player Mode Ranking:UNKNOWN");
			break;
		default:
			break;
		}

		if (rank == 100) {
			if (ReadDataPut[0].readstage < 12) {
				DrawFormatString(250, 100, Cr[ColorAssign(ReadDataPut[0].readdifficult)], "1st:%upoints:stage%d", ReadDataPut[0].readpoint, ReadDataPut[0].readstage);
			}
			else if (ReadDataPut[0].readstage == 12) {
				DrawFormatString(250, 100, Cr[ColorAssign(ReadDataPut[0].readdifficult)], "1st:%upoints:Clear", ReadDataPut[0].readpoint);
			}
			if (ReadDataPut[1].readstage < 12) {
				DrawFormatString(250, 125, Cr[ColorAssign(ReadDataPut[1].readdifficult)], "2nd:%upoints:stage%d", ReadDataPut[1].readpoint, ReadDataPut[1].readstage);
			}
			else if (ReadDataPut[1].readstage == 12) {
				DrawFormatString(250, 125, Cr[ColorAssign(ReadDataPut[1].readdifficult)], "2nd:%upoints:Clear", ReadDataPut[1].readpoint);
			}
			if (ReadDataPut[2].readstage < 12) {
				DrawFormatString(250, 150, Cr[ColorAssign(ReadDataPut[2].readdifficult)], "3rd:%upoints:stage%d", ReadDataPut[2].readpoint, ReadDataPut[2].readstage);
			}
			else if (ReadDataPut[2].readstage == 12) {
				DrawFormatString(250, 150, Cr[ColorAssign(ReadDataPut[2].readdifficult)], "3rd:%upoints:Clear", ReadDataPut[2].readpoint);
			}
			for (i = 3; i < GETPOINT_RANK_NUM; i++) {
				if (ReadDataPut[i].readstage < 12) {
					DrawFormatString(250, 100 + i * 25, Cr[ColorAssign(ReadDataPut[i].readdifficult)], "%dth:%upoints:stage%d", i + 1, ReadDataPut[i].readpoint, ReadDataPut[i].readstage);
				}
				else if (ReadDataPut[i].readstage == 12) {
					DrawFormatString(250, 100 + i * 25, Cr[ColorAssign(ReadDataPut[i].readdifficult)], "%dth:%upoints:Clear", i + 1, ReadDataPut[i].readpoint);
				}
			}
			DrawFormatString(150, 360, Cr[3], "Easy");
			DrawFormatString(250, 360, Cr[2], "Normal");
			DrawFormatString(350, 360, Cr[1], "Hard");
			for (i = 0; i < GETPOINT_RANK_NUM; i++) {
				if (ReadDataPut[2].readdifficult == 4) {
					DrawFormatString(450, 360, Cr[4], "UNKNOWN");
				}
			}
		}
		else if (rank > 100 && rank < 105) {
			if (ReadDataPut[0].readstage < 12) {
				DrawFormatString(250, 100, Cr[2], "1st:%upoints:stage%d", ReadDataPut[0].readpoint, ReadDataPut[0].readstage);
			}
			else if (ReadDataPut[0].readstage == 12) {
				DrawFormatString(250, 100, Cr[2], "1st:%upoints:Clear", ReadDataPut[0].readpoint);
			}
			if (ReadDataPut[1].readstage < 12) {
				DrawFormatString(250, 125, Cr[3], "2nd:%upoints:stage%d", ReadDataPut[1].readpoint, ReadDataPut[1].readstage);
			}
			else if (ReadDataPut[1].readstage == 12) {
				DrawFormatString(250, 125, Cr[3], "2nd:%upoints:Clear", ReadDataPut[1].readpoint);
			}
			if (ReadDataPut[2].readstage < 12) {
				DrawFormatString(250, 150, Cr[3], "3rd:%upoints:stage%d", ReadDataPut[2].readpoint, ReadDataPut[2].readstage);
			}
			else if (ReadDataPut[2].readstage == 12) {
				DrawFormatString(250, 150, Cr[3], "3rd:%upoints:Clear", ReadDataPut[2].readpoint);
			}
			for (i = 3; i < GETPOINT_RANK_NUM; i++) {
				if (ReadDataPut[i].readstage < 12) {
					DrawFormatString(250, 100 + i * 25, Cr[0], "%dth:%upoints:stage%d", i + 1, ReadDataPut[i].readpoint,ReadDataPut[i].readstage);
				}
				else if (ReadDataPut[i].readstage == 12) {
					DrawFormatString(250, 100 + i * 25, Cr[0], "%dth:%upoints:Clear", i + 1, ReadDataPut[i].readpoint);
				}
			}
		}
	}
}

int RankingFileCheck(int *ErrorCheck, unsigned int point, int callflag, int stage) {
	/*�G���[�`�F�b�N,�l���|�C���g,�Ăяo�����(100�`104:��Փx�ʌĂяo���̂�,1�`4:��Փx�ɂ�菑�����݂���)*/
	int rank = 0, count = 0;//�����N,�_�ŏ����p
	unsigned int stagepoint;//���_�ǂݍ���
	struct FileReadData ReadDataPutALL[GETPOINT_RANK_NUM + 1];//�ǂݍ��ݗp(�S��)
	struct FileReadData ReadDataPutDif[GETPOINT_RANK_NUM + 1];//�ǂݍ��ݗp(��Փx��)
	int i;

	/*�����̐F*/
	int Cr[7];
	Cr[0] = GetColor(150, 150, 150);// �D�F�̒l���擾
	Cr[1] = GetColor(200, 0, 0);// �ԐF�̒l���擾
	Cr[2] = GetColor(200, 200, 0);// ���F�̒l���擾
	Cr[3] = GetColor(0, 200, 0);// �ΐF�̒l���擾
	Cr[4] = GetColor(0, 200, 200);// ���F�̒l���擾
	Cr[5] = GetColor(240, 240, 240);// ���F�̒l���擾
	Cr[6] = GetColor(200, 0, 200);// ���F�̒l���擾

	/*�Ăяo���Ȃ��Ȃ�߂�*/
	if (callflag == 999) {//�Ăяo���Ȃ�
		return 0;
	}

	///*�t�@�C���ǂݍ���*///
	ReadFile(ErrorCheck, 10, ReadDataPutALL);//ALL�͂ǂ���ɂ���Ăяo��
	switch (callflag){
	case 1:
	case 101:
		ReadFile(ErrorCheck, 11, ReadDataPutDif);//EASY�Ăяo��
		break;
	case 2:
	case 102:
		ReadFile(ErrorCheck, 12, ReadDataPutDif);//NORMAL�Ăяo��
		break;
	case 3:
	case 103:
		ReadFile(ErrorCheck, 13, ReadDataPutDif);//HARD�Ăяo��
		break;
	case 4:
	case 104:
		ReadFile(ErrorCheck, 14, ReadDataPutDif);//UNKNOWN�Ăяo��
		break;
	}
	/*�t�@�C���ǂݍ��݂����܂�*/

	bool Key = TRUE;
	/*result��ʕ\��*/
	if (callflag <= 4) {//�����L���O�\�������ʕ\��

		//�������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
		int SHandle = LoadSoundMem("../exe/package/bgm/rank.mp3");
		if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/rank.mp3");//�ēǂݍ���

		RankCheck(ReadDataPutALL, point, stage, callflag);//���ʓ���ւ�
		rank = RankCheck(ReadDataPutDif, point, stage, callflag);//���ʓ���ւ�
		while (1) {

			if (CheckSoundMem(SHandle) == 0) {
				PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//���y
			}

			ClearDrawScreen(); // ��ʂ�����

			/*�r�������I������*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				ESCGameEnd(ErrorCheck);//�����I��
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

			/*�I��*/
			if (CheckHitKeyAll() == 0)Key = FALSE;//�L�[����P���𗣂�����

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
				Key = TRUE;
				break;
			}

			///*�\��*///
			PointPrint(ReadDataPutDif, Cr, rank, point, count);//���ʂƃ|�C���g�\��
			DrawFormatString(350, 400, Cr[0], "Thank you for playing!\nPlease SPACE or ENTER key...");

			ScreenFlip();
			count++;
			if (count > 30000)count = 0;
		}

		/*�s�������Z�b�g*/
		FALSEErrorCheck(ReadDataPutALL);
		FALSEErrorCheck(ReadDataPutDif);

		while (Key == TRUE) {
			if (CheckHitKeyAll() == 0)Key = FALSE;//�L�[����P���𗣂�����

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				return -1;//error�Ȃ狭���I��
			}

			if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
				*ErrorCheck = 1;
				return -1;        // �G���[���N�����烋�[�v�𔲂���
			}
		}//�L�[�������ꖳ���Ȃ�܂ő҂�

		///*�t�@�C����������*///
		ReadFile(ErrorCheck, 20, ReadDataPutALL);//ALL�͂ǂ���ɂ��揑������
		switch (callflag) {
		case 1:
			ReadFile(ErrorCheck, 21, ReadDataPutDif);//EASY��������
			break;
		case 2:
			ReadFile(ErrorCheck, 22, ReadDataPutDif);//NORMAL��������
			break;
		case 3:
			ReadFile(ErrorCheck, 23, ReadDataPutDif);//HARD��������
			break;
		case 4:
			ReadFile(ErrorCheck, 24, ReadDataPutDif);//UNKNOWN��������
			break;
		}
		/*�t�@�C���������݂����܂�*/

		// �T�E���h�n���h���̍폜
		DeleteSoundMem(SHandle);

		return rank;
	}
	else if (callflag >= 100 && callflag <= 104) {//�Ăяo���̂�
		ClearDrawScreen(); // ��ʂ�����
		/*�����L���O�\��*/
		if (callflag == 100) {
			PointPrint(ReadDataPutALL, Cr, callflag, 0, count);//ALL�\��
		}
		else if (callflag > 100 && callflag < 105) {
			PointPrint(ReadDataPutDif, Cr, callflag, 0, count);//��Փx�ʕ\��
		}

		ScreenFlip();
		WaitTimer(500);// ������0.5�b�܂�

		while (1) {
			ClearDrawScreen(); // ��ʂ�����

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

			/*�I��*/
			if (CheckHitKeyAll() == 0)Key = FALSE;//�L�[����P���𗣂�����

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
				break;
			}

			/*���ꏈ���i�f�o�b�O�p�j*/
			if (CheckHitKey(KEY_INPUT_F) == 1 && CheckHitKey(KEY_INPUT_A) == 1 && CheckHitKey(KEY_INPUT_L) == 1 && CheckHitKey(KEY_INPUT_S) == 1 && CheckHitKey(KEY_INPUT_E) == 1 && Key == FALSE) {
				int FontHandle = CreateFontToHandle(NULL, 30, 3);
				int endflag = 0;
				while (1) {
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

					ClearDrawScreen(); // ��ʂ�����
					DrawStringToHandle(120, 150, "���f�[�^�����������܂����H", Cr[2], FontHandle);
					DrawStringToHandle(100, 220, "�͂�:y", Cr[2], FontHandle);
					DrawStringToHandle(300, 220, "������:n", Cr[2], FontHandle);
					if (endflag == 1)DrawBox(80, 200, 200, 280, Cr[4], FALSE);    // �l�p�`��`��
					else if (endflag == 0)DrawBox(280, 200, 450, 280, Cr[4], FALSE);    // �l�p�`��`��
					DrawFormatString(100, 330, Cr[1], "�\���L�[�őI�����邩�Ay��������n�őI������z��������ENTER�Ō���");
					ScreenFlip();

					if (endflag == 1) {
						if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
							for (i = 0; i < GETPOINT_RANK_NUM; i++) {
								if (callflag == 100) {
									ReadDataPutALL[i].ErrorSet(i);
								}
								else {
									ReadDataPutDif[i].ErrorSet(i);
								}		
							}//���Z�b�g
							break;
						}
						else if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_N) == 1) {
							endflag = 0;
						}
					}
					else {
						if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
							break;
						}
						else if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_Y) == 1) {
							endflag = 1;
						}
					}

				}
				ClearDrawScreen(); // ��ʂ�����
				Key = TRUE;
			}
			/*�f�o�b�O�R�}���h�����܂�*/

			///*��ʕ\��*///
			if (callflag == 100) {
				PointPrint(ReadDataPutALL, Cr, callflag, 0, count);//ALL�\��
			}
			else if (callflag > 100 && callflag < 105) {
				PointPrint(ReadDataPutDif, Cr, callflag, 0, count);//��Փx�ʕ\��
			}
			DrawFormatString(350, 400, Cr[0], "Please SPACE or ENTER key.");

			ScreenFlip();
		}

		/*�s�������Z�b�g*/
		FALSEErrorCheck(ReadDataPutALL);
		FALSEErrorCheck(ReadDataPutDif);


		///*�t�@�C����������*///
		ReadFile(ErrorCheck, 20, ReadDataPutALL);//ALL�͂ǂ���ɂ��揑������
		switch (callflag) {
		case 101:
			ReadFile(ErrorCheck, 21, ReadDataPutDif);//EASY��������
			break;
		case 102:
			ReadFile(ErrorCheck, 22, ReadDataPutDif);//NORMAL��������
			break;
		case 103:
			ReadFile(ErrorCheck, 23, ReadDataPutDif);//HARD��������
			break;
		case 104:
			ReadFile(ErrorCheck, 24, ReadDataPutDif);//UNKNOWN��������
			break;
		}
		/*�t�@�C���������݂����܂�*/
	}

	return 0;
}
