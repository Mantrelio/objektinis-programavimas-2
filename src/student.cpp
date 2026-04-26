#include "student.h"

#include "grading-utils.h"

#include <sstream>

Student::Student(std::istream& is) : Student() {
    readStudent(is);
}

double Student::finalGradeAverage() const {
    if (homeworkGrades_.empty() || examGrade_ < 1 || examGrade_ > 10) {
        return 0;
    }

    return calculateFinalGradeAverage(homeworkGrades_, examGrade_);
}

double Student::finalGradeMedian() const {
    if (homeworkGrades_.empty() || examGrade_ < 1 || examGrade_ > 10) {
        return 0;
    }

    return calculateFinalGradeMedian(homeworkGrades_, examGrade_);
}

std::istream& Student::readStudent(std::istream& is) {
    string line;
    if (!getline(is >> std::ws, line)) {
        return is;
    }

    std::istringstream iss(line);
    string name;
    string surname;

    if (!(iss >> name >> surname)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    vector<int> grades;
    string token;

    while (iss >> token) {
        std::istringstream ts(token);
        int grade;
        if (!(ts >> grade) || !ts.eof()) {
            is.setstate(std::ios::failbit);
            return is;
        }

        if (grade < 1 || grade > 10) {
            is.setstate(std::ios::failbit);
            return is;
        }

        grades.push_back(grade);
    }

    if (grades.size() < 2) {
        is.setstate(std::ios::failbit);
        return is;
    }

    const int examGrade = grades.back();
    grades.pop_back();

    setName(name);
    setSurname(surname);
    setExamGrade(examGrade);
    setHomeworkGrades(grades);

    return is;
}

std::istream& operator>>(std::istream& is, Student& student) {
    return student.readStudent(is);
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << left << setw(20) << student.name()
       << left << setw(20) << student.surname()
       << right << std::fixed << std::setprecision(2) << setw(15) << student.finalGradeAverage()
       << right << std::fixed << std::setprecision(2) << setw(15) << student.finalGradeMedian();

    return os;
}
