#ifndef METHODS_H
#define METHODS_H

#include "Osipova_LR3-4_Contract.h" 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include <iomanip>



// Определение глобального вектора (ОДИН раз в ОДНОМ .cpp файле!)
std::vector<Contract> allContracts;

// // Function prototypes for input validation
bool isValidString(const std::string& str) {
    return !str.empty() && std::any_of(str.begin(), str.end(), [](char c){ return !std::isspace(c); });
}

bool isValidInteger(const std::string& str) {
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

bool isValidDate(const std::string& date) {
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



// Реализации для ввода с проверкой
std::string enterString(const std::string& prompt) {
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

int enterInteger(const std::string& prompt) {
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

std::string enterDate(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt << ": ";
        std::getline(std::cin, input);
        if (isValidDate(input)) {
            break;
        } else {
            std::cout << "Неправильный ввод даты. Пожалуйста введите дату в формате ГГГГ-ММ-ДД.\n";
        }
    } while (true);
    return input;
}

void enterNumber(int& choice, const std::string& prompt) {
    std::cout << prompt << ": ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the input buffer
}

// Реализации функций
void createDefaultContract(std::vector<Contract>& contracts) {
    int numContracts;

    do {
        std::cout << "Введите сколько контрактов по умолчанию вы хотите создать (1-5): ";
        std::cin >> numContracts;
        std::cin.ignore(); // Очистить буфер ввода

        if (numContracts < 1 || numContracts > 5) {
            std::cout << "Пожалуйста, введите число от 1 до 5.\n";
        }
    } while (numContracts < 1 || numContracts > 5);

    for (int i = 0; i < numContracts; ++i) {
        Contract newContract;
        contracts.push_back(newContract);
        std::cout << "Контракт по умолчанию № " << i + 1 << " был создан!\n";
        std::cout << newContract << std::endl; // Вывод данных нового контракта
    }

}

void createParameterizedContract(std::vector<Contract>& contracts) {
    std::string side1 = enterString("Введите сторону 1: ");
    std::string side2 = enterString("Введите сторону 2: ");
    std::string signingDate = enterDate("Введите дату подписания (ГГГГ-MM-ДД): ");
    int duration = enterInteger("Введите продолжительность (дни) ");

    int numReSigningDates;
    std::cout << "Сколько дат переподписания вы хотите добавить: ";
    std::cin >> numReSigningDates;
    std::cin.ignore(); // Очистить буфер ввода

    Contract newContract(side1, side2, signingDate, duration);

    for (int i = 0; i < numReSigningDates; ++i) {
        std::string reSigningDate = enterDate("Введите дату переподписания №" + std::to_string(i + 1) + ": ");
        newContract.addReSigningDate(reSigningDate);
    }

    contracts.push_back(newContract); //  добавляем newContract в переданный вектор contracts
    std::cout << "Параметрический конструктор был создан и контракт добавлен!\n";
}

void displayAllContracts(const std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет данных для отображения.\n";
        return;
    }

    std::cout << "--- Все данные контрактов ---\n";
    for (const auto& contract : contracts) {
        std::cout << contract << std::endl; // Предполагается, что оператор << перегружен для Contract
        std::cout << "--------------------\n";
    }
}

void someFunction(std::vector<Contract>& contracts);

void addDataToContract(std::vector<Contract>& contracts) {
    // Здесь должна быть реализация addDataToContract,
    // которая принимает std::vector<Contract>& contracts
    std::cout << "addDataToContract not implemented yet\n";
}

void sortContracts(std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "No contracts to sort.\n";
        return;
    }
    std::sort(contracts.begin(), contracts.end());
    std::cout << "Contracts sorted by signing date.\n";
}

void testContractFunctions(std::vector<Contract>& contracts) {
    // Здесь должна быть реализация testContractFunctions,
    // которая принимает std::vector<Contract>& contracts
    std::cout << "testContractFunctions not implemented yet\n";
}

void testContractsMethod(std::vector<Contract>& contracts) {
    // Здесь должна быть реализация testContractsMethod,
    // которая принимает std::vector<Contract>& contracts
    std::cout << "testContractsMethod not implemented yet\n";
}


#endif