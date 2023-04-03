#define _CRT_SECURE_NO_WARNINGS  //ȥ��������������
#include <iostream>
#include <graphics.h> 
#include <conio.h>
#include <stdlib.h>
using namespace std;
IMAGE img[12];
int imgIndex[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int i, j; //ѭ�������ı���
int map[4][4] = { 0 };

void loadResource() //�������غ���
{
	for (i = 0; i < 12; i++)
	{
		char fileName[20] = "";
		sprintf(fileName, "%d.bmp", imgIndex[i]);//��ӡ��fileName��
		loadimage(img + i, fileName);//����ͼƬ
	}
}
void drawMap()
{
	setbkcolor(RGB(218, 180, 134));
	cleardevice();
	settextcolor(WHITE);
	settextstyle(35, 0, "����");
	outtextxy(50, 10, "2048��Ϸ");
	int x, y, k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			x = 60 * j;
			y = 60 * i + 50;
			for (k = 0; k < 12; k++)
			{//�����ǰԪ�ض�Ӧ��ͼƬ���
				if (imgIndex[k] == map[i][j])
					break;
			}
			putimage(x, y, img + k);//����Ӧ��ŵ�ͼƬ
		}
	}
}
int randIntNum() 
{
	srand((unsigned int)time(NULL));   //�����������
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				map[i][j] = (rand() % 3)*2;
				if (map[i][j] == 0)
					continue;
				return 0;
			}
		}
	}
	return 0;

}
int moveRight() 
{
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 4 - 1; j >= 0; j--)
		{
			int curKey = map[i][j];//�ó���ǰԪ�ص�ֵ�ж���û����ͬ��
			if(curKey!=0)
			{
				int k = j - 1;
				while (k >= 0)
				{
					int curKeyNext = map[i][k];
					if (curKeyNext != 0)
					{
						if (curKey == curKeyNext)
						{
							flag = 1;//2244>0408
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = -1;
						break;
					}
					k--;//�ж�����λ��
				}
			}
		}
	}
	//0208>0028
	for (i = 0; i < 4; i++)
	{
		for (j = i-1; j >= 0; j--)
		{
			int curKey = map[i][j];
			if (curKey == 0)
			{
				int k = j - 1;
				while (k >= 0)
				{
					int curKeyNext = map[i][k];
					if (curKeyNext != 0)
					{
						flag = 1;
						map[i][j] = curKeyNext;//�ѷ�0�Ƶ�0��λ��
						map[i][k] = 0;//�ƶ����Ϊ0
						k = -1;
					}
					k--;
				}
			}
		}
		if (flag)
			return 0;
		else
			return 4;
	}
}
int moveLeft()
{
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			int curKey = map[i][j];
			if (curKey != 0)
			{
				int k = j + 1;
				while (k < 4)
				{
					int curKeyNext = map[i][k];
					if (curKeyNext != 0)
					{
						if (curKey == curKeyNext)
						{
							flag = 1;
							map[i][j] += map[i][k];
							map[i][k] = 0;
						}
						k = 4;
						break;
					}
					k++;
				}
			}
		}
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				int curKey = map[i][j];
				if (curKey == 0)
				{
					int k = j + 1;
					while (k < 4)
					{
						int curKeyNext = map[i][k];
						if (curKeyNext != 0)
						{
							flag = 1;
							map[i][j] = curKeyNext;
							map[i][k] = 0;
							k = 4;
						}
						k++;
					}
				}
			}
			if (flag)
				return 0;
			else
				return 4;
		}
	}
}
int moveUp()
{
	int flag = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j <4; j++)
		{
			int curKey = map[i][j];
			if (curKey != 0)
			{
				int k = i + 1;
				while (k < 4)
				{
					int curKeyNext = map[k][j];
					if (curKeyNext != 0)
					{
						if (curKey == curKeyNext)
						{
							flag = 1;
							map[i][j] += map[k][j];
							map[k][j] = 0;
						}
						k = 4;
						break;
					}
					k++;
				}
			}
		}
	}
	for (i = 0; i < 4-1; i++)
	{
		for (j = 0; j < 4; j++)
		{
			int curKey = map[i][j];
			if (curKey == 0)
			{
				int k = i + 1;
				while (k < 4)
				{
					int curKeyNext = map[k][j];
					if (curKeyNext != 0)
					{
						flag = 1;
						map[i][j] = curKeyNext;
						map[k][j] = 0;
						k = 4;
					}
					k++;
				}
			}
		}
		if (flag)
			return 0;
		else
			return 4;
	}
}
int moveDown()
{
	int flag = 0;
	for (i = 4 - 1; i >= 0; i--)
	{
		for (j = 0; j < 4; j++)
		{
			int curKey = map[i][j];
			if (curKey != 0)
			{
				int k = i - 1;
				while(k>=0)
				{
					int curKeyNext = map[k][j];
					if (curKeyNext != 0)
					{
						if (map[i][j] == map[k][j])
						{
							flag = 1;
							map[i][j] += map[k][j];
							map[k][j] = 0;
						}
						k = 0;
						break;
					}
					k--;
				}
			}
		}
	}
	for (i = 4 - 1; i > 0; i--)
	{
		for (j = 0; j < 4; j++)
		{
			int curKey = map[i][j];
			if (curKey == 0)
			{
				int k = i - 1;
				while (k >= 0)
				{
					int curKeyNext = map[k][j];
					if (curKeyNext != 0)
					{
						flag = 1;
						map[i][j] = curKeyNext;
						map[k][j] = 0;
						k = 0;
					}
					k--;
				}
			}
		}
	}
	if (flag)
		return 0;
	else
		return 4;
}
void keyDown()
{
	char key = _getch();
	switch (key)
	{
		case 'w':
		case 'W':
			randIntNum();
			moveUp();
			break;
		case 's':
		case 'S':
			randIntNum();
			moveDown();
			break;
		case 'a':
		case 'A':
			randIntNum();
			moveLeft();
			break;
		case 'd':
		case 'D':
			randIntNum();
			moveRight();
			break;
	
	}

}
int main() 
{
	loadResource();
	initgraph(60 * 4, 60 * 4 + 60);
	drawMap();
	while (1)
	{
		keyDown();
		drawMap();
	}
	getchar();
	closegraph();
	system("pause");
	return 0;
}