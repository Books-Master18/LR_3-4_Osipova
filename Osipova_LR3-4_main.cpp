#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <functional>
#include "Osipova_LR3-4_Methods.h"
#include "Osipova_LR3-4_Contract.cpp"

using namespace std;

struct MenuItem {
    string title;
    function<void(std::vector<Contract>&)> action;

    MenuItem(string title, function<void(vector<Contract>&)> action) : title(title), action(action) {}
    MenuItem() : title(""), action(nullptr) {} // If you need a default constructor
};


int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    map<int, MenuItem> menu = {
        {1, {"Создать Contract по умолчанию", createDefaultContract}},
        {2, {"Создать параметрический Contract", createParameterizedContract}},
        {3, {"Отобразить все данные из Contracts", displayAllContracts}},
        {4, {"Отсортировать Contract по дате первого подписания", displaySortedContracts}},
        {5, {"Вычислить среднее даты переподписания", calculateAverageReSigningDate}},
    };
    

    std::vector<Contract> contracts; //Вектор для хранения контрактов Contracts

    int choice = 0;
    cout <<"=============== Меню ==============="<<endl;
    cout <<""<<endl;
        for (const auto& item : menu) 
        {
            cout << "Пункт "<< item.first << ". " << item.second.title << endl;
        }
    cout <<"0. Выход"<< endl;
    while (true){
        enterNumber(choice, "Введите выбор пункта");
        if (choice == 0)
        {
            std::cout <<"2025 Osipova Aleksandra" << endl;
            break;
        }
        cout << endl<<"===============Действие===============" << endl;
        if (menu.count(choice)) {
            if (menu[choice].action != nullptr) {
                menu[choice].action(contracts);
            }
            else {
                cout << "Выходи из программы.\n";
            }
        }
        else {
            cout << "Неопознаный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);
    return 0;
}