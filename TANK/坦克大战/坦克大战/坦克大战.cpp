// 坦克大战.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"


int main()
{
	
	startgraph();
	initGameMap();
	mciSendString(_T("play res/background.mp3"), 0, 0, 0);	
	play();
	/*Enemy enemyTank{ 0, 0, UP };
	Enemy enemyTank2{ 12, 2, LEFT };
	Enemy enemyTank3{ 24, 3, DOWN };
	vector<Enemy> enemyArr = { enemyTank ,enemyTank2 ,enemyTank3 };*/
	//Enemy* enemy = new Enemy{ 0, 0, UP };
	//Enemy enemy{ 2, 0, UP };
	//Enemy enemy4=enemyTank3 = 
	//enemyArr[3] = enemy;
	 //enemyArr[2]=enemy;
	//enemyArr.push_back(enemy);
	 //vector<Enemy>::iterator it;
	 //tempIterator = enemyArr[2].at();
	 //enemyArr.remove(2);
	 //for (it = enemyArr.begin(); it != enemyArr.end(); ) {
		// if ((*it).x  == 0) {
		//	 it = enemyArr.erase(it);
		// }
		// else {
		//	 ++it; //cout << enemyArr[i];
		// }
	 //}
	 //for (unsigned int i = 0; i < enemyArr.size(); i++) {
		// cout << enemyArr.at(i).x << "----y= "<<enemyArr[i].y << endl;
	 //}
	
	//cout << "取地址"<<enemyArr[2].x<<"取名字"<<"第三个"<<&enemyTank3 ;
	/**/
	/*int a[5]; int* p = a; p[1] = 5; for (size_t i = 0; i < _countof(a); i++) {

	}*/
	system("pause");
}

