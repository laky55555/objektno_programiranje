#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "FileObserver.h"

// Na komandnoj liniji se zadaje ime ulazne datoteke
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " file_name\n";
        return EXIT_FAILURE;
    }
    // konkretni subjekt
    Prices test(argv[1]);
    // konkretni observer
    DisplayInfo display(&test);

    while (true) {
        test.setState();
        // spavaj jednu sekundu
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return EXIT_SUCCESS;
}
