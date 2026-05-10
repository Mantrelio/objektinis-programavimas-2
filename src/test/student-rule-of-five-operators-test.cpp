#include "student-rule-of-five-operators-test.h"

#include "human.h"
#include "student.h"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

void printTestResult(const char* testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

bool testCopyConstructor() {
    Student original("Jonas", "Jonaitis", {8, 9}, 10);
    Student copy(original);

    return copy.name() == "Jonas" &&
           copy.surname() == "Jonaitis" &&
           copy.examGrade() == 10 &&
           copy.homeworkGrades() == std::vector<int>({8, 9});
}

bool testMoveConstructor() {
    Student source("Petras", "Petraitis", {6, 7, 8}, 9);
    Student moved(std::move(source));

    return moved.name() == "Petras" &&
           moved.surname() == "Petraitis" &&
           moved.examGrade() == 9 &&
           moved.homeworkGrades() == std::vector<int>({6, 7, 8}) &&
           source.name().empty() &&
           source.surname().empty() &&
           source.examGrade() == 0 &&
           source.homeworkGrades().empty();
}

bool testCopyAssignment() {
    Student source("Ona", "Onute", {10, 9, 8}, 9);
    Student target("A", "B", {1}, 1);

    target = source;

    return target.name() == "Ona" &&
           target.surname() == "Onute" &&
           target.examGrade() == 9 &&
           target.homeworkGrades() == std::vector<int>({10, 9, 8});

}

bool testMoveAssignment() {
    Student source("Ieva", "Ievaite", {7, 8}, 10);
    Student target("X", "Y", {1, 2, 3}, 4);

    target = std::move(source);

    return target.name() == "Ieva" &&
           target.surname() == "Ievaite" &&
           target.examGrade() == 10 &&
           target.homeworkGrades() == std::vector<int>({7, 8}) &&
           source.name().empty() &&
           source.surname().empty() &&
           source.examGrade() == 0 &&
           source.homeworkGrades().empty();
}

bool testDestructor() {
    alignas(Student) std::byte storage[sizeof(Student)];
    void* const mem = static_cast<void*>(storage);

    Student* student = ::new (mem) Student("Lina", "Linute", std::vector<int>{9, 8, 10}, 10);
    student->~Student();

    Student* rebuilt = ::new (mem) Student();
    const bool ok = rebuilt->name().empty() &&
                    rebuilt->surname().empty() &&
                    rebuilt->examGrade() == 0 &&
                    rebuilt->homeworkGrades().empty();
    rebuilt->~Student();

    return ok;
}

bool testInputOperatorValid() {
    std::istringstream input("Matas Matutis 10 9 8 7\n");
    Student student;
    input >> student;

    return static_cast<bool>(input) &&
           student.name() == "Matas" &&
           student.surname() == "Matutis" &&
           student.examGrade() == 7 &&
           student.homeworkGrades() == std::vector<int>({10, 9, 8});
}

bool testInputOperatorInvalid() {
    std::istringstream input("Matas Matutis 10 A 8 7\n");
    Student student;
    input >> student;

    return static_cast<bool>(input.fail());
}

bool testOutputOperator() {
    Student student("Rasa", "Rasaite", {8, 8}, 10);
    std::ostringstream output;
    output << student;

    std::ostringstream expected;
    expected << std::left << std::setw(20) << "Rasa"
             << std::left << std::setw(20) << "Rasaite"
             << std::right << std::fixed << std::setprecision(2) << std::setw(15) << "9.20"
             << std::right << std::fixed << std::setprecision(2) << std::setw(15) << "9.20";

    return output.str() == expected.str();
}

bool testHumanIsAbstractAndNotInstantiable() {
    return std::is_abstract<Human>::value &&
           !std::is_default_constructible<Human>::value;
}

void handleStudentRuleOfFiveAndOperatorsTest() {
    int passed = 0;
    int failed = 0;

    const struct {
        const char* name;
        bool (*fn)();
    } tests[] = {
        {"Copy constructor", testCopyConstructor},
        {"Move constructor", testMoveConstructor},
        {"Copy assignment", testCopyAssignment},
        {"Move assignment", testMoveAssignment},
        {"Destructor", testDestructor},
        {"operator>> valid input", testInputOperatorValid},
        {"operator>> invalid input", testInputOperatorInvalid},
        {"operator<< output formatting", testOutputOperator},
        {"Human negali buti sukurtas (abstrakti klase)", testHumanIsAbstractAndNotInstantiable},
    };

    std::cout << "\n=== Student Rule of Five ir operatoriu testai ===" << std::endl;

    for (const auto& test : tests) {
        const bool ok = test.fn();
        printTestResult(test.name, ok);
        if (ok) {
            passed++;
        } else {
            failed++;
        }
    }

    std::cout << "\nRezultatas: " << passed << " pavyko, " << failed << " nepavyko." << std::endl;
}
