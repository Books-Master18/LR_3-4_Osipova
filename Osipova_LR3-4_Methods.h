#ifndef METHODS_H
#define METHODS_H

// Include the Contract header
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <iomanip>
#include "Osipova_LR3-4_Contract.h" 

// описание глобального вектора объектов классов; 
extern std::vector<Contract> allContracts;

// Function prototypes for input validation
bool isValidString(const std::string& str);
bool isValidInteger(const std::string& str);
bool isValidDate(const std::string& date);

// Function prototypes for input with validation
std::string enterString(const std::string& prompt);
int enterInteger(const std::string& prompt);
std::string enterDate(const std::string& prompt);

// Function prototypes for allContract operations
void displayAllContracts();

void enterNumber(int& choice, const std::string& prompt); // Объявление enterNumber
// Function prototypes demonstrating class functionality
void demonstrateConstructors();
void demonstrateOperators();

// Implementation (Move implementation from .cpp here)
void createDefaultContract(std::vector<Contract>& contracts) {
    std::cout << "createDefaultContract called.\n";
}

void createParameterizedContract(std::vector<Contract>& contracts) {
    std::cout << "createParameterizedContract called.\n";
}

void createFullContract(std::vector<Contract>& contracts) {
    std::cout << "createFullContract called.\n";
}

void createContractFromConsole(std::vector<Contract>& contracts) {
    std::cout << "createContractFromConsole called.\n";
}

void displayAllContracts(std::vector<Contract>& contracts) {
    std::cout << "displayAllContracts called.\n";
}

void calculateAverageReSigningDate(std::vector<Contract>& contracts) {
    std::cout << "calculateAverageReSigningDate called.\n";
}

void sortContracts(std::vector<Contract>& contracts) {
    std::cout << "sortContracts called.\n";
}

void testContractFunctions(std::vector<Contract>& contracts) {
    std::cout << "testContractFunctions called.\n";
}

void testContractsMethod(std::vector<Contract>& contracts) {
    std::cout << "testContractsMethod called.\n";
}



// Implementations for input validation
inline bool isValidString(const std::string& str) {
    return !str.empty() && std::any_of(str.begin(), str.end(), [](char c){ return !std::isspace(c); });
}

inline bool isValidInteger(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    try {
        std::stoi(str);
        return true;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

inline bool isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    int year, month, day;
    try {
        year = std::stoi(date.substr(0, 4));
        month = std::stoi(date.substr(5, 2));
        day = std::stoi(date.substr(8, 2));
    } catch (const std::invalid_argument& ia) {
        return false;
    } catch (const std::out_of_range& oor) {
        return false;
    }
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) return false;
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29) return false;
        if (day == 29 && !isLeapYear) return false;
    }
    return true;
}

// Implementations for input with validation
inline std::string enterString(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt << ": ";
        std::getline(std::cin, input);
        if (isValidString(input)) {
            break;
        } else {
            std::cout << "Invalid input. Please enter a non-empty string.\n";
        }
    } while (true);
    return input;
}

inline int enterInteger(const std::string& prompt) {
    std::string input;
    int number;
    do {
        std::cout << prompt << ": ";
        std::getline(std::cin, input);
        if (isValidInteger(input)) {
            try {
                number = std::stoi(input);
                break;
            } catch (const std::out_of_range& oor) {
                std::cout << "Number out of range. Please enter a smaller number.\n";
            }
        } else {
            std::cout << "Invalid input. Please enter an integer.\n";
        }
    } while (true);
    return number;
}

inline std::string enterDate(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt << ": ";
        std::getline(std::cin, input);
        if (isValidDate(input)) {
            break;
        } else {
            std::cout << "Invalid date format. Please enter a date in YYYY-MM-DD format.\n";
        }
    } while (true);
    return input;
}
inline void displayAllContracts() {
    if (allContracts.empty()) {
        std::cout << "No contracts to display.\n";
        return;
    }
    for (size_t i = 0; i < allContracts.size(); ++i) {
        std::cout << "Contract " << i + 1 << ":\n" << allContracts[i] << "\n";
    }
    std::cout << "---------------------------\n";
}



std::vector<Contract> sortContractsBySigningDate(const std::vector<Contract>& contracts);

inline void demonstrateConstructors() {
    std::cout << "Demonstrating Constructors:" << std::endl;

        // Default constructor
        Contract c1;
        std::cout << "Default Constructor:" << std::endl << c1;

        // Parameterized constructor
        Contract c2("PartyA", "PartyB", "2023-10-26", 365);
        std::cout << "\nParameterized Constructor:" << std::endl << c2;

        // Copy constructor
        Contract c3(c2);
        std::cout << "\nCopy Constructor:" << std::endl << c3;

        // Conversion constructor
        Contract c4("PartyC,PartyD,2024-01-01,180");
        std::cout << "\nConversion Constructor:" << std::endl << c4;

        allContracts.push_back(c1);
        allContracts.push_back(c2);
        allContracts.push_back(c3);
        allContracts.push_back(c4);

        std::cout << "\nAll contracts created are now stored in the global vector 'allContracts'." << std::endl;

}

inline void demonstrateOperators() {
    if (allContracts.size() < 2) {
        std::cout << "Need at least two contracts in 'allContracts' to demonstrate operators.  Use menu option to create them first.\n";
        return;
    }

    std::cout << "\nDemonstrating Operators:" << std::endl;
    Contract& c1 = allContracts[0];
    Contract& c2 = allContracts[1];

    // GET и SET методы
    std::cout << "\n--- GET и SET методы ---" << std::endl;
    std::cout << "side1 (c1): " << c1.getside1() << std::endl;
    c1.setside1("Updated side1 c1");
    std::cout << "Updated side1 (c1): " << c1.getside1() << std::endl;

    std::cout << "side2 (c1): " << c1.getside2() << std::endl;
    c1.setside2("Updated side2 c1");
    std::cout << "Updated side2 (c1): " << c1.getside2() << std::endl;

    std::cout << "Signing Date (c1): " << c1.getSigningDate() << std::endl;
    c1.setSigningDate("2024-07-01");
    std::cout << "Updated Signing Date (c1): " << c1.getSigningDate() << std::endl;

    std::cout << "Duration (c1): " << c1.getDuration() << std::endl;
    c1.setDuration(730);
    std::cout << "Updated Duration (c1): " << c1.getDuration() << std::endl;

    std::cout << "Re-signing Dates (c1):";
    for (const auto& date : c1.getReSigningDates()) {
        std::cout << " " << date;
    }
    std::cout << std::endl;
    c1.addReSigningDate("2025-01-01");
    std::cout << "Updated Re-signing Dates (c1):";
    for (const auto& date : c1.getReSigningDates()) {
        std::cout << " " << date;
    }
    std::cout << std::endl;



    // Оператор сравнения <
    std::cout << "\n--- Оператор сравнения < ---" << std::endl;

    if (c1 < c2) {
        std::cout << "c1 is earlier than c2" << std::endl;
    } else {
        std::cout << "c1 is not earlier than c2" << std::endl;
    }

    // Оператор сложения +
    std::cout << "\n--- Оператор сложения + ---" << std::endl;
    Contract c3 = c1 + c2;
    std::cout << "c1:\n" << c1 << std::endl;
    std::cout << "c2:\n" << c2 << std::endl;
    std::cout << "c1 + c2:\n" << c3 << std::endl;

    // Оператор префиксного инкремента ++
    std::cout << "\n--- Оператор префиксного инкремента ++ ---" << std::endl;
    std::cout << "Duration before ++c1: " << c1.getDuration() << std::endl;
    ++c1;
    std::cout << "Duration after ++c1: " << c1.getDuration() << std::endl;

    // Оператор постфиксного инкремента ++
    std::cout << "\n--- Оператор постфиксного инкремента ++ ---" << std::endl;
    std::cout << "Duration before c2++: " << c2.getDuration() << std::endl;
    Contract c4 = c2++;
    std::cout << "Duration after c2++: " << c2.getDuration() << std::endl;
    std::cout << "Duration of c4 (result of c2++): " << c4.getDuration() << std::endl;


}


#endif