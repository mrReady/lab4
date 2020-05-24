#include <iostream>
#include <fstream>
#include"Flow.h"
int main(int argc, char* argv[])
{
	try {
		ifstream input("input.txt");
		Flow flow(input);
		std::cout <<"Max flow for the input graph is: "<< flow.max_flow();
	}
	catch (exception& ex) {
		std::cout << ex.what();
	}
	return 0;
}