#include "SFML_Socket.hpp"

bool connection()
{
    bool success = false;

    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    char connectionType, mode;
    char buffer[200];
    size_t recieved;
    string text = "Connected to: ";

    cout << "Enter (s) for Server, Enter (c) for client: " << endl;
    cin >> connectionType;

    if (connectionType == 's')
    {
        TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
        text += "Server";
        socket.send(text.c_str(), text.length() + 1);
    }
    else if (connectionType == 'c')
    {
        socket.connect(ip, 2000);
        text += "Client";
    }

    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), recieved);
    cout << buffer << endl;
    system("pause");

    return success;
}

// code to test:

//TcpSocket csocket;
//if (socket.connect("10.109.142.239", 50000) != socket.Done)
//{
//	cout << "Error connecting to IP" << endl;
//	return false;
//}
//
//char buffer[500];
//size_t recieved;
//if (socket.receive(buffer, sizeof(buffer), recieved) != socket.Done)
//{
//	cout << "Error recieving message" << endl;
//	return false;
//}
//
//cout << "Message from server: " << buffer << endl;
//cout << "inside the Connection() function" << endl;
