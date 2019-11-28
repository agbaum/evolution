#include "logger.hpp"
#include "environment.hpp"

#include <string>
#include <iostream>

Logger::Logger(std::ostream* out, Environment* env) {
    if (this->out == NULL) {
        this->out = &std::cout;
    } else {
        this->out = out;
    }
    this->buffer.reserve(BUF_SIZE);
    this->env = env;
}

void Logger::log(std::string s) {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    std::lock_guard<std::mutex> log_guard { this->lock };
    this->buffer += std::to_string(now.QuadPart - this->env->clock_start.QuadPart);
    this->buffer += ": ";
    this->buffer += s;
    this->buffer += "\n";

    if (this->buffer.length() > BUF_SIZE - BUF_BUFFER){
        this->flush();
    } 
    //something about flushing
}

void Logger::flush() {
    // std::lock_guard<std::mutex> log_guard { this->lock };
    *this->out << this->buffer;
    this->buffer.clear();
}