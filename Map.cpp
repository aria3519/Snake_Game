#include "Map.h"


Map::Map()
{
	m_ix = 45;
	m_iy = 25;
	m_iTime = clock();
}

void Map::DrawMap()
{
	system("cls");
	for (int y = 0; y < m_iy; y++)
	{
		gotoxy(STOP, STOP + y);
		if (y == 0)
		{
			for(int x=0;x<m_ix;x++)
				cout << "¢Ë";
		}
		else if (y == m_iy - 1)
		{
			for (int x = 0; x <m_ix; x++)
				cout << "¢Ë";
		}
		else
		{
			cout << "¢Ë";
			for (int x = 1; x < m_ix - 1; x++)
				cout << "  ";
			cout << "¢Ë";
		}
	}
}

void Map::CreateWall()
{
	//randTemp = rand() % (b + 1 - a) + a; a~b ±îÁö 

	Point ptemp;
	bool flag = true;
	while (flag)
	{
		while (1)
		{
			ptemp.x = rand() % (2 * (m_ix - 2))  + 2;
			if (ptemp.x % 2 == 0)
				break;
		}
		ptemp.y = rand() % (m_iy - 2) + 1;
		if (!ListLoop(m_ListWall, ptemp.x, ptemp.y))
		{
			if (m_ListWall.size() < MAXWALL)
				m_ListWall.push_back(ptemp);
			else
				break;
		}
	}
	for (list<Point>::iterator iter = m_ListWall.begin(); iter != m_ListWall.end(); iter++)
		DrawWall(iter->x, iter->y);
}

void Map::CreateFood(list<Point>Snake)
{
	Point temp;
	bool flag = true;
	if (clock() -  m_iTime>= FOODTIME)
	{
		if (m_ListFood.size() < MAXFOOD)
		{
			while (flag)
			{
				while (1)
				{
					temp.x = rand() % (2 * (m_ix - 2)) + 2; // 86~2
					if (temp.x % 2 == 0)
						break;
				}
				temp.y = rand() % (m_iy - 1)  + 1; // 24~1
				flag = ListLoop(m_ListWall, temp.x, temp.y); // f
				if (!flag)
					flag = ListLoop(Snake, temp.x, temp.y);
				if (!m_ListFood.empty() && !flag)
					flag = ListLoop(m_ListFood, temp.x, temp.y);
			}
			DrawFood(temp.x, temp.y);
			m_ListFood.push_back(temp);
			m_iTime = clock();
		}
		else
			m_iTime = clock();

	}
}
void Map::DrawWall(int x,int y)
{
	gotoxy(x, y);
	cout << "¢Ã";
}
void Map::DrawFood(int x, int y)
{
	gotoxy(x, y);
	cout << "¢½";
}

bool Map::ListLoop(list<Point> temp,int x, int y)
{
	for (list<Point>::iterator iter =temp.begin()
		; iter != temp.end(); iter++)
	{
		if (iter->x == x && iter->y == y)
			return true;
	}
	return false;
}

void Map::ListLoopRemove(Point ptemp)
{
	list<Point>::iterator iter = m_ListFood.begin();
	for (list<Point>::iterator iter = m_ListFood.begin(); iter != m_ListFood.end(); iter++)
	{
		if (iter->x == ptemp.x && iter->y == ptemp.y)
		{
			m_ListFood.erase(iter);
			if (!m_ListFood.empty())
				iter = m_ListFood.begin();
			else
				return;
		}
	}
	
}

