# pragma once

#include "environment.hpp"

#define BUF_SIZE 1000000 //size of buffer
#define BUF_BUFFER 200 //flush buffer when this close to size

struct Logger {
    Logger(std::ostream* out, Environment* env);
    void log(std::string s);
    void flush();

    std::string buffer;
    std::ostream* out;
    std::mutex lock;
    Environment* env;
};
