#pragma once

#ifdef BUILD_WINDOWS
#include <platform/windows/UdpWindows.hpp>
typedef UdpWindows UdpConnection;
#endif

#ifdef BUILD_LINUX
#include <platform/linux/UdpLinux.hpp>
typedef UdpLinux UdpConnection;
#endif



class Network {
public:
	static bool Initialise();
	static void Terminate();

	static UdpConnection UdpConnect(const std::string& ip, int port);
};
