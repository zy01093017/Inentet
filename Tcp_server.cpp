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



	while (CBoard[x - 1][y - 1] != -1)
	{
		cout << "该位置已经有子了，请重新落子！" << endl;
		cin >> x;
		cin >> y;
		point.x = x;
		point.y = y;
	}

}

// ./server  ip地址  端口号
int main(int argc,char* argv[])
{
	//进程 ip地址  端口号
	if(argc != 3){
		perror("Usage ./server [ip] [port]\n");
		return 1;
	}
	//ipv4 面向字节流  创建socket
	int new_sock = socket(AF_INET, SOCK_STREAM,0);
	if(new_sock < 0){
		perror("socket");
		return 2;
	}

	struct sockaddr_in server;//绑定的是服务器的ip和端口号
	server.sin_family = AF_INET;//协议族
	server.sin_addr.s_addr = inet_addr(argv[1]);//将ip专程4字节ip地址，在转成大端字节序
	server.sin_port = htons(atoi(argv[2]));


	//绑定端口号
	int ret = bind(new_sock, (struct sockaddr*)&server,sizeof(server));
	if(ret < 0){//绑定失败
		perror("bind");
		return 3;
	}

	//设置成监听状态,socket文件描述符,第二个参数为连接客户端的最大个数
	int lis = listen(new_sock, 5);
	if(lis < 0){
		perror("listen");
		return 4;
	}

	printf("listen success...\n");

	struct sockaddr_in client;
    
    ChessBoard cb;
    int IsWin = 0;
	while(1){
		//获取与客户端的连接,这里的结构体获取的是客户端的ip和端口号，还没传过来
		socklen_t len = sizeof(client);
		int client_sock = accept(new_sock,(struct sockaddr*)&client, &len);
		if(client_sock < 0){//获取失败,接着获取
			perror("accept");
			continue;
		}

		printf("Get connet[%s]:[%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		char buf[1024];
		//获取连接，也监听到了客户端
    	while(1){//一直从客户端读取信息，在将信息发回给客户端
		
        	//从客户端读到坐标，打印棋盘，然后走自己的,判断输赢
            ssize_t rd = read(client_sock,&cb.point, sizeof(cb.point));
            if(rd < 0){
                cout<<"读取失败"<<endl;
                return 1;
            }
            else if (rd == 0){
                cout << "client quit..."<<endl;
                break;
             }
		    cb.ClientGo(0, cb.point);//查看客户端的走棋
                cb.Show();
		
		    cb.Pos(cb.point);//服务器端走棋

            cb.ServerGo(1, cb.point);//服务器端走黑棋
            IsWin = cb.CheckWin(0, cb.point);

            if(IsWin != 'g')
           	{
                if(IsWin == 'p')
                     {
                    cout << "本局为平局"<<endl;
                    break;
                     }
              cout << "恭喜" << (IsWin == 0 ? "白棋" : "黑棋") << "获胜" << endl;
                break;
            }
            cout << endl;
            cb.Show();

            //在将坐标发给客户端
            ssize_t wr = write(client_sock,&cb.point, sizeof(cb.point));
        }
    }

	close(new_sock);
	return 0;
}
