#include	"unp.h"
#include	<string.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;
	char				recvline[MAXLINE + 1];
	int n;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(7001);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		while(strcmp(recvline,"exit\r\n")){
	    if ( (n = read(connfd, recvline, MAXLINE)) > 0) {
			recvline[n] = 0;	/* null terminate */
			fputs("server-recvmsg:",stdout);
			if (fputs(recvline, stdout) == EOF)
				err_sys("fputs error");
			int a,b;
			sscanf(recvline, "%d %d", &a, &b);
			//fputs("server said:",stdout);
			//fgets(buff, MAXLINE-1, stdin);
			snprintf(buff, sizeof(buff), "add: %d\r\nsub: %d\r\nmul: %d\r\ndiv: %f\r\n", a+b,a-b,a*b,(float)a/(float)b);
			Write(connfd, buff, strlen(buff));
		}
        //ticks = time(NULL);

        //Write(connfd, buff, strlen(buff));

		}
		Close(connfd);
	}
}
