/*#include<iostream>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
using namespace std;

#pragma(lib,"ws2_32.lib")

/*
* intialize winsock library
* create socket
* getip and port
* bind the ip/port
* listen the socket
* accept
* blocking call
* rec and send
* close
* clean up the win socket

bool Initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}
int main()
{

	if (!Initialize())
	{
		cout << "winsock iniliazation is failed" << endl;
		return 1;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "socket creation failsed" << endl;
		return 1;
	}
	//Create address structure
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(12345);
	int port = 12345;
	//convert the ip adrees (0.0.0.0 inside th 
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1)
	{
		cout << "setting address stucture failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//bind
	if (bind(listenSocket, reinterpret_cast<sockaddr*> (&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout << "BInding is falied" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "BInding is falied" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	cout << "server has started listening on port" << port << endl;

	SOCKET cllientSocket = accept(listenSocket, nullptr, nullptr);
	if (cllientSocket == INVALID_SOCKET)
	{
		cout << "socket is invalid" << endl;
	}
	char buffer[4096];
	int bytesRecived = recv(cllientSocket, buffer, sizeof(buffer), 0);

	string message(buffer, bytesRecived);
	cout << "message from clenst" << message << endl;

	closesocket(cllientSocket);
	closesocket(listenSocket);
	cout << "server closed" << endl;
	WSACleanup();
}
*/