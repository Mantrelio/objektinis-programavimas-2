#pragma once

#include "student.h"

Student createStudentManual();
Student createStudentRandomGrades();
Student createStudentFullyRandom();

template <typename T>
T createStudentsFromFile(const string& filename);
