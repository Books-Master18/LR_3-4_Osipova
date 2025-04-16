#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Contract.cpp"

using namespace std;

struct MenuItem {
    string title;
    void (*action)(std::vector<Contract>&); // Function pointer. It now takes a vector.
};


int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    map<int, MenuItem> menu = {
      {1, {"Создать Contract по умолчанию", createDefaultContract}},
      {2, {"Создать параметрический Contract", createParameterizedContract}},
      {3, {"Создать Contract со всеми данными", createFullContract}},
      {4, {"Contract from Console", createContractFromConsole}},
      {5, {"Отобразить все данные из Contracts", displayAllContracts}},
      {6, {"Вычислить среднее даты переподписания", calculateAverageReSigningDate}},
      {7, {"Добавить новые данные в Contract", createContractFromConsole}}, // Reuse createContractFromConsole to add
      {8, {"Отсортировать Contract по дате первого подписания", sortContracts}},
      {9, {"Тестировать операторы", testContractFunctions}},
      {10, {"тестирование методов", testContractsMethod}},

    };

    std::vector<Contract> contracts; //Vector to store the Contracts

    int choice = 0;
    std::cout <<"=============== Меню ==============="<<std::endl;
    // std::cout <<""<<std::endl;
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
                menu[choice].action(contracts); //Pass in vector to use
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