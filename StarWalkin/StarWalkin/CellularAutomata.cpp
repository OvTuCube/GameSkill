#include<iostream>
#include<time.h>

using namespace std;

#define MapSize 64 //크기
#define CountTileGoal 4 //이거 늘리면 세대가 지나면서 땅이 점점 줄어들음
#define NoiseVelo 55 //0 에서 100 사이 값 클수록 벽 비율 올라감

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
				cout << "■";
			else
				cout << "□";
		}
		cout << endl;
	}
}

int CheckTile(int i, int j)
{
	int countTile = 0;
	//======================================
	//좌측위
	if ((i == 0 || j == 0) == false)
		countTile += Map[i - 1][j - 1];
	//위
	if ((i == 0) == false)
		countTile += Map[i - 1][j];
	//우측위
	if ((i == 0 || j == MapSize - 1) == false)
		countTile += Map[i - 1][j + 1];
	//======================================
	//좌측
	if (j != 0)
		countTile += Map[i][j - 1];
	//우측
	if (j != MapSize - 1)
		countTile += Map[i][j + 1];
	//======================================
	//좌측아래
	if ((i == MapSize - 1 || j == 0) == false)
		countTile += Map[i + 1][j - 1];
	//아래
	if ((i == MapSize - 1) == false)
		countTile += Map[i + 1][j];
	//우측아래
	if ((i == MapSize - 1 || j == MapSize - 1) == false)
		countTile += Map[i + 1][j + 1];

	//결과 임시저장
	if (CountTileGoal <= countTile)
		return 1;
	else
		return 0;
	return 0;
}

void Transition()
{
	//조건 
	//->주변타일에 벽이 4이상이면 벽 아니면 땅

	for (int i = 0; i < MapSize; i++)
	{
		for (int j = 0; j < MapSize; j++)
		{
			TempMap[i][j] = CheckTile(i, j);
		}
	}

	//Map 적용
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