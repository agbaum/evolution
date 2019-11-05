#pragma once
// #include "organism.hpp"

#include <map>
#include <memory>
#include <set>
#include <mutex>
#include <thread>
#include <vector>

struct Organism;

struct Food {
    Food(unsigned int id);
    unsigned int id;
};

struct Environment {
    Environment(std::ostream* logger);
    ~Environment();

    std::map<unsigned int, Organism*> orgs;
    std::ostream* logger;
    bool shutdown; // true if mid-destruct
    std::vector<std::thread> threads; // protected by orgs_lock and shutdown

    std::chrono::high_resolution_clock::time_point clock_start;

    std::mutex orgs_lock;
    std::mutex log_lock;
    std::mutex food_lock;

    void log(std::string s);
    void add_organisms(unsigned int n);
    // void kill_organism(unsigned int id);

    std::unique_ptr<Food> make_food();
    unsigned int food_counter;
    // void require_food(unsigned int id);

    void main_loop();
};

