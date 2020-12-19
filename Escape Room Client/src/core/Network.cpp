#include <core/Network.hpp>

UdpConnection Network::UdpConnect(const std::string& ip, int port) {
	return UdpConnection(ip, port);
}

#ifdef BUILD_WINDOWS
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment (lib, "ws2_32.lib")

bool Network::Initialise() {
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version, &data);

	if (wsOk != 0) {
		return false;
	}
	return true;
}

void Network::Terminate() {
	WSACleanup();
}

#endif

#ifdef BUILD_LINUX

bool Network::Initialise() {
	return true;
}

void Network::Terminate() {

}

#endif