#include "QQ_clinet.h"


CS FLAM;

void clinet_down(int argc)
{
	QQ_clinet_down(&FLAM);
	close(FLAM.sockfd);
	kill(0,SIGINT);
	exit(3);
}


int main(int argc, char const *argv[])
{

	signal(SIGINT,clinet_down);//客户端下线提醒

	QQ_clinet_up((void *)&FLAM);//客户端上线提醒

	QQ_clinet_talking((void *)&FLAM);// 客户端聊天

	return 0;
}
