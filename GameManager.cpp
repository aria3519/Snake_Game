#include"GameManager.h"

GameManager::GameManager( )
{
	while (1)
	{
		switch (Menu())
		{
		case 1: // ���� ���� 
			Play();
			break;
		case 2: // ���� ���� 
			MapManager.DrawMap();
			DrawMidStr(m_Mapx-5, m_Mapy * 0.5f, "�١� ������ ����˴ϴ�.�١� ");
			gotoxy(m_Mapx-20, m_Mapy * 0.55f);
			system("pause");
			return;
		}
	}
}

int  GameManager::Menu()
{
	int temp;
	m_Mapx = MapManager.getx();
	m_Mapy = MapManager.gety();
	CMDSizeChange(2.2 * m_Mapx, m_Mapy + 3);
	MapManager.DrawMap();
	DrawMidStr(m_Mapx,m_Mapy*0.3f,"�١� Snake Game�١� ");
	DrawMidStr(m_Mapx,m_Mapy*0.4f,"1. ���� ����       ");
	DrawMidStr(m_Mapx,m_Mapy*0.5f,"2. ���� ����       ");
	DrawMidStr(m_Mapx,m_Mapy*0.6f," ����:      ");
	gotoxy(m_Mapx+1, m_Mapy * 0.6f);
	cin >> temp;
	return temp;

}

void GameManager::DrawMidStr(int x, int y ,string str)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
}

void GameManager::DrawMidint(int x, int y, int temp)
{
	gotoxy(x, y);
	cout << temp;
}

void GameManager::CMDSizeChange(int x,int y)
{
	char strtemp[26];
	sprintf(strtemp, "mode con:cols=%d lines=%d", x, y);
	system(strtemp);
}

void GameManager::Play()
{
	bool flag = true;
	STATE SnakeState = STATE_KEEP;
	MapManager.DrawMap();
	MapManager.CreateWall();//�������� 20�� ������ ���� ����
	SnakeManager.DrawSnake();
	DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
	DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
	while (flag)
	{
		
		// 5�ʿ� �ѹ��� ���� ���� 
		MapManager.CreateFood(SnakeManager.GetMySnake());
		// 0.3�� �������� ���� ������ + ����Ʈ�� �ö󰥼��� ���� ������
		SnakeState =SnakeManager.MoveSnake(MapManager.getWall(), MapManager.getFood());
		switch (SnakeState)
		{
		case STATE_DEATH: // ���� ��� 
			flag = false;
			break;
		case STATE_KEEP: // ���� 
			break;
		case STATE_EATFOOD: // ���̸� ���� ��� 
			MapManager.ListLoopRemove(SnakeManager.EatFoodPoint());
			DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
			DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
			break;
		}
		if (flag)
		{
			if (kbhit())
				SnakeManager.ChangeMove();
			// ���� �ö󰥶��� �׷��ְ� 
		}
	}
	ReSet();
	char ch = getch();
	while (ch != 32)
		return;
}

void GameManager::ReSet()
{
	MapManager.DrawMap();
	DrawMidStr(m_Mapx, m_Mapy * 0.3f, "�١� Game Over �١� ");
	DrawMidStr(m_Mapx, m_Mapy * 0.5f, "Continue : Space Bar");
	DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
	DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
	MapManager.ReSetList();
	SnakeManager.ReSet();
}

