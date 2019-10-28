#include "organism.hpp"

Organism::Organism(int id, Environment* env) {
    this->id = id;
    this->env = env;

    this->birth_message();
}

Organism::~Organism(){
    this->death_message();
}

void Organism::request_food(){
    std::unique_ptr<Food> food = env->make_food();
    this->stomach.push(std::move(food));
}

// logs the birth message of an organism
void Organism::birth_message() {
    *this->env->logger << "Birth: " << id << "\n";
}

// logs the death message of an organism
void Organism::death_message() {
    *this->env->logger << "Death: " << id << "\n";
}
