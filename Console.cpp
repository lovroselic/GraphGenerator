/*
	v 1.1
*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include "Console.h"

void printArray(int* data, int length) {
	int* p = data;
	for (int x = 0; x < length; x++) {
		std::cout << p << " --> cell[" << x << "]\t= " << *p << std::endl;
		p++;
	}
	std::cout << std::endl;
}
