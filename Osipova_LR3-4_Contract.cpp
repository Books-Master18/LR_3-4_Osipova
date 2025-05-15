#include <string>
#include <ctime>
#include <random>
#include <iomanip>
#include "Osipova_LR3-4_Methods.h"
#include "Osipova_LR3-4_Contract.h" 
#include <sstream>

using namespace std;


string generate_random_date_first() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> year_dist(2020, 2024);
    uniform_int_distribution<> month_dist(1, 12);
    uniform_int_distribution<> day_dist(1, 28);

    int year = year_dist(generator);
    int month = month_dist(generator);
    int day = day_dist(generator);

    char buffer[20];
    sprintf(buffer, "%04d-%02d-%02d", year, month, day);

    return string(buffer);
}

string generate_random_string(int length) {
    string result;
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist('A', 'Z');

    for (int i = 0; i < length; ++i) {
        result += static_cast<char>(dist(generator));
    }
    return result;
}


// Конструктор по умолочанию
Contract::Contract() :
    side1(generate_random_string(1)),       // Случайная сторона 1
    side2(generate_random_string(1)),       // Случайная сторона 2
    signingDate(generate_random_date_first()),    // Случайная дата подписания
    duration(rand() % 365 + 30)  // Случайный срок действия от 30 до 394 дней
    {
        reSigningDates.resize(rand() % 3 + 2);
        generate(reSigningDates.begin(), reSigningDates.end(), [&]() { return generate_random_date_first(); });
    }

// Конструктор копирования+
Contract::Contract(const Contract& other) :
side1(other.side1), side2(other.side2), signingDate(other.signingDate), duration(other.duration),
    reSigningDates(other.reSigningDates) {}

//Оператор присваивания+
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


//Префиксный инкремент+
Contract& Contract::operator++() {
    duration+=10;
    return *this;
}

//Постфиксный инкремент+
Contract Contract::operator++(int) {
    Contract temp = *this;
    ++(*this);
    return temp;
}

Contract operator+(const Contract& contr1, const Contract& contr2) {
    Contract result = contr1; // Создаем копию первого контракта

    // Объединяем стороны договора
    result.side1 = result.side1 + " & " + contr2.side1;
    result.side2 = result.side2 + " & " + contr2.side2;

    // Объединяем срок действия
    result.duration += contr2.duration;

    // Объединяем даты переподписания (используем insert для добавления элементов из c2.reSigningDates в result.reSigningDates)
    result.reSigningDates.insert(result.reSigningDates.end(), contr2.reSigningDates.begin(), contr2.reSigningDates.end());

    return result;
}

//вывод+
ostream& operator<<(ostream& os, const Contract& contract) {
    // os << "Номер договора: " << contract.numcontract << endl;
    os << "Сторона 1: " << contract.side1 << endl;
    os << "Сторона 2: " << contract.side2 << endl;
    os << "Дата подписания: " << contract.signingDate << endl;
    os << "Продолжительность: " << contract.duration << " дней" << endl;
    os << "Даты переподписания: ";
    for (const auto& date : contract.reSigningDates) {
        os << date << " ";
    }
    os << endl;
    return os;
}

//ввод+
istream& operator>>(istream& is, Contract& contract) {
    // enterNumber(contract.numcontract, "Введите номер договора: ");
    enterString(contract.side1, "Введите сторону 1: ");
    enterString(contract.side2, "Введите сторону 2: ");
    enterDate(contract.signingDate, "Введите дату подписания (YYYY-MM-DD): ");
    enterNumber(contract.duration, "Введите срок действия (дни): ");

    contract.reSigningDates.clear();
    int numReSigningDates;
    enterNumber(numReSigningDates, "Сколько дат переподписания вы хотите добавить?");

    for (int i = 0; i < numReSigningDates; ++i) {
        string date;
        cout << "Дата переподписания № " << i + 1 <<endl;
        enterDate(contract.signingDate, "Введите дату переподписания");
        cout<<endl;
        contract.reSigningDates.push_back(date);
    }
    return is;
}