#include <iostream>
#include <fstream>
#include "environment.hpp"

int main() {
    std::ofstream logfile{ "log.txt" };

    Environment env(&logfile);
    env.add_organisms(4);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "done!\ns"
}

