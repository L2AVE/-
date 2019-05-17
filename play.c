#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

#define MAP_SIZE 10

#define WALL 1
#define CHAR 2
#define SHIT 3
#define EMPTY 0

typedef struct Monster
{
	int monster_x;
	int monster_y;

}Monster;

Monster _monster[9999];
int monster_num = 0;

int true = 1;
int false = 0;


int map[MAP_SIZE][MAP_SIZE] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
};

int block_j = 0; // 블럭의 랜덤한 가로 위치 변수를 선언
int cj = 0; //캐릭터의 랜덤한 가로 위치 변수를 선언
int ci = 8; // 캐릭터가 고정되어 있는 위치 변수를 선언

int _move()
{
	int key = 0;
	
	key = getch();
	if (key == 224)
	{
		key = getch();

		switch (key)
		{
		//case 72: //↑
		//	if (map[ci - 1][cj] != WALL)
		//	{
		//		map[ci][cj] = EMPTY;
		//		map[ci - 1][cj] = CHAR;
		//		ci--;
		//	}
		//	break;
		case 75: //←
			if (map[ci][cj - 1] != WALL)
			{
				map[ci][cj] = EMPTY;
				map[ci][cj - 1] = CHAR;
				cj--;
			}
			else if (map[ci][cj - 1] == SHIT)
				return 1;
			break;
		case 77: //→
			if (map[ci][cj + 1] != WALL)
			{
				map[ci][cj] = EMPTY;
				map[ci][cj + 1] = CHAR;
				cj++;
			}
			else if (map[ci][cj + 1] == SHIT)
				return 1;
			break;
		//case 80: //↓
		//	if (map[ci + 1][cj] != WALL)
		//	{
		//		map[ci][cj] = EMPTY;
		//		map[ci + 1][cj] = CHAR;
		//		ci++;
		//	}
		//	break;
		default:
			break;
		}

	}
	return false;
}


void game_over()
{
	system("cls");

	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<100; j++)
		{
			printf("  ");
			if (i > 5)
			{
				printf("＠");
			}
		}
	}
	printf("\n\n\n\n\n\n\t\t\t\t\t\t게임 종료\n\n\n\n\n");
}

void _print()
{
	system("cls");
	for (int i = 0; i < MAP_SIZE; i ++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == WALL)
				printf("■");

			else if (map[i][j] == EMPTY)
				printf("  ");

			else if (map[i][j] == CHAR)
				printf("★");

			else if (map[i][j] == SHIT)
				printf("▼");
		}
		printf("\n");
	}
	
}

void _create()
{
	int i = 1 + rand() % 8;
	map[1][i] = SHIT; //처음 인덱스에 똥 생성
	_monster[monster_num].monster_x = i;
	_monster[monster_num].monster_y = 1;
	monster_num++;
}

int _drop()
{
	for (int i = 0; i < monster_num; i++)
	{
		if (map[_monster[i].monster_y + 1][_monster[i].monster_x] != WALL // 몬스터 밑에 벽이 없고
			&& map[_monster[i].monster_y + 1][_monster[i].monster_x] != CHAR) //몬스터 밑에 캐릭터가 아니면
		{
			map[_monster[i].monster_y][_monster[i].monster_x] = EMPTY;
			map[_monster[i].monster_y + 1][_monster[i].monster_x] = SHIT;
			_monster[i].monster_y++;
		}
		else if(map[_monster[i].monster_y + 1][_monster[i].monster_x] == WALL) //벽이라면 몬스터를 소멸
		{
			map[_monster[i].monster_y][_monster[i].monster_x] = EMPTY;
			_monster[i].monster_y = EMPTY;
			_monster[i].monster_x = EMPTY;
			
			
		}
		else if (map[_monster[i].monster_y + 1][_monster[i].monster_x] == CHAR) //캐릭터라면 게임 종료
		{
			return 1;
		}
		
	}
	return 0;

	//int i = 1;
	//map[i][block_j] = SHIT; //똥을 넣고
	//map[i - 1][block_j] = EMPTY; //현재 인덱스의 똥을 제거
	//	
	//_print();
	//if (map[i + 1][block_j] == WALL) // 다음 인덱스가 벽이라면
	//{
	//	map[i][block_j] = EMPTY; //똥이 떨어질 필요가 없으니 똥을 제거
	//}
	//else if (map[i + 1][block_j] == CHAR) // 다음 인덱스가 캐릭터라면
	//{
	//	return 1; // 1을 반환
	//}
	//
	//return 0; // 충돌이 없으면 0을 반환
	
}
void init()						 // 초기화// 게임 시작할때 배열에 무언가가 들어가있을지 모르니깐 미리 초기화 해줌 (예외처리)
{
	if (monster_num > 0)
	{
		for (int i = 0; i < monster_num; i++)
		{
			memset(_monster, 0, monster_num);
		}
		monster_num = 0;
	}
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			map[i][j] = 0;
		}
	}
}

int main()
{
	start:
	init();
	int i = 0, j = 0, move = 0;
	srand((unsigned)time(NULL));
	cj = 1 + rand() % 8; // 캐릭터 위치 지정
	map[ci][cj] = 2; // 캐릭터 생성

	while (1)
	{
		i++;
		j++;
		if (j > 3)
		{
			_create();
			j = 0;
		}
		if (kbhit()) 
		{
			if (_move())
				game_over();
		}
		if (i > 1)
		{
			if (_drop()) 
			{
				game_over();
				break;
			}
			i = 0;
		}
	}
	int re_start = 0;
	printf("다시 시작? yes: 1 no: 0 >>> ");
	scanf("%d", &re_start);
	if (re_start == 0)
		return 0;
	else
		goto start;

}