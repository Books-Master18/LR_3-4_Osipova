#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include <vector>
#include <iostream>

class Contract {
private:
    std::string side1; // сторона 1
    std::string side2; // сторона 2
    std::string signingDate; // дата подписания
    int duration; // срок действия
    std::vector<std::string> reSigningDates; // даты повторного подписания

public:

    // Get-методы (inline)
    std::string getside1() const { return side1; }
    std::string getside2() const { return side2; }
    std::string getSigningDate() const { return signingDate; }
    int getDuration() const { return duration; }
    const std::vector<std::string>& getReSigningDates() const { return reSigningDates; }

    // Set-методы (inline)
    void setside1(const std::string& s1) { side1 = s1; }
    void setside2(const std::string& s2) { side2 = s2; }
    void setSigningDate(const std::string& date) { signingDate = date; }
    void setDuration(int dur) { duration = dur; }
    void setaddReSigningDates(const std::vector<std::string>& newDates); // Установка дат переподписания
    void addReSigningDate(const std::string& date); // Добавление одной даты



    // Конструкторы
    Contract();  // конструктор по умолчанию
    Contract(const std::string& s1, const std::string& s2, const std::string& date, int dur);  // Констроктор, заданный параметрически
    Contract(const Contract& other);  // Конструктор копирования
    explicit Contract(const std::string& contractString);  // Конструктор преобразования

    // Метод вывода информации
    void displayContract() const;


    
    // Метод вычисления средней даты переподписания
    std::string calculateAverageReSigningDate() const;
    // перегруженные операции 
    bool operator<(const Contract& other) const;
    Contract operator+(const Contract& other) const;
    Contract& operator++();
    Contract operator++(int);
    Contract& operator=(const Contract& other);

    // Дружественные методы ввода/вывода объекта класса на консоль
    friend std::ostream& operator<<(std::ostream& os, const Contract& contract);
    friend std::istream& operator>>(std::istream& is, Contract& contract);

    // деструктор
    ~Contract() {}
};

#endif