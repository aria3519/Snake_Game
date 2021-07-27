#include"Map.h"
#include"Snake.h"

// 메뉴 관리 , 
class GameManager
{

private:
	Map MapManager;
	Snake SnakeManager;
	int m_Mapx;
	int m_Mapy;

public:
	GameManager();
	int Menu();
	void DrawMidStr(int x, int y ,string str);
	void DrawMidint(int x, int y ,int temp);
	void CMDSizeChange(int x,int y);
	void Play();
	void ReSet();
	


	static inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
};