#pragma once

#include "student.h"

void showMainMenu();

template <typename T>
void handleMenuChoice(int choice, T& students);

template <typename T>
void startMainMenu();
