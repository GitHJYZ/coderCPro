#include "QQ_server.h"

LIST *head = NULL;

int sock_f_d = 0;

void clinet_down(int argc)
{
	close_serve(head);
	close(sock_f_d);
	exit(3);
}

void *server_fun(void *arg)
{
	LIST *tp = (LIST *)arg;
	unsigned long int t_in;
	char buf[1024]="";
	char buff[1024]="";	
	int num=0;

	
	while(1){
		
		char *result[5]={NULL};
		num = 0;

		bzero(buf, sizeof(buf));

		LIST *pb = head;
		if(NULL == head) break;
		while(NULL != pb->next)
		{
			pb = pb->next;
		}

		tp->new_fd = pb->new_fd;
		int ret = recv(tp->new_fd,buf,sizeof(buf),0);
		printf("recv tp->num ==%lu\n",tp->num);
        
		if (0 == ret)
		{
			break;
		}
		printf("buf = %s\n", buf);

		result[num]=strtok(buf,":");

		while(!(result[num]==NULL))
		{
			num++;
			result[num]=strtok(NULL,":");
		}

		printf("result[3] = %s\n", result[3]);
		printf("result[2] = %s\n", result[2]);
		printf("result[1] = %s\n", result[1]);
		printf("result[0] = %s\n", result[0]);
		printf("====================================\n");
		
		if (result[3] != NULL){
			bzero(&t_in, sizeof(t_in));
			bzero(buff,sizeof(buff));
			inet_pton(AF_INET,result[2], &t_in);

			LIST *tmp = search_ip(head,t_in);
			
			sprintf(buff,"%s:[%s]:%s","msg",result[1], result[3]);
	
			send(tmp->new_fd,buff,strlen(buff),0);	
		
		}else if(strstr(result[0], "up")){
			LIST *tmp = search_ip(head,tp->num);

			char up_msg[128]="";
			bzero(up_msg,sizeof(up_msg));
			sprintf(up_msg, "up:%s", tmp->name);
			up_link(head, up_msg, tmp->num);
		
		}else if(strstr(result[0], "down")){
			if(result[1] != NULL){
				unsigned long cNum = atol(result[1]);
				LIST *tmp = search_ip(head,cNum);

				char up_msg[128]="";
				bzero(up_msg,sizeof(up_msg));
				sprintf(up_msg, "down:%s", tmp->name);
				up_link(head, up_msg, cNum);
				head = delete_link(head, tmp->name);	
			}
		}else if(strstr(result[0], "checkall")){

			unsigned long sNum = 0;
			inet_pton(AF_INET, result[1], &sNum);

			check_all_member(head,sNum);

		}else if(strstr(result[0], "find")){
			unsigned long sNum = 0,dNum = 0;
			inet_pton(AF_INET, result[1], &sNum);

			inet_pton(AF_INET, result[2], &dNum);

			char up_msg[128]="";
			bzero(up_msg,sizeof(up_msg));
			sprintf(up_msg, "%s", result[2]);
			check_member(head,up_msg,sNum,dNum);
		}else if(strstr(result[0], "file")){
			char file_msg[1024]="";
			sprintf(file_msg, "do you recv file from:%s", result[1]);

			bzero(&t_in, sizeof(t_in));
			inet_pton(AF_INET,result[2], &t_in);

			LIST *tmp = search_ip(head,t_in);
			send(tmp->new_fd, file_msg, strlen(file_msg),0);	
		
		}else if(strstr(result[0], "yes")){
			bzero(&t_in, sizeof(t_in));
			bzero(buff,sizeof(buff));

			inet_pton(AF_INET,result[2], &t_in);

			LIST *tmp = search_ip(head,t_in);

			sprintf(buff,"%s:%s","yes", result[1]);

			send(tmp->new_fd, buff, strlen(buff),0);
		}
	}
	printf("=================close new_fd===================\n");
	close(tp->new_fd);
	pthread_exit(NULL);
}


void server_bind(void *data)
{
	SER *tp = (SER *)data;

	tp->sockfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&tp->my_addr,sizeof(tp->my_addr));

	tp->my_addr.sin_family = AF_INET;
	tp->my_addr.sin_port = htons(8000);
	tp->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	signal(SIGINT,clinet_down);

	int ret = bind(tp->sockfd,(struct sockaddr *)&tp->my_addr,sizeof(tp->my_addr));
	if (0 != ret)
	{
		perror("bind");
		close(tp->sockfd);
		exit(1);
	}

	sock_f_d = tp->sockfd;

	listen(tp->sockfd,10);

	while(1)
	{	
		
		struct sockaddr_in from_addr;
		socklen_t from_len = sizeof(from_addr);
	
		tp->new_fd =  accept(tp->sockfd,(struct sockaddr *)&from_addr,&from_len);

		LIST temp;
		temp.new_fd = tp->new_fd;
		temp.num = from_addr.sin_addr.s_addr;
#if 1
		char ip[16]="";
		inet_ntop(AF_INET, &from_addr.sin_addr.s_addr, ip, 16);
		strcpy(temp.name, ip);
		printf("ip = [%s]\n", ip);
#endif		

		printf("temp.num ==%lu\n",temp.num);

		head = insert_link(head,temp);
		
		usleep(500);

		char up_msg[128]="";
		bzero(up_msg,sizeof(up_msg));
		sprintf(up_msg, "IP:%lu", temp.num);
		send(tp->new_fd, up_msg, strlen(up_msg),0);
	
		pthread_t tid;

		pthread_create(&tid,NULL,server_fun,&temp);	
		
		pthread_detach(tid);//线程分离
	}

}

