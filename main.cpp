#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include <Windows.h>

#define TEST
//#define CONSOLECOMMANDS

const int votersSize = 400;
const int partySize = 4;
#ifdef CONSOLECOMMANDS
	const char* prompt = "Press Enter To Continue...";
#endif //CONSOLECOMMANDS 


int randomNumGenerator(int randomRange);
void createVotersGroup(int votersSize, int partySize, int votersGroup[]);
void convincer(int votersSize, int votersGroup[], int countConvinces);
void print(int votersSize, int votersGroup[]);
void statisticProvider(int votersSize, int partySize, int votersGroup[]);
void clear_screen();
void pause(const char* prompt);

int main() {

#ifdef TEST
	srand(1);
#endif // TEST
#ifndef TEST
	srand(time(0));
#endif // !TEST

	int votersGroup[votersSize];
	int runs = 0;
	int printSteps = 0;
	int countConvinces = 0;
	std::cout << "Enter runs: ";
	std::cin >> runs;
	std::cout << "Enter steps: ";
	std::cin >> printSteps;
	createVotersGroup(votersSize, partySize, votersGroup);
	print(votersSize, votersGroup);
	statisticProvider(votersSize, partySize, votersGroup);

	for (int currentRuns = 0; currentRuns < runs; currentRuns++) {
		convincer(votersSize, votersGroup, countConvinces);

		if (currentRuns % printSteps == 0) {
			print(votersSize, votersGroup);
			statisticProvider(votersSize, partySize, votersGroup);
			std::cout << "Current runs: " << currentRuns << "\n";
			Sleep(10);

		#ifdef CONSOLECOMMANDS
			clear_screen();
		#else
			system("CLS");
		#endif // CONSOLECOMMANDS
		}
	}

#ifdef CONSOLECOMMANDS
	pause(prompt);
#else
	system("PAUSE");
#endif

	return 0;
}

int randomNumGenerator(int randomRange) {
	int randomNumber = rand() % randomRange;
	return randomNumber;
}

void createVotersGroup(int votersSize, int partySize, int votersGroup[]) {
	for (int counter = 0; counter < votersSize; counter++) {
		votersGroup[counter] = randomNumGenerator(partySize);
	}
}

void clear_screen() {
#ifdef _WIN32
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };
	DWORD count;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

	SetConsoleCursorPosition(hStdOut, coord);
#endif //_WIN32
#ifdef __unix__
	system("clear");
#endif
}

void convincer(int votersSize, int votersGroup[], int countConvinces) {

	int i = randomNumGenerator(votersSize);

	int selector = randomNumGenerator(4);

	//std::cout << "\n" << selector << "\n";

	switch (selector) {
	case 0: {	//links verschieben
		if (i % int(sqrt(votersSize)) == 0) {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i + (int(sqrt(votersSize)) - 1);
				//std::cout << "\n" << temp << "\n";
				votersGroup[i + (int(sqrt(votersSize)) - 1)] = votersGroup[i]; // +19 bei 400 voters
				countConvinces++;
			}
		}
		else {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i - 1;
				//std::cout << "\n" << temp << "\n";
				votersGroup[i - 1] = votersGroup[i];
				countConvinces++;
			}
		}
		break;
	}

	case 1: {	//rechtsverschieben
		if ((i + 1) % int(sqrt(votersSize)) == 0) {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i - (int(sqrt(votersSize)) - 1);
				//std::cout << "\n" << temp << " -19" << "\n";
				votersGroup[i - (int(sqrt(votersSize)) - 1)] = votersGroup[i]; // -19 bei 400 voters
				countConvinces++;
			}
		}
		else {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i + 1;
				//std::cout << "\n" << temp <<  "\n";
				votersGroup[i + 1] = votersGroup[i];
				countConvinces++;
			}
		}
		break;
	}

	case 2: {	//nach oben verschieben
		if (i <= int(sqrt(votersSize) - 1)) {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i + ((votersSize - 1) - (int(sqrt(votersSize)) - 1));
				//std::cout << "\n" << temp << "\n";
				votersGroup[i + ((votersSize - 1) - (int(sqrt(votersSize)) - 1))] = votersGroup[i]; // +380
				countConvinces++;
			}
		}
		else {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i - int(sqrt(votersSize));
				//std::cout << "\n" << temp << "\n";
				votersGroup[i - int(sqrt(votersSize))] = votersGroup[i];
				countConvinces;
			}
		}
		break;
	}

	case 3: {	//nach unten verschieben
		if (i >= (votersSize - 1) - (int(sqrt(votersSize)) - 1)) {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i - ((votersSize - 1) - (int(sqrt(votersSize)) - 1));
				//std::cout << "\n"  << temp << "\n";
				votersGroup[i - ((votersSize - 1) - (int(sqrt(votersSize)) - 1))] = votersGroup[i];
				countConvinces++;
			}
		}
		else {
			int ran = randomNumGenerator(2);
			if (ran == 0) {
				int temp = i + int(sqrt(votersSize));
				//std::cout << "\n" << temp << "\n";
				votersGroup[i + int(sqrt(votersSize))] = votersGroup[i];
				countConvinces++;
			}
		}
		break;
	}
	}
}

void print(int votersSize, int votersGroup[]) {
	std::string output = "";
	for (int i = 0; i < votersSize; i++) {
		output.append(std::to_string(votersGroup[i]) + " ");
		if ((i + 1) % int(sqrt(votersSize)) == 0) {
			output.append("\n");
		}
	}
	std::cout << output;
}

void statisticProvider(int votersSize, int partySize, int votersGroup[]) {
	std::cout << "\n";
	std::string statisitcMap = "";
	int votersPerParty = 0;
	std::string spaceFormat = "";
	for (int partyCounter = 0; partyCounter < partySize; partyCounter++) {
		for (int votersCounter = 0; votersCounter < votersSize; votersCounter++) {
			if (votersGroup[votersCounter] == partyCounter)
				votersPerParty++;
		}
		if (votersPerParty < 100) {
			spaceFormat += " "; //create spaces so votersPerParty will stay in column
		}
		statisitcMap += "Amount of [" + std::to_string(partyCounter) + "] = " + spaceFormat + std::to_string(votersPerParty) + "\n";
		votersPerParty = 0; //reset to 0
		spaceFormat = "";	//reset to empty
	}
	std::cout << statisitcMap;
}

#ifdef max	//	windows.h library defines a function-like macro with the name of max()
#define _TEMP_MACRO_ max	//	store the predefined macro in a new one
#undef max	//	undefine the problamatic macro.
#endif
void pause(const char* prompt) {
	std::cin.clear(); // clear failed/error states of the stream if they are set

	if (std::cin.rdbuf()->in_avail()) // if there are any characters in the input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // throw them away

	std::cout << prompt;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

#ifdef _Temp_MACRO_
#define max _TEMP_MACRO_	// restore the max() macro.
#undef _TEMP_MACRO_	// undefine the temporary macro.
#endif
