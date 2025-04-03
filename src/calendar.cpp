#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

// ANSI color codes
#define RESET  "\033[0m"
#define RED    "\033[31m"  // Red (Sunday)
#define ORANGE "\033[33m"  // Orange (Saturday)

// List of month names
const string monthNames[] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

std::pair<int, int> getTerminalSize() {
	struct winsize w;

	// Get terminal size
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		return {-1, -1}; // Return -1 if failed
	}

	return {w.ws_col, w.ws_row}; // (Width, Height)
}

// Function to get the number of days in a given month
int getDaysInMonth(int month, int year) {
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	// Leap year check (February has 29 days)
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
	}
	return daysInMonth[month - 1];
}

// Function to determine the first day of the month (0 = Sunday, 1 = Monday, etc.)
int getStartDayOfMonth(int year, int month) {
	struct tm timeStruct = {0};
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = 1;

	mktime(&timeStruct);
	return timeStruct.tm_wday;
}

// Function to print the calendar for a given month and year
void printMonth(int year, int month) {
	int daysInMonth = getDaysInMonth(month, year);
	int startDay = getStartDayOfMonth(year, month);

	cout << "\n  " << monthNames[month - 1] << " " << year << "\n";
	cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

	for (int i = 0; i < startDay; i++) {
		cout << "     ";
	}

	for (int day = 1; day <= daysInMonth; day++) {
		// Apply colors for Sundays (Red) and Saturdays (Orange)
		if ((startDay + day - 1) % 7 == 0) { // Sunday
			cout << RED << setw(5) << day << RESET;
		} else if ((startDay + day - 1) % 7 == 6) { // Saturday
			cout << ORANGE << setw(5) << day << RESET;
		} else {
			cout << setw(5) << day;
		}

		if ((startDay + day) % 7 == 0) {
			cout << endl;
		}
	}
	cout << endl;
}

// Function to convert month name (full or partial) to number (1-12)
int monthNameToNumber(string inputMonth) {
	transform(inputMonth.begin(), inputMonth.end(), inputMonth.begin(), ::tolower);

	for (int i = 0; i < 12; i++) {
		string lowerMonth = monthNames[i];
		transform(lowerMonth.begin(), lowerMonth.end(), lowerMonth.begin(), ::tolower);

		if (lowerMonth.find(inputMonth) == 0) {
			return i + 1; // Convert 0-based index to 1-based month
		}
	}
	return -1; // Invalid month
}

// Function to print help message
void printHelp() {
	cout << "Usage: cal [OPTIONS]\n";
	cout << "Options:\n";
	cout << "  -m, --month <month>   Specify month (number 1-12 or name)\n";
	cout << "  -y, --year <year>     Specify year (4-digit)\n";
	cout << "  -n <count>            Number of months to print (default: 1)\n";
	cout << "  -h, --help            Show this help message\n";
	cout << "Examples:\n";
	cout << "  cal                   Print current month\n";
	cout << "  cal -m March -y 2024  Print March 2024\n";
	cout << "  cal -m 10 -y 2023 -n 3  Print October-December 2023\n";
}

// Main function
int main(int argc, char* argv[]) {
	auto [width, height] = getTerminalSize();

	// Get current month and year as defaults
	time_t now = time(0);
	struct tm *current = localtime(&now);
	int month = current->tm_mon + 1;
	int year = current->tm_year + 1900;
	int numMonths = 1; // Default number of months to print

	// Parse command-line arguments
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			printHelp();
			return 0;
		}
		else if ((strcmp(argv[i], "--month") == 0 || strcmp(argv[i], "-m") == 0) && i + 1 < argc) {
			string monthArg = argv[i + 1];

			if (isdigit(monthArg[0])) { // If it's a number
				int tempMonth = atoi(monthArg.c_str());
				if (tempMonth >= 1 && tempMonth <= 12) {
					month = tempMonth;
				} else {
					cerr << "Invalid month number: " << monthArg << endl;
					return 1;
				}
			} else { // If it's a string (month name)
				int tempMonth = monthNameToNumber(monthArg);
				if (tempMonth != -1) {
					month = tempMonth;
				} else {
					cerr << "Invalid month name: " << monthArg << endl;
					return 1;
				}
			}
			i++;
		}
		else if ((strcmp(argv[i], "--year") == 0 || strcmp(argv[i], "-y") == 0) && i + 1 < argc) {
			int tempYear = atoi(argv[i + 1]);
			if (tempYear >= 1900 && tempYear <= 9999) {
				year = tempYear;
			} else {
				cerr << "Invalid year: " << argv[i + 1] << endl;
				return 1;
			}
			i++;
		}
		else if ((strcmp(argv[i], "-n") == 0) && i + 1 < argc) {
			int tempN = atoi(argv[i + 1]);
			if (tempN > 0 && tempN <= 12) { // Limit to a max of 12 months
				numMonths = tempN;
			} else {
				cerr << "Invalid number of months: " << argv[i + 1] << endl;
				return 1;
			}
			i++;
		}
	}

	// Print the requested months
	for (int i = 0; i < numMonths; i++) {
		printMonth(year, month);
		month++; // Move to the next month
		if (month > 12) { // Wrap around to next year
			month = 1;
			year++;
		}
	}

	return 0;
}
