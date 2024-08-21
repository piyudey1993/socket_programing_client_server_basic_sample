#include<iostream>
#include<Winsock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
#include<vector>
using namespace std;

// Link with ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

// Function to initialize Winsock
bool Initialize()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}
void interactWithClientRecv(SOCKET clientSocket,vector<SOCKET> clients)
{
    //send recv
   
    char buffer[4096];
    while (1)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            string message(buffer, bytesReceived);
            cout << "Message from client: " << message << endl;
            for (auto itr_client : clients)
            {
                if(itr_client!= clientSocket)
                send(itr_client, message.c_str(), message.length(), 0);
            }
        }
        else if (bytesReceived == 0)
        {
            cout << "Connection closed by client" << endl;
            break;
        }
        else
        {
            cout << "Receive failed" << endl;
            break;
        }
        
    }
    auto it = find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end())
    {
        clients.erase(it);
    }
}

void interactWithClientSend(SOCKET S)
{
    string name, mesg;
    cout << "enter your chat name" << endl;
    cin >> name;
    while (1)
    {
        cout << "type_your message : : ";
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
int main()
{
    // Initialize Winsock
    if (!Initialize())
    {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    // Create a socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    // Create address structure
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(12345);
    int port = 12345;
    
    
    // Convert the IP address (0.0.0.0)
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1)
    {
        cout << "Setting address structure failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Bind the socket
    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "Binding failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Listen on the socket
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listening failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    cout << "Server has started listening on port " << port << endl;
    vector<SOCKET> client_vector;
    // Accept a client socket
    while (1)
    {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET)
        {
            cout << "Accepting client socket failed" << endl;
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }
        client_vector.push_back(clientSocket);
        thread th1(interactWithClientRecv, clientSocket,std::ref(client_vector));
        thread th2(interactWithClientSend, clientSocket);
        // Receive data from client
        th1.join();
        th2.join();
    }

    // Close sockets
  //  closesocket(clientSocket);
    closesocket(listenSocket);
    cout << "Server closed" << endl;
   
    // Cleanup Winsock
    WSACleanup();

    return 0;
}

