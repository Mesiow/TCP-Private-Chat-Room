#include <iostream>
#include "App.h"


char getHost()
{
	char c;
	std::cout << "[S]erver or [C]lient: ";
	std::cin >> c;

	return c;
}

int main()
{
	char op = getHost();
	const unsigned short port = 54000;

	App app;
	app.init(op, port);
	app.run();

	return 0;
}