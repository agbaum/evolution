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
    std::lock_guard<std::mutex> guard { this->orgs_lock };
    for (size_t i = 0; i < n; i++) {
        this->orgs.insert({i, new Organism(i, this)});
        Organism* org = this->orgs.at(i);
        // lock all orgs until everyone is made
        org->org_lock.lock();
        this->threads.emplace_back( &Organism::main_loop, org );
        this->threads.emplace_back( &Organism::hunger_loop, org );
    }

    // go through and unlock all added orgs
    for (size_t i = 0; i < n; i++) {
        this->orgs.at(i)->org_lock.unlock();
    }
}

// // must have organism's 
// void Environment::kill_organism(unsigned int id) {
//     Organism* org = this->orgs.at(id);
    
//     this->orgs.erase(id);
// }

std::unique_ptr<Food> Environment::make_food() {
    std::unique_ptr<Food> food { new Food(this->food_counter) };
    this->food_counter++;
    std::ostringstream logss;
    logss << "Food Made: " << food->id;
    this->logger->log(logss.str());
    return food;
}

// void Environment::require_food(unsigned int id) {
//     Organism* org = this->orgs.at(id);
//     if(org->stomach.empty()) {
//         kill_organism(id);
//     } else {
//         if(!org->stomach.front())
//             kill_organism(id);
//         std::unique_ptr<Food> recieved_food = std::move(this->orgs.at(id)->stomach.front());
//         this->orgs.at(id)->stomach.pop();
//         *this->logger << "Food Consumed: " << id << ", " << recieved_food->id << "\n";
//     }
// }

Food::Food(unsigned int id) {
    this->id = id;
}
