#include <iostream>
#include "Client.h"
using namespace std;

int main(int argc, char *args[])
{
	Client client;
	client.init();
	client.connecting();	
	system("pause");
	return 0;
}