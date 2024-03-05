#ifndef SocketClusterClient_h
#define SocketClusterClient_h

#include <functional>
#include <string>
#include <list>
#include <memory>

#include "json/json.h"
#include "Connection.h"

typedef std::function<void(std::string event, const Json::Value& data)> Callback;

class SocketClusterClient {
public:
    SocketClusterClient();
    ~SocketClusterClient(); 

    std::shared_ptr<Connection> createConnection(const std::string& url, int port); 
    std::list<std::shared_ptr<Connection>>& getConnections(); 

private:
    std::list<std::shared_ptr<Connection>> m_connections;
};

#endif /* SocketClusterClient_h */
