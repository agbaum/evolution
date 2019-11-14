#include <iostream>
#include <fstream>
#include "environment.hpp"

int main() {
    std::ofstream logfile{ "log.txt" };

    Environment env(&logfile);
    env.add_organisms(100);
    std::this_thread::sleep_for(std::chrono::seconds(60));
    std::cout << "done!\n";
}

