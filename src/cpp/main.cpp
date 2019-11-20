#include <iostream>
#include <fstream>
#include "environment.hpp"
#include "logger.hpp"
#include <sstream>
#include <windows.h>

int main() {
    std::ofstream logfile{ "log.txt" };

    Environment env(&logfile);
    env.add_organisms(100);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "done!\n";    
}

