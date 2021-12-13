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

/*!
 * Entry point of the task that serves one request of one client of the server
 * Function sends an HTML file with plots if receives a GET request to the root
 *
 * @param client_fd Open file descriptor for communication with the client through TCP socker
*/
static void one_client_server(int client_fd) {
    char buf[HTTP_RECCEIVER_BUF_SIZE];
    int message_size;
    if ((message_size = recv(client_fd, buf, sizeof(buf) - 1, 0))) {
        if (message_size == -1) {
            perror("Receiving message through the socket");
            close(client_fd);
            return;
        }
        buf[message_size] = '\0';
        // Ignoring all headers for now. TODO:
        // Dealing only with GET request to the root
#ifdef DEBUG_OUTPUT
        int i;
        for (i = 0; i < message_size; i++)
            printf("%c", buf[i]);

#endif
       // Firstly, check if the request is the GET one to the root
        if (message_size > 5) {
            if (strncmp(buf, "GET / ", 6) == 0) {
                printf("Sending SVG..\n");
                FILE *f = fdopen(client_fd, "w");i

                // Send the only header
                fprintf(f, "HTTP/1.0 200 OK\r\n\r\n");

                // Send html first tags with JS function for reloading page
                fprintf(f, "<!DOCTYPE html>\n<html>\n");
                fprintf(f, "<body onload=\"setTimeout(function(){location.reload()}, 400);\">");
                
                // Generate plots in the file
                generate_html_file(f);

                // Send html closing tags
                fprintf(f, "</body>\n</html>");
                fclose(f);
#ifdef DEBUG_OUTPUT
                printf("Image sent\n");
#endif
            }
        }
    }

    close(client_fd);
}

/*!
 * Entry point of the task for running the HTTP server
 * The task creates a new task for serving each request from any client
*/
void run_http_srv() {
    int s;
    int new_fd;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t sockAddrSize;

    sockAddrSize = sizeof(struct sockaddr_in);
    bzero((char *) &serverAddr, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(HTTP_SERVER_PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
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

#ifdef DEBUG_OUTPUT
    printf("www server running\n");
#endif

    char task_name_buf[100];

    int client_num = 0;
    while (1) {
        /* accept waits for somebody to connect and the returns a new file descriptor */
        if ((new_fd = accept(s, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR) {
            perror("www accept");
            close(s);
            return;
        }
        sprintf(task_name_buf, "tOneClientServer%d", client_num++);
        if (taskSpawn(task_name_buf, HTTP_SERVER_PRIORITY, VX_FP_TASK, 65536, (FUNCPTR) one_client_server, new_fd, 0, 0, 0, 0, 0, 0, 0, 0, 0) == ERROR) {
            perror("Creating task for communication with an client");
            close(s);
            close(new_fd);
            return;
        }
    }
}
