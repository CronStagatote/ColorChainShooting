#include "DxLib.h"
#include"Color_Chain_Shooting.h"
#include"Player1ModeSystemData.h"

#define MAXENEMY 70
#define MAXMAPX 500
#define MAXMAPY 395 
#define AFTERGAMEOVERCOUNT 300

#define NEXTKEYTIME1 60

/////---**1Player mode**---/////

/*ステージ初めの際の敵出現用関数*/
void NormalStage_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	int i, j;
	int enemyxnum = 0, enemyynum = 0;//横に並ぶ総数、縦に並ぶ総数
	int Enemypx[MAXENEMY] = {}, Enemypy[MAXENEMY] = {};//敵機の座標指定
	int Enemykindr[MAXENEMY] = {};//敵機の種類
	int startx;//敵のxの端の座標
	int stageenkind = 0;//ステージによる敵機の種類数
	/*ステージ内の敵数*/
	switch (stage) {
	case 1:
		enemyxnum = 8;
		enemyynum = 2;
		startx = 90;
		stageenkind = 5;
		break;
	case 2:
		enemyxnum = 10;
		enemyynum = 2;
		startx = 50;
		stageenkind = 5;
		break;
	case 4:
		enemyxnum = 10;
		enemyynum = 3;
		startx = 50;
		stageenkind = 6;
		break;
	case 5:
		enemyxnum = 12;
		enemyynum = 3;
		startx = 10;
		stageenkind = 6;
		break;
	case 7:
		enemyxnum = 10;
		enemyynum = 4;
		startx = 50;
		stageenkind = 7;
		break;
	case 8:
		enemyxnum = 12;
		enemyynum = 4;
		startx = 10;
		stageenkind = 7;
		break;
	case 10:
		enemyxnum = 12;
		enemyynum = 5;
		startx = 10;
		stageenkind = 7;
		break;
	default://stage3,6,9,11はボス
		return;
	}

	for (i = 0; i < enemyynum; i++) {
		for (j = 0; j < enemyxnum; j++) {
			Enemypx[i*enemyxnum + j] = startx + j * 40;
			Enemypy[i*enemyxnum + j] = 10 + i * 40;
			Enemykindr[i*enemyxnum + j] = GetRand(stageenkind);//0～5,6,7までの乱数を取得
		}
	}

	for (i = 0; i < enemyxnum*enemyynum; i++) {
		Enemy[i].AppearEnemy(Enemypx[i], Enemypy[i], Enemykindr[i]);
	}//出現処理

}//ステージ初めの処理(ノーマルステージのみ)

/*ステージクリア画面*/
unsigned int StageClear(int *ErrorCheck,int stage, unsigned int point, Mode1Player Player, int gameflag, int gamecount,int gamemode,int itemnum) {
	//色作成
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//赤
	Cr[1] = GetColor(15, 15, 255);//青
	Cr[2] = GetColor(255, 255, 15);//黄
	Cr[3] = GetColor(15, 255, 15);//緑
	Cr[4] = GetColor(255, 156, 0);//橙
	Cr[5] = GetColor(159, 15, 255);//紫
	Cr[6] = GetColor(218, 0, 224);//赤紫
	Cr[7] = GetColor(76, 255, 255);//空
	Cr[8] = GetColor(240, 240, 240);//白
	Cr[9] = GetColor(128, 128, 128);//灰

	int ComboNum[3] = {};
	Player.PlayerShotCombo(ComboNum);
	int truepoints = 0, a = 1, b = 0, c = 0;
	int times;
	bool KeyCheck = true, QEndflag = false;
	a = Player.GetPoint();

	if (gameflag < 10) {//通常モード
		if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {//ボスステージ
			b += 5 * stage*(itemnum + 1);
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (ComboNum[i] == 0) {
					b += 5 * stage;
				}
				else {
					b += (ComboNum[i] - 1) * (ComboNum[i] + stage);
				}
			}
		}
		b += itemnum * 50;
		c = Player.PlayerHP(0) * 5 * gamemode;
		if (Player.PlayerHP(0) == 30) {//HP最大でクリア
			c += 50;
		}
		times = gamemode * 2 + stage + 5;
		a = a * times / 5;
		if (gamemode == 3) {
			a *= 1.5;
		}
		else if (gamemode == 4) {
			a *= 2;
		}

		if (a > 999999999 || (Player.GetPoint() > 10000 && a < 10000))a = 999999999;//オーバーフロー時エラー防止
		if (Player.GetPoint() >= 999999999)a = 999999999;//オーバーフローエラー防止
		if (stage == 3 || stage == 6 || stage == 9) {
			a *= 0.75;//ボスの倍率を低めにする
		}

		if (gameflag == 3) {//GameOver
			b = 0;
			c = 0;
		}//ボーナス点なし

		b += Player.TotalComboNum()*gamemode;//2以上のコンボ達成数*難易度ボーナスが加算

		/*ボーナス点変動*/
		if (gamemode == 1) {//EASY
			b *= 0.75;
			c *= 0.375;
		}
		else if (gamemode == 3) {//HARD
			b *= 1.5;
			c *= 2;
		}
		else if (gamemode == 4) {//UNKNOWN
			b *= 3;
			c *= 5;
		}
		
		b *= 0.5;//調整用
		c *= 0.5;//調整用
		truepoints = a + b + c;//合計得点(最終的なステージ得点)
		if (truepoints > 999999999)truepoints = 999999999;//オーバーフローエラー防止
		if (point > 1000000000) {//オーバーフローエラー防止
			unsigned int pointtmp = point;
			point += truepoints;
			if (pointtmp > point) {//オーバーフローした
				point = UINT_MAX;
			}
		}
		else {
			point += truepoints;
		}
		
	}

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/result.mp3");
	if (SHandle == -1) {
		SHandle = LoadSoundMem("./package/bgm/result.mp3");//再読み込み
	}
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
	

	do {
		ClearDrawScreen(); // 画面を消す
		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		if (CheckHitKeyAll() == 0) {
			KeyCheck = false;
		}

		/*途中強制終了処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
			KeyCheck = true;
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

		if ((CheckHitKey(KEY_INPUT_SPACE) == 1 || CheckHitKey(KEY_INPUT_RETURN) == 1) && KeyCheck == false) {
			break;
		}

		if (CheckHitKey(KEY_INPUT_Q) == 1 && gamemode < 10 && KeyCheck == false) {
			if (QEndflag == false) {
				QEndflag = true;
				KeyCheck = true;
			}
			else {
				*ErrorCheck = -2;
				break;
			}
		}


		if (gamemode < 10) {//通常モード
		/*画面表示*/
			SetFontSize(30);
			if (gameflag == 1) {
				DrawFormatString(100, 50, Cr[0], "Stage %d Clear!!", stage);
			}
			else if (gameflag == 2) {
				DrawFormatString(100, 50, Cr[7], "1Player Mode Clear!!");
			}
			else if (gameflag == 3) {
				DrawFormatString(100, 50, Cr[1], "Stage %d", stage);
			}
			SetFontSize(15);
			if (gameflag == 1) {
				if (stage == 2 || stage == 5 || stage == 8) {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:%d(BOSS STAGE)", stage + 1);
				}
				else if (stage == 10) {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:LAST(Boss)");
				}
				else {
					DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->NEXT STAGE:%d", stage + 1);
				}

				if (QEndflag == false) {
					DrawFormatString(100, 440, Cr[4], "Q -->Game End(back Title)");
				}
				else {
					DrawFormatString(100, 440, Cr[4], "本当に戻ってもよろしいですか?");
					DrawFormatString(100, 455, Cr[4], "はい>Q  戻らずに続行する>SPACE or ENTER");
				}
			}
			else if (gameflag == 2) {
				DrawFormatString(200, 85, Cr[2], "Thank You For Playing!!");
				if (gamemode == 3) {
					DrawFormatString(200, 105, Cr[8], "難易度選択画面で下キーを連打すると...?");
				}
				DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Ranking");
			}
			else if (gameflag == 3) {
				DrawFormatString(100, 80, Cr[1], "Game Over...");
				DrawFormatString(100, 110, Cr[2], "Thank You For Playing!!");
				DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Ranking");
			}
			DrawFormatString(50, 150, Cr[5], "Stage Points:%d", Player.GetPoint());
			DrawFormatString(50, 180, Cr[3], "Rest HP:%d", Player.PlayerHP(0));
			if (gamemode == 1) {//EASY
				if (gameflag == 1 && Player.PlayerHP(0) < 30)DrawFormatString(50, 200, Cr[3], ">Heal 30HP(MAX:30)");
			}
			else if (gamemode == 2) {//NORMAL
				if (gameflag == 1 && Player.PlayerHP(0) < 30)DrawFormatString(50, 200, Cr[3], ">Heal 5HP(MAX:30)");
			}
			else {
				if (gameflag == 1 && Player.PlayerHP(0) == 0)DrawFormatString(50, 200, Cr[3], ">Heal 1HP");
			}

			DrawFormatString(50, 240, Cr[6], "Last Combo(Z):%d", ComboNum[0]);
			DrawFormatString(50, 260, Cr[6], "Last Combo(X):%d", ComboNum[1]);
			DrawFormatString(50, 280, Cr[6], "Last Combo(C):%d", ComboNum[2]);
			DrawFormatString(50, 330, Cr[8], "RESULT");
			DrawFormatString(50, 350, Cr[0], "Stage %d Skill Points(Stage Points + Bonus points):%d", stage, truepoints);
			DrawFormatString(50, 370, Cr[3], "Total Points:%u", point);
		}
		else {//特殊モード
			SetFontSize(35);
			if (gameflag == 1 || gameflag == 2) {//クリア時
				if (gamemode == 20) {
					DrawFormatString(100, 100, Cr[3], "PUZZLE Mode CLEAR!");
				}
				else {
					if (stage == 11 && gamemode >= 13) {
						DrawFormatString(100, 100, Cr[3], "Boss Rush CLEAR.");
					}
					else {
						DrawFormatString(100, 100, Cr[3], "Boss Rush CLEAR!");
					}
				}
			}
			else {
				DrawFormatString(100, 100, Cr[1], "Game Over...");
			}

			if (gamemode == 11) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:EASY");
			}
			else if (gamemode == 12) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:NORMAL");
			}
			else if (gamemode == 13) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:HARD");
			}
			else if (gamemode == 14) {
				DrawFormatString(100, 200, Cr[6], "Game Mode:UNKNOWN");
			}

			if (gamemode == 20) {
				DrawFormatString(100, 200, Cr[4], "Points:%d", Player.GetPoint());
			}
			SetFontSize(15);
			if (stage == 16 && gamemode == 13) {
				if (gamemode == 13) {
					DrawFormatString(100, 300, Cr[8], "難易度選択画面で下キーを連打すると...?");
				}
				else if (gamemode == 14) {
					DrawFormatString(100, 300, Cr[2], "おめでとう! BossRush完全クリア!");
				}
			}
			DrawFormatString(100, 420, Cr[4], "SPACE or ENTER -->Back");
		}

		/*その他の処理*/
		
		ScreenFlip();

	} while (1);//終了しない限り


	SetFontSize(16);
	ClearDrawScreen(); // 画面を消す
	ScreenFlip();
	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);

	return point;
}

//////////////////////////////////////////////////////////////////
//     1Player mode　main　　　　　　　　　　　　　　　　　　   //
//////////////////////////////////////////////////////////////////
int Player1mode(int *ErrorCheck,int gamemode) {

	//色作成
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//赤
	Cr[1] = GetColor(15, 15, 255);//青
	Cr[2] = GetColor(255, 255, 15);//黄
	Cr[3] = GetColor(15, 255, 15);//緑
	Cr[4] = GetColor(255, 156, 0);//橙
	Cr[5] = GetColor(159, 15, 255);//紫
	Cr[6] = GetColor(218, 0, 224);//赤紫
	Cr[7] = GetColor(76, 255, 255);//空
	Cr[8] = GetColor(240, 240, 240);//白
	Cr[9] = GetColor(128, 128, 128);//灰

	/*ロード*/
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す
	DrawString(250, 250, "Now Lording...", Cr[8]);
	switch (gamemode){
	case 1:
		DrawString(50, 350, "得点", Cr[8]);
		DrawString(50, 380, "同じ色の敵を連続で倒すと得点が倍々になっていく.", Cr[8]);
		DrawString(50, 400, "最終コンボ数,残りHP,アイテム数もボーナス点の対象になるぞ.", Cr[8]);
		break;
	case 2:
		DrawString(50, 350, "ステージ", Cr[8]);
		DrawString(50, 380, "ステージは全部で11ステージ.", Cr[8]);
		DrawString(50, 400, "ステージ3,6,9,11はボス戦だ.", Cr[8]);
		break;
	case 3:
		DrawString(50, 350, "アイテム", Cr[8]);
		DrawString(50, 380, "5コンボごとにアイテムが1たまる.", Cr[8]);
		DrawString(50, 400, "3種のアイテムを使って有利に進めよう.", Cr[8]);
		DrawString(50, 420, "ちなみに,ゲーム開始時に1つ,ボスを倒しても1つたまる.", Cr[8]);
		break;
	case 4:
		DrawString(50, 350, "難易度", Cr[8]);
		DrawString(50, 380, "難易度は全部で4種類.", Cr[8]);
		DrawString(50, 400, "難しいほど敵の攻撃が激しくなるが,ボーナス点が加算される.", Cr[8]);
		break;
	case 11:
		DrawString(50, 350, "ボス Grad 特殊技:誘導弾", Cr[8]);
		DrawString(50, 380, "自機を追尾する赤い弾.", Cr[8]);
		DrawString(50, 400, "ひきつけてから左右どちらかに避けよう.", Cr[8]);
		break;
	case 12:
		DrawString(50, 350, "ボス Cron 特殊技:レーザー", Cr[8]);
		DrawString(50, 380, "直線状を貫く強力レーザー.", Cr[8]);
		DrawString(50, 400, "攻撃が早いので不自然に近づいてきたら逃げよう.", Cr[8]);
		break;
	case 13:
		DrawString(50, 350, "ボス Erec 特殊技:突進", Cr[8]);
		DrawString(50, 380, "自機に向かって機体ごと突っ込んでくる.", Cr[8]);
		DrawString(50, 400, "難易度が上がると速度も上がる.", Cr[8]);
		break;
	case 14:
		DrawString(50, 350, "制限時間", Cr[8]);
		DrawString(50, 380, "このゲームに制限時間はない.", Cr[8]);
		DrawString(50, 400, "時には敵の動きを見極めることも必要だ.", Cr[8]);
		break;
	case 20:
		DrawString(50, 350, "パズルモード", Cr[8]);
		DrawString(50, 380, "敵は攻撃してこないモード.", Cr[8]);
		DrawString(50, 400, "正確に狙って得点を稼げ!", Cr[8]);
		break;
	default:
		break;
	}
	ScreenFlip();

	bool SPflag = false, OneBossflag = false;//特殊なモードかどうか
	if (gamemode > 10) {//11～14,20
		SPflag = true;//特殊モード
		if (gamemode == 11) {
			gamemode = 1;//EASY
		}
		else if (gamemode == 12) {
			gamemode = 2;//NORMAL
		}
		else if (gamemode == 13) {
			gamemode = 3;//HARD
		}
		else if (gamemode == 14) {
			gamemode = 4;//UNKNOWN
		}
		else if (gamemode == 40) {
			gamemode = 4;
			OneBossflag = TRUE;
		}
	}

	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	Fps fps;
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG画像のメモリへの分割読み込み
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	
	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	
	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	
	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//再読み込み
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:スタート時 1:ステージクリア 2:全ステージクリア 3:ゲームオーバー 4:ゲーム終了 5:エラー
	int gameovercount = AFTERGAMEOVERCOUNT;//戻るまでの秒数(1/60 s)
	int stage = 0;//現在ステージ
	int gamecount = 1;//ゲーム内時間
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind = 0;//ステージの種類 1:ノーマルステージ 2:ボスステージ 3:ゲームクリア 4:その他 (0:エラー)
	unsigned int playerpoint = 0;//得点の合計値
	bool clearflag = false;//ステージクリア
	int ppx = 0, ppy = 0;//自機のx座標とy座標
	int NextHPdamage = 0;//HP引継ぎ用
	int itemnum = 1, itemtime = 0, command = 0;//アイテム個数,効果時間
	bool itemmenu = false, Key = false;//アイテムメニューを開いているか
	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/stage.mp3");
	//再読み込み
	if(SHandle==-1)SHandle = LoadSoundMem("./package/bgm/stage.mp3");

	int SHandle2 = LoadSoundMem("../exe/package/bgm/boss.mp3");
	//再読み込み
	if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/boss.mp3");

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//再読み込み
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//再読み込み
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	int SElaser = LoadSoundMem("../exe/package/bgm/laser.wav");
	//再読み込み
	if (SElaser == -1)SElaser = LoadSoundMem("./package/bgm/laser.wav");

	i = 0;
	do {
		if (stage != 0) {
			ClearDrawScreen(); // 画面を消す
			DrawString(250, 250, "Now Lording...", Cr[8]);
			ScreenFlip();
		}

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
		
		if (stage > 100)*ErrorCheck = 5;//明らかなエラー

		/*ステージ初めの処理*/
		ClearDrawScreen(); // 画面を消す
		stage++;//ステージ数を1増やす
		if (SPflag == true) {//特殊モード処理
			if (stage == 1 && gamemode==20) {//パズル 始め
				stage = 10;
			}
			else if (stage == 1) {//ボスラッシュ 始め
				stage = 3;//1
			}
			else if (stage == 11) {//パズル 終了
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//クリア画面
				return 0;//戻る
			}
			else if (stage == 4) {
				stage = 6;//2
			}
			else if (stage == 7) {
				stage = 9;//3
			}
			else if (stage == 10) {
				stage = 11;//4
			}
			else if (stage == 12) {//ボスラッシュ 終了(?)
				if (NextHPdamage < 16 && gamemode >= 3) {//HP半分以上かつHARD以上
					stage = 16;
					ClearDrawScreen(); // 画面を消す
					DrawString(250, 250, "Last One.", Cr[0]);
					ScreenFlip();
					WaitTimer(2000);// ここで2秒まつ
				}
				else {
					gamemode += 10;
					StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//クリア画面
					gamemode -= 10;
					return 0;//戻る
				}	
			}
			else if (stage == 17 && OneBossflag == false) {
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//クリア画面
				gamemode -= 10;
				return 0;//戻る
			}
			else {
				*ErrorCheck = -15;
			}

			if (OneBossflag == true) {
				if (stage == 16) {
					return 0;//戻る
				}
				SHandle2 = LoadSoundMem("../exe/package/bgm/lastboss.mp3");//ラスボス
		    	//再読み込み
				if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/lastboss.mp3");
				stage = 16;
			}
		}
		gamecount = 0;//経過時間を0にリセット
		gameovercount = AFTERGAMEOVERCOUNT;//終了までの時刻をリセット
		gameflag = 0;//ステージクリアしていない状態にする
		clearflag = false;
		Player.StartSet();//自機の初期化処理
		for (i = 0; i < MAXENEMY; i++) {
			NormalEnemy[i].StartSet(gamemode);
		}//敵機の初期化処理
		Boss[0].StartSet(0, gamemode);//ボスの初期化
		Boss[1].StartSet(0, gamemode);//ボスの初期化

		/*ステージ開始準備*/
		switch (stage){
		case 7://ノーマルステージ
			SHandle = LoadSoundMem("../exe/package/bgm/stage2.mp3");//曲替え
			//再読み込み
			if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/stage2.mp3");
		case 1:
		case 2:
		case 4:
		case 5:
		case 8:
		case 10:
			stagekind = 1;
			break;
		case 11://ボスステージ
			SHandle2 = LoadSoundMem("../exe/package/bgm/lastboss.mp3");//ラスボス
			//再読み込み
			if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/lastboss.mp3");
		case 3:
		case 6:
		case 9:
		case 16:
			stagekind = 2;
			break;
		case 12://全クリア
			stagekind = 3;
			gameflag = 2;
			break;
		default:
			*ErrorCheck = 3;
			break;
		}

		if (stagekind == 0) {//エラー
			*ErrorCheck = 3;
			return -1;
		}
		else if (stagekind == 1) {//ノーマルステージ
			NormalStage_StartPrepare(stage, ErrorCheck, NormalEnemy);//ノーマルステージ用準備
		}
		else if (stagekind == 2) {//ボスステージ
			Boss[0].StartSet(stage, gamemode);//ボスのセット
			if (stage == 11)Boss[1].StartSet(99, gamemode);//分身のセット
			else if (stage == 16)Boss[1].StartSet(100, gamemode);//パーツのセット
		}

		Player.PlayerHP(NextHPdamage);//前ステージで受けたダメージ分

		if (stagekind == 2) {
			PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//音楽
		}
		else {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		command = 50;
		Key = true;
		itemmenu = false;
		itemtime = 0;
		while(gameflag == 0) {
			/////**ステージ内処理**/////
			ClearDrawScreen(); // 画面を消す

			if (stagekind == 2) {
				if (CheckSoundMem(SHandle2) == 0) {
					PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//音楽
				}
			}
			else {
				if (CheckSoundMem(SHandle) == 0) {
					PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
				}
			}

			/*途中強制終了処理*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				Key = true;
				if (*ErrorCheck == 0) {//正常なことの確認
					*ErrorCheck = -999;
				}
				ESCGameEnd(ErrorCheck);//強制終了
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;//errorなら強制終了
			}

			if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
				*ErrorCheck = 1;
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;        // エラーが起きたらループを抜ける
			}


			if (itemmenu == false) {//アイテムメニューが開かれていれば処理停止
			/*ゲームオーバー処理*/
				if (Player.PlayerHP(0) == 0) {
					if (gameovercount == AFTERGAMEOVERCOUNT) {
						PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
					}
					else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
						DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//破壊
					}
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 3;
						break;
					}
				}
				if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0未満にはならない

				/*ステージクリア*/
				if (stagekind == 1) {//ノーマルステージ
					if (gameflag == 3) {//ゲームオーバーになるならクリアはしない
						clearflag = false;
					}
					else {
						clearflag = true;
					}
					for (i = 0; i < MAXENEMY; i++) {
						if (NormalEnemy[i].EnemyExistCheck() == true) {
							clearflag = false;
						}
					}
				}
				else if (stagekind == 2) {//ボスステージ
					if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//自分がゲームオーバーでなく、かつボスのHPが0でクリア
						clearflag = true;
					}
				}

				if (clearflag == true) {
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 1;
						if (stagekind == 2) {//ボスステージ
							itemnum += 1;
						}
						break;
					}
				}

				///////ステージメイン処理///////
				/*プレイヤー*/
				Player.PlayerMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot);

				/*敵機*/
				Player.PlayerPosition(&ppx, &ppy);
				if (stagekind == 1) {//ノーマルステージ
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}
				else if (stagekind == 2) {//ボスステージ
					if (stage == 11) {//分身の方が下
						Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak,SElaser);
						if (Boss[0].BossHP(0) < 25 && Boss[1].BossMoveSet(0, false) < 10 && gamemode >= 3)Boss[1].BossMoveSet(10, true);//RainのHPが30を切ると分身の行動変化
						if (Boss[0].BossHP(0) == 0)Boss[1].BossHP(99);//本体が消えれば分身も消える
					}
					Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, SElaser);
					if (stage == 16) {//パーツの方が上
						Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, SElaser);
						if (Boss[0].BossHP(0) == 0)Boss[1].BossHP(99);//本体が消えればパーツも消える
						BossStage_NormalEnemyAppear(ErrorCheck, NormalEnemy, Boss);
					}
					Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
					for (i = 0; i < 20; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}

			}

			/////**情報**/////
			DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[9], false);// 四角形を描画

			/*アイテム*/
			if (itemmenu == true) {//アイテム メニュー
				if (CheckHitKeyAll() == 0) {//キーが押されていない
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_X) == 1) {
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyGraphicDrawing(ErrorCheck, NormalEnemyGraphic);
					}
				}
				else {
					DrawBox(80, 50, 440, 345, Cr[1], false);// 四角形を描画
					if (command < 10) {

						if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {
							itemmenu = false;
							Key = true;
						}
						DrawString(100, 70, "アイテム メニュー", Cr[8]);
						if (itemnum == 0) {
							DrawString(120, 100, "色替え(ITEM:1)", Cr[9]);
							DrawString(120, 125, "ストップ(ITEM:2)", Cr[9]);
							DrawString(120, 150, "HP回復(ITEM:2)", Cr[9]);
						}
						else {
							DrawString(120, 100, "色替え(ITEM:1)", Cr[8]);
							if (itemtime > 0 || itemnum == 1) {
								DrawString(120, 125, "ストップ(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 125, "ストップ(ITEM:2)", Cr[8]);
							}
							if (Player.PlayerHP(0) == 30 || itemnum == 1) {
								DrawString(120, 150, "HP回復(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 150, "HP回復(ITEM:2)", Cr[8]);
							}
						}
						DrawString(120, 175, "メニューを閉じる", Cr[8]);
						DrawString(100, 270, "上下キーで選択、ENTERで決定", Cr[8]);
						DrawString(100, 290, "Xを押している間,敵を表示", Cr[8]);
					}
					else if (command < 40) {
						if (command < 20) {
							DrawString(100, 70, "色替え: Z ショット", Cr[8]);
						}
						else if (command < 30) {
							DrawString(100, 70, "色替え: X ショット", Cr[8]);
							DrawString(120, 260, "1つ戻る(Zショット)", Cr[8]);
						}
						else {
							DrawString(100, 70, "色替え: C ショット", Cr[8]);
							DrawString(120, 260, "1つ戻る(Xショット)", Cr[8]);
						}
						DrawString(120, 100, "赤", Cr[0]);
						DrawString(120, 120, "青", Cr[1]);
						DrawString(120, 140, "黄", Cr[2]);
						DrawString(120, 160, "緑", Cr[3]);
						DrawString(120, 180, "橙", Cr[4]);
						DrawString(120, 200, "紫", Cr[5]);
						DrawString(120, 220, "赤紫", Cr[6]);
						DrawString(120, 240, "空", Cr[7]);
						DrawString(100, 300, "上下キーで選択、ENTERで決定", Cr[8]);
						DrawString(100, 320, "Xを押している間,敵を表示", Cr[8]);
					}

					switch (command) {
					case 0:
						DrawCircle(100, 107, 5, Cr[6], true);
						DrawString(100, 215, "3つのショットの色を,\nコンボ数を保ったまま任意の色に変えます.", Cr[3]);
						break;
					case 1:
						DrawCircle(100, 132, 5, Cr[6], true);
						DrawString(100, 215, "敵の弾を消した上で,\n敵の動きを少しの間止めます.", Cr[3]);
						break;
					case 2:
						DrawCircle(100, 157, 5, Cr[6], true);
						DrawString(100, 215, "HPを10回復します(最大値:30).\nさらに,一瞬だけ無敵になります.", Cr[3]);
						break;
					case 3:
						DrawCircle(100, 182, 5, Cr[6], true);
						if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {
							DrawString(100, 215, "アイテムはボス戦では入手できませんが、\n持っていれば使うことはできます", Cr[2]);
						}
						else {
							DrawString(100, 215, "アイテムは5コンボごとに1増えます.\n表示分だけ消費して使用可能です.", Cr[2]);
						}
						break;
					case 10:
					case 20:
					case 30:
						DrawCircle(100, 107, 5, Cr[0], true);
						break;
					case 11:
					case 21:
					case 31:
						DrawCircle(100, 127, 5, Cr[1], true);
						break;
					case 12:
					case 22:
					case 32:
						DrawCircle(100, 147, 5, Cr[2], true);
						break;
					case 13:
					case 23:
					case 33:
						DrawCircle(100, 167, 5, Cr[3], true);
						break;
					case 14:
					case 24:
					case 34:
						DrawCircle(100, 187, 5, Cr[4], true);
						break;
					case 15:
					case 25:
					case 35:
						DrawCircle(100, 207, 5, Cr[5], true);
						break;
					case 16:
					case 26:
					case 36:
						DrawCircle(100, 227, 5, Cr[6], true);
						break;
					case 17:
					case 27:
					case 37:
						DrawCircle(100, 247, 5, Cr[7], true);
						break;
					case 28:
					case 38:
						DrawCircle(100, 267, 5, Cr[8], true);
						break;
					case 50:
						break;
					default:
						*ErrorCheck = 11;
						break;
					}

					if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == false) {
						if (command == 0) {//色替え
							if (itemnum > 0) {
								itemnum -= 1;
								command = 10;
							}
						}
						else if (command == 1) {//ストップ
							if (itemnum > 1 && itemtime <= 0) {
								itemnum -= 2;
								if (stagekind == 1) {//ノーマルステージ
									itemtime = 300;
								}
								else if (stagekind == 2) {//ボスステージ
									itemtime = 180;
								}
								for (i = 0; i < MAXENEMY; i++) {
									NormalEnemy[i].EnemyShotFlagFALSE();//弾を消す
								}
								for (i = 0; i < 2; i++) {
									for (int j = 0; j < 10; j++) {
										Boss[i].BossShotFlagFALSE(j);//弾を消す
									}
								}
								itemmenu = false;
							}
						}
						else if (command == 2) {//HP回復
							if (Player.PlayerHP(0) != 30 && itemnum > 1) {
								itemnum -= 2;
								Player.PlayerHP(-10);
								itemmenu = false;
							}
						}
						else if (command == 3) {
							itemmenu = false;
						}
						else if (10 <= command && command <= 17) {//Z
							Player.ColorSet(0, command - 10);
							command = 20;
						}
						else if (20 <= command && command <= 27) {//X
							Player.ColorSet(1, command - 20);
							command = 30;
						}
						else if (command == 28) {//戻る
							command = 10;
						}
						else if (30 <= command && command <= 37) {//C
							Player.ColorSet(2, command - 30);
							command = 50;//どのコマンドでもない
							itemmenu = false;
						}
						else if (command == 38) {//戻る
							command = 20;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W) == 1) && Key == false) {
						if (command == 0) {
							command = 3;
						}
						else if (command == 10) {
							command = 17;
						}
						else if (command == 20) {
							command = 28;
						}
						else if (command == 30) {
							command = 38;
						}
						else {
							command--;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S) == 1) && Key == false) {
						if (command == 3) {
							command = 0;
						}
						else if (command == 17) {
							command = 10;
						}
						else if (command == 28) {
							command = 20;
						}
						else if (command == 38) {
							command = 30;
						}
						else {
							command++;
						}
						Key = true;
					}
				}
			}			
			/*アイテムここまで*/

			Player.PlayerShotColor(PlayerShotKind);
			Player.PlayerShotCombo(ShotCombonum);

			DrawString(515, 210, "現在の弾の種類", Cr[9]);
			DrawString(515, 250, "Zショット:\n\n\nXショット:\n\n\nCショット:", Cr[8]);
			for (i = 0; i < 3; i++) {
				DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "コンボ:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(605, 250 + i * 54, "赤", Cr[0]);
					break;
				case 1:
					DrawString(605, 250 + i * 54, "青", Cr[1]);
					break;
				case 2:
					DrawString(605, 250 + i * 54, "黄", Cr[2]);
					break;
				case 3:
					DrawString(605, 250 + i * 54, "緑", Cr[3]);
					break;
				case 4:
					DrawString(605, 250 + i * 54, "橙", Cr[4]);
					break;
				case 5:
					DrawString(605, 250 + i * 54, "紫", Cr[5]);
					break;
				case 6:
					DrawString(605, 250 + i * 54, "赤紫", Cr[6]);
					break;
				case 7:
					DrawString(605, 250 + i * 54, "空", Cr[7]);
					break;
				default:
					DrawString(605, 250 + i * 54, "無", Cr[9]);
					break;
				}
			}

			if (SPflag == true) {//特殊モード
				DrawString(0, 420, "LEFTキー:左 RIGHTキー:右 Z,X,C:ショット", Cr[9]);
			}
			else {//通常
				DrawString(0, 420, "LEFTキー:左 RIGHTキー:右 Z,X,C:ショット SPACE:アイテム", Cr[9]);
				if (stage == 11) {
					DrawFormatString(515, 30, Cr[8], "Stage:LAST");
				}
				else {
					DrawFormatString(515, 30, Cr[8], "Stage:%d", stage);
				}
				if (itemnum == 0) {
					DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
				}
				else {
					DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
				}
			}

			if (Player.PlayerHP(0) > 15) {
				DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HPを描画
			}
			else if (Player.PlayerHP(0) > 7) {
				DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HPを描画
			}
			else {
				DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HPを描画
			}

			DrawString(0, 440, "ESCAPE:ゲーム強制終了", Cr[9]);
			DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

			if (gamemode == 1) {//EASY
				DrawString(530, 60, "EASY", Cr[8]);
			}
			else if (gamemode == 2) {//NORMAL
				DrawString(530, 60, "NORMAL", Cr[8]);
			}
			else if (gamemode == 3) {//HARD
				DrawString(530, 60, "HARD", Cr[8]);
			}
			else if (gamemode == 4) {//UNKNOWN
				DrawString(530, 60, "UNKNOWN", Cr[8]);
			}

			/*その他の処理*/
			/*Player.DebagColorSet();//デバッグ用
			if (CheckHitKey(KEY_INPUT_P) == 1) {
				gameflag = 1;
			}
			/**/

			if (itemmenu == false) {//アイテムメニューが開かれていないとき
				gamecount++;//時間経過
				if (itemtime > -1)itemtime--;
				if (CheckHitKey(KEY_INPUT_SPACE) == 0) {
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false && SPflag == false) {//アイテムメニュー
					itemmenu = true;
					command = 3;
					Key = true;
				}
			}
			if (gamecount > 100000000)gamecount = 0;//バグの防止
			if (gamecount > 150000000)*ErrorCheck = 4;//時間経過しすぎ
			fps.Update();	//更新
			fps.Wait();		//待機
			//fps.Draw();		//描画
			ScreenFlip();

		}//クリアするまで

		ClearDrawScreen(); // 画面を消す
		if (gameflag == 1 && stage >= 11) {//最終ステージクリア
			gameflag = 2;
			if (stage == 11 && SPflag == TRUE && gamemode >= 3 && NextHPdamage < 16) {
				gameflag = 1;
			}
		}
		// 再生を止めます
		StopSoundMem(SHandle);
		StopSoundMem(SHandle2);

		if (SPflag == false) {
			playerpoint = StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);//ステージクリア画面
		}
		else {
			if (OneBossflag == true) {
				return 0;//戻る
			}

			if (gameflag == 3) {//ボスラッシュのゲームオーバー
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);
				gamemode -= 10;
			}
			else if (gameflag == 2) {//ボスラッシュのクリア
				gamemode += 10;
				StageClear(ErrorCheck, stage, playerpoint, Player, gameflag, gamecount, gamemode, itemnum);
				gamemode -= 10;
			}
		}


		if (SPflag == false) {
			if (*ErrorCheck == -2) {//途中終了の場合
				*ErrorCheck = 0;//正常に戻す
				gameflag = 3;//ゲームオーバーにする
				stage += 1;
			}
			if (gameflag == 2 || gameflag == 3) {//クリアかゲームオーバー(得点表を呼ぶ)
				if (gameflag == 2)stage = 12;
				RankingFileCheck(ErrorCheck, playerpoint, gamemode, stage);
				break;
			}
		}

		ScreenFlip();

		if (SPflag == true) {//ボスラッシュ
			NextHPdamage = 30 - Player.PlayerHP(0);//回復なし
			if (Player.PlayerHP(0) == 0) {//0のときのみ
				NextHPdamage = 29;
			}
		}
		else if (gamemode == 1) {//EASY
			NextHPdamage = 0;//ステージクリアごとに全回復
		}
		else if (gamemode == 2) {//NORMAL
			NextHPdamage = 25 - Player.PlayerHP(0);//ステージクリアごとに5回復
			if (NextHPdamage < 0)NextHPdamage = 0;
		}
		else if (gamemode == 3 || gamemode == 4) {//HARD || UNKNOWN
			NextHPdamage = 30 - Player.PlayerHP(0);//回復なし
			if (Player.PlayerHP(0) == 0) {//0のときのみ
				NextHPdamage = 29;
			}
		}
		
	} while (gameflag <= 1);//ゲームが終了しない限り

	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);
	DeleteSoundMem(SHandle2);

	return 0;
}


//////////////////////////////////
/////---**チュートリアル**---/////
/////////////////////////////////

/*チュートリアル用ステージスタート時の敵配置*/
void Tutoreal_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	/*ステージ1*/
	if (stage == 1) {
		Enemy[0].AppearEnemy(90, 10, 0);
		Enemy[1].AppearEnemy(130, 10, 0);
		Enemy[2].AppearEnemy(170, 10, 0);
		Enemy[3].AppearEnemy(210, 10, 2);
		Enemy[4].AppearEnemy(250, 10, 3);
		Enemy[5].AppearEnemy(290, 10, 2);
		Enemy[6].AppearEnemy(330, 10, 1);
		Enemy[7].AppearEnemy(370, 10, 2);
		Enemy[8].AppearEnemy(90, 50, 0);
		Enemy[9].AppearEnemy(130, 50, 0);
		Enemy[10].AppearEnemy(170, 50, 1);
		Enemy[11].AppearEnemy(210, 50, 3);
		Enemy[12].AppearEnemy(250, 50, 2);
		Enemy[13].AppearEnemy(290, 50, 3);
		Enemy[14].AppearEnemy(330, 50, 1);
		Enemy[15].AppearEnemy(370, 50, 2);
		for (int i = 16; i < 24; i++) {
			Enemy[i].AppearEnemy(90 + (i - 16) * 40, 80, 11);
		}
	}

	/*ステージ2*/
	if (stage == 2) {
		Enemy[0].AppearEnemy(50, 10, 0);
		Enemy[1].AppearEnemy(90, 10, 0);
		Enemy[2].AppearEnemy(130, 10, 1);
		Enemy[3].AppearEnemy(170, 10, 2);
		Enemy[4].AppearEnemy(210, 10, 0);
		Enemy[5].AppearEnemy(250, 10, 0);
		Enemy[6].AppearEnemy(290, 10, 3);
		Enemy[7].AppearEnemy(330, 10, 3);
		Enemy[8].AppearEnemy(370, 10, 4);
		Enemy[9].AppearEnemy(410, 10, 4);
		Enemy[10].AppearEnemy(50, 50, 1);
		Enemy[11].AppearEnemy(90, 50, 1);
		Enemy[12].AppearEnemy(130, 50, 0);
		Enemy[13].AppearEnemy(170, 50, 2);
		Enemy[14].AppearEnemy(210, 50, 2);
		Enemy[15].AppearEnemy(250, 50, 2);
		Enemy[16].AppearEnemy(290, 50, 3);
		Enemy[17].AppearEnemy(330, 50, 3);
		Enemy[18].AppearEnemy(370, 50, 5);
		Enemy[19].AppearEnemy(410, 50, 5);
		for (int i = 20; i < 30; i++) {
			Enemy[i].AppearEnemy(50 + (i - 20) * 40, 80, 11);
		}
	}
}

/*チュートリアルのメイン*/
int Tutoreal(int *ErrorCheck) {
	//色作成
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//赤
	Cr[1] = GetColor(15, 15, 255);//青
	Cr[2] = GetColor(255, 255, 15);//黄
	Cr[3] = GetColor(15, 255, 15);//緑
	Cr[4] = GetColor(255, 156, 0);//橙
	Cr[5] = GetColor(159, 15, 255);//紫
	Cr[6] = GetColor(218, 0, 224);//赤紫
	Cr[7] = GetColor(76, 255, 255);//空
	Cr[8] = GetColor(240, 240, 240);//白
	Cr[9] = GetColor(128, 128, 128);//灰

	/*ロード*/
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す
	DrawString(250, 250, "Now Lording...", Cr[8]);
	ScreenFlip();

	int gamemode = 1;//EASY
	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG画像のメモリへの分割読み込み
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);

	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//再読み込み
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:スタート時 1:ステージクリア 2:全ステージクリア 3:ゲームオーバー 4:ゲーム終了 5:エラー
	int gameovercount = 300;//戻るまでの秒数(1/60 s)
	int stage = 0;//現在ステージ
	int gamecount = 1;//ゲーム内時間
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	unsigned int playerpoint = 0;//得点の合計値
	bool clearflag = false;//ステージクリア
	int ppx = 0, ppy = 0;//自機のx座標とy座標
	int itemnum = 0, itemtime = 0, command = 0;//アイテム個数,効果時間
	bool itemmenu = false, Key = false;//アイテムメニューを開いているか
	int Tutorealcount = 120, TutorealNo = 1;//チュートリアル用変数
	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/stage.mp3");
	//再読み込み
	if (SHandle == -1)SHandle = LoadSoundMem("./package/bgm/stage.mp3");

	int SHandle2 = LoadSoundMem("../exe/package/bgm/boss.mp3");
	//再読み込み
	if (SHandle2 == -1)SHandle2 = LoadSoundMem("./package/bgm/boss.mp3");

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//再読み込み
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//再読み込み
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	i = 0;
	do {
		ClearDrawScreen(); // 画面を消す
		DrawString(250, 250, "Now Lording...", Cr[8]);
		ScreenFlip();

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

		if (stage > 100)*ErrorCheck = 5;//明らかなエラー

		/*ステージ初めの処理*/
		ClearDrawScreen(); // 画面を消す
		stage++;//ステージ数を1増やす
		gamecount = 0;//経過時間を0にリセット
		gameovercount = AFTERGAMEOVERCOUNT;//終了までの時刻をリセット
		gameflag = 0;//ステージクリアしていない状態にする
		clearflag = false;
		Player.StartSet();//自機の初期化処理
		for (i = 0; i < MAXENEMY; i++) {
			NormalEnemy[i].StartSet(gamemode);
		}//敵機の初期化処理
		Boss[0].StartSet(0, gamemode);//ボスの初期化
		Boss[1].StartSet(0, gamemode);//ボスの初期化

		/*チュートリアル終了処理*/
		if (stage >= 4) {
			break;//終了
		}

		/*ステージ開始準備*/
		if (stage != 3) {//ノーマルステージ
			Tutoreal_StartPrepare(stage, ErrorCheck, NormalEnemy);//ノーマルステージ用準備
		}
		else if (stage == 3) {//ボスステージ
			Boss[0].StartSet(stage, gamemode);//ボスのセット
		}

		if (stage == 3) {
			PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//音楽
		}
		else {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		command = 50;
		Key = true;
		itemmenu = false;
		itemtime = 0;
		if (stage == 1) {
			Tutorealcount = 120;
			TutorealNo = 1;
			itemnum = 0;
		}
		else if (stage == 2) {
			Tutorealcount = 120;
			TutorealNo = 11;
			itemnum = 0;
		}
		else if (stage == 3) {
			Tutorealcount = 120;
			TutorealNo = 21;
		}

		while (gameflag == 0) {
			/////**ステージ内処理**/////
			ClearDrawScreen(); // 画面を消す

			if (stage == 3) {
				if (CheckSoundMem(SHandle2) == 0) {
					PlaySoundMem(SHandle2, DX_PLAYTYPE_BACK);//音楽
				}
			}
			else {
				if (CheckSoundMem(SHandle) == 0) {
					PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
				}
			}

			/*途中強制終了処理*/
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
				Key = true;
				if (*ErrorCheck == 0) {//正常なことの確認
					*ErrorCheck = -999;
				}
				ESCGameEnd(ErrorCheck);//強制終了
			}

			if (*ErrorCheck > 0 || *ErrorCheck == -1) {
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;//errorなら強制終了
			}

			if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
				*ErrorCheck = 1;
				// サウンドハンドルの削除
				DeleteSoundMem(SHandle);
				DeleteSoundMem(SHandle2);
				return -1;        // エラーが起きたらループを抜ける
			}


			if (itemmenu == false) {//アイテムメニューが開かれていれば処理停止
			/*ゲームオーバー処理*/
				if (Player.PlayerHP(0) == 0) {
					if (gameovercount == AFTERGAMEOVERCOUNT) {
						PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
					}
					else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
						DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//破壊
					}
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 3;
						break;
					}
				}
				if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0未満にはならない

				/*ステージクリア*/
				if (stage != 3) {//ノーマルステージ
					if (gameflag == 3) {//ゲームオーバーになるならクリアはしない
						clearflag = false;
					}
					else {
						clearflag = true;
					}
					for (i = 0; i < MAXENEMY; i++) {
						if (NormalEnemy[i].EnemyExistCheck() == true) {
							clearflag = false;
						}
					}
				}
				else if (stage == 3) {//ボスステージ
					if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//自分がゲームオーバーでなく、かつボスのHPが0でクリア
						clearflag = true;
					}
				}

				if (clearflag == true) {
					gameovercount--;
					if (gameovercount <= 0) {
						gameflag = 1;
						break;
					}
				}

				///////ステージメイン処理///////
				/*チュートリアル 説明*/
				DrawBox(40, 110, 460, 350, Cr[9], false);// 四角形を描画

				switch (TutorealNo){
					/*stage1*/
				case 1:
					DrawString(50, 120, "チュートリアルへようこそ!", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 180;
						TutorealNo = 2;
					}
					break;
				case 2:
					DrawString(50, 120, "このゲームは,敵からの攻撃を避けつつ", Cr[8]);
					DrawString(50, 140, "敵を倒して得点を稼ぐのが目的です.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 3;
					}
					break;
				case 3:
					DrawString(50, 120, "まずは,基本的な動作説明です.", Cr[8]);
					DrawString(50, 140, "右キーで右に,左キーで左に動きます.", Cr[8]);
					DrawString(50, 160, "プレイヤーは,左右にしか動くことはできません.", Cr[8]);
					DrawString(50, 180, "敵が弾を撃ってくるので,動いて避けましょう.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 720;
						TutorealNo = 4;
					}
					break;
				case 4:
					DrawString(50, 120, "次に,ショットについてです.", Cr[8]);
					DrawString(50, 140, "ショットは,Z,X,Cで撃つことができます.", Cr[8]);
					DrawString(50, 160, "これらのショットは全て", Cr[8]);
					DrawString(50, 180, "独立した弾になっています.", Cr[8]);
					DrawString(50, 200, "1つのショットにつき,画面上には最大3発まで", Cr[8]);
					DrawString(50, 220, "撃つことができます.", Cr[8]);
					DrawString(50, 240, "以後,Z,X,Cキーによるショットをそれぞれ", Cr[8]);
					DrawString(50, 260, "Zショット,Xショット,Cショットと呼びます.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 480;
						TutorealNo = 5;
					}
					break;
				case 5:
					DrawString(50, 120, "各ショットには,直前に倒した(攻撃した)敵により", Cr[8]);
					DrawString(50, 140, "それぞれ色が保存されます.", Cr[8]);
					DrawString(50, 160, "例えば,Zショットで赤の敵を倒せば,", Cr[8]);
					DrawString(50, 180, "Zショットに赤が保存されます.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 720;
						TutorealNo = 6;
						NormalEnemy[16].BreakEnemy();
						NormalEnemy[17].BreakEnemy();
					}
					break;
				case 6:
					DrawString(50, 120, "では,実際に左側の4体の赤の敵を", Cr[8]);
					DrawString(50, 140, "Zショットで倒してみましょう.", Cr[8]);
					DrawString(50, 160, "すると,画面右側のZショットの欄に", Cr[8]);
					DrawString(50, 180, "Zショット:赤 4コンボ と表示されるはずです.", Cr[8]);
					DrawString(50, 200, "これはすなわち,Zショットで赤の敵を", Cr[8]);
					DrawString(50, 220, "連続で4体倒したことを意味します.", Cr[8]);
					if (NormalEnemy[0].EnemyExistCheck() == false && NormalEnemy[1].EnemyExistCheck() == false) {
						TutorealNo = 7;
						NormalEnemy[18].BreakEnemy();
					}
					break;
				case 7:
					DrawString(50, 120, "次に,左側の青と赤の敵を倒してみましょう.", Cr[8]);
					DrawString(50, 140, "Xショットで青の敵を倒してからZショットで", Cr[8]);
					DrawString(50, 160, "赤の敵を倒せば,Zショットのコンボを", Cr[8]);
					DrawString(50, 180, "続けることができます.", Cr[8]);
					if (NormalEnemy[2].EnemyExistCheck() == false) {
						TutorealNo = 8;
					}
					break;
				case 8:
					DrawString(50, 120, "ここまで,指示通りの行動をしていれば,", Cr[8]);
					DrawString(50, 140, "画面右側には Zショット:赤 5コンボ,", Cr[8]);
					DrawString(50, 160, "Xショット:青 1コンボとなっているはずです.", Cr[8]);
					DrawString(50, 180, "しかし,例えばZショット:赤:4コンボの状態で", Cr[8]);
					DrawString(50, 200, "Zショットで青の敵を倒してしまうと,", Cr[8]);
					DrawString(50, 220, "Zショットは青の1コンボになってしまい,", Cr[8]);
					DrawString(50, 240, "そこからZショットで赤の敵を倒しても,", Cr[8]);
					DrawString(50, 260, "Zショット:赤:1コンボとなってしまいます.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 9;
						for (i = 19; i < 24; i++) {
							NormalEnemy[i].BreakEnemy();
						}
					}
					break;
				case 9:
					DrawString(50, 120, "では,うまくコンボを稼ぎつつ,", Cr[8]);
					DrawString(50, 140, "敵を全滅させてください.", Cr[8]);
					DrawString(50, 160, "1コンボで1点,2コンボで2点,3コンボで4点...", Cr[8]);
					DrawString(50, 180, "というように,得点はコンボ数に応じて倍々に", Cr[8]);
					DrawString(50, 200, "増えていきます.", Cr[8]);
					DrawString(50, 220, "弾の種類が3種類に対し,敵は4種類います.", Cr[8]);
					DrawString(50, 240, "本編では最終コンボ数がボーナス点となるので,", Cr[8]);
					DrawString(50, 260, "コンボが少ないショットのコンボを切り,4種類目を", Cr[8]);
					DrawString(50, 280, "倒すとよいでしょう.", Cr[8]);
					break;
					/*stage2*/
				case 11:
					DrawString(60, 120, "ここでは,アイテムについて説明します.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 12;
					}
					break;
				case 12:
					DrawString(50, 120, "itemは最初に1つ持っています.", Cr[8]);
					DrawString(50, 140, "(現在はチュートリアルなので持っていません.)", Cr[8]);
					DrawString(50, 160, "また,ノーマルステージでは,", Cr[8]);
					DrawString(50, 180, "5コンボごとに1つ,", Cr[8]);
					DrawString(50, 200, "ボスステージでは,ボスを倒すと1つ", Cr[8]);
					DrawString(50, 220, "itemの量が増えます.", Cr[8]);
					DrawString(50, 240, "itemの個数は,", Cr[8]);
					DrawString(50, 260, "画面右下でいつでも確認できます.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 13;
					}
					break;
				case 13:
					DrawString(50, 120, "アイテムは3種類あり,所持itemを消費して", Cr[8]);
					DrawString(50, 140, "使うことができます.", Cr[8]);
					DrawString(50, 160, "1.色替え", Cr[8]);
					DrawString(50, 180, "itemを1消費して,Z,X,C全てのショットに", Cr[8]);
					DrawString(50, 200, "保存されている色を,それぞれ任意に", Cr[8]);
					DrawString(50, 220, "変えることができます.", Cr[8]);
					DrawString(50, 240, "色を変えてもコンボは途切れないので,", Cr[8]);
					DrawString(50, 260, "例えば赤4コンボの後に青に変えて,青の敵を倒せば", Cr[8]);
					DrawString(50, 280, "青の5コンボとして扱われます.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 600;
						TutorealNo = 14;
					}
					break;
				case 14:
					DrawString(50, 120, "2.ストップ", Cr[8]);
					DrawString(50, 140, "itemを2消費して,しばらく敵の動きを止めたうえで,", Cr[8]);
					DrawString(50, 160, "飛んでいる弾もすべて消します.", Cr[8]);
					DrawString(50, 180, "敵の弾が多いときなどに有効でしょう.", Cr[8]);
					DrawString(50, 220, "3.HP回復", Cr[8]);
					DrawString(50, 240, "itemを2消費して,HPを10回復します.", Cr[8]);
					DrawString(50, 260, "最大HPは30なので,それ以上は回復しません.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 420;
						TutorealNo = 15;
					}
					break;
				case 15:
					DrawString(50, 120, "これらのアイテムは,全てSPACEキーで開く", Cr[8]);
					DrawString(50, 140, "アイテムメニューから使うことができます.", Cr[8]);
					DrawString(50, 160, "説明もそこで見ることが可能です.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 16;
						for (i = 20; i < 30; i++) {
							NormalEnemy[i].BreakEnemy();
						}
						itemnum = 3;
					}
					break;
				case 16:
					DrawString(50, 120, "では,itemを3つ渡しますので,", Cr[8]);
					DrawString(50, 140, "色替えを使い,全てZショットで倒して", Cr[8]);
					DrawString(50, 160, "20コンボを狙ってみましょう", Cr[8]);
					DrawString(50, 180, "(もちろん狙わなくても構いません)", Cr[8]);
					DrawString(50, 200, "敵を全滅させれば,次のステージに進みます.", Cr[8]);
					break;
					/*stage3*/
				case 21:
					DrawString(50, 120, "stage3,6,9,11では,ボス戦があります.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						Tutorealcount = 240;
						TutorealNo = 22;
					}
					break;
				case 22:
					DrawString(50, 120, "ボスはHPを持っていて,0にすることで", Cr[8]);
					DrawString(50, 140, "倒すことができます", Cr[8]);
					DrawString(50, 160, "倒せばステージクリアです.", Cr[8]);
					DrawString(50, 180, "ボスのHPは,上部に表示されています.", Cr[8]);
					Tutorealcount--;
					if (Tutorealcount < 0) {
						TutorealNo = 23;
					}
					break;
				case 23:
					DrawString(50, 120, "ボスにも色が設定されており,", Cr[8]);
					DrawString(50, 140, "時間経過で変わります.", Cr[8]);
					DrawString(50, 160, "現在のボスの色は,HPバーと同じです.", Cr[8]);
					DrawString(50, 180, "ボスの得点は,ダメージを与えるたびに", Cr[8]);
					DrawString(50, 200, "3+(コンボ数)点,", Cr[8]);
					DrawString(50, 220, "倒すとEASY:100,NORMAL:200,HARD:300点が", Cr[8]);
					DrawString(50, 240, "加算されます.", Cr[8]);
					DrawString(50, 260, "このボスを倒せば,チュートリアル終了です!", Cr[8]);
				default:
					break;
				}


				/*プレイヤー*/
				Player.PlayerMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot);

				/*敵機*/
				Player.PlayerPosition(&ppx, &ppy);
				if (stage != 3) {//ノーマルステージ
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, 0, itemtime);
					}
					Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
				}
				else if (stage == 3) {//ボスステージ
					Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, itemtime, SEbreak, 0);
					Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
				}

			}

			/////**情報**/////
			DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[8], false);// 四角形を描画

			/*アイテム*/
			if (itemmenu == true) {//アイテム メニュー
				if (CheckHitKeyAll() == 0) {//キーが押されていない
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_X) == 1) {
					for (i = 0; i < MAXENEMY; i++) {
						NormalEnemy[i].NormalEnemyGraphicDrawing(ErrorCheck, NormalEnemyGraphic);
					}
				}
				else {
					DrawBox(80, 50, 440, 345, Cr[1], false);// 四角形を描画
					if (command < 10) {

						if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {
							itemmenu = false;
							Key = true;
						}
						DrawString(100, 70, "アイテム メニュー", Cr[8]);
						if (itemnum == 0) {
							DrawString(120, 100, "色替え(ITEM:1)", Cr[9]);
							DrawString(120, 125, "ストップ(ITEM:2)", Cr[9]);
							DrawString(120, 150, "HP回復(ITEM:2)", Cr[9]);
						}
						else {
							DrawString(120, 100, "色替え(ITEM:1)", Cr[8]);
							if (itemtime > 0 || itemnum == 1) {
								DrawString(120, 125, "ストップ(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 125, "ストップ(ITEM:2)", Cr[8]);
							}
							if (Player.PlayerHP(0) == 30 || itemnum == 1) {
								DrawString(120, 150, "HP回復(ITEM:2)", Cr[9]);
							}
							else {
								DrawString(120, 150, "HP回復(ITEM:2)", Cr[8]);
							}
						}
						DrawString(120, 175, "メニューを閉じる", Cr[8]);
						DrawString(100, 270, "上下キーで選択、ENTERで決定", Cr[8]);
						DrawString(100, 290, "Xを押している間,敵を表示", Cr[8]);
					}
					else if (command < 40) {
						if (command < 20) {
							DrawString(100, 70, "色替え: Z ショット", Cr[8]);
						}
						else if (command < 30) {
							DrawString(100, 70, "色替え: X ショット", Cr[8]);
							DrawString(120, 260, "1つ戻る(Zショット)", Cr[8]);
						}
						else {
							DrawString(100, 70, "色替え: C ショット", Cr[8]);
							DrawString(120, 260, "1つ戻る(Xショット)", Cr[8]);
						}
						DrawString(120, 100, "赤", Cr[0]);
						DrawString(120, 120, "青", Cr[1]);
						DrawString(120, 140, "黄", Cr[2]);
						DrawString(120, 160, "緑", Cr[3]);
						DrawString(120, 180, "橙", Cr[4]);
						DrawString(120, 200, "紫", Cr[5]);
						DrawString(120, 220, "赤紫", Cr[6]);
						DrawString(120, 240, "空", Cr[7]);
						DrawString(100, 300, "上下キーで選択、ENTERで決定", Cr[8]);
						DrawString(100, 320, "Xを押している間,敵を表示", Cr[8]);
					}

					switch (command) {
					case 0:
						DrawCircle(100, 107, 5, Cr[6], true);
						DrawString(100, 215, "3つのショットの色を,\nコンボ数を保ったまま任意の色に変えます.", Cr[3]);
						break;
					case 1:
						DrawCircle(100, 132, 5, Cr[6], true);
						DrawString(100, 215, "敵の弾を消した上で,\n敵の動きを少しの間止めます.", Cr[3]);
						break;
					case 2:
						DrawCircle(100, 157, 5, Cr[6], true);
						DrawString(100, 215, "HPを10回復します(最大値:30).\nさらに,一瞬だけ無敵になります.", Cr[3]);
						break;
					case 3:
						DrawCircle(100, 182, 5, Cr[6], true);
						if (stage == 3 || stage == 6 || stage == 9 || stage == 11) {
							DrawString(100, 215, "アイテムはボス戦では入手できませんが、\n持っていれば使うことはできます", Cr[2]);
						}
						else {
							DrawString(100, 215, "アイテムは5コンボごとに1増えます.\n表示分だけ消費して使用可能です.", Cr[2]);
						}
						break;
					case 10:
					case 20:
					case 30:
						DrawCircle(100, 107, 5, Cr[0], true);
						break;
					case 11:
					case 21:
					case 31:
						DrawCircle(100, 127, 5, Cr[1], true);
						break;
					case 12:
					case 22:
					case 32:
						DrawCircle(100, 147, 5, Cr[2], true);
						break;
					case 13:
					case 23:
					case 33:
						DrawCircle(100, 167, 5, Cr[3], true);
						break;
					case 14:
					case 24:
					case 34:
						DrawCircle(100, 187, 5, Cr[4], true);
						break;
					case 15:
					case 25:
					case 35:
						DrawCircle(100, 207, 5, Cr[5], true);
						break;
					case 16:
					case 26:
					case 36:
						DrawCircle(100, 227, 5, Cr[6], true);
						break;
					case 17:
					case 27:
					case 37:
						DrawCircle(100, 247, 5, Cr[7], true);
						break;
					case 28:
					case 38:
						DrawCircle(100, 267, 5, Cr[8], true);
						break;
					case 50:
						break;
					default:
						*ErrorCheck = 11;
						break;
					}

					if (CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == false) {
						if (command == 0) {//色替え
							if (itemnum > 0) {
								itemnum -= 1;
								command = 10;
							}
						}
						else if (command == 1) {//ストップ
							if (itemnum > 1 && itemtime <= 0) {
								itemnum -= 2;
								itemtime = 240;
								for (i = 0; i < MAXENEMY; i++) {
									NormalEnemy[i].EnemyShotFlagFALSE();//弾を消す
								}
								for (i = 0; i < 2; i++) {
									for (int j = 0; j < 10; j++) {
										Boss[i].BossShotFlagFALSE(j);//弾を消す
									}
								}
								itemmenu = false;
							}
						}
						else if (command == 2) {//HP回復
							if (Player.PlayerHP(0) != 30 && itemnum > 1) {
								itemnum -= 2;
								Player.PlayerHP(-10);
								itemmenu = false;
							}
						}
						else if (command == 3) {
							itemmenu = false;
						}
						else if (10 <= command && command <= 17) {//Z
							Player.ColorSet(0, command - 10);
							command = 20;
						}
						else if (20 <= command && command <= 27) {//X
							Player.ColorSet(1, command - 20);
							command = 30;
						}
						else if (command == 28) {//戻る
							command = 10;
						}
						else if (30 <= command && command <= 37) {//C
							Player.ColorSet(2, command - 30);
							command = 50;//どのコマンドでもない
							itemmenu = false;
						}
						else if (command == 38) {//戻る
							command = 20;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_W) == 1) && Key == false) {
						if (command == 0) {
							command = 3;
						}
						else if (command == 10) {
							command = 17;
						}
						else if (command == 20) {
							command = 28;
						}
						else if (command == 30) {
							command = 38;
						}
						else {
							command--;
						}
						Key = true;
					}
					else if ((CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_S) == 1) && Key == false) {
						if (command == 3) {
							command = 0;
						}
						else if (command == 17) {
							command = 10;
						}
						else if (command == 28) {
							command = 20;
						}
						else if (command == 38) {
							command = 30;
						}
						else {
							command++;
						}
						Key = true;
					}
				}
			}
			/*アイテムここまで*/

			Player.PlayerShotColor(PlayerShotKind);
			Player.PlayerShotCombo(ShotCombonum);

			DrawString(515, 210, "現在の弾の種類", Cr[9]);
			DrawString(515, 250, "Zショット:\n\n\nXショット:\n\n\nCショット:", Cr[8]);
			for (i = 0; i < 3; i++) {
				DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "コンボ:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(605, 250 + i * 54, "赤", Cr[0]);
					break;
				case 1:
					DrawString(605, 250 + i * 54, "青", Cr[1]);
					break;
				case 2:
					DrawString(605, 250 + i * 54, "黄", Cr[2]);
					break;
				case 3:
					DrawString(605, 250 + i * 54, "緑", Cr[3]);
					break;
				case 4:
					DrawString(605, 250 + i * 54, "橙", Cr[4]);
					break;
				case 5:
					DrawString(605, 250 + i * 54, "紫", Cr[5]);
					break;
				case 6:
					DrawString(605, 250 + i * 54, "赤紫", Cr[6]);
					break;
				case 7:
					DrawString(605, 250 + i * 54, "空", Cr[7]);
					break;
				default:
					DrawString(605, 250 + i * 54, "無", Cr[9]);
					break;
				}
			}

			DrawString(0, 420, "LEFTキー:左 RIGHTキー:右 Z,X,C:ショット SPACE:アイテム", Cr[9]);
			DrawFormatString(515, 30, Cr[8], "Stage:%d", stage);
			if (itemnum == 0) {
				DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
			}
			else {
				DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
			}

			if (Player.PlayerHP(0) > 15) {
				DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HPを描画
			}
			else if (Player.PlayerHP(0) > 7) {
				DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HPを描画
			}
			else {
				DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
				DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HPを描画
			}

			DrawString(0, 440, "ESCAPE:ゲーム強制終了", Cr[9]);
			DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

			DrawString(530, 60, "Tutoreal", Cr[8]);

			if (itemmenu == false) {//アイテムメニューが開かれていないとき
				gamecount++;//時間経過
				if (itemtime > -1)itemtime--;
				if (CheckHitKey(KEY_INPUT_SPACE) == 0) {
					Key = false;
				}

				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == false) {//アイテムメニュー
					itemmenu = true;
					command = 3;
					Key = true;
				}
			}
			if (gamecount > 100000000)gamecount = 0;//バグの防止
			if (gamecount > 150000000)*ErrorCheck = 4;//時間経過しすぎ
			ScreenFlip();

		}//クリアするまで

		ClearDrawScreen(); // 画面を消す
		if (gameflag == 1 && stage >= 3) {//最終ステージクリア
			gameflag = 2;
		}
		// 再生を止めます
		StopSoundMem(SHandle);
		StopSoundMem(SHandle2);

		if (*ErrorCheck == -2) {//途中終了の場合
			*ErrorCheck = 0;//正常に戻す
			gameflag = 3;//ゲームオーバーにする
		}

	} while (gameflag <= 1);//ゲームが終了しない限り

	DrawString(0, 200, "これでチュートリアルは終了です.", Cr[8]);
	DrawString(0, 250, "本編はステージ11まであります.", Cr[8]);
	DrawString(0, 300, "ぜひ最後までお楽しみください.", Cr[8]);
	ScreenFlip();
	WaitTimer(2000);//ここで2秒まつ

	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);
	DeleteSoundMem(SHandle2);

	return 0;
}

/*デモ画面*/
void Demonstration(int *ErrorCheck) {
	int demoselect = GetRand(2) + 1;//どのデモを再生するか(1～3)
	int demotimecount = 3600;//1デモの最大再生時間
	int BGM;

	//色作成
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//赤
	Cr[1] = GetColor(15, 15, 255);//青
	Cr[2] = GetColor(255, 255, 15);//黄
	Cr[3] = GetColor(15, 255, 15);//緑
	Cr[4] = GetColor(255, 156, 0);//橙
	Cr[5] = GetColor(159, 15, 255);//紫
	Cr[6] = GetColor(218, 0, 224);//赤紫
	Cr[7] = GetColor(76, 255, 255);//空
	Cr[8] = GetColor(240, 240, 240);//白
	Cr[9] = GetColor(128, 128, 128);//灰

	Mode1Player Player;
	Mode1Enemy NormalEnemy[MAXENEMY];
	Mode1Boss Boss[2];
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic, BossGraphic[6];
	// PNG画像のメモリへの分割読み込み
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);

	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);

	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	//再読み込み
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);

	MyGraphic = LoadGraph("../exe/package/paint/Player1.png");
	//再読み込み
	if (MyGraphic == -1)MyGraphic = LoadGraph("./package/paint/Player1.png");

	int gameflag = 0;//0:スタート時 1:ステージクリア 2:全ステージクリア 3:ゲームオーバー 4:ゲーム終了 5:エラー
	int gameovercount = AFTERGAMEOVERCOUNT;//戻るまでの秒数(1/60 s)
	int stage = 0;//現在ステージ
	int gamecount = 1;//ゲーム内時間
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind = 0;//ステージの種類 1:ノーマルステージ 2:ボスステージ 3:ゲームクリア 4:その他 (0:エラー)
	unsigned int playerpoint = 0;//得点の合計値
	bool clearflag = false;//ステージクリア
	int ppx = 0, ppy = 0;//自機のx座標とy座標
	int itemnum = 0;//アイテム個数
	int gamemode = 0;
	int moveselect = 0, movetime = 0;//動きの決定と動きの時間

	int SEshot = LoadSoundMem("../exe/package/bgm/shot.mp3");
	//再読み込み
	if (SEshot == -1)SEshot = LoadSoundMem("./package/bgm/shot.mp3");

	int SEbreak = LoadSoundMem("../exe/package/bgm/break.mp3");
	//再読み込み
	if (SEbreak == -1)SEbreak = LoadSoundMem("./package/bgm/break.mp3");

	int SElaser = LoadSoundMem("../exe/package/bgm/laser.wav");
	//再読み込み
	if (SElaser == -1)SElaser = LoadSoundMem("./package/bgm/laser.wav");

	i = 0;
	if (demoselect == 1) {
		demotimecount = 1800;
		stage = 4;
		stagekind = 1;
		gamemode = 1;
		BGM = LoadSoundMem("../exe/package/bgm/stage.mp3");
		//再読み込み
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/stage.mp3");
	}
	else if (demoselect == 2) {
		stage = 6;
		stagekind = 2;
		gamemode = 3;
		BGM = LoadSoundMem("../exe/package/bgm/boss.mp3");
		//再読み込み
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/boss.mp3");
	}
	else if (demoselect == 3) {
		demotimecount = 1800;
		stage = 7;
		stagekind = 1;
		gamemode = 2;
		BGM = LoadSoundMem("../exe/package/bgm/stage2.mp3");
		//再読み込み
		if (BGM == -1)BGM = LoadSoundMem("./package/bgm/stage2.mp3");
	}
	else {
		*ErrorCheck = -9;
	}
	itemnum = GetRand(5);

	if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
		*ErrorCheck = 1;
		return;        // エラーが起きたらループを抜ける
	}

	if (stage > 100)*ErrorCheck = 5;//明らかなエラー

	if (*ErrorCheck != 0) {
		return;//errorなら強制終了
	}

	/*ステージ初めの処理*/
	ClearDrawScreen(); // 画面を消す
	gamecount = 0;//経過時間を0にリセット
	gameovercount = AFTERGAMEOVERCOUNT;//終了までの時刻をリセット
	gameflag = 0;//ステージクリアしていない状態にする
	clearflag = false;
	Player.StartSet();//自機の初期化処理
	for (i = 0; i < MAXENEMY; i++) {
		NormalEnemy[i].StartSet(gamemode);
	}//敵機の初期化処理
	Boss[0].StartSet(0, gamemode);//ボスの初期化
	Boss[1].StartSet(0, gamemode);//ボスの初期化

	if (stagekind == 0) {//エラー
		*ErrorCheck = 3;
		return;
	}
	else if (stagekind == 1) {//ノーマルステージ
		NormalStage_StartPrepare(stage, ErrorCheck, NormalEnemy);//ノーマルステージ用準備
	}
	else if (stagekind == 2) {//ボスステージ
		Boss[0].StartSet(stage, gamemode);//ボスのセット
	}

	while (gameflag == 0) {
		/////**ステージ内処理**/////
		ClearDrawScreen(); // 画面を消す

		if (CheckSoundMem(BGM) == 0) {
			PlaySoundMem(BGM, DX_PLAYTYPE_BACK);//音楽
		}

		/*途中強制終了処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			if (*ErrorCheck == 0) {//正常なことの確認
				*ErrorCheck = -999;
			}
			ESCGameEnd(ErrorCheck);//強制終了
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			return;//errorなら強制終了
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			// サウンドハンドルの削除
			DeleteSoundMem(BGM);
			return;        // エラーが起きたらループを抜ける
		}

		/*終了処理*/
		if (CheckHitKey(KEY_INPUT_RETURN) == 1) {//デモ終了
			gameflag = 4;
			break;
		}

		if (demotimecount < 0) {
			gameflag = 4;
			break;
		}


		/*ゲームオーバー処理*/
		if (Player.PlayerHP(0) == 0) {
			if (gameovercount == AFTERGAMEOVERCOUNT) {
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (gameovercount > AFTERGAMEOVERCOUNT - 20) {
				DrawGraph(ppx, ppy, NormalEnemyGraphic[15], true);//破壊
			}
			gameovercount--;
			if (gameovercount <= 0) {
				gameflag = 3;
				break;
			}
		}
		if (Player.PlayerHP(0) < 0)*ErrorCheck = 2;//0未満にはならない

		/*ステージクリア*/
		if (stagekind == 1) {//ノーマルステージ
			if (gameflag == 3) {//ゲームオーバーになるならクリアはしない
				clearflag = false;
			}
			else {
				clearflag = true;
			}
			for (i = 0; i < MAXENEMY; i++) {
				if (NormalEnemy[i].EnemyExistCheck() == true) {
					clearflag = false;
				}
			}
		}
		else if (stagekind == 2) {//ボスステージ
			if (Boss[0].BossHP(0) == 0 && gameflag != 3) {//自分がゲームオーバーでなく、かつボスのHPが0でクリア
				clearflag = true;
			}
		}

		if (clearflag == true) {
			gameovercount--;
			if (gameovercount <= 0) {
				gameflag = 1;
				if (stagekind == 2) {//ボスステージ
					itemnum += 1;
				}
				break;
			}
		}

		///////ステージメイン処理///////
		/*プレイヤーの動きの決定*/
		if (movetime < 0) {
			demoselect = GetRand(99);
			if (demoselect < 25) {//右長め
				moveselect = 1;
				movetime = 60;
			}
			else if (demoselect < 50) {//左長め
				moveselect = 2;
				movetime = 60;
			}
			else if (demoselect < 70) {//右短め
				moveselect = 1;
				movetime = 30;
			}
			else if (demoselect < 90) {//左短め
				moveselect = 2;
				movetime = 30;
			}
			else {//静止
				moveselect = 0;
				movetime = 30;
			}
		}
		/*プレイヤーの実際の動き*/
		Player.PlayerDemoRandamMove(ErrorCheck, MyGraphic, PlayerShotGraphic, gamemode, SEshot, moveselect);

		/*敵機*/
		Player.PlayerPosition(&ppx, &ppy);
		if (stagekind == 1) {//ノーマルステージ
			for (i = 0; i < MAXENEMY; i++) {
				NormalEnemy[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx, ppy, gamemode, 0);
			}
			Player.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy, &itemnum);
		}
		else if (stagekind == 2) {//ボスステージ
			Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx, ppy, gamemode, 0, SEbreak, SElaser);
			Player.BossStage_CollisionDetection(ErrorCheck, Boss, stage, gamemode);
		}

		/////**情報**/////
		DrawBox(0, 0, MAXMAPX + 5, MAXMAPY, Cr[9], false);// 四角形を描画

		Player.PlayerShotColor(PlayerShotKind);
		Player.PlayerShotCombo(ShotCombonum);

		DrawString(515, 210, "現在の弾の種類", Cr[9]);
		DrawString(515, 250, "Zショット:\n\n\nXショット:\n\n\nCショット:", Cr[8]);
		for (i = 0; i < 3; i++) {
			DrawFormatString(515, 270 + i * 54, Cr[PlayerShotKind[i]], "コンボ:%d", ShotCombonum[i]);
			switch (PlayerShotKind[i]) {
			case 0:
				DrawString(605, 250 + i * 54, "赤", Cr[0]);
				break;
			case 1:
				DrawString(605, 250 + i * 54, "青", Cr[1]);
				break;
			case 2:
				DrawString(605, 250 + i * 54, "黄", Cr[2]);
				break;
			case 3:
				DrawString(605, 250 + i * 54, "緑", Cr[3]);
				break;
			case 4:
				DrawString(605, 250 + i * 54, "橙", Cr[4]);
				break;
			case 5:
				DrawString(605, 250 + i * 54, "紫", Cr[5]);
				break;
			case 6:
				DrawString(605, 250 + i * 54, "赤紫", Cr[6]);
				break;
			case 7:
				DrawString(605, 250 + i * 54, "空", Cr[7]);
				break;
			default:
				DrawString(605, 250 + i * 54, "無", Cr[9]);
				break;
			}
		}

		DrawString(0, 420, "ESCキー:ゲーム終了\nENTERキー:デモ画面を終了してタイトルに戻る", Cr[9]);
		DrawFormatString(515, 30, Cr[8], "Demo");
		if (itemnum == 0) {
			DrawFormatString(480, 420, Cr[9], "ITEM:%d", itemnum);
		}
		else {
			DrawFormatString(480, 420, Cr[8], "ITEM:%d", itemnum);
		}

		if (Player.PlayerHP(0) > 15) {
			DrawFormatString(515, 90, Cr[3], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[3], true);// HPを描画
		}
		else if (Player.PlayerHP(0) > 7) {
			DrawFormatString(515, 90, Cr[2], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[2], true);// HPを描画
		}
		else {
			DrawFormatString(515, 90, Cr[0], "HP:%d", Player.PlayerHP(0));
			DrawBox(510, 112, 510 + 4 * Player.PlayerHP(0), 117, Cr[0], true);// HPを描画
		}

		DrawFormatString(520, 140, Cr[8], "Stage Points\n:%d", Player.GetPoint());

		if (gamemode == 1) {//EASY
			DrawString(530, 60, "EASY", Cr[8]);
		}
		else if (gamemode == 2) {//NORMAL
			DrawString(530, 60, "NORMAL", Cr[8]);
		}
		else if (gamemode == 3) {//HARD
			DrawString(530, 60, "HARD", Cr[8]);
		}
		else if (gamemode == 4) {//UNKNOWN
			DrawString(530, 60, "UNKNOWN", Cr[8]);
		}

		/*時間経過*/
		gamecount++;
		demotimecount--;
		movetime--;

		if (gamecount > 100000000)gamecount = 0;//バグの防止
		if (gamecount > 150000000)*ErrorCheck = 4;//時間経過しすぎ
		ScreenFlip();

	}//クリアするまで

	// サウンドハンドルの削除
	DeleteSoundMem(BGM);

	return;
}

