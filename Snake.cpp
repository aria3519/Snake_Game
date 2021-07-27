#include "Snake.h"


Snake::Snake()
{
	Point temp;
	temp.x = 40;
	temp.y = 12;
	m_MyPoint.push_back(temp);
	m_iSpeed = 300;
	m_iPoint = 0;
	m_bLife = true;
	m_iDir = READY;
	m_iTime = clock();
	CheckFood = false;
	
}

void Snake::DrawSnake()
{
	if(m_iDir != STOP)
	{ 
		for (list<Point>::iterator iter = m_MyPoint.begin(); iter != m_MyPoint.end(); iter++)
		{
			if (iter == m_MyPoint.begin())
			{
				gotoxy(iter->x, iter->y);
				cout << "◎";
			}
			else
			{
				gotoxy(iter->x, iter->y);
				cout << "○";
			}
		}
	}
}
void Snake::RemoveSnake()
{
	gotoxy(m_MyPoint.back().x, m_MyPoint.back().y);
	cout << "  ";
}

STATE  Snake::MoveSnake(list<Point>ListWall , list<Point>ListFood)
{
	if (clock() - m_iTime >= m_iSpeed)
	{
		Point beforetemp;
		Point temp;
		STATE state = STATE_KEEP;
		beforetemp.x = m_MyPoint.begin()->x;
		beforetemp.y = m_MyPoint.begin()->y;
		CheckFood = false;
		state=HeadCheck(ListWall,ListFood);
		for (list<Point>::iterator iter = m_MyPoint.begin()
			; iter != m_MyPoint.end(); iter++)
		{
			
			if (iter == m_MyPoint.begin())
				continue;
			else // 첫번째 이외는 이전 좌표 따라가게 
			{
				
				temp.x = iter->x;
				temp.y = iter->y;
				iter->x = beforetemp.x;
				iter->y = beforetemp.y;
				beforetemp.x = temp.x;
				beforetemp.y = temp.y;
			}

		}
		DrawSnake();
		m_iTime = clock();
		return state;
	}
	return STATE_KEEP;
}

void Snake::ChangeMove()
{
	char ch;
	ch = getch();
	if (ch == -32)
	{
		ch = getch();
		switch (ch)
		{
		case LEFT:
			if (ListLoopNotFirst(m_MyPoint, m_MyPoint.begin()->x - 2,
				m_MyPoint.begin()->y))
				break;
			else
				m_iDir = LEFT;
			break;
		case RIGHT:
			if (ListLoopNotFirst(m_MyPoint, m_MyPoint.begin()->x + 2,
				m_MyPoint.begin()->y))
				break;
			else
				m_iDir = RIGHT;
			break;
		case UP:
			if (ListLoopNotFirst(m_MyPoint, m_MyPoint.begin()->x,
				m_MyPoint.begin()->y - 1))
				break;
			else
				m_iDir = UP;
			break;
		case DOWN:
			if (ListLoopNotFirst(m_MyPoint, m_MyPoint.begin()->x,
				m_MyPoint.begin()->y + 1))
				break;
			else
				m_iDir = DOWN;
			break;
		}
	}
}

bool Snake::ListLoop(list<Point> temp, int x, int y)
{
	for (list<Point>::iterator iter = temp.begin()
		; iter != temp.end(); iter++)
	{
		if (iter->x == x && iter->y == y)
			return true;
	}
	return false;
}
bool Snake::ListLoopNotFirst(list<Point> temp, int x, int y)
{
	for (list<Point>::iterator iter = temp.begin()
		; iter != temp.end(); iter++)
	{
		if (iter == temp.begin())
			continue;
		if (iter->x == x && iter->y == y)
			return true;
	}
	return false;
}

void Snake::AddTail()
{
	Point temp;
	temp.x = m_MyPoint.back().x+2;
	temp.y = m_MyPoint.back().y;
	m_MyPoint.push_back(temp);
	m_iPoint +=10;
}


STATE Snake::HeadCheck(list<Point>ListWall,list<Point>ListFood)
{
		switch (m_iDir)
		{
		case READY:
			m_iDir = STOP;
			break;
		case STOP:
			break;
		case LEFT:
			RemoveSnake();
			m_MyPoint.begin()->x = m_MyPoint.begin()->x - 2;
			if (m_MyPoint.begin()->x == NULL)
				return STATE_DEATH;
			break;
		case RIGHT:
			RemoveSnake();
			m_MyPoint.begin()->x = m_MyPoint.begin()->x + 2;
			if (m_MyPoint.begin()->x == MAX_X)
				return STATE_DEATH;
			break;
		case UP:
			RemoveSnake();
			m_MyPoint.begin()->y = m_MyPoint.begin()->y - 1;
			if (m_MyPoint.begin()->y == NULL)
				return STATE_DEATH;
			break;
		case DOWN:
			RemoveSnake();
			m_MyPoint.begin()->y = m_MyPoint.begin()->y + 1;
			if (m_MyPoint.begin()->y == MAX_Y)
				return STATE_DEATH;
			break;
		}
		if (ListLoop(ListWall, m_MyPoint.begin()->x, m_MyPoint.begin()->y))
			return STATE_DEATH;
		else // 벽에 부딪히지 않은 경우 
		{
			if(ListLoopNotFirst(m_MyPoint, m_MyPoint.begin()->x, m_MyPoint.begin()->y)) // 꼬리에 부딪힌 경우 
				return STATE_DEATH;
			if (ListLoop(ListFood, m_MyPoint.begin()->x, m_MyPoint.begin()->y)) // 먹이를 먹은 경우 
			{
				
				EatFood.x = m_MyPoint.begin()->x;
				EatFood.y = m_MyPoint.begin()->y;
				AddTail();
				if (m_iPoint%20==0)
					m_iSpeed -= 10;
				CheckFood = true;
				return STATE_EATFOOD;
			}
		} 
		return STATE_KEEP;
}