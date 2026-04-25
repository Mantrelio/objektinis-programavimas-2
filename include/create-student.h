#pragma once

#include "student.h"

string randomName();
string randomSurname();

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();

template <typename T>
T createStudentsFromFile(const string& filename);
