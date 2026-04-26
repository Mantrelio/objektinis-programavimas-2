#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;

class Student {
private:
    string name_;
    string surname_;
    int examGrade_;
    vector<int> homeworkGrades_;

public:
    Student() : examGrade_(0) {}

    Student(string name, string surname) : name_(name), surname_(surname), examGrade_(0) {}
    Student(string name, string surname, vector<int> homeworkGrades, int examGrade) : name_(name), surname_(surname), examGrade_(examGrade), homeworkGrades_(homeworkGrades) {}
    Student(std::istream& is);
    Student(const Student& other)
        : name_(other.name_),
          surname_(other.surname_),
          examGrade_(other.examGrade_),
          homeworkGrades_(other.homeworkGrades_) {}

    Student(Student&& other) noexcept
        : name_(std::move(other.name_)),
          surname_(std::move(other.surname_)),
          examGrade_(other.examGrade_),
          homeworkGrades_(std::move(other.homeworkGrades_)) {
        other.examGrade_ = 0;
    }
    Student& operator=(const Student& other) {
        if (this == &other) {
            return *this;
        }

        name_ = other.name_;
        surname_ = other.surname_;
        examGrade_ = other.examGrade_;
        homeworkGrades_ = other.homeworkGrades_;

        return *this;
    }
    Student& operator=(Student&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        name_ = std::move(other.name_);
        surname_ = std::move(other.surname_);
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

    inline const string& name() const { return name_; }
    inline const string& surname() const { return surname_; }
    inline int examGrade() const { return examGrade_; }
    inline const vector<int>& homeworkGrades() const { return homeworkGrades_; }
    double finalGradeAverage() const;
    double finalGradeMedian() const;

    inline void setName(string name) { name_ = name; }
    inline void setSurname(string surname) { surname_ = surname; }
    inline void setExamGrade(int examGrade) { examGrade_ = examGrade; }
    inline void setHomeworkGrades(vector<int> homeworkGrades) { homeworkGrades_ = homeworkGrades; }

    std::istream& readStudent(std::istream& is);
    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};
