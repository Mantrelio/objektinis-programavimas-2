#pragma once

#include "create-student.h"
#include "input-utils.h"
#include "output-results.h"
#include "sort-students.h"
#include "student.h"
#include "grading-utils.h"

#include <utility>

template <typename T>
void handleSortNuskriaustiAndProtingiFromFile();

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiFirstStrategy(const T& students);

template <typename T>
T sortNuskriaustiAndProtingiSecondStrategy(T& students);

template <typename T>
std::pair<T, T> sortNuskriaustiAndProtingiThirdStrategy(T& students);