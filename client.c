#include <stdio.h>
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
	char buf[MAX_LINE];
	int s;
	int len;

	if(argc==2){
		host=argv[1];
	}
	else{
		fprintf(stderr,"host\n");
	}

	//host name into peer's ip
	hp=gethostbyname(host);
	if(!hp){
		fprintf(stderr,"unknown host : %s\n",host);
	}

	//addr data structure
	bzero((char *)&sin,sizeof(sin)); //buffer 0으로 저장
	sin.sin_family=AF_INET;
	bcopy(hp->h_addr,(char *)&sin.sin_addr,hp->h_length);
	sin.sin_port=htons(SERVER_PORT); //host byte -> network byte

	//active open
	if((s=socket(PF_INET,SOCK_STREAM,0))<0){
		perror("socket");
	}

	if(connect(s,(struct sockaddr *)&sin,sizeof(sin))<0){
		perror("connect");
		close(s);
	}

	while(fgets(buf,sizeof(buf),stdin)){
		buf[MAX_LINE-1]='\0';
		len=strlen(buf)+1;
		send(s,buf,len,0);
	}
}