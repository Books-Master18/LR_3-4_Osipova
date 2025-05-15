#ifndef CONTRACT_H
#define CONTRACT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Contract {

    string side1; // сторона № 1
    string side2; // сторона №2
    string signingDate; // Дата 1-го подписания
    int duration; // Срок действия
    vector<string> reSigningDates; // даты повторного подписания

public:
    // Объявления конструкторов

    // конструктор по умолчанию
    Contract();

    // Констроктор, заданный параметрически
    Contract(const string& s1, const string& s2, const string& signingDate, int dur, const vector<string>& reSigning):
  side1(s1), side2(s2), signingDate(signingDate), duration(dur) {}  


    // Конструктор копирования
    Contract(const Contract& other); 

    //Конструктор преобразования
    Contract(int dur) : Contract() {
      duration = dur;
    }

    // деструктор
    ~Contract()=default;

    // Get-методы 
    string getside1() const { return side1; }
    string getside2() const { return side2; }
    string getSigningDate() const { return signingDate; }
    int getDuration() const { return duration; }
    const vector<string>& getReSigningDates() const { return reSigningDates; }

    // Set-методы
    // void setnumcontract(int numcontr) { numcontract = numcontr; }
    void setside1(const string& s1) { side1 = s1; }
    void setside2(const string& s2) { side2 = s2; }
    void setSigningDate(const string& date) { signingDate = date; }
    void setDuration(int dur) { duration = dur; }
    void setreSigningDates(const vector<string>& newDates) {reSigningDates =  newDates;} 
    
    // Метод вычисления средней даты переподписания у одного контракта
    string calculateAverageReSigningDate() const; 



    // перегруженные операции 
    bool operator<(const Contract& other) const;
    bool operator>(const Contract& other) const;
    bool operator<=(const Contract& other) const;
    bool operator>=(const Contract& other) const;
    bool operator==(const Contract& other) const;
    bool operator!=(const Contract& other) const;
    friend Contract operator+(const Contract& с1, const Contract& с2);
    Contract& operator++(); //префиксный инкремент для (чего?)
    Contract operator++(int); //постфиксный инкремент для (чего?)
    Contract& operator=(const Contract& other);

    // Дружественные методы ввода/вывода объекта класса на консоль
    friend ostream& operator<<(ostream& os, const Contract &contract);
    friend istream& operator>>(istream& is, Contract &contract);

};

#endif