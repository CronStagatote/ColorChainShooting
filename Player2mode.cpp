#include "DxLib.h"
#include"Color_Chain_Shooting.h"
/////---**2Player mode**---/////

#define MAX1PlayerENEMY 40

#define MAXMAPX1 300
#define MAXMAPX2 610
#define MAXMAPYALL 360

#define NEXTKEYTIME2 60

/////**敵機用関数(ノーマル)**/////
class Mode2Enemy {
private:
	int epx, epy;//x座標,y座標
	bool existflag;//存在しているか
	bool esflag;//弾が打たれているか
	int ekind;//種類
	int eskind;//狙う場所
	int esx, esy;//弾の座標
	int nextshotcount;//次の弾発射までの間隔

public:
	void StartSet();//最初の初期化処理
	void AppearEnemy(int x, int y, int kind);//敵出現用関数
	void NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy, int No);//敵の動きに関する処理(ノーマル敵)
																								 /*敵機の座標と種類,敵の弾の座標,存在フラグを返す*/
	void EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag);
	void BreakEnemy();//敵を倒したときの処理
	bool EnemyExistCheck() { return existflag; };//存在するかどうか
	int EnemyKindCheck() { return ekind; };//種類は何か
	void EnemyShotFlagFALSE() { esflag = FALSE; };//弾が撃たれていない状態にする
};


/////**敵機用関数(ボス)**/////
class Mode2Boss {
private:
	int epx, epy;//ボス自体のx座標,y座標
	int ekind;//種類(11:grad 12:cron 13:erec 14:rain 15:staga)*stagaは2PlayerModeでのみ出現するので欠番
	int esx[7], esy[7], eskind[7];//弾の座標と種類
	bool esflag[7];//弾が存在しているか
	int move;//動き方の指定
	int bosscount, protectcount;//時間制御,無敵時間
	int maxhp, nowhp;//最大、現在HP(0で消滅)

public:
	void StartSet(int stage, int No);//最初の初期化処理と出現
							 /*敵の動きに関する処理(ボス敵)*/
	void BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int No, Mode2Enemy NormalEnemy[]);
	int BossHP(int damage);//ボスの残りHP(0で消滅を表す) 
						   /*敵機の座標,敵の種類,敵の弾の座標,弾の種類,無敵時間を返す*/
	void BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect);
	void BossShotFlagFALSE(int n) { esflag[n] = FALSE; };//弾が撃たれていない状態にする
};


/////**自機用関数**/////
class Mode2Player {
private:
	int ppx, ppy;//x座標,y座標
	int php, damagetime;//自機HP,ダメージ後の復帰時間
	bool psflag[3][3];//弾が打たれているか
	int pskind[3];//現在の弾の種類(9:何もなし)
	int psx[3][3], psy[3][3];//それぞれの弾の座標
	bool keyflag[3];//キーが押されているか
	int keyflagcount[3];//キーが押されていない状態になるまでの時間
	int pscombocount[3], pscombotimes[3];//コンボ数と倍率
	int point;//得点
	int PlayerNo;//Player1か、2か

public:
	void StartSet(int no);//最初の初期化処理
	int PlayerHP(int damage);//プレイヤーのHPに関する処理
	void PlayerMove1(int *errorcheck, int MyGraphicint, int PlayerShotGraphic[]);//プレイヤー1の動きに関する処理
	void PlayerMove2(int *errorcheck, int MyGraphicint, int PlayerShotGraphic[]);//プレイヤー2の動きに関する処理
	void PlayerShotColor(int PlayerShotKind[]);//弾の種類を返す関数
	void PlayerShotCombo(int ShotComboNum[]);//コンボ数を返す関数
	void NormalStage_CollisionDetection(int *errorcheck, Mode2Enemy Enemy[], int stage);//当たり判定とダメージ
	void PointPlus(int plus) { point += plus; };//得点追加
	int GetPoint() { return point; };//得点を返す
	void PlayerPosition(int *x, int *y) { *x = ppx; *y = ppy; };//場所を返す
	void BossStage_CollisionDetection(int *errorcheck, Mode2Boss Boss[],int No);//当たり判定とダメージ
};


/////**関数集**/////

 /*ゲーム処理用*/
void Mode2Player::StartSet(int no) {
	int i, j;
	PlayerNo = no;
	if (no == 1 || no == 3) {
		ppx = 140;
		if (no == 1) {
			php = 30;//HPの初期値
			point = 0;
		}
	}
	else if (no == 2 || no == 4) {
		ppx = 450;
		if (no == 2) {
			php = 30;//HPの初期値
			point = 0;
		}
	}
	ppy = 320;
	for (i = 0; i < 3; i++) {
		pskind[i] = 9;
		pscombocount[i] = 0;
		pscombotimes[i] = 1;
		if (CheckHitKeyAll() == 0) {//キーが押されていない
			keyflag[i] = FALSE;
			keyflagcount[i] = 0;
		}
		else {
			keyflag[i] = TRUE;
			keyflagcount[i] = NEXTKEYTIME2;
		}
		for (j = 0; j < 3; j++) {
			psflag[i][j] = FALSE;
			psx[i][j] = ppx + 12;
			psy[i][j] = ppy;
		}
	}
	damagetime = 0;

}//最初の処理

int Mode2Player::PlayerHP(int damage) {
	point -= damage;
	if (damage > 0) {//ダメージを受けている
		damagetime = 60;
	}
	return point;
}//2Player ModeではHPの代わりに得点が減る

void Mode2Player::PlayerMove1(int *errorcheck, int MyGraphic, int PlayerShotGraphic[]) {
	int i, j;
	if (ppx > MAXMAPX1 + 100 || ppx < -100)*errorcheck = 2;//左右へ行きすぎ

														  /*弾のキーチェック*/
	if (CheckHitKey(KEY_INPUT_Q) == 0) {
		keyflag[0] = FALSE;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_W) == 0) {
		keyflag[1] = FALSE;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_E) == 0) {
		keyflag[2] = FALSE;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == TRUE) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = FALSE;
		}
	}

	/*ボタンと対応する動き*/
	if (php > 0) {//HPが尽きていないなら
		if (CheckHitKey(KEY_INPUT_B) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX1 - 30)ppx = MAXMAPX1 - 30;
		}
		if (CheckHitKey(KEY_INPUT_C) == 1) {
			ppx -= 3;
			if (ppx < 0)ppx = 0;
		}
		if (CheckHitKey(KEY_INPUT_Q) == 1 && keyflag[0] == FALSE) {
			keyflag[0] = TRUE;
			keyflagcount[0] = NEXTKEYTIME2;
			if (psflag[0][0] == FALSE) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = TRUE;
			}
			else if (psflag[0][1] == FALSE) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = TRUE;
			}
			else if (psflag[0][2] == FALSE) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_W) == 1 && keyflag[1] == FALSE) {
			keyflag[1] = TRUE;
			keyflagcount[1] = NEXTKEYTIME2;
			if (psflag[1][0] == FALSE) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = TRUE;
			}
			else if (psflag[1][1] == FALSE) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = TRUE;
			}
			else if (psflag[1][2] == FALSE) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_E) == 1 && keyflag[2] == FALSE) {
			keyflag[2] = TRUE;
			keyflagcount[2] = NEXTKEYTIME2;
			if (psflag[2][0] == FALSE) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = TRUE;
			}
			else if (psflag[2][1] == FALSE) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = TRUE;
			}
			else if (psflag[2][2] == FALSE) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = TRUE;
			}
		}
	}

	/*グラフィック表示*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, TRUE);//倒されていないなら表示
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == TRUE) {
				psy[i][j] -= 5;//自機の弾の動き
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], TRUE);
				if (psy[i][j] < -50) {
					psflag[i][j] = FALSE;
				}
			}
		}
	}

	/*時間経過による処理*/
	if (damagetime >= -5)damagetime--;

}//プレイヤー1の動きに関する処理(弾も)

void Mode2Player::PlayerMove2(int *errorcheck, int MyGraphic, int PlayerShotGraphic[]) {
	int i, j;
	if (ppx > MAXMAPX2 + 100 || ppx < -100)*errorcheck = 2;//左右へ行きすぎ

														   /*弾のキーチェック*/
	if (CheckHitKey(KEY_INPUT_I) == 0) {
		keyflag[0] = FALSE;
		keyflagcount[0] = 0;
	}
	if (CheckHitKey(KEY_INPUT_O) == 0) {
		keyflag[1] = FALSE;
		keyflagcount[1] = 0;
	}
	if (CheckHitKey(KEY_INPUT_P) == 0) {
		keyflag[2] = FALSE;
		keyflagcount[2] = 0;
	}

	for (i = 0; i < 3; i++) {
		if (keyflag[i] == TRUE) {
			keyflagcount[i]--;
			if (keyflagcount[i] < 0)keyflag[i] = FALSE;
		}
	}

	/*ボタンと対応する動き*/
	if (php > 0) {//HPが尽きていないなら
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			ppx += 3;
			if (ppx > MAXMAPX2 - 30)ppx = MAXMAPX2 - 30;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			ppx -= 3;
			if (ppx < MAXMAPX1 + 10)ppx = MAXMAPX1 + 10;
		}
		if (CheckHitKey(KEY_INPUT_I) == 1 && keyflag[0] == FALSE) {
			keyflag[0] = TRUE;
			keyflagcount[0] = NEXTKEYTIME2;
			if (psflag[0][0] == FALSE) {
				psy[0][0] = ppy;
				psx[0][0] = ppx + 12;
				psflag[0][0] = TRUE;
			}
			else if (psflag[0][1] == FALSE) {
				psy[0][1] = ppy;
				psx[0][1] = ppx + 12;
				psflag[0][1] = TRUE;
			}
			else if (psflag[0][2] == FALSE) {
				psy[0][2] = ppy;
				psx[0][2] = ppx + 12;
				psflag[0][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_O) == 1 && keyflag[1] == FALSE) {
			keyflag[1] = TRUE;
			keyflagcount[1] = NEXTKEYTIME2;
			if (psflag[1][0] == FALSE) {
				psy[1][0] = ppy;
				psx[1][0] = ppx + 12;
				psflag[1][0] = TRUE;
			}
			else if (psflag[1][1] == FALSE) {
				psy[1][1] = ppy;
				psx[1][1] = ppx + 12;
				psflag[1][1] = TRUE;
			}
			else if (psflag[1][2] == FALSE) {
				psy[1][2] = ppy;
				psx[1][2] = ppx + 12;
				psflag[1][2] = TRUE;
			}
		}
		if (CheckHitKey(KEY_INPUT_P) == 1 && keyflag[2] == FALSE) {
			keyflag[2] = TRUE;
			keyflagcount[2] = NEXTKEYTIME2;
			if (psflag[2][0] == FALSE) {
				psy[2][0] = ppy;
				psx[2][0] = ppx + 12;
				psflag[2][0] = TRUE;
			}
			else if (psflag[2][1] == FALSE) {
				psy[2][1] = ppy;
				psx[2][1] = ppx + 12;
				psflag[2][1] = TRUE;
			}
			else if (psflag[2][2] == FALSE) {
				psy[2][2] = ppy;
				psx[2][2] = ppx + 12;
				psflag[2][2] = TRUE;
			}
		}
	}

	/*グラフィック表示*/
	if (php > 0 && (damagetime < 1 || damagetime % 5 < 3)) {
		DrawGraph(ppx, ppy, MyGraphic, TRUE);//倒されていないなら表示
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (psflag[i][j] == TRUE) {
				psy[i][j] -= 5;//自機の弾の動き
				DrawGraph(psx[i][j], psy[i][j], PlayerShotGraphic[pskind[i]], TRUE);
				if (psy[i][j] < -50) {
					psflag[i][j] = FALSE;
				}
			}
		}
	}

	/*時間経過による処理*/
	if (damagetime >= -5)damagetime--;

}//プレイヤー2の動きに関する処理(弾も)

void Mode2Player::PlayerShotColor(int PlayerShotKind[]) {
	for (int i = 0; i < 3; i++) {
		PlayerShotKind[i] = pskind[i];
	}
}//弾の種類を返す関数

void Mode2Player::PlayerShotCombo(int ShotComboNum[]) {
	for (int i = 0; i < 3; i++) {
		ShotComboNum[i] = pscombocount[i];
	}
}//コンボ数を返す関数

 /*当たり判定とダメージ*/
void Mode2Player::NormalStage_CollisionDetection(int *errorcheck, Mode2Enemy Enemy[], int stage) {
	int epx = 0, epy = 0, enemykind = 9;//敵機の座標と種類
	int esx = 0, esy = 0;//敵の弾の座標
	int enemyxnum = 0, enemyynum = 0;
	bool enemyflag = FALSE, enemyshotflag = FALSE;//存在フラグ
	int i, j, k;
	bool breakflag = FALSE;

	for (i = 0; i < MAX1PlayerENEMY; i++) {
		breakflag = FALSE;
		/*敵機の情報取得*/
		Enemy[i].EnemyInfoReturn(&epx, &epy, &enemykind, &esx, &esy, &enemyflag, &enemyshotflag);
		if (enemyflag == TRUE && enemykind == 9)*errorcheck = 4;//存在しているのに存在していない
		if (enemyflag == TRUE) {//敵機が存在しているとき
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 3; k++) {
					if (psx[j][k] + 5 < epx + 28 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 28 && psy[j][k] + 16>epy + 4) {
						/*弾が当たった時*/
						if (pskind[j] == enemykind) {//前回と同じ
							pscombocount[j] += 1;//コンボ数を1増やす
							pscombotimes[j] *= 3;//コンボ倍率を上げる

						}
						else if (enemykind == 8) {//白（コンボに加算されない）だった
							point += 5;//ポイント加算
						}
						else {//特に特殊なことはなかった
							pskind[j] = enemykind;//弾を変える
							pscombocount[j] = 1;//コンボ数を１にする
							pscombotimes[j] = 1;
						}

						/*共通処理*/
						Enemy[i].BreakEnemy();//敵を破壊
						psflag[j][k] = FALSE;//弾を消す
						point += pscombotimes[j] + pscombocount[j];//ポイント加算
						breakflag = TRUE;
					}
				}
				if (breakflag == TRUE)break;
			}
		}
		if (enemyshotflag == TRUE) {//敵の弾が存在しているとき
			if (esx + 10 < ppx + 32 && esx + 22 > ppx + 8 && esy + 10 < ppy + 32 && esy + 22 > ppy + 4) {
				/*敵の弾がぶつかった*/
				if (damagetime <= 0)PlayerHP(10);//ダメージ
				Enemy[i].EnemyShotFlagFALSE();
			}
		}
	}

	/*時間経過による処理*/
	if (damagetime >= -5)damagetime--;

}//当たり判定確認用関数

void Mode2Player::BossStage_CollisionDetection(int *errorcheck, Mode2Boss Boss[], int No) {
	int epx = 0, epy = 0, enemykind = 9;//敵機の座標と種類
	int esx[5] = {}, esy[5] = {}, eskind[5] = {};//敵の弾の座標
	int protecttime = 0;//無敵時間
	bool enemyshotflag[5] = {};//存在フラグ
	int i, j, k;
	No--;

	/*敵機の情報取得*/
	Boss[No].BossInfoReturn(&epx, &epy, &enemykind, esx, esy, eskind, enemyshotflag, &protecttime);
	if (Boss[No].BossHP(0) > 0 && enemykind == 9)*errorcheck = 4;//存在しているのに存在していない
	if (Boss[No].BossHP(0) > 0) {//敵機が存在しているとき
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (psflag[j][k] == TRUE) {//弾が存在しているとき
					if (psx[j][k] + 5 < epx + 35 && psx[j][k] + 11 > epx + 4 && psy[j][k]<epy + 35 && psy[j][k] + 16 > epy + 4) {
						/*弾が当たった時*/
						if (protecttime <= 0) {
							Boss[No].BossHP(1);//1ダメージを与える
							point += 5;
							if (Boss[No].BossHP(0) == 0) {
								point += 1000;
							}
						}
						psflag[j][k] = FALSE;
					}
				}
			}
		}
	}
	for (i = 0; i < 5; i++) {
		if (enemyshotflag[i] == TRUE) {//敵の弾が存在しているとき
			if (esx[i] + 10 < ppx + 32 && esx[i] + 22 > ppx + 8 && esy[i] + 10 < ppy + 32 && esy[i] + 22 > ppy + 4) {
				/*敵の弾がぶつかった*/
				if (damagetime <= 0) {
					if (eskind[i] >= 20) {
						PlayerHP(10);//得点が減る
						Boss[No].BossShotFlagFALSE(i);
					}
					else {//通常のダメージ
						PlayerHP(10);//得点が減る
						Boss[No].BossShotFlagFALSE(i);
					}
				}
			}
		}
	}

}//当たり判定確認用関数

void Mode2Enemy::StartSet() {//最初の処理
	epx = 0;
	epy = 0;
	existflag = FALSE;
	esflag = FALSE;
	ekind = 9;
	eskind = 0;
	esx = epx;
	esy = epy;
	nextshotcount = 90 + GetRand(180);
}

void Mode2Enemy::AppearEnemy(int x, int y, int kind) {//出現場所と種類を決めて呼び出す
	epx = x;
	epy = y;
	existflag = TRUE;
	esflag = FALSE;
	ekind = kind;
	eskind = 0;
	esx = epx;
	esy = epy;
}//敵出現用関数

void Mode2Enemy::NormalEnemyMove(int *errorcheck, int NormalEnemyGraphic[], int count, int ppx, int ppy,int No) {
	/*グラフィック*/
	if (esflag == TRUE) {//弾が存在するなら
		DrawGraph(esx, esy, NormalEnemyGraphic[11], TRUE);//弾
	}

	if (existflag == TRUE) {//機体が存在するなら
		DrawGraph(epx, epy, NormalEnemyGraphic[ekind], TRUE);//機体

		/*移動*/
		if (count % 3 == 0) {
			if (count % 60 < 30) {
				epx += 1;
			}
			else {
				epx -= 1;
			}
		}

		/*弾撃ち*/
		nextshotcount--;
		if (nextshotcount < 0) {//一定時間ごとに発射
			nextshotcount = 100 + GetRand(250);//時間のリセット
			if (esflag == FALSE) {//弾が撃たれていないなら
				esx = epx;
				esy = epy;
				if (ekind != 6)esflag = TRUE;//弾を撃つ
				 /*狙う場所*/
				switch (ekind) {
				case 0://赤
					eskind = 1;
					break;
				case 1://青
					if (ppx < epx - 150) {//150以上左
						eskind = 8;
					}
					else if (ppx < epx - 100) {//100以上左
						eskind = 6;
					}
					else if (ppx < epx - 50) {//50以上左
						eskind = 4;
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
					if (ppx < epx - 150) {//150以上左
						eskind = 4;
					}
					else if (ppx < epx - 100) {//100以上左
						eskind = 2;
					}
					else if (ppx < epx - 50) {//50以上左
						eskind = 1;
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
					if (ppx < epx - 150) {//150以上左
						eskind = 6;
					}
					else if (ppx < epx - 80) {//80以上左
						eskind = 4;
					}
					else if (ppx < epx - 30) {//30以上左
						eskind = 2;
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
					if (No == 1) {
						if (CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_B) == 1) {
							if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
						else if (CheckHitKey(KEY_INPUT_B) == 1) {
							if (ppx < epx - 150) {//150以上左
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 1;
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
						else if (CheckHitKey(KEY_INPUT_C) == 1) {
							if (ppx < epx - 150) {//150以上左
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 4;
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
							if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
					}
					else if (No == 2) {
						if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && CheckHitKey(KEY_INPUT_LEFT) == 1) {
							if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
						else if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
							if (ppx < epx - 150) {//150以上左
								eskind = 4;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 2;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 1;
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
							if (ppx < epx - 150) {//150以上左
								eskind = 8;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 6;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 4;
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
							if (ppx < epx - 150) {//150以上左
								eskind = 6;
							}
							else if (ppx < epx - 100) {//100以上左
								eskind = 4;
							}
							else if (ppx < epx - 50) {//50以上左
								eskind = 2;
							}
							else if (ppx > epx + 150) {//150以上右
								eskind = 7;
							}
							else if (ppx > epx + 100) {//100以上右
								eskind = 5;
							}
							else if (ppx > epx + 50) {//50以上右
								eskind = 3;
							}
							else {
								eskind = 1;
							}
						}
					}
					break;
				case 8://白
					if (ppx < epx - 150) {//150以上左
						eskind = 6;
					}
					else if (ppx < epx - 80) {//80以上左
						eskind = 4;
					}
					else if (ppx < epx - 30) {//30以上左
						eskind = 2;
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
				}

				
			}
		}
	}

	if (esflag == TRUE) {//弾が撃たれているとき
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
		}
		
		if (No == 1) {
			if (esy > MAXMAPYALL - 30 || esx > MAXMAPX1 - 16 || esx < -10)esflag = FALSE;// 端に到達時に消える
		}
		else if (No == 2) {
			if (esy > MAXMAPYALL - 30 || esx > MAXMAPX2 - 16 || esx < MAXMAPX1 + 10)esflag = FALSE;// 端に到達時に消える
		}
		
	}

}//敵の動きと弾に関する処理(ノーマル敵) 

void Mode2Enemy::EnemyInfoReturn(int *enemyx, int *enemyy, int *enemykind, int *shotx, int *eshoty, bool *enemyflag, bool *shotflag) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*shotx = esx;
	*eshoty = esy;
	*enemyflag = existflag;
	*shotflag = esflag;
}//敵機の座標,敵の弾の座標,存在フラグを返す

void Mode2Enemy::BreakEnemy() {
	existflag = FALSE;
}//敵を倒したときの処理

void Mode2Boss::StartSet(int stage,int No) {
	if (No == 1) {
		epx = 135;
	}
	else if (No == 2) {
		epx = 445;
	}
	epy = 30;
	move = 0;
	switch (stage) {
	case 5:
		ekind = 15;
		maxhp = 50;
		break;
	default://それ以外がボスステージになることはない
		return;
	}
	nowhp = maxhp;
	for (int i = 0; i < 5; i++) {
		esx[i] = epx;
		esy[i] = epy;
		eskind[i] = 0;
		esflag[i] = FALSE;
	}
	bosscount = 150;//時間制御
	protectcount = 120;//無敵時間
}//最初の初期化処理と出現

void Mode2Boss::BossMove(int *errorcheck, int NormalEnemyGraphic[], int BossGraphic[], int count, int ppx, int ppy, int No, Mode2Enemy NormalEnemy[]) {
	int i;
	//色作成
	int Cr = GetColor(128, 128, 128);//灰(文字用)
	int HPCr = GetColor(15, 255, 15);//緑（HP用）

	/*ステージチェックと名前表示、敵の動きなど*/
	switch (ekind) {
	case 11://2PlayerModeではなし		
		break;
	case 12://2PlayerModeではなし		
		break;
	case 13://2PlayerModeではなし		
		break;
	case 14://2PlayerModeではなし	
		break;
	case 15:
		if (No == 1) {
			DrawFormatString(5, 3, Cr, "Staga:HP");
			if (nowhp > 0) {//存在するときのみ動く
				if (move == 0) {
					epx += 2;
					if (epx > 250) {
						move = 1;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 1) {
					epx -= 2;
					if (epx < 50) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 2) {
					if (epx < 130) {
						epx += 2;
					}
					else if (epx > 145) {
						epx -= 2;
					}
					else {
						move = 3;
						bosscount = 15;
					}
				}
				else if (move == 3) {
					bosscount--;
					if (bosscount < 0) {
						move = 4;
						bosscount = 30;
					}
				}
				else if (move == 4) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(55 + i * 40, 70, 8);
					}
					move = 5;
				}
				else if (move == 5) {
					epx += 1;
					if (epx > 250) {
						move = 6;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[1] = 1;
							}
							else {//中央か右側
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[2] = 3;
							}
							else {//中央か右側
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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
					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 6) {
					epx -= 1;
					if (epx < 50) {
						move = 5;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[1] = 1;
							}
							else {//中央か右側
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[2] = 3;
							}
							else {//中央か右側
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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

					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 7) {
					if (epx < 130) {
						epx += 2;
					}
					else if (epx > 145) {
						epx -= 2;
					}
					else {
						if (nowhp < 25) {
							move = 8;
						}
						else {
							move = 0;
						}
						bosscount = 90;
					}
				}
				else if (move == 8) {
					epx += 3;
					if (epx > 250) {
						move = 9;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 10;
						bosscount = 90;
					}
				}
				else if (move == 9) {
					epx -= 3;
					if (epx < 50) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}

						if (count % 600 == 0) {
							move = 10;
							bosscount = 90;
						}
					}
				}
				else if (move == 10) {
					if (epx < 130) {
						epx += 3;
					}
					else if (epx > 145) {
						epx -= 3;
					}
					else {
						move = 11;
						bosscount = 15;
					}
				}
				else if (move == 11) {
					bosscount--;
					if (bosscount < 0) {
						move = 12;
						bosscount = 30;
					}
				}
				else if (move == 12) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(55 + i * 40, 70, 8);
					}
					move = 13;
				}
				else if (move == 13) {
					esflag[5] = TRUE;
					eskind[5] = 12;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 14;
				}
				else if (move == 14) {
					bosscount--;
					if (bosscount < 0) {
						move = 15;
					}
				}
				else if (move == 15) {
					esflag[6] = TRUE;
					eskind[6] = 17;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 16;
				}
				else if (move == 16) {
					bosscount--;
					if (bosscount < 0) {
						move = 17;
					}
				}
				else if (move == 17) {
					esflag[0] = TRUE;
					eskind[0] = 14;
					esx[0] = epx + 3;
					esy[0] = epy;
					bosscount = 10;
					move = 18;
				}
				else if (move == 18) {
					bosscount--;
					if (bosscount < 0) {
						move = 19;
					}
				}
				else if (move == 19) {
					esflag[1] = TRUE;
					eskind[1] = 19;
					esx[1] = epx + 3;
					esy[1] = epy;
					bosscount = 10;
					move = 20;
				}
				else if (move == 20) {
					bosscount--;
					if (bosscount < 0) {
						move = 21;
					}
				}
				else if (move == 21) {
					esflag[2] = TRUE;
					eskind[2] = 5;
					esx[2] = epx + 3;
					esy[2] = epy;
					bosscount = 10;
					move = 22;
				}
				else if (move == 22) {
					bosscount--;
					if (bosscount < 0) {
						move = 23;
					}
				}
				else if (move == 23) {
					esflag[3] = TRUE;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
					bosscount = 10;
					move = 24;
				}
				else if (move == 24) {
					bosscount--;
					if (bosscount < 0) {
						move = 25;
					}
				}
				else if (move == 25) {
					esflag[4] = TRUE;
					eskind[4] = 13;
					esx[4] = epx + 3;
					esy[4] = epy;
					bosscount = 10;
					move = 26;
				}
				else if (move == 26) {
					bosscount--;
					if (bosscount < 0) {
						move = 27;
					}
				}
				else if (move == 27) {
					esflag[5] = TRUE;
					eskind[5] = 16;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 28;
				}
				else if (move == 28) {
					bosscount--;
					if (bosscount < 0) {
						move = 29;
					}
				}
				else if (move == 29) {
					esflag[6] = TRUE;
					eskind[6] = 11;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 30;
				}
				else if (move == 30) {
					epx += 3;
					if (epx > 250) {
						move = 31;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 31) {
					epx -= 3;
					if (epx < 50) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 32) {
					epx += 2;
					if (epx > 250) {
						move = 33;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}
				else if (move == 33) {
					epx -= 3;
					if (epx < 50) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}

			}
		}
		else if (No == 2) {
			DrawFormatString(320, 3, Cr, "Staga:HP");
			if (nowhp > 0) {//存在するときのみ動く
				if (move == 0) {
					epx += 2;
					if (epx > 570) {
						move = 1;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 1) {
					epx -= 2;
					if (epx < 365) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 90;
						for (i = 0; i < 5; i++) {
							if (esflag[i] == FALSE) {
								esflag[i] = TRUE;
								eskind[i] = i + 10;
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
				else if (move == 2) {
					if (epx < 440) {
						epx += 2;
					}
					else if (epx > 455) {
						epx -= 2;
					}
					else {
						move = 3;
						bosscount = 15;
					}
				}
				else if (move == 3) {
					bosscount--;
					if (bosscount < 0) {
						move = 4;
						bosscount = 30;
					}
				}
				else if (move == 4) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(365 + i * 40, 70, 8);
					}
					move = 5;
				}
				else if (move == 5) {
					epx += 1;
					if (epx > 570) {
						move = 6;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[1] = 1;
							}
							else {//中央か右側
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[2] = 3;
							}
							else {//中央か右側
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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
					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 6) {
					epx -= 1;
					if (epx < 365) {
						move = 5;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 100;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 0;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[1] = 1;
							}
							else {//中央か右側
								eskind[1] = 2;
							}
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							if (ppx + 5 < epx) {//左側にいる
								eskind[2] = 3;
							}
							else {//中央か右側
								eskind[2] = 4;
							}
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
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
						if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
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

					if (count % 600 == 0) {
						move = 7;
						bosscount = 90;
					}
				}
				else if (move == 7) {
					if (epx < 440) {
						epx += 2;
					}
					else if (epx > 455) {
						epx -= 2;
					}
					else {
						if (nowhp < 25) {
							move = 8;
						}
						else {
							move = 0;
						}
						bosscount = 90;
					}
				}
				else if (move == 8) {
					epx += 3;
					if (epx > 570) {
						move = 9;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 10;
						bosscount = 90;
					}
				}
				else if (move == 9) {
					epx -= 3;
					if (epx < 365) {
						move = 0;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}

						if (count % 600 == 0) {
							move = 10;
							bosscount = 90;
						}
					}
				}
				else if (move == 10) {
					if (epx < 440) {
						epx += 3;
					}
					else if (epx > 455) {
						epx -= 3;
					}
					else {
						move = 11;
						bosscount = 15;
					}
				}
				else if (move == 11) {
					bosscount--;
					if (bosscount < 0) {
						move = 12;
						bosscount = 30;
					}
				}
				else if (move == 12) {
					for (i = 0; i < 5; i++) {
						NormalEnemy[i].AppearEnemy(365 + i * 40, 70, 8);
					}
					move = 13;
				}
				else if (move == 13) {
					esflag[5] = TRUE;
					eskind[5] = 12;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 14;
				}
				else if (move == 14) {
					bosscount--;
					if (bosscount < 0) {
						move = 15;
					}
				}
				else if (move == 15) {
					esflag[6] = TRUE;
					eskind[6] = 17;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 16;
				}
				else if (move == 16) {
					bosscount--;
					if (bosscount < 0) {
						move = 17;
					}
				}
				else if (move == 17) {
					esflag[0] = TRUE;
					eskind[0] = 14;
					esx[0] = epx + 3;
					esy[0] = epy;
					bosscount = 10;
					move = 18;
				}
				else if (move == 18) {
					bosscount--;
					if (bosscount < 0) {
						move = 19;
					}
				}
				else if (move == 19) {
					esflag[1] = TRUE;
					eskind[1] = 19;
					esx[1] = epx + 3;
					esy[1] = epy;
					bosscount = 10;
					move = 20;
				}
				else if (move == 20) {
					bosscount--;
					if (bosscount < 0) {
						move = 21;
					}
				}
				else if (move == 21) {
					esflag[2] = TRUE;
					eskind[2] = 5;
					esx[2] = epx + 3;
					esy[2] = epy;
					bosscount = 10;
					move = 22;
				}
				else if (move == 22) {
					bosscount--;
					if (bosscount < 0) {
						move = 23;
					}
				}
				else if (move == 23) {
					esflag[3] = TRUE;
					eskind[3] = 18;
					esx[3] = epx + 3;
					esy[3] = epy;
					bosscount = 10;
					move = 24;
				}
				else if (move == 24) {
					bosscount--;
					if (bosscount < 0) {
						move = 25;
					}
				}
				else if (move == 25) {
					esflag[4] = TRUE;
					eskind[4] = 13;
					esx[4] = epx + 3;
					esy[4] = epy;
					bosscount = 10;
					move = 26;
				}
				else if (move == 26) {
					bosscount--;
					if (bosscount < 0) {
						move = 27;
					}
				}
				else if (move == 27) {
					esflag[5] = TRUE;
					eskind[5] = 16;
					esx[5] = epx + 3;
					esy[5] = epy;
					bosscount = 10;
					move = 28;
				}
				else if (move == 28) {
					bosscount--;
					if (bosscount < 0) {
						move = 29;
					}
				}
				else if (move == 29) {
					esflag[6] = TRUE;
					eskind[6] = 11;
					esx[6] = epx + 3;
					esy[6] = epy;
					bosscount = 10;
					move = 30;
				}
				else if (move == 30) {
					epx += 3;
					if (epx > 570) {
						move = 31;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 31) {
					epx -= 3;
					if (epx < 365) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = GetRand(9) + 10;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = GetRand(9) + 10;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = GetRand(9) + 10;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = GetRand(9) + 10;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = GetRand(9) + 10;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 32;
						bosscount = 90;
					}
				}
				else if (move == 32) {
					epx += 2;
					if (epx > 570) {
						move = 33;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
						else if (esflag[5] == FALSE) {
							esflag[5] = TRUE;
							eskind[5] = GetRand(9) + 10;
							esx[5] = epx + 3;
							esy[5] = epy;
						}
						else if (esflag[6] == FALSE) {
							esflag[6] = TRUE;
							eskind[6] = GetRand(9) + 10;
							esx[6] = epx + 3;
							esy[6] = epy;
						}
						else if (esflag[7] == FALSE) {
							esflag[7] = TRUE;
							eskind[7] = GetRand(9) + 10;
							esx[7] = epx + 3;
							esy[7] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}
				else if (move == 33) {
					epx -= 3;
					if (epx < 365) {
						move = 30;
					}

					bosscount--;
					if (bosscount < 0) {
						bosscount = 20;
						if (esflag[0] == FALSE) {
							esflag[0] = TRUE;
							eskind[0] = 15;
							esx[0] = epx + 3;
							esy[0] = epy;
						}
						else if (esflag[1] == FALSE) {
							esflag[1] = TRUE;
							eskind[1] = 15;
							esx[1] = epx + 3;
							esy[1] = epy;
						}
						else if (esflag[2] == FALSE) {
							esflag[2] = TRUE;
							eskind[2] = 15;
							esx[2] = epx + 3;
							esy[2] = epy;
						}
						else if (esflag[3] == FALSE) {
							esflag[3] = TRUE;
							eskind[3] = 15;
							esx[3] = epx + 3;
							esy[3] = epy;
						}
						else if (esflag[4] == FALSE) {
							esflag[4] = TRUE;
							eskind[4] = 15;
							esx[4] = epx + 3;
							esy[4] = epy;
						}
					}

					if (count % 600 == 0) {
						move = 8;
						bosscount = 90;
					}
				}

			}
		}	
		break;
	case 99://2PlayerModeではなし
		break;
	default:
		*errorcheck = 6;//呼び出されないはず
		break;
	}

	/*HP表示と機体表示*/
	if (nowhp > 0) {
		if (No == 1) {
			DrawBox(80, 6, 91 + 200 * nowhp / maxhp, 14, HPCr, TRUE);// HPを描画
		}
		else if (No == 2) {
			DrawBox(390, 6, 402 + 200 * nowhp / maxhp, 14, HPCr, TRUE);// HPを描画
		}
		if (protectcount <= 0 || count % 5 < 3)DrawGraph(epx, epy, BossGraphic[ekind - 11], TRUE);//機体
	}
	/*弾の動きと描画*/
	for (i = 0; i < 7; i++) {
		if (esflag[i] == TRUE) {
			switch (eskind[i]) {
			case 0://下
				esy[i] += 3;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 1://少し左
				esy[i] += 3;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 2://少し右
				esy[i] += 3;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 3://左
				esy[i] += 3;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 4://右
				esy[i] += 3;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 5://下（高速）
				esy[i] += 5;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 6://かなり左
				esy[i] += 3;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 7://かなり右
				esy[i] += 3;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 8://すごく左
				esy[i] += 3;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 9://すごく右
				esy[i] += 3;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 10://下
				esy[i] += 5;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 11://すごく左
				esy[i] += 5;
				esx[i] -= 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 12://すごく右
				esy[i] += 5;
				esx[i] += 2;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 13://左
				esy[i] += 5;
				esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 14://右
				esy[i] += 5;
				esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 15://下（高速）
				esy[i] += 8;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 16://かなり左
				esy[i] += 5;
				esx[i] -= 1;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 17://かなり右
				esy[i] += 5;
				esx[i] += 1;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 18://少し左
				esy[i] += 5;
				if (count % 2 == 0)esx[i] -= 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 19://少し右
				esy[i] += 5;
				if (count % 2 == 0)esx[i] += 1;
				DrawGraph(esx[i], esy[i], NormalEnemyGraphic[13], TRUE);//弾
				break;
			case 30://Stagaの技
				break;
			default:
				break;
			}
			if (No == 1) {
				if (esy[i] > MAXMAPYALL - 30 || esx[i] > MAXMAPX1 - 16 || esx[i] < -10)esflag[i] = FALSE;// 端に到達時に消える
			}
			else if (No == 2) {
				if (esy[i] > MAXMAPYALL - 30 || esx[i] > MAXMAPX2 - 16 || esx[i] < MAXMAPX1 + 10)esflag[i] = FALSE;// 端に到達時に消える
			}
			
		}
	}

	/*時間経過による処理*/
	if (protectcount > -5)protectcount--;


}//ボスの動きに関する処理

int Mode2Boss::BossHP(int damage) {
	nowhp -= damage;
	if (nowhp < 0)nowhp = 0;
	if (damage > 0) {//ダメージを受けている
		protectcount = 15;
	}
	return nowhp;
}

void Mode2Boss::BossInfoReturn(int *enemyx, int *enemyy, int *enemykind, int shotx[], int shoty[], int shotkind[], bool shotflag[], int *protect) {
	*enemyx = epx;
	*enemyy = epy;
	*enemykind = ekind;
	*protect = protectcount;
	for (int i = 0; i < 5; i++) {
		shotx[i] = esx[i];
		shoty[i] = esy[i];
		shotkind[i] = eskind[i];
		shotflag[i] = esflag[i];
	}
}

/*ステージ初めの際の敵出現用関数*/
void NormalStage_StartPrepare(int stage, int *errorcheck, Mode2Enemy Enemy[],int No) {
	if (stage < 0) {
		*errorcheck = 2;
		return;
	}

	int i, j;
	int enemyxnum = 0, enemyynum = 0;//横に並ぶ総数、縦に並ぶ総数
	int Enemypx[MAX1PlayerENEMY] = {}, Enemypy[MAX1PlayerENEMY] = {};//敵機の座標指定
	int Enemykindr[MAX1PlayerENEMY] = {};//敵機の種類
	int startx;//敵のxの端の座標
	int stageenkind = 0;//ステージによる敵機の種類数
						/*ステージ内の敵数*/
	switch (stage) {
	case 1:
		enemyxnum = 5;
		enemyynum = 3;
		if (No == 1) {
			startx = 55;
		}
		else if (No == 2) {
			startx = 365;
		}
		stageenkind = 5;
		break;
	case 2:
		enemyxnum = 5;
		enemyynum = 4;
		if (No == 1) {
			startx = 55;
		}
		else if (No == 2) {
			startx = 365;
		}
		stageenkind = 6;
		break;
	case 3:
		enemyxnum = 7;
		enemyynum = 4;
		if (No == 1) {
			startx = 15;
		}
		else if (No == 2) {
			startx = 325;
		}
		stageenkind = 6;
		break;
	case 4:
		enemyxnum = 7;
		enemyynum = 5;
		if (No == 1) {
			startx = 15;
		}
		else if (No == 2) {
			startx = 325;
		}
		stageenkind = 7;
		break;
	default://stage5はボス
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

/*最終画面*/
void Mode2RESULT(int *ErrorCheck, int gameflag, int point1, int point2) {
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

	//フォントを作成し作成したデータの識別番号を変数 FontHandle に保存する
	int FontHandle = CreateFontToHandle(NULL, 15, 6);

	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/result.mp3");

	bool Key = TRUE;

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	ClearDrawScreen(); // 画面を消す
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽

	do {
		if (CheckHitKeyAll() == 0)Key = FALSE;//キーから１回手を離すこと

		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}

		/*途中強制終了処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 && Key == FALSE) {
			ESCGameEnd(ErrorCheck);//強制終了
			Key = TRUE;
		}

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// サウンドハンドルの削除
			DeleteSoundMem(SHandle);
			return;//errorなら強制終了
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			// サウンドハンドルの削除
			DeleteSoundMem(SHandle);
			return;        // エラーが起きたらループを抜ける
		}

		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && Key == FALSE || CheckHitKey(KEY_INPUT_RETURN) == 1 && Key == FALSE) {
			break;
		}

		/*画面表示*/
		SetFontSize(32);
		DrawFormatString(150, 20, Cr[6], "2Player Mode Finish!!");
		SetFontSize(16);
		DrawFormatString(100, 70, Cr[2], "Player1");
		DrawFormatString(400, 70, Cr[2], "Player2");
		if (gameflag == 1) {//Player1のみクリア
			DrawFormatString(100, 90, Cr[3], "Clear!");
			DrawFormatString(400, 90, Cr[0], "Not Clear...");
		}
		else if (gameflag == 2) {//Player2のみクリア
			DrawFormatString(400, 90, Cr[3], "Clear!");
			DrawFormatString(100, 90, Cr[0], "Not Clear...");
		}
		else if (gameflag == 3) {//両方ともクリア
			DrawFormatString(100, 90, Cr[3], "Clear!");
			DrawFormatString(400, 90, Cr[3], "Clear!");
		}
		DrawFormatString(100, 150, Cr[8], "Get Points : %d", point1);
		DrawFormatString(400, 150, Cr[8], "Get Points : %d", point2);
		DrawFormatString(200, 400, Cr[5], "Please SPACE or ENTER Key...");
		SetFontSize(24);
		if (point1 > point2) {
			DrawFormatString(200, 200, Cr[7], "Player1 Win!!");
		}
		else if (point1 < point2) {
			DrawFormatString(200, 200, Cr[7], "Player2 Win!!");
		}
		else {
			if (gameflag == 1) {
				DrawFormatString(200, 200, Cr[7], "Player1 Win!!");
			}
			else if (gameflag == 2) {
				DrawFormatString(200, 200, Cr[7], "Player2 Win!!");
			}
			else if (gameflag == 3) {
				DrawFormatString(220, 200, Cr[7], "Draw...");
			}
		}

		/*その他の処理*/

		ScreenFlip();

	} while (1);//終了しない限り

	SetFontSize(16);
	ClearDrawScreen(); // 画面を消す
	ScreenFlip();
	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);
}

//////////////////////////////////////////////////////////////////
//     2Player mode　main　　　　　　　　　　　　　　　　　　   //
//////////////////////////////////////////////////////////////////
int Player2mode(int *ErrorCheck) {//2Player mode　main

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
	DrawString(200, 300, "敵", Cr[8]);
	DrawString(200, 330, "敵の動きは,色ごとに決まっている.", Cr[8]);
	DrawString(200, 350, "タイトル画面のContentsで確認できる.", Cr[8]);
	ScreenFlip();

	Mode2Player Player1, Player2;
	Mode2Enemy NormalEnemy1[MAX1PlayerENEMY], NormalEnemy2[MAX1PlayerENEMY];
	Mode2Boss Boss[2];
	Fps fps;
	int i = -1;

	int NormalEnemyGraphic[20], PlayerShotGraphic[10], MyGraphic[2], BossGraphic[6];
	// PNG画像のメモリへの分割読み込み
	i = LoadDivGraph("../exe/package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);
	if (i == -1)LoadDivGraph("./package/paint/NormalEnemy.png", 20, 4, 5, 32, 32, NormalEnemyGraphic);//再読み込み
	i = LoadDivGraph("../exe/package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);
	if (i == -1)LoadDivGraph("./package/paint/Boss.png", 6, 3, 2, 40, 40, BossGraphic);//再読み込み
	i = LoadDivGraph("../exe/package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);
	if (i == -1)LoadDivGraph("./package/paint/PlayerShot.png", 10, 5, 2, 16, 16, PlayerShotGraphic);//再読み込み
	i = LoadDivGraph("../exe/package/paint/Player2.png", 2, 2, 1, 40, 40, MyGraphic);
	if (i == -1)LoadDivGraph("./package/paint/Player2.png", 2, 2, 1, 40, 40, MyGraphic);//再読み込み
	int FontHandle = CreateFontToHandle(NULL, 16, 3);

	int gameflag = 0;//0:スタート時 1～３:ゲーム終了 -1:エラー
	int stage[2] = {};//現在ステージ
	int gamecount = 1;//ゲーム内時間
	int PlayerShotKind[3] = { 9,9,9 }, ShotCombonum[3] = {};
	int stagekind[2] = {};//ステージの種類 1:ノーマルステージ 2:ボスステージ 3:ゲームクリア 4:２人ともクリア 5:その他 (0:エラー)
	int playerpoint[2] = {};
	bool clearflag[2] = {};//ステージクリア
	bool clearcheckflag[2] = {};//ステージクリア判定用
	int clearcount[2] = {};//ステージクリアから次のステージの準備までの時間
	int ppx[2] = {}, ppy[2] = {};//自機のx座標とy座標

	//フォントを作成し作成したデータの識別番号を変数 FontHandleに保存する
	int FontHandle2 = CreateFontToHandle(NULL, 30, 8);//大きい文字
	//メモリへの読み込みサウンドハンドルをSHandleに保存します
	int SHandle = LoadSoundMem("../exe/package/bgm/battle.mp3");
	if (SHandle == -1) SHandle = LoadSoundMem("./package/bgm/battle.mp3");//再読み込み

	i = 0;
	/////**2Player Mode Start**/////
	SetFontSize(14);
	/*途中強制終了処理*/
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		ESCGameEnd(ErrorCheck);//強制終了
	}

	if (*ErrorCheck > 0 || *ErrorCheck == -1) {
		// 読み込んだ画像のグラフィックハンドルを削除
		for (i = 0; i < 10; i++) {
			DeleteGraph(PlayerShotGraphic[i]);
		}
		for (i = 0; i < 12; i++) {
			DeleteGraph(NormalEnemyGraphic[i]);
		}
		for (i = 0; i < 6; i++) {
			DeleteGraph(BossGraphic[i]);
		}
		for (i = 0; i < 2; i++) {
			DeleteGraph(MyGraphic[i]);
		}
		// サウンドハンドルの削除
		DeleteSoundMem(SHandle);
		return -1;//errorなら強制終了
	}

	if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
		*ErrorCheck = 1;
		// 読み込んだ画像のグラフィックハンドルを削除
		for (i = 0; i < 10; i++) {
			DeleteGraph(PlayerShotGraphic[i]);
		}
		for (i = 0; i < 12; i++) {
			DeleteGraph(NormalEnemyGraphic[i]);
		}
		for (i = 0; i < 6; i++) {
			DeleteGraph(BossGraphic[i]);
		}
		for (i = 0; i < 2; i++) {
			DeleteGraph(MyGraphic[i]);
		}
		// サウンドハンドルの削除
		DeleteSoundMem(SHandle);
		return -1;        // エラーが起きたらループを抜ける
	}

	/*初期化処理*/
	Player1.StartSet(1);
	Player2.StartSet(2);
	for (i = 0; i < MAX1PlayerENEMY; i++) {
		NormalEnemy1[i].StartSet();
		NormalEnemy2[i].StartSet();
	}
	stage[0] = 0;
	stage[1] = 0;
	clearcheckflag[0] = TRUE;
	clearcheckflag[1] = TRUE;
	clearcount[0] = 300;
	clearcount[1] = 300;
	PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽

	while (gameflag == 0) {

		if (CheckSoundMem(SHandle) == 0) {
			PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);//音楽
		}
		/*途中強制終了処理*/
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			ESCGameEnd(ErrorCheck);//強制終了
		}
		fps.Update();	//更新
		fps.Wait();		//待機

		if (*ErrorCheck > 0 || *ErrorCheck == -1) {
			// 読み込んだ画像のグラフィックハンドルを削除
			for (i = 0; i < 10; i++) {
				DeleteGraph(PlayerShotGraphic[i]);
			}
			for (i = 0; i < 12; i++) {
				DeleteGraph(NormalEnemyGraphic[i]);
			}
			for (i = 0; i < 6; i++) {
				DeleteGraph(BossGraphic[i]);
			}
			for (i = 0; i < 2; i++) {
				DeleteGraph(MyGraphic[i]);
			}
			return -1;//errorなら強制終了
		}

		if (ProcessMessage() == -1) {// メッセージループに代わる処理をする
			*ErrorCheck = 1;
			return -1;        // エラーが起きたらループを抜ける
		}

		ClearDrawScreen(); // 画面を消す
		/*それぞれのプレイヤーのステージ開始時処理*/
		/*Player1*/
		if (clearflag[0] == TRUE) {
			/*ステージクリア時処理*/
			stage[0]++;
			clearcount[0] = 120;
			clearflag[0] = FALSE;
			clearcheckflag[0] = FALSE;
			if (stage[0] < 5) {
				Player1.PointPlus(100);
				stagekind[0] = 1;//ノーマルステージ
				NormalStage_StartPrepare(stage[0], ErrorCheck, NormalEnemy1, 1);
			}
			else if (stage[0] == 5) {
				Player1.PointPlus(100);
				stagekind[0] = 2;//ボスステージ
				for (i = 0; i < MAX1PlayerENEMY; i++) {
					NormalEnemy1[i].StartSet();
				}
				Boss[0].StartSet(stage[0], 1);
				for (i = 0; i < 5; i++) {
					NormalEnemy1[i].AppearEnemy(55 + i * 40, 70, 8);
				}
			}
			else if (stage[0] == 6) {
				stagekind[0] = 3;//全ステージクリア
				clearcount[0] = 3600;
			}
			Player1.StartSet(3);
		}

		/*Player2*/
		if (clearflag[1] == TRUE) {
			/*ステージクリア時処理*/
			stage[1]++;
			clearcount[1] = 120;
			clearflag[1] = FALSE;
			clearcheckflag[1] = FALSE;
			if (stage[1] < 5) {
				Player2.PointPlus(100);
				stagekind[1] = 1;//ノーマルステージ
				NormalStage_StartPrepare(stage[1], ErrorCheck, NormalEnemy2, 2);
			}
			else if (stage[1] == 5) {
				Player2.PointPlus(100);
				stagekind[1] = 2;//ボスステージ
				for (i = 0; i < MAX1PlayerENEMY; i++) {
					NormalEnemy2[i].StartSet();
				}
				Boss[1].StartSet(stage[1], 2);
				for (i = 0; i < 5; i++) {
					NormalEnemy2[i].AppearEnemy(365 + i * 40, 70, 8);
				}
			}
			else if (stage[1] == 6) {
				stagekind[1] = 3;//全ステージクリア
				clearcount[1] = 3600;
			}
			Player2.StartSet(4);
		}

		/*ステージクリア判定*/
		if (stagekind[0] == 1) {//ノーマルステージ
			clearcheckflag[0] = TRUE;
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				if (NormalEnemy1[i].EnemyExistCheck() == TRUE) {
					clearcheckflag[0] = FALSE;
				}
			}
		}
		else if (stagekind[0] == 2) {//ボスステージ
			if (Boss[0].BossHP(0) == 0) {
				clearcheckflag[0] = TRUE;
			}
		}

		if (stagekind[1] == 1) {//ノーマルステージ
			clearcheckflag[1] = TRUE;
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				if (NormalEnemy2[i].EnemyExistCheck() == TRUE) {
					clearcheckflag[1] = FALSE;
				}
			}
		}
		else if (stagekind[1] == 2) {//ボスステージ
			if (Boss[1].BossHP(0) == 0) {
				clearcheckflag[1] = TRUE;
			}
		}

		for (i = 0; i < 2; i++) {
			if (clearcheckflag[i] == TRUE) {
				clearcount[i]--;
				if (clearcount[i] < 0) {
					clearflag[i] = TRUE;
				}
			}
		}

		/*各プレイヤーの動きと描画*/
		if (stagekind[0] < 3) {
			Player1.PlayerMove1(ErrorCheck, MyGraphic[0], PlayerShotGraphic);
			Player1.PlayerPosition(&ppx[0], &ppy[0]);
		}
		if (stagekind[1] < 3) {
			Player2.PlayerMove2(ErrorCheck, MyGraphic[1], PlayerShotGraphic);
			Player2.PlayerPosition(&ppx[1], &ppy[1]);
		}

		/*敵機の動きと描画,当たり判定*/
		//*Player1*/
		if (stagekind[0] < 3) {
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				NormalEnemy1[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx[0], ppy[0], 1);
			}
			Player1.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy1, stage[0]);
			if (stagekind[0] == 2) {//ボスステージ
				Boss[0].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx[0], ppy[0], 1, NormalEnemy1);
				Player1.BossStage_CollisionDetection(ErrorCheck, Boss, 1);
			}
		}
	
		//*Player2*/
		if (stagekind[1] < 3) {
			for (i = 0; i < MAX1PlayerENEMY; i++) {
				NormalEnemy2[i].NormalEnemyMove(ErrorCheck, NormalEnemyGraphic, gamecount, ppx[1], ppy[1], 2);
			}
			Player2.NormalStage_CollisionDetection(ErrorCheck, NormalEnemy2, stage[1]);
			if (stagekind[1] == 2) {//ボスステージ
				Boss[1].BossMove(ErrorCheck, NormalEnemyGraphic, BossGraphic, gamecount, ppx[1], ppy[1], 2, NormalEnemy2);
				Player2.BossStage_CollisionDetection(ErrorCheck, Boss, 2);
			}
		}
		

		/////**情報**/////
		/*Player1*/
		DrawBox(0, 0, MAXMAPX1 + 5, MAXMAPYALL, Cr[9], FALSE);// 四角形を描画
		if (stagekind[0] < 3) {
			Player1.PlayerShotColor(PlayerShotKind);
			Player1.PlayerShotCombo(ShotCombonum);
			DrawFormatString(0, 370, Cr[9], "Player1 : Stage %d : Total Points %d", stage[0], Player1.GetPoint());
			DrawString(0, 387, "Cキー:左 Bキー:右", Cr[9]);
			DrawFormatString(0, 404, Cr[9], "Q:ショット |    |");
			DrawStringToHandle(0, 421, "W", Cr[9], FontHandle);
			DrawFormatString(8, 421, Cr[9], ":ショット |    |");
			DrawFormatString(0, 438, Cr[9], "E:ショット |    |");
			for (i = 0; i < 3; i++) {
				DrawFormatString(130, 404 + i * 17, Cr[PlayerShotKind[i]], "コンボ:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(99, 404 + i * 17, "赤", Cr[0]);
					break;
				case 1:
					DrawString(99, 404 + i * 17, "青", Cr[1]);
					break;
				case 2:
					DrawString(99, 404 + i * 17, "黄", Cr[2]);
					break;
				case 3:
					DrawString(99, 404 + i * 17, "緑", Cr[3]);
					break;
				case 4:
					DrawString(99, 404 + i * 17, "橙", Cr[4]);
					break;
				case 5:
					DrawString(99, 404 + i * 17, "紫", Cr[5]);
					break;
				case 6:
					DrawString(92, 404 + i * 17, "赤紫", Cr[6]);
					break;
				case 7:
					DrawString(99, 404 + i * 17, "空", Cr[7]);
					break;
				default:
					DrawString(99, 404 + i * 17, "無", Cr[9]);
					break;
				}
			}

			if (stage[0] == 0) {//開始前画面表示
				if (clearcount[0] > 180) {
					DrawStringToHandle(20, 50, "Player 1", Cr[6], FontHandle2);
					DrawStringToHandle(20, 100, "Please Wait...", Cr[6], FontHandle2);
				}
				else if (clearcount[0] > 120) {
					DrawStringToHandle(140, 70, "3", Cr[0], FontHandle2);
				}
				else if (clearcount[0] > 60) {
					DrawStringToHandle(140, 70, "2", Cr[2], FontHandle2);
				}
				else {
					DrawStringToHandle(140, 70, "1", Cr[3], FontHandle2);
				}
			}
		}
		else if (stagekind[0] == 3) {
			DrawStringToHandle(15, 50, "Player1 Clear!", Cr[0], FontHandle2);
			DrawStringToHandle(15, 90, "Please wait by Player2 end...", Cr[4], FontHandle);
			DrawFormatString(15, 150, Cr[7], "Player1 Total Points:%d", Player1.GetPoint());
			DrawFormatString(15, 220, Cr[8], "Player2 Time Out:");
			if (clearcount[0] > 1200) {
				DrawFormatString(155, 220, Cr[3], "%d", clearcount[0] / 60);
			}
			else {
				DrawFormatString(155, 220, Cr[2], "%d", clearcount[0] / 60);
			}	
			clearcount[0]--;
		}

		/*Player2*/
		DrawBox(MAXMAPX1 + 15, 0, MAXMAPX2 + 5, MAXMAPYALL, Cr[9], FALSE);// 四角形を描画
		if (stagekind[1] < 3) {
			Player2.PlayerShotColor(PlayerShotKind);
			Player2.PlayerShotCombo(ShotCombonum);
			DrawFormatString(320, 370, Cr[9], "Player2 : Stage %d : Total Points %d", stage[1], Player2.GetPoint());
			DrawString(320, 387, "LEFTキー:左 RIGHTキー:右", Cr[9]);
			DrawFormatString(320, 404, Cr[9], "I:ショット |    |");
			DrawFormatString(320, 421, Cr[9], "O:ショット |    |");
			DrawFormatString(320, 438, Cr[9], "P:ショット |    |");
			for (i = 0; i < 3; i++) {
				DrawFormatString(450, 404 + i * 17, Cr[PlayerShotKind[i]], "コンボ:%d", ShotCombonum[i]);
				switch (PlayerShotKind[i]) {
				case 0:
					DrawString(419, 404 + i * 17, "赤", Cr[0]);
					break;
				case 1:
					DrawString(419, 404 + i * 17, "青", Cr[1]);
					break;
				case 2:
					DrawString(419, 404 + i * 17, "黄", Cr[2]);
					break;
				case 3:
					DrawString(419, 404 + i * 17, "緑", Cr[3]);
					break;
				case 4:
					DrawString(419, 404 + i * 17, "橙", Cr[4]);
					break;
				case 5:
					DrawString(419, 404 + i * 17, "紫", Cr[5]);
					break;
				case 6:
					DrawString(412, 404 + i * 17, "赤紫", Cr[6]);
					break;
				case 7:
					DrawString(419, 404 + i * 17, "空", Cr[7]);
					break;
				default:
					DrawString(419, 404 + i * 17, "無", Cr[9]);
					break;
				}
			}

			if (stage[1] == 0) {//開始前画面表示
				if (clearcount[1] > 180) {
					DrawStringToHandle(370, 50, "Player 2", Cr[6], FontHandle2);
					DrawStringToHandle(370, 100, "Please Wait...", Cr[6], FontHandle2);
				}
				else if (clearcount[1] > 120) {
					DrawStringToHandle(460, 70, "3", Cr[0], FontHandle2);
				}
				else if (clearcount[1] > 60) {
					DrawStringToHandle(460, 70, "2", Cr[2], FontHandle2);
				}
				else {
					DrawStringToHandle(460, 70, "1", Cr[3], FontHandle2);
				}
			}
		}
		else if (stagekind[1] == 3) {
			DrawStringToHandle(330, 50, "Player2 Clear!", Cr[1], FontHandle2);
			DrawStringToHandle(330, 90, "Please wait by Player1 end...", Cr[4], FontHandle);
			DrawFormatString(330, 150, Cr[7], "Player2 Total Points:%d", Player2.GetPoint());
			DrawFormatString(330, 220, Cr[8], "Player1 Time Out:");
			if (clearcount[1] > 1200) {
				DrawFormatString(470, 220, Cr[3], "%d", clearcount[1] / 60);
			}
			else {
				DrawFormatString(470, 220, Cr[2], "%d", clearcount[1] / 60);
			}
			clearcount[1]--;
		}

		gamecount++;//時間経過
		if (gamecount > 100000000)gamecount = 0;//バグの防止
		if (gamecount > 150000000)*ErrorCheck = 4;//時間経過しすぎ

		/*全ステージクリア判定*/
		if (stagekind[0] == 3 && stagekind[1] == 3) {
			gameflag = 3;//正常終了
		}
		if (stagekind[0] == 3) {
			if (clearcount[0] < 0 && stagekind[1] != 3) {//時間経過したのにPlayer2がクリアしていない
				gameflag = 1;//Player1のみクリア,Player2は強制終了
			}
		}
		if (stagekind[1] == 3) {
			if (clearcount[1] < 0 && stagekind[0] != 3) {//時間経過したのにPlayer1がクリアしていない
				gameflag = 2;//Player2のみクリア,Player1は強制終了
			}
		}

		ScreenFlip();
	}//ループここまで

	if (gameflag > 0) {//クリアしたことによって終了
		Mode2RESULT(ErrorCheck, gameflag, Player1.GetPoint(), Player2.GetPoint());
	}

	// 読み込んだ画像のグラフィックハンドルを削除
	for (i = 0; i < 10; i++) {
		DeleteGraph(PlayerShotGraphic[i]);
	}
	for (i = 0; i < 12; i++) {
		DeleteGraph(NormalEnemyGraphic[i]);
	}
	for (i = 0; i < 6; i++) {
		DeleteGraph(BossGraphic[i]);
	}
	for (i = 0; i < 2; i++) {
		DeleteGraph(MyGraphic[i]);
	}
	// サウンドハンドルの削除
	DeleteSoundMem(SHandle);

	return 0;

}
