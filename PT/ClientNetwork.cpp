#include "Client.h"

void updateGraphic(Graphic graphic, Tank tanks[4])
{
	int dTank[8];
	dTank[0] = tanks[0].getX();
	dTank[1] = tanks[0].getY();

	dTank[2] = tanks[1].getX();
	dTank[3] = tanks[1].getY();

	dTank[4] = tanks[2].getX();
	dTank[5] = tanks[2].getY();

	dTank[6] = tanks[3].getX();
	dTank[7] = tanks[3].getY();
	graphic.update(dTank);
}

void setTanks(string msg, Tank tanks[], Graphic graphic)
{
	std::stringstream stream(msg);
	int p, x, y;
	stream >> p >> x >> y;

	tanks[p].setX(x);
	tanks[p].setY(y);
	cout << "Player #" << p << " | " << tanks[p].getX() << " " << tanks[p].getY() << endl;
	updateGraphic(graphic, tanks);
}

int process_client(client_type &new_client, Tank tanks[], Graphic graphic)
{
	while (1)
	{
		memset(new_client.received_message, 0, DEFAULT_BUFLEN);
		if (new_client.socket != 0)
		{
			int iResult = recv(new_client.socket, new_client.received_message, DEFAULT_BUFLEN, 0);
			if (iResult != SOCKET_ERROR)
			{
				setTanks(new_client.received_message, tanks, graphic);
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