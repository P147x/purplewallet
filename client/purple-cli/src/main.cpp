#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "config.hpp"

int	main(int argc, char *argv[])
{
	Config config;
	termios oldt;
  	tcgetattr(STDIN_FILENO, &oldt);
  	termios newt = oldt;
  	newt.c_lflag &= ~ECHO;
  	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 	std::string s;
  	std::cout << "Enter password:";
  	getline(std::cin, s);
  	std::cout << std::endl;
	
	return 0;
}
