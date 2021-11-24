#include <config.h>

/*
 * udp_latency()
 *  : (char *) ip_address  -- IPv4 address of the target board for sending data to
                              `null` (`0` in Workbench) = run as listener
 *  : (int) port           -- port used for communication
 *  : (int) payload_size   -- size of the payload in Bytes
 *  : (int) messages_count -- number of messages to be sent/read
 *                            0 = INFINITE
 *
 *  Entry point function.
 *
 *  This function is used for measuring round-trip time of UDP messages.
 *  Depending on the arguments, the application is run as SENDER or LISTENER.
 *  In both versions the application starts with printing `Measurement started` to
 *  stdout and when it finishes it prints `Measurement finished`.
 *
 *  SENDER mode
 *  The application send packets of `payload_size` size to board with
 *  IP address `ip_address` using port `port`. After a packet is sent, it waits
 *  for response. Time between sending and receiving packet is measured, divided
 *  by two and stored in a histogram. After `messages_count` packets are sent and
 *  received, the histogram is printed out and the application finishes.
 *
 *  LISTENER mode
 *  The application is expecting packets of size at most `payload_size` on port `port`.
 *  When a packet is received, it is sent back to the sender.
 *
 *  Histogram data format:
 *   1) First row is the x-axis of the histogram, values in microseconds, ordered as a
 *      strictly increasing sequence.
 *   2) Second row contains the counts of packets with single-trip time corresponding
 *      value from the first row. The sequence has the same number of elements as the
 *      first row.
 *  Printed out values are delimited only by commas ','. Rows end with '\n'.
 *
 *  Example:
 *      -> udp_latency(0, 2227, 1400, 5)
 *      Measurement started
 *      Measurement finished
 *
 *      -> udp_latency("10.35.1.2", 2227, 4, 5)
 *      Measurement started
 *      0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
 *      0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,2
 *      Measurement finished
 */
void udp_latency(char * ip_address, int port, int payload_size, int messages_count) {
	// to measure with high resolution:
	// unsigned t = sysTimestamp();
	
}

void listener(uint16_t port){
  int sockd;
  struct sockaddr_in my_name, cli_name;
  char buf[MAX_BUF];
  int status;
  int addrlen;

  /* Create a UDP socket */
  sockd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockd == -1)
  {
    perror("Socket creation error");
    exit(1);
  }

  /* Configure server address */
  my_name.sin_family = AF_INET;
  my_name.sin_addr.s_addr = INADDR_ANY;
  my_name.sin_port = htons(port);

  status = bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name));

  addrlen = sizeof(cli_name);
  status = recvfrom(sockd, buf, MAX_BUF, 0,
      (struct sockaddr*)&cli_name, &addrlen);

  printf("%s", buf);
  strcat(buf, "OK!\n");

  status = sendto(sockd, buf, strlen(buf)+1, 0,
      (struct sockaddr*)&cli_name, sizeof(cli_name));

  close(sockd);
}

void transmitter(const char *address, uint16_t port) {
  int sockd;
  struct sockaddr_in my_addr, srv_addr;
  char buf[MAX_BUF];
  int count;
  int addrlen;

  /* Create a UDP socket */
  sockd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockd == -1)
  {
    perror("Socket creation error");
    exit(1);
  }

  /* Configure client address */
  my_addr.sin_family = AF_INET;
  my_addr.sin_addr.s_addr = INADDR_ANY;
  my_addr.sin_port = 0;

  bind(sockd, (struct sockaddr*)&my_addr, sizeof(my_addr));

  strcpy(buf, "Hello world\n");

  /* Set server address */
  srv_addr.sin_family = AF_INET;
  inet_aton(addrests, &srv_addr.sin_addr);
  srv_addr.sin_port = htons(port);

  sendto(sockd, buf, strlen(buf)+1, 0,
      (struct sockaddr*)&srv_addr, sizeof(srv_addr));

  addrlen = sizeof(srv_addr);
  count = recvfrom(sockd, buf, MAX_BUF, 0,
      (struct sockaddr*)&srv_addr, &addrlen);
  write(1, buf, count);

  close(sockd);
}
