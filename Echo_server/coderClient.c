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
    saddr.sin_port = htons(9999);
    int ret = connect(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }
    char recvBuf[1024];
    char buf[128];
    while(1){
        memset(buf,0,128);
        fgets(buf,128,stdin);
        write(fd,buf,strlen(buf));

        int len = read(fd,recvBuf,sizeof(recvBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv server data : %s\n",recvBuf);
        }else if(len == 0){
            printf("server closed...\n");
            break;
        }
    }

      // 关闭连接
    close(fd);
    return 0;
}
