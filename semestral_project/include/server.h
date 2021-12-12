#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inetLib.h>
#include <sockLib.h>
#include <sysLib.h>
#include <taskLib.h>
#include "../include/shared.h"

#define DEFAULT_PORT 8000

void run_udp_srv(char *ip_address, int port);

#endif
