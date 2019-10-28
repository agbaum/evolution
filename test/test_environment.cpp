#include "catch.hpp"
#include <sstream>

#include "../src/environment.hpp"
#include "../src/organism.hpp"

TEST_CASE("Environment construct and destruct"){
    std::ostringstream ss;

    Environment* env = new Environment(&ss);
    env->add_organisms(2);

    SECTION("ids"){
        REQUIRE(env->orgs.at(0)->id == 0);
        REQUIRE(env->orgs.at(1)->id == 1);
    }

    SECTION("birth logs"){
        const auto birth_messages = ss.str();
        REQUIRE(birth_messages == "Birth: 0\nBirth: 1\n");
    }

    SECTION("kill"){
        const auto birth_messages = ss.str();
        CHECK(birth_messages == "Birth: 0\nBirth: 1\n");
        ss.str("");

        env->kill_organism(0);

        SECTION("kill org message"){
            const auto death_message_0 = ss.str();
            REQUIRE(death_message_0 == "Death: 0\n");
        }

        SECTION("kill org remaining"){
            REQUIRE(env->orgs.at(1)->id == 1);
        }

        SECTION("kill org gone"){
            REQUIRE_THROWS(env->orgs.at(0));
        }
    }
    
    SECTION("destruction"){
        const auto birth_messages = ss.str();
        CHECK(birth_messages == "Birth: 0\nBirth: 1\n");
        ss.str("");
        delete env;

        const auto death_messages = ss.str();
        REQUIRE(death_messages == "Death: 0\nDeath: 1\n");
    }
}

TEST_CASE("Food"){
    std::ostringstream ss;
    Environment* env = new Environment(&ss);

    SECTION("make food"){
        std::unique_ptr<Food> food = env->make_food();
        auto food_message = ss.str();

        REQUIRE(food_message == "Food Made: 0\n");

        ss.str("");
        std::unique_ptr<Food> food1 = env->make_food();
        
        food_message = ss.str();
        REQUIRE(food_message == "Food Made: 1\n");
    }

    SECTION("food not transferable"){
        std::unique_ptr<Food> food = env->make_food();
        const auto food_message = ss.str();

        CHECK(food_message == "Food Made: 0\n");

        std::unique_ptr<Food> stolen_food;

        stolen_food = std::move(food);

        REQUIRE(stolen_food->id == 0);
        REQUIRE_FALSE(food);
    }
}

TEST_CASE("feeding"){
    std::ostringstream ss;

    Environment* env = new Environment(&ss);
    env->add_organisms(1);

    const auto birth_message = ss.str();
    CHECK(birth_message == "Birth: 0\n");
    ss.str("");

    Organism* org = env->orgs.at(0);
    CHECK(org != nullptr);

    SECTION("get food"){
        CHECK(org->stomach.size() == 0);
        org->request_food();
        const auto food_message = ss.str();
        REQUIRE(food_message == "Food Made: 0\n");

        REQUIRE(org->stomach.size() == 1);
    }

    SECTION("eat food"){
        org->request_food();
        const auto food_message = ss.str();
        CHECK(food_message == "Food Made: 0\n");
        ss.str("");

        env->require_food(0);
        const auto consume_message = ss.str();
        REQUIRE(consume_message == "Food Consumed: 0, 0\n");
        REQUIRE(env->orgs.at(0) == org);
        REQUIRE(org->stomach.size() == 0);
    }

    SECTION("food fail"){
        env->require_food(0);
        const auto death_message = ss.str();
        REQUIRE(death_message == "Death: 0\n");
        REQUIRE_THROWS(env->orgs.at(0));
    }   
}