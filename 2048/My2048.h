// My2048.cpp: implementation of the My2048 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Windows.h>
#include "time.h"
#include "iostream"
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
class My2048
{
public:
	enum MoveNormal {//枚举4个方向
		Up,
		Down,
		Left,
		Right,
	};
	int UnEmptyPosNum; //当前不是0的方块进行记数
	int StartShowNumCount;//一开始显示的数字，0代表没有方块
	int MapSize;//几X几的2048游戏
	int MaxNum;//允许出现的最大值
	int MinNum;//允许出现的最小值
	void UpdateUI(MoveNormal, int xy[4][4]); //更新UI
	void FreshUI(int xy[4][4]);//刷新UI
	int GetMerge(int num1, int num2);//加法
	bool CanMerge(int num1, int num2);//判定是否可加
	void Init(int xy[4][4]);//主界面
	bool CanMoveX(int xy[4][4]);//x轴方向是否可以进行移动
	bool CanMoveY(int xy[4][4]);//y轴方向是否可以进行移动
	bool CheckCanMove(int xy[4][4]);//确定是否可以移动


	My2048()
	{
	}

	~My2048()
	{
	}

private:
	void ShowNextNum(int xy[4][4]);//生成新的数字
	int Random(int m, int n);//生成随机数字
};



void My2048::Init(int xy[4][4])
{
	StartShowNumCount = 3;
	MinNum = 2;
	UnEmptyPosNum = 0;
	int m, n;
	srand((int)time(NULL));//利用时间来生成伪随机数
	m = 0;
	n = 3;
	for (int i = 0; i<StartShowNumCount; i++) {
		//随即设置初始的方块值;
		xy[Random(m, n)][Random(m, n)] = MinNum;
	}
	FreshUI(xy);
}

bool My2048::CanMerge(int num1, int num2)
{
	if (num1 == num2 || num1 == 0 || num2 == 0) {
		//两个相等是可以相加的，如果是0的话就认定是一个空的给自
		//另一个数字可以移动过去
		return true;
	}
	return false;
}

int My2048::GetMerge(int num1, int num2)
{
	return num1 + num2;
}

void My2048::FreshUI(int xy[4][4])
{
	MapSize = 4;
	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j<MapSize; j++) {
			cout << xy[i][j] << "\t";
		}
		cout << endl;
	}
}



bool My2048::CheckCanMove(int xy[4][4])
{
	MapSize = 4;
	UnEmptyPosNum = 0;
	for (int i = 0; i<MapSize; i++) {
		for (int j = 0; j<MapSize; j++) {
			if (xy[i][j] != 0) {
				UnEmptyPosNum++;
			}
			if (xy[i][j] == 2048) {
				cout << "win" << endl;
			}
		}
	}
	if (UnEmptyPosNum == 16) {
		if (CanMoveX(xy) == false && CanMoveY(xy) == false) {
		//	cout << "你输了" << endl;
			int result = MessageBox(NULL, TEXT("U LOSE"), TEXT("2048"), MB_ICONINFORMATION | MB_YESNO);

			return false;
		}
	}
	return true;

}

int My2048::Random(int m, int n)
{
	int pos, dis;
	if (m == n) {
		return m;
	}
	else if (m > n)
	{
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	}
	else
	{
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}
}

void My2048::ShowNextNum(int xy[][4])
{
	int m, n;
	m = 0;
	n = 3;
	int i, j;
	i = Random(m, n);
	j = Random(m, n);
	if (xy[i][j] == 0) {
		xy[i][j] = Random(1, 2) * 2;
	}
	else {
		ShowNextNum(xy);
	}
}

bool My2048::CanMoveX(int xy[4][4])
{
	MapSize = 4;
	for (int j = 0; j <MapSize; j++) {
		for (int i = 0; i<MapSize; i++) {
			if (CanMerge(xy[i][j], xy[i - 1][j])) {
				return true;
			}
		}
	}
	return false;

}

bool My2048::CanMoveY(int xy[4][4])
{
	MapSize = 4;
	for (int i = 0; i<MapSize; i++) {
		for (int j = 0; j <MapSize; j++) {
			if (CanMerge(xy[i][j], xy[i][j - 1])) {
				return true;
			}
		}
	}
	return false;
}



void My2048::UpdateUI(MoveNormal nor, int xy[4][4])
{
	UnEmptyPosNum = 0;
	MapSize = 4;
	int i, j, k, n;
	switch (nor)
	{
	case Left:
		for (i = 0; i<MapSize; i++) {
			n = 0;
			for (j = 1; j<MapSize; j++) {
				if (CanMerge(xy[i][j], xy[i][j - 1])) {

					if (xy[i][j] != 0 && xy[i][j - 1] != 0) {
						n = n + 1;
					}
					xy[i][j - 1] = GetMerge(xy[i][j], xy[i][j - 1]);
					xy[i][j] = 0;
					for (k = j - 1; k>0; k--) {
						if (CanMerge(xy[i][k], xy[i][k - 1])) {
							if (n<1) {
								if (xy[i][k] != 0 && xy[i][k - 1] != 0) {
									n = n + 1;
								}
								xy[i][k - 1] = GetMerge(xy[i][k], xy[i][k - 1]);
								xy[i][k] = 0;
							}
						}
					}
				}
			}
		}
		break;
	case Right:
		for (i = 0; i<MapSize; i++) {
			n = 0;
			for (j = MapSize - 1; j>0; j--) {
				if (CanMerge(xy[i][j], xy[i][j - 1])) {

					if (xy[i][j] != 0 && xy[i][j - 1] != 0) {
						n = n + 1;
					}
					xy[i][j] = GetMerge(xy[i][j], xy[i][j - 1]);
					xy[i][j - 1] = 0;
					for (k = j; k<3; k++) {
						if (CanMerge(xy[i][k], xy[i][k + 1])) {
							if (n<1) {
								if (xy[i][k] != 0 && xy[i][k + 1] != 0) {
									n = n + 1;
								}
								xy[i][k + 1] = GetMerge(xy[i][k], xy[i][k + 1]);
								xy[i][k] = 0;
							}
						}
					}
				}
			}
		}
		break;
	case Up:
		for (j = 0; j < MapSize; j++) {//上下移动与列无关，只需检测行，遍历每一列
			n = 0;
			for (i = 1; i < MapSize; i++) {//i=1是检查2行和1行,i=2时检查3行和2行，i=3时检查4行
				if (CanMerge(xy[i][j], xy[i - 1][j])) {//如果3行可以和2行相加

					if (xy[i][j] != 0 && xy[i - 1][j] != 0) {
						n = n + 1;//如果相加的两个数都不等于0，则记一次有效相加，否则无视
					}
					xy[i - 1][j] = GetMerge(xy[i][j], xy[i - 1][j]);//把这一行的值加到上行
					xy[i][j] = 0;//并把这一行的值归零
					for (k = i - 1; k > 0; k--) {//再检查这行和上行是否可以相加，只有从第3，4行开始检查的时候会执行
						if (CanMerge(xy[k][j], xy[k - 1][j])) {//若可以相加
							if (n<1) {
								if (xy[k - 1][j] != 0 && xy[k][j] != 0) {
									n = n + 1;
								}
								xy[k - 1][j] = GetMerge(xy[k][j], xy[k - 1][j]);
								xy[k][j] = 0;
							}
						}
					}
				}
			}
		}
		break;
	case Down:
		for (j = 0; j< MapSize; j++) {
			n = 0;
			for (i = MapSize - 1; i > 0; i--) {
				if (CanMerge(xy[i][j], xy[i - 1][j])) {

					if (xy[i][j] != 0 && xy[i - 1][j] != 0) {
						n = n + 1;
					}
					xy[i][j] = GetMerge(xy[i][j], xy[i - 1][j]);
					xy[i - 1][j] = 0;
					for (k = i; k < 3; k++) {
						if (CanMerge(xy[k][j], xy[k + 1][j])) {
							if (n >= 1) {

							}
							else {
								if (xy[k][j] != 0 && xy[k + 1][j] != 0) {
									n = n + 1;
								}
								xy[k + 1][j] = GetMerge(xy[k][j], xy[k + 1][j]);
								xy[k][j] = 0;
							}
						}
					}
				}
			}
		}
		break;
	}
	ShowNextNum(xy);
	FreshUI(xy);
}
