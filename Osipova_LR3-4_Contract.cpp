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
    static random_device rd;
    static mt19937 gen(rd());

    // Generate random sides ensuring they are different
    string sides[] = {"A", "B", "C", "D", "E"};
    uniform_int_distribution<> side_dist(0, 4);
    int side1_index = side_dist(gen);
    int side2_index;

    // Ensure side2 is different from side1
    do {
        side2_index = side_dist(gen);
    } while (side2_index == side1_index);

    side1 = sides[side1_index];
    side2 = sides[side2_index];

    // Generate a random date within a year
    uniform_int_distribution<> year_dist(2006, 2025); // диапазон годов
    uniform_int_distribution<> month_dist(1, 12);
    int year = year_dist(gen);
    int month = month_dist(gen);

    int day_max = 31;
    if (month == 2) {
        day_max = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        day_max = 30;
    }
    std::uniform_int_distribution<> day_dist(1, day_max);
    int day = day_dist(gen);
    // Format the date string (Corrected to use iomanip for formatting)
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << year << "-"
       << std::setfill('0') << std::setw(2) << month << "-"
       << std::setfill('0') << std::setw(2) << day;

    signingDate = ss.str();


    // Generate random duration
    std::uniform_int_distribution<> duration_dist(30, 1000);
    duration = duration_dist(gen);

    // Generate random reSigningDates (example: 0 to 3 dates)
    std::uniform_int_distribution<> num_re_signings_dist(0, 3);
    int numReSignings = num_re_signings_dist(gen); //0 to 3 dates
    reSigningDates.clear();
    for (int i = 0; i < numReSignings; ++i) {
        std::uniform_int_distribution<> day_offset_dist(1, 365);
        int dayOffset = day_offset_dist(gen);

        //Create a new date based on the signing date.
        std::tm t{};
        std::istringstream ss(signingDate);
        ss >> std::get_time(&t, "%Y-%m-%d");

        if (ss.fail()) {
            std::cerr << "Ошибка при генерации reSigningDate.\n";
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
Contract::Contract(const string& p1, const string& p2, const string& date, int dur) :
side1(p1), side2(p2), signingDate(date), duration(dur) {}

// Конструктор копирования
Contract::Contract(const Contract& other) :
side1(other.side1), side2(other.side2), signingDate(other.signingDate), duration(other.duration),
    reSigningDates(other.reSigningDates) {}

// конструктор преобразования
Contract::Contract(const string& contractString) {
    stringstream ss(contractString);
    string token;

    // Попытка извлечь данные из строки, разделитель - запятая (,)
    // Пример входной строки: "Сторона1,Сторона2,2024-10-27,365"

    // 1. side1
    if (getline(ss, token, ',')) {
        side1 = token;
    } else {
        side1 = "Неизвестная сторона 1"; // или выбросить исключение
        std::cerr << "Ошибка: Не удалось извлечь side1 из строки: " << contractString << endl;
    }

    // 2. side2
    if (getline(ss, token, ',')) {
        side2 = token;
    } else {
        side2 = "Неизвестная сторона 2"; // или выбросить исключение
         cerr << "Ошибка: Не удалось извлечь side2 из строки: " << contractString << endl;
    }

    // 3. signingDate
    if (getline(ss, token, ',')) {
        signingDate = token;
        // Дополнительная проверка формата даты может быть добавлена здесь
    } else {
        signingDate = "2000-01-01"; // или выбросить исключение
         cerr << "Ошибка: Не удалось извлечь signingDate из строки: " << contractString << endl;
    }

    // 4. duration
    if (getline(ss, token, ',')) {
         try {
            duration = stoi(token);
        }
        catch (const invalid_argument& e) {
             duration = 0; // Или другое значение по умолчанию
             cerr << "Ошибка: Не удалось преобразовать duration в число из строки: " << contractString << endl;
        }
        catch (const std::out_of_range& e) {
             duration = 0; // Или другое значение по умолчанию
             std::cerr << "Ошибка: duration выходит за пределы диапазона из строки: " << contractString << endl;
        }
    } else {
        duration = 0; // или выбросить исключение
         cerr << "Ошибка: Не удалось извлечь duration из строки: " << contractString << endl;
    }
}

// Метод вывода информации
void Contract::displayContract() const {
    cout << "Сторона 1: " << side1 << endl;
    cout << "Сторона 2: " << side2 << endl;
    cout << "Дата подписания: " << signingDate << endl;
    cout << "Срок действия: " << duration << " дней" << endl;
    cout << "Даты переподписания:" << endl;
    for (const auto& date : reSigningDates) {
        cout << "  " << date << endl;
    }
}

// Функция сортировки контрактов по дате подписания 
vector<Contract> sortContractsBySigningDate(const vector<Contract>& contracts) {
    vector<Contract> sortedContracts = contracts;
    sort(sortedContracts.begin(), sortedContracts.end(), [](const Contract& a, const Contract& b) {
        return a.getSigningDate() < b.getSigningDate();
    });
    return sortedContracts;
}

// Метод вычисления средней даты переподписания
std::string Contract::calculateAverageReSigningDate() const {
    if (reSigningDates.empty()) {
        return "Нет дат переподписания";
    }

    time_t totalTime = 0;
    for (const auto& dateStr : reSigningDates) {
        std::tm t{};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&t, "%Y-%m-%d");
        if (ss.fail()) {
            std::cerr << "Ошибка при парсинге даты: " << dateStr << std::endl;
            return "Ошибка при вычислении средней даты";
        }
        totalTime += mktime(&t);
    }

    time_t averageTime = totalTime / reSigningDates.size();
    std::tm* timeinfo = localtime(&averageTime);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

// Функция отображения отсортированных дат переподписания
void displaySortedContracts(const vector<Contract>& contracts) {

    if (contracts.empty()) {
        cout << "Нет контрактов для отображения.\n";
        return;
    }

    vector<Contract> sortedContracts = sortContractsBySigningDate(contracts); // Sort the contracts

    cout << "--- Отсортированные контракты (по дате подписания) ---\n";
    for (const auto& contract : sortedContracts) {
        cout << contract << endl; // Предполагается, что оператор << перегружен для Contract
        cout << "--------------------\n";
    }
}


// перегруженные операции 

//Оператор < для сравнения по средней дате
bool Contract::operator<(const Contract& other) const {
    std::tm tm1 = {};
    std::istringstream ss1(signingDate);
    ss1 >> std::get_time(&tm1, "%Y-%m-%d");

    std::tm tm2 = {};
    std::istringstream ss2(other.signingDate);
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");

    std::time_t time1 = mktime(&tm1);
    std::time_t time2 = mktime(&tm2);

    return time1 < time2;
}

//Оператор + для объединения сторон и сложения сроков действия
Contract Contract::operator+(const Contract& other) const {
    return Contract(this->side1 + " + " + other.side1,
        this->side2 + " + " + other.side2,
        this->signingDate,
        this->duration + other.duration);
}

//Префиксный инкремент
Contract& Contract::operator++() {
    duration++;
    return *this;
}

//Постфиксный инкремент
Contract Contract::operator++(int) {
    Contract temp = *this;
    ++(*this);
    return temp;
}


//Оператор присваивания
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


ostream& operator<<(ostream& os, const Contract& contract) {
    os << "Сторона 1: Сторона " << contract.side1 << std::endl;
    os << "Сторона 2: Сторона " << contract.side2 << std::endl;
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

