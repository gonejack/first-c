/*
 * Poll Usage Sample
 * int poll (struct pollfd *fds, nfds_t nfds, int timeout);
 * Note:
 * As a tcp server, this program can accept multi-client connections simultaneously.
 *
 * Copyright (c) 2016 Liming Shao <lmshao@163.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <poll.h>

#define BACKLOG 5
#define BUFF_SIZE 200
#define DEFAULT_PORT 6666
#define OPEN_MAX 1024
int main(int argc, char **argv) {
  int SERV_PORT = DEFAULT_PORT;

  if (argc > 2)
    printf("param err:\nUsage:\n\t%s port | %s\n\n", argv[0], argv[0]);
  if (argc == 2)
    SERV_PORT = atoi(argv[1]);

  int i, maxi, nready;
  int servSocket, cliSocket;
  ssize_t nbytes;
  char buf[BUFF_SIZE];
  socklen_t addrLen;
  struct pollfd client[OPEN_MAX];
  struct sockaddr_in cliAddr, servAddr;

  if ((servSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }

  int optval = 1;
  if (setsockopt(servSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("setsockopt");
    exit(0);
  }

  bzero(&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons(SERV_PORT);
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(servSocket, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
    perror("bind");
    exit(1);
  }

  if (listen(servSocket, BACKLOG) < 0) {
    perror("listen err");
    exit(1);
  }
  printf("Listen Port: %d\nListening ...\n", SERV_PORT);

  client[0].fd = servSocket;
  client[0].events = POLLRDNORM;
  for (i = 1; i < OPEN_MAX; i++)
    client[i].fd = -1; /* -1 indicates available entry */
  maxi = 0;              /* max index into client[] array */

  for (;;) {
    nready = poll(client, maxi + 1, -1);
    if (nready < 0) {
      printf("poll err");
      exit(1);
    }

    if (client[0].revents & POLLRDNORM) /* new client connection */
    {
      addrLen = sizeof(cliAddr);
      if ((cliSocket = accept(servSocket, (struct sockaddr *) &cliAddr, &addrLen)) < 0) {
        printf("accept err");
        exit(1);
      }

      for (i = 1; i < OPEN_MAX; i++)
        if (client[i].fd < 0) {
          client[i].fd = cliSocket; /* save descriptor */
          break;
        }

      printf("\nNew client connections client[%d] %s:%d\n", i, inet_ntoa(cliAddr.sin_addr),
             ntohs(cliAddr.sin_port));

      if (i == OPEN_MAX)
        printf("too many clients");

      client[i].events = POLLRDNORM;
      if (i > maxi)
        maxi = i; /* max index in client[] array */

      if (--nready <= 0)
        continue; /* no more readable descriptors */
    }

    for (i = 1; i <= maxi; i++) /* check all clients for data */
    {
      if ((cliSocket = client[i].fd) < 0)
        continue;

      if (client[i].revents & (POLLRDNORM | POLLERR)) {
        memset(buf, 0, BUFF_SIZE);
        nbytes = recv(cliSocket, buf, BUFF_SIZE, 0);
        if (nbytes < 0) {
          printf("recv err");
          continue;
        } else if (nbytes == 0) {
          printf("client[%d] closed connection\n", i);
          close(cliSocket);
          client[i].fd = -1;
        } else {
          printf("\nFrom client[%d]\n", i);
          printf("Recv: %sLength: %d\n\n", buf, (int) nbytes);
        }

        if (--nready <= 0)
          break; /* no more readable descriptors */
      }
    }
  }
}