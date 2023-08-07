#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Simulate sending a packet
void sender(int seq) {
    printf("SENDER: Sending packet with sequence number: %d\n", seq);
    sleep(1);  // Simulate transmission delay

    // Simulate acknowledgment
    int ack = rand() % 2;  // 0 for no acknowledgment, 1 for acknowledgment

    if (ack) {
        printf("SENDER: Received ACK for packet %d\n", seq);
    } else {
        printf("SENDER: Packet %d lost, retransmitting...\n", seq);
    }
}

// Simulate receiving a packet and sending acknowledgment
void receiver(int seq) {
    printf("RECEIVER: Received packet with sequence number: %d\n", seq);
    sleep(1);  // Simulate processing delay

    // Simulate sending acknowledgment
    int ack = rand() % 2;  // 0 for not sending ACK, 1 for sending ACK

    if (ack) {
        printf("RECEIVER: Sending ACK for packet %d\n", seq);
    } else {
        printf("RECEIVER: Not sending ACK for packet %d\n", seq);
    }
}

int main() {
    int totalPackets = 5;  // Total number of packets to send

    // Communication loop
    for (int seq = 0; seq < totalPackets; seq++) {
        sender(seq);   // Send packet
        receiver(seq); // Receive packet and send ACK
    }

    return 0;
}
