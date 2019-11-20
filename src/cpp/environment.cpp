#include "environment.hpp"
#include "organism.hpp"
#include "logger.hpp"
#include <sstream>

Environment::Environment(std::ostream* log_out) {
    QueryPerformanceCounter(&this->clock_start);
    if (log_out == NULL)
         this->logger = new Logger(&std::cout, this);
    else
        this->logger = new Logger(log_out, this);
    this->food_counter = 0;
    this->shutdown = false;
}

Environment::~Environment() {    
    this->orgs_lock.lock();
    this->shutdown = true;
    for (auto &&o : this->orgs) {
        std::lock_guard<std::mutex> org_guard { o.second->org_lock };
        o.second->dead = true;
    }
    this->orgs_lock.unlock();
    for (auto &&i : this->threads) { 
        i.join();
    }
    this->logger->log("done");
    delete this->logger;
}


void Environment::add_organisms(unsigned int n) {
    std::lock_guard<std::mutex> org_guard { this->orgs_lock };
    this->food_lock.lock();

    // start food main loops (can't start getting food until everyone starts)
    for (size_t i = 0; i < n; i++) {
        this->orgs.insert({i, new Organism(i, this)});
        Organism* org = this->orgs.at(i);
        this->threads.emplace_back( &Organism::main_loop, org );
    }
    this->food_lock.unlock();

    // start hunger loops
    for (size_t i = 0; i < n; i++) {
        this->threads.emplace_back( &Organism::hunger_loop, this->orgs.at(i) );
    }
}

std::unique_ptr<Food> Environment::make_food() {
    std::lock_guard<std::mutex> food_guard { this->food_lock };
    std::unique_ptr<Food> food { new Food(this->food_counter) };
    this->food_counter++;
    std::ostringstream logss;
    logss << "Food Made: " << food->id;
    this->logger->log(logss.str());
    return food;
}

Food::Food(unsigned int id) {
    this->id = id;
}
