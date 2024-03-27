#include "SocketClusterClient.h"
#include "Connection.h" 
#include <memory> // For smart pointers 
#include <iostream>

SocketClusterClient::SocketClusterClient() {
    std::cout << "Creating Client" << std::endl;
    // Initialization (if any)
}

SocketClusterClient::~SocketClusterClient() {
    // No explicit cleanup needed! Smart pointers handle deletion
}

std::shared_ptr<Connection> SocketClusterClient::createConnection(const std::string& url, int port) {
    auto connection = std::make_shared<Connection>(url, port);
    m_connections.push_back(connection);
    return connection;
}

std::list<std::shared_ptr<Connection>>& SocketClusterClient::getConnections() {
    return m_connections;
}