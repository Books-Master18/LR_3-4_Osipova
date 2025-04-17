#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include "Osipova_LR3-4_Methods.h"

using namespace std;

// Конструктор по умолчанию
// Contract::Contract() : side1("Сторона1"), side2("Сторона2"), signingDate("2023-01-01"), duration(365) {}


// Конструктор по умолчанию

Contract::Contract() {
    // Initialize random number generator (use a static instance for the class)
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Generate random values
    std::string sides[] = {"Сторона A", "Сторона B", "Сторона C", "Сторона D", "Сторона E"};
    std::uniform_int_distribution<> side_dist(0, 5); // Choose from 0 to 5
    side1 = sides[side_dist(gen)];
    side2 = sides[side_dist(gen)];


    // Generate a random date within a year
    std::uniform_int_distribution<> year_dist(2023, 2024);
    std::uniform_int_distribution<> month_dist(1, 12);
    std::uniform_int_distribution<> day_dist(1, 28); // Basic:  Avoiding out-of-range dates. can be improved.

    signingDate = std::to_string(year_dist(gen)) + "-" +
                  (month_dist(gen) < 10 ? "0" : "") + std::to_string(month_dist(gen)) + "-" +
                  (day_dist(gen) < 10 ? "0" : "") + std::to_string(day_dist(gen));


    // Generate random duration
    std::uniform_int_distribution<> duration_dist(30, 1000);
    duration = duration_dist(gen);

    // Generate random reSigningDates (example: 0 to 3 dates)
    int numReSignings = 1 + rand() % 3; //0 to 2 dates
    reSigningDates.clear();
    for (int i = 0; i < numReSignings; ++i) {
        std::uniform_int_distribution<> day_offset_dist(1, 365);
        int dayOffset = day_offset_dist(gen);

        //Create a new date based on the signing date.
        std::tm t{};
        std::istringstream ss(signingDate);
        ss >> std::get_time(&t, "%Y-%m-%d");

        if(ss.fail()){
             std::cerr << "Ошибка при генерации.\n";
             continue; // Skip this re-signing date
        }
        std::time_t signingTime = mktime(&t); // Convert to time_t

        std::time_t reSigningTime = signingTime + (dayOffset * 24 * 60 * 60); //Offset.
        std::tm* reSigningTm = std::localtime(&reSigningTime);

        std::stringstream reSigningSs;
        reSigningSs << std::put_time(reSigningTm, "%Y-%m-%d");
        reSigningDates.push_back(reSigningSs.str());
    }
}


// Констроктор, заданный параметрически
Contract::Contract(const std::string& p1, const std::string& p2, const std::string& date, int dur) :
side1(p1), side2(p2), signingDate(date), duration(dur) {}

// Конструктор копирования
Contract::Contract(const Contract& other) :
side1(other.side1), side2(other.side2), signingDate(other.signingDate), duration(other.duration),
    reSigningDates(other.reSigningDates) {}

// конструктор преобразования
Contract::Contract(const std::string& contractString) {
    // Implement parsing logic here (example)
    side1 = "Первая сторона"; 
    side2 = "Вторая сторона"; 
    signingDate = "2024-01-01";     
    duration = 365;              
}

// Метод вывода информации
void Contract::displayContract() const {
    cout << "Сторона 1: " << side1 << endl;
    cout << "Сторона 2: " << side2 << endl;
    cout << "Дата подписания: " << signingDate << std::endl;
    std::cout << "Срок действия: " << duration << " дней" << std::endl;
    std::cout << "Даты переподписания:" << std::endl;
    for (const auto& date : reSigningDates) {
        std::cout << "  " << date << std::endl;
    }
}

// std::string calculateAverageReSigningDate(const std::vector<Contract>& contracts) {
//     if (contracts.empty()) {
//         return "No contracts to calculate average re-signing date.";
//     }

//     int totalYears = 0;
//     int totalMonths = 0;
//     int totalDays = 0;
//     int totalDates = 0;

//     for (const auto& contract : contracts) {
//         const auto& reSigningDates = contract.getReSigningDates();
//         for (const auto& date : reSigningDates) {
//             int year, month, day;
//             char dash1, dash2;
//             std::stringstream ss(date);

//             if (ss >> year >> dash1 >> month >> dash2 >> day && dash1 == '-' && dash2 == '-') {
//                 totalYears += year;
//                 totalMonths += month;
//                 totalDays += day;
//                 totalDates++;
//             } else {
//                 std::cerr << "Invalid date format: " << date << std::endl;
//             }
//         }
//     }

//     if (totalDates == 0) {
//         return "No valid re-signing dates found in contracts.";
//     }

//     int averageYear = totalYears / totalDates;
//     int averageMonth = totalMonths / totalDates;
//     int averageDay = totalDays / totalDates;

//     // Нормализация: приведение месяца и дня к допустимым значениям
//     while (averageMonth > 12) {
//         averageYear++;
//         averageMonth -= 12;
//     }

//     // Внимание: упрощенный подход, не учитывающий количество дней в каждом месяце и високосные годы
//     while (averageDay > 30) {
//         averageMonth++;
//         averageDay -= 30;
//         if (averageMonth > 12) {
//             averageYear++;
//             averageMonth -= 12;
//         }
//     }

//     // Форматирование результата
//     std::stringstream result;
//     result << std::setw(4) << std::setfill('0') << averageYear << "-"
//            << std::setw(2) << std::setfill('0') << averageMonth << "-"
//            << std::setw(2) << std::setfill('0') << averageDay;

//     return result.str();
// }

// Function to sort contracts by signing date
std::vector<Contract> sortContractsBySigningDate(const std::vector<Contract>& contracts) 
{
    std::vector<Contract> sortedContracts = contracts;
    std::sort(sortedContracts.begin(), sortedContracts.end(), [](const Contract& a, const Contract& b) {
        return a.getSigningDate() < b.getSigningDate();
    });
    return sortedContracts;
}


// перегруженные операции 

// Сравнение по дате подписания
bool Contract::operator<(const Contract& other) const {
    return signingDate < other.signingDate;
}

// Addition (combines reSigningDates)
Contract Contract::operator+(const Contract& other) const {
    Contract result(*this);  // Copy the current object
    result.reSigningDates.insert(result.reSigningDates.end(), other.reSigningDates.begin(), other.reSigningDates.end());
    return result;
}
//Substraction
Contract Contract::operator-(const Contract& other) const {
	Contract result(*this);
	result.duration = this->duration - other.duration;
    return result;
}

//Multiplication
Contract Contract::operator*(const Contract& other) const {
	Contract result(*this);
	result.duration = this->duration * other.duration;
    return result;
}
// Prefix increment (increase duration)
Contract& Contract::operator++() {
    duration++;
    return *this;
}

// Postfix increment (increase duration)
Contract Contract::operator++(int) {
    Contract temp = *this;
    duration++;
    return temp;
}
// Prefix decrement (decrease duration)
Contract& Contract::operator--() {
    duration--;
    return *this;
}

// Postfix decrement (decrease duration)
Contract Contract::operator--(int) {
    Contract temp = *this; // Создаем копию текущего объекта для возврата
    duration--;             // Уменьшаем значение duration у текущего объекта
    return temp;            // Возвращаем копию объекта, сделанную до уменьшения
}
// Assignment operator
Contract& Contract::operator=(const Contract& other) {
    if (this != &other) {
        side1 = other.side1;
        side2 = other.side2;
        signingDate = other.signingDate;
        duration = other.duration;
        reSigningDates = other.reSigningDates;
    }
    return *this;
}


std::string& Contract::operator[](int index){
		if(index == 0) return side1;
		if(index == 1) return side2;
		return side1;
}
//// Дружественные методы вывода объекта класса на консоль
std::ostream& operator<<(std::ostream& os, const Contract& contract) {
    os << "Сторона 1: " << contract.side1 << "\n";
    os << "Сторона 2: " << contract.side2 << "\n";
    os << "Дата первого подписания: " << contract.signingDate << "\n";
    os << "Срок действия: " << contract.duration << " дней\n";
    os << "Даты переподписания: ";
    for (const auto& date : contract.reSigningDates) {
        os << date << " ";
    }
    os << "\n";
    return os;
}

 // Дружественные методы ввода объекта класса на консоль
std::istream& operator>>(std::istream& is, Contract& contract) {
        std::cout << "Введите сторону 1: ";
        std::getline(is >> std::ws, contract.side1); // To read the entire name

        std::cout << "Введите сторону 2: ";
        std::getline(is >> std::ws, contract.side2);

        std::cout << "Введите дату 1 подписания (ГГГГ-ММ-ДД): ";
        std::getline(is >> std::ws, contract.signingDate); // Read the signing date

        std::cout << "Введите строк действия (в днях): ";
        is >> contract.duration; // Read the duration

        std::cout << "Введите даты переподписания (ГГГГ-ММ-ДД): ";
         std::string date;
          std::cin>>date;
           contract.reSigningDates.push_back(date);
       
        return is;
}

