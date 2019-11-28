#pragma once
// #include "organism.hpp"
#include "logger.hpp"

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
    Environment(std::ostream* log_out, int hunger_min, int hunger_max);
    ~Environment();

    std::map<unsigned int, Organism*> orgs;
    Logger logger;
    bool shutdown; // true if mid-destruct
    std::vector<std::thread> threads; // protected by orgs_lock and shutdown
    int hunger_min; //in us
    int hunger_max; // in us

    LARGE_INTEGER clock_start;

    std::mutex orgs_lock;
    std::mutex log_lock;
    std::mutex food_lock;

    void add_organisms(unsigned int n);
    void stop();

    std::unique_ptr<Food> make_food(int org_id);
    unsigned int food_counter;

    void main_loop();
};

