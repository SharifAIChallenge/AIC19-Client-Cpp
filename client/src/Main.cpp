#include <cstdlib>
#include <ctime>

#include <iostream>
#include <memory>
#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_map>
#include <string>
#include <exception>

#include "Utility.h"
#include "Core/Controller.h"

bool global_verbose_flag = false;

int main(int argc, char** argv) {
    try {
        using std::pair;
        using std::string;

        srand(time(nullptr));

        pair<string, string> host = {"AICHostIP", "127.0.0.1"};
        pair<string, string> port = {"AICHostPort", "7099"};
        pair<string, string> token = {"AICToken", "00000000000000000000000000000000"};
        pair<string, string> retry_delay = {"AICRetryDelay", "1000"};

        if (argc > 1 && std::string(argv[1]) == "--verbose")
            global_verbose_flag = true;

        if (const char* host_env = std::getenv(host.first.c_str()))
            host.second = std::string(host_env);
        if (const char* port_env = std::getenv(port.first.c_str()))
            port.second = std::string(port_env);
        if (const char* token_env = std::getenv(token.first.c_str()))
            token.second = std::string(token_env);
        if (const char* retry_delay_env = std::getenv(retry_delay.first.c_str()))
            retry_delay.second = std::string(retry_delay_env);

        auto controller = std::make_unique<Controller>(host.second,
                                                       std::stoi(port.second),
                                                       token.second,
                                                       std::stoi(retry_delay.second));
        controller->run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return -1;
    }

    return 0;
}
