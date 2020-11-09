#include "GreeterClient.h"
#include "signal.h"


inline void handler(int sig) {
    Kama::GreeterClient::getInstance().stopGreeter();
}

int main(int argc, const char** argv) {
    signal(SIGTERM, handler);
    signal(SIGINT, handler);

    std::string client_name{ "client_name" };
    if (argc >= 2) {
        client_name = argv[1];    
    }

    std::string server_address{ "localhost:6000" };
    if (argc >= 3) {
        server_address = argv[2];
    }

    try {
        if (!Kama::GreeterClient::getInstance().init(client_name, server_address)) {
            return 1;
        }
        Kama::GreeterClient::getInstance().runGreeter();
    }
    catch (std::exception& e) {
        return 1;
    }

    return 0;
}