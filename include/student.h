#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "human.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;

class Student : public Human {
private:
    int examGrade_;
    vector<int> homeworkGrades_;

public:
    Student() : Human(), examGrade_(0) {}

    Student(string name, string surname) : Human(name, surname), examGrade_(0) {}
    Student(string name, string surname, vector<int> homeworkGrades, int examGrade) : Human(name, surname), examGrade_(examGrade), homeworkGrades_(homeworkGrades) {}
    Student(std::istream& is);
    Student(const Student& other)
        : Human(other),
          examGrade_(other.examGrade_),
          homeworkGrades_(other.homeworkGrades_) {}

    Student(Student&& other) noexcept
        : Human(std::move(other)),
          examGrade_(other.examGrade_),
          homeworkGrades_(std::move(other.homeworkGrades_)) {
        other.examGrade_ = 0;
    }
    Student& operator=(const Student& other) {
        if (this == &other) {
            return *this;
        }

        Human::operator=(other);
        examGrade_ = other.examGrade_;
        homeworkGrades_ = other.homeworkGrades_;

        return *this;
    }
    Student& operator=(Student&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Human::operator=(std::move(other));
        examGrade_ = other.examGrade_;
        homeworkGrades_ = std::move(other.homeworkGrades_);
        other.examGrade_ = 0;

        return *this;
    }
    ~Student() {
        name_.clear();
        surname_.clear();
        homeworkGrades_.clear();
        examGrade_ = 0;
    }

    using Human::name;
    using Human::surname;
    inline int examGrade() const { return examGrade_; }
    inline const vector<int>& homeworkGrades() const { return homeworkGrades_; }
    double finalGradeAverage() const;
    double finalGradeMedian() const;

    using Human::setName;
    using Human::setSurname;
    inline void setExamGrade(int examGrade) { examGrade_ = examGrade; }
    inline void setHomeworkGrades(vector<int> homeworkGrades) { homeworkGrades_ = homeworkGrades; }

    std::istream& readStudent(std::istream& is);
    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};
