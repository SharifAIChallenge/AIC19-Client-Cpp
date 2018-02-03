#include <iostream>
#include <memory>
#include <exception>

#include "Core/Controller.h"

int main(int argc, char** argv) {
    try {
        std::string host = argc > 1 ? argv[1] : "localhost";
        int port = argc > 2 ? std::stoi(argv[2]) : 7099;

        auto controller = std::make_unique<Controller>(host, port);
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
