#include "../include/server.h"
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


/*!
 * \brief Run udp server for sharing data
 * We use this function for communication between two microzed boards
 * It sends desire position from one board to another using BSD sockets
 * 
 * @param ip_address : char* - server's ip address 
 * @param port : int - udp port for sockets
 */
void run_udp_srv(char *ip_address, int port) {
    // init semaphore
    SEM_ID sem_motor_pwm_change = semOpen("/sem_motor_pwm_change", SEM_TYPE_COUNTING, SEM_EMPTY, SEM_Q_FIFO, OM_CREATE, NULL);

    // information_preprocessing
    if (sysTimestampEnable() == ERROR) {
        perror("Time stamps could not be enabled");
        return;
    }

    int sockd;
    struct sockaddr_in my_name, cli_name, srv_addr;
    socklen_t addrlen;
    const int buf_len = sizeof(int32_t);
    int i, status;

    // Common part for both receiver and the transmitter
    sockd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockd == -1) {
        perror("Could not open the socket...");
        exit(1);
    }

    my_name.sin_family = AF_INET;
    my_name.sin_addr.s_addr = INADDR_ANY;
    my_name.sin_port = htons(port);

    if (bind(sockd, (struct sockaddr *) &my_name, sizeof(my_name)) == -1) {
        perror("Could not bind the socket...");
        close(sockd);
        exit(2);
    }

    addrlen = sizeof(cli_name);


    if (ip_address == NULL) {
        // Running as a receiver
        //		set int32_t motor_driver_shared.desired_position
#ifdef DEBUG_OUTPUT
        printf("Runnign as a receiver...\n");
#endif

        while (1) {
            status = recvfrom(sockd, &(motor_driver_shared.desired_position), buf_len, 0, (struct sockaddr *) &cli_name, & addrlen);
            semGive(sem_motor_pwm_change);
#ifdef DEBUG_OUTPUT
            printf("received %i\n", motor_driver_shared.desired_position);
#endif
        }
        close(sockd);
    } else {
#ifdef DEBUG_OUTPUT
        printf("Runnign as a transmitter...\n");
#endif
        // Running as a transmitter
        //		transfer int32_t motor_driver_shared.desired_position
        srv_addr.sin_family = AF_INET;
        inet_aton(ip_address, &srv_addr.sin_addr);
        srv_addr.sin_port = htons(port);

        i = 0;
        while (1) {
            sendto(sockd, &(motor_driver_shared.position), buf_len, 0, (struct sockaddr *) &srv_addr, sizeof(srv_addr));
#ifdef DEBUG_OUTPUT
            printf("sent %i\n", motor_driver_shared.position);
#endif
            taskDelay(SERVER_SEND_DELAY);
        }
        close(sockd);
    }
    printf("Measurement finished\n");
}
