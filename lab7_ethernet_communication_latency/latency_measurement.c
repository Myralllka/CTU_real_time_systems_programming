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

#define MAX_BUF 2048
char buf[MAX_BUF];
char recv_buf[MAX_BUF];

#define MAX_DELAY 10000
#define CLOCK_RATE 1000

uint32_t delays[MAX_DELAY];


#define DEBUG_OUTPUT
#undef DEBUG_OUTPUT


void udp_latency(char *ip_address, int port, int payload_size, int messages_count)	
{
	
	if (payload_size > MAX_BUF) {
		fprintf(stderr, "Error: Max allowed payload size -- %d\n", MAX_BUF);
		exit(3);
	}
    if (sysTimestampEnable() == ERROR) {
        perror("Time stamps could not be enabled");
        return;
    };
	memset(delays, 0, sizeof(delays));
	sysClkRateSet(CLOCK_RATE);
	
	
	int sockd;
	struct sockaddr_in my_name, cli_name, srv_addr;
	int count;
	int addrlen;
	int i;
	uint64_t  start, end;
	uint32_t time_elapsed, max_delay = 0;
	
	
	// Common part for both listened and the sender
	sockd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockd == -1) {
		perror("Could not open the socket...");
		exit(1);
	}
	
	my_name.sin_family = AF_INET;
	my_name.sin_addr.s_addr = INADDR_ANY;
	my_name.sin_port = htons(port);
	
	if (bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name)) == -1) {
		perror("Could not bind the socket...");
		close(sockd);
		exit(2);
	}
	
	printf("Measurement started\n");
	if (ip_address == NULL) {
		// Running as a listener
		
#ifdef DEBUG_OUTPUT
		printf("Runnign as a listener...\n");
#endif

		i = 0;
		addrlen = sizeof(cli_name);
		while ((i++ != messages_count) || messages_count == 0) {			
			
			if (recvfrom(sockd, buf, MAX_BUF, 0, (struct sockaddr*)&cli_name, &addrlen) == -1) {
				continue;
			}
			if (sendto(sockd, buf, strlen( buf)+1, 0, (struct sockaddr*)&cli_name, sizeof(cli_name)) == -1) {
				perror("Message not sent back");
			}
		}
		close(sockd);
	} else {
		// Running as a sender
		for (i = 0; i < payload_size; i++) {
			buf[i] = '0' + (i % 10); // Fill buf with digits
			buf[payload_size - 1] = '\0';
		}
		
		srv_addr.sin_family = AF_INET;
		inet_aton(ip_address, &srv_addr.sin_addr);
		srv_addr.sin_port = htons(port);
		
		i = 0;
		while (i++ != messages_count || messages_count == 0) {
			addrlen = sizeof(srv_addr);
			
			start = sysTimestamp();
			sendto(sockd, buf, payload_size, 0, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
			
			count = recvfrom(sockd, recv_buf, payload_size, 0, (struct sockaddr*)&srv_addr, &addrlen);
			end = sysTimestamp();

#ifdef DEBUG_OUTPUT
			if (strcmp(buf, recv_buf) != 0) {
				printf("Received message is wrong...\n");
				int j;
				for (j = 0; j < payload_size - 1; j++) {
					buf[j] = (buf[j] + 1) % 10 + '0';
				}
			}
			if (start > end) {
				fprintf(stderr, "END > START....\n");
				continue;
			}
			if (count != payload_size) {
				printf("Received message is of wrong size...\n Message: %s\n", recv_buf);
			}
#endif
			
			
			time_elapsed = ((end - start) * 1000000) / sysTimestampFreq();
			if (time_elapsed < MAX_DELAY) {
				max_delay = max_delay < time_elapsed ? time_elapsed : max_delay;
				delays[time_elapsed]++;
			} else {
#ifdef DEBUG_OUTPUT
				printf("Delay is too big: %d...\n", time_elapsed);
#endif
			}
		}
		close(sockd);
		
		printf("0");
		for (i = 1; i < max_delay + 1; i++) {
			printf(", %d", i);
		}
		printf("\n");
		
		printf("%d", delays[0]);
		for (i = 1; i < max_delay + 1; i++) {
			printf(", %d", delays[i]);
		}
		printf("\n");
	}
	printf("Measurement finished\n");
}
