#pragma once
#include"head.h"

class Map
{
private:
	int m_ix;
	int m_iy;
	int m_iTime;
	list<Point> m_ListWall;
	list<Point> m_ListFood;

public:
	Map();
	int getx()
	{
		return m_ix;
	}
	int  gety()
	{
		return m_iy;
	}
	list<Point> getWall()
	{
		return m_ListWall;
	}
	list<Point> getFood()
	{
		return m_ListFood;
	}
	void DrawMap();
	void CreateWall();
	void DrawWall(int x,int y);
	void DrawFood(int x,int y);
	void ReSetList()
	{
		m_ListWall.clear();
		m_ListFood.clear();
	}
	void CreateFood(list<Point>Snake);
	bool ListLoop(list<Point>temp, int x,int y);
	void ListLoopRemove(Point temp);
	




	static inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

};

