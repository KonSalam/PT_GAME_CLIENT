#ifndef Client_H
#define Client_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include <sstream>
#include "Tank.h"
#include "Graphic.h"

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
	client_type client;
	Graphic graphic;
	Tank tanks[MAX_CLIENTS];
	string sent_message;
	string message;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	int iResult;
	int run();


public:
	Client();
	int init();
	int connecting();
};
#endif