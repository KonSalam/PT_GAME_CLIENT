#include "Client.h"

void setTanks(string msg, Tank tanks[])
{
	std::stringstream stream(msg);
	int p, x, y, c, s;// id, x, y, course, czyStrzal 0-ruch 1-strzal 2-trafiony
	stream >> p >> x >> y >> c >> s;

	if (s == 0) {
		tanks[p].setX(x);
		tanks[p].setY(y);
		tanks[p].setCourse(c);
		cout << "Player #" << p << " | " << tanks[p].getX() << " " << tanks[p].getY() << " course: " << tanks[p].getCourse() << endl;
	}
	else if (s == 1) {
		tanks[p].setX(x);
		tanks[p].setY(y);
		tanks[p].setCourse(c);
		cout << "Player Shoot #" << p << " | " << tanks[p].getX() << " " << tanks[p].getY() << " course: " << tanks[p].getCourse() << endl;
		//Grafika od strzelania 
	}
	else if (s == 2) {
		cout << "Player Trafiony #" << p << " | " << x << " " << y << " course: " << c << endl;
		tanks[p].setLife();
	}
}

int process_client(client_type &new_client, Tank tanks[])
{
	while (1)
	{
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);
		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);
			if (iResult != SOCKET_ERROR)
			{
				setTanks(new_client.received_message, tanks);
				cout << endl;
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