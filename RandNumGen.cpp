#include "RandNumGen.h"
#include "mhook-lib/mhook.h"

#include <cstdlib>
#include <random>
#include <string>
#include <windows.h>


int GenerateRandomNumber(
	const int min,
	const int max
) {
	if (min > max) {
		throw std::invalid_argument("[ERROR] MIN cannot be greater than MAX.");
	}
	// Use std::random_device to avoid number sequence replication for multiple runs.
	// Use 64-bit std::mersenne_twister_engine seeded with std::random_device.
	thread_local std::mt19937_64 generator(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	// Transform the generated UINT into an int in range [min, max].
	return dist(generator);
}

void DisplayMessageBox(int& randNum) {
	while (true) {
		std::string msg{ "Random number is: " + std::to_string(randNum) };

		int msgboxID = MessageBox(
			NULL,
			msg.c_str(),
			"RandNumGen",
			MB_ICONINFORMATION | MB_CANCELTRYCONTINUE | MB_DEFBUTTON3
		);

		if (msgboxID == IDCANCEL) {
			exit(0);
		}
		else if (msgboxID == IDTRYAGAIN) {
			try {
				randNum = GenerateRandomNumber(rangeMIN, rangeMAX);
			}
			catch (const std::invalid_argument& errorInvalArg) {
				std::cerr << errorInvalArg.what() << "\n";
			}
		}
		else {
			break;
		}
	}
}

void HookDisplayMessageBox(int& randNum) {
	if (randNum == 1) {
		randNum = 100;
	}
	if (randNum == 2) {
		std::abort();
	}
	(*pDisplayMessageBox)(randNum);
}

int main()
{
	int randNum{ 0 };
	try {
		randNum = GenerateRandomNumber(rangeMIN, rangeMAX);

		DisplayMessageBox(randNum);

		if (!Mhook_SetHook(
			reinterpret_cast<PVOID*>(&pDisplayMessageBox),
			reinterpret_cast<PVOID>(HookDisplayMessageBox)
		)) {
			std::cout << "[ERROR] Couldn't hook the DisplayMessageBox function.\n";
		}
		else {
			DisplayMessageBox(randNum);
			if (!Mhook_Unhook(reinterpret_cast<PVOID*>(&pDisplayMessageBox))) {
				std::cout << "[ERROR] Couldn't unhook the DisplayMessageBox function.\n";
			}
		}
	}
	catch (const std::invalid_argument& errorInvalArg) {
		std::cerr << errorInvalArg.what() << "\n";
	}

	return 0;
}
