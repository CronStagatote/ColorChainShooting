#include "DxLib.h"
#include "Color_Chain_Shooting.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{//main���̊J�n
	int ErrorCheck = 0;//�G���[�`�F�b�N�p�ϐ��@���ׂĂ̊֐��ň����Ƃ��Ă��������B
	/*0:����
	1�ȏ�:�����ɋ����I������K�v�̂���G���[
	-1�ȉ�:�Q�[���i�s����Ȃ��G���[*/

	int gamemode = 0;
	int gameflag = 0;

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
		return -1;    // �G���[���N�����璼���ɏI��

	// �^�C�g����ύX
	SetMainWindowText("Color Chain Shooting");
	SetBackgroundColor(0, 0, 0);

	// �E�C���h�E���[�h�ɕύX
	//ChangeWindowMode(TRUE);

	do {
		// �`�悷�镶����̑�����ݒ�
		SetFontThickness(6);
		SetFontSize(16);

		gameflag = Title(&ErrorCheck, &gamemode);//�^�C�g�����
		if (ErrorCheck > 0) {
			goto ErrorEnd;//error�Ȃ狭���I��
		}

		if (gameflag == 1) {//1Player mode
			if (gamemode == 0) {
				Tutoreal(&ErrorCheck);
			}
			else {
				Player1mode(&ErrorCheck, gamemode);
			}		
		}
		else if (gameflag == 2) {//2Player mode
			Player2mode(&ErrorCheck);
		}
		else if (gameflag == 3) {//Contents
			Contents(&ErrorCheck);
		}

		if (ErrorCheck > 0) {
			goto ErrorEnd;//error�Ȃ狭���I��
		}
		else if (ErrorCheck < 0) {//�^�C�g���ɖ߂�G���[
			ErrorCheck = 0;
		}

	} while (gameflag != 0 && ErrorCheck == 0);//�Q�[���I�����I������ĂȂ��A�G���[�łȂ�

    ErrorEnd://error�Ȃ炱���ɋ����I�ɔ��
	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;

}
