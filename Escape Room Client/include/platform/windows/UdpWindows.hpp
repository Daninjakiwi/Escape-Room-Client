#pragma once
#include <thread>

#include <interface/UdpConnection.hpp>

class UdpWindows : public _UdpConnection {
private:
	unsigned long long _socket;

	MessageCallback _callback;
	std::thread _message_thread;
	bool _is_running;
public:
	UdpWindows(const std::string& ip, int port);
	UdpWindows();
	~UdpWindows();

	void Send(const std::string& message);
	void ListenForMessages(MessageCallback callback);
	void StopMessages();
	void SetDestination(const std::string& ip, int port);
private:
	void ReadMessages();
};
