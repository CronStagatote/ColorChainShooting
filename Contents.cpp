#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/*Contents*/

void Contents1_ScoreBoard(int *ErrorCheck, int SE,int Handle);
void Contents2_Enemy(int *ErrorCheck);
void Contents3_Operation(int *ErrorCheck);

int Contents(int *ErrorCheck) {//オプションと操作説明など
    //コンテンツメニュー
	int gameflag = -1, command = 0, commandtime = 0;
	bool Key = TRUE;
	int veryhardcount = 0;
	int Cr,Cr2;
	int Handle[12];
	int SE = LoadSoundMem("../exe/package/bgm/select.mp3");
	if (SE == -1)SE = LoadSoundMem("./package/bgm/select.mp3");

	// 　デフォルトのフォントで、フォントを作成し
	// 作成したデータの識別番号を変数 FontHandle に保存する
	int FontHandle = CreateFontToHandle(NULL, 15, 3);
	int FontHandle2 = CreateFontToHandle(NULL, 30, 3);

	// 色の値を取得
	Cr = GetColor(240, 240, 240);
	Cr2 = GetColor(240, 30, 30);
	int Cr3 = GetColor(255, 150, 30);

	/*ロード*/
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す
	DrawString(250, 250, "Now Lording...", Cr);
	DrawString(50, 320, "Contents Mode", Cr);
	DrawString(50, 340, "このモードでは様々な情報を見ることができるほか,", Cr);
	DrawString(50, 360, "ノーマル敵が攻撃してこないステージ10で遊べるパズルモード,", Cr);
	DrawString(50, 380, "ボス敵のみと戦えるボスラッシュといったモードがある.", Cr);
	DrawString(50, 400, "これらのモードで練習し,Player1 Modeで高得点を目指そう!", Cr);
	ScreenFlip();

	// PNG画像のメモリへの分割読み込み
	veryhardcount = LoadDivGraph("../exe/package/paint/Select.png", 12, 4, 3, 32, 32, Handle);
	//再読み込み
	if (veryhardcount == -1)LoadDivGraph("./package/paint/Select.png", 12, 4, 3, 32, 32, Handle);

	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
	//再読み込み
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽

	veryhardcount = 0;
	Key = TRUE;//ボタンが押されていることにしておく
	do{
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
			Key = TRUE;
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

		if (command < 10) {
			DrawStringToHandle(200, 100, "Contents", Cr2, FontHandle2);
			DrawString(240, 170, "1Player mode 得点表:1", Cr);
			DrawString(240, 200, "敵の種類と特徴:2", Cr);
			DrawString(240, 230, "操作説明とルール:3", Cr);
			DrawString(240, 260, "パズルモード:4", Cr);
			DrawString(240, 290, "ボスラッシュ:5", Cr);
			DrawString(240, 320, "タイトルに戻る:6", Cr);
			DrawStringToHandle(100, 410, "上下キーもしくは数字キー(1～4)で選択、ENTERもしくはzキーで決定", Cr, FontHandle);

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
			DrawString(200, 100, "難易度選択\n(ボスラッシュ)", Cr);
			DrawString(240, 200, "EASY", Cr);
			DrawString(240, 230, "NORMAL", Cr);
			DrawString(240, 260, "HARD", Cr);
			DrawString(240, 290, "Contents一覧に戻る", Cr);
			if (command == 15) {
				DrawString(240, 320, "UNKNOWN", Cr2);
				DrawStringToHandle(100, 450, "Sを押しながら下キーを押すと別モードに変更.", Cr3, FontHandle);
			}
			else if (command == 16) {
				DrawString(240, 320, "Stagatote_SP UNKNOWN", Cr2);
			}

			if (command != 16) {
				if (command == 13 || command == 15) {
					DrawStringToHandle(100, 355, "ボスラッシュは1PlayerModeに登場するボス4体(?)と連戦するモードです.", Cr3, FontHandle);
				}
				else {
					DrawStringToHandle(100, 355, "ボスラッシュは1PlayerModeに登場するボス4体と連戦するモードです.", Cr3, FontHandle);
				}
				DrawStringToHandle(100, 370, "難易度にかかわらず,アイテム使用不可,\nステージクリア時のHP回復なしとなっています.", Cr3, FontHandle);
			}
			else {
				DrawStringToHandle(100, 370, "難易度:UNKNOWNで裏ボスと戦えるモードです.\n結果は一切表示されません.", Cr3, FontHandle);
			}
			DrawStringToHandle(100, 430, "上下キーもしくは数字キー(1～4)で選択、ENTERもしくはzキーで決定", Cr, FontHandle);

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
			if (command == 0) {//1Player mode 得点表
				Contents1_ScoreBoard(ErrorCheck, SE, Handle[0]);
				gameflag = 1;
			}
			else if (command == 1) {//敵の種類と特徴
				Contents2_Enemy(ErrorCheck);
				gameflag = 2;
			}
			else if (command == 2) {//操作説明とルール
				Contents3_Operation(ErrorCheck);
				gameflag = 3;
			}
			else if (command == 3) {//パズルモード
				DeleteSoundMem(SHandle);
				/*ロード*/
				ClearDrawScreen(); // 画面を消す
				DrawString(250, 250, "Now Lording...", Cr);
				ScreenFlip();
				Player1mode(ErrorCheck, 20);
				SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
				//再読み込み
				if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
			}
			else if (command == 4) {//ボスラッシュ
				command = 11;
			}
			else if (command == 5) {//タイトルに戻る
				gameflag = 0;
			}
			else if (command >= 11 && command != 14) {
				DeleteSoundMem(SHandle);
				SHandle = LoadSoundMem("../exe/package/bgm/contents.mp3");
				//再読み込み
				if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/contents.mp3");
				/*ロード*/
				ClearDrawScreen(); // 画面を消す
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
			else if (command == 14) {//戻る
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
				if (veryhardcount >= 5) {//隠しコマンド
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

	while (Key == TRUE) {//キーが押されなくなるまで待つ
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			// 作成したフォントデータを削除する
			DeleteFontToHandle(FontHandle);
			return -1;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			Key = FALSE;
		}
	}

	// 作成したフォントデータを削除する
	DeleteFontToHandle(FontHandle);
	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);

	return 0;
}//Contents Menu


void Contents1_ScoreBoard(int *ErrorCheck,int SE,int Handle) {
	/*得点表*/
	bool KeyCheck = TRUE;//キーボードが押されているか
	int Cr = GetColor(240, 240, 240);
	int commandtime = 0;
	int veryhardcount = 0;
	int command = 0;
	bool Key = TRUE;//ボタンが押されていることにしておく
	do {
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
			Key = TRUE;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//errorなら強制終了
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
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

		DrawString(240, 100, "1Player mode 得点表", Cr);
		DrawString(240, 170, "ALL", Cr);
		DrawString(240, 200, "EASYのみ", Cr);
		DrawString(240, 230, "NORMALのみ", Cr);
		DrawString(240, 260, "HARDのみ", Cr);
		DrawString(240, 290, "戻る", Cr);
		if (command == 5)DrawString(240, 320, "UNKNOWNのみ", Cr);
		DrawString(50, 400, "上下キーもしくは数字キー(1～4)で選択、\nENTERもしくはzキーで決定", Cr);

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
				RankingFileCheck(ErrorCheck, 0, 100, 0);//得点表を呼ぶ(callflag==10*で読み取りのみ)
			}
			else if (command == 1) {
				RankingFileCheck(ErrorCheck, 0, 101, 0);//得点表を呼ぶ(callflag==10*で読み取りのみ)
			}
			else if (command == 2) {
				RankingFileCheck(ErrorCheck, 0, 102, 0);//得点表を呼ぶ(callflag==10*で読み取りのみ)
			}
			else if (command == 3) {
				RankingFileCheck(ErrorCheck, 0, 103, 0);//得点表を呼ぶ(callflag==10*で読み取りのみ)
			}
			else if (command == 4) {
				break;
			}
			else if (command == 5) {
				RankingFileCheck(ErrorCheck, 0, 104, 0);//得点表を呼ぶ(callflag==10*で読み取りのみ)
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
				if (veryhardcount >= 5) {//隠しコマンド
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

	while (KeyCheck == TRUE) {//キーが押されなくなるまで待つ
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			KeyCheck = FALSE;
		}
	}
	
}//Contents1_ScoreBoard


void Contents2_Enemy(int *ErrorCheck) {
	/*敵の種類と特徴*/
	bool KeyCheck = TRUE;//キーボードが押されているか
	int Cr = GetColor(240, 240, 240);
	int NormalEnemyGraphic[20], BossGraphic[6];
	int page = -1;
	// PNG画像のメモリへの分割読み込み
	page = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//再読み込み
	if (page == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	page = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//再読み込み
	if (page == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	page = 0;
	do {

		ClearDrawScreen(); // 画面を消す
		/*ループ抜け用処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//errorなら強制終了
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			KeyCheck = FALSE;
		}

		if (KeyCheck == FALSE) {//キーが一回離された
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				KeyCheck = TRUE;
				page++;
				if (page >= 3)break;//Zキーが押されたらループを抜ける
			}
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
		}

		/*処理本体*/
		if (page == 0) {
			DrawString(230, 10, "Normal Enemy", Cr);
			DrawGraph(30, 50, NormalEnemyGraphic[0], TRUE);
			DrawString(30, 90, "色:赤\n狙う場所:真下", Cr);
			DrawGraph(230, 50, NormalEnemyGraphic[1], TRUE);
			DrawString(230, 90, "色:青\n狙う場所:自機左", Cr);
			DrawGraph(430, 50, NormalEnemyGraphic[2], TRUE);
			DrawString(430, 90, "色:黄\n狙う場所:自機右", Cr);

			DrawGraph(30, 150, NormalEnemyGraphic[3], TRUE);
			DrawString(30, 190, "色:緑\n狙う場所:自機", Cr);
			DrawGraph(230, 150, NormalEnemyGraphic[4], TRUE);
			DrawString(230, 190, "色:橙\n狙う場所:左", Cr);
			DrawGraph(430, 150, NormalEnemyGraphic[5], TRUE);
			DrawString(430, 190, "色:紫\n狙う場所:右", Cr);

			DrawGraph(30, 250, NormalEnemyGraphic[6], TRUE);
			DrawString(30, 290, "色:赤紫\n攻撃しない", Cr);
			DrawGraph(230, 250, NormalEnemyGraphic[7], TRUE);
			DrawString(230, 290, "色:空\n自機の動く先を狙う", Cr);
			DrawGraph(430, 250, NormalEnemyGraphic[8], TRUE);
			DrawString(430, 290, "色:白\n狙う場所:自機\n", Cr);
			DrawString(20, 350, "白機体は倒してもコンボに加算されず、色も変わらない。一律3点.", Cr);

			DrawString(20, 400, "*ZキーまたはENTERキーで次のページへ.", Cr);
		}
		else if (page == 1) {
			DrawString(230, 10, "Boss Enemy1", Cr);
			DrawGraph(30, 40, BossGraphic[0], TRUE);
			DrawString(100, 40, "名称:Grad(グラド)  出現ステージ:3", Cr);
			DrawString(100, 60, "HP > EASY:20 Normal:25 Hard:30", Cr);
			DrawString(100, 80, "特殊技:誘導弾  色:赤,橙,黄", Cr);

			DrawGraph(30, 120, BossGraphic[1], TRUE);
			DrawString(100, 120, "名称:Cron(クロン)  出現ステージ:6", Cr);
			DrawString(100, 140, "HP > EASY:28 Normal:35 Hard:42", Cr);
			DrawString(100, 160, "特殊技:レーザー  色:緑,紫,空", Cr);

			DrawGraph(30, 220, BossGraphic[2], TRUE);
			DrawString(100, 220, "名称:Erec(エレク)  出現ステージ:9", Cr);
			DrawString(100, 240, "HP > EASY:38 Normal:48 Hard:58", Cr);
			DrawString(100, 260, "特殊技:突進  色:青,黄,紫", Cr);

			DrawGraph(30, 300, BossGraphic[3], TRUE);
			DrawString(100, 300, "名称:Rain(レイン)  出現ステージ:11(LAST)", Cr);
			DrawString(100, 320, "HP > EASY:56 Normal:70 Hard:84", Cr);
			DrawString(100, 340, "特殊技:誘導弾,レーザー,突進  色:全", Cr);
			DrawGraph(30, 370, BossGraphic[5], TRUE);
			DrawString(100, 370, "(Rainの分身)", Cr);
			DrawString(100, 390, "HP: -  ダメージを受けず,RainのHPが0になると同時に消滅.", Cr);
			DrawString(100, 410, "ただし,攻撃すると1秒程度(難易度により変動)動きが止まる.", Cr);

			DrawString(20, 440, "*ZキーまたはENTERキーで次のページへ.", Cr);
		}
		else if (page == 2) {
			DrawString(230, 10, "Boss Enemy2", Cr);

			DrawGraph(30, 40, BossGraphic[4], TRUE);
			DrawString(100, 40, "名称:Staga(スタガ)  出現ステージ:5(2Player Mode)", Cr);
			DrawString(100, 60, "HP:50  特殊技:ノーマル敵（白)召喚", Cr);

			DrawGraph(30, 120, BossGraphic[4], TRUE);
			DrawGraph(34, 123, NormalEnemyGraphic[9], TRUE);
			DrawString(100, 120, "名称:Stagatote_SP(スタガトテ・スペシャル)", Cr);
			DrawString(100, 140, "Boss Rushにて残りHP15以上でRainを倒すと出現", Cr);
			DrawString(100, 160, "HP(HARD):66 (EASY,NORMALでは出現しない)", Cr);
			DrawString(100, 180, "特殊技:ノーマル敵（白)召喚,バリアショット", Cr);
			DrawString(100, 200, "*特殊技前にワープする能力を持つ*    色:無", Cr);

			DrawString(230, 250, "敵の弾について", Cr);
			DrawGraph(30, 280, NormalEnemyGraphic[11], TRUE);
			DrawGraph(65, 280, NormalEnemyGraphic[12], TRUE);
			DrawGraph(100, 280, NormalEnemyGraphic[13], TRUE);
			DrawString(150, 280, "通常弾.当たると1ダメージ.", Cr);
			DrawString(150, 300, "飛び方は様々.", Cr);

			DrawGraph(30, 330, NormalEnemyGraphic[14], TRUE);
			DrawString(70, 330, "誘導弾.当たると3ダメージ.", Cr);
			DrawString(70, 350, "自機に向かってくる.", Cr);

			DrawGraph(30, 380, NormalEnemyGraphic[10], TRUE);
			DrawString(70, 380, "バリアショット.当たると3ダメージ.", Cr);
			DrawString(70, 400, "自機の攻撃をガードする弾(通常弾は自機の攻撃をすり抜ける).", Cr);

			DrawString(20, 440, "*ZキーまたはENTERキーで戻る.", Cr);
		}


		ScreenFlip();
	} while (1);

	while (KeyCheck == TRUE) {//キーが押されなくなるまで待つ
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			KeyCheck = FALSE;
		}
	}

}//Contents2_Enemy


void Contents3_Operation(int *ErrorCheck) {
	/*操作方法と得点計算など*/
	bool KeyCheck = TRUE;//キーボードが押されているか
	int Cr = GetColor(240, 240, 240);
	int page = 0;
	SetFontSize(12);
	SetFontThickness(4);

	do {

		ClearDrawScreen(); // 画面を消す
		/*ループ抜け用処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			SetFontSize(16);
			SetFontThickness(6);
			return;//errorなら強制終了
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			KeyCheck = FALSE;
		}

		if (KeyCheck == FALSE) {//キーが一回離された
			if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) {
				KeyCheck = TRUE;
				page++;
				if (page >= 4)break;//Zキーが押されたらループを抜ける
			}
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
		}

		/*処理本体*/
		if (page == 0) {
			DrawString(200, 20, "操作説明", Cr);
			DrawString(200, 40, "-1Player Mode-", Cr);
			DrawString(200, 60, "・LEFTキー:左に移動", Cr);
			DrawString(200, 80, "・RIGHTキー:右に移動", Cr);
			DrawString(200, 100, "・Zキー:ショット1", Cr);
			DrawString(200, 120, "・Xキー:ショット2", Cr);
			DrawString(200, 140, "・Cキー:ショット3", Cr);
			DrawString(200, 200, "-2Player Mode-", Cr);
			DrawString(50, 230, "<Player1>", Cr);
			DrawString(50, 250, "・Cキー:左に移動", Cr);
			DrawString(50, 270, "・Bキー:右に移動", Cr);
			DrawString(50, 290, "・Qキー:ショット1", Cr);
			DrawString(50, 310, "・Wキー:ショット2", Cr);
			DrawString(50, 330, "・Eキー:ショット3", Cr);
			DrawString(300, 230, "<Player2>", Cr);
			DrawString(300, 250, "・LEFTキー:左に移動", Cr);
			DrawString(300, 270, "・RIGHTキー:右に移動", Cr);
			DrawString(300, 290, "・Iキー:ショット1", Cr);
			DrawString(300, 310, "・Oキー:ショット2", Cr);
			DrawString(300, 330, "・Pキー:ショット3", Cr);

			DrawString(100, 400, "*ZキーまたはENTERキーで次のページへ.", Cr);
		}
		else if (page == 1) {
			DrawString(200, 20, "得点について", Cr);
			DrawString(200, 40, "*1Player Mode", Cr);
			DrawString(100, 60, "<ノーマルステージ>", Cr);
			DrawString(50, 80,"基本,一体倒すごとに1点.ただし、倒したときの\nショットのコンボ(-注下-)数によって以下のように変化する.", Cr);
			DrawString(50, 110, "・1コンボにつき,倒したときの得点が2倍になる.", Cr);
			DrawString(50, 125, "・コンボが途切れると,また1点に戻る.", Cr);
			DrawString(50, 140, "例", Cr);
			DrawString(50, 160, "1.Zショットで赤の機体を倒す:(基本点1)点=1点　計1点", Cr);
			DrawString(50, 180, "2.Zショットで赤の機体を倒す:(基本点1*2)点=2点　計3点", Cr);
			DrawString(50, 200, "3.Zショットで赤の機体を倒す:(基本点1*2*2)点=4点　計7点", Cr);
			DrawString(50, 220, "4.Zショットで赤の機体を倒す:(基本点1*2*2*2)点=8点　計15点", Cr);
			DrawString(50, 240, "5.Xショットで赤の機体を倒す:(基本点1)点=1点　計16点", Cr);
			DrawString(50, 260, "6.Zショットで赤の機体を倒す:(基本点1*2*2*2*2)点=16点　計32点", Cr);
			DrawString(50, 280, "7.Zショットで青の機体を倒す:(基本点1)点=1点　計33点", Cr);
			DrawString(50, 300, "8.Zショットで赤の機体を倒す:(基本点1)点=1点　計34点", Cr);
			DrawString(50, 325, "-注-  コンボ:同じショットで、何回連続で同じ色の機体を倒したか", Cr);
			DrawString(50, 355, "<ボスステージ>", Cr);
			DrawString(50, 375, "1回攻撃を与える度に3点,倒すとEASY:100,NORMAL:200,HARD:300点", Cr);
			DrawString(50, 392, "(LASTステージではEASY:1000,NORMAL:2000,HARD:3000点)", Cr);
			DrawString(50, 410, "ステージ11以外は敵の部位によってショットに色がつく.", Cr);
			DrawString(50, 430, "同じ部位を攻撃するとコンボになる.コンボ数分の得点が加算される.", Cr);
			DrawString(100, 450, "*ZキーまたはENTERキーで次のページへ.", Cr);
		}
		else if (page == 2) {
			DrawString(200, 20, "得点について", Cr);
			DrawString(200, 40, "*2Player Mode", Cr);
			DrawString(100, 60, "<ノーマルステージ>", Cr);
			DrawString(50, 80, "基本,一体倒すごとに1点.ただし、倒したときの\nショットのコンボ数によって以下のように変化する.", Cr);
			DrawString(50, 120, "・1コンボにつき,倒したときの得点が3倍になる.", Cr);
			DrawString(50, 135, "・コンボ数と同じだけボーナス点が入る", Cr);
			DrawString(50, 160, "<ボスステージ>", Cr);
			DrawString(50, 180, "1回攻撃を与える度に3点,倒すと1000点", Cr);
			DrawString(50, 200, "ボスの出現させる敵は一体倒すごとに5点(コンボ数は増えず,ショットの色も無のまま)", Cr);

			DrawString(50, 300, ":注:2Player Modeでは,各プレイヤーにHPがない代わり,\n敵の弾に当たると得点が10下がる", Cr);

			DrawString(100, 400, "*ZキーまたはENTERキーで次のページへ.", Cr);
		}
		else if (page == 3) {
			DrawString(200, 20, "アイテムについて", Cr);
			DrawString(50, 60, "アイテムは1Player Modeでしか入手できない.", Cr);
			DrawString(50, 75, "自身の使用可能アイテム数はHPの下のITEMに表示.", Cr);
			DrawString(50, 90, "アイテム所持数は,ゲーム開始時は1だが,いずれかのショットが(5の倍数)コンボに", Cr);
			DrawString(50, 105, "なるたびに1増える.また,ボスを倒しても1増える.", Cr);
			DrawString(50, 120, "SPACEキーを押すと,アイテムメニューが開く.", Cr);
			DrawString(50, 135, "そこでは,以下の３つのアイテムを選んで使うことができる.", Cr);
			DrawString(50, 150, "(使用するとアイテム所持数がカッコ内の分だけ減る.)", Cr);
			DrawString(50, 180, "1:色替え(ITEM1消費)", Cr);
			DrawString(120, 200, "このアイテムを使うと、Z,X,C全てのショットの色を", Cr);
			DrawString(120, 215, "任意の色に変えることができる。", Cr);
			DrawString(120, 230, "元の色を選択して、変えないことも可能.", Cr);
			DrawString(120, 245, "コンボ数に変化はないため、例えば赤で5コンボ中のZショット", Cr);
			DrawString(120, 260, "を青に変え,青を倒すと6コンボになる.", Cr);
			DrawString(50, 290, "2:ストップ(ITEM2消費)", Cr);
			DrawString(120, 310, "このアイテムを使うと、現在存在中の敵の弾をすべて消し,", Cr);
			DrawString(120, 325, "さらに5秒程度(ボスは3秒程度)動きを止めることができる.", Cr);
			DrawString(50, 355, "3:HP回復(ITEM2消費)", Cr);
			DrawString(120, 375, "このアイテムを使うと、即座にHPが10回復し,一種無敵になる.", Cr);
			DrawString(120, 390, "HPの最大値は30なので,30までしか回復しないので注意.", Cr);
			DrawString(120, 405, "なお,現在HPが30の場合,使用できない(灰色になっている).", Cr);

			DrawString(100, 430, "*ZキーまたはENTERキーで戻る.", Cr);
		}

		ScreenFlip();
	} while (1);

	SetFontSize(16);
	SetFontThickness(6);

	while (KeyCheck == TRUE) {//キーが押されなくなるまで待つ
		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKeyAll() == 0) {//キーが押されていない
			KeyCheck = FALSE;
		}
	}

}//Contents3_Operation