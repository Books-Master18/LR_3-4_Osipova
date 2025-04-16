#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <functional>
#include "Osipova_LR3-4_Methods.h"

using namespace std;

// Конструктор по умолчанию
Contract::Contract() : side1("Сторона1"), side2("Сторона2"), signingDate("2023-01-01"), duration(365) {}

// онстроктор, заданный параметрически
Contract::Contract(const std::string& p1, const std::string& p2, const std::string& date, int dur) :
side1(p1), side2(p2), signingDate(date), duration(dur) {}

// Конструктор копирования
Contract::Contract(const Contract& other) :
side1(other.side1), side2(other.side2), signingDate(other.signingDate), duration(other.duration),
    reSigningDates(other.reSigningDates) {}

// конструктор преобразования
Contract::Contract(const std::string& contractString) {
    // Implement parsing logic here (example)
    side1 = "Первая сторона"; // Placeholder, replace with parsing
    side2 = "Вторая сторона"; // Placeholder, replace with parsing
    signingDate = "2024-01-01";     // Placeholder, replace with parsing
    duration = 365;              // Placeholder, replace with parsing
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

// перегруженные операции 
void enterNumber(int& choice, const std::string& prompt) {
    std::cout << prompt << ": ";
    std::cin >> choice;
    std::cin.ignore(); // Clear the input buffer
}
// Comparison by signing date
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

// // Дружественные методы ввода объекта класса на консоль
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

// Function to sort contracts by signing date
std::vector<Contract> sortContractsBySigningDate(const std::vector<Contract>& contracts) 
{
    std::vector<Contract> sortedContracts = contracts;
    std::sort(sortedContracts.begin(), sortedContracts.end(), [](const Contract& a, const Contract& b) {
        return a.getSigningDate() < b.getSigningDate();
    });
    return sortedContracts;
}
