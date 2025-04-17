#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <functional>
#include "Osipova_LR3-4_Contract.cpp"
#include "Osipova_LR3-4_Methods.h"

using namespace std;

struct MenuItem {
    string title;
    void (*action)(std::vector<Contract>&); // Указатель на функцию. 

};

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    map<int, MenuItem> menu = {
      {1, {"Создать Contract по умолчанию", createDefaultContract}},
      {2, {"Создать параметрический Contract", createParameterizedContract}},
      {3, {"Отобразить все данные из Contracts", displayAllContracts}},
    //   {6, {"Вычислить среднее даты переподписания", calculateAverageReSigningDate}},
    //   {7, {"Добавить новые данные в Contract", addDataToContract}}, 
    //   {8, {"Отсортировать Contract по дате первого подписания", sortContracts}},
    //   {9, {"Тестировать операторы", testContractFunctions}},
    //   {10, {"тестирование методов", testContractsMethod}},

    };

    std::vector<Contract> contracts; //Вектор для хранения контрактов Contracts

    int choice = 0;
    std::cout <<"=============== Меню ==============="<<std::endl;
    std::cout <<""<<std::endl;
        for (const auto& item : menu) 
        {
            std::cout << "Пункт "<< item.first << ". " << item.second.title << std::endl;
        }
    std::cout <<"0. Выход"<<std::endl;
    while (true){
        enterNumber(choice, "Введите выбор пункта");
        if (choice == 0)
        {
            std::cout <<"2025 Osipova Aleksandra" << std::endl;
            break;
        }
        std::cout <<std::endl<<"===============Action===============" <<std::endl;
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