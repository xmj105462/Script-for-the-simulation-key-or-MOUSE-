#include"Man.h"
#include"Maze.h"
#include<iostream>
#include<graphics.h>

constexpr unsigned short SCREEN_WIDTH = 832;
constexpr unsigned short SCREEN_HEIGHT = 560;
constexpr unsigned short START_X = 180;
constexpr unsigned short START_Y = 80;
constexpr unsigned short IMAGE_SIZE = 61;
#define MAN_PUTiMAGE putimage(START_X + (ls.top->date.x) * IMAGE_SIZE, START_Y + (ls.top->date.y) * IMAGE_SIZE, &manImage);
#define CLEAR_FRONT clearrectangle(START_X + (ls.top->date.x) * IMAGE_SIZE, START_Y + (ls.top->date.y) * IMAGE_SIZE, START_X + (ls.top->date.x + 1) * IMAGE_SIZE, START_Y + (ls.top->date.y + 1) * IMAGE_SIZE);
using namespace std;
int map[MAP_Y][MAP_X] = { {0, 0, 1, 0, 0, 0 },
							  {0, 0, 1, 1, 1, 0 },
							  {0, 0, 1, 0, 0, 0 },
							  {0, 1, 1, 1, 1, 0 },
							  {0, 0, 1, 0, 1, 0 },
							  {0, 0, 0, 0, 1, 0 }, };
IMAGE manImage;
inline void judgeValue(LS& ls, DLhead& head, int posNext_y, int posNext_x);
	void initPosition(DLhead& head, LS& ls) {
		DateLink *dateNode = new DateLink();
		head.next = dateNode;
		dateNode->date.y = 0; dateNode->date.x = 2;
		pushLinkStack(ls, *dateNode,head);
		  ++ls.mapValue;
		map[ls.top->date.y][ls.top->date.x] = ls.mapValue;
		setcolor(LIGHTGREEN);
		settextstyle(50, 0, _T("微软雅黑"));
		loadimage(&manImage, _T("man.bmp"), IMAGE_SIZE, IMAGE_SIZE, true);
		putimage(START_X + (ls.top->date.x) * IMAGE_SIZE, START_Y + (ls.top->date.y) * IMAGE_SIZE, &manImage);//人物	
	}

	void move(LS& ls, DLhead& head) {
		while (ls.length>0) {
			Sleep(100);
			judge(ls,head);
			if (ls.top->date.y==5&& (ls.top->date).x==4) {//到达终点
				for (int j = 0; j < MAP_Y; j++) {
					for (int i = 0; i < MAP_X; i++) {
						cout << map[j][i] << "\t";
					}cout << endl;
				}//cout << "恭喜逃出生天\n"; 				
				outtextxy(550, 200, _T("恭喜逃出生天"));
				return;
			}			
		}//cout << "遗憾你将死在这里\n";
		outtextxy(500, 200, _T("遗憾你将死在这里"));
	}

	bool judge(LS& ls, DLhead& head) {//当前位置		
		int current_y = (ls.top->date).y; int current_x = (ls.top->date).x;
		if (current_y >0) {//上
			if (map[current_y - 1][current_x]==1) {
				//清除移动前的区域
				CLEAR_FRONT
				judgeValue(ls, head, current_y - 1, current_x);//移动
				MAN_PUTiMAGE//画移动后的图
				return true;
			};
		}
		if (current_x > 0) {//左
			if (map[current_y][current_x-1]==1) {
				CLEAR_FRONT
				judgeValue(ls, head, current_y, current_x-1);
				MAN_PUTiMAGE
				return true;
			};
		}
		if (current_x < (MAP_X-1)) {//右
			if (map[current_y][current_x+1]==1) {
				CLEAR_FRONT
				judgeValue(ls, head, current_y, current_x+1);
				MAN_PUTiMAGE
				return true;
			};
		}
		if (current_y < (MAP_Y-1)) {//下
			if (map[current_y +1][current_x]==1) {
				CLEAR_FRONT
				judgeValue(ls, head, current_y + 1, current_x);
				MAN_PUTiMAGE
				return true;
			};
		}
		//死胡同
		DateLink popNode;
		if (ls.length>1)CLEAR_FRONT
		popLinkStack(ls, popNode);
		if(ls.length==0)return false;
		MAN_PUTiMAGE
		--ls.mapValue;
		map[popNode.date.y][popNode.date.x] = 0;
		return false;
	}

	void initFrame() {
		IMAGE bkImage; IMAGE wallImage;
			initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
			loadimage(&bkImage, _T("blackground.gif"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
			putimage(0, 0, &bkImage);//背景	
			loadimage(&wallImage, _T("wall.bmp"), IMAGE_SIZE, IMAGE_SIZE, true);
			for (unsigned short j = 0; j < MAP_Y; j++) {
				for (unsigned short i = 0; i < MAP_X; i++) {//绘制地图
					if(map[j][i]==0)putimage(START_X + i * IMAGE_SIZE, START_Y + j * IMAGE_SIZE, &wallImage);
				}
			}
			
		
	}

	inline void judgeValue(LS& ls, DLhead& head,int posNext_y,int posNext_x) {
		DateLink* dateNode = new DateLink();
		ls.top->next = dateNode;
		dateNode->date.y = posNext_y; dateNode->date.x = posNext_x;
		pushLinkStack(ls, *dateNode, head);
		++ls.mapValue;
		map[ls.top->date.y][ls.top->date.x] = ls.mapValue;
	}
