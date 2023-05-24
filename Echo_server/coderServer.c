//TCP 通讯服务端实现

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1){
        perror("socket");
        exit(-1);
    }
    unsigned int num = 0;
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.80.134", &num);
    saddr.sin_addr.s_addr = num;
    //saddr.sin_addr.s_addr = 0;
    saddr.sin_port = htons(9999);
    int ret = bind(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    ret = listen(fd,8);
    if(ret == -1){
        perror("listen");
        exit(-1);
    }
    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(fd,(struct sockaddr*)&clientaddr,&len);
     if(cfd == -1){
        perror("accept");
        exit(-1);
    }

    char clientIP[16];
    inet_ntop(AF_INET,(struct sockaddr*)&clientaddr.sin_addr,clientIP,16);
    printf("ip = %s\n",clientIP);

    // 5.通信
    char recvBuf[1024] = {0};
    char buf[128];
    while(1){
        printf("wait client rev data....\n");
        int num = read(cfd,recvBuf,sizeof(recvBuf));
        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data : %s\n", recvBuf);
        } else if(num == 0) {
            // 表示客户端断开连接
            printf("clinet closed...");
            break;
        }
        write(cfd, recvBuf, strlen(recvBuf));
    }

     // 关闭文件描述符
    close(fd);
    close(cfd);

    return 0;
}
