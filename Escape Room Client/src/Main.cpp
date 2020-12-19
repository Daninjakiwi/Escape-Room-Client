#include <iostream>
#include <core/Network.hpp>

int main() {

	if (!Network::Initialise()) {
		return -1;
	}

	std::cin.get();

	Network::Terminate();
}