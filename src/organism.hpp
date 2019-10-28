#pragma once
#include <iostream>
#include <queue>
#include <memory>

#include "environment.hpp"

struct Organism {
    Organism(int id, Environment* env);
    ~Organism();

    unsigned int id;
    Environment* env;
    std::queue<std::unique_ptr<Food>> stomach;

    void request_food();

private:
    void birth_message();
    void death_message();
};