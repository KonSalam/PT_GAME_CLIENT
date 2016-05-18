#include <iostream>
#include "Client.h"
using namespace std;

int main()
{
	Client client;
	client.init();
	client.connecting();

	system("pause");
	return 0;
}