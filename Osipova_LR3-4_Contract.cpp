#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include "Osipova_LR3-4_Contract.h" 

using namespace std;

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
Contract::Contract(const std::string& p1, const string& p2, const string& date, int dur) :
side1(p1), side2(p2), signingDate(date), duration(dur) {}

// Конструктор копирования
Contract::Contract(const Contract& other) :
side1(other.side1), side2(other.side2), signingDate(other.signingDate), duration(other.duration),
    reSigningDates(other.reSigningDates) {}

// конструктор преобразования
Contract::Contract(const string& contractString) {
    std::stringstream ss(contractString);
    std::string token;

    // Попытка извлечь данные из строки, разделитель - запятая (,)
    // Пример входной строки: "Сторона1,Сторона2,2024-10-27,365"

    // 1. side1
    if (std::getline(ss, token, ',')) {
        side1 = token;
    } else {
        side1 = "Неизвестная сторона 1"; // или выбросить исключение
        std::cerr << "Ошибка: Не удалось извлечь side1 из строки: " << contractString << std::endl;
    }

    // 2. side2
    if (std::getline(ss, token, ',')) {
        side2 = token;
    } else {
        side2 = "Неизвестная сторона 2"; // или выбросить исключение
         std::cerr << "Ошибка: Не удалось извлечь side2 из строки: " << contractString << std::endl;
    }

    // 3. signingDate
    if (std::getline(ss, token, ',')) {
        signingDate = token;
        // Дополнительная проверка формата даты может быть добавлена здесь
    } else {
        signingDate = "2000-01-01"; // или выбросить исключение
         std::cerr << "Ошибка: Не удалось извлечь signingDate из строки: " << contractString << std::endl;
    }

    // 4. duration
    if (std::getline(ss, token, ',')) {
         try {
            duration = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
             duration = 0; // Или другое значение по умолчанию
             std::cerr << "Ошибка: Не удалось преобразовать duration в число из строки: " << contractString << std::endl;
        }
        catch (const std::out_of_range& e) {
             duration = 0; // Или другое значение по умолчанию
             std::cerr << "Ошибка: duration выходит за пределы диапазона из строки: " << contractString << std::endl;
        }
    } else {
        duration = 0; // или выбросить исключение
         std::cerr << "Ошибка: Не удалось извлечь duration из строки: " << contractString << std::endl;
    }
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

// Function to sort contracts by signing date
std::vector<Contract> sortContractsBySigningDate(const vector<Contract>& contracts) {
    std::vector<Contract> sortedContracts = contracts;
    std::sort(sortedContracts.begin(), sortedContracts.end(), [](const Contract& a, const Contract& b) {
        return a.getSigningDate() < b.getSigningDate();
    });
    return sortedContracts;
}


// Function to display sorted contracts
void displaySortedContracts(const vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет контрактов для отображения.\n";
        return;
    }

    std::vector<Contract> sortedContracts = sortContractsBySigningDate(contracts); // Sort the contracts

    std::cout << "--- Отсортированные контракты (по дате подписания) ---\n";
    for (const auto& contract : sortedContracts) {
        std::cout << contract << std::endl; // Предполагается, что оператор << перегружен для Contract
        std::cout << "--------------------\n";
    }
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


string& Contract::operator[](int index){


		if(index == 0) return side1;
		if(index == 1) return side2;
		return side1;
}


ostream& operator<<(ostream& os, const Contract& contract) {
    os << "Сторона 1: " << contract.side1 << std::endl;
    os << "Сторона 2: " << contract.side2 << std::endl;
    os << "Дата подписания: " << contract.signingDate << std::endl;
    os << "Продолжительность: " << contract.duration << " дней" << std::endl;
    os << "Даты переподписания: ";
    for (const auto& date : contract.reSigningDates) {
        os << date << " ";
    }
    os << std::endl;
    return os;
}


istream& operator>>(istream& is, Contract& contract) {
    cout << "Введите сторону 1: ";
    getline(is, contract.side1);

    cout << "Введите сторону 2: ";
    getline(is, contract.side2);

    cout << "Введите дату подписания (ГГГГ-MM-ДД): ";
    getline(is, contract.signingDate);

    cout << "Введите продолжительность (дни): ";
    is >> contract.duration;
    is.ignore(); // Consume newline after reading duration

    // Get re-signing dates
    contract.reSigningDates.clear(); // Clear previous dates
    int numReSigningDates;
    cout << "Сколько дат переподписания вы хотите добавить? ";
    is >> numReSigningDates;
    is.ignore(); // Consume newline after reading number of dates

    for (int i = 0; i < numReSigningDates; ++i) {
        string date;
        cout << "Введите дату переподписания №" << i + 1 << ": ";
        getline(is, date);
        contract.addReSigningDate(date);
    }

    return is;
}

