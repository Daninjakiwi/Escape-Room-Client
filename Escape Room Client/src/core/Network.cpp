#include <core/Network.hpp>
#include <curl/curl.h>

size_t WriteString(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string EncodeData(CURL* handler, std::unordered_map<std::string, std::string>& data) {
	std::string encoded = "";

	for (auto it = data.begin(); it != data.end(); ++it) {
		encoded += it->first + "=";
		char* d = curl_easy_escape(handler, it->second.c_str(), (int)it->second.length());
		encoded += d;
		encoded += "&";
		curl_free(d);
	}

	return encoded;
}

void* Network::curl_handle = nullptr;

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

	curl_easy_init();

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();

	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteString);

	return true;
}

void Network::Terminate() {
	WSACleanup();
	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();
}

std::string Network::HttpRequest(const std::string& address) {
	std::unordered_map<std::string, std::string> temp;

	return HttpRequest(address, RequestType::GET, temp);
}

std::string Network::HttpRequest(const std::string& address, RequestType type, std::unordered_map<std::string, std::string>& data) {
	std::string result;
	std::string encoded = EncodeData(curl_handle, data);

	if (type == RequestType::GET) {
		curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);
		curl_easy_setopt(curl_handle, CURLOPT_URL, (address + "?" + encoded).c_str());
	}
	else if (type == RequestType::POST) {
		curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

		curl_easy_setopt(curl_handle, CURLOPT_URL, address.c_str());
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, encoded.c_str());
	}
	
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &result);

	curl_easy_perform(curl_handle);

	return result;
}

#endif

#ifdef BUILD_LINUX

bool Network::Initialise() {
	return true;
}

void Network::Terminate() {

}

#endif