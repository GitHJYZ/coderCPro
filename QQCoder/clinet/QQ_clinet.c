#include "QQ_clinet.h"

void QQ_clinet_up(void *data)//客户端提醒上线
{
	CS *FLAM = (CS *)data;

	FLAM->sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (FLAM->sockfd < 3)
	{
		perror("socket");
		close(FLAM->sockfd);
		exit(1);
	}

	bzero(&FLAM->dst_addr,sizeof(FLAM->dst_addr));

	FLAM->dst_addr.sin_family = AF_INET;
	FLAM->dst_addr.sin_port = htons(8000);
	FLAM->dst_addr.sin_addr.s_addr = inet_addr("192.168.80.134");

	int ret = connect(FLAM->sockfd,(struct sockaddr *)&FLAM->dst_addr,sizeof(FLAM->dst_addr));
	if (0 != ret)
	{
		perror("connect");
		close(FLAM->sockfd);
		exit(2);
	}

	char msg[]="up:I'm Coming!"; 

	send(FLAM->sockfd,msg,strlen(msg),0);
	
	return;
}

void *clinet_recever(void *arg)//客户端收消息
{
	CS *FLAM = (CS *)arg;
	char buf[1024]="";
	int num=0;

	while(1)
	{
		
		bzero(buf, sizeof(buf));
		char *result[5]={NULL};
		num = 0;

		int ret = recv(FLAM->sockfd,buf,sizeof(buf),0);
		if (0 == ret)
		{
			printf("111111111111111\n");
			close(FLAM->sockfd);
			exit(3);
		}

		result[num]=strtok(buf,":");
		while(!(result[num]==NULL))
		{
			num++;
			result[num]=strtok(NULL,":");
		}

		printf("recv result[3] = %s\n", result[3]);
		printf("result[2] = %s\n", result[2]);
		printf("result[1] = %s\n", result[1]);
		printf("result[0] = %s\n", result[0]);


		if (strstr(result[0], "msg")){
			printf("from:%s:%s\n", result[1], result[2]);
			printf("please input:A.IP:function:B.IP:news\n");
		}else if(strstr(result[0], "yes")){
			int sock_fd = 0;
			send_file(sock_fd, result[1]);
		}else if(strstr(result[0], "IP")){ 
			FLAM->num = atol(result[1]);
			//printf("myIdNum%s\n", result[1]);
		}else if(strstr(result[0], "up")){
			printf("%s:%s\n", result[1], result[0]);
		}else if(strstr(result[0], "down")){
			printf("%s:%s\n", result[1], result[0]);
		}else if(strstr(result[0], "exist")){
			printf("%s:%s\n", result[1], result[0]);
		}else if(strstr(result[0], "find")){
			printf("%s:%s\n", result[1], result[0]);
		}else{
			printf("%s\n",result[0]);
			printf("please input:A.IP:function:B.IP:news\n");
		}
		
	}
	
	return NULL;
} 



void QQ_clinet_talking(void *data)//客户端发消息
{
	CS *FLAM = (CS *)data;
	char cmd[1024]="";
	char temp[1024] = "";
	int num = 0;
	pthread_t tid;

	pthread_create(&tid,NULL,clinet_recever,FLAM);

	pthread_detach(tid);

	while(1){
		printf("msg:please input: msg:SRC.IP:DST.IP:news\n");
		printf("find:please input:find:SRC.IP:DST.IP\n");
		printf("checkall:please input:checkall:SRC.IP\n");
		printf("file:please input: file:SRC.IP:DST.IP\n");
		printf("yes:please input: yes:SRC.IP:DST.IP\n");
		
		fgets(cmd,sizeof(cmd),stdin);
		cmd[strlen(cmd)-1]=0;

		strcpy(temp, cmd);

		char *result[5]={NULL};
		num = 0;

		result[num]=strtok(cmd,":");

		printf("push result[0] = %s\n", result[0]);

		while(!(result[num]==NULL))
		{
			num++;
			result[num]=strtok(NULL,":");
		}

		printf("push result[3] = %s\n", result[3]);
		printf("result[2] = %s\n", result[2]);
		printf("result[1] = %s\n", result[1]);
		printf("result[0] = %s\n", result[0]);

		if (!strcmp(result[0], "yes"))
		{
			int sock_fd = 0;
			send(FLAM->sockfd, temp, strlen(temp), 0);
			file_sock(sock_fd, result[2]);
			sleep(1);
		}else{
			send(FLAM->sockfd, temp, strlen(temp), 0);
			printf("%s\n",temp);
		}
		
	}
	printf("=========FLAM->sockfd===========\n");
	close(FLAM->sockfd);
	return;
}


void QQ_clinet_down(void *data)//客户端下线提醒
{
	CS *FLAM = (CS *)data;

	char d_msg[32]="";

	sprintf(d_msg, "down:%lu", FLAM->num);

	send(FLAM->sockfd,d_msg,strlen(d_msg),0);

	return;
}




void file_sock(int sockf_d, char *dst_ip)
{
	sockf_d = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockf_d < 0)
	{
		perror("socket");
		exit(-2);
	}

	struct sockaddr_in my_addr;
	bzero(&my_addr, sizeof(my_addr));

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(7000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(sockf_d, (struct sockaddr *)&my_addr,sizeof(my_addr));
	if (ret != 0)
	{
		perror("bind");
		exit(-1);
	}


	char file_name[128]="";

	struct sockaddr_in from_addr;
	bzero(&from_addr, sizeof(from_addr));

	socklen_t sock_len = sizeof(from_addr);

	ret = recvfrom(sockf_d, file_name, sizeof(file_name), 0, (struct sockaddr *)&from_addr, &sock_len);


	printf("ret recv  =  %d file_name = %s\n", ret, file_name);

	FILE *fp = fopen(file_name, "w+b");

	char buff[1024] = "";
	char send_buf[18]="";
	int i = 0;
	while(1)
	{	
		bzero(send_buf, sizeof(send_buf));

		sprintf(send_buf, "%d", i);
		ret = sendto(sockf_d, send_buf, strlen(send_buf), 0, (struct sockaddr *)&from_addr, sizeof(from_addr));
		printf("ret sendto = %d\n", ret);

		bzero(buff, sizeof(buff));
		ret = recvfrom(sockf_d, buff, sizeof(buff), 0, (struct sockaddr *)&from_addr, &sock_len);

		i++;

		fwrite(buff, 1, 1024, fp);

		printf("ret write = %d\n", ret);

		if (ret < 1024)
		{
			break;
		}
	}
	close(sockf_d);
}


void send_file(int sock_fd, char *dst_ip)
{
	int ret = sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (ret < 0)
	{
		perror("socket");
		exit(-3);
	}


	struct sockaddr_in my_addr;
	bzero(&my_addr, sizeof(my_addr));

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8000);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sock_fd, (struct sockaddr *)&my_addr,sizeof(my_addr));
	if (ret != 0)
	{
		perror("bind");
		exit(-4);
	}


	struct sockaddr_in dst_addr;
	bzero(&dst_addr, sizeof(dst_addr));
	
	dst_addr.sin_family = AF_INET;
	dst_addr.sin_port = htons(7000);
	dst_addr.sin_addr.s_addr = inet_addr(dst_ip);	

	printf("please input file name\n");
	
	char file_name[128]="";
	fgets(file_name, sizeof(file_name), stdin);
	file_name[strlen(file_name)-1] = 0;

	printf("file_name = %s\n", file_name);
	ret = sendto(sock_fd, file_name, strlen(file_name), 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
	printf("UDP_SEND ret = %d\n", ret);

	FILE *fp = fopen(file_name, "a+b");
	char send_buf[1024]="";
	char rcv_buf[16]="";
	int i = 0;

	while(1){

		recvfrom(sock_fd, rcv_buf, sizeof(rcv_buf), 0, NULL, NULL);
		printf("rcv_buf = %s\n", rcv_buf);

		if (atoi(rcv_buf) == i)
		{
			bzero(send_buf, sizeof(send_buf));
			ret = fread(send_buf, 1, 1024, fp);
			printf("read ret 1 = %d\n", ret);

			ret = sendto(sock_fd, send_buf, ret, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));

			printf("ret read = %d\n", ret);
			i++;
		}
		

		if (ret < 1024)
		{
			break;
		}
	}
	close(sock_fd);
}