#include "DxLib.h"
#include"Color_Chain_Shooting.h"


int Title(int *ErrorCheck, int *gamemode) {//タイトル画面
	//ゲームスタート時の画面用
	int checktmp = -1;
	int gameflag = 0, command = 0, commandtime = 0;
	bool Key;
	int Handle[12], G;
	int veryhardcount = 0;
	int FontHandle = CreateFontToHandle(NULL, 15, 3);
	int FontHandle2 = CreateFontToHandle(NULL, 30, 5);
	int titlewaittime = 0;

	// 色の値を取得
	int Cr = GetColor(240, 240, 240);
	int CrG = GetColor(0, 240, 0);//緑
	int CrY = GetColor(240, 240, 0);//黄
	int CrR = GetColor(240, 0, 0);//赤
	int CrP = GetColor(150, 30, 240);//紫
	int CrB = GetColor(0, 0, 0);//黒

	// PNG画像のメモリへの分割読み込み
	checktmp = LoadDivGraph("../exe/package/paint/Select.png", 12, 4, 3, 32, 32, Handle);
	if (checktmp == -1)LoadDivGraph("./package/paint/Select.png", 12, 4, 3, 32, 32, Handle);//再読み込み
	G = LoadGraph("../exe/package/paint/Title.png");
	if (G == -1)G = LoadGraph("./package/paint/Title.png");//再読み込み

	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/title.mp3");
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/title.mp3");//再読み込み
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
	int SE = LoadSoundMem("../exe/package/bgm/select.mp3");
	if (SE == -1)SE = LoadSoundMem("./package/bgm/select.mp3");//再読み込み
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	Key = true;//ボタンが押されていることにしておく
	while (gameflag != 1) {
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			Key = true;
			ESCGameEnd(ErrorCheck);//強制終了
			if (command == 4) {
				SetBackgroundColor(240, 240, 240);
			}
		}


		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// 作成したフォントデータを削除する
			DeleteFontToHandle(FontHandle);
			// サウンドハンドルの削除
			DeleteSoundMem(SHandle);
			return -1;//errorなら強制終了
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			// 作成したフォントデータを削除する
			DeleteFontToHandle(FontHandle);
			// サウンドハンドルの削除
			DeleteSoundMem(SHandle);
			return -1;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			Key = FALSE;
		}
		else {//キーが押されている
			commandtime++;
			if (commandtime > 1000) {
				commandtime = 0;
				Key = FALSE;
			}
		}

		ClearDrawScreen(); // 画面を消す

		if (gameflag != 10) {
			DrawGraph(0, 0, G, true);//タイトル画面

			DrawString(280, 270, "1Player mode:1", Cr);
			DrawString(280, 300, "2Player mode:2", Cr);
			DrawString(280, 330, "contents:3", Cr);
			DrawString(280, 360, "ゲーム終了:4", Cr);
			DrawStringToHandle(100, 420, "上下キーもしくは数字キー(1～4)で選択、ENTERもしくはzキーで決定", Cr, FontHandle);


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
				else if (command == 3) {//ゲーム終了
					gameflag = 0;
					// 作成したフォントデータを削除する
					DeleteFontToHandle(FontHandle);
					// サウンドハンドルの削除
					DeleteSoundMem(SHandle);
					return gameflag;//1:1Player 2:2Player 3:Contents 0:end
				}
				Key = true;
				if (gameflag != 10)break;//Zキーが押されたらループを抜ける
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

			/*時間経過とデモ画面*/
			titlewaittime++;
			if (titlewaittime > 3600) {
				StopSoundMem(SHandle);
				Demonstration(ErrorCheck);
				titlewaittime = 0;
				Key = true;
			}
		}
		else {//gameflag=10:ゲームモード選択
			if (command == 0) {
				DrawStringToHandle(250, 80, "難易度選択", CrG, FontHandle2);
			}
			else if (command == 1) {
				DrawStringToHandle(250, 80, "難易度選択", CrY, FontHandle2);
			}
			else if (command == 2) {
				DrawStringToHandle(250, 80, "難易度選択", CrR, FontHandle2);
			}
			else if (command == 4) {
				DrawStringToHandle(250, 80, "難易度選択", CrB, FontHandle2);
			}
			else {
				DrawStringToHandle(250, 80, "難易度選択", Cr, FontHandle2);
			}
			DrawString(280, 150, "Tutoreal:0", Cr);
			DrawString(280, 180, "EASY:1", Cr);
			DrawString(280, 210, "NORMAL:2", Cr);
			DrawString(280, 240, "HARD:3", Cr);
			DrawString(280, 270, "戻る:4", Cr);
			DrawStringToHandle(100, 420, "上下キーもしくは数字キー(1～4)で選択、ENTERもしくはzキーで決定", Cr, FontHandle);

			if (command == -1) {
				DrawGraph(240, 140, Handle[5], true);
				DrawStringToHandle(100, 320, "チュートリアルモードです.", Cr, FontHandle);
				DrawStringToHandle(100, 338, "敵の配置は固定で,ステージ3までとなっています.", Cr, FontHandle);
				DrawStringToHandle(100, 356, "説明用のモードで,記録は一切保存されません.", Cr, FontHandle);
			}
			else if (command == 0) {
				DrawGraph(240, 170, Handle[5], true);
				DrawStringToHandle(100, 320, "EASY", CrG, FontHandle);
				DrawStringToHandle(100, 338, "HPが毎ステージ全回復します(HP:30).", CrG, FontHandle);
				DrawStringToHandle(100, 356, "NORMALと比べ,敵の攻撃間隔が長く,弾数が減ります.", CrG, FontHandle);
				DrawStringToHandle(100, 374, "さらに,ボスのHPもNORMALと比べ減少します。", CrG, FontHandle);
				DrawStringToHandle(100, 392, "ただし,ボーナス得点もNORMALと比べ減少します.", CrG, FontHandle);
			}
			else if (command == 1) {
				DrawGraph(240, 200, Handle[5], true);
				DrawStringToHandle(100, 320, "NORMAL", CrY, FontHandle);
				DrawStringToHandle(100, 338, "HPが毎ステージ5回復します(最大値:30).", CrY, FontHandle);
				DrawStringToHandle(100, 356, "推奨難易度です.", CrY, FontHandle);
				DrawStringToHandle(100, 374, "よりパズルを求めるならEASYを,", CrY, FontHandle);
				DrawStringToHandle(100, 392, "よりシューティングを求めるならHARDを選んでください.", CrY, FontHandle);
			}
			else if (command == 2) {
				DrawGraph(240, 230, Handle[5], true);
				DrawStringToHandle(100, 320, "HARD", CrR, FontHandle);
				DrawStringToHandle(100, 338, "HPは次ステージに持ち越しになります(ステージ毎の回復なし).", CrR, FontHandle);
				DrawStringToHandle(100, 356, "Normalと比べ,敵の攻撃間隔が短くなります.", CrR, FontHandle);
				DrawStringToHandle(100, 374, "さらに,ボスのHPもNORMALと比べ増加します.", CrR, FontHandle);
				DrawStringToHandle(100, 392, "しかし,ボーナス得点もNORMALと比べ増加します.", CrR, FontHandle);
			}
			else if (command == 3) {
				DrawGraph(240, 260, Handle[5], true);
			}
			else if (command == 4) {//隠しコマンド
				DrawGraph(240, 290, Handle[5], true);
				//DrawBox(90, 330, 500, 410, CrY, true);
				DrawString(280, 300, "UNKNOWN", CrR);
				DrawStringToHandle(100, 338, "基本はHARDと同じ.", CrP, FontHandle);
				DrawStringToHandle(100, 356, "ボスの攻撃激化,ノーマル敵は全てランダム攻撃.", CrP, FontHandle);
				DrawStringToHandle(100, 374, "ボスのHPはHARDよりも増加.", CrP, FontHandle);
				DrawStringToHandle(100, 392, "ボーナス得点もHARDよりも増加.", CrP, FontHandle);
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
				if (gameflag != 0)break;//Zキーが押されたらループを抜ける
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
					if (veryhardcount >= 10) {//隠しコマンド
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

	while (Key == true) {//キーが押され無くなるまで待つ
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			// 作成したフォントデータを削除する
			DeleteFontToHandle(FontHandle);
			return -9;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			Key = FALSE;
		}
	}

	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle);

	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);

	command = 0;

	return gameflag;//1:1Player 2:2Player 3:Contents 0:end
}
