#pragma warning(disable:4996)
#include <stdio.h>
#include "DxLib.h"
#include "Color_Chain_Shooting.h"
#define GETPOINT_RANK_NUM 10

struct FileReadData {
	int readrank;//1～10
	unsigned int readpoint;//得点
	int readdifficult;//難易度
	int readstage;//ステージ
	void ErrorSet(int i);
};

void FileReadData::ErrorSet(int i) {
	/*iはreadrank-1*/
	if (i > 10)i = 0;
	readrank = i + 1;
	readpoint = 1000 - i * 100;
	readdifficult = 0;
	readstage = 0;
}

int RankCheck(struct FileReadData ReadDataPut[], unsigned int getpoint, int stage, int difficult) {
	int i, j;

	for (i = 0; i < GETPOINT_RANK_NUM; i++) {
		if (getpoint > ReadDataPut[i].readpoint) {//獲得ポイントが前のポイントよりも高ければ
			for (j = GETPOINT_RANK_NUM; j > i; j--) {//入れ替え
				ReadDataPut[j] = ReadDataPut[j - 1];
			}
			/*代入*/
			ReadDataPut[i].readpoint = getpoint;//獲得ポイント
			ReadDataPut[i].readstage = stage;//到達ステージ
			ReadDataPut[i].readdifficult = difficult;//難易度
			for (j = 0; j < 10; j++) {
				ReadDataPut[j].readrank = j + 1;//ランクを直す
			}
			return i + 1;
		}
	}

	return 99;
}

int ReadFile(int *errorcheck,int readflag,struct FileReadData ReadDataPut[]) {
	/*readflagの概要
	10:読み取り
	20:書き込み
	0:ALL
	1:EASY
	2:NORMAL
	3:HARD
	4:UNKNOWN
	readflagの概要ここまで*/

	FILE *filepointer = 0;
	int Cr = GetColor(150, 150, 150);// 灰色の値を取得

	///*ファイル読み取りと書き込み*///
	switch (readflag) {
	case 10:
		filepointer = fopen("../exe/package/1PlayerModeApoints.dat", "rb");
		if (filepointer == NULL) {
			filepointer = fopen("./package/1PlayerModeApoints.dat", "rb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeEpoints.dat", "rb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeNpoints.dat", "rb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeHpoints.dat", "rb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeUpoints.dat", "rb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeApoints.dat", "wb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeEpoints.dat", "wb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeNpoints.dat", "wb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeHpoints.dat", "wb");//再読み込み
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
			filepointer = fopen("./package/1PlayerModeUpoints.dat", "wb");//再読み込み
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
	/*読み取り*/
	if (readflag / 10 == 1) {
		for (int i = 0; i < GETPOINT_RANK_NUM; i++) {
			fscanf(filepointer, "%d,%u,%d,%d", &ReadDataPut[i].readrank, &ReadDataPut[i].readpoint, &ReadDataPut[i].readstage, &ReadDataPut[i].readdifficult);
		}
	}

	/*書き込み*/
	if (readflag / 10 == 2) {
		for (int i = 0; i < GETPOINT_RANK_NUM; i++) {
			fprintf(filepointer, "%d,%u,%d,%d\n", ReadDataPut[i].readrank, ReadDataPut[i].readpoint, ReadDataPut[i].readstage, ReadDataPut[i].readdifficult);
		}
	}

	fclose(filepointer);
	/*ファイル読み取りと書き込みここまで*/

	return 0;
}

void FALSEErrorCheck(struct FileReadData ReadDataPut[]) {
	bool RightCheck = TRUE;
	int i = 0;

	for (i = 0; i < GETPOINT_RANK_NUM; i++) {
		if (ReadDataPut[i].readrank != i + 1) {//ランクは1～10が順番に並ぶ
			RightCheck = FALSE;
		}
	}
	if (RightCheck == FALSE) {
		for (i = 0; i < GETPOINT_RANK_NUM; i++) {
			ReadDataPut[i].ErrorSet(i);
		}//リセット
		RightCheck = TRUE;
	}

}

int ColorAssign(int ReadDifficult) {
	switch (ReadDifficult) {
	case 1:
		return 3;//緑
	case 2:
		return 2;//黄
	case 3:
		return 1;//赤
	case 4:
		return 4;//水色
	default:
		return 5;//白
	}//色指定
	return 5;//白
}

void PointPrint(struct FileReadData ReadDataPut[],int Cr[],int rank,int point,int count) {
	int i = 0;
	/*rank=100以降で読み取りのみ*/
	if (rank < 100) {
		DrawFormatString(100, 50, Cr[1], "Ranking");
		/*１～３位*/
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
		/*4位以降*/
		for (i = 3; i < GETPOINT_RANK_NUM; i++) {
			if (rank == i + 1) {
				if (count % 20 < 10)DrawFormatString(100, 100 + i * 25, Cr[4], "%dth:%upoints", i + 1, ReadDataPut[i].readpoint);
			}
			else {
				DrawFormatString(100, 100 + i * 25, Cr[0], "%dth:%upoints", i + 1, ReadDataPut[i].readpoint);
			}
		}
		/*ランク外*/
		if (rank == 99)DrawFormatString(300, 100, Cr[4], "Now Get Points:%upoints", point);
	}
	else {
		/*ランキング表示*/
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
	/*エラーチェック,獲得ポイント,呼び出され方(100～104:難易度別呼び出しのみ,1～4:難易度により書き込みあり)*/
	int rank = 0, count = 0;//ランク,点滅処理用
	unsigned int stagepoint;//得点読み込み
	struct FileReadData ReadDataPutALL[GETPOINT_RANK_NUM + 1];//読み込み用(全体)
	struct FileReadData ReadDataPutDif[GETPOINT_RANK_NUM + 1];//読み込み用(難易度別)
	int i;

	/*文字の色*/
	int Cr[7];
	Cr[0] = GetColor(150, 150, 150);// 灰色の値を取得
	Cr[1] = GetColor(200, 0, 0);// 赤色の値を取得
	Cr[2] = GetColor(200, 200, 0);// 黄色の値を取得
	Cr[3] = GetColor(0, 200, 0);// 緑色の値を取得
	Cr[4] = GetColor(0, 200, 200);// 水色の値を取得
	Cr[5] = GetColor(240, 240, 240);// 白色の値を取得
	Cr[6] = GetColor(200, 0, 200);// 紫色の値を取得

	/*呼び出しなしなら戻る*/
	if (callflag == 999) {//呼び出しなし
		return 0;
	}

	///*ファイル読み込み*///
	ReadFile(ErrorCheck, 10, ReadDataPutALL);//ALLはどちらにせよ呼び出し
	switch (callflag){
	case 1:
	case 101:
		ReadFile(ErrorCheck, 11, ReadDataPutDif);//EASY呼び出し
		break;
	case 2:
	case 102:
		ReadFile(ErrorCheck, 12, ReadDataPutDif);//NORMAL呼び出し
		break;
	case 3:
	case 103:
		ReadFile(ErrorCheck, 13, ReadDataPutDif);//HARD呼び出し
		break;
	case 4:
	case 104:
		ReadFile(ErrorCheck, 14, ReadDataPutDif);//UNKNOWN呼び出し
		break;
	}
	/*ファイル読み込みここまで*/

	bool Key = TRUE;
	/*result画面表示*/
	if (callflag <= 4) {//ランキング表示＆結果表示

		//メモリへの読み込みサウンドハンドルをSHandleに保存します
		int SHandle = LoadSoundMem("../exe/package/bgm/rank.mp3");
		if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/rank.mp3");//再読み込み

		RankCheck(ReadDataPutALL, point, stage, callflag);//順位入れ替え
		rank = RankCheck(ReadDataPutDif, point, stage, callflag);//順位入れ替え
		while (1) {

			if (CheckSoundMem(SHandle) == 0) {
				PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
			}

			ClearDrawScreen(); // 画面を消す

			/*途中強制終了処理*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				ESCGameEnd(ErrorCheck);//強制終了
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				return -1;//errorなら強制終了
			}

			if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
				*ErrorCheck = 1;
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				return -1;        // エラーが起きたらループを抜ける
			}

			/*終了*/
			if (CheckHitKeyAll() == 0)Key = FALSE;//キーから１回手を離すこと

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
				Key = TRUE;
				break;
			}

			///*表示*///
			PointPrint(ReadDataPutDif, Cr, rank, point, count);//順位とポイント表示
			DrawFormatString(350, 400, Cr[0], "Thank you for playing!\nPlease SPACE or ENTER key...");

			ScreenFlip();
			count++;
			if (count > 30000)count = 0;
		}

		/*不正時リセット*/
		FALSEErrorCheck(ReadDataPutALL);
		FALSEErrorCheck(ReadDataPutDif);

		while (Key == TRUE) {
			if (CheckHitKeyAll() == 0)Key = FALSE;//キーから１回手を離すこと

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				return -1;//errorなら強制終了
			}

			if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
				*ErrorCheck = 1;
				return -1;        // エラーが起きたらループを抜ける
			}
		}//キーが押され無くなるまで待つ

		///*ファイル書き込み*///
		ReadFile(ErrorCheck, 20, ReadDataPutALL);//ALLはどちらにせよ書き込み
		switch (callflag) {
		case 1:
			ReadFile(ErrorCheck, 21, ReadDataPutDif);//EASY書き込み
			break;
		case 2:
			ReadFile(ErrorCheck, 22, ReadDataPutDif);//NORMAL書き込み
			break;
		case 3:
			ReadFile(ErrorCheck, 23, ReadDataPutDif);//HARD書き込み
			break;
		case 4:
			ReadFile(ErrorCheck, 24, ReadDataPutDif);//UNKNOWN書き込み
			break;
		}
		/*ファイル書き込みここまで*/

		// サウンドハンドルの削除
		DeleteSoundMem(SHandle);

		return rank;
	}
	else if (callflag >= 100 && callflag <= 104) {//呼び出しのみ
		ClearDrawScreen(); // 画面を消す
		/*ランキング表示*/
		if (callflag == 100) {
			PointPrint(ReadDataPutALL, Cr, callflag, 0, count);//ALL表示
		}
		else if (callflag > 100 && callflag < 105) {
			PointPrint(ReadDataPutDif, Cr, callflag, 0, count);//難易度別表示
		}

		ScreenFlip();
		WaitTimer(500);// ここで0.5秒まつ

		while (1) {
			ClearDrawScreen(); // 画面を消す

			/*途中強制終了処理*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				ESCGameEnd(ErrorCheck);//強制終了
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				return -1;//errorなら強制終了
			}

			if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
				*ErrorCheck = 1;
				return -1;        // エラーが起きたらループを抜ける
			}

			/*終了*/
			if (CheckHitKeyAll() == 0)Key = FALSE;//キーから１回手を離すこと

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
				break;
			}

			/*特殊処理（デバッグ用）*/
			if (CheckHitKey(KEY_INPUT_F) == 1 && CheckHitKey(KEY_INPUT_A) == 1 && CheckHitKey(KEY_INPUT_L) == 1 && CheckHitKey(KEY_INPUT_S) == 1 && CheckHitKey(KEY_INPUT_E) == 1 && Key == FALSE) {
				int FontHandle = CreateFontToHandle(NULL, 30, 3);
				int endflag = 0;
				while (1) {
					/*途中強制終了処理*/
					if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
						ESCGameEnd(ErrorCheck);//強制終了
					}

					if (*ErrorCheck > 0 || *ErrorCheck == -1) {
						return -1;//errorなら強制終了
					}

					if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
						*ErrorCheck = 1;
						return -1;        // エラーが起きたらループを抜ける
					}

					ClearDrawScreen(); // 画面を消す
					DrawStringToHandle(120, 150, "▲データを初期化しますか？", Cr[2], FontHandle);
					DrawStringToHandle(100, 220, "はい:y", Cr[2], FontHandle);
					DrawStringToHandle(300, 220, "いいえ:n", Cr[2], FontHandle);
					if (endflag == 1)DrawBox(80, 200, 200, 280, Cr[4], FALSE);    // 四角形を描画
					else if (endflag == 0)DrawBox(280, 200, 450, 280, Cr[4], FALSE);    // 四角形を描画
					DrawFormatString(100, 330, Cr[1], "十字キーで選択するか、yもしくはnで選択してzもしくはENTERで決定");
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
							}//リセット
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
				ClearDrawScreen(); // 画面を消す
				Key = TRUE;
			}
			/*デバッグコマンドここまで*/

			///*画面表示*///
			if (callflag == 100) {
				PointPrint(ReadDataPutALL, Cr, callflag, 0, count);//ALL表示
			}
			else if (callflag > 100 && callflag < 105) {
				PointPrint(ReadDataPutDif, Cr, callflag, 0, count);//難易度別表示
			}
			DrawFormatString(350, 400, Cr[0], "Please SPACE or ENTER key.");

			ScreenFlip();
		}

		/*不正時リセット*/
		FALSEErrorCheck(ReadDataPutALL);
		FALSEErrorCheck(ReadDataPutDif);


		///*ファイル書き込み*///
		ReadFile(ErrorCheck, 20, ReadDataPutALL);//ALLはどちらにせよ書き込み
		switch (callflag) {
		case 101:
			ReadFile(ErrorCheck, 21, ReadDataPutDif);//EASY書き込み
			break;
		case 102:
			ReadFile(ErrorCheck, 22, ReadDataPutDif);//NORMAL書き込み
			break;
		case 103:
			ReadFile(ErrorCheck, 23, ReadDataPutDif);//HARD書き込み
			break;
		case 104:
			ReadFile(ErrorCheck, 24, ReadDataPutDif);//UNKNOWN書き込み
			break;
		}
		/*ファイル書き込みここまで*/
	}

	return 0;
}
