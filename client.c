#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 47500
#define MAX_LINE 256

int main(int argc, char *argv[]){
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin; 
	char *host;
	char buf[]="2014210069";
	int s=socket(PF_INET,SOCK_STREAM,0);
	int len;

	host = '127.0.0.1';

	if(argc==2){
		host=argv[1];
	}
	else{
		fprintf(stderr,"host\n");
	}

	//host name into peer's ip
	hp=gethostbyname(host);
	if(hp==NULL){
		fprintf(stderr,"unknown host : %s\n",host);
		exit(0);
	}

	//addr data structure
	bzero((char *)&sin,sizeof(sin)); //buffer 0으로 저장
	sin.sin_family=AF_INET;
	bcopy(hp->h_addr,(char *)&sin.sin_addr,hp->h_length);
	sin.sin_port=htons(SERVER_PORT); //host byte -> network byte

	//active open
	if(s<0){
		perror("socket");
		exit(0);
	}

	if(connect(s,(struct sockaddr *)&sin,sizeof(sin))<0){
		perror("connect");
		close(s);
	}
	bzero(buf,MAX_LINE);

		buf[MAX_LINE-1]='\0';
		len=strlen(buf)+1;
		send(s,buf,len,0);

}