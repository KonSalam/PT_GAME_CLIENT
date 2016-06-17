#include "Client.h"
#include "Graphic.h"

Client::Client()
{
	tanks[0] = Tank(0, 0, 1);
	tanks[1] = Tank(0, 500, 2);
	tanks[2] = Tank(500, 0, 1);
	tanks[3] = Tank(500, 500, 2);
	sent_message = "";
	iResult = 0;
}

int Client::init()
{
	cout << "Starting Client...\n";
	client = { INVALID_SOCKET, -1, "" };

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
	cout << "Player #" << id << " connected\n\n";
	run();
}

int Client::run()
{
	bool czySend = false;
	thread graphic_thread(&Graphic::init, graphic, tanks);
	
	if (message != "Server is full")
	{
		client.id = atoi(client.received_message);
		thread my_thread(process_client, client, tanks, graphic);

		while (1)
		{
			int a = _getch();
			if (a == 0 || a == 0xE0) a = _getch();

			if (a == 72)
				sent_message = to_string(a);
			else if (a == 80)
				sent_message = to_string(a);
			else if (a == 75)
				sent_message = to_string(a);
			else if (a == 77)
				sent_message = to_string(a);
			else if (a == 115)
				sent_message = to_string(a);
			else
				czySend = false;

			if (czySend == true && tanks[client.id].getLife() != 0)
			{
				iResult = send(client.socket, sent_message.c_str(), strlen(sent_message.c_str()), 0);
				if (iResult <= 0)
				{
					cout << "send() failed: " << WSAGetLastError() << endl;
					break;
				}
			}
			czySend = true;
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