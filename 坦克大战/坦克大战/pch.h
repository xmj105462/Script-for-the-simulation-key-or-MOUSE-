
#ifndef PCH_H
#define PCH_H
#include<graphics.h>
#include<conio.h>
#include<MMStream.h>//播放音乐需要的头文件
#pragma comment(lib,"winmm.lib")//加载winmm库文件
#include <iostream>
#include<vector>
// TODO: 添加要在此处预编译的标头
constexpr short START_X = 781;
constexpr short LOGO_X = 433;
constexpr short RECTANGLE_X1 = (START_X - LOGO_X) / 2 + 30;
constexpr short RECTANGLE_X2 = (START_X - LOGO_X) / 2 + 150;
constexpr short TEXT_SIZE = 40;
constexpr short MAP_Y = 26;
constexpr auto IMAGE_SIZE = 30;
constexpr unsigned short KEY_UP = 72;
constexpr unsigned short KEY_RIGHT = 77;
constexpr unsigned short KEY_DOWN = 80;
constexpr unsigned short KEY_LEFT = 75;
constexpr unsigned short KEY_SPACE = 32;
constexpr unsigned short BLAST = 8;
#define LOAD_TANK(T0,T1,T2) loadimage(&T0[T1], _T(T2), IMAGE_SIZE<<1, IMAGE_SIZE<<1, true);
//地图跟着移动
#define MAP_MOVE map[myTank->y][myTank->x] = 100; map[myTank->y][myTank->x+1] = 100;\
map[myTank->y+1][myTank->x] = 100; map[myTank->y+1][myTank->x+1] = 100;
#define MAP_MOVE2 map[this->y][this->x] = 200; map[this->y][this->x+1] = 200;\
map[this->y+1][this->x] = 200; map[this->y+1][this->x+1] = 200;
//键盘移动,敌方自动移动
#define KEY_MOVE(T1,T2)  clearrectangle(myTank->x*IMAGE_SIZE, myTank->y*IMAGE_SIZE, \
(myTank->x+2)*IMAGE_SIZE, (myTank->y+2)*IMAGE_SIZE);\
myTank->T1 T2= 1;putimage(myTank->x * IMAGE_SIZE, myTank->y * IMAGE_SIZE, &myTankImg[myTank->tDir]);
#define ENE_MOVE2(T1,T2)  clearrectangle(this->x*IMAGE_SIZE, this->y*IMAGE_SIZE,(this->x+2)*IMAGE_SIZE, (this->y+2)*IMAGE_SIZE);\
this->T1 T2=1;putimage(this->x * IMAGE_SIZE, this->y * IMAGE_SIZE, &eTankImg[tDir]);

//子弹移动
#define BULLET_yMOVE  clearrectangle(biu->x * IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE );\
biu->y -= 1;putimage(biu->x* IMAGE_SIZE + IMAGE_SIZE / 2, biu->y * IMAGE_SIZE, bullImg);
//敌人子弹
#define eBULLET_yMOVE  clearrectangle(bullet->x * IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE );\
bullet->y -= 1;putimage(bullet->x* IMAGE_SIZE + IMAGE_SIZE / 2, bullet->y * IMAGE_SIZE, eBullImg);
//判断当前坦克方向是否和按键相同,敌方
#define IF_TANK_DIR(T1) if (myTank->tDir != T1) {myTank->tDir = T1;\
putimage(myTank->x * IMAGE_SIZE, myTank->y * IMAGE_SIZE, &myTankImg[myTank->tDir]);}
#define IF_TANK_DIR2(T1) if (this->tDir != T1) {this->tDir = T1;\
putimage(this->x * IMAGE_SIZE, this->y * IMAGE_SIZE, &eTankImg[this->tDir]);}

//坦克位置初始化
#define TANK_INIT(T1,T2) map[T1.y][T1.x] = T2; map[T1.y][T1.x+1] = T2;\
map[T1.y + 1][T1.x] = T2; map[T1.y + 1][T1.x + 1] = T2;
#endif //PCH_H
#define LOAD_BLAST(T1,T2) loadimage(&blastImg[T1], _T(T2), IMAGE_SIZE<<1, 47, true);
#define ENEMY_INIT map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;\
map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x + 1] = 0;
#define ENEMY_INIT2 map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;\
map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x - 1] = 0;

//炮击到墙
#define SHELL clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE);\
map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0; delete biu; biu = nullptr;
#define SHELL2 clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE, (biu->y + 2) * IMAGE_SIZE);\
map[biu->y][biu->x] = 0; map[biu->y+1][biu->x] = 0; delete biu; biu = nullptr;
//敌方子弹
#define E_SHELL clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 2) * IMAGE_SIZE, (bullet->y + 1) * IMAGE_SIZE);\
map[bullet->y][bullet->x] = 0; map[bullet->y][bullet->x + 1] = 0; bullet->live = false; 
#define E_SHELL2 clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE, (bullet->y + 2) * IMAGE_SIZE);\
map[bullet->y][bullet->x] = 0; map[bullet->y+1][bullet->x] = 0; bullet->live = false; 
//#define us_INIT map[biu->y][biu->x] = 0; map[biu->y][biu->x + 1] = 0;\
//map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x + 1] = 0;
//#define ENEMY_INIT2 map[biu->y][biu->x] = 0; map[biu->y][biu->x - 1] = 0;\
//map[biu->y - 1][biu->x] = 0; map[biu->y - 1][biu->x - 1] = 0;
//子弹向上
#define BULLET_UP else if (map[biu->y][biu->x] == 1 || map[biu->y][biu->x + 1] == 1) {SHELL}\
else if (map[biu->y - 1][biu->x] == 2) {Sleep(30);\
	clearrectangle(biu->x * IMAGE_SIZE, biu->y * IMAGE_SIZE, (biu->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (biu->y + 1) * IMAGE_SIZE);\
	delete biu; biu = nullptr;}

#define eBULLET_UP else if (map[bullet->y][bullet->x] == 1 || map[bullet->y][bullet->x + 1] == 1) {E_SHELL}\
else if (map[bullet->y - 1][bullet->x] == 2) {Sleep(30);\
	clearrectangle(bullet->x * IMAGE_SIZE, bullet->y * IMAGE_SIZE, (bullet->x + 1) * IMAGE_SIZE + IMAGE_SIZE / 2, (bullet->y + 1) * IMAGE_SIZE);\
	bullet->live=false;}

#define BULLET_UP2 else if (map[biu->y][biu->x] == 200) {\
for (size_t i = 0; i < eARR_size; i++) {if (biu == nullptr)break;\
if (enemyArr[i].x == biu->x && enemyArr[i].y == (biu->y - 1)){\
	clearrectangle(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, (biu->x + 2) * IMAGE_SIZE, (biu->y + 1) * IMAGE_SIZE);\
	mciSendString(_T("play res/paoji.mp3"), 0, 0, 0);		
#define BULLET_BLAST if (i >= BLAST) {\
						putimage(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]);Sleep(10);\
						}\
						else {\
							putimage(biu->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]);Sleep(10);}

#define eBULLET_BLAST if (i >= BLAST) {\
						putimage(bullet->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i - 2 * (i - BLAST + 1)]);Sleep(10);\
						}\
						else {\
							putimage(bullet->x * IMAGE_SIZE, (biu->y - 1) * IMAGE_SIZE, &blastImg[i]);Sleep(10);}
//子弹向下
#define BULLET_DOWN else if (map[biu->y][biu->x] == 1 || map[biu->y][biu->x + 1] == 1) {SHELL}\
BULLET_UP BULLET_UP2 for (size_t i = 0; i < BLAST * 2; i++) {BULLET_BLAST}ENEMY_INIT delete biu; biu = nullptr;}else { BULLET_yMOVE Sleep(30); }\			

#define DELETE_B delete biu; biu = nullptr;
using namespace std;
//定义地图数组可消除墙为1，不可消除墙为2，老鹰(3,4),w方坦克 100 - 109,d方坦克200
int map[MAP_Y][MAP_Y] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 },
{ 2, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 2, 2 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
typedef enum {
	wall, unWall, home, all
}MapEnum;
typedef enum {
	us,enemy,Tall
}TankType;
typedef enum {
	me, m_home, eTall
}eTankType;
typedef enum {
	UP, DOWN, LEFT, RIGHT, Dall
}TankDir;
struct Tank {
	short x;
	short y;
	TankDir tDir;
	TankType type;

}; 
class Bullet {
public:
	short x;
	short y;
	TankDir bDir;
	//TankType type;
	bool live;
	/*Bullet(Bullet* bull) {
		x = bull->x;
	}*/Bullet() {
		x = 0; y = 0; bDir = UP; live = false;
	}
};
class Enemy {
public:
	short x;
	short y;
	TankDir tDir;
	bool live;
	Bullet* bullet = nullptr;
	eTankType ett;
	Enemy(short x,short y,TankDir tDir,bool live=true, eTankType ett=me) {
		this->x =x; this->y = y; this->tDir = tDir; this->live = live; this->ett = ett;
		//cout << "重载默认"<<this<<endl;
	}Enemy() {
		this->x = 4; this->y = 0; this->tDir = DOWN; this->live = true; this->ett=m_home;
		//cout << "默认"<<this<<endl;
	}
	Enemy(const Enemy& other) {
		x = other.x; y = other.y; tDir = other.tDir; live = other.live; this->ett = other.ett;
		bullet = new Bullet();
		//bull=

	//cout << "拷贝"<<this<<endl;
	}
	~Enemy() {if(bullet!=nullptr)delete bullet; }
	

	 const Enemy& operator=( const Enemy& other) {
		 x = other.x; y = other.y; tDir = other.tDir; live = other.live; this->ett = other.ett;
		 bullet = new Bullet();
		//cout << "赋值\n"<<x<<endl; 
		return other;
	}

	bool enemyCreateBullet(IMAGE* blastImg, IMAGE* eBullImg);
	bool enemyBulletMove(IMAGE* blastImg, IMAGE* eBullImg, Tank* myTank);
	bool move(IMAGE* eTankImg, Tank* myTank);
};


void startgraph();
void initGameMap();
void bulletMove(IMAGE *bullImg, IMAGE* blastImg, Enemy*enemyArr, size_t eARR_size);
void keyCheck1(short key, Tank *myTank, IMAGE *myTankImg, IMAGE *bullImg, IMAGE* blastImg, Enemy* enemyArr, size_t eARR_size);
__int64 _GetSysTickCount64();
void endGame(bool gameOver);
void play();
