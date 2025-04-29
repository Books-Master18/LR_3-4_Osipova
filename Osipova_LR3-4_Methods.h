#ifndef METHODS_H
#define METHODS_H

#include "Osipova_LR3-4_Contract.h" 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <limits>  // Для numeric_limits

// Определение глобального вектора 
std::vector<Contract> allContracts;

// Прототипы функций для проверки вводимых данных
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


// реализация проверки вводимых данных
std::string enterString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

std::string enterDate(const std::string& prompt) {
    std::string date;
    std::cout << prompt;
    std::cin >> date;
    std::cin.ignore(); // Очистить буфер ввода после cin >> date
    return date;
}

int enterInteger(const std::string& prompt) {
    int num;
    std::cout << prompt;
    std::cin >> num;
    std::cin.ignore(); // Очистить буфер ввода после cin >> num
    return num;
}


void enterNumber(int& choice, const std::string& prompt) {
    std::cout << prompt << ": ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the input buffer
    if (std::cin.fail()) {
        std::cerr << "Ошибка ввода!  Пожалуйста, введите число.\n";
        std::cin.clear(); // Сбрасываем флаги ошибок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер
        choice = -1; // или какое-то другое значение по умолчанию или флаг ошибки
        return; // Выходим из функции
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
}



// Реализации функций, методов и т. д.

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
    std::string side1 = enterString("Введите сторону 1 (Нужно написать только название на англ.): ");
    std::string side2 = enterString("Введите сторону 2 (Нужно написать только название на англ.): ");
    std::string signingDate = enterDate("Введите дату подписания за период от 2006 до 2025 гг. (ГГГГ-MM-ДД): ");
    int duration = enterInteger("Введите продолжительность (дни): ");

    Contract newContract(side1, side2, signingDate, duration);

    // Добавление дат переподписания (необязательно)
    int numReSigningDates;
    std::cout << "Сколько дат переподписания вы хотите добавить? (0 если не нужно): ";
    std::cin >> numReSigningDates;
    std::cin.ignore();

    for (int i = 0; i < numReSigningDates; ++i) {
        std::string reSigningDate = enterDate("Введите дату переподписания №" + std::to_string(i + 1) + ": ");
        newContract.addReSigningDate(reSigningDate); // Теперь используем addReSigningDate
    }

    contracts.push_back(newContract);
    std::cout << "Контракт успешно добавлен!\n";
}

void displayAllContracts(const std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет данных для отображения.\n";
        return;
    }

    std::cout << "--- Все данные контрактов ---\n";
    for (const auto& contract : contracts) {
        std::cout << contract << std::endl; 
        std::cout << "--------------------\n";
    }
}


// Функция для вычисления средней даты переподписания для всех контрактов
void calculateAverageReSigningDate(const std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет контрактов для вычисления средней даты переподписания.\n";
        return;
    }

    std::vector<std::string> allReSigningDates;
    for (const auto& contract : contracts) {
        std::vector<std::string> contractReSigningDates = contract.getReSigningDates();
        allReSigningDates.insert(allReSigningDates.end(), contractReSigningDates.begin(), contractReSigningDates.end());
    }

    if (allReSigningDates.empty()) {
        std::cout << "Нет дат переподписания для вычисления средней даты.\n";
        return;
    }

    time_t totalTime = 0;
    int validDateCount = 0;

    for (const auto& dateStr : allReSigningDates) {
        std::tm t{};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&t, "%Y-%m-%d");

        if (!ss.fail()) {
            totalTime += mktime(&t);
            validDateCount++;
        } else {
            std::cerr << "Ошибка даты: " << dateStr << std::endl;
        }
    }

    if (validDateCount == 0) {
        std::cout << "Нет корректных дат переподписания для вычисления средней даты.\n";
        return;
    }

    time_t averageTime = totalTime / validDateCount;
    std::tm* timeinfo = localtime(&averageTime);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    std::cout << "Средняя дата переподписания для всех контрактов: " << buffer << std::endl;
}

#endif