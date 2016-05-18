#ifndef Client_H
#define Client_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include "Tank.h"

using namespace std;
#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024            
#define IP_ADDRESS "127.0.0.1"
#define DEFAULT_PORT "2556"
const int MAX_CLIENTS = 4;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77

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
	string sent_message;
	client_type client;
	int iResult;
	string message;
	Tank tanks[MAX_CLIENTS];

private:
	int run();

public:
	Client();
	int init();
	int connecting();

};
#endif