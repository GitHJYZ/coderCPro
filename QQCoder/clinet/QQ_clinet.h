#ifndef __QQ_CLINET_H__
#define __QQ_CLINET_H__

#include "signal.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "string.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include <pthread.h>

typedef void (*sighandler_t)(int);

typedef struct clinet_s
{
	int sockfd;
	unsigned long int num;
	struct sockaddr_in dst_addr;
}CS;

extern void QQ_clinet_up(void *data);
extern void QQ_clinet_talking(void *data);
extern void QQ_clinet_down(void *data);
extern void send_file(int sock_fd, char *dst_ip);
extern void file_sock(int sockf_d, char *dst_ip);

#endif