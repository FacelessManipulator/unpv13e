#include	"unp.h"
#include	<time.h>

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
	servaddr.sin_port        = htons(8000);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		while(strcmp(recvline,"exit")){
	    if ( (n = read(connfd, recvline, MAXLINE)) > 0) {
			recvline[n] = 0;	/* null terminate */
			fputs("server-recvmsg:",stdout);
			if (fputs(recvline, stdout) == EOF)
				err_sys("fputs error");
		}
        //ticks = time(NULL);
        //snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        //Write(connfd, buff, strlen(buff));
		fputs("server said:",stdout);
		fgets(buff, MAXLINE-1, stdin);
        Write(connfd, buff, strlen(buff));
		}
		Close(connfd);
	}
}
