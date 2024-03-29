#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <future>

#include "SocketClusterClient.h"
#include "Connection.h"


int connect_to_socket() {
     SocketClusterClient *c = new SocketClusterClient();
     std::string url = "ws://127.0.0.1";
     std::shared_ptr<Connection> con = c->createConnection(url, 8000);

     std::promise<ConnectionResult> connection_promise;
     auto connection_future = connection_promise.get_future();

    return 0;
}

TEST_CASE("connect_socket")
{
    REQUIRE(connect_to_socket() == 0);
}

int add_ints(int a, int b)
{
    return(a + b);
}

TEST_CASE("add_ints")
{
    REQUIRE(add_ints(5, 10) == 15);
}

TEST_CASE("Trivial test", "[pass]") {
    REQUIRE(1 == 1);
}

