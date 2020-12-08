#pragma once
#include "DxLib.h"

#define MAXENEMY 70
#define MAXMAPX 500
#define MAXMAPY 395 
#define AFTERGAMEOVERCOUNT 300

#define NEXTKEYTIME1 60

/////---**1Player mode**---/////
/////**敵機用関数(ノーマル)**/////
class Mode1Enemy {
private:
	int epx, epy;//x座標,y座標
	bool existflag;//存在しているか
	bool esflag;//弾が打たれているか
	int ekind;//種類
	int eax, eay, eskind;//狙う場所
	int esx, esy;//弾の座標
	int nextshotcount;//次の弾発射までの間隔

public:
	void StartSet(int gamemode);//最初の初期化処理
	void AppearEnemy(int x, int y, int kind);//敵出現用関数
	void NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime);//敵の動きに関する処理(ノーマル敵)
	/*敵機の座標と種類,敵の弾の座標,存在フラグを返す*/
	void EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag);
	void BreakEnemy();//敵を倒したときの処理
	bool EnemyExistCheck() { return existflag; };//存在するかどうか
	int EnemyKindCheck() { return ekind; };//種類は何か
	void EnemyShotFlagFALSE() { esflag = false; };//弾が撃たれていない状態にする
	void NormalEnemyGraphicDrawing(int *errorcheck, int NormalEnemyGraphic[]);//グラフィックのみ表示
};


/////**敵機用関数(ボス)**/////
class Mode1Boss {
private:
	int epx, epy;//ボス自体のx座標,y座標
	int ekind;//種類(11:grad 12:cron 13:erec 14:rain 15:staga)*stagaは2PlayerModeでのみ出現するので欠番
	int esx[10], esy[10], eskind[10];//弾の座標と種類
	bool esflag[10];//弾が存在しているか
	bool existflag;//ボス自体が存在しているか
	int move, bosscolor;//動き方の指定、色の指定
	int bosscount, protectcount;//時間制御,無敵時間
	int maxhp, nowhp;//最大、現在HP

	void Boss_Grad_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Cron_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Erec_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode);
	void Boss_Rain_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS);
	void Boss_StagatoteSP_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS);

public:
	void StartSet(int stage, int gamemode);//最初の初期化処理と出現
	/*敵の動きに関する処理(ボス敵)*/
	void BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime, int SEbreak, int SElaser);
	int BossHP(int damage);//ボスの残りHP
	/*敵機の座標,敵の種類,敵の弾の座標,弾の種類,無敵時間を返す*/
	void BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect);
	void BossShotFlagFALSE(int n);//弾が撃たれていない状態にする
	int BossMoveSet(int n, bool changeflag);//falseならn=0(変化なし)か1～4(反転させる)
	int BossColorCheck() { return bosscolor; };//ボスの色を返す
	int BossPositionCheck(int *enemyx, int *enemyy);//ボスの位置と特殊技の種類取得
	void BossPositionMove(int movex, int movey);//位置の強制移動
};


/////**自機用関数**/////
class Mode1Player {
private:
	int ppx, ppy;//x座標,y座標
	int php, damagetime;//自機HP,ダメージ後の復帰時間
	bool psflag[3][3];//弾が打たれているか
	int pskind[3];//現在の弾の種類(9:何もなし)
	int psx[3][3], psy[3][3];//それぞれの弾の座標
	bool keyflag[3];//キーが押されているか
	int keyflagcount[3];//キーが押されていない状態になるまでの時間
	int pscombocount[3], pscombotimes[3];//コンボ数と倍率
	int point, totalcombonum;//得点とコンボ数

public:
	void DebagColorSet();//デバッグ用弾の色設定関数
	void StartSet();//最初の初期化処理
	int PlayerHP(int damage);//プレイヤーのHPに関する処理
	void PlayerMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE);//プレイヤーの動きに関する処理
	void PlayerShotColor(int PlayerShotKind[]);//弾の種類を返す関数
	void PlayerShotCombo(int ShotComboNum[]);//コンボ数を返す関数
	void NormalStage_CollisionDetection(int *errorcheck, Mode1Enemy Enemy[], int *itemnum);//当たり判定とダメージ
	int GetPoint() { return point; };//得点を返す
	void PlayerPosition(int *x, int *y) { *x = ppx; *y = ppy; };//場所を返す
	void BossStage_CollisionDetection(int *errorcheck, Mode1Boss Boss[], int stage, int gamemode);//当たり判定とダメージ
	void ColorSet(int key, int color) { pskind[key] = color; };//アイテム:色替え
	int TotalComboNum() { return totalcombonum; };
	/*デモ画面用プレーヤーのランダムな動き(動き指定用の数値は外で指定)*/
	void PlayerDemoRandamMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE, int MoveSelect);
};


/////**関数集**/////
/*デバッグ用*/
void Mode1Player::DebagColorSet() {
	if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[0] = 0;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[0] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[0] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[0] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[0] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[0] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[0] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[0] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[0] = 9;
	}

	if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[1] = 0;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[1] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[1] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[1] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[1] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[1] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[1] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[1] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_X) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[1] = 9;
	}

	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_0) == 1) {
		pskind[2] = 0;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_1) == 1) {
		pskind[2] = 1;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_2) == 1) {
		pskind[2] = 2;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_3) == 1) {
		pskind[2] = 3;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_4) == 1) {
		pskind[2] = 4;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_5) == 1) {
		pskind[2] = 5;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_6) == 1) {
		pskind[2] = 6;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_7) == 1) {
		pskind[2] = 7;
	}
	else if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_9) == 1) {
		pskind[2] = 9;
	}

}//デバッグ用


/*ゲーム処理用*/
int InductionShotMotion(int count) {
	int n = 14;
	if (count % 48 < 6) {
		n = 14;
	}
	else if (count % 48 < 12) {
		n = 16;
	}
	else if (count % 48 < 18) {
		n = 17;
	}
	else if (count % 48 < 24) {
		n = 16;
	}
	else if (count % 48 < 30) {
		n = 14;
	}
	else if (count % 48 < 36) {
		n = 18;
	}
	else if (count % 48 < 42) {
		n = 19;
	}
	else {
		n = 18;
	}

	return n;
}

void Mode1Player::StartSet() {
	int i, j;
	ppx = 250;
	ppy = 355;
	php = 30;//HPの初期値
	point = 0;
	for (i = 0; i < 3; i++) {
		pskind[i] = 9;
		pscombocount[i] = 0;
		pscombotimes[i] = 1;
		if (CheckHitKeyAll() == 0) {//キーが押されていない
			keyflag[i] = false;
			keyflagcount[i] = 0;
		}
		else {
			keyflag[i] = true;
			keyflagcount[i] = NEXTKEYTIME1;
		}
		for (j = 0; j < 3; j++) {
			psflag[i][j] = false;
			psx[i][j] = ppx + 12;
			psy[i][j] = ppy;
		}
	}
	totalcombonum = 0;
	damagetime = 0;
}//最初の処理

int Mode1Player::PlayerHP(int damage) {
	php -= damage;
	if (php < 0) {
		php = 0;
	}
	else if (php > 30) {
		php = 30;
	}

	if (damage > 0) {//ダメージを受けている
		damagetime = 45;
	}
	else if (damage < -1) {//アイテム:HP回復
		damagetime = 15;
	}
	return php;
}//プレイヤーのHPに関する処理

void Mode1Player::PlayerMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE) {
	int i, j;
	if (ppx > MAXMAPX + 100 || ppx < -100)*errorcheck = 2;//左右へ行きすぎ

	/*弾のキーチェック*/
	if (CheckHitKey(KEY_INPUT_Z) == 0) {
		keyflag[0] = false;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_X) == 0) {
		keyflag[1] = false;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_C) == 0) {
		keyflag[2] = false;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == true) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = false;
		}
	}

	/*ボタンと対応する動き*/
	if (php > 0) {//HPが尽きていないなら
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX - 30)ppx = MAXMAPX - 30;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_A) == 1) {
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (CheckHitKey(KEY_INPUT_Z) == 1 && keyflag[0] == false) {
			keyflag[0] = true;
			keyflagcount[0] = NEXTKEYTIME1;
			if (psflag[0][0] == false) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][1] == false) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][2] == false) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (CheckHitKey(KEY_INPUT_X) == 1 && keyflag[1] == false) {
			keyflag[1] = true;
			keyflagcount[1] = NEXTKEYTIME1;
			if (psflag[1][0] == false) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][1] == false) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][2] == false) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (CheckHitKey(KEY_INPUT_C) == 1 && keyflag[2] == false) {
			keyflag[2] = true;
			keyflagcount[2] = NEXTKEYTIME1;
			if (psflag[2][0] == false) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][1] == false) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][2] == false) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
	}

	/*グラフィック表示*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, true);//倒されていないなら表示
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == true) {
				psy[i][j] -= 5;//自機の弾の動き
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], true);
				if (psy[i][j] < -50) {
					psflag[i][j] = false;
				}
			}
		}
	}

	/*時間経過による処理*/
	if (damagetime >= -5) {
		if (damagetime > 30 && gamemode == 3) {//HARD
			damagetime = 30;
		}
		else if (damagetime > 15 && gamemode == 4) {//UNKNOWN
			damagetime = 15;
		}
		damagetime--;
	}

}//プレイヤーの動きに関する処理(弾も)

void Mode1Player::PlayerShotColor(int PlayerShotKind[]) {
	for (int i = 0; i < 3; i++) {
		PlayerShotKind[i] = pskind[i];
	}
}//弾の種類を返す関数

void Mode1Player::PlayerShotCombo(int ShotComboNum[]) {
	for (int i = 0; i < 3; i++) {
		ShotComboNum[i] = pscombocount[i];
	}
}//コンボ数を返す関数

 /*当たり判定とダメージ*/
void Mode1Player::NormalStage_CollisionDetection(int *errorcheck, Mode1Enemy Enemy[], int *itemnum) {
	int epx = 0, epy = 0, enemykind = 9;//敵機の座標と種類
	int esx = 0, esy = 0;//敵の弾の座標
	bool enemyflag = false, enemyshotflag = false;//存在フラグ
	int i, j, k;
	bool breakflag = false;

	for (i = 0; i < MAXENEMY; i++) {
		breakflag = false;
		/*敵機の情報取得*/
		Enemy[i].EnemyInfoReturn(&epx, &epy, &enemykind, &esx, &esy, &enemyflag, &enemyshotflag);
		if (enemyflag == true && enemykind == 9)*errorcheck = 4;//存在しているのに存在していない
		if (enemyflag == true) {//敵機が存在しているとき
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psflag[j][k] == true) {//弾が存在しているとき
						if (psx[j][k] + 5 < epx + 28 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 28 && psy[j][k] + 16>epy + 4) {
							/*弾が当たった時*/
							if (enemykind < 10) {//バリアショット以外
								if (pskind[j] == enemykind) {//前回と同じ
									totalcombonum += 1;//コンボ数に加算
									pscombocount[j] += 1;//コンボ数を1増やす
									pscombotimes[j] *= 2;//コンボ倍率を上げる
									if (pscombotimes[j] > 999999999)pscombotimes[j] = 999999999;//エラー防止
									if (pscombocount[j] % 5 == 0 && pscombocount[j] > 0) {
										*itemnum += 1;
									}
								}
								else if (enemykind == 8) {//白（コンボに加算されない）だった
									point += 5;
								}
								else {//特に特殊なことはなかった
									pskind[j] = enemykind;//弾を変える
									pscombocount[j] = 1;//コンボ数を１にする
									pscombotimes[j] = 1;
								}

								/*共通処理*/
								Enemy[i].BreakEnemy();//敵を破壊
								point += pscombotimes[j];//ポイント加算
								if (point > 999999999)point = 999999999;//エラー防止
							}
							psflag[j][k] = false;//弾を消す
							breakflag = true;
						}
					}
				}
				if (breakflag == true)break;
			}

			if (ppx + 8 < epx + 30 && ppx + 32 > epx + 2 && ppy + 20 < epy + 30 && ppy + 35 > epy + 2) {
				/*敵機が当たった時(バリアショットのみ)*/
				if (damagetime < 1)PlayerHP(3);//ダメージ
				Enemy[i].BreakEnemy();//敵機を消す
			}

		}
		if (enemyshotflag == true) {//敵の弾が存在しているとき
			if (esx + 12 < ppx + 30 && esx + 20 > ppx + 10 && esy + 12 < ppy + 30 && esy + 20 > ppy + 6) {
				/*敵の弾がぶつかった*/
				if (damagetime < 1)PlayerHP(1);//ダメージ
				Enemy[i].EnemyShotFlagFALSE();
			}
		}
	}

}//当たり判定確認用関数

void Mode1Player::BossStage_CollisionDetection(int *errorcheck, Mode1Boss Boss[], int stage, int gamemode) {
	int epx = 0, epy = 0, enemykind = 9;//敵機の座標と種類
	int esx[10] = {}, esy[10] = {}, eskind[10] = {};//敵の弾の座標
	int protecttime = 0;//無敵時間
	bool enemyshotflag[10] = {};//存在フラグ
	int i, j, k;
	int tmp = 0;//仮置き用

	/*敵機の情報取得*/
	Boss[0].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
	if (Boss[0].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//存在しているのに存在していない
	if (Boss[0].BossHP(0) > 0) {//敵機が存在しているとき
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (psflag[j][k] == true) {//弾が存在しているとき
					if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
						/*弾が当たった時*/
						if (protecttime <= 0) {
							Boss[0].BossHP(1);//1ダメージを与える
							point += 3;

							if (Boss[0].BossColorCheck() >= 9 || Boss[0].BossColorCheck() < 0) {
								/*特に何もなし*/
							}
							else if (pskind[j] == Boss[0].BossColorCheck()) {//前回と同じ色
								pscombocount[j] += 1;//コンボ数を1増やす
							}
							else {//前回と違う色
								pskind[j] = Boss[0].BossColorCheck();//弾を変える
								pscombocount[j] = 1;//コンボ数を１にする
								pscombotimes[j] = 1;
							}

							point += pscombocount[j];//ボーナスポイント
							if (Boss[0].BossHP(0) == 0) {
								if (stage != 11)point += 100 * gamemode;
								else if (stage == 11)point += 1000 * gamemode;
							}
						}
						psflag[j][k] = false;
					}
				}
			}
		}
	}
	for (i = 0; i < 10; i++) {
		if (enemyshotflag[i] == true) {//敵の弾が存在しているとき
			if (esx[i] + 12 < ppx + 30 && esx[i] + 20 > ppx + 10 && esy[i] + 12 < ppy + 30 && esy[i] + 20 > ppy + 6) {
				/*敵の弾がぶつかった*/
				if (damagetime <= 0) {
					if (eskind[i] >= 20 && eskind[i] < 50) {
						PlayerHP(3);//3ダメージ
						Boss[0].BossShotFlagFALSE(i);
					}
					else {//通常のダメージ
						PlayerHP(1);//ダメージ
						Boss[0].BossShotFlagFALSE(i);
					}
				}
			}
		}
	}

	/*分身について*/
	if (stage == 11 || stage == 16) {
		Boss[1].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
		if (Boss[1].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//存在しているのに存在していない
		if (Boss[1].BossHP(0) > 0) {//敵機が存在しているとき
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psflag[j][k] == true) {//弾が存在しているとき
						if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
							/*弾が当たった時*/
							if (stage == 11)Boss[1].BossMoveSet(gamemode, false);
							psflag[j][k] = false;
						}
					}
				}
			}
		}
		for (i = 0; i < 10; i++) {
			if (enemyshotflag[i] == true) {//敵の弾が存在しているとき
				if (esx[i] + 12 < ppx + 30 && esx[i] + 20 > ppx + 10 && esy[i] + 12 < ppy + 30 && esy[i] + 20 > ppy + 6) {
					/*敵の弾がぶつかった*/
					if (damagetime <= 0) {
						if (eskind[i] >= 20 && eskind[i] < 50) {
							PlayerHP(3);//3ダメージ
							Boss[1].BossShotFlagFALSE(i);
						}
						else {//通常のダメージ
							PlayerHP(1);//ダメージ
							Boss[1].BossShotFlagFALSE(i);
						}
					}
				}
			}
		}
	}

}//当たり判定確認用関数

void Mode1Player::PlayerDemoRandamMove(int *errorcheck, int MyGraphic, int PlayerShotGraphic[], int gamemode, int SE, int MoveSelect) {
	int i, j;
	if (ppx > MAXMAPX + 100 || ppx < -100)*errorcheck = 2;//左右へ行きすぎ

	/*ショットの決定*/
	bool Zshot = false, Xshot = false, Cshot = false;
	int tmprandam = 0;
	tmprandam = GetRand(100);
	if (tmprandam  < 2) {
		Zshot = true;
	}
	tmprandam = GetRand(100);
	if (tmprandam < 20 && tmprandam  >= 18) {
		Xshot = true;
	}
	tmprandam = GetRand(100);
	if (tmprandam < 56 && tmprandam >= 54) {
		Cshot = true;
	}

	/*動き*/
	if (php > 0) {//HPが尽きていないなら
		if (MoveSelect == 1) {//右
			ppx += 3;
			if (ppx > MAXMAPX - 30)ppx = MAXMAPX - 30;
		}
		if (MoveSelect == 2) {//左
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (Zshot = true) {
			keyflag[0] = true;
			keyflagcount[0] = NEXTKEYTIME1;
			if (psflag[0][0] == false) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][1] == false) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[0][2] == false) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (Xshot = true) {
			keyflag[1] = true;
			keyflagcount[1] = NEXTKEYTIME1;
			if (psflag[1][0] == false) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][1] == false) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[1][2] == false) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
		if (Cshot = true) {
			keyflag[2] = true;
			keyflagcount[2] = NEXTKEYTIME1;
			if (psflag[2][0] == false) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][1] == false) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
			else if (psflag[2][2] == false) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = true;
				PlaySoundMem(SE, DX_PLAYTYPE_BACK);//SE
			}
		}
	}

	/*グラフィック表示*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, true);//倒されていないなら表示
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == true) {
				psy[i][j] -= 5;//自機の弾の動き
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], true);
				if (psy[i][j] < -50) {
					psflag[i][j] = false;
				}
			}
		}
	}

	/*時間経過による処理*/
	if (damagetime >= -5) {
		if (damagetime > 30 && gamemode == 3) {//HARD
			damagetime = 30;
		}
		else if (damagetime > 15 && gamemode == 4) {//UNKNOWN
			damagetime = 15;
		}
		damagetime--;
	}
}

void Mode1Enemy::StartSet(int gamemode) {//最初の処理
	epx = 0;
	epy = 0;
	eskind = 0;
	existflag = false;
	esflag = false;
	ekind = 9;
	eax = epx;
	eay = epy;
	esx = epx;
	esy = epy;
	if (gamemode == 1) {//EASY
		nextshotcount = 540 + GetRand(1200);
	}
	else if (gamemode = 2) {//NORMAL
		nextshotcount = 135 + GetRand(600);
	}
	else if (gamemode == 3) {//HARD
		nextshotcount = 45 + GetRand(300);
	}
	else if (gamemode == 4) {//UNKNOWN
		nextshotcount = 15 + GetRand(150);
	}
}

void Mode1Enemy::AppearEnemy(int x, int y, int kind) {//出現場所と種類を決めて呼び出す
	if (existflag == false) {
		epx = x;
		epy = y;
		existflag = true;
		esflag = false;
		ekind = kind;
		eax = epx;
		eay = epy;
		esx = epx;
		esy = epy;
	}
}//敵出現用関数

void Mode1Enemy::BreakEnemy() {
	existflag = false;
}//敵を倒したときの処理

void Mode1Enemy::NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime) {
	/*グラフィック*/
	if (esflag == true) {//弾が存在するなら
		DrawGraph(esx, esy, NormalEnemyGraphic[11], true);//弾
	}

	if (existflag == true) {//機体が存在するなら
		NormalEnemyGraphicDrawing(errorcheck, NormalEnemyGraphic);

		if (itemtime < 1) {
			/*移動*/
			if (ekind == 10) {//バリアショット
				epy += 1;
				if (epy > MAXMAPY - 28) {
					BreakEnemy();//下端到達時に消滅
				}
			}
			else if (ekind == 11) {//バリア
				/*動かない*/
			}
			else if (count % 3 == 0) {
				if (gamemode >= 3) {//HARD以上
					if (count % 120 < 60) {
						epx += 1;
					}
					else {
						epx -= 1;
					}
				}
				else if (gamemode == 1) {
					if (count % 120 >= 30 && count % 120 < 90) {
						if (count % 6 == 0)
							epx += 1;
					}
					else {
						if (count % 6 == 0) {
							epx -= 1;
						}
					}
				}
				else if (gamemode == 2) {//Normal(ゆっくり動く)
					if (count % 360 >= 90 && count % 360 < 270) {
						if (count % 6 == 0) {
							epx += 1;
						}
					}
					else {
						if (count % 6 == 0) {
							epx -= 1;
						}
					}
				}
			}


			if (gamemode == 20 || ekind >= 10) {//弾を撃たない
				return;
			}

			/*弾撃ち*/
			nextshotcount--;
			if (nextshotcount < 0) {//一定時間ごとに発射
				if (gamemode <= 1) {//EASY
					nextshotcount = 420 + GetRand(900);//時間のリセット
				}
				else if (gamemode == 2) {//NORMAL
					nextshotcount = 270 + GetRand(540);//時間のリセット
				}
				else if (gamemode == 3) {//HARD
					if (esflag == false) {
						nextshotcount = 60 + GetRand(360);
					}
				}
				else if (gamemode == 4) {//UNKNOWN
					nextshotcount = GetRand(180);
				}

				if (esflag == false) {//弾が撃たれていないなら
					esx = epx;
					esy = epy;
					eax = ppx;
					eay = ppy;
					if (gamemode == 4 && ekind != 8) {//UNKNOWN
						esflag = true;
						eskind = GetRand(9) + 1;
						if (eskind == 10) {
							eax = 3 * (eax - esx) / (eay - esy);
							eskind = 99;
						}
					}
					else {
						if (ekind != 6)esflag = true;//弾を撃つ
					}

					if (gamemode <= 3 || ekind == 8) {//EASY || NORMAL || HARD
						/*狙う場所*/
						switch (ekind) {
						case 0://赤
							eskind = 1;
							break;
						case 1://青
							if (ppx < epx - 200) {
								eax -= 30;
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150以上左
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 4;
							}
							else if (ppx > epx + 200) {
								eax -= 30;
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 5;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 3;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 1;
							}
							else {
								eskind = 2;
							}
							break;
						case 2://黄
							if (ppx < epx - 200) {
								eax += 30;
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150以上左
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 1;
							}
							else if (ppx > epx + 200) {
								eax += 30;
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 9;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 7;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 5;
							}
							else {
								eskind = 3;
							}
							break;
						case 3://緑
							if (ppx < epx - 200) {
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 80) {//80以上左
								eskind = 4;
							}
							else if (ppx < epx - 30) {//30以上左
								eskind = 2;
							}
							else if (ppx > epx + 200) {
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 80) {//80以上右
								eskind = 5;
							}
							else if (ppx > epx + 30) {//30以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
							break;
						case 4://橙
							eskind = 2;
							break;
						case 5://紫
							eskind = 3;
							break;
						case 6://赤紫
							break;
						case 7://空
							if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1) {
								if (ppx < epx - 200) {
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150以上左
									eskind = 6;
								}
								else if (ppx < epx - 80) {//80以上左
									eskind = 4;
								}
								else if (ppx < epx - 30) {//30以上左
									eskind = 2;
								}
								else if (ppx > epx + 200) {
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150以上右
									eskind = 7;
								}
								else if (ppx > epx + 80) {//80以上右
									eskind = 5;
								}
								else if (ppx > epx + 30) {//30以上右
									eskind = 3;
								}
								else {
									eskind = 1;
								}
							}
							else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
								if (ppx < epx - 200) {
									eax += 30;
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150以上左
									eskind = 4;
								}
								else if (ppx < epx - 100) {//100以上左
									eskind = 2;
								}
								else if (ppx < epx - 50) {//50以上左
									eskind = 1;
								}
								else if (ppx > epx + 200) {
									eax += 30;
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150以上右
									eskind = 9;
								}
								else if (ppx > epx + 100) {//100以上右
									eskind = 7;
								}
								else if (ppx > epx + 50) {//50以上右
									eskind = 5;
								}
								else {
									eskind = 3;
								}
							}
							else if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
								if (ppx < epx - 200) {
									eax -= 30;
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150以上左
									eskind = 8;
								}
								else if (ppx < epx - 100) {//100以上左
									eskind = 6;
								}
								else if (ppx < epx - 50) {//50以上左
									eskind = 4;
								}
								else if (ppx > epx + 200) {
									eax -= 30;
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150以上右
									eskind = 5;
								}
								else if (ppx > epx + 100) {//100以上右
									eskind = 3;
								}
								else if (ppx > epx + 50) {//50以上右
									eskind = 1;
								}
								else {
									eskind = 2;
								}
							}
							else {
								if (ppx < epx - 200) {
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx < epx - 150) {//150以上左
									eskind = 6;
								}
								else if (ppx < epx - 80) {//80以上左
									eskind = 4;
								}
								else if (ppx < epx - 30) {//30以上左
									eskind = 2;
								}
								else if (ppx > epx + 200) {
									eskind = 99;
									if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
										eax = 3 * (eax - esx) / (eay - esy);
									}
									else {
										eax = 0;
									}
								}
								else if (ppx > epx + 150) {//150以上右
									eskind = 7;
								}
								else if (ppx > epx + 80) {//80以上右
									eskind = 5;
								}
								else if (ppx > epx + 30) {//30以上右
									eskind = 3;
								}
								else {
									eskind = 1;
								}
							}
							break;
						case 8://白
							if (ppx < epx - 200) {
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 80) {//80以上左
								eskind = 4;
							}
							else if (ppx < epx - 30) {//30以上左
								eskind = 2;
							}
							else if (ppx > epx + 200) {
								eskind = 99;
								if (eay != esy) {//狙う場所よりも弾が左か右,かつ0除算を防ぐ
									eax = 3 * (eax - esx) / (eay - esy);
								}
								else {
									eax = 0;
								}
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 80) {//80以上右
								eskind = 5;
							}
							else if (ppx > epx + 30) {//30以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
							break;
						case 9://灰
							break;
						case 10://バリアショット
							break;
						}
					}
				}
			}
		}
	}

	if (esflag == true) {//弾が撃たれているとき
		switch (eskind) {
		case 0://弾を撃たない
			break;
		case 1://真下
			esy += 3;
			break;
		case 2://0.5左
			esy += 3;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 3://0.5右
			esy += 3;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 4://1左
			esy += 3;
			esx -= 1;
			break;
		case 5://1右
			esy += 3;
			esx += 1;
			break;
		case 6://1.5左
			esy += 3;
			esx -= 1;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 7://1.5右
			esy += 3;
			esx += 1;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 8://2左
			esy += 3;
			esx -= 2;
			break;
		case 9://2右
			esy += 3;
			esx += 2;
			break;
		case 10://2.5左
			esy += 3;
			esx -= 2;
			if (count % 2 == 0) {
				esx -= 1;
			}
			break;
		case 11://2.5右
			esy += 3;
			esx += 2;
			if (count % 2 == 0) {
				esx += 1;
			}
			break;
		case 99://狙う
			esy += 3;
			esx += eax;
			break;
		}


		if (esy > MAXMAPY - 30 || esx > MAXMAPX - 15 || esx < -10)esflag = false;// 端に到達時に消える
	}

}//敵の動きと弾に関する処理(ノーマル敵) 

void Mode1Enemy::EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*shotx = esx;
	*eshoty = esy;
	*enemyflag = existflag;
	*shotflag = esflag;
}//敵機の座標,敵の弾の座標,存在フラグを返す

void Mode1Enemy::NormalEnemyGraphicDrawing(int *errorcheck, int NormalEnemyGraphic[]) {
	if (existflag == true) {//機体が存在するなら
		if (ekind == 11) {
			DrawGraph(epx, epy, NormalEnemyGraphic[10], true);//機体
		}
		else if (ekind < 11) {
			DrawGraph(epx, epy, NormalEnemyGraphic[ekind], true);//機体
		}
		else {
			*errorcheck = -9;
		}
	}
}

void Mode1Boss::StartSet(int stage, int gamemode) {
	existflag = true;
	epx = 250;
	epy = 30;
	move = 0;
	bosscolor = 9;//エラー防止(色なし)
	maxhp = 1;//エラー防止(HP1)
	bosscount = 150;//時間制御
	protectcount = 90;//無敵時間
	switch (stage) {
	case 0://出現しない
		maxhp = 0;
		existflag = false;
		break;
	case 3:
		ekind = 11;
		bosscolor = 4;
		if (gamemode == 1) {//EASY
			maxhp = 20;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 25;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 30;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 33;
		}
		break;
	case 6:
		ekind = 12;
		bosscolor = 3;
		if (gamemode == 1) {//EASY
			maxhp = 28;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 35;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 42;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 45;
		}
		break;
	case 9:
		ekind = 13;
		bosscolor = 2;
		if (gamemode == 1) {//EASY
			maxhp = 38;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 48;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 58;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 62;
		}
		break;
	case 11:
		ekind = 14;
		epy = 70;
		bosscolor = GetRand(7);
		if (gamemode == 1) {//EASY
			maxhp = 56;
		}
		else if (gamemode == 2) {//NORMAL
			maxhp = 70;
		}
		else if (gamemode == 3) {//HARD
			maxhp = 84;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 100;
		}
		break;
	case 16://HARD以上  SPステージ(処理上はステージ16)
		ekind = 16;
		bosscolor = 9;//無色
		if (gamemode == 3) {//HARD
			maxhp = 66;
		}
		else if (gamemode == 4) {//UNKNOWN
			maxhp = 80;
		}
		break;
	case 99://ステージ11の分身
		ekind = 99;
		bosscolor = 10;//無色かつ色変化なし
		maxhp = 10;
		move = 100;
		epy = 70;
		protectcount = 180;
		break;
	case 100://SPステージの補助パーツ
		ekind = 100;
		bosscolor = 10;//無色かつ色変化なし
		maxhp = 7;
		move = 0;
		epy = 15;
		protectcount = 10;
		break;
	default://それ以外がボスステージになることはない
		return;
	}
	nowhp = maxhp;
	for (int i = 0; i < 10; i++) {
		esx[i] = epx;
		esy[i] = epy;
		eskind[i] = 0;
		esflag[i] = false;
	}
}//最初の初期化処理と出現

void Mode1Boss::BossShotFlagFALSE(int n) {
	eskind[n] = 0;
	esflag[n] = false;
}

void Mode1Boss::BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int gamemode, int itemtime, int SEbreak, int SElaser) {
	int i;
	//色作成
	int Cr[10];
	Cr[0] = GetColor(255, 15, 15);//赤
	Cr[1] = GetColor(15, 15, 255);//青
	Cr[2] = GetColor(255, 255, 15);//黄
	Cr[3] = GetColor(15, 255, 15);//緑
	Cr[4] = GetColor(255, 156, 0);//橙
	Cr[5] = GetColor(159, 15, 255);//紫
	Cr[6] = GetColor(218, 0, 224);//赤紫
	Cr[7] = GetColor(35, 255, 255);//空
	Cr[8] = GetColor(240, 240, 240);//白
	Cr[9] = GetColor(128, 128, 128);//灰

	/*ステージチェックと名前表示、敵の動きなど*/
	switch (ekind) {
	case 11:
		DrawFormatString(5, 3, Cr[bosscolor], "Grad:HP");//赤、黄、橙
		/*敵の動き*/
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_Grad_Move(errorcheck, count, ppx, ppy, gamemode);//Gradの動き
			}
		}
		break;
	case 12:
		DrawFormatString(5, 3, Cr[bosscolor], "Cron:HP");//紫、空、緑
		/*敵の動き*/
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_Cron_Move(errorcheck, count, ppx, ppy, gamemode);//Cronの動き
			}
		}
		break;
	case 13:
		DrawFormatString(5, 3, Cr[bosscolor], "Erec:HP");//青、紫、黄
		/*敵の動き*/
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_Erec_Move(errorcheck, count, ppx, ppy, gamemode);//Erecの動き
			}
		}
		break;
	case 14:
		DrawFormatString(5, 3, Cr[bosscolor], "Rain:HP");//全色
		/*敵の動き*/
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_Rain_Move(errorcheck, count, ppx, ppy, gamemode, true);//Rainの動き
			}
		}
		break;
	case 15://1PlayerModeではなし
		break;
	case 16://BOSSRUSHのみ Stagatote_SP
		DrawFormatString(5, 3, Cr[9], "Stagatote_SP:HP");//無色
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_StagatoteSP_Move(errorcheck, count, ppx, ppy, gamemode, true);//Stagatote_SPの動き
			}
		}

		break;
	case 99://ekind=14:Rainの分身
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_Rain_Move(errorcheck, count, ppx, ppy, gamemode, false);//Rainの分身の動き
			}
		}
		break;
	case 100://BOSSRUSHのみ Stagatote_SPの補助パーツ
		if (itemtime < 1) {
			if (nowhp > 0) {//存在するときのみ動く
				Boss_StagatoteSP_Move(errorcheck, count, ppx, ppy, gamemode, false);//Stagatote_SP補助の動き
			}
		}
		break;
	default:
		*errorcheck = 6;//呼び出されないはず
		break;
	}

	/*HP表示と機体表示*/
	if (ekind == 99) {
		if (nowhp > 0) {
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[5], true);//機体
		}
		else {
			existflag = false;
		}
	}
	else if (ekind == 16) {
		if (nowhp > 0) {
			DrawBox(142, 7, 142 + 350 * nowhp / maxhp, 15, Cr[3], true);// HPを描画
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[4], true);//機体
		}
		else {
			if (existflag == true) {
				protectcount = 20;//爆発エフェクトの時間
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (protectcount > 0) {
				DrawGraph(epx, epy, NormalEnemyGraphic[15], true);//破壊
			}
			existflag = false;
		}
	}
	else if (ekind == 100) {
		if (nowhp > 0) {
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, NormalEnemyGraphic[9], true);//機体
		}
		else {
			existflag = false;
		}
	}
	else {
		if (nowhp > 0) {
			if (bosscolor < 9) {
				DrawBox(72, 7, 71 + 400 * nowhp / maxhp, 15, Cr[bosscolor], true);// HPを描画
			}
			else {
				DrawBox(72, 7, 71 + 400 * nowhp / maxhp, 15, Cr[3], true);// HPを描画
			}
			if (protectcount <= 0 || count % 4 < 3)DrawGraph(epx, epy, BossGraphic[ekind - 11], true);//機体
		}
		else {
			if (existflag == true) {
				protectcount = 20;//爆発エフェクトの時間
				PlaySoundMem(SEbreak, DX_PLAYTYPE_BACK);//SE
			}
			else if (protectcount > 0) {
				DrawGraph(epx, epy, NormalEnemyGraphic[15], true);//破壊
			}
			existflag = false;
		}
	}

	/*弾の動きと描画*/
	for (i = 0; i < 10; i++) {
		if (esflag[i] == true) {
			switch (eskind[i]) {
			case 0://下
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 1://少し左
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 2://少し右
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 3://左
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 4://右
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 5://下（高速）
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 6://かなり左
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 7://かなり右
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 8://すごく左
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 9://すごく右
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[11], true);//弾
				break;
			case 10://下
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 18://少し左
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 19://少し右
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 13://左
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 14://右
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 15://下（高速）
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 16://かなり左
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 17://かなり右
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 11://すごく左
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 12://すごく右
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[12], true);//弾
				break;
			case 20://誘導炎弾
				esy[i] += 2;
				if (esx[i] < ppx)esx[i] += 2;
				else if (esx[i] > ppx)esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[InductionShotMotion(count)], true);//弾
				break;
			case 21://高速ビーム
				DrawBox(esx[i] + 2, epy + 30, esx[i] + 12, MAXMAPY, Cr[7], true);
				PlaySoundMem(SElaser, DX_PLAYTYPE_BACK);//SE
				break;
			case 22://体当たり
				break;
			case 23://誘導炎弾
				esy[i] += 2;
				if (esx[i] < ppx)esx[i] += 1;
				else if (esx[i] > ppx)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[InductionShotMotion(count)], true);//弾
				break;
			case 24://ノーマル敵
				break;
			case 25://バリアショット
				break;
			case 51://下
				esy[i] += 4;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 52://0.5左
				esy[i] += 4;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 53://0.5右
				esy[i] += 4;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 54://1左
				esy[i] += 4;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 55://1右
				esy[i] += 4;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 56://1.5左
				esy[i] += 4;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 57://1.5右
				esy[i] += 4;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 58://2左
				esy[i] += 4;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 59://2右
				esy[i] += 4;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 60://超高速下
				esy[i] += 10;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 61://高速下
				esy[i] += 7;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 62://高速0.5左
				esy[i] += 7;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 63://高速0.5右
				esy[i] += 7;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 64://高速1左
				esy[i] += 7;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 65://高速1右
				esy[i] += 7;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 66://高速1.5左
				esy[i] += 7;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 67://高速1.5右
				esy[i] += 7;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 68://高速2左
				esy[i] += 7;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			case 69://高速2右
				esy[i] += 7;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], true);//弾
				break;
			default:
				break;
			}
			if (esy[i] > MAXMAPY - 30 || esx[i] > MAXMAPX || esx[i] < -10)esflag[i] = false;// 端に到達時に消える
		}
	}

	/*時間経過による処理*/
	if (protectcount > -5)protectcount--;


}//ボスの動きに関する処理

/*ボスの動き(BossMove 内関数)*/
void Mode1Boss::Boss_Grad_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	/*色替え*/
	if (count % 400 == 0) {
		if (bosscolor == 4) {//橙>赤
			bosscolor = 0;
		}
		else if (bosscolor == 0) {//赤>黄
			bosscolor = 2;
		}
		else {//黄>橙
			bosscolor = 4;
		}
	}

	/*動きの記述*/
	if (move == 0) {
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			move = 1;
		}

		if (count % 80 < 35) {
			if (epx < MAXMAPX - 30)epx += 5;
			if (gamemode == 1) {//EASY
				epx -= 2;
			}
		}
		else {
			if (epx > 0)epx -= 5;
			if (gamemode == 1) {//EASY
				epx += 2;
			}
		}
	}
	else if (move == 1) {
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 2;
		}
	}
	else if (move == 2) {//通常攻撃1
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 12;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 0;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 0;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 0;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 0;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 0;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 0;
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 0;
				esx[6] = epx + 3;
				esy[6] = epy;
			}

			if (gamemode >= 3) {//HARD以上
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 1;
					esx[7] = epx;
					esy[7] = epy;
				}
				if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx;
					esy[8] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 3;
			if (gamemode == 4) {//UNKNOWN
				move = 7;
			}
			bosscount = 90;
		}
	}
	else if (move == 3) {//通常攻撃2
		if (epx < MAXMAPX - 30 && count % 2 == 0)epx += 1;
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 15;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 1;
				esx[0] = epx;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 1;
				esx[1] = epx;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 1;
				esx[2] = epx;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 1;
				esx[3] = epx;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 1;
				esx[4] = epx;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 1;
				esx[5] = epx;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 1;
				esx[6] = epx;
				esy[6] = epy;
			}

			if (gamemode == 4) {//UNKNOWN
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 0;
					esx[7] = epx;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = 4;
					esx[9] = epx;
					esy[9] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 4;
			bosscount = 90;
		}
	}
	else if (move == 4) {//通常攻撃3
		if (epx > 0 && count % 2 == 0)epx -= 1;
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			else if (gamemode == 4) {//UNKNOWN
				bosscount = 15;
			}

			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 2;
				esx[0] = epx;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 2;
				esx[1] = epx;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 2;
				esx[2] = epx;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 2;
				esx[3] = epx;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 2;
				esx[4] = epx;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = 2;
				esx[5] = epx;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = 2;
				esx[6] = epx;
				esy[6] = epy;
			}

			if (gamemode == 4) {//UNKNOWN
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 0;
					esx[7] = epx;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 1;
					esx[8] = epx;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = 3;
					esx[9] = epx;
					esy[9] = epy;
				}
			}
		}
		if (count % 300 == 0) {
			move = 5;
			bosscount = 90;
		}
	}
	else if (move == 5) {
		bosscount--;
		if (bosscount < 0) {
			bosscount = 300;
			move = 6;
		}

		if (count % 50 < 25) {
			if (epx < MAXMAPX - 30)epx += 4;
		}
		else {
			if (epx > 0)epx -= 4;
		}
	}
	else if (move == 6) {//誘導弾
		esflag[0] = true;
		eskind[0] = 20;
		esx[0] = epx;
		esy[0] = epy;
		bosscount = 120;
		move = 0;
	}
	else if (move == 7) {
		esflag[9] = true;
		eskind[9] = 20;
		esx[9] = epx;
		esy[9] = epy;
		bosscount = 120;
		move = 3;
	}
}

void Mode1Boss::Boss_Cron_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	int i, Cr = GetColor(35, 255, 255);//レーザーため用

	/*色替え*/
	if (count % 400 == 0) {
		if (bosscolor == 3) {//緑>紫
			bosscolor = 5;
		}
		else if (bosscolor == 5) {//紫>空
			bosscolor = 7;
		}
		else {//空>緑
			bosscolor = 3;
		}
	}

	/*動きの記述*/
	if (move < 10) {
		if (gamemode == 4 && nowhp < maxhp * 3 / 5) {//UNKNOWN && HP60%未満
			move = 10;
		}
	}

	if (move == 0) {//通常1 下に連射
		if (ppx < epx - 3) {
			if (epx > 0)epx -= 1;
		}
		else if (ppx > epx - 3) {
			if (epx < MAXMAPX - 30)epx += 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (gamemode == 1) {//EASY
				bosscount = 40;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 5;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 5;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 5;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 5;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 5;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 1;
			bosscount = 90;
		}
	}
	else if (move == 1) {//通常2 多方向
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			if (gamemode == 1) {//EASY
				bosscount = 150;
			}
			for (i = 0; i < 5; i++) {
				if (gamemode == 1) {//EASY
					if (i == 3)break;
				}
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (gamemode >= 3 && bosscount == 45) {//HARD以上
			for (i = 5; i < 10; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					if (i == 5) {
						eskind[i] = 0;
					}
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
	}
	else if (move == 2) {//レーザー前動き
		if (epx + 5 < ppx) {
			epx += 2;
			if (gamemode >= 3) {//HARD以上
				epx += 1;
			}
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
			if (gamemode >= 3) {//HARD以上
				epx -= 1;
			}
		}
		else {
			move = 3;
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD以上
				bosscount = 15;
			}
		}
	}
	else if (move == 3) {//レーザー前ため
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 4;
		}
	}
	else if (move == 4) {//レーザー
		bosscount--;
		esflag[0] = true;
		eskind[0] = 21;
		esx[0] = epx + 10;
		esy[0] = ppy;
		if (bosscount < 0) {
			esflag[0] = false;
			move = 5;
		}
	}
	else if (move == 5) {//真ん中に戻る
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 0;
		}
	}
	else if (move == 10) {//UNKNOWN　通常2 多方向
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;

			for (i = 0; i < 5; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}

		if (bosscount == 45) {
			for (i = 6; i < 10; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i - 5;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 11;
			bosscount = 90;
		}
	}
	else if (move == 11) {//UNKNOWN　レーザー前動き
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 12;
			bosscount = 12;
		}
	}
	else if (move == 12) {//UNKNOWN レーザー前ため
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 13;
		}
	}
	else if (move == 13) {//UNKNOWN レーザー
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 14;
		}
	}
	else if (move == 14) {//UNKNOWN 通常1 速射
		if (ppx < epx - 3) {
			if (epx > 0)epx -= 1;
		}
		else if (ppx > epx - 3) {
			if (epx < MAXMAPX - 30)epx += 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 20;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = 5;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = 5;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = 5;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = 5;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = 5;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 15;
			bosscount = 90;
		}
	}
	else if (move == 15) {//UNKNOWN　レーザー前動き
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 16;
			bosscount = 12;
		}
	}
	else if (move == 16) {//UNKNOWN レーザー前ため
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 17;
		}
	}
	else if (move == 17) {//UNKNOWN レーザー
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 18;
		}
	}
	else if (move == 18) {//UNKNOWN 通常3 9方向
		if (1) {}
		if (count % 200 < 50 || count % 200 > 150) {
			if (epx > 0)epx -= 2;
		}
		else {
			if (epx < MAXMAPX - 30)epx += 2;
		}
		bosscount--;
		if (bosscount < 0 && esflag[0] == false) {
			bosscount = 180;

			for (i = 0; i < 10; i++) {
				if (esflag[i] == false && i != 5) {
					esflag[i] = true;
					eskind[i] = i;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
	}
	else if (move == 19) {//UNKNOWN　レーザー前動き
		if (epx + 5 < ppx) {
			epx += 3;
		}
		else if (epx - 5 > ppx) {
			epx -= 3;
		}
		else {
			move = 20;
			bosscount = 12;
		}
	}
	else if (move == 20) {//UNKNOWN レーザー前ため
		bosscount--;
		DrawCircle(epx + 20, epy + 35, 7, Cr, true);
		if (bosscount < 0) {
			bosscount = 5;
			move = 21;
		}
	}
	else if (move == 21) {//UNKNOWN レーザー
		bosscount--;
		esflag[5] = true;
		eskind[5] = 21;
		esx[5] = epx + 10;
		esy[5] = ppy;
		if (bosscount < 0) {
			esflag[5] = false;
			move = 10;
		}
	}
}

void Mode1Boss::Boss_Erec_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode) {
	int i;
	/*色替え*/
	if (count % 400 == 0) {
		if (bosscolor == 2) {//黄>青
			bosscolor = 1;
		}
		else if (bosscolor == 1) {//青>紫
			bosscolor = 5;
		}
		else {//紫>黄
			bosscolor = 2;
		}
	}

	/*動きの記述*/
	if (move < 3) {
		if (gamemode == 4 && nowhp < maxhp / 2) {//UNKNOWN && HP50%未満
			move = 10;
		}
	}
	switch (move) {
	case 0://通常1 ランダム攻撃 右移動
		epx += 2;
		if (gamemode == 1) {//EASY
			epx -= 1;
		}
		if (epx > 400) {
			move = 1;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD以上
				bosscount = 15;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false && gamemode >= 3) {//HARD以上
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false && gamemode >= 3) {//HARD以上
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false && gamemode >= 3) {//HARD以上
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false && gamemode >= 3) {//HARD以上
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false && gamemode >= 3) {//HARD以上
				esflag[9] = true;
				eskind[9] = GetRand(7);
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
		break;
	case 1://通常1 ランダム攻撃 左移動
		epx -= 2;
		if (gamemode == 1) {//EASY
			epx += 1;
		}
		if (epx < 100) {
			move = 0;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (gamemode == 1) {//EASY
				bosscount = 60;
			}
			else if (gamemode >= 3) {//HARD以上
				bosscount = 15;
			}
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false && gamemode >= 3) {//HARD以上
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false && gamemode >= 3) {//HARD以上
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false && gamemode >= 3) {//HARD以上
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false && gamemode >= 3) {//HARD以上
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false && gamemode >= 3) {//HARD以上
				esflag[9] = true;
				eskind[9] = GetRand(7);
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 2;
			bosscount = 90;
		}
		break;
	case 2://通常2 多方向 右移動
		epx += 1;
		if (epx > 350) {
			move = 3;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			if (gamemode == 1) {//EASY
				bosscount = 120;
			}

			if (gamemode < 3) {//EASY || NORMAL
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 0;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[1] = 1;
					}
					else {//中央か右側
						eskind[1] = 2;
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[2] = 3;
					}
					else {//中央か右側
						eskind[2] = 4;
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[3] = 6;
					}
					else if (ppx - 5 > epx) {//右側にいる
						eskind[3] = 7;
					}
					else {//中央
						eskind[3] = 1;
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[4] = 8;
					}
					else if (ppx - 5 > epx) {//右側にいる
						eskind[4] = 9;
					}
					else {//中央
						eskind[4] = 3;
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}
			else {//HARD以上
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
		}
		if (count % 600 == 0) {
			move = 4;
			bosscount = 90;
		}
		break;
	case 3://通常2 多方向 左移動
		epx -= 1;
		if (epx < 150) {
			move = 2;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			if (gamemode == 1) {//EASY
				bosscount = 120;
			}

			if (gamemode < 3) {//EASY || NORMAL
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 0;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[1] = 1;
					}
					else {//中央か右側
						eskind[1] = 2;
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[2] = 3;
					}
					else {//中央か右側
						eskind[2] = 4;
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[3] = 6;
					}
					else if (ppx - 5 > epx) {//右側にいる
						eskind[3] = 7;
					}
					else {//中央
						eskind[3] = 1;
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					if (ppx + 5 < epx) {//左側にいる
						eskind[4] = 8;
					}
					else if (ppx - 5 > epx) {//右側にいる
						eskind[4] = 9;
					}
					else {//中央
						eskind[4] = 3;
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}
			else {//HARD以上
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

		}
		if (count % 600 == 0) {
			move = 4;
			bosscount = 90;
		}
		break;
	case 4://突進前準備			
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 8;
			bosscount = 25;
		}
		if (gamemode == 4) {//UNKNOWN 
			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
		}

		break;
	case 5://突進	
		epy += 5;
		if (gamemode == 2) {//NORMAL
			epy += 3;
		}
		else if (gamemode >= 3) {//HARD || UNKNOWN
			epy += 7;
		}
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 6;
		}
		break;
	case 6://突進戻り
		epy -= 3;
		if (gamemode >= 3) {//HARD以上
			epy -= 5;
		}
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 7;
		}
		break;
	case 7://中央に戻る
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 0;
		}
		break;
	case 8:
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 5;
		}
		break;
	case 10://UNKNOWN 通常2 多方向 右移動
		epx += 1;
		if (epx > 350) {
			move = 11;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 12;
			bosscount = 90;
		}
		break;
	case 11://UNKNOWN 通常2 多方向 左移動
		epx -= 1;
		if (epx < 150) {
			move = 10;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 90;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 12;
			bosscount = 90;
		}
		break;
	case 12://UNKNOWN 通常2 多方向 突進前準備	
		if (epx + 5 < ppx) {
			epx += 1;
		}
		else if (epx - 5 > ppx) {
			epx -= 1;
		}
		else {
			move = 13;
			bosscount = 15;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 60;
			for (i = 0; i < 9; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = i + 1;
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		break;
	case 13://UNKNOWN 突進前ため
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 14;
		}
		break;
	case 14://UNKNOWN 突進
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 15;
		}
		break;
	case 15://UNKNOWN 突進戻り
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 16;
		}
		break;
	case 16://UNKNOWN 中央に戻る
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 17;
		}
		break;
	case 17://UNKNOWN 通常1 ランダム攻撃 右移動
		epx += 2;
		if (epx > 400) {
			move = 18;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
		break;
	case 18://UNKNOWN 通常1 ランダム攻撃 左移動
		epx -= 2;
		if (epx < 100) {
			move = 17;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		if (count % 600 == 0) {
			move = 19;
			bosscount = 90;
		}
		break;
	case 19://UNKNOWN 通常1 ランダム攻撃 突進前準備	
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 20;
			bosscount = 15;
		}

		bosscount--;
		if (bosscount < 0) {
			bosscount = 10;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(7);
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(7);
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(7);
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(7);
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}
		}
		break;
	case 20://UNKNOWN 突進前ため
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 21;
		}
		break;
	case 21://UNKNOWN 突進
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 22;
		}
		break;
	case 22://UNKNOWN 突進戻り
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 23;
		}
		break;
	case 23://UNKNOWN 中央に戻る
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 24;
		}
		break;
	case 24://UNKNOWN 通常3 ランダム+4方向 右移動
		epx += 1;
		if (epx > 400) {
			move = 25;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 26;
			bosscount = 90;
		}
		break;
	case 25://UNKNOWN 通常3 ランダム+4方向 左移動
		epx -= 1;
		if (epx < 150) {
			move = 24;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		if (count % 600 == 0) {
			move = 26;
			bosscount = 90;
		}
		break;
	case 26://UNKNOWN 通常3 ランダム+4方向 突進前準備	
		if (epx + 5 < ppx) {
			epx += 2;
		}
		else if (epx - 5 > ppx) {
			epx -= 2;
		}
		else {
			move = 27;
			bosscount = 15;
		}
		bosscount--;
		if (bosscount < 0) {
			bosscount = 30;
			if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(7);
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(7);
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(7);
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(7);
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(7);
				esx[8] = epx + 3;
				esy[8] = epy;
			}

			for (i = 0; i < 4; i++) {
				if (esflag[i] == false) {
					esflag[i] = true;
					eskind[i] = GetRand(7);
					esx[i] = epx + 3;
					esy[i] = epy;
				}
			}
		}
		break;
	case 27://UNKNOWN 突進前ため
		bosscount--;
		if (bosscount < 0) {
			bosscount = 1;
			move = 28;
		}
		break;
	case 28://UNKNOWN 突進
		epy += 15;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy > MAXMAPY) {
			move = 29;
		}
		break;
	case 29://UNKNOWN 突進戻り
		epy -= 8;
		esflag[9] = true;
		eskind[9] = 22;
		esx[9] = epx + 10;
		esy[9] = epy + 10;
		if (epy < 31) {
			esflag[0] = false;
			epy = 30;
			move = 30;
		}
		break;
	case 30://UNKNOWN 中央に戻る
		if (epx < 245) {
			epx += 3;
		}
		else if (epx > 255) {
			epx -= 3;
		}
		else {
			bosscount = 30;
			move = 10;
		}
		break;
	default:
		move = 0;
		break;
	}
}

void Mode1Boss::Boss_Rain_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS) {
	int i, Cr = GetColor(35, 255, 255);//レーザーため用

	if (trueBOSS == true) {//本物
		/*色替え*/
		if (count % 250 == 0) {
			bosscolor = GetRand(7);//ランダム
		}

		/*動きの記述*/
		switch (move) {
		case 0:

			if (gamemode == 4) {//UNKNOWN
				move = 20;
			}

			epx += 2;
			if (gamemode == 1) {//EASY
				epx -= 1;
			}

			if (epx > 350) {
				move = 1;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				if (gamemode == 1) {//EASY
					bosscount = 100;
				}

				if (gamemode < 3) {//EASY || NORMAL
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 0;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					if (esflag[1] == false) {
						esflag[1] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[1] = 1;
						}
						else {//中央か右側
							eskind[1] = 2;
						}
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					if (esflag[2] == false) {
						esflag[2] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[2] = 3;
						}
						else {//中央か右側
							eskind[2] = 4;
						}
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					if (esflag[3] == false) {
						esflag[3] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[3] = 6;
						}
						else if (ppx - 5 > epx) {//右側にいる
							eskind[3] = 7;
						}
						else {//中央
							eskind[3] = 1;
						}
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					if (esflag[4] == false) {
						esflag[4] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[4] = 8;
						}
						else if (ppx - 5 > epx) {//右側にいる
							eskind[4] = 9;
						}
						else {//中央
							eskind[4] = 3;
						}
						esx[4] = epx + 3;
						esy[4] = epy;
					}
				}
				else {//HARD以上
					for (i = 0; i < 7; i++) {
						if (esflag[i] == false) {
							esflag[i] = true;
							if (i == 5) {
								eskind[i] = 9;
							}
							else if (i == 6) {
								eskind[i] = 8;
							}
							else {
								eskind[i] = i;
							}
							esx[i] = epx + 3;
							esy[i] = epy;
						}
					}
				}

			}
			if (count % 600 == 0) {
				move = 2;
				bosscount = 90;
			}
			break;
		case 1:
			epx -= 2;
			if (gamemode == 1) {//EASY
				epx += 1;
			}

			if (epx < 150) {
				move = 0;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 60;
				if (gamemode == 1) {//EASY
					bosscount = 100;
				}

				if (gamemode < 3) {//EASY || NORMAL
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 0;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					if (esflag[1] == false) {
						esflag[1] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[1] = 1;
						}
						else {//中央か右側
							eskind[1] = 2;
						}
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					if (esflag[2] == false) {
						esflag[2] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[2] = 3;
						}
						else {//中央か右側
							eskind[2] = 4;
						}
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					if (esflag[3] == false) {
						esflag[3] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[3] = 6;
						}
						else if (ppx - 5 > epx) {//右側にいる
							eskind[3] = 7;
						}
						else {//中央
							eskind[3] = 1;
						}
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					if (esflag[4] == false) {
						esflag[4] = true;
						if (ppx + 5 < epx) {//左側にいる
							eskind[4] = 8;
						}
						else if (ppx - 5 > epx) {//右側にいる
							eskind[4] = 9;
						}
						else {//中央
							eskind[4] = 3;
						}
						esx[4] = epx + 3;
						esy[4] = epy;
					}
				}
				else {//HARD以上
					for (i = 0; i < 7; i++) {
						if (esflag[i] == false) {
							esflag[i] = true;
							if (i == 5) {
								eskind[i] = 9;
							}
							else if (i == 6) {
								eskind[i] = 8;
							}
							else {
								eskind[i] = i;
							}
							esx[i] = epx + 3;
							esy[i] = epy;
						}
					}
				}

			}

			if (count % 600 == 0) {
				move = 2;
				bosscount = 90;
			}
			break;
		case 2:
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 3;
				bosscount = 25;
			}
			break;
		case 3:
			bosscount--;
			if (bosscount < 0) {
				move = 4;
				bosscount = 60;
			}
			break;
		case 4:
			esflag[0] = true;
			eskind[0] = 20;
			esx[0] = epx;
			esy[0] = epy;
			bosscount = 90;
			move = 5;
			break;
		case 5:
			bosscount--;
			if (bosscount < 0) {
				move = 6;
				bosscount = 60;
			}
			break;
		case 6://レーザー準備
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 7;
				bosscount = 50;
				if (gamemode >= 3) {//HARD以上
					bosscount = 25;
				}
			}
			break;
		case 7:
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 8;
			}
			break;
		case 8:
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 9;
				bosscount = 30;
			}
			break;
		case 9://突進準備
			bosscount--;
			if (bosscount < 0) {
				if (epx + 5 < ppx) {
					epx += 2;
				}
				else if (epx - 5 > ppx) {
					epx -= 2;
				}
				else {
					move = 10;
					bosscount = 25;
				}
			}
			break;
		case 10:
			if (gamemode == 1) {//EASY
				epy += 5;
			}
			else if (gamemode == 2) {//NORMAL
				epy += 8;
			}
			else if (gamemode == 3) {//HARD
				epy += 12;
			}
			else if (gamemode == 4) {//UNKNOWN
				epy += 15;
			}
			esflag[0] = true;
			eskind[0] = 22;
			esx[0] = epx + 10;
			esy[0] = epy + 10;
			if (epy > MAXMAPY) {
				move = 11;
			}
			break;
		case 11:
			epy -= 5;
			if (gamemode != 1) {//NORMAL || HARD || UNKNOWN
				epy -= 3;
			}
			esflag[0] = true;
			eskind[0] = 22;
			esx[0] = epx + 10;
			esy[0] = epy + 10;
			if (epy < 71) {
				esflag[0] = false;
				epy = 70;
				move = 12;
			}
			break;
		case 12:
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 13;
			}
			break;
		case 13:
			epx += 2;
			if (epx > 400) {
				move = 14;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 70;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 15;
				bosscount = 60;
			}
			break;
		case 14:
			epx -= 2;
			if (epx < 100) {
				move = 13;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 70;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 15;
				bosscount = 60;
			}
			break;
		case 15:
			move = 0;
			break;
		case 20://UNKNOWN 7方向　右移動
			if (nowhp < 60) {
				move = 39;
			}
			epx += 2;
			if (epx > 400) {
				move = 21;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 22;
				bosscount = 60;
			}
			break;
		case 21://UNKNOWN 7方向　左移動
			if (nowhp < 60) {
				move = 39;
			}
			epx -= 2;
			if (epx < 100) {
				move = 20;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 22;
				bosscount = 60;
			}
			break;
		case 22://UNKNOWN 7方向　突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 23;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			break;
		case 23://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 24;
			}
			break;
		case 24://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 25;
			}
			break;
		case 25://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 26;
			}
			break;
		case 26://UNKNOWN 中央に戻る
			if (nowhp < 60) {
				move = 39;
			}
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 27;
			}
			break;
		case 27://UNKNOWN 左右から連射
			if (nowhp < 60) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 8;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 6;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 3;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 1;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}

				if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 9;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 7;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 4;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 2;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 28;
				bosscount = 60;
			}
			break;
		case 28://UNKNOWN 突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 29;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 29://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 30;
			}
			break;
		case 30://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 31;
			}
			break;
		case 31://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 32;
			}
			break;
		case 32://UNKNOWN 中央に戻る
			if (nowhp < 60) {
				move = 39;
			}
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 33;
			}
			break;
		case 33://UNKNOWN 中央から左右へ連射
			if (nowhp < 60) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 5;
					esx[0] = epx + 3;
					esy[0] = epy;
				}

				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 2;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 4;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 7;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 9;
					esx[4] = epx + 3;
					esy[4] = epy;
				}

				if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 1;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 3;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 6;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 8;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 34;
				bosscount = 60;
			}
			break;
		case 34://UNKNOWN 突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 35;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 35://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 36;
			}
			break;
		case 36://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 37;
			}
			break;
		case 37://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 38;
			}
			break;
		case 38://UNKNOWN 中央に戻る
			if (nowhp < 60) {
				move = 39;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 20;
			}
			break;
		case 39://UNKNOWN 中央に戻る
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 40;
			}
			break;
		case 40://UNKNOWN 4方向 右移動
			if (nowhp < 25) {
				move = 60;
			}

			epx += 2;
			if (epx > 400) {
				move = 41;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 42;
				bosscount = 60;
			}
			break;
		case 41://UNKNOWN 4方向 左移動
			if (nowhp < 25) {
				move = 60;
			}

			epx -= 2;
			if (epx < 100) {
				move = 40;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 42;
				bosscount = 60;
			}
			break;
		case 42://UNKNOWN 4方向 レーザー前移動
			if (epx + 5 < ppx) {
				epx += 1;
			}
			else if (epx - 5 > ppx) {
				epx -= 1;
			}
			else {
				move = 43;
				bosscount = 10;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 90;
				for (i = 0; i < 4; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 1;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			else if (bosscount == 45) {
				for (i = 4; i < 8; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i - 3;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}
			break;
		case 43://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 44;
			}
			break;
		case 44://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 45;
				bosscount = 30;
			}
			break;
		case 45://UNKNOWN 中央に戻る
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 46;
			}
			break;
		case 46://UNKNOWN ランダム攻撃
			if (nowhp < 25) {
				move = 60;
			}

			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 23;//誘導弾
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 23;//誘導弾
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 23;//誘導弾
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 23;//誘導弾
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 23;//誘導弾
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 23;//誘導弾
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 23;//誘導弾
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 23;//誘導弾
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 23;//誘導弾
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 47;
				bosscount = 60;
			}
			break;
		case 47://UNKNOWN ランダム攻撃 レーザー前移動
			if (epx + 5 < ppx) {
				epx += 1;
			}
			else if (epx - 5 > ppx) {
				epx -= 1;
			}
			else {
				move = 48;
				bosscount = 10;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 23;//誘導弾
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 23;//誘導弾
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 23;//誘導弾
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 23;//誘導弾
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 23;//誘導弾
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 23;//誘導弾
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 23;//誘導弾
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 23;//誘導弾
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 23;//誘導弾
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 48://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 49;
			}
			break;
		case 49://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 50;
				bosscount = 30;
			}
			break;
		case 50://UNKNOWN 中央に戻る
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 51;
			}
			break;
		case 51://UNKNOWN 自機方向狙い連射
			if (nowhp < 25) {
				move = 60;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 8;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 6;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 3;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 8;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 6;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 3;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 8;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 6;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 3;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 9;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 7;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 4;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 9;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 7;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 4;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 9;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 7;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 4;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 10;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4);
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4);
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4);
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4);
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4);
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4);
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4);
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4);
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4);
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}
			if (count % 600 == 0) {
				move = 52;
				bosscount = 60;
			}
			break;
		case 52://UNKNOWN レーザー前移動
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 53;
				bosscount = 10;
			}
			break;
		case 53://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 54;
			}
			break;
		case 54://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 55;
				bosscount = 30;
			}
			break;
		case 55://UNKNOWN 中央に戻る
			if (nowhp < 25) {
				move = 60;
			}

			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 40;
			}
			break;
		case 60://UNKNOWN 7方向　右移動
			epx += 2;
			if (epx > 400) {
				move = 61;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 5) {
							eskind[5] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 62;
				bosscount = 60;
			}
			break;
		case 61://UNKNOWN 7方向　左移動
			epx -= 2;
			if (epx < 100) {
				move = 60;
			}

			bosscount--;
			if (bosscount < 0 && esflag[0] == false) {
				bosscount = 60;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 5) {
							eskind[5] = 7;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 62;
				bosscount = 60;
			}
			break;
		case 62://UNKNOWN レーザー前移動
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 63;
				bosscount = 6;
			}
			break;
		case 63://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 64;
			}
			break;
		case 64://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 65;
				bosscount = 30;
			}
			break;
		case 65://UNKNOWN ランダム攻撃 右移動
			epx += 2;
			if (epx > 400) {
				move = 66;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 20;//誘導弾
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 20;//誘導弾
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 20;//誘導弾
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 20;//誘導弾
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 20;//誘導弾
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 20;//誘導弾
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 20;//誘導弾
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 20;//誘導弾
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 20;//誘導弾
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 67;
				bosscount = 60;
			}
			break;
		case 66://UNKNOWN ランダム攻撃 左移動
			epx -= 2;
			if (epx < 100) {
				move = 65;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(10);
					if (eskind[0] == 10) {
						eskind[0] = 20;//誘導弾
					}
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(10);
					if (eskind[1] == 10) {
						eskind[1] = 20;//誘導弾
					}
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(10);
					if (eskind[2] == 10) {
						eskind[2] = 20;//誘導弾
					}
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(10);
					if (eskind[3] == 10) {
						eskind[3] = 20;//誘導弾
					}
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(10);
					if (eskind[4] == 10) {
						eskind[4] = 20;//誘導弾
					}
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(10);
					if (eskind[5] == 10) {
						eskind[5] = 20;//誘導弾
					}
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(10);
					if (eskind[6] == 10) {
						eskind[6] = 20;//誘導弾
					}
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(10);
					if (eskind[7] == 10) {
						eskind[7] = 20;//誘導弾
					}
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(10);
					if (eskind[8] == 10) {
						eskind[8] = 20;//誘導弾
					}
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 67;
				bosscount = 60;
			}
			break;
		case 67://UNKNOWN 突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 68;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 68://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 69;
			}
			break;
		case 69://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 70;
			}
			break;
		case 70://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 71;
			}
			break;
		case 71://UNKNOWN 中央に戻る
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 72;
			}
			break;
		case 72://UNKNOWN 3方向連射
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 30;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 3;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 3;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 3;
					esx[2] = epx + 3;
					esy[2] = epy;
				}

				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 0;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 0;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 0;
					esx[5] = epx + 3;
					esy[5] = epy;
				}

				if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 4;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 4;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 4;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 600 == 0) {
				move = 73;
				bosscount = 60;
			}
			break;
		case 73://UNKNOWN レーザー前移動
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 74;
				bosscount = 6;
			}
			break;
		case 74://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 75;
			}
			break;
		case 75://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 76;
				bosscount = 30;
			}
			break;
		case 76://UNKNOWN 8方向+誘導弾
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0 && esflag[5] == false) {
				bosscount = 90;
				for (i = 0; i < 9; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i;
						if (i == 0) {
							eskind[0] = 9;
						}
						else if (i == 5) {
							eskind[5] = 20;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 600 == 0) {
				move = 77;
				bosscount = 60;
			}
			break;
		case 77://UNKNOWN 突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 78;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 78://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 79;
			}
			break;
		case 79://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 80;
			}
			break;
		case 80://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 81;
			}
			break;
		case 81://UNKNOWN 中央に戻る
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 82;
			}
			break;
		case 82://UNKNOWN 自機方向狙い連射
			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 8;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 6;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 3;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 8;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 6;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 3;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 8;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 6;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 3;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 20;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 9;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 7;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 4;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 9;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 7;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 4;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 9;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 7;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 4;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 10;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4);
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4);
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4);
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4);
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4);
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4);
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4);
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4);
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4);
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}
			if (count % 600 == 0) {
				move = 83;
				bosscount = 60;
			}
			break;
		case 83://UNKNOWN レーザー前移動
			if (epx + 5 < ppx) {
				epx += 3;
			}
			else if (epx - 5 > ppx) {
				epx -= 3;
			}
			else {
				move = 84;
				bosscount = 6;
			}
			break;
		case 84://UNKNOWN レーザー前ため
			bosscount--;
			DrawCircle(epx + 20, epy + 35, 7, Cr, true);
			if (bosscount < 0) {
				bosscount = 5;
				move = 54;
			}
			break;
		case 85://UNKNOWN レーザー
			bosscount--;
			esflag[9] = true;
			eskind[9] = 21;
			esx[9] = epx + 10;
			esy[9] = ppy;
			if (bosscount < 0) {
				esflag[9] = false;
				move = 86;
				bosscount = 30;
			}
			break;
		case 86://UNKNOWN 突進前移動
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			else {
				move = 87;
				bosscount = 15;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9);
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9);
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9);
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9);
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9);
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9);
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9);
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9);
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9);
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}
			break;
		case 87://UNKNOWN 突進前ため
			bosscount--;
			if (bosscount < 0) {
				move = 88;
			}
			break;
		case 88://UNKNOWN 突進
			epy += 18;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy > MAXMAPY) {
				move = 89;
			}
			break;
		case 89://UNKNOWN 突進戻り
			epy -= 8;
			esflag[9] = true;
			eskind[9] = 22;
			esx[9] = epx + 10;
			esy[9] = epy + 10;
			if (epy < 71) {
				esflag[9] = false;
				epy = 70;
				move = 81;
			}
			break;
		case 90://UNKNOWN 中央に戻る
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				bosscount = 30;
				move = 60;
			}
			break;
		default:
			move = 0;
			break;
		}
	}
	else {//分身
		switch (move) {
		case 100://出現
			epy -= 2;
			if (epy < 30) {
				epy = 30;
				move = 1;
			}
			break;
		case 1://5方向 右移動
			epx += 2;
			if (epx > 400) {
				move = 2;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 150;
				if (gamemode == 1) {//EASY
					bosscount = 210;
				}
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 75 && gamemode >= 3) {//HARD || UNKNOWN
				for (i = 5; i < 10; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 5;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 700 == 0) {
				move = 3;
				bosscount = 90;
			}
			break;
		case 2://5方向 左移動
			epx -= 2;
			if (epx < 100) {
				move = 1;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 150;
				if (gamemode == 1 || gamemode == 3) {//EASY || HARD
					bosscount = 210;
				}

				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 75 && gamemode >= 3) {//HARD || UNKNOWN
				for (i = 5; i < 10; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 5;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 700 == 0) {
				move = 3;
				bosscount = 90;
			}
			break;
		case 3://ランダム
			bosscount--;
			if (bosscount < 0) {
				bosscount = 30;
				if (gamemode == 1) {//EASY
					bosscount = 90;
				}
				else if (gamemode >= 3) {//HARD以上
					bosscount = 20;
				}

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 10;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 10;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 10;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 10;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false && gamemode >= 3) {//HARD以上
					esflag[5] = true;
					eskind[5] = GetRand(9) + 10;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false && gamemode >= 3) {//HARD以上
					esflag[6] = true;
					eskind[6] = GetRand(9) + 10;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false && gamemode >= 3) {//HARD以上
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false && gamemode >= 3) {//HARD以上
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false && gamemode >= 3) {//HARD以上
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 1;
				bosscount = 90;
			}
			break;
		case 10://UNKNOWN 7方向 右移動
			epx += 2;
			if (count % 700 == 0) {
				move = 12;
				bosscount = 90;
			}

			if (epx > 400) {
				move = 11;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 200;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						if (i == 5) {
							eskind[i] = 17;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 100) {
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}
			break;
		case 11://UNKNOWN 7方向 左移動
			epx -= 2;
			if (count % 700 == 0) {
				move = 12;
				bosscount = 90;
			}

			if (epx < 100) {
				move = 10;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 200;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 10;
						if (i == 5) {
							eskind[i] = 17;
						}
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (bosscount == 100) {
				if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}
			break;
		case 12://UNKNOWN 右から連射
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 12;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 17;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 14;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 19;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 18;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 13;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 16;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 11;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 13;
				bosscount = 90;
			}
			break;
		case 13://UNKNOWN 左から連射
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 11;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 16;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 13;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 19;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 14;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 17;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 12;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 14://UNKNOWN ランダム	
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 3;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 3;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 10;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 10;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 10;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 10;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 10;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 10;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 10;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 10;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 10;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
				else if (esflag[9] == false) {
					esflag[9] = true;
					eskind[9] = GetRand(9) + 10;
					esx[9] = epx + 3;
					esy[9] = epy;
				}
			}

			if (count % 700 == 0) {
				move = 10;
				bosscount = 90;
			}
			break;
		case -1:
		case -2:
		case -3:
		case -10:
		case -11:
		case -12:
		case -13:
		case -14:
			bosscount--;
			if (bosscount < 0) {
				move *= -1;//戻す
			}
			break;
		default:
			move = 1;
			break;
		}
	}
}

void Mode1Boss::Boss_StagatoteSP_Move(int *errorcheck, int count, int ppx, int ppy, int gamemode, bool trueBOSS) {
	int i;
	int Cr = GetColor(240, 240, 240);
	if (trueBOSS == true) {//本体
		if (nowhp < maxhp / 2 && move < 20) {//HP半分を切ると行動が変わる
			move = 20;
		}

		switch (move) {

			/*HP1/2以上*/
		case 0://ワープ 右
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 400;
				move = 1;
			}
			break;
		case 1://ワープ 左
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 100;
				move = 2;
			}
			break;
		case 2://ワープ 中央
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				epx = 250;
				move = 3;
			}
			break;
		case 3://5方向弾 右移動
			epx += 2;
			if (epx > 400) {
				move = 4;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 5;
				bosscount = 90;
			}
			break;
		case 4://5方向弾 左移動
			epx -= 2;
			if (epx < 100) {
				move = 3;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 5; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 5;
				bosscount = 90;
			}
			break;
		case 5://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 6;
			break;
		case 6://自機狙いランダム(左右動き)
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//ボスが右側
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 7;
				bosscount = 90;
			}
			break;
		case 7://バリアショット
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 8;
			break;
		case 8://中央に戻る
			if (epx < 245) {
				epx += 3;
			}
			else if (epx > 255) {
				epx -= 3;
			}
			else {
				move = 9;
			}
			break;
		case 9://右から連射
			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 59;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 57;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 55;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 53;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 52;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 54;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 56;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 58;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 300 == 0) {
				move = 10;
				bosscount = 90;
			}
			break;
		case 10://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 11;
			break;
		case 11://左から連射
			bosscount--;
			if (bosscount < 0) {
				bosscount = 10;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 58;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 56;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 54;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 52;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 53;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 55;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = 57;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = 59;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 300 == 0) {
				move = 12;
				bosscount = 90;
			}
			break;
		case 12://低速ランダム 左移動
			epx -= 2;
			if (epx < 100) {
				move = 13;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(8) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(8) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(8) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(8) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(8) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(8) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(8) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(8) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(8) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 13://低速ランダム 右移動
			epx += 2;
			if (epx > 400) {
				move = 12;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(8) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(8) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(8) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(8) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(8) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(8) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(8) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(8) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(8) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 14;
				bosscount = 90;
			}
			break;
		case 14://バリアショット
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 0;
			break;
			/*HP1/2を切った時に一回のみ使用(全ての難易度)*/
		case 20://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 21;
			break;
		case 21://バリアショット左
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 22;
				bosscount = 10;
			}
			break;
		case 22://バリアショット右
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 23;
				bosscount = 10;
			}
		case 23://バリアショット自機
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				move = 24;
				bosscount = 10;
			}
			break;
		case 24://難易度による行動チェンジ
			if (gamemode == 3) {//HARD
				move = 30;
				bosscount = 15;
			}
			else if (gamemode == 4) {//UNKNOUN
				move = 50;
				bosscount = 15;
			}
			else {
				move = -1;//エラー
			}
			break;
			/*HARD HP1/2未満*/
		case 30://自機狙いランダム(左右移動)
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//ボスが右側
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 31;
				bosscount = 90;
			}
			break;
		case 31://バリアショット
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 32;
			break;
		case 32://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 33;
			break;
		case 33://自機狙い下
			if (epx + 5 < ppx) {
				epx += 2;
			}
			else if (epx - 5 > ppx) {
				epx -= 2;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 61;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 61;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 61;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 61;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = 61;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = 61;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
			}
			if (count % 360 == 0) {
				move = 34;
				bosscount = 90;
			}
			break;
		case 34://バリアショット
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 35;
			break;
		case 35://空き高速5方向弾 左
			epx -= 2;
			if (epx < 150) {
				move = 36;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 64;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 65;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 68;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 69;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 37;
				bosscount = 90;
			}
			break;
		case 36://空き高速5方向弾 右
			epx += 2;
			if (epx > 350) {
				move = 35;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = 61;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = 64;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = 65;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = 68;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = 69;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 37;
				bosscount = 90;
			}
			break;
		case 37://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 38;
			break;
		case 38://ランダムショット 右
			epx += 2;
			if (epx > 400) {
				move = 39;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(18) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(18) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(18) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(18) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(18) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(18) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(18) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(18) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(18) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 1800 == 0) {
				move = 40;
				bosscount = 90;
			}
			break;
		case 39://ランダムショット 左
			epx -= 2;
			if (epx < 100) {
				move = 38;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 15;
				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(18) + 51;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(18) + 51;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(18) + 51;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(18) + 51;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(18) + 51;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(18) + 51;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(18) + 51;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(18) + 51;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(18) + 51;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 1800 == 0) {
				move = 40;
				bosscount = 90;
			}
			break;
		case 40://バリアショット
			epx = ppx;
			esflag[9] = true;
			eskind[9] = 25;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 30;
			break;
			/*UNKNOWN HP1/2未満*/
		case 50://7方向弾 右
			epx += 2;
			if (epx > 400) {
				move = 51;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 52;
				bosscount = 5;
			}
			break;
		case 51://7方向弾 左
			epx -= 2;
			if (epx < 100) {
				move = 50;
			}
			bosscount--;
			if (bosscount < 0) {
				bosscount = 50;
				for (i = 0; i < 7; i++) {
					if (esflag[i] == false) {
						esflag[i] = true;
						eskind[i] = i + 51;
						esx[i] = epx + 3;
						esy[i] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 52;
				bosscount = 5;
			}
			break;
		case 52://バリアショット 中央
			bosscount--;
			if (bosscount < 0) {
				epx = 250;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 53;
			}
			break;
		case 53://バリアショット 自機
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 54;
			}
			break;
		case 54://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 55;
			break;
		case 55://高速ランダム 左
			epx -= 2;
			if (epx < 100) {
				move = 56;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 60;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 60;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 60;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 60;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 60;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 60;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 60;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 60;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 60;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 57;
				bosscount = 90;
			}
			break;
		case 56://高速ランダム 右
			epx += 2;
			if (epx > 400) {
				move = 55;
			}

			bosscount--;
			if (bosscount < 0) {
				bosscount = 20;

				if (esflag[0] == false) {
					esflag[0] = true;
					eskind[0] = GetRand(9) + 60;
					esx[0] = epx + 3;
					esy[0] = epy;
				}
				else if (esflag[1] == false) {
					esflag[1] = true;
					eskind[1] = GetRand(9) + 60;
					esx[1] = epx + 3;
					esy[1] = epy;
				}
				else if (esflag[2] == false) {
					esflag[2] = true;
					eskind[2] = GetRand(9) + 60;
					esx[2] = epx + 3;
					esy[2] = epy;
				}
				else if (esflag[3] == false) {
					esflag[3] = true;
					eskind[3] = GetRand(9) + 60;
					esx[3] = epx + 3;
					esy[3] = epy;
				}
				else if (esflag[4] == false) {
					esflag[4] = true;
					eskind[4] = GetRand(9) + 60;
					esx[4] = epx + 3;
					esy[4] = epy;
				}
				else if (esflag[5] == false) {
					esflag[5] = true;
					eskind[5] = GetRand(9) + 60;
					esx[5] = epx + 3;
					esy[5] = epy;
				}
				else if (esflag[6] == false) {
					esflag[6] = true;
					eskind[6] = GetRand(9) + 60;
					esx[6] = epx + 3;
					esy[6] = epy;
				}
				else if (esflag[7] == false) {
					esflag[7] = true;
					eskind[7] = GetRand(9) + 60;
					esx[7] = epx + 3;
					esy[7] = epy;
				}
				else if (esflag[8] == false) {
					esflag[8] = true;
					eskind[8] = GetRand(9) + 60;
					esx[8] = epx + 3;
					esy[8] = epy;
				}
			}

			if (count % 900 == 0) {
				move = 57;
				bosscount = 90;
			}
			break;
		case 57://バリアショット 左
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 58;
			}
			break;
		case 58://バリアショット 右
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 59;
			}
			break;
		case 59://バリアショット 自機
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 60;
			}
			break;
		case 60://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 61;
			break;
		case 61://自機狙いランダム
			if (count % 200 < 50 || count % 200 > 150) {
				if (epx > 0)epx -= 2;
			}
			else {
				if (epx < MAXMAPX - 30)epx += 2;
			}

			bosscount--;
			if (bosscount < 0) {
				if (epx - 5 > ppx) {//ボスが右側
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 59;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 57;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 55;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 59;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 57;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 55;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 59;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 57;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 55;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else if (epx + 35 < ppx) {
					bosscount = 30;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = 58;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = 56;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = 54;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = 58;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = 56;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = 54;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = 58;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = 56;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = 54;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
				else {
					bosscount = 15;
					if (esflag[0] == false) {
						esflag[0] = true;
						eskind[0] = GetRand(4) + 51;
						esx[0] = epx + 3;
						esy[0] = epy;
					}
					else if (esflag[1] == false) {
						esflag[1] = true;
						eskind[1] = GetRand(4) + 51;
						esx[1] = epx + 3;
						esy[1] = epy;
					}
					else if (esflag[2] == false) {
						esflag[2] = true;
						eskind[2] = GetRand(4) + 51;
						esx[2] = epx + 3;
						esy[2] = epy;
					}
					else if (esflag[3] == false) {
						esflag[3] = true;
						eskind[3] = GetRand(4) + 51;
						esx[3] = epx + 3;
						esy[3] = epy;
					}
					else if (esflag[4] == false) {
						esflag[4] = true;
						eskind[4] = GetRand(4) + 51;
						esx[4] = epx + 3;
						esy[4] = epy;
					}
					else if (esflag[5] == false) {
						esflag[5] = true;
						eskind[5] = GetRand(4) + 51;
						esx[5] = epx + 3;
						esy[5] = epy;
					}
					else if (esflag[6] == false) {
						esflag[6] = true;
						eskind[6] = GetRand(4) + 51;
						esx[6] = epx + 3;
						esy[6] = epy;
					}
					else if (esflag[7] == false) {
						esflag[7] = true;
						eskind[7] = GetRand(4) + 51;
						esx[7] = epx + 3;
						esy[7] = epy;
					}
					else if (esflag[8] == false) {
						esflag[8] = true;
						eskind[8] = GetRand(4) + 51;
						esx[8] = epx + 3;
						esy[8] = epy;
					}
				}
			}

			if (count % 900 == 0) {
				move = 62;
				bosscount = 90;
			}
			break;
		case 62://バリアショット 右
			bosscount--;
			if (bosscount < 0) {
				epx = 400;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 63;
			}
			break;
		case 63://バリアショット 左
			bosscount--;
			if (bosscount < 0) {
				epx = 100;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 64;
			}
			break;
		case 64://バリアショット 自機
			bosscount--;
			if (bosscount < 0) {
				epx = ppx;
				esflag[9] = true;
				eskind[9] = 25;
				esx[9] = epx + 3;
				esy[9] = epy;
				bosscount = 15;
				move = 65;
			}
			break;
		case 65://ノーマル敵出現
			epx = 250;
			esflag[9] = true;
			eskind[9] = 24;
			esx[9] = epx + 3;
			esy[9] = epy;
			bosscount = 15;
			move = 50;
			break;
		default:
			bosscount = 10;
			move = 0;
			break;
		}
	}
	else {//補助パーツ
		bosscount--;
		if (bosscount < 0) {
			bosscount = 15;
			if (esflag[0] == false) {
				esflag[0] = true;
				eskind[0] = GetRand(18) + 51;
				esx[0] = epx + 3;
				esy[0] = epy;
			}
			else if (esflag[1] == false) {
				esflag[1] = true;
				eskind[1] = GetRand(18) + 51;
				esx[1] = epx + 3;
				esy[1] = epy;
			}
			else if (esflag[2] == false) {
				esflag[2] = true;
				eskind[2] = GetRand(18) + 51;
				esx[2] = epx + 3;
				esy[2] = epy;
			}
			else if (esflag[3] == false) {
				esflag[3] = true;
				eskind[3] = GetRand(18) + 51;
				esx[3] = epx + 3;
				esy[3] = epy;
			}
			else if (esflag[4] == false) {
				esflag[4] = true;
				eskind[4] = GetRand(18) + 51;
				esx[4] = epx + 3;
				esy[4] = epy;
			}
			else if (esflag[5] == false) {
				esflag[5] = true;
				eskind[5] = GetRand(18) + 51;
				esx[5] = epx + 3;
				esy[5] = epy;
			}
			else if (esflag[6] == false) {
				esflag[6] = true;
				eskind[6] = GetRand(18) + 51;
				esx[6] = epx + 3;
				esy[6] = epy;
			}
			else if (esflag[7] == false) {
				esflag[7] = true;
				eskind[7] = GetRand(18) + 51;
				esx[7] = epx + 3;
				esy[7] = epy;
			}
			else if (esflag[8] == false) {
				esflag[8] = true;
				eskind[8] = GetRand(18) + 51;
				esx[8] = epx + 3;
				esy[8] = epy;
			}
			else if (esflag[9] == false) {
				esflag[9] = true;
				eskind[9] = GetRand(18) + 51;
				esx[9] = epx + 3;
				esy[9] = epy;
			}
		}
	}
}
/*ボスの動きここまで*/

int Mode1Boss::BossHP(int damage) {
	nowhp -= damage;
	if (nowhp < 0)nowhp = 0;
	if (damage > 0) {//ダメージを受けている
		protectcount = 12;
	}
	return nowhp;
}

void Mode1Boss::BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*protect = protectcount;
	for (int i = 0; i < 10; i++) {
		shotx[i] = esx[i];
		shoty[i] = esy[i];
		shotkind[i] = eskind[i];
		shotflag[i] = esflag[i];
	}
}

int Mode1Boss::BossMoveSet(int n, bool changeflag) {
	if (changeflag == true) {
		move = n;
	}
	else {
		if (n >= 1) {//反転させる(分身のみ適用)
			move *= -1;
			switch (n) {
			case 1://EASY
			case 2://NORMAL
				bosscount = 90;//止めている時間
				protectcount = 90;
				break;
			case 3://HARD
				bosscount = 60;//止めている時間
				protectcount = 60;
				break;
			case 4://UNKNOWN
				bosscount = 45;//止めている時間
				protectcount = 45;
				break;
			default:
				break;
			}
		}
	}
	return move;
}

int Mode1Boss::BossPositionCheck(int *enemyx, int *enemyy) {
	*enemyx = epx;
	*enemyy = epy;
	return eskind[9];
}

void Mode1Boss::BossPositionMove(int movex, int movey) {
	epx = movex;
	epy = movey;
}

/*ステージ16(ボスラッシュ:Stagatote_SPステージ)の敵出現用関数と補助パーツの本体同時移動*/
void BossStage_NormalEnemyAppear(int *errorcheck, Mode1Enemy Enemy[], Mode1Boss Boss[]) {
	int epx = 0, epy = 0, eskind = 0;
	eskind = Boss[0].BossPositionCheck(&epx, &epy);
	Boss[1].BossPositionMove(epx + 3, epy);//補助パーツの移動
	if (eskind == 24) {//ノーマル敵出現
		for (int i = 0; i < 7; i++) {
			Enemy[i].AppearEnemy(100 + i * 50, 70, 8);
		}
	}
	else if (eskind == 25) {//バリアショット
		if (Enemy[10].EnemyExistCheck() == false) {
			Enemy[10].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[11].EnemyExistCheck() == false) {
			Enemy[11].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[12].EnemyExistCheck() == false) {
			Enemy[12].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[13].EnemyExistCheck() == false) {
			Enemy[13].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[14].EnemyExistCheck() == false) {
			Enemy[14].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[15].EnemyExistCheck() == false) {
			Enemy[15].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[16].EnemyExistCheck() == false) {
			Enemy[16].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[17].EnemyExistCheck() == false) {
			Enemy[17].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[18].EnemyExistCheck() == false) {
			Enemy[18].AppearEnemy(epx + 10, epy + 35, 10);
		}
		else if (Enemy[19].EnemyExistCheck() == false) {
			Enemy[19].AppearEnemy(epx + 10, epy + 35, 10);
		}
	}
	else {//それ以外は関係なし
		return;
	}

	Boss[0].BossShotFlagFALSE(9);//一回のみ撃つようにする
}

void NormalStage_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]);

unsigned int StageClear(int *ErrorCheck, int stage, unsigned int point, Mode1Player Player, int gameflag, int gamecount, int gamemode, int itemnum);

int Player1mode(int *ErrorCheck, int gamemode);

void Tutoreal_StartPrepare(int stage, int *errorcheck, Mode1Enemy Enemy[]);

int Tutoreal(int *ErrorCheck);



