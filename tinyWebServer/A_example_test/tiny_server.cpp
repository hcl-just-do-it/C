/*linux socket AF_INET TCP 编程示例，单进程单线程，ehco 服务端*/
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

void sendHtml(int clientfd,const char *filePath){
    FILE *fp = fopen(filePath,"r");
    if(fp == nullptr){
        printf("fopen filePath error\n");
		return ;
    }
    char data[1024];
    while(fgets(data,1024,fp)!=NULL){
        printf("%s",data);
        send(clientfd,data,strlen(data),0);
    }
    fclose(fp);
}
int main()
{
	//注意开放端口！！！！！！！！！！
	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	int serv_addr_len = sizeof(serv_addr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(1234);
	
	//将 inet_ntoa() 改用 inet_ntop() 这个现代方法，支持 IPV4 和 IPV6
	//printf("bind in %s : %d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
	//INET_ADDRSTRLEN 是标识 IPV4 地址展现字符串的大小常量,INET6_ADDRSTRLEN是 IPV6 的
	char serv_ip[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &serv_addr.sin_addr, serv_ip, sizeof(serv_ip)) == NULL) {
		printf("inet_ntop error\n");
		close(server_sock);
		return 0;
	}
	int reuse = 1;
	//端口复用，无需等待time_wait。
    setsockopt( server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( reuse ) );
	printf("bind in ip = %s port =  %d\n", serv_ip, ntohs(serv_addr.sin_port));
	if (bind(server_sock, (struct sockaddr*)&serv_addr, serv_addr_len) < 0) {
		printf("bind error\n");
		return 0;
	}
	
	if (listen(server_sock, 1)) {
		printf("listen error\n");
		return 0;
	}
	
	char buf[1024];int count = 0;
	while (1) {
		struct sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);
		
		printf("等待第%d次链接的到来\n",count++);
		int client_sock = accept( server_sock, 
								  (struct sockaddr*)&client_addr, 
								  (unsigned int *)&client_addr_len );

		if (client_sock == -1) {
			printf("accept error\n");
			return 0;
		}
		printf("有新连接到来\n");
		printf("连接请求：\n");
        int n = recv(client_sock, buf, sizeof(buf), 0);
		buf[n] = '\0';//字符串结束符，不加会乱码
		printf("%s",buf);
		printf("n = %d\n",n);
		printf("连接响应：\n");
        char sendBuf[1024];
        sprintf(sendBuf,"HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n");
        if (send(client_sock, sendBuf, strlen(sendBuf), 0) < 0) {//char数组用strlen而不是sizeof
            printf("send error\n");
            return 0;
        }
		printf("发送数据:%s",sendBuf);
		//sendHtml(client_sock,"./tinyWebServer/root/welcome.html");//文件发送
		sprintf(sendBuf,"<html><body><h1>hello html</h1></body></html>");//直接发送
		if (send(client_sock, sendBuf, strlen(sendBuf), 0) < 0) {//char数组用strlen而不是sizeof
            printf("send error\n");
            return 0;
        }
		close(client_sock);
		printf("连接离开\n");
	}

	close(server_sock);
	return 0;
}