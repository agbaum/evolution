#include <iostream>
#include "environment.hpp"

int main() {
    Environment env(&std::cout);
    env.add_organisms(4);
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

