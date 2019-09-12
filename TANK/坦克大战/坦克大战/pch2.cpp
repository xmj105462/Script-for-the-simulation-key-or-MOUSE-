// pch.cpp: 与预编译标头对应的源文件；编译成功所必需的

#include "pch.h"
#include <xlocinfo>
#include <time.h>
//#include<sysinfoapi.h>
__int64 t1, t2;


// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。
void startgraph() {
	initgraph(START_X, 780);
	IMAGE img;
	loadimage(&img, _T("res/logo.gif"), LOGO_X, 147, 1);
	putimage((START_X - LOGO_X) >> 1, 10, &img);
	setlinecolor(WHITE);
	setfillcolor(BLACK);
	fillrectangle(RECTANGLE_X1, 200, RECTANGLE_X2, 250);
	settextcolor(YELLOW);
	settextstyle(TEXT_SIZE, 0, _T("微软雅黑"));
	outtextxy(RECTANGLE_X1 + 25, 205, _T("说明"));
	fillrectangle(RECTANGLE_X2 + 50, 200, RECTANGLE_X2 + 170, 250);
	outtextxy(RECTANGLE_X2 + 75, 205, _T("开始"));
	MOUSEMSG mouseCheck;
	IMAGE explainImg;
	loadimage(&explainImg, _T("res/explain.gif"), 300, 300, true);
	while (true) {
		mouseCheck = GetMouseMsg();
		switch (mouseCheck.uMsg) {
		case WM_MOUSEMOVE:
			if (mouseCheck.x > RECTANGLE_X1 + 25 && mouseCheck.x < RECTANGLE_X2 - 25 && mouseCheck.y>200 && mouseCheck.y < 250) {
				putimage(RECTANGLE_X1, 260, &explainImg);
			}
			else {
				//setlinecolor(BLACK);
				solidrectangle(RECTANGLE_X1, 260, RECTANGLE_X1 + 300, 560);
			}
			break;
		case WM_LBUTTONDOWN:
			if (mouseCheck.x > RECTANGLE_X2 + 75 && mouseCheck.x < RECTANGLE_X2 + 150 && mouseCheck.y>200 && mouseCheck.y < 250) {
				cleardevice(); return;
			}
			break;
		default:
			break;
		}
	}
}

void initGameMap() {
	IMAGE Img[all];
	loadimage(&Img[wall], _T("res/wall.gif"), IMAGE_SIZE, IMAGE_SIZE, true);
	//IMAGE unWallImg;
	loadimage(&Img[unWall], _T("res/unWall.gif"), IMAGE_SIZE, IMAGE_SIZE, true);
	//IMAGE homeImg;
	loadimage(&Img[home], _T("res/home.gif"), IMAGE_SIZE * 2, IMAGE_SIZE * 2, true);
	for (unsigned short j = 0; j < MAP_Y; j++) {
		for (unsigned short i = 0; i < MAP_Y; i++) {
			if (map[j][i] > 0) {
				if (map[j][i] == 3) {
					putimage(i * IMAGE_SIZE, j * IMAGE_SIZE, &Img[map[j][i] - 1]);
					map[j][i] = 4; map[j][i + 1] = 4; map[j + 1][i] = 4; map[j + 1][i + 1] = 4; continue;
				}
				putimage(i * IMAGE_SIZE, j * IMAGE_SIZE, &Img[map[j][i] - 1]);
			}

		}
	}

}Bullet* biu = nullptr;
void bulletMove(IMAGE* bullImg, IMAGE* blastImg, Enemy* enemyArr, size_t eARR_size) {
	if (biu == nullptr) return;
	if (biu->bDir == UP) {

		if (biu->y < 0) {
			DELETE_B
		}
		
		BULLET_UP//子弹打到不可消墙
		else if (map[biu->y][biu->x] == 200) {
			for (size_t i = 0; i < eARR_size; i++) {
				if (biu == nullptr)break;
				if (enemyArr[i].x == (biu->x) && enemyArr[i].y == (biu->y-1)) {
					clearrectangle(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE);
					mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//子弹打到敌方		
					for (size_t i = 0; i < BLAST * 2; i++) {
						BULLET_BLAST//爆炸动画
					}
					enemyArr[i].live = false; ENEMY_INIT(biu) DELETE_B break;
				}
				else if ((enemyArr[i].x) == (biu->x - 1) && enemyArr[i].y == (biu->y-1)) {
					clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);
					mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
					for (size_t i = 0; i < BLAST * 2; i++) {
						if (i >= BLAST) {
							putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
						}
						else {
							putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
						}
						enemyArr[i].live = false; ENEMY_INIT2(biu) DELETE_B break;
					}

				}
			}
		}

	else {
		BULLET_yMOVE //Sleep(30);
	}
}
	else if (biu->bDir == DOWN) {
	if (biu->y > (MAP_Y - 2)) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);
		DELETE_B return;
	}
	if (map[biu->y][biu->x] == 1 || map[biu->y][biu->x + 1] == 1) {
		SHELL
	}
	else if (map[biu->y + 1][biu->x] == 2 || map[biu->y + 1][biu->x] == 4) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);
		DELETE_B
	}
	else if (map[biu->y][biu->x] == 200) {//待加线程
		for (size_t i = 0; i < eARR_size; i++) {
			if (biu == nullptr)break;
			if (enemyArr[i].x == (biu->x) && enemyArr[i].y == biu->y) {
				clearrectangle(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}
				enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
				map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x + 1] = 0;
				DELETE_B break;
			}
			else if ((enemyArr[i].x) == (biu->x - 1) && enemyArr[i].y == biu->y) {
				clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}
				}
				enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
				map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x - 1] = 0;
				DELETE_B break;
			}
		}
	}
	else {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);
		biu->y += 1;
		putimage(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, bullImg);
	}

	}
	else if (biu->bDir == LEFT) {
	if (biu->x < 1) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		DELETE_B return;
	}if (map[biu->y][biu->x] == 1 || map[biu->y + 1][biu->x] == 1) {
		SHELL2
	}
	else if (map[biu->y][biu->x - 1] == 2 || map[biu->y][biu->x - 1] == 4 || map[biu->y + 1][biu->x - 1] == 4 || map[biu->y + 1][biu->x - 1] == 2) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		DELETE_B
	}
	else if (map[biu->y][biu->x] == 200 && biu->x > 0) {//待加线程
		for (size_t i = 0; i < eARR_size; i++) {
			if (biu == nullptr)break;
			if (enemyArr[i].x == (biu->x - 1) && enemyArr[i].y == biu->y) {
				clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}
				enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
				map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x - 1] = 0;
				DELETE_B break;
			}
			else if (enemyArr[i].x == (biu->x - 1) && enemyArr[i].y == (biu->y - 1)) {
				clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}
				enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
				map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x - 1] = 0;
				DELETE_B break;
			}
		}

	}
	else {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		biu->x -= 1;
		putimage(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, bullImg);
	}
	}
	else if (biu->bDir == RIGHT) {
	if (biu->x > (MAP_Y - 2)) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		DELETE_B return;
	}

	if (map[biu->y][biu->x] == 1 || map[biu->y + 1][biu->x] == 1) {
		SHELL2
	}
	else if (map[biu->y][biu->x + 1] == 2 || map[biu->y][biu->x + 1] == 4 || map[biu->y + 1][biu->x + 1] == 4 || map[biu->y + 1][biu->x + 1] == 2) {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		DELETE_B
	}
	else if (map[biu->y][biu->x] == 200 && biu->x < (MAP_Y - 1)) {//待加线程
		for (size_t i = 0; i < eARR_size; i++) {
			if (biu == nullptr)break;
			if (enemyArr[i].x == biu->x && enemyArr[i].y == biu->y) {
				clearrectangle((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
				map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x + 1] = 0;
				DELETE_B break;
			}
			else if (enemyArr[i].x == biu->x && enemyArr[i].y == (biu->y - 1)) {
				clearrectangle((biu->x) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((biu->x) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((biu->x) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}enemyArr[i].live = false;
				map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
				map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x + 1] = 0;
				DELETE_B break;
			}
		}
	}
	else {
		//Sleep(30);
		clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
		biu->x += 1;
		putimage(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, bullImg);
	}
	}
}
void play() {
	struct Tank myTank { 8, 24, UP, us };//我方坦克
	IMAGE myTankImg[Dall];
	LOAD_TANK(myTankImg, UP, "res/tank_up.gif");
	LOAD_TANK(myTankImg, DOWN, "res/tank_down.gif");
	LOAD_TANK(myTankImg, LEFT, "res/tank_left.gif");
	LOAD_TANK(myTankImg, RIGHT, "res/tank_right.gif");
	putimage(myTank.x * IMAGE_SIZE, myTank.y * IMAGE_SIZE, &myTankImg[myTank.tDir]);
	TANK_INIT(myTank, 100)
		//敌方坦克初始化
		Enemy enemyTank;
	Enemy enemyTank2{ 12, 0, LEFT };
	Enemy enemyTank3{ 24, 0, DOWN };
	IMAGE eTankImg[Dall];
	LOAD_TANK(eTankImg, UP, "res/enemy_tank_up.gif");
	LOAD_TANK(eTankImg, DOWN, "res/enemy_tank_down.gif");
	LOAD_TANK(eTankImg, LEFT, "res/enemy_tank_left.gif");
	LOAD_TANK(eTankImg, RIGHT, "res/enemy_tank_right.gif");
	putimage(enemyTank.x * IMAGE_SIZE, enemyTank.y * IMAGE_SIZE, &eTankImg[enemyTank.tDir]);
	putimage(enemyTank2.x * IMAGE_SIZE, enemyTank2.y * IMAGE_SIZE, &eTankImg[enemyTank2.tDir]);
	putimage(enemyTank3.x * IMAGE_SIZE, enemyTank3.y * IMAGE_SIZE, &eTankImg[enemyTank3.tDir]);
	TANK_INIT(enemyTank, 200)TANK_INIT(enemyTank2, 200)TANK_INIT(enemyTank3, 200)//敌方在地图中位置
	//加载子弹图片
		IMAGE bullImg;
	loadimage(&bullImg, _T("res/bullet.png"), 29, 30, true);
	IMAGE eBullImg;
	loadimage(&eBullImg, _T("res/eBullet.gif"), 29, 30, true);
	//加载爆炸图片	
	char  name[128]; IMAGE blastImg[BLAST];
	for (int i = 1; i <= _countof(blastImg); i++) {
		sprintf_s(name, "res/blast%d.gif", i);
		loadimage(&blastImg[i - 1], name);
	}
	//敌方坦克数组
	vector <Enemy> enemyArr = { enemyTank ,enemyTank2 ,enemyTank3 };
	unsigned int timeCount = 0;//计算时间，每隔一段时间出新坦克
	vector<Enemy>::iterator it;//标记挂了的坦克迭代器
	short key; //int timeCount = 0;
	t1 = _GetSysTickCount64(); 
	while (1) {
		if ((timeCount % 5) == 0&&!enemyArr.empty())bulletMove(&bullImg, blastImg, &enemyArr[0], enemyArr.size());
		//else break;
		bool ifLive = false;
		if (!enemyArr.empty()) {
			for (it = enemyArr.begin(); it != enemyArr.end(); ) {//回收挂了的坦克
				if (it->live == false) {
					it = enemyArr.erase(it); ifLive = true; break;
				}
				else {
					++it;
				}
			}
			if (ifLive) {
				continue;
			}
			if (_kbhit()) {//如果按键			 			
				key = _getch();//监听按下的键
				keyCheck1(key, &myTank, myTankImg, &bullImg, blastImg, &enemyArr[0], enemyArr.size());
			}
			if (t2 - t1 >= 10000) {
				vector<Enemy>::iterator ite;
				t1 = t2;
				Enemy* enemy = new Enemy;
				enemyArr.push_back(*enemy);
				ite = enemyArr.end() - 1;
				putimage(ite->x * IMAGE_SIZE, ite->y * IMAGE_SIZE, &eTankImg[ite->tDir]);
				TANK_INIT((*ite), 200)
					delete enemy;
			}
			for (size_t i = 0; i < enemyArr.size(); i++) {

				/*if (enemyArr[i].move(eTankImg, &myTank)) {
					 continue;
				}*/

				if ((timeCount % 30) == 0) {
					if (enemyArr[i].move(eTankImg, &myTank)) {
						//continue;
					}
				}
				//子弹生成

				if ((timeCount % 300) == 0) {

					if (enemyArr[i].enemyCreateBullet(blastImg, &eBullImg))return;
				}
				//子弹行动				
				if ((timeCount % 5) == 0) {
					if (enemyArr[i].enemyBulletMove(blastImg, &eBullImg, &myTank, &enemyArr[0], enemyArr.size()))return;
				}for (it = enemyArr.begin(); it != enemyArr.end(); ) {//回收挂了的坦克
					if (it->live == false) {
						it = enemyArr.erase(it); ifLive = true; break;
					}
					else {
						++it;
					}
				}if (ifLive) {
					break;
				}
			}
		}
		else {
			break;
		}
		
		//if (!enemyArr.empty()) {
			//for (size_t i = 0; i < enemyArr.size(); i++) {
			//	
			//	/*if (enemyArr[i].move(eTankImg, &myTank)) {
			//		 continue;
			//	}*/
			//	
			//	if ((timeCount % 30) == 0) { if (enemyArr[i].move(eTankImg, &myTank)) {
			//		 //continue;
			//	}  }
			//	//子弹生成
			//	
			//	 if ((timeCount % 300) == 0) {
			//		
			//		if (enemyArr[i].enemyCreateBullet(blastImg, &eBullImg))return;
			//	}
			//	//子弹行动				
			//	 if ((timeCount%5)==0) {					
			//		if (enemyArr[i].enemyBulletMove(blastImg, &eBullImg, &myTank, &enemyArr[0], enemyArr.size()))return;
			//	}for (it = enemyArr.begin(); it != enemyArr.end(); ) {//回收挂了的坦克
			//		if (it->live == false) {
			//			it = enemyArr.erase(it); ifLive = true; break;
			//		}
			//		else {
			//			++it;
			//		}
			//	}if (ifLive) {
			//		break;
			//	}
			//}
		//}
		t2 = _GetSysTickCount64(); Sleep(10); timeCount++;
	}endGame(false);
}

void keyCheck1(short key, Tank* myTank, IMAGE* myTankImg, IMAGE* bullImg, IMAGE* blastImg, Enemy* enemyArr, size_t eARR_size) {

	switch (key) {
	case KEY_UP:
	case 'w':
		IF_TANK_DIR(UP)
			if (map[myTank->y - 1][myTank->x] == 0 && map[myTank->y - 1][myTank->x + 1] == 0 && myTank->y > 0) {
				map[myTank->y + 1][myTank->x] = 0; map[myTank->y + 1][myTank->x + 1] = 0;
				KEY_MOVE(y, -) MAP_MOVE
					//MAP_MOVE(, , +, 1)
			}
		break;
	case KEY_RIGHT:
	case 'd':
		IF_TANK_DIR(RIGHT)
			if (map[myTank->y][myTank->x + 2] == 0 && map[myTank->y + 1][myTank->x + 2] == 0 && myTank->x < 24) {
				map[myTank->y][myTank->x] = 0; map[myTank->y + 1][myTank->x] = 0;
				KEY_MOVE(x, +) MAP_MOVE
					//MAP_MOVE(+, 1, , )
			}
		break;
	case KEY_DOWN:
	case 's':
		IF_TANK_DIR(DOWN)
			if (map[myTank->y + 2][myTank->x] == 0 && map[myTank->y + 2][myTank->x + 1] == 0 && myTank->y < 24) {
				map[myTank->y][myTank->x] = 0; map[myTank->y][myTank->x + 1] = 0;
				KEY_MOVE(y, +) MAP_MOVE
					//MAP_MOVE(, , +, 1)
			}
		break;
	case KEY_LEFT:

	case 'a':
		IF_TANK_DIR(LEFT)
			if (map[myTank->y][myTank->x - 1] == 0 && map[myTank->y + 1][myTank->x - 1] == 0 && myTank->x > 0) {
				map[myTank->y][myTank->x + 1] = 0; map[myTank->y + 1][myTank->x + 1] = 0;
				KEY_MOVE(x, -) MAP_MOVE
					//MAP_MOVE(+, 1, , )
			}
		break;
	case 'x':
	case 'j':
		//if (enemyArr.empty())return;
		if (biu == nullptr) {
			if (myTank->tDir == UP) {
				if ((myTank->y - 1) < 0) {
					return;
				}
				else {
					biu = new Bullet; biu->bDir = myTank->tDir;
					biu->x = myTank->x; biu->y = myTank->y - 1;
				}

				if (map[biu->y][biu->x] == 1 || map[biu->y][biu->x + 1] == 1) {
					SHELL
				}
				else if (map[biu->y][biu->x] == 2) {

					DELETE_B
				}
				else if (map[biu->y][biu->x] == 200) {//待加线程
					for (size_t i = 0; i < eARR_size; i++) {
						if (biu == nullptr)break;
						if (enemyArr[i].x == biu->x && enemyArr[i].y == (biu->y - 1)) {
							clearrectangle(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE);
							mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
									putimage(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
									putimage(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}
							enemyArr[i].live = false; ENEMY_INIT(biu) DELETE_B break;
						}
						else if (enemyArr[i].x == (biu->x - 1) && enemyArr[i].y == (biu->y - 1)) {
							clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);
							mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
									putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
									putimage((biu->x - 1) * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}
								enemyArr[i].live = false; ENEMY_INIT2(biu) DELETE_B break;
							}

						}
					}
				}
				else {
					putimage(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, bullImg);
				}

			}
			else if (myTank->tDir == DOWN) {

				if (myTank->y > (MAP_Y - 3)) {
					return;
				}
				else {
					biu = new Bullet(); biu->bDir = myTank->tDir;
					biu->x = myTank->x; biu->y = myTank->y + 2;
				}

				if (map[biu->y][biu->x] == 1 || map[biu->y][biu->x + 1] == 1) {
					SHELL
				}
				else if (map[biu->y][biu->x] == 2 || map[biu->y][biu->x] == 4) {
					DELETE_B
				}
				else if (map[biu->y][biu->x] == 200 && biu->y < (MAP_Y - 4)) {//待加线程
					for (size_t i = 0; i < eARR_size; i++) {
						if (biu == nullptr)break;
						if (enemyArr[i].x == biu->x && enemyArr[i].y == biu->y) {
						clearrectangle(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
								putimage(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
							putimage(biu->x * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}
							enemyArr[i].live = false;
							map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
							map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x + 1] = 0;
							DELETE_B break;
						}
						else if (enemyArr[i].x == (biu->x-1) && enemyArr[i].y == biu->y) {
							clearrectangle((biu->x - 1)* IMAGE_SIZE, (biu->y)* IMAGE_SIZE, (biu->x + 1)* IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 2)* IMAGE_SIZE);
								mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
								for (size_t i = 0; i < BLAST * 2; i++) {
									if (i >= BLAST) {
										putimage((biu->x - 1)* IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
									}
									else {
										putimage((biu->x - 1)* IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
									}
								}
								enemyArr[i].live = false;
								map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
								map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x - 1] = 0;
								DELETE_B break;
						}
					}
				}
				else {
					putimage(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, bullImg);
				}
			}
			else if (myTank->tDir == LEFT) {

				if (myTank->x < 1) {
					return;
				}
				else {
					biu = new Bullet(); biu->bDir = myTank->tDir;
					biu->x = myTank->x - 1; biu->y = myTank->y;
				}
				if (map[biu->y][biu->x] == 1 || map[biu->y + 1][biu->x] == 1) {
					SHELL2
				}
				else if (map[biu->y][biu->x] == 2 || map[biu->y][biu->x] == 4) {
					DELETE_B
				}
				else if (map[biu->y][biu->x] == 200 && biu->x > 0) {//待加线程
					for (size_t i = 0; i < eARR_size; i++) {
						if (biu == nullptr)break;
						if (enemyArr[i].x == (biu->x - 1) && enemyArr[i].y == biu->y) {
						clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
								putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
								putimage((biu->x - 1) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}	
							enemyArr[i].live = false;
							map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
							map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x - 1] = 0;
							DELETE_B break;
						}
						else if (enemyArr[i].x == (biu->x - 1) && enemyArr[i].y == (biu->y-1)) {
							clearrectangle((biu->x - 1) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
							mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
									putimage((biu->x - 1) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
									putimage((biu->x - 1) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}
							enemyArr[i].live = false;
							map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;
							map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x - 1] = 0;
							DELETE_B break;
						}
					}

				}
				else {
					putimage(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, bullImg);
				}
			}
			else if (myTank->tDir == RIGHT) {
				if (myTank->x > (MAP_Y - 3)) {
					DELETE_B return;
				}
				else {
					biu = new Bullet(); biu->bDir = myTank->tDir;
					biu->x = myTank->x + 2; biu->y = myTank->y;
				}if (map[biu->y][biu->x] == 1 || map[biu->y + 1][biu->x] == 1) {
					SHELL2
				}
				else if (map[biu->y][biu->x] == 2 || map[biu->y][biu->x] == 4) {
					DELETE_B
				}
				else if (map[biu->y][biu->x] == 200 && biu->x < (MAP_Y - 1)) {//待加线程
					for (size_t i = 0; i < eARR_size; i++) {
						if (biu == nullptr)break;
						if (enemyArr[i].x == biu->x && enemyArr[i].y == biu->y) {
							clearrectangle((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);
							mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
									putimage((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
									putimage((biu->x) * IMAGE_SIZE, (biu->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}enemyArr[i].live = false;
							map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
							map[biu->y + 1][biu->x] = 0; map[biu->y + 1][biu->x + 1] = 0;
							DELETE_B break;							
						}
						else if (enemyArr[i].x == biu->x && enemyArr[i].y == (biu->y-1)) {
							clearrectangle((biu->x) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
							mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);//		
							for (size_t i = 0; i < BLAST * 2; i++) {
								if (i >= BLAST) {
									putimage((biu->x) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
								}
								else {
									putimage((biu->x) * IMAGE_SIZE, (biu->y-1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
								}

							}enemyArr[i].live = false;
							map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;
							map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x + 1] = 0;
							DELETE_B break;
						}
					}
				}
				else {
					putimage(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE + IMAGE_SIZE / 2, bullImg);
				}

			}
		}
		break;
	case KEY_SPACE://空格退出
	case 'p':
		key = _getch();//
		break;
	default:
		break;
	}
}


bool Enemy::move(IMAGE* eTankImg, Tank* myTank) {
	bool canMove = 1;
	srand((unsigned)time(NULL));//产生随机(时间)种子
	this->tDir = (TankDir)(rand() % Dall);//取余，保证数字在0-3	
		if (y < myTank->y|| this->ett ==m_home) {
			if (tDir == UP)return 0;
		}
		else {
			if (tDir == DOWN)return 0;
		}	
	switch (this->tDir) {
	case UP:
		IF_TANK_DIR2(UP)//转向
			if (map[this->y - 1][this->x] == 0 && map[this->y - 1][this->x + 1] == 0 && this->y > 0) {
				map[this->y + 1][this->x] = 0; map[this->y + 1][this->x + 1] = 0;
				//ENE_MOVE2(y, -)
				clearrectangle(this->x * IMAGE_SIZE, this->y * IMAGE_SIZE, (this->x + 2) * IMAGE_SIZE, (this->y + 2) * IMAGE_SIZE);
				this->y -= 1; putimage(this->x * IMAGE_SIZE, this->y * IMAGE_SIZE, &eTankImg[tDir]);
				//MAP_MOVE2(, , +, 1)
				MAP_MOVE2
			}
			else {
				canMove = 0;
			}
		break;
	case RIGHT:

		IF_TANK_DIR2(RIGHT)
			if (map[this->y][this->x + 2] == 0 && map[this->y + 1][this->x + 2] == 0 && this->x < 24) {
				map[this->y][this->x] = 0; map[this->y + 1][this->x] = 0;
				ENE_MOVE2(x, +)
					//MAP_MOVE2(+, 1, , )
					MAP_MOVE2
			}
			else {
				canMove = 0;
			}
		break;
	case DOWN:

		IF_TANK_DIR2(DOWN)
			if (map[this->y + 2][this->x] == 0 && map[this->y + 2][this->x + 1] == 0 && this->y < 24) {
				map[this->y][this->x] = 0; map[this->y][this->x + 1] = 0;
				ENE_MOVE2(y, +)
					//MAP_MOVE2(, , +, 1)
					MAP_MOVE2
			}
			else {
				canMove = 0;
			}
		break;
	case LEFT:
		IF_TANK_DIR2(LEFT)
			if (map[this->y][this->x - 1] == 0 && map[this->y + 1][this->x - 1] == 0 && this->x > 0) {
				map[this->y][this->x + 1] = 0; map[this->y + 1][this->x + 1] = 0;
				ENE_MOVE2(x, -)
					//MAP_MOVE2(+, 1, , )
					MAP_MOVE2
			}
			else {
				canMove = 0;
			}
		break;

	}return canMove;


}
bool Enemy::enemyCreateBullet(IMAGE * blastImg,IMAGE* eBullImg) {
	if (bullet == nullptr) return false;
	if (bullet->live == false) {
		if (this->tDir == UP) {
			if ((this->y - 1) < 0) {
				bullet->live=false;
			}
			else {
				bullet->live = true; bullet->bDir = this->tDir;
				bullet->x = this->x; bullet->y = this->y - 1;
			}

			if (map[bullet->y][bullet->x] == 1 || map[bullet->y][bullet->x + 1] == 1) {
				E_SHELL
			}
			else if (map[bullet->y][bullet->x] == 2) {
				bullet->live = false;//delete bullte;
			}
			else if (map[bullet->y][bullet->x] == 100) {//待加线程
				clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE);
				mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}bullet->live = false;//delete bullet; 
				endGame(true); return true;
			}
			else {
				putimage(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, eBullImg);
			}

		}
		else if (this->tDir == DOWN) {

			if (this->y > (MAP_Y - 3)) {
				bullet->live = false;
			}
			else {
				bullet->live=true; bullet->bDir = this->tDir;
				bullet->x = this->x; bullet->y = this->y + 2;
			}

			if (map[bullet->y][bullet->x] == 1 || map[bullet->y][bullet->x + 1] == 1) {
				E_SHELL
			}
			else if (map[bullet->y][bullet->x] == 2) {
				bullet->live = false;//delete bullet;
			}
			else if ((map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4 )&& bullet->y < (MAP_Y - 4)) {//待加线程
				clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE);
				mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}
				bullet->live = false;//delete bullet; 
				endGame(true); return true;
			}
			else {
				putimage(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, eBullImg);
			}
		}
		else if (this->tDir == LEFT) {
			if (this->x < 1) {
				bullet->live = false;
			}
			else {
				bullet->live=true; bullet->bDir = this->tDir;
				bullet->x = this->x - 1; bullet->y = this->y;
			}
			if (map[bullet->y][bullet->x] == 1 || map[bullet->y + 1][bullet->x] == 1) {
				E_SHELL2
			}
			else if (map[bullet->y][bullet->x] == 2) {
				bullet->live = false;//delete bullet;
			}
			else if ((map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4)&& bullet->x > 0) {//待加线程
				clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}

				}
				bullet->live = false;//delete bullet; 
				endGame(true); return true;
			}
			else {
				putimage(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, eBullImg);
			}
		}
		else if (this->tDir == RIGHT) {
			if (this->x > (MAP_Y - 3)) {
				bullet->live = false; //delete bullet;
			}
			else {
				bullet->live=true; bullet->bDir = this->tDir;
				bullet->x = this->x + 2; bullet->y = this->y;
			}if (map[bullet->y][bullet->x] == 1 || map[bullet->y + 1][bullet->x] == 1) {
				E_SHELL2
			}
			else if (map[bullet->y][bullet->x] == 2) {
				bullet->live = false;
				//delete bullet;
			}
			else if ((map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4)&& bullet->x < (MAP_Y - 1)) {//待加线程
				clearrectangle((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
				mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
				for (size_t i = 0; i < BLAST * 2; i++) {
					if (i >= BLAST) {
						putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					}
					else {
						putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					}
				}	
				bullet->live = false;//delete bullet; 
				endGame(true); return true;
			}
			else {
				putimage(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, eBullImg);
			}
		}
	}
	return false;		//break;
}


inline __int64 _GetSysTickCount64() {
	LARGE_INTEGER TicksPerSecond = { 0 };
	LARGE_INTEGER Tick;
	if (!TicksPerSecond.QuadPart)
		QueryPerformanceFrequency(&TicksPerSecond);
	QueryPerformanceCounter(&Tick);
	__int64 Seconds = Tick.QuadPart / TicksPerSecond.QuadPart;
	__int64 LeftPart = Tick.QuadPart - (TicksPerSecond.QuadPart * Seconds);
	__int64 MillSeconds = LeftPart * 1000 / TicksPerSecond.QuadPart;
	__int64 Ret = Seconds * 1000 + MillSeconds;
	return Ret;
}
void endGame(bool gameOver) {
	cleardevice(); 
	if (gameOver) {
		IMAGE gameOverImage;
		loadimage(&gameOverImage, "res/failure.jpg", 430, 244, true);
		putimage(200, 100, &gameOverImage);
	}
	else {
		IMAGE endImage;
		loadimage(&endImage, "res/success.jpg", 430, 244, true);
		putimage(200, 100, &endImage);
	}
}
bool Enemy::enemyBulletMove(IMAGE* blastImg, IMAGE* eBullImg, Tank* myTank, Enemy* enemyArr, size_t eARR_size) {
	//子弹live活的才动
	if (bullet == nullptr) return false;
	if (bullet->live==true) {			
		if (bullet->bDir == UP) {
			if (bullet->y < 0) {
				bullet->live = false;
				clearrectangle(bullet->x * IMAGE_SIZE, 0, (bullet->x + 1) * IMAGE_SIZE+ IMAGE_SIZE/2,IMAGE_SIZE);
			}
			eBULLET_UP//子弹打到不可消墙
			else if (map[bullet->y][bullet->x] == 100 ) {
				mciSendString(_T("play res/boom.mp3"), 0, 0, 0);
				endGame(true); return true;
			}
			else if (map[bullet->y][bullet->x] == 200) {
					//if (myTank->x == bullet->x && myTank->y == (bullet->y - 1)) {
					//	clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//子弹打到敌方		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		eBULLET_BLAST//爆炸动画
					//	}						 
					//}
					//else if (myTank->x == (bullet->x - 1) && myTank->y == (bullet->y - 1)) {
					//	clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}							
					//		
					//	}
					//}
				for (size_t i = 0; i < eARR_size; i++) {
					if (bullet == nullptr)break;
					if (enemyArr[i].x == (bullet->x) && enemyArr[i].y == (bullet->y - 1)) {
						clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//子弹打到敌方		
						for (size_t i = 0; i < BLAST * 2; i++) {
							eBULLET_BLAST//爆炸动画
						}
						enemyArr[i].live = false; ENEMY_INIT(bullet) bullet->live = false; break;
					}
					else if ((enemyArr[i].x) == (bullet->x - 1) && enemyArr[i].y == (bullet->y - 1)) {
						clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}
							enemyArr[i].live = false; ENEMY_INIT2(bullet) bullet->live = false; break;
						}

					}
				}
			}
			else {
				//Sleep(30); 
				eBULLET_yMOVE
			}
		}
		else if (bullet->bDir == DOWN) {
			if (bullet->y > (MAP_Y - 2)) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);
				bullet->live = false; return false;
			}
			if (map[bullet->y][bullet->x] == 1 || map[bullet->y][bullet->x + 1] == 1) {
				E_SHELL
			}
			else if (map[bullet->y + 1][bullet->x] == 2 ) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);
				bullet->live = false;
			}
			else if (map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4) {
				mciSendString(_T("play res/boom.mp3"), 0, 0, 0);
				endGame(true); return true;
			}
			else if ( map[bullet->y][bullet->x] == 200) {//待加线程
					//if ((myTank->x) == bullet->x && myTank->y == bullet->y) {
					//	clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}
					//	}
					//	
					//}
					//else if (myTank->x == (bullet->x - 1) && myTank->y == bullet->y) {
					//	clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 2) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}
					//	}
					//	
					//}
				for (size_t i = 0; i < eARR_size; i++) {
					if (bullet == nullptr)break;
					if (enemyArr[i].x == (bullet->x) && enemyArr[i].y == bullet->y) {
						clearrectangle(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage(bullet->x * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}

						}
						enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x + 1] = 0;
						map[bullet->y + 1][bullet->x] = 0; map[bullet->y + 1][bullet->x + 1] = 0;
						bullet->live = false; break;
					}
					else if ((enemyArr[i].x) == (bullet->x - 1) && enemyArr[i].y == bullet->y) {
						clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}
						}
						enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x - 1] = 0;
						map[bullet->y + 1][bullet->x] = 0; map[bullet->y + 1][bullet->x - 1] = 0;
						bullet->live = false; break;
					}
				}
			}
			else {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);
				bullet->y += 1;
				putimage(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, eBullImg);
			}

		}
		else if (bullet->bDir == LEFT) {
			if (bullet->x < 1) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->live = false; return false;
			}if (map[bullet->y][bullet->x] == 1 || map[bullet->y + 1][bullet->x] == 1) {
				E_SHELL2
			}
			else if (map[bullet->y][bullet->x - 1] == 2  || map[bullet->y + 1][bullet->x - 1] == 2) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->live = false;
			}
			else if (map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4) {
				mciSendString(_T("play res/boom.mp3"), 0, 0, 0);
				endGame(true); return true;
			}
			else if (map[bullet->y][bullet->x] == 200 && bullet->x > 0) {//待加线程		
					//if (myTank->x == (bullet->x - 1) && myTank->y == bullet->y) {
					//	clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}

					//	}
					//	endGame(true); return true;
					//}
					//else if (myTank->x == (bullet->x - 1) && myTank->y == (bullet->y - 1)) {
					//	clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}

					//	}
					//	
					//}
				for (size_t i = 0; i < eARR_size; i++) {
					if (bullet == nullptr)break;
					if (enemyArr[i].x == (bullet->x - 1) && enemyArr[i].y == bullet->y) {
						clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}

						}
						enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x - 1] = 0;
						map[bullet->y + 1][bullet->x] = 0; map[bullet->y + 1][bullet->x - 1] = 0;
						bullet->live = false; break;
					}
					else if (enemyArr[i].x == (bullet->x - 1) && enemyArr[i].y == (bullet->y - 1)) {
						clearrectangle((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x - 1) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}

						}
						enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x - 1] = 0;
						map[bullet->y - 1][bullet->x] = 0; map[bullet->y - 1][bullet->x - 1] = 0;
						bullet->live = false; break;
					}
				}
			
			}
			else {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->x -= 1;
				putimage(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, eBullImg);
			}
		}
		else if (bullet->bDir == RIGHT) {
			if (bullet->x > (MAP_Y - 2)) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->live = false; return false;
			}

			if (map[bullet->y][bullet->x] == 1 || map[bullet->y + 1][bullet->x] == 1) {
				E_SHELL2
			}
			else if (map[bullet->y][bullet->x + 1] == 2  || map[bullet->y + 1][bullet->x + 1] == 2) {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->live = false;
			}
			else if (map[bullet->y][bullet->x] == 100 || map[bullet->y][bullet->x] == 4) {
				mciSendString(_T("play res/boom.mp3"), 0, 0, 0);
				endGame(true); return true;
			}
			else if (map[bullet->y][bullet->x] == 200 && bullet->x < (MAP_Y - 1)) {//待加线程
					//if (myTank->x == bullet->x && myTank->y == bullet->y) {
					//	clearrectangle((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}

					//	}
					//}
					//else if (myTank->x == bullet->x && myTank->y == (bullet->y - 1)) {
					//	clearrectangle((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
					//	mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
					//	for (size_t i = 0; i < BLAST * 2; i++) {
					//		if (i >= BLAST) {
					//			putimage((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
					//		}
					//		else {
					//			putimage((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
					//		}

					//	}endGame(true); return true;
					//}
				for (size_t i = 0; i < eARR_size; i++) {
					if (bullet == nullptr)break;
					if (enemyArr[i].x == bullet->x && enemyArr[i].y == bullet->y) {
						clearrectangle((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x) * IMAGE_SIZE, (bullet->y) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}

						}enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x + 1] = 0;
						map[bullet->y + 1][bullet->x] = 0; map[bullet->y + 1][bullet->x + 1] = 0;
						bullet->live = false; break;
					}
					else if (enemyArr[i].x == bullet->x && enemyArr[i].y == (bullet->y - 1)) {
						clearrectangle((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
						mciSendString(_T("play res/hit.mp3"), 0, 0, 0);//		
						for (size_t i = 0; i < BLAST * 2; i++) {
							if (i >= BLAST) {
								putimage((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]); Sleep(10);
							}
							else {
								putimage((bullet->x) * IMAGE_SIZE, (bullet->y - 1) * IMAGE_SIZE, &blastImg[i]); Sleep(10);
							}

						}enemyArr[i].live = false;
						map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x + 1] = 0;
						map[bullet->y - 1][bullet->x] = 0; map[bullet->y - 1][bullet->x + 1] = 0;
						bullet->live = false; break;
					}
				}
				
			}
			else {
				//Sleep(30);
				clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE + IMAGE_SIZE / 2);
				bullet->x += 1;
				putimage(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE + IMAGE_SIZE / 2, eBullImg);
			}
		}
	}
	return false;
}

