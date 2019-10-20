#include "organism.hpp"
#include <iostream>


using namespace std;

Organism::Organism(int id) {
    this->id = id;
    this->logger = &cout;
    this->birth_message();
}

Organism::Organism(int id, std::ostream* logger) {
    this->id = id;
    this->logger = logger;
    this->birth_message();
}

Organism::~Organism(){
    this->death_message();
}

// logs the birth message of an organism
void Organism::birth_message() {
    *this->logger << "Birth: " << id << "\n";
}

// logs the death message of an organism
void Organism::death_message() {
    *this->logger << "Death: " << id << "\n";
}
