#ifndef Connection_h
#define Connection_h

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything" //ignore warnings in external libs

#include "websocketpp/client.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"

#include <string>
#include <functional>

typedef websocketpp::client<websocketpp::config::asio_client> Client;
typedef Client::connection_ptr ConnectionPtr;
typedef websocketpp::connection_hdl ConnectionHDL;
typedef websocketpp::lib::error_code ErrorCode; 

typedef websocketpp::config::asio_client::message_type::ptr MessagePtr;

enum class ConnectionResult {
    SUCCESS = 0,
    ERROR_TIMEOUT = -1,
    ERROR_UNKNOWN = -2,
    // ... add more specific error codes as needed
};

class Connection {
public:
    Connection(const std::string& url, int port);
    ~Connection();

    bool connect();

private:
    const std::string& m_url;
    int m_port;

    Client * m_client;
    ConnectionHDL m_connectionHdl;

    
    void close();
    void send(const std::string& data);
    void onWebSocketOpen(ConnectionHDL hdl);
    void onWebSocketClose(ConnectionHDL hdl);
    void onWebSocketMessage(ConnectionHDL hdl, Client::message_ptr msg);
};

#endif /* Connection_h */
