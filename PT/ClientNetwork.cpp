#include "Client.h"

void setTanks(string msg, Tank tanks[],Graphic graphic)
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
		tanks[p].setShooting(true);
	}
	else if (s == 2) {
		cout << "Player Trafiony #" << p << " | " << x << " " << y << " course: " << c << endl;
		tanks[p].setLife();
		if (tanks[p].getLife() == 0){
			tanks[p].setDead();
		}
	}
	else if (s == 3) {
		cout << "Player Zastrzelony/Rozlaczony #" << p << " | " << x << " " << y << " course: " << c << endl;
		tanks[p].setDead();
	}
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
				setTanks(new_client.received_message, tanks,graphic);
				cout << endl;
				if (tanks[new_client.id].getLife() == 0)
				{
					graphic.showMessage(false, "Niestety zostales 3 razy trafiony i przegrales");
				}

				if (tanks[new_client.id].getLife() != 0){
					bool win = true;
					for (int i = 0; i < 4; i++){
						if (i == new_client.id) continue;
						if (tanks[i].getLife() != 0){
							win = false;
							break;
						}
					}
					if (win == true){
						graphic.showMessage(true, "Wygrales caly turniej!! Gratulacje Graczu!");
					}
				}
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