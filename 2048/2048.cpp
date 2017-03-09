// 2048.cpp : �������̨Ӧ�ó������ڵ㡣
//




#include "stdafx.h"
#include "My2048.h"
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	char Move;
	cout << "C++ʵ��2048" << endl;
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
		cout << "����WASD���ƶ�����" << endl;
		cin >> Move;
		if (Move == 'A' ||Move == 'S'|| Move == 'W' ||Move == 'D')
		{
			Move = Move + 32;
		}
		switch (Move) {
		case 'w':
			printf("��\n");
			mGameData.UpdateUI(My2048::Up, MapPos);
			continue;
		case 'a':
			printf("��\n");
			mGameData.UpdateUI(My2048::Left, MapPos);
			continue;
		case 'd':
			printf("��\n");
			mGameData.UpdateUI(My2048::Right, MapPos);
			continue;
		case's':
			printf("��\n");
			mGameData.UpdateUI(My2048::Down, MapPos);
			continue;
		default:
			continue;
		}
	}
	return 0;
}

