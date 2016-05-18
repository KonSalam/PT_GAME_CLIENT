#include "Client.h"
using namespace std;

int process_client(client_type &new_client);

Client::Client()
{
	Tank tanks[MAX_CLIENTS] = { Tank(0, 0), Tank(0, 500), Tank(500, 0), Tank(500, 500) };
	sent_message = "";
	iResult = 0;
}

int Client::init()
{
	cout << "Starting Client...\n";
	client = { INVALID_SOCKET, -1, "" };

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0) {
		cout << "WSAStartup() failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

int Client::connecting()
{
	cout << "Connecting...\n";
	iResult = getaddrinfo(static_cast<LPCTSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo() failed with error: " << iResult << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		client.socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (client.socket == INVALID_SOCKET) {
			cout << "socket() failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			system("pause");
			return 1;
		}

		// Connect to server.
		iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(client.socket);
			client.socket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);
	if (client.socket == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	cout << "Successfully Connected" << endl;
	//Obtain id from server for this client;
	recv(client.socket, client.received_message, DEFAULT_BUFLEN, 0);
	message = client.received_message;

	//set player play
	int id = atoi(client.received_message);
	tanks[id].setPlay();
	cout << id << " " << tanks[id].getX() << tanks[id].getPlay() << endl;

	run();
}

int Client::run()
{
	if (message != "Server is full")
	{
		client.id = atoi(client.received_message);
		thread my_thread(process_client, client);
		Tank tanks[MAX_CLIENTS] = { Tank(0, 0), Tank(0, 500), Tank(500, 0), Tank(500, 500) };

		while (1)
		{
			int a = _getch();
			if (a == 0 || a == 0xE0) a = _getch();

			if (a == 27) 
				break;
			else if (a == 72)
				sent_message = to_string(a);
			else if (a == 80)
				sent_message = to_string(a);
			else if (a == 75)
				sent_message = to_string(a);
			else if (a == 77)
				sent_message = to_string(a);

			iResult = send(client.socket, sent_message.c_str(), strlen(sent_message.c_str()), 0);


			if (iResult <= 0)
			{
				cout << "send() failed: " << WSAGetLastError() << endl;
				break;
			}
		}

		//Shutdown the connection since no more data will be sent
		my_thread.detach();
	}
	else
		cout << client.received_message << endl;

	cout << "Shutting down socket..." << endl;
	iResult = shutdown(client.socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown() failed with error: " << WSAGetLastError() << endl;
		closesocket(client.socket);
		WSACleanup();
		system("pause");
		return 1;
	}

	closesocket(client.socket);
	WSACleanup();
}

int process_client(client_type &new_client)
{
	while (1)
	{
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);

		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);


			if (iResult != SOCKET_ERROR)
			{

				cout << new_client.received_message << endl;
				if (new_client.received_message[0] == 'g')
				{
					//tanks[(int)new_client.received_message[3]].setY(tanks[new_client.received_message[3]].getY() - 5);
				}
				else if (new_client.received_message[0] == 'd')
				{
					//tanks[(int)new_client.received_message[3]].setY(tanks[new_client.received_message[3]].getY() + 5);
				}
				else if (new_client.received_message[0] == 'l')
				{
					//tanks[(int)new_client.received_message[3]].setX(tanks[new_client.received_message[3]].getX() - 5);
				}
				else if (new_client.received_message[0] == 'p')
				{
					//tanks[(int)new_client.received_message[3]].setX(tanks[new_client.received_message[3]].getX() + 5);
				}

				//cout << tanks[(int)new_client.received_message[3]].getX() << " " << tanks[(int)new_client.received_message[3]].getY() << endl;
				//funckja odswiezania gui
			}
			else
			{
				cout << "recv() failed: " << WSAGetLastError() << endl;
				break;
			}
		}
	}

	if (WSAGetLastError() == WSAECONNRESET)
		cout << "The server has disconnected" << endl;

	return 0;
}