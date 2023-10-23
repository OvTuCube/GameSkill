#include<iostream>
#include<time.h>

using namespace std;

#define MapSize 64 //ũ��
#define CountTileGoal 4 //�̰� �ø��� ���밡 �����鼭 ���� ���� �پ����
#define NoiseVelo 55 //0 ���� 100 ���� �� Ŭ���� �� ���� �ö�

int Map[MapSize][MapSize] = {};
int TempMap[MapSize][MapSize] = {};

void Noise()
{
	srand(time(NULL));

	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < MapSize; j++)
		{
			int TileIndex = rand() % 100;
			if (TileIndex > NoiseVelo)
				TileIndex = 1;
			else
				TileIndex = 0;

			Map[i][j] = TileIndex;
		}
	}
}

void PrintMap()
{
	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < MapSize; j++)
		{
			if (Map[i][j] == 1)
				cout << "��";
			else
				cout << "��";
		}
		cout << endl;
	}
}

int CheckTile(int i, int j)
{
	int countTile = 0;
	//======================================
	//������
	if ((i == 0 || j == 0) == false)
		countTile += Map[i - 1][j - 1];
	//��
	if ((i == 0) == false)
		countTile += Map[i - 1][j];
	//������
	if ((i == 0 || j == MapSize - 1) == false)
		countTile += Map[i - 1][j + 1];
	//======================================
	//����
	if (j != 0)
		countTile += Map[i][j - 1];
	//����
	if (j != MapSize - 1)
		countTile += Map[i][j + 1];
	//======================================
	//�����Ʒ�
	if ((i == MapSize - 1 || j == 0) == false)
		countTile += Map[i + 1][j - 1];
	//�Ʒ�
	if ((i == MapSize - 1) == false)
		countTile += Map[i + 1][j];
	//�����Ʒ�
	if ((i == MapSize - 1 || j == MapSize - 1) == false)
		countTile += Map[i + 1][j + 1];

	//��� �ӽ�����
	if (CountTileGoal <= countTile)
		return 1;
	else
		return 0;
	return 0;
}

void Transition()
{
	//���� 
	//->�ֺ�Ÿ�Ͽ� ���� 4�̻��̸� �� �ƴϸ� ��

	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < MapSize; j++)
		{
			TempMap[i][j] = CheckTile(i, j);
		}
	}

	//Map ����
	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < MapSize; j++)
		{
			Map[i][j] = TempMap[i][j];
		}
	}
}

int main()
{
	Noise();

	int chooseIndex = 0;
	while (true)
	{
		system("cls");

		PrintMap();

		cin >> chooseIndex;
		if (chooseIndex == 0)
			break;
		else if(chooseIndex == 1)
			Noise();
		else
			Transition();
	}

	system("pause");
	return 0;
}