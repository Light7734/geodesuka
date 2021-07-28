#include <geodesuka/core/io/socket_t.h>

#include <string.h>

#include <iostream>

#include <vector>
#include <list>
//#include <string>

#include <thread>
#include <mutex>

// System dependent Libraries
#if defined(_WIN32) || defined(_WIN64)
 #include <windows.h>
 #include <winsock2.h>
 #include <ws2tcpip.h>
 // Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
 #pragma comment (lib, "Ws2_32.lib")
 #pragma comment (lib, "Mswsock.lib")
 #pragma comment (lib, "AdvApi32.lib")
#elif defined(__APPLE__) || defined(MACOSX)
 // Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
 // Linux
 #include <unistd.h> 
 #include <sys/socket.h> 
 #include <netinet/in.h> 
 #include <arpa/inet.h>
#endif

void incoming_message(socket_t* Socket) {
	while(true) {
		udpMessage Msg;
		sockaddr_in Source;
		socklen_t SourceSize{sizeof(struct sockaddr_in)};
		//memset(Msg.chMsg, 0, sizeof(Msg.chMsg));
		int n = recvfrom(Socket->ID, (char*)&Msg, sizeof(Msg), 0, (sockaddr*)&Source, &SourceSize);
		Socket->Mutex.lock();
		bool TestExit = Socket->ExitThread;
		Socket->Mutex.unlock();
		if (TestExit) {
			break;
		}
		else if (n < 0) {
			continue;
		}
		else {
			std::cout << "Message Received: " << Msg.chMsg << std::endl;
			if (Msg.nVersion != 1) continue;
			switch (Msg.nType) {
			case 0:
				// the composite message is immediately cleared and anything in the 
				// chMsg buffer is ignored.
				break;
			case 1:
				// the composite message is immediately cleared and the message in chMsg 
				// is used as the start of a new composite message
				break;
			case 2:
				// the message in chMsg is added to the composite message based on its
				// lSeqNum
				break;
			case 3:
				// the server immediately sends to all clients the current composite message
				// and clears out the composite message.
				break;
			case 4:
				// indicates this is a composite message.
				break;
			}
			//Socket->addMessage(Msg);
			//Socket->addSource(Source);
		}
	}
}

/////////////////////////////////////////////////
// Cross-platform socket initialization
int socket_t::initialize() {
#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	WSAData Data;
	WORD dllVersion = MAKEWORD(2, 2);
	return WSAStartup(dllVersion, &Data);
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
	return 0;
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	return 0;
#endif
}

/////////////////////////////////////////////////
// Cross-platform socket termination
int socket_t::terminate() {
#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	return WSACleanup();
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
	return 0;
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	return 0;
#endif
}

//socket_t::socket_t(unsigned short aPortNumber) {
//	*this = socket_t(NULL, aPortNumber);
//}

socket_t::socket_t(const char* aIP, unsigned short aPortNumber) {
	this->IP = aIP;
	this->PortNumber = aPortNumber;

	// Creates Socket
	this->ID = socket(AF_INET, SOCK_DGRAM, 0/*IPPROTO_UDP*/);

	int ErrorCode = 0;
	int Timeout = 1;
	// Defines Timeout.
#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	DWORD tv = Timeout * 1000;
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	struct timeval tv;
	tv.tv_sec = Timeout;
	tv.tv_usec = 0;
#endif
	setsockopt(this->ID, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	int Option = 1;
	ErrorCode = setsockopt(this->ID, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &Option, sizeof(Option));
#endif

	// Creates Socket Address Info.
	//struct sockaddr_in Address;
	//SOCKADDR_IN Address;
	//ZeroMemory(&Address, sizeof(Address));
	memset(&Address, 0, sizeof(Address));
	Address.sin_family = AF_INET;
	if (this->IP != NULL) {
#if defined(_WIN32) || defined(_WIN64)
		// Windows OS
		Address.sin_addr.S_un.S_addr = inet_addr(this->IP);
#elif defined(__APPLE__) || defined(MACOSX)
		// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
		// Linux OS
		inet_pton(AF_INET, this->IP, &Address.sin_addr);
#endif
	}
	else {
#if defined(_WIN32) || defined(_WIN64)
		// Windows OS
		Address.sin_addr.S_un.S_addr = INADDR_ANY;
#elif defined(__APPLE__) || defined(MACOSX)
		// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
		// Linux OS
		Address.sin_addr.s_addr = INADDR_ANY;
#endif
	}
	Address.sin_port = htons(this->PortNumber);

	// Binds Socket
	if (this->IP != NULL) {
		// Outgoing connection
		connect(this->ID, (const sockaddr*)&Address, sizeof(Address));
	}
	else {
		// Binds to 
		bind(this->ID, (const sockaddr*)&Address, sizeof(Address));
	}


	this->ExitThread = false;
	this->Thread = std::thread(incoming_message, this);
}

socket_t::~socket_t() {
	//std::cout << "Desctructor Called!" << std::endl;
	this->Mutex.lock();
	this->ExitThread = true;
	//std::cout << "ExitThread: " << this->ExitThread << std::endl;
	this->Mutex.unlock();
	this->Thread.join();

	this->IP = NULL;
#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	closesocket(this->ID);
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	close(this->ID);
#endif
}

//int socket_t::msend(const char* aBuffer, int aBufferSize, int aFlags) {
//	return sendto(this->ID, aBuffer, aBufferSize, aFlags, (const sockaddr*)&this->Address, sizeof(this->Address));
//}
//
//int socket_t::mrecv(char* aBuffer, int aBufferSize, int aFlags) {
//	return recv(this->ID, aBuffer, aBufferSize, aFlags);
//}

void socket_t::addMessage(const udpMessage& inMsg) {
	this->Mutex.lock();
	this->MessageList.push_back(inMsg);
	this->Mutex.unlock();
}

void socket_t::addSource(const sockaddr_in& from) {
	this->Mutex.lock();
	this->AddressList.push_back(from);
	this->Mutex.unlock();
}

void socket_t::clearMessageList() {
	this->Mutex.lock();
	this->MessageList.clear();
	this->Mutex.unlock();
}

void socket_t::displayMessageList() {
	std::list<udpMessage>::iterator it;
	for (it = this->MessageList.begin(); it != this->MessageList.end(); ++it) {
		std::cout << it->chMsg;// << std::endl;
	}
}

bool socket_t::getNextMessage(udpMessage& msg) {
	return false;
}

void socket_t::sendMessage(const std::string& strTo, unsigned short usPortNum, const udpMessage& msg) {
	sockaddr_in Target;
	Target.sin_family = AF_INET;
	


	Target.sin_port = htons(usPortNum);
	sendto(this->ID, (const char*)&msg, sizeof(msg), 0, (const sockaddr*)&Address, sizeof(Address));

#if defined(_WIN32) || defined(_WIN64)
	// Windows OS
	Target.sin_addr.S_un.S_addr = inet_addr(strTo.c_str());
	//Address.sin_addr.S_un.S_addr = inet_addr(this->IP);
#elif defined(__APPLE__) || defined(MACOSX)
	// Garbage OS
#elif defined(__linux__) && !defined(__ANDROID__)
	// Linux OS
	inet_pton(AF_INET, strTo.c_str(), &Address.sin_addr);
	//inet_pton(AF_INET, this->IP, &Address.sin_addr)
#endif

}
