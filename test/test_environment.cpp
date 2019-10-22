#include "catch.hpp"
#include <sstream>

#include "../src/environment.hpp"

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