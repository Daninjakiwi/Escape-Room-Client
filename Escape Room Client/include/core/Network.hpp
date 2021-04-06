#pragma once
#include <unordered_map>

#ifdef BUILD_WINDOWS
#include <platform/windows/UdpWindows.hpp>
typedef UdpWindows UdpConnection;
#endif

#ifdef BUILD_LINUX
#include <platform/linux/UdpLinux.hpp>
typedef UdpLinux UdpConnection;
#endif

enum class RequestType {
	GET, POST
};

class Network {
private:
	static void* curl_handle;
public:
	static bool Initialise();
	static void Terminate();

	static std::string HttpRequest(const std::string& address);
	static std::string HttpRequest(const std::string& address, RequestType type, std::unordered_map<std::string, std::string>& data);

	static UdpConnection UdpConnect(const std::string& ip, int port);
};
