#pragma once
// #include "organism.hpp"

#include <map>
#include <memory>
#include <set>

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
    std::set<unsigned int> food_ids;

    void add_organisms(unsigned int n);
    void kill_organism(unsigned int id);

    std::unique_ptr<Food> make_food();
    unsigned int food_counter;
    void require_food(unsigned int id);
};

