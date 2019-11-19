#pragma once
// #include "organism.hpp"

#include <map>
#include <memory>
#include <set>
#include <mutex>
#include <thread>
#include <vector>
#include <windows.h>

struct Organism;
struct Logger;

struct Food {
    Food(unsigned int id);
    unsigned int id;
};

struct Environment {
    Environment(std::ostream* log_out);
    ~Environment();

    std::map<unsigned int, Organism*> orgs;
    Logger* logger;
    bool shutdown; // true if mid-destruct
    std::vector<std::thread> threads; // protected by orgs_lock and shutdown

    LARGE_INTEGER clock_start;

    std::mutex orgs_lock;
    std::mutex log_lock;
    std::mutex food_lock;

    void add_organisms(unsigned int n);
    // void kill_organism(unsigned int id);

    std::unique_ptr<Food> make_food();
    unsigned int food_counter;
    // void require_food(unsigned int id);

    void main_loop();
};

