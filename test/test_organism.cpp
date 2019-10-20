#include "catch.hpp"
#include <iostream>
#include <string>
#include <sstream>

#include "../src/organism.hpp"

TEST_CASE("organism lifecycle"){
    std::ostringstream ss;
    Organism* org = new Organism(5, &ss);

    SECTION("id"){
        REQUIRE(org.id == 5);
    }


    SECTION("birth log"){
        const auto birth_message = ss.str();

        REQUIRE(birth_message == "Birth: 5\n");
    }

    SECTION("death log"){
        const auto birth_message = ss.str();
        CHECK(birth_message == "Birth: 5\n");

        ss.str("");
        delete org;
        const auto death_message = ss.str();
        REQUIRE(death_message == "Death: 5\n");
    }
}