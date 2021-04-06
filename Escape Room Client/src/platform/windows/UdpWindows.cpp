#include <iostream>
#include <platform/windows/UdpWindows.hpp>
#include <algorithm>


#ifdef BUILD_WINDOWS

#include <WS2tcpip.h>

void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

UdpWindows::UdpWindows(const std::string& ip, int port) : _UdpConnection(ip, port), _socket(0), _callback(nullptr),_is_running(false) {
	_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int timeout = 50;
	setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
}

UdpWindows::UdpWindows() : _UdpConnection("", 0), _socket(0), _callback(nullptr), _is_running(false) {

}

void UdpWindows::SetDestination(const std::string& ip, int port) {
	_ip = ip;
	_port = port;
}

UdpWindows::~UdpWindows() {
	StopMessages();
	closesocket(_socket);
}

void UdpWindows::Send(const std::string& message) {
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(_port);

	inet_pton(AF_INET, _ip.c_str(), &server.sin_addr);

	std::string encoded = message;

	findAndReplaceAll(encoded, "\"", "%22");
	findAndReplaceAll(encoded, "{", "%7B");
	findAndReplaceAll(encoded, "}", "%7D");

	sendto(_socket, encoded.c_str(), encoded.size() + 1, 0, (sockaddr*)&server, sizeof(server));
}

void UdpWindows::ListenForMessages(MessageCallback callback) {
	_callback = callback;
	_is_running = true;
	_message_thread = std::thread(&UdpWindows::ReadMessages, this);
}

void UdpWindows::StopMessages() {
	if (_is_running) {
		_is_running = false;
		_message_thread.join();
	}
}

void UdpWindows::ReadMessages() {
	const int buffer_size = 256;

	sockaddr_in client;

	int client_size = sizeof(client);

	ZeroMemory(&client, client_size);

	char buffer[buffer_size];

	while (_is_running) {
		ZeroMemory(buffer, buffer_size);

		int success = recvfrom(_socket, buffer, buffer_size, 0, (sockaddr*)&client, &client_size);

		if (success > 0) {
			if (_callback != nullptr && _is_running) {
				std::string out;
				out.resize(buffer_size);

				memcpy(out.data(), buffer, buffer_size);

				_callback(out);
			}
		}
	}
}

#endif