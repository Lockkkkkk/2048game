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
	enum MoveNormal {//ö��4������
		Up,
		Down,
		Left,
		Right,
	};
	int UnEmptyPosNum; //��ǰ����0�ķ�����м���
	int StartShowNumCount;//һ��ʼ��ʾ�����֣�0����û�з���
	int MapSize;//��X����2048��Ϸ
	int MaxNum;//������ֵ����ֵ
	int MinNum;//������ֵ���Сֵ
	void UpdateUI(MoveNormal, int xy[4][4]); //����UI
	void FreshUI(int xy[4][4]);//ˢ��UI
	int GetMerge(int num1, int num2);//�ӷ�
	bool CanMerge(int num1, int num2);//�ж��Ƿ�ɼ�
	void Init(int xy[4][4]);//������
	bool CanMoveX(int xy[4][4]);//x�᷽���Ƿ���Խ����ƶ�
	bool CanMoveY(int xy[4][4]);//y�᷽���Ƿ���Խ����ƶ�
	bool CheckCanMove(int xy[4][4]);//ȷ���Ƿ�����ƶ�


	My2048()
	{
	}

	~My2048()
	{
	}

private:
	void ShowNextNum(int xy[4][4]);//�����µ�����
	int Random(int m, int n);//�����������
};



void My2048::Init(int xy[4][4])
{
	StartShowNumCount = 3;
	MinNum = 2;
	UnEmptyPosNum = 0;
	int m, n;
	srand((int)time(NULL));//����ʱ��������α�����
	m = 0;
	n = 3;
	for (int i = 0; i<StartShowNumCount; i++) {
		//�漴���ó�ʼ�ķ���ֵ;
		xy[Random(m, n)][Random(m, n)] = MinNum;
	}
	FreshUI(xy);
}

bool My2048::CanMerge(int num1, int num2)
{
	if (num1 == num2 || num1 == 0 || num2 == 0) {
		//��������ǿ�����ӵģ������0�Ļ����϶���һ���յĸ���
		//��һ�����ֿ����ƶ���ȥ
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
		//	cout << "������" << endl;
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
		for (j = 0; j < MapSize; j++) {//�����ƶ������޹أ�ֻ�����У�����ÿһ��
			n = 0;
			for (i = 1; i < MapSize; i++) {//i=1�Ǽ��2�к�1��,i=2ʱ���3�к�2�У�i=3ʱ���4��
				if (CanMerge(xy[i][j], xy[i - 1][j])) {//���3�п��Ժ�2�����

					if (xy[i][j] != 0 && xy[i - 1][j] != 0) {
						n = n + 1;//�����ӵ���������������0�����һ����Ч��ӣ���������
					}
					xy[i - 1][j] = GetMerge(xy[i][j], xy[i - 1][j]);//����һ�е�ֵ�ӵ�����
					xy[i][j] = 0;//������һ�е�ֵ����
					for (k = i - 1; k > 0; k--) {//�ټ�����к������Ƿ������ӣ�ֻ�дӵ�3��4�п�ʼ����ʱ���ִ��
						if (CanMerge(xy[k][j], xy[k - 1][j])) {//���������
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
