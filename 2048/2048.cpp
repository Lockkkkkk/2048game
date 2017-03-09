// 2048.cpp : 定义控制台应用程序的入口点。
//




#include "stdafx.h"
#include "My2048.h"
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	char Move;
	cout << "C++实现2048" << endl;
	int MapPos[4][4] = {
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	};
	My2048 mGameData;
	mGameData.Init(MapPos);
	while (mGameData.UnEmptyPosNum < mGameData.MapSize * mGameData.MapSize)
	{
		if (mGameData.CheckCanMove(MapPos) == false) {
			break;
		}
		cout << "输入WASD来移动数字" << endl;
		cin >> Move;
		if (Move == 'A' ||Move == 'S'|| Move == 'W' ||Move == 'D')
		{
			Move = Move + 32;
		}
		switch (Move) {
		case 'w':
			printf("上\n");
			mGameData.UpdateUI(My2048::Up, MapPos);
			continue;
		case 'a':
			printf("左\n");
			mGameData.UpdateUI(My2048::Left, MapPos);
			continue;
		case 'd':
			printf("右\n");
			mGameData.UpdateUI(My2048::Right, MapPos);
			continue;
		case's':
			printf("下\n");
			mGameData.UpdateUI(My2048::Down, MapPos);
			continue;
		default:
			continue;
		}
	}
	return 0;
}

