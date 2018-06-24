#include <iostream>
using namespace std;


#include <vector>
#include <stdlib.h>

#define BOARDSIZE 15


/*约定：先下的人是白棋，后下的是黑棋*/

struct Point
{
	int x;
	int y;
};


class ChessBoard
{
public:
	Point point;
	ChessBoard();
	~ChessBoard();
	void Show();//显示棋盘

	char CheckWin(int x, Point& point);                //检查五子连珠函数  
	bool IsFull();
	void ClientGo(char Color,Point& point);      //人走子函数   Color为当前人所执子的颜色  
	void ServerGo(char Color,Point& point);      //电脑走子函数 Corlor为当前人所执子的颜色
	bool ColState(Point& point); //判断列方向
	bool RowState(Point& point); //判断行方向
	bool UpLeftState(Point& point);//对角线
	bool UpRightState(Point& point);//对角线
	void Pos(Point& point);
protected:
	char CBoard[BOARDSIZE][BOARDSIZE];    //定义棋盘  
	
};
