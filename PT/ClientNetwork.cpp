#include "Client.h"

void updateGraphic(Graphic graphic, Tank tanks[4])
{
	int dTank[12];
	dTank[0] = tanks[0].getX();
	dTank[1] = tanks[0].getY();
	dTank[2] = tanks[0].getCourse();

	dTank[3] = tanks[1].getX();
	dTank[4] = tanks[1].getY();
	dTank[5] = tanks[1].getCourse();

	dTank[6] = tanks[2].getX();
	dTank[7] = tanks[2].getY();
	dTank[8] = tanks[2].getCourse();

	dTank[9] = tanks[3].getX();
	dTank[10] = tanks[3].getY();
	dTank[11] = tanks[3].getCourse();
	graphic.updatePosition(dTank);
}

void setTanks(string msg, Tank tanks[], Graphic graphic)
{
	std::stringstream stream(msg);
	int p, x, y, c;// id, x, y, course
	stream >> p >> x >> y >> c;

	tanks[p].setX(x);
	tanks[p].setY(y);
	tanks[p].setCourse(c);
	cout << "Player #" << p << " | " << tanks[p].getX() << " " << tanks[p].getY() << " course: " << tanks[p].getCourse() << endl;
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