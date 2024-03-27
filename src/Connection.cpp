#include "Connection.h"
#include <websocketpp/config/asio_no_tls_client.hpp> // For error codes
#include <iostream> // Temporary, for basic error reporting

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

Connection::Connection(const std::string& url, int port) : m_url(url), m_port(port) 
{
    // Initialize client endpoint (more setup might be needed later)
    m_client = new Client();
    m_client->init_asio();
    m_client->set_access_channels(websocketpp::log::alevel::all); // Optional: suppress logs
}

Connection::~Connection() {
    // Ensure clean disconnect here (if connected)
}

bool Connection::connect() {
    // 1. Create a connection URI
    std::cout << "Url: " << m_url << std::endl;
    std::string uri = m_url + ":" + std::to_string(m_port);
    std::cout << "Uri: " << uri << std::endl;

    ErrorCode ec;
    ConnectionPtr con = m_client->get_connection(uri, ec);
    
    if (ec) {
        std::cout << "Could not create connection: " << ec.message() << std::endl;
        return false;
    }
    
    m_client->set_open_handler(bind(&Connection::onWebSocketOpen, this, _1));
    m_client->set_close_handler(bind(&Connection::onWebSocketClose, this, _1));
    m_client->set_message_handler(bind(&Connection::onWebSocketMessage, this, _1, _2)); 

    // 3. Start the connection
    m_client->connect(con);

    // 4. Start the ASIO io_service run loop
    m_client->run();

    return true; // Replace with proper success/failure logic
}

void Connection::close() {
    // Add logic to gracefully close the WebSocket connection
}

void Connection::send(const std::string& data) {
     // Use m_client to send data over the WebSocket connection
}

void Connection::onWebSocketOpen(ConnectionHDL hdl) {
     m_connectionHdl = hdl;
     std::cout << "Connection established." << std::endl;
}

void Connection::onWebSocketClose(ConnectionHDL hdl) {
    std::cout << "Connection closed." << std::endl;
}

void Connection::onWebSocketMessage(ConnectionHDL hdl, Client::message_ptr msg) {
    std::cout << "Incoming message." << std::endl;
     // ... Process incoming message (payload is in msg->get_payload()) 
} 
