#ifndef METHODS_H
#define METHODS_H

#include "Osipova_LR3-4_Contract.h" 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctime>
#include<sstream>
#include <iomanip>

// Определение глобального вектора 
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


// void addDataToContract(std::vector<Contract>& contracts) {
//     // Здесь должна быть реализация addDataToContract,
//     // которая принимает std::vector<Contract>& contracts
//     std::cout << "addDataToContract not implemented yet\n";
// }

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




// // Реализации операций

// inline void demonstrateConstructors() {
//     std::cout << "Demonstrating Constructors:" << std::endl;

//         // Default constructor
//         Contract c1;
//         std::cout << "Default Constructor:" << std::endl << c1;

//         // Parameterized constructor
//         Contract c2("PartyA", "PartyB", "2023-10-26", 365);
//         std::cout << "\nParameterized Constructor:" << std::endl << c2;

//         // Copy constructor
//         Contract c3(c2);
//         std::cout << "\nCopy Constructor:" << std::endl << c3;

//         // Conversion constructor
//         Contract c4("PartyC,PartyD,2024-01-01,180");
//         std::cout << "\nConversion Constructor:" << std::endl << c4;

//         allContracts.push_back(c1);
//         allContracts.push_back(c2);
//         allContracts.push_back(c3);
//         allContracts.push_back(c4);

//         std::cout << "\nAll contracts created are now stored in the global vector 'allContracts'." << std::endl;

// }

// //вызов конструктора по умолчанию
// void createDefaultContract(std::vector<Contract>&) {
//     Contract newContract; // Создает значения по умолчанию и случайные значения
//     allContracts.push_back(newContract);
//     std::cout << "Default contract created and added!\n";
// }

// // вызов параметризованного конструктора
// void createParameterizedContract() {
//     std::string side1 = enterString("Enter side 1");
//     std::string side2 = enterString("Enter side 2");
//     std::string signingDate = enterDate("Enter signing date (YYYY-MM-DD)");
//     int duration = enterInteger("Enter duration (days)");
//     Contract newContract(side1, side2, signingDate, duration);
//     allContracts.push_back(newContract);
//     std::cout << "Parameterized contract created and added!\n";
// }

// void createFullContract() {
//    Contract newContract;
//         std::cout << "Enter contract data using operator>>:\n";
//         std::cin >> newContract;
//         allContracts.push_back(newContract);
//         std::cout << "Full contract created and added!\n";
// }

// void createContractFromConsole()
// {
//     createParameterizedContract(); // This can be implemented as a duplicate to createParameterizedContract
// }

// //отображения всех объектов класса
// void displayAllContracts() {
//     if (allContracts.empty()) {
//         std::cout << "No contracts to display.\n";
//         return;
//     }

//     std::cout << "--- All Contracts ---\n";
//     for (const auto& contract : allContracts) {
//         std::cout << contract << std::endl; // Assumes << operator is overloaded
//         std::cout << "--------------------\n";
//     }
// }

// void calculateAverageReSigningDate() {
//     if (allContracts.empty()) {
//         std::cout << "No contracts to calculate average re-signing date.\n";
//         return;
//     }

//     std::cout << "Calculating the average re-signing date is not yet implemented.\n";
// }

// void addDataToContract() {
//     if (allContracts.empty()) {
//         std::cout << "Нет контрактов для добавления данных. Пожалуйста, сначала создайте контракты.\n";
//         return;
//     }

//     // Выводим список контрактов с номерами
//     std::cout << "Выберите контракт для изменения:\n";
//     for (size_t i = 0; i < allContracts.size(); ++i) {
//         std::cout << i + 1 << ": " << allContracts[i].getside1() << " - " << allContracts[i].getside2() << "\n"; // Пример вывода, можно изменить
//     }

//     // Запрашиваем номер контракта у пользователя
//     int choice;
//     std::cout << "Введите номер контракта: ";
//     std::cin >> choice;
//     std::cin.ignore(); // Пропускаем символ новой строки

//     // Проверяем корректность ввода
//     if (choice < 1 || choice > allContracts.size()) {
//         std::cout << "Некорректный номер контракта.\n";
//         return;
//     }

//     // Получаем выбранный контракт (индекс на 1 меньше введенного номера)
//     Contract& selectedContract = allContracts[choice - 1];

//     // Предлагаем пользователю ввести новые данные для контракта
//     std::cout << "Введите новые данные для контракта:\n";
//     std::cin >> selectedContract; // Используем перегруженный оператор >> для ввода данных

//     std::cout << "Данные контракта обновлены.\n";
// }

// void sortContracts() {
//      if (allContracts.empty()) {
//         std::cout << "No contracts to sort.\n";
//         return;
//     }
//     std::sort(allContracts.begin(), allContracts.end());
//     std::cout << "Contracts sorted by signing date.\n";
// }

// void testContractFunctions() {
//      if (allContracts.size() < 2) {
//         std::cout << "Need at least 2 contracts to test functions. Create some first.\n";
//         return;
//     }
//      Contract contract1 = allContracts[0];
//     Contract contract2 = allContracts[1];

//     // Example using overloaded operators
//     std::cout << "contract1 + contract2:\n" << (contract1 + contract2) << std::endl;

//     std::cout << "contract1 - contract2 (Duration): " << (contract1 - contract2).getDuration() << std::endl;

//      std::cout << "contract1 * contract2 (Duration): " << (contract1 * contract2).getDuration() << std::endl;

//     // Example using []
//     std::cout << "contract1[0] (Side 1): " << contract1[0] << std::endl;
// }

// void testContractsMethod() {
//      if (allContracts.empty()) {
//         std::cout << "No contracts to test a method on.\n";
//         return;
//     }
//     //Demonstration of calling methods from Osipova_LR3-4_Contract class
//         Contract contract = allContracts[0]; //get first contract
//         contract.displayContract();
// }


// std::vector<Contract> sortContractsBySigningDate(const std::vector<Contract>& contracts);



// inline void demonstrateOperators() {
//     if (allContracts.size() < 2) {
//         std::cout << "Need at least two contracts in 'allContracts' to demonstrate operators.  Use menu option to create them first.\n";
//         return;
//     }

//     std::cout << "\nDemonstrating Operators:" << std::endl;
//     Contract& c1 = allContracts[0];
//     Contract& c2 = allContracts[1];

//     // GET и SET методы
//     std::cout << "\n--- GET и SET методы ---" << std::endl;
//     std::cout << "side1 (c1): " << c1.getside1() << std::endl;
//     c1.setside1("Updated side1 c1");
//     std::cout << "Updated side1 (c1): " << c1.getside1() << std::endl;

//     std::cout << "side2 (c1): " << c1.getside2() << std::endl;
//     c1.setside2("Updated side2 c1");
//     std::cout << "Updated side2 (c1): " << c1.getside2() << std::endl;

//     std::cout << "Signing Date (c1): " << c1.getSigningDate() << std::endl;
//     c1.setSigningDate("2024-07-01");
//     std::cout << "Updated Signing Date (c1): " << c1.getSigningDate() << std::endl;

//     std::cout << "Duration (c1): " << c1.getDuration() << std::endl;
//     c1.setDuration(730);
//     std::cout << "Updated Duration (c1): " << c1.getDuration() << std::endl;

//     std::cout << "Re-signing Dates (c1):";
//     for (const auto& date : c1.getReSigningDates()) {
//         std::cout << " " << date;
//     }
//     std::cout << std::endl;
//     c1.addReSigningDate("2025-01-01");
//     std::cout << "Updated Re-signing Dates (c1):";
//     for (const auto& date : c1.getReSigningDates()) {
//         std::cout << " " << date;
//     }
//     std::cout << std::endl;



//     // Оператор сравнения <
//     std::cout << "\n--- Оператор сравнения < ---" << std::endl;

//     if (c1 < c2) {
//         std::cout << "c1 is earlier than c2" << std::endl;
//     } else {
//         std::cout << "c1 is not earlier than c2" << std::endl;
//     }

//     // Оператор сложения +
//     std::cout << "\n--- Оператор сложения + ---" << std::endl;
//     Contract c3 = c1 + c2;
//     std::cout << "c1:\n" << c1 << std::endl;
//     std::cout << "c2:\n" << c2 << std::endl;
//     std::cout << "c1 + c2:\n" << c3 << std::endl;

//     // Оператор префиксного инкремента ++
//     std::cout << "\n--- Оператор префиксного инкремента ++ ---" << std::endl;
//     std::cout << "Duration before ++c1: " << c1.getDuration() << std::endl;
//     ++c1;
//     std::cout << "Duration after ++c1: " << c1.getDuration() << std::endl;

//     // Оператор постфиксного инкремента ++
//     std::cout << "\n--- Оператор постфиксного инкремента ++ ---" << std::endl;
//     std::cout << "Duration before c2++: " << c2.getDuration() << std::endl;
//     Contract c4 = c2++;
//     std::cout << "Duration after c2++: " << c2.getDuration() << std::endl;
//     std::cout << "Duration of c4 (result of c2++): " << c4.getDuration() << std::endl;


// }


#endif