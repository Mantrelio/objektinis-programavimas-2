#include "catch_amalgamated.hpp"

#include "student.h"

#include <sstream>
#include <vector>

TEST_CASE("Student copy constructor keeps all values", "[student]") {
    Student original("Jonas", "Jonaitis", {8, 9}, 10);
    Student copy(original);

    REQUIRE(copy.name() == "Jonas");
    REQUIRE(copy.surname() == "Jonaitis");
    REQUIRE(copy.examGrade() == 10);
    REQUIRE(copy.homeworkGrades() == std::vector<int>{8, 9});
}

TEST_CASE("Student input operator rejects invalid tokens", "[student]") {
    std::istringstream input("Matas Matutis 10 A 8 7\n");
    Student student;

    input >> student;

    REQUIRE(input.fail());
}
