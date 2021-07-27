#include"GameManager.h"

GameManager::GameManager( )
{
	while (1)
	{
		switch (Menu())
		{
		case 1: // 게임 시작 
			Play();
			break;
		case 2: // 게임 종료 
			MapManager.DrawMap();
			DrawMidStr(m_Mapx-5, m_Mapy * 0.5f, "☆★ 게임이 종료됩니다.☆★ ");
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
	DrawMidStr(m_Mapx,m_Mapy*0.3f,"☆★ Snake Game☆★ ");
	DrawMidStr(m_Mapx,m_Mapy*0.4f,"1. 게임 시작       ");
	DrawMidStr(m_Mapx,m_Mapy*0.5f,"2. 게임 종료       ");
	DrawMidStr(m_Mapx,m_Mapy*0.6f," 선택:      ");
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
	MapManager.CreateWall();//랜덤으로 20개 정도의 벽을 생성
	SnakeManager.DrawSnake();
	DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
	DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
	while (flag)
	{
		
		// 5초에 한번씩 먹이 생성 
		MapManager.CreateFood(SnakeManager.GetMySnake());
		// 0.3초 간격으로 뱀을 움직임 + 포인트가 올라갈수록 점점 빨리짐
		SnakeState =SnakeManager.MoveSnake(MapManager.getWall(), MapManager.getFood());
		switch (SnakeState)
		{
		case STATE_DEATH: // 죽은 경우 
			flag = false;
			break;
		case STATE_KEEP: // 평상시 
			break;
		case STATE_EATFOOD: // 먹이를 먹은 경우 
			MapManager.ListLoopRemove(SnakeManager.EatFoodPoint());
			DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
			DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
			break;
		}
		if (flag)
		{
			if (kbhit())
				SnakeManager.ChangeMove();
			// 점수 올라갈때만 그려주게 
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
	DrawMidStr(m_Mapx, m_Mapy * 0.3f, "☆★ Game Over ☆★ ");
	DrawMidStr(m_Mapx, m_Mapy * 0.5f, "Continue : Space Bar");
	DrawMidStr(m_Mapx, m_Mapy * 1.1f, "Point: ");
	DrawMidint(m_Mapx + 5, m_Mapy * 1.1f, SnakeManager.GetPoint());
	MapManager.ReSetList();
	SnakeManager.ReSet();
}

