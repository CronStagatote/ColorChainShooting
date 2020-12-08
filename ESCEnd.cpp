#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/*�����I���p�֐�*/

int ESCGameEnd(int *ErrorCheck) {
	/*ESC�L�[���Ăяo���ꂽ���Ɏ��s����AErrorCode:999�Ƃ��ċ����I��*/
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetBackgroundColor(0, 0, 0);
	int Endcount = 6000;
	int Cr = GetColor(220, 220, 0);
	int Cr2 = GetColor(0, 220, 0);
	int FontHandle = CreateFontToHandle(NULL, 30, 3);
	int endflag = 0;//1�ŋ����I��
	bool GameFlag = FALSE;
	if (*ErrorCheck == -999) {
		GameFlag = TRUE;
		*ErrorCheck = 0;//���Ɉُ�ł͂Ȃ�
	}

	while (Endcount > 0) {
		if (ProcessMessage() == -1) {// ���b�Z�[�W���[�v�ɑ��鏈��������
			*ErrorCheck = 1;
			return 1;        // �G���[���N�����烋�[�v�𔲂���
		}
		if (*ErrorCheck > 0) {
			return -1;//error�Ȃ狭���I��
		}

		Endcount--;
		ClearDrawScreen(); // ��ʂ�����
		DrawStringToHandle(120, 150, "�Q�[���������I�����܂����H", Cr, FontHandle);
		DrawStringToHandle(100, 220, "�͂�:y", Cr, FontHandle);
		DrawStringToHandle(300, 220, "������:n", Cr, FontHandle);
		if (endflag == 1)DrawBox(80, 200, 200, 280, Cr2, FALSE);    // �l�p�`��`��
		else if (endflag == 0)DrawBox(280, 200, 450, 280, Cr2, FALSE);    // �l�p�`��`��
		DrawFormatString(80, 320, Cr, "�\���L�[�őI�����邩,y��������n�őI������z��������ENTER�Ō���");
		DrawFormatString(80, 340, Cr, "*���̉�ʂ�SPACE��SHIFT�𓯎��ɉ�����,\n �^�C�g���ɋ����I�ɖ߂�܂�.");
		if (GameFlag == TRUE) {
			DrawFormatString(80, 380, Cr, "*���̉�ʂ���Q�[���I��,�܂��̓^�C�g���ɖ߂��,\n����̋L�^�͕ۑ�����܂���.");
			DrawFormatString(200, 430, Cr, "�����I��:%d", Endcount / 60);
		}
		else {
			DrawFormatString(200, 410, Cr, "�����I��:%d", Endcount / 60);
		}
		ScreenFlip();

		if (Endcount <= 0) {
			endflag = 1;
			*ErrorCheck = 999;
			break;
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && (CheckHitKey(KEY_INPUT_LSHIFT) == 1 || CheckHitKey(KEY_INPUT_RSHIFT) == 1)) {
			endflag = 2;
			*ErrorCheck = -1;
			break;
		}

		if (endflag == 0) {
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				break;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_Y) == 1) {
				endflag = 1;
			}
		}
		else {
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				*ErrorCheck = 999;
				break;
			}
			else if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_N) == 1) {
				endflag = 0;
			}
		}

	}
	ClearDrawScreen(); // ��ʂ�����

	return endflag;
}

/*�Ăѕ�
if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
ESCGameEnd(ErrorCheck);//�����I��
}
*/
