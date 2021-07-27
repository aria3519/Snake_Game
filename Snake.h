#pragma once
#include"Head.h"
class Snake
{

private:
	bool m_bLife;
	int m_iDir;
	int m_iSpeed;
	int m_iPoint;
	int m_iTime;
	list<Point>m_MyPoint;
	Point EatFood;
	bool CheckFood;

public:
	Snake();
	void DrawSnake();
	void RemoveSnake();
	void AddTail();
	void ReSet()
	{
		Point temp;
		m_iDir = READY;
		m_MyPoint.clear();
		temp.x = 40;
		temp.y = 12;
		m_MyPoint.push_back(temp);
		m_iSpeed = 300;
		m_iPoint = 0;
		m_bLife = true;
	}
	bool ListLoop(list<Point>temp, int x, int y);
	bool ListLoopNotFirst(list<Point>temp, int x, int y);
	STATE MoveSnake(list<Point>ListWall, list<Point>ListFood);
	void ChangeMove();
	STATE HeadCheck(list<Point>ListWall,list<Point>ListFood);
	int GetPoint()
	{
		return m_iPoint;
	}
	bool getlife()
	{
		return m_bLife;
	}
	bool GetCheckFood()
	{
		return CheckFood;
	}
	list<Point> GetMySnake()
	{
		return m_MyPoint;
	}
	Point EatFoodPoint()
	{
		return EatFood;
	}
	
	static inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

};

