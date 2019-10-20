#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <string>
#include <sstream>

TEST_CASE("base_pass") {
    std::cout << "hello test!";
    REQUIRE(true);
}

TEST_CASE("test iostream") {
    std::ostringstream ss;
    ss << "Check ";
    ss << "one" << "\n";

    const auto check_one = ss.str();
    ss.str("");

    ss << "Check two\n";

    const auto check_two = ss.str();

    REQUIRE(check_one == "Check one\n");
    REQUIRE(check_two == "Check two\n");
}