#include "catch_amalgamated.hpp"

#include "human.h"
#include "student.h"

#include <cstddef>
#include <iomanip>
#include <new>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

TEST_CASE("Student copy constructor copies all fields", "[student][rule-of-five]") {
    const Student original("Jonas", "Jonaitis", {8, 9}, 10);

    const Student copy(original);

    REQUIRE(copy.name() == "Jonas");
    REQUIRE(copy.surname() == "Jonaitis");
    REQUIRE(copy.examGrade() == 10);
    REQUIRE(copy.homeworkGrades() == std::vector<int>({8, 9}));
}

TEST_CASE("Student move constructor moves all fields and resets source", "[student][rule-of-five]") {
    Student source("Petras", "Petraitis", {6, 7, 8}, 9);

    const Student moved(std::move(source));

    REQUIRE(moved.name() == "Petras");
    REQUIRE(moved.surname() == "Petraitis");
    REQUIRE(moved.examGrade() == 9);
    REQUIRE(moved.homeworkGrades() == std::vector<int>({6, 7, 8}));

    REQUIRE(source.name().empty());
    REQUIRE(source.surname().empty());
    REQUIRE(source.examGrade() == 0);
    REQUIRE(source.homeworkGrades().empty());
}

TEST_CASE("Student copy assignment copies all fields", "[student][rule-of-five]") {
    const Student source("Ona", "Onute", {10, 9, 8}, 9);
    Student target("A", "B", {1}, 1);

    target = source;

    REQUIRE(target.name() == "Ona");
    REQUIRE(target.surname() == "Onute");
    REQUIRE(target.examGrade() == 9);
    REQUIRE(target.homeworkGrades() == std::vector<int>({10, 9, 8}));
}

TEST_CASE("Student move assignment moves all fields and resets source", "[student][rule-of-five]") {
    Student source("Ieva", "Ievaite", {7, 8}, 10);
    Student target("X", "Y", {1, 2, 3}, 4);

    target = std::move(source);

    REQUIRE(target.name() == "Ieva");
    REQUIRE(target.surname() == "Ievaite");
    REQUIRE(target.examGrade() == 10);
    REQUIRE(target.homeworkGrades() == std::vector<int>({7, 8}));

    REQUIRE(source.name().empty());
    REQUIRE(source.surname().empty());
    REQUIRE(source.examGrade() == 0);
    REQUIRE(source.homeworkGrades().empty());
}

TEST_CASE("Student destructor allows safe destruction and reconstruction in place", "[student][rule-of-five]") {
    alignas(Student) std::byte storage[sizeof(Student)];
    void* const mem = static_cast<void*>(storage);

    Student* student = ::new (mem) Student("Lina", "Linute", std::vector<int>{9, 8, 10}, 10);
    student->~Student();

    Student* rebuilt = ::new (mem) Student();
    REQUIRE(rebuilt->name().empty());
    REQUIRE(rebuilt->surname().empty());
    REQUIRE(rebuilt->examGrade() == 0);
    REQUIRE(rebuilt->homeworkGrades().empty());
    rebuilt->~Student();
}

TEST_CASE("Student satisfies basic rule-of-five traits", "[student][rule-of-five]") {
    REQUIRE(std::is_copy_constructible<Student>::value);
    REQUIRE(std::is_move_constructible<Student>::value);
    REQUIRE(std::is_copy_assignable<Student>::value);
    REQUIRE(std::is_move_assignable<Student>::value);
}

TEST_CASE("Student input operator parses valid input", "[student][operators]") {
    std::istringstream input("Matas Matutis 10 9 8 7\n");
    Student student;

    input >> student;

    REQUIRE(static_cast<bool>(input));
    REQUIRE(student.name() == "Matas");
    REQUIRE(student.surname() == "Matutis");
    REQUIRE(student.examGrade() == 7);
    REQUIRE(student.homeworkGrades() == std::vector<int>({10, 9, 8}));
}

TEST_CASE("Student input operator fails on invalid input", "[student][operators]") {
    std::istringstream input("Matas Matutis 10 A 8 7\n");
    Student student;

    input >> student;

    REQUIRE(input.fail());
}

TEST_CASE("Student output operator formats output correctly", "[student][operators]") {
    const Student student("Rasa", "Rasaite", {8, 8}, 10);
    std::ostringstream output;
    output << student;

    std::ostringstream expected;
    expected << std::left << std::setw(20) << "Rasa"
             << std::left << std::setw(20) << "Rasaite"
             << std::right << std::fixed << std::setprecision(2) << std::setw(15) << "9.20"
             << std::right << std::fixed << std::setprecision(2) << std::setw(15) << "9.20";

    REQUIRE(output.str() == expected.str());
}

TEST_CASE("Human is abstract and not default constructible", "[human][type-traits]") {
    REQUIRE(std::is_abstract<Human>::value);
    REQUIRE_FALSE(std::is_default_constructible<Human>::value);
}
