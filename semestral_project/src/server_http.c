#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../include/shared.h"
#include "../include/server_http.h"
#include "../include/svg_generator.h"
#include <netdb.h>
#include <stdio.h>
#include <sockLib.h>
#include <string.h>
#include <taskLib.h>


static void one_client_server(int client_fd) {
	char buf[HTTP_RECCEIVER_BUF_SIZE];
	int message_size;
	while ((message_size = recv(client_fd, buf, sizeof(buf) - 1, 0))) {
		if (message_size == -1) {
			perror("Receiving message through the socket");
			break;
		}
		buf[message_size] = '\0';
		// Ignoring all headers for now. TODO: 
		// Dealing only with GET request to the root
#ifdef DEBUG_OUTPUT
		int i;
		for (i = 0; i < message_size; i++)
			printf("%c", buf[i]);
			
#endif
		
		
		if (message_size > 5) {
			if (strncmp(buf, "GET / ", 6) == 0) {
				printf("Sending SVG..\n");
				FILE *f = fdopen(client_fd, "w");
				fprintf(f, "HTTP/1.0 200 OK\r\n\r\n");
				generate_html_file(f);
				fclose(f);
				printf("Image sent\n");
				
				
			}
		}
	}
	
	close(client_fd);
}


void run_http_srv() {
  int s;
  int new_fd;
  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  int sockAddrSize;

  sockAddrSize = sizeof(struct sockaddr_in);
  bzero((char *) &serverAddr, sizeof(struct sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(HTTP_SERVER_PORT);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s<0) {
    printf("Error: www: socket(%d)\n", s);
    return;
  }


  if (bind(s, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR) {
    printf("Error: www: bind\n");
    return;
  }

  if (listen(s, HTTP_SERVER_MAX_CONNECTIONS) == ERROR) {
    perror("www listen");
    close(s);
    return;
  }

  printf("www server running\n");
  
  char task_name_buf[100];

  int client_num = 0;
  while(1) {
    /* accept waits for somebody to connect and the returns a new file descriptor */
    if ((new_fd = accept(s, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR) {
      perror("www accept");
      close(s);
      return;
    }
    sprintf(task_name_buf, "tOneClientServer%d", client_num++);
    if (taskSpawn(task_name_buf, HTTP_SERVER_PRIORITY, 0, 65536, (FUNCPTR)one_client_server, new_fd, 0, 0, 0, 0, 0, 0, 0, 0, 0) == ERROR) {
    	perror("Creating task for communication with on client");
    	close(s);
    	close(new_fd);
    	return;
    }
    
  }
}
