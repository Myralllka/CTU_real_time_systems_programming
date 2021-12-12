#ifndef SERVER_HTTP_H
#define SERVER_HTTP_H

#define HTTP_SERVER_PORT     80 /* Port 80 is reserved for HTTP protocol */
#define HTTP_SERVER_MAX_CONNECTIONS  20
#define HTTP_RECCEIVER_BUF_SIZE 5000

void run_http_srv();
void update_statistics();


#endif
