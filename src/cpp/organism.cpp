#include "organism.hpp"
#include "logger.hpp"
#include <sstream>
#include <chrono>


Organism::Organism(int id, Environment* env) {
    this->id = id;
    this->env = env;
    this->remaining_threads = 2;
    this->dead = false;
    
    this->birth_message();
}

Organism::~Organism() {
    //this->death_message();
}

// must have org_lock locked before calling this
void Organism::request_food() {
    this->org_lock.unlock();
    std::unique_ptr<Food> food = env->make_food();
    this->org_lock.lock();
    this->stomach.push(std::move(food));
}

// must have org_lock locked before calling this
void Organism::die() {
    this->death_message();
    this->dead = true;
    this->org_lock.unlock();
    std::lock_guard<std::mutex> guard { this->env->orgs_lock };
    this->env->orgs.erase(id);
    this->org_lock.lock();
}

void Organism::close_thread() {
    this->org_lock.lock();
    this->remaining_threads--;
    if (this->remaining_threads == 0) {
        this->org_lock.unlock();
        delete this;
    } else {
        this->org_lock.unlock();
    }
}

void Organism::main_loop() {
    int i = 0;
    while(1) {
        std::lock_guard<std::mutex> guard { this->org_lock };
        if (this->dead)
            break;
        this->request_food();
        i++;
    }

   this->close_thread();
}

void Organism::hunger_loop() {
    
    int i = 0;
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(
            this->hunger_dist(this->rand_gen)));
        std::lock_guard<std::mutex> guard { this->org_lock };
        if (this->dead)
            break;

        if(this->stomach.empty()) {
            //stomach empty -> die
            this->die();
        } else {
            //loop through stomach removing false food
            while(!this->stomach.empty() && !this->stomach.front()) {
                this->stomach.pop();
            }
            //if stomach now empty -> die
            if(this->stomach.empty()) {
                this->die();
            } else {
                // take the food
                std::unique_ptr<Food> recieved_food = std::move(this->stomach.front());
                this->stomach.pop();
                std::ostringstream logss;
                logss << "Food Consumed: " << id << ", " << recieved_food->id;
                this->env->logger->log(logss.str());
            }
        }
        i++;
    }

    this->close_thread();
}

// logs the birth message of an organism
void Organism::birth_message() {
    std::ostringstream logss;
    logss << "Birth: " << id;
    this->env->logger->log(logss.str());
}

// logs the death message of an organism
void Organism::death_message() {
    std::ostringstream logss;
    logss << "Death: " << id;
    this->env->logger->log(logss.str());
}

