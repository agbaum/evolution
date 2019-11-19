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

    // LARGE_INTEGER start_time;
    // QueryPerformanceCounter(&start_time);

    // for (size_t i = 0; i < 1000000000; i++)
    // {
    //     LARGE_INTEGER now;
    //     QueryPerformanceCounter(&now);
    //     std::ostringstream ss;

    //     ss << now.QuadPart - start_time.QuadPart << ": " << i;
    //     env.logger->log(ss.str());
    // }
    
}

