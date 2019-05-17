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

int block_j = 0; // ���� ������ ���� ��ġ ������ ����
int cj = 0; //ĳ������ ������ ���� ��ġ ������ ����
int ci = 8; // ĳ���Ͱ� �����Ǿ� �ִ� ��ġ ������ ����

int _move()
{
	int key = 0;
	
	key = getch();
	if (key == 224)
	{
		key = getch();

		switch (key)
		{
		//case 72: //��
		//	if (map[ci - 1][cj] != WALL)
		//	{
		//		map[ci][cj] = EMPTY;
		//		map[ci - 1][cj] = CHAR;
		//		ci--;
		//	}
		//	break;
		case 75: //��
			if (map[ci][cj - 1] != WALL)
			{
				map[ci][cj] = EMPTY;
				map[ci][cj - 1] = CHAR;
				cj--;
			}
			else if (map[ci][cj - 1] == SHIT)
				return 1;
			break;
		case 77: //��
			if (map[ci][cj + 1] != WALL)
			{
				map[ci][cj] = EMPTY;
				map[ci][cj + 1] = CHAR;
				cj++;
			}
			else if (map[ci][cj + 1] == SHIT)
				return 1;
			break;
		//case 80: //��
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
				printf("��");
			}
		}
	}
	printf("\n\n\n\n\n\n\t\t\t\t\t\t���� ����\n\n\n\n\n");
}

void _print()
{
	system("cls");
	for (int i = 0; i < MAP_SIZE; i ++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == WALL)
				printf("��");

			else if (map[i][j] == EMPTY)
				printf("  ");

			else if (map[i][j] == CHAR)
				printf("��");

			else if (map[i][j] == SHIT)
				printf("��");
		}
		printf("\n");
	}
	
}

void _create()
{
	int i = 1 + rand() % 8;
	map[1][i] = SHIT; //ó�� �ε����� �� ����
	_monster[monster_num].monster_x = i;
	_monster[monster_num].monster_y = 1;
	monster_num++;
}

int _drop()
{
	for (int i = 0; i < monster_num; i++)
	{
		if (map[_monster[i].monster_y + 1][_monster[i].monster_x] != WALL // ���� �ؿ� ���� ����
			&& map[_monster[i].monster_y + 1][_monster[i].monster_x] != CHAR) //���� �ؿ� ĳ���Ͱ� �ƴϸ�
		{
			map[_monster[i].monster_y][_monster[i].monster_x] = EMPTY;
			map[_monster[i].monster_y + 1][_monster[i].monster_x] = SHIT;
			_monster[i].monster_y++;
		}
		else if(map[_monster[i].monster_y + 1][_monster[i].monster_x] == WALL) //���̶�� ���͸� �Ҹ�
		{
			map[_monster[i].monster_y][_monster[i].monster_x] = EMPTY;
			_monster[i].monster_y = EMPTY;
			_monster[i].monster_x = EMPTY;
			
			
		}
		else if (map[_monster[i].monster_y + 1][_monster[i].monster_x] == CHAR) //ĳ���Ͷ�� ���� ����
		{
			return 1;
		}
		
	}
	return 0;

	//int i = 1;
	//map[i][block_j] = SHIT; //���� �ְ�
	//map[i - 1][block_j] = EMPTY; //���� �ε����� ���� ����
	//	
	//_print();
	//if (map[i + 1][block_j] == WALL) // ���� �ε����� ���̶��
	//{
	//	map[i][block_j] = EMPTY; //���� ������ �ʿ䰡 ������ ���� ����
	//}
	//else if (map[i + 1][block_j] == CHAR) // ���� �ε����� ĳ���Ͷ��
	//{
	//	return 1; // 1�� ��ȯ
	//}
	//
	//return 0; // �浹�� ������ 0�� ��ȯ
	
}
void init()						 // �ʱ�ȭ// ���� �����Ҷ� �迭�� ���𰡰� �������� �𸣴ϱ� �̸� �ʱ�ȭ ���� (����ó��)
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
	cj = 1 + rand() % 8; // ĳ���� ��ġ ����
	map[ci][cj] = 2; // ĳ���� ����

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
	printf("�ٽ� ����? yes: 1 no: 0 >>> ");
	scanf("%d", &re_start);
	if (re_start == 0)
		return 0;
	else
		goto start;

}