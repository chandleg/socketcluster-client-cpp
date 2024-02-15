//
//  SCClient.h
//
//  Created by Daniel Cloran on 11/2/21.
//

#ifndef SCClient_h
#define SCClient_h

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything" //ignore warnings in external libs

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "json-c/json.h"

// Callback and Subscription types
typedef std::function<void(std::string event, json_object *data)> socketCallback;
typedef std::tuple<std::string, socketCallback> subscription;




class SCClient
{
public:
    // SCClient(); Constructor avaiable to user (also make init socket connection) Singleton SCClient
    // SCSocket mySocket = SCClient.create_socket("host", "port")
    // create_socket(): takes host, port etc.
        // returns socket handle that allows control

    
    // SocketHandler
        // subscribe (possible Subscriber)
        // unsubscribe

        // publish

        // publishers
        // subscribers




    // Some public list of sockets / socket handlers

private:
    // void fail(beast::error_code ec, char const* what);
    // void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
    // void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);
    // void on_handshake(beast::error_code ec);
    // void on_write(beast::error_code ec, std::size_t bytes_transferred);
    // void on_read(beast::error_code ec, std::size_t bytes_transferred);
    // void on_close(beast::error_code ec);
};

#endif /* SCClient_h */