#pragma once
#ifndef SOCKET_T_H
#define SOCKET_T_H

#include <vector>
#include <list>
//#include <string>

#include <thread>
#include <mutex>

// System dependent Libraries
#if defined(_WIN32) || defined(_WIN64)
 #define WIN32_LEAN_AND_MEAN
 #define _WINSOCK_DEPRECATED_NO_WARNINGS
 #include <windows.h>
 #include <winsock2.h>
 #include <ws2tcpip.h>
#elif defined(__APPLE__) || defined(MACOSX)
 // Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
 // Linux
 #include <unistd.h> 
 #include <sys/socket.h> 
 #include <netinet/in.h> 
 #include <arpa/inet.h>
#endif

struct udpMessage
{
	unsigned short nVersion;  // htons()
	unsigned short nType;     // htons()
	unsigned short nMsgLen;   // htons()
	unsigned long lSeqNum;    // htonl()
	char chMsg[1000];
};

/*
* this file is an old file type from another project from school. It needs to 
* be repurposed for more general use. It was already written for windows and
* linux.
*/

class socket_t {
public:

	static int initialize();
	static int terminate();

	socket_t() = delete;
	// This but binds to local ip.
	//socket_t(unsigned short aPortNumber);
	// Pass null for binding, Pass IP for connection to.
	socket_t(const char* aIP, unsigned short aPortNumber);
	~socket_t();

	//int msend(const char* aBuffer, int aBufferSize, int aFlags);
	//int mrecv(char* aBuffer, int aBufferSize, int aFlags);

	void addMessage(const udpMessage& inMsg); // Add msg to the list
	void addSource(const sockaddr_in& from); // Add source to the list
	void clearMessageList();
	void displayMessageList();

	bool getNextMessage(udpMessage& msg);
	void sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg);

//private:

	const char* IP;
	unsigned short PortNumber;

	// Platform Dependent Garbage
#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	SOCKET ID;
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	int ID;
#endif
	std::thread Thread;
	bool ExitThread;
	struct sockaddr_in Address;
	std::list<udpMessage> MessageList;
	std::vector<sockaddr_in> AddressList;
	std::mutex Mutex;


};

#endif // !SOCKET_T_H
