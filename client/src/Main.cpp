#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>
#include <exception>

#include "Utility.h"
#include "Core/Controller.h"

bool global_verbose_flag = true;

int main(int argc, char** argv) {
    try {
        std::vector<std::string> args;
        for (int i = 1; i < argc; ++i)
            args.emplace_back(argv[i]);

        global_verbose_flag = (std::find(args.begin(), args.end(), "--verbose") != args.end());

        auto iter = std::find(args.begin(), args.end(), "--host");
        std::string host = (iter == args.end() ? "localhost" : *(iter + 1));

        iter = std::find(args.begin(), args.end(), "--port");
        int port = (iter == args.end() ? 7099 : std::stoi(*(iter + 1)));

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
