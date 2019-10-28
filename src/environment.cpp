#include "environment.hpp"
#include "organism.hpp"

Environment::Environment(std::ostream* logger) {
    if (logger == NULL)
        this->logger = &std::cout;
    else
        this->logger = logger;
    this->food_counter = 0;
}

Environment::~Environment() {
    for (auto &&i : this->orgs) {
        kill_organism(i.first);
    }
}


void Environment::add_organisms(unsigned int n) {
    for (size_t i = 0; i < n; i++) {
        this->orgs.insert({i, new Organism(i, this)});
    }
}

void Environment::kill_organism(unsigned int id) {
    delete this->orgs.at(id);
    this->orgs.erase(id);
}

std::unique_ptr<Food> Environment::make_food(){
    std::unique_ptr<Food> food { new Food(this->food_counter) };
    this->food_counter++;
    *this->logger << "Food Made: " << food->id << "\n";
    return food;
}

void Environment::require_food(unsigned int id){
    Organism* org = this->orgs.at(id);
    if(org->stomach.empty()){
        kill_organism(id);
    } else {
        if(!org->stomach.front())
            kill_organism(id);
        std::unique_ptr<Food> recieved_food = std::move(this->orgs.at(id)->stomach.front());
        this->orgs.at(id)->stomach.pop();
        *this->logger << "Food Consumed: " << id << ", " << recieved_food->id << "\n";
    }
}

Food::Food(unsigned int id){
    this->id = id;
}
