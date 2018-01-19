#include <iostream>
#include <memory>
#include <exception>

#include "Core/Controller.h"

int main(int argc, char** argv) {
    try {
        auto controller = std::make_unique<Controller>("127.0.0.1", 8080);
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
