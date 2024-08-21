#include<iostream>
#include<winSock2.h>
#include<WS2tcpip.h>
#include<thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
/*
* initiaze win sock
* create sock
* connect to the server
* send and recive
* close the server
*/
bool initialize()
{
	WSADATA data;
	return( WSAStartup(MAKEWORD(2, 2), &data) == 0);
}

void sendMsg(SOCKET S)
{
	string name,mesg;
	cout << "enter your chat name" << endl;
	cin >> name;
	while (1)
	{
		cout << "type_your message : ";
		getline(cin, mesg);
		string msg = name + " : " + mesg;
		
		int bytesSent;
		bytesSent = send(S, msg.c_str(), msg.length(), 0);

		if (bytesSent == SOCKET_ERROR)
		{
			cout << "send failed " << endl;
		}
	}
	
	closesocket(S);
	WSACleanup();
}
void recvMsg(SOCKET S)
{
	cout << "Recv_msg" << endl;
	char buffer[4096];
	while (1)
	{
		int bytesReceived = recv(S, buffer, sizeof(buffer), 0);
		
		if (bytesReceived > 0)
		{
			string message(buffer, bytesReceived);
			cout << "Message from client: " << message << endl;
			
		}
		else if (bytesReceived == 0)
		{
			cout << "Connection closed by client" << endl;
			break;
		}
		else
		{
			cout << bytesReceived<< "Receive failed" << endl;
			break;
		}

	}
}

int main()
{
	if (!(initialize()))
	{
		cout << "socket initialization is failed" << endl;
	}
	SOCKET S;
	S = socket(AF_INET, SOCK_STREAM, 0);
	if (S == INVALID_SOCKET)
	{
		cout << " invalid socket created " << endl;
		return 1;
	}
	cout << "it is initialized" << endl;
	int port = 12345;
	string serveraddress = "127.0.0.1";
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	//serveraddr.sin_addr
	if (inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr)) != 1)
	{
		cout << "Setting address structure failed" << endl;

	}
	if (connect(S, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout << "not able to connect the server" << endl;
		closesocket(S);
		WSACleanup();
		return 1;
	}
	
	cout << "suceesfully connect the server" << endl;
	while (1)
	{
		//thread senderThread(sendMsg, S);
		thread reciverThread(recvMsg, S);

		//senderThread.join();
		reciverThread.join();
	}
	//senderThread.join();
	//reciverThread.join();
	WSACleanup();
	cout << "client socket close" << endl;
}