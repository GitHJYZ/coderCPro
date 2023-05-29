#ifndef __QQ_server_H__
#define __QQ_server_H__

#include "link.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "unistd.h"
#include "pthread.h"
#include "signal.h"

typedef struct server
{
	int sockfd;
	int new_fd;
	struct sockaddr_in my_addr;
	struct sockaddr_in dst_addr;	

}SER;

extern void server_bind(void *data);

#endif