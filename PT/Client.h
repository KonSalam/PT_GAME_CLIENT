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

#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024            
#define IP_ADDRESS "192.168.1.102"
#define DEFAULT_PORT "2556"
using namespace std;
const int MAX_CLIENTS = 4;

struct client_type
{
	SOCKET socket;
	int id;
	char received_message[DEFAULT_BUFLEN];
};

void updateGraphic(Graphic graphic, Tank tanks[4]);
void setTanks(string msg, Tank tanks[], Graphic graphic);
int process_client(client_type &new_client, Tank tanks[]);

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