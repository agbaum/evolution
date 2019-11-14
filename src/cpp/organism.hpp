#pragma once
#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <random>

#include "environment.hpp"

#define HUNGER_MIN 6 //in ms
#define HUNGER_MAX 100 //in ms

struct Organism {
    Organism(int id, Environment* env);
    ~Organism();

    unsigned int id;
    Environment* env;
    std::queue<std::unique_ptr<Food>> stomach;

    std::mutex org_lock;
    int remaining_threads; 
    bool dead;

    void request_food();
    void die();

    void main_loop();
    void hunger_loop();
    

private:
    void birth_message();
    void death_message();
    void close_thread();

    std::default_random_engine rand_gen;
    std::uniform_int_distribution<int> hunger_dist {HUNGER_MIN, HUNGER_MAX};
};

