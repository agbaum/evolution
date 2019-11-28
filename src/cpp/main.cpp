#include <iostream>
#include <fstream>
#include "environment.hpp"
#include "logger.hpp"
#include <sstream>
#include <windows.h>

int main() {
    //the if true is an awkward solution but here we are
    std::ofstream logfile1{ "log1_10.txt" };
    Environment env1 { &logfile1, 1, 10 };
    env1.add_organisms(50);
    std::this_thread::sleep_for(std::chrono::seconds(60));
    env1.stop();
    std::cout << "1 done!\n";    

    // env1.add_organisms(200);

    // std::ofstream logfile2{ "log1_100.txt" };
    // Environment env2 { &logfile2, 1, 100 };
    // env2.add_organisms(200);
    // std::this_thread::sleep_for(std::chrono::seconds(60));
    // env2.stop();
    // std::cout << "2 done!\n"; 

    // std::ofstream logfile3{ "log10_1000.txt" };
    // Environment env3 { &logfile3, 10, 1000 };
    // env3.add_organisms(200);
    // std::this_thread::sleep_for(std::chrono::seconds(60));
    // env3.stop();
    // std::cout << "3 done!\n"; 

    // std::ofstream logfile4{ "log100_1000.txt" };
    // Environment env4 = { &logfile4, 100, 1000 };
    // env4.add_organisms(200);
    // std::this_thread::sleep_for(std::chrono::seconds(60));
    // env4.stop();
    // std::cout << "4 done!\n"; 
}

