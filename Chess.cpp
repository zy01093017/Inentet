#include"Board.h"


//初始化，全部初始化为-1
ChessBoard::ChessBoard()
{
	for (int i = 0; i < BOARDSIZE; ++i)
	{
		for (int j = 0; j < BOARDSIZE; ++j)
		{
			CBoard[i][j] = -1;
		}
	}
}


ChessBoard::~ChessBoard()
{
	
}


void ChessBoard::Show()//显示棋盘
{
	cout << "   ";
	for (int i = 0; i < BOARDSIZE; i++)
	{
		
		cout << " " << i+1;
	}
	cout << endl;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		
		cout << i+1 << "  ";
		if (i < 9)
		{
			cout << " ";
		}
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (CBoard[i][j] == -1)
			{
				cout << "＋";
			}
			else if (CBoard[i][j] == 1)//定义color为1，表示黑棋
			{
				cout << "○ ";
			}
			else
			{
				cout << "● ";//0表示白棋
			}
		}
		cout << endl;
	}
}


bool ChessBoard::IsFull()
{
	int row = 0;
	int col = 0;
	for (row = 0; row < BOARDSIZE; row++)
	{
		for (col = 0; col < BOARDSIZE; col++)
		{
			if (CBoard[row][col] == -1)
				return false;
		}
	}
	return true;
}


//检查竖直方向
bool ChessBoard::ColState(Point& point)
{
	int x = point.x -1;
	int y = point.y -1;
	int count = 1;

	while (x - 1 >= 0)
	{

		if (CBoard[x][y] != CBoard[x - 1][y] || ((CBoard[x][y] == CBoard[x - 1][y]) && CBoard[x - 1][y] == '-1'))
			 break;

		count++;
		if (count == 5)
		{
		   //如果往上遍历已经够了五个，说明已经赢了，直接返回
			return true;
		}
		x--;
	}


	//到这里说明当前点往上走是不满足条件的
	//但是已经走到了最上面的点，所以从临界点往相反方向找
	//必须要找到五个连续的才算满足条件   
	count = 1;//count 重新被设定为1
	while (x + 1 <= BOARDSIZE)
	{
		if (CBoard[x][y] == CBoard[x + 1][y] || ((CBoard[x][y] == CBoard[x +1][y]) && CBoard[x + 1][y] == '-1'))
		{
			count++;
			if (count == 5)
			{
				return true;
			}
			x++;
		}
		else
		{
			//n 代表当前状态未满足赢的条件
			return false;
		}
	}
	return false;
}
bool ChessBoard::RowState(Point& point)
{
	int x = point.x -1;
	int y = point.y -1;
	int count = 1;
	while (y - 1 >= 0)
	{
		if (CBoard[x][y] != CBoard[x][y - 1] || ((CBoard[x][y] == CBoard[x][y-1]) && CBoard[x][y] == '-1'))
			break;
		count++;
		if (count == 5)
		{
			//如果往左遍历已经够了五个，说明已经赢了，直接返回
			return true;
		}
		y--;
	}
	//到这里说明当前点往左走是不满足条件的
	//但是已经走到了最左面的点，所以从临界点往相反方向找
	//必须要找到五个连续的才算满足条件
	count = 1;//count 重新被设定为1
	while (y + 1 <= BOARDSIZE)
	{
		if (CBoard[x][y] == CBoard[x][y + 1] || ((CBoard[x][y] == CBoard[x][y+1]) && CBoard[x][y + 1] == '-1'))
		{
			count++;
			if (count == 5)
			{
				return true;
			}
			y++;
		}
		else
		{
			//n 代表当前状态未满足赢的条件
			return false;
		}
	}
	return false;
}


//左上到右下的对角线
bool ChessBoard::UpLeftState(Point& point)
{
	int x = point.x - 1;
	int y = point.y - 1;
	int count = 1;
	while (x - 1 >= 0 && y - 1 >= 0)
	{
		if (CBoard[x][y] != CBoard[x - 1][y - 1] || ((CBoard[x][y] == CBoard[x - 1][y - 1]) && CBoard[x - 1][y - 1] == '-1'))
			break;
		count++;
		if (count == 5)
		{
			//如果往左上遍历已经够了五个，说明已经赢了，直接返回
			return true;
		}
		x--;
		y--;
	}
	//到这里说明当前点往左上走是不满足条件的
	//但是已经走到了最左上的点，所以从临界点往相反方向找
	//必须要找到五个连续的才算满足条件
	count = 1;//count 重新被设定为1
	while (x + 1 <= BOARDSIZE && y + 1 <= BOARDSIZE)
	{
		if (CBoard[x][y] == CBoard[x + 1][y + 1] || ((CBoard[x][y] == CBoard[x + 1][y + 1]) && CBoard[x + 1][y + 1] == '-1'))
		{
			count++;
			if (count == 5)
			{
				return true;
			}
			x++;
			y++;
		}
		else
		{
			//n 代表当前状态未满足赢的条件
			return false;
		}
	}
	return false;
}

//右上到左下的对角线
bool ChessBoard::UpRightState(Point& point)
{
	int x = point.x -1;
	int y = point.y -1;
	int count = 1;
	while (x - 1 >= 0 && y + 1 <= BOARDSIZE)
	{
		if (CBoard[x][y] != CBoard[x - 1][y + 1] || ((CBoard[x][y] == CBoard[x - 1][y +1]) && CBoard[x - 1][y +1] == '-1'))
			break;
		count++;
		if (count == 5)
		{
			//如果往右上遍历已经够了五个，说明已经赢了，直接返回
			return true;
		}
		x--;
		y++;
	}
	//到这里说明当前点往右上走是不满足条件的
	//但是已经走到了最右上面的点，所以从临界点往相反方向找
	//必须要找到五个连续的才算满足条件
	count = 1;//count 重新被设定为1
	while (x + 1 <= BOARDSIZE && y - 1 <= BOARDSIZE)
	{
		if (CBoard[x][y] == CBoard[x + 1][y - 1] || ((CBoard[x][y] == CBoard[x + 1][y - 1]) && CBoard[x + 1][y - 1] == '-1'))
		{
			count++;
			if (count == 5)
			{
				return true;
			}
			x++;
			y--;
		}
		else
		{
			//n 代表当前状态未满足赢的条件
			return false;
		}
	}
	return false;
}

char ChessBoard::CheckWin(int x, Point& point )                //检查五子连珠函数  
{
	
	   //判断当前点所在列是否是连续五个子儿
		if (ColState(point) == true)
		{
			return	CBoard[point.x][point.y];
		}
	   //判断当前点所在行是否是连续五个子儿
		else if (RowState(point) == true)
		{
			return	CBoard[point.x][point.y];
		}
	   //判断当前点所在左上与右下的对角线是否满足条件
	  else if (UpLeftState(point) == true)
	  {
		  return	CBoard[point.x][point.y];
	  }
	   //判断当前点所在左上与右下的对角线是否满足条件
	  else if (UpRightState(point) == true)
	  {
		  return	CBoard[point.x][point.y];
	  }
	 else if (IsFull()) //平局
	 {
		 return 'p';
	 }
		       
	 //当前没有输赢，继续游戏
     return 'g';
}

void ChessBoard::ClientGo(char Color,Point& point)      //人走子函数   Color为当前人所执子的颜色  
{
	CBoard[point.x-1][point.y-1] = Color;
}
void ChessBoard::ServerGo(char Color,Point& point)      //电脑走子函数 Corlor为当前人所执子的颜色
{
	
	CBoard[point.x - 1][point.y - 1] = Color;
	
}


