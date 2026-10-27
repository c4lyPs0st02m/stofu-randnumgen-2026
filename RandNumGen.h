#pragma once

#include <iostream>

const int rangeMIN{ 1 }, rangeMAX{ 20 };

/// @brief Generates a random integer within a specified range.
///
/// @param[in] min Range's lower bound.
/// @param[in] max Range's upper bound.
int GenerateRandomNumber(
	const int min,
	const int max
);

/// @brief Displays a message box with the random generated integer.
///
/// @param[in,out] randNum Random generated integer.
void DisplayMessageBox(int& randNum);

/// Pointer to the DisplayMessageBox function.
void (*pDisplayMessageBox)(int&) { &DisplayMessageBox };

/// @brief Hook function for DisplayMessageBox.
///
/// @param[in,out] randNum Random generated integer.
void HookDisplayMessageBox(int& randNum);
