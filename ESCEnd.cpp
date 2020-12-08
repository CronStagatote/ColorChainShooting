#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/*強制終了用関数*/

int ESCGameEnd(int *ErrorCheck) {
	/*ESCキーが呼び出された時に実行され、ErrorCode:999として強制終了*/
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetBackgroundColor(0, 0, 0);
	int Endcount = 6000;
	int Cr = GetColor(220, 220, 0);
	int Cr2 = GetColor(0, 220, 0);
	int FontHandle = CreateFontToHandle(NULL, 30, 3);
	int endflag = 0;//1で強制終了
	bool GameFlag = FALSE;
	if (*ErrorCheck == -999) {
		GameFlag = TRUE;
		*ErrorCheck = 0;//特に異常ではない
	}

	while (Endcount > 0) {
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return 1;        // エラーが起きたらループを抜ける
		}
		if (*ErrorCheck > 0) {
			return -1;//errorなら強制終了
		}

		Endcount--;
		ClearDrawScreen(); // 画面を消す
		DrawStringToHandle(120, 150, "ゲームを強制終了しますか？", Cr, FontHandle);
		DrawStringToHandle(100, 220, "はい:y", Cr, FontHandle);
		DrawStringToHandle(300, 220, "いいえ:n", Cr, FontHandle);
		if (endflag == 1)DrawBox(80, 200, 200, 280, Cr2, FALSE);    // 四角形を描画
		else if (endflag == 0)DrawBox(280, 200, 450, 280, Cr2, FALSE);    // 四角形を描画
		DrawFormatString(80, 320, Cr, "十字キーで選択するか,yもしくはnで選択してzもしくはENTERで決定");
		DrawFormatString(80, 340, Cr, "*この画面でSPACEとSHIFTを同時に押すと,\n タイトルに強制的に戻ります.");
		if (GameFlag == TRUE) {
			DrawFormatString(80, 380, Cr, "*この画面からゲーム終了,またはタイトルに戻ると,\n今回の記録は保存されません.");
			DrawFormatString(200, 430, Cr, "強制終了:%d", Endcount / 60);
		}
		else {
			DrawFormatString(200, 410, Cr, "強制終了:%d", Endcount / 60);
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
	ClearDrawScreen(); // 画面を消す

	return endflag;
}

/*呼び方
if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
ESCGameEnd(ErrorCheck);//強制終了
}
*/
