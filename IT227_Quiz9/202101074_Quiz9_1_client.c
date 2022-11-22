#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

char *questions[] = {"You study in which university?", "which course are you studying?", "what is your area of interest? ", " Which degree have you registered for ? "};
char *answers[] = {"DAIICT", "Systems Programming", "Embedded Systems", "MSc IT"};

#define MAXLINE 8192

int open_clientfd(char *hostname, char *port) {
     int clientfd;
     struct addrinfo hints, *listp, *p;
     char host[MAXLINE], service[MAXLINE];
     int flags;

     memset(&hints, 0, sizeof(struct addrinfo));
     hints.ai_socktype = SOCK_STREAM;
     hints.ai_flags = AI_NUMERICSERV;
     hints.ai_flags |= AI_ADDRCONFIG;
     getaddrinfo(hostname, port, &hints, &listp);

     for (p = listp; p; p = p->ai_next) {
          if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
               continue;

          flags = NI_NUMERICHOST | NI_NUMERICSERV;
          getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
          printf("host:%s, service:%s\n", host, service);

          if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
               printf("Connected to server %s at port %s\n", host, service);
               break;
          }
          close(clientfd);
     }
     freeaddrinfo(listp);
     if (!p)
          return -1;
     else
          return clientfd;
}

int main() {
     int clientfd;
     char *host, *port;
     host = "0.0.0.0";
     port = "5000";
     clientfd = open_clientfd(host, port);
     while (1) {
          int n;

          printf("Choose question number (1-4) or 0 to exit: \n");
          for (int i = 0; i < 4; i++) {
               printf("Question %d: %s\n", i + 1, questions[i]);
          }
          scanf("%d", &n);
          if (n == 0) {
               write(clientfd, "quit", 5);
               break;
          }
          else if (n > 0 && n < 5) {
               write(clientfd, questions[n - 1], strlen(questions[n - 1]) + 1);
               char buf[MAXLINE];
               read(clientfd, buf, MAXLINE);
               printf("Answer: %s\n", buf);
          }
          else {
               printf("Invalid question number");
          }
     }
     close(clientfd);
     exit(0);
}