#include "DxLib.h"
#include "Color_Chain_Shooting.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{//main文の開始
	int ErrorCheck = 0;//エラーチェック用変数　すべての関数で引数としてください。
	/*0:正常
	1以上:すぐに強制終了する必要のあるエラー
	-1以下:ゲーム進行上問題ないエラー*/

	int gamemode = 0;
	int gameflag = 0;

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
		return -1;    // エラーが起きたら直ちに終了

	// タイトルを変更
	SetMainWindowText("Color Chain Shooting");
	SetBackgroundColor(0, 0, 0);

	// ウインドウモードに変更
	//ChangeWindowMode(TRUE);

	do {
		// 描画する文字列の太さを設定
		SetFontThickness(6);
		SetFontSize(16);

		gameflag = Title(&ErrorCheck, &gamemode);//タイトル画面
		if (ErrorCheck > 0) {
			goto ErrorEnd;//errorなら強制終了
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
			goto ErrorEnd;//errorなら強制終了
		}
		else if (ErrorCheck < 0) {//タイトルに戻るエラー
			ErrorCheck = 0;
		}

	} while (gameflag != 0 && ErrorCheck == 0);//ゲーム終了が選択されてなく、エラーでない

    ErrorEnd://errorならここに強制的に飛ぶ
	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;

}
