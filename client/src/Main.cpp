#include <iostream>
#include <memory>
#include <exception>

#include "Network/Network.h"

int main(int argc, char** argv) {
    std::cout << "Welcome to Sharif AI Challenge 2018!" << std::endl;

    try {
        auto network = std::make_unique<Network>("127.0.0.1", 8080);
        network->connect();

        std::cin.get();
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
