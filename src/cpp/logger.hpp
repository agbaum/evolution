# pragma once

#include <mutex>
#include <iostream>
#include <string>

#define BUF_SIZE 1000 //size of buffer
#define BUF_BUFFER 200 //flush buffer when this close to size

struct Environment;

struct Logger {
    Logger(std::ostream* out, Environment* env);
    void log(std::string s);
    void flush();

    std::string buffer;
    std::ostream* out;
    std::mutex lock;
    Environment* env;
};
