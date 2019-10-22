#pragma once
#include "organism.hpp"

#include <map>

struct Environment {
    Environment(std::ostream* logger);
    ~Environment();

    std::map<unsigned int, Organism*> orgs;
    std::ostream* logger;

    void add_organisms(unsigned int n);
    void kill_organism(unsigned int);
};