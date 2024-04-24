#include "SFML_Socket.hpp"

// the following is not working properly, dont use:

/*
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
*/

// the following is an updated version using server/client connection, need to fix bugs and finalize a connection:

bool connection()
{
	bool success = false;
	TcpSocket socket;
	TcpListener listener;
	listener.listen(50000);

	// server
	if (listener.listen(50000) != socket.Done)
	{
		cout << "Error connecting to port" << endl;
		return false;
	}

	if (listener.accept(socket) != socket.Done)
	{
		cout << "Error accepting to socket" << endl;
		return false;
	}

	string message = "Server says Hello!";
	if (socket.send(message.c_str(), message.size() + 1) != socket.Done)
	{
		cout << "Error sending message from Server" << endl;
		return false;
	}

	//client
	TcpSocket csocket;
	if (socket.connect("10.109.142.239", 50000) != socket.Done)
	{
		cout << "Error connecting to IP" << endl;
		return false;
	}

	char buffer[500];
	size_t recieved;
	if (socket.receive(buffer, sizeof(buffer), recieved) != socket.Done)
	{
		cout << "Error recieving message" << endl;
		return false;
	}

	cout << "Message from server: " << buffer << endl;
	cout << "inside the Connection() function" << endl;

	return success;
}
