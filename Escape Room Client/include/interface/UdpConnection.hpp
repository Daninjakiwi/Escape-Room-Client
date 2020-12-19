#pragma once
#include <string>

typedef void (*MessageCallback)(const std::string& message);

class _UdpConnection {
protected:
	std::string _ip;
	int _port;
public:
	_UdpConnection(const std::string& ip, int port) : _ip(ip), _port(port) {};
	virtual ~_UdpConnection() {};

	virtual void Send(const std::string& message) {};
	virtual void ListenForMessages(MessageCallback callback) {};
	virtual void StopMessages() {};
};
