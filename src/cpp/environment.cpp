#include "environment.hpp"
#include "organism.hpp"
#include <sstream>

Environment::Environment(std::ostream* logger) {
    clock_start = std::chrono::high_resolution_clock::now();
    if (logger == NULL)
        this->logger = &std::cout;
    else
        this->logger = logger;
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
    this->log("done");
}

void Environment::log(std::string s){
    auto time = std::chrono::high_resolution_clock::now() - this->clock_start;
    std::lock_guard<std::mutex> log_guard { this->log_lock };
    *this->logger << time.count() << ": " << s << "\n";
}

void Environment::add_organisms(unsigned int n) {
    std::lock_guard<std::mutex> guard { this->orgs_lock };
    for (size_t i = 0; i < n; i++) {
        this->orgs.insert({i, new Organism(i, this)});
        Organism* org = this->orgs.at(i);
        std::lock_guard<std::mutex> org_lock { org->org_lock };
        this->threads.emplace_back( &Organism::main_loop, org );
        this->threads.emplace_back( &Organism::hunger_loop, org );
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
    this->log(logss.str());
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
