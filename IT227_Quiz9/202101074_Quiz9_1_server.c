
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define MAXLINE 8192
#define LISTENQ 1024

char *questions[] = {"You study in which university?", "which course are you studying?", "what is your area of interest? ", " Which degree have you registered for ? "};
char *answers[] = {"DAIICT", "Systems Programming", "Embedded Systems", "MSc IT"};

int open_listenfd(char *port) {
     struct addrinfo hints, *listp, *p;
     int listenfd, optval = 1;
     char host[MAXLINE], service[MAXLINE];
     int flags;

     memset(&hints, 0, sizeof(struct addrinfo));
     hints.ai_socktype = SOCK_STREAM;
     hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
     hints.ai_flags |= AI_NUMERICSERV;
     getaddrinfo(NULL, port, &hints, &listp);

     for (p = listp; p; p = p->ai_next) {
          if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
               continue;

          setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

          flags = NI_NUMERICHOST | NI_NUMERICSERV;
          getnameinfo(p->ai_addr, p->ai_addrlen, host, MAXLINE, service, MAXLINE, flags);
          printf("host:%s, service:%s\n", host, service);

          if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
               break;
          close(listenfd);
     }

     freeaddrinfo(listp);
     if (!p)
          return -1;

     if (listen(listenfd, LISTENQ) < 0) {
          close(listenfd);
          return -1;
     }
     return listenfd;
}

void echo(int connfd) {
     size_t n;
     char buf[MAXLINE];
     while ((n = read(connfd, buf, MAXLINE)) != 0) {
          if (strcmp(buf, "quit") == 0) {
               printf("Client disconnected\n");
               exit(0);
          }
          printf("server received %d bytes\n", (int)n);
          printf("Question: %s\n", buf);
          for (int i = 0; i < 4; i++) {
               if (strcmp(buf, questions[i]) == 0) {
                    printf("Answer: %s\n", answers[i]);
                    write(connfd, answers[i], strlen(answers[i]) + 1);
                    break;
               }
          }
     }
}

int main(int argc, char **argv) {
     int listenfd, connfd;
     socklen_t clientlen;
     struct sockaddr_storage clientaddr;
     char client_hostname[MAXLINE], client_port[MAXLINE];
     listenfd = open_listenfd("5000");
     while (1) {
          printf("Waiting for a new Client to connect\n");
          clientlen = sizeof(struct sockaddr_storage);
          connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
          getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
          printf("Connected to (%s, %s)\n", client_hostname, client_port);
          printf("Start Communication with Client\n");
          echo(connfd);
          printf("End Communication with Client\n");
          close(connfd);
     }
     exit(0);
}