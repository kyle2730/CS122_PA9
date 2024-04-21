#pragma once

#include "SFML_header-2.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using sf::TcpSocket;
using sf::TcpListener;
using sf::IpAddress;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::size_t;

bool connection();
// for use with the sockets, not perfect.
