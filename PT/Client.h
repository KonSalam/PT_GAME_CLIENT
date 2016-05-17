#ifndef Client_H
#define Client_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include "Tank.h"

using namespace std;
#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024            
#define IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT "2556"
const int MAX_CLIENTS = 4;

struct client_type
{
	SOCKET socket;
	int id;
	char received_message[DEFAULT_BUFLEN];
};

class Client
{
private:
	WSAData wsa_data;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	string sent_message = "";
	client_type client;
	int iResult = 0;
	string message;

	int run();

public:
	int init();
	int connecting();

};
#endif