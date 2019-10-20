#pragma once
#include <iostream>

struct Organism {
    Organism(int id);
    Organism(int id, std::ostream* logger);
    ~Organism();

    int id;
    std::ostream* logger;
private:
    void birth_message();
    void death_message();
};