#ifndef CONTRACT_H
#define CONTRACT_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Contract {
private:
    string side1; //сторона 1
    string side2; //сторона 2
    string signingDate; //дата подписания
    int duration; //срок действия
    vector<string> reSigningDates; //даты повторного подписания

public:
    // Конструкторы

    Contract();  // конструктор по умолчанию
    Contract(const string& s1, const string& s2, const string& date, int dur);  // Констроктор, заданный параметрически
    Contract(const Contract& other);  // Конструктор копирования

    // конструктор преобразования
    explicit Contract(const string& contractString);

    // Get-методы (inline)
    inline string getside1() const { return side1; }
    inline string getside2() const { return side2; }
    inline string getSigningDate() const { return signingDate; }
    inline int getDuration() const { return duration; }
    inline const vector<string>& getReSigningDates() const { return reSigningDates; }

    // Set-методы (inline)
    inline void setside1(const std::string& s1) { side1 = s1; }
    inline void setside2(const std::string& s2) { side2 = s2; }
    inline void setSigningDate(const std::string& date) { signingDate = date; }
    inline void setDuration(int dur) { duration = dur; }
    inline void addReSigningDate(const std::string& date) { reSigningDates.push_back(date); }

    // Метод вывода информации
    void displayContract() const;

    //Вычислить среднее даты переподписания


    std::string calculateAverageReSigningDate(const std::vector<Contract>& contracts);

    // Функция сортировки контрактов по дате подписания
    std::vector<Contract> sortContractsBySigningDate(const std::vector<Contract>& contracts);
    // void addReSigningDate(const std::string& date);

    // перегруженные операции 
    bool operator<(const Contract& other) const; // перегруженные операции сложения, вычитания, умножения, инкремента, декремента, индексирования, присваивания; 
    Contract operator+(const Contract& other) const; // перегруженные операции сложения
    Contract operator-(const Contract& other) const; // перегруженные операции вычитания
    Contract operator*(const Contract& other) const; // перегруженные операции умножения
    Contract& operator++(); // перегруженные операции префиксный инкремент
    Contract operator++(int); // перегруженные операции постфиксный инкремент 
    Contract& operator--();   // Префиксный декремент
    Contract operator--(int);    // Постфиксный декремент
    Contract& operator=(const Contract& other); // перегруженные операции присваивания
    std::string& operator[](int index); // перегруженные операции индексирования;

    // Дружественные методы ввода/вывода объекта класса на консоль
    friend std::ostream& operator<<(std::ostream& os, const Contract& contract);
    friend std::istream& operator>>(std::istream& is, Contract& contract);


    // деструктор
    virtual ~Contract() {}
};



#endif