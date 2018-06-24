#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


#include "Board.h"


void ChessBoard::Pos(Point& point)
{
	int x, y;
	
	
	cout << "请输入坐标：[横坐标在前，纵坐标在后]" << endl;
	cin >> x;
	cin >> y;

	point.x = x;
	point.y = y;

	if (IsFull())
	{
		cout << "棋盘已满" << endl;
		return;
	}

	while ((x < 1 || x > BOARDSIZE) || (y < 1 || y > BOARDSIZE))
	{
		cout << "位置格式有误,请重新输入：" << endl;
		cin >> x;
		cin >> y;
		point.x = x;
		point.y = y;

	}

	

	while(CBoard[x-1][y-1] != -1)
	{
		cout << "该位置已经有子了，请重新落子！" << endl;
		cin >> x;
		cin >> y;
		point.x = x;
		point.y = y;
	}
} 

void play(int sockfd)
{
	ChessBoard cb;//对象
	int IsWin = 0;//判断输赢
   
  
		while (1)
		{
			
			cb.Pos(cb.point);
			cb.ClientGo(0, cb.point); //走子,先手拿白棋,0代表白棋
			ssize_t wr = write(sockfd,(void*)&cb.point,sizeof(cb.point));
            if(wr < 0){
                cout<<"写入失败"<<endl;
                return;
            }
			IsWin = cb.CheckWin(0,cb.point);//每走完一步判断输赢,将坐标传过去
			
			if (IsWin != 'g')
			{
				if (IsWin == 'p')
				{
					cout << "本局为平局" << endl;
					break;
				}
				cout << "恭喜" << (IsWin == 0 ? "白棋" : "黑棋") << "获胜" << endl;
				break;
			}
			cout << endl;
			cb.Show();
		 
       		read(sockfd, &cb.point, sizeof(cb.point));
			cb.ServerGo(1, cb.point);
       	  	cb.Show();

		}
	
}

void Start(int sockfd)
{

	int start = 0;
	while (1)
	{
		
		cout << "请选择是否开始游戏：【1-->开始】 【0-->退出】" << endl;
		cin >> start;
		ChessBoard cb;//对象
	
		if (start == 1)
		{
			cb.Show();
			play(sockfd);
		}
		else
		{
			break;
		}

	}
	cout << "开始退出" << endl;

}

// ./client  ip地址  端口号
int main(int argc,char* argv[])
{
	//进程 ip地址  端口号
	if(argc != 3){
		perror("Usage ./server [ip] [port]\n");
		return 1;
	}
	//ipv4 面向字节流  创建socket
	int sock = socket(AF_INET, SOCK_STREAM,0);
	if(sock < 0){
		perror("socket");
		return 2;
	}

 	struct sockaddr_in server;//绑定的是服务器的ip和端口号
	server.sin_family = AF_INET;//协议族
	server.sin_addr.s_addr = inet_addr(argv[1]);//将ip专程4字节ip地址，在转成大端字节序
	server.sin_port = htons(atoi(argv[2]));

	//连接服务器
	int ret = connect(sock,(struct sockaddr*)&server,sizeof(server));
	if(ret < 0){//连接失败
		perror("connect");
		return 3;
	}

	//表示连接成功
	printf("Connect success...\n");

	while(1){//连接成功

        Start(sock);//开始游戏,并将套接字传过去
	}

	close(sock);
	return 0;
}
