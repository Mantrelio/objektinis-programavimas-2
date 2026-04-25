#pragma once

#include "student.h"

#include <iostream>

template <typename T>
void outputResults(const T& students, std::ostream& out);

template <typename T>
void chooseOutputAndPrint(T& students);
