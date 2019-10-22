#include "environment.hpp"

Environment::Environment(std::ostream* logger) {
    if (logger == NULL)
        this->logger = &std::cout;
    else
        this->logger = logger;
}

Environment::~Environment() {
    for (auto &&i : this->orgs) {
        kill_organism(i.first);
    }
}

void Environment::kill_organism(unsigned int id) {
    delete this->orgs.at(id);
    this->orgs.erase(id);
}

void Environment::add_organisms(unsigned int n) {
    for (size_t i = 0; i < n; i++) {
        this->orgs.insert({i, new Organism(i, this->logger)});
    }
}