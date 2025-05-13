#include <ctime>
#include <map>
#include "Osipova_LR3-4_Methods.h"
#include "Osipova_LR3-4_Contract.cpp"


using namespace std;


struct MenuItem {
    string title;
    function<void(vector<Contract>&)> action;

    MenuItem(string title, function<void(vector<Contract>&)> action) : title(title), action(action) {}
    MenuItem() : title(""), action(nullptr) {} 
};


int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    

    map<int, MenuItem> menu = {
        {1,{"Создать Contract по умолчанию",createDefaultContract}},
        {2, {"Создать параметрический Contract", createParameterizedContract}},
        {3,{"Конструктор копирования контракта", createContractcopy}},
        {4,{"Преобразование", replaceContract}},
        {5,{"Создание Contract с консоли",createContractconsol}},
        {6,{"Отобразить все данные из Contracts", displayAllContracts}},
        {7,{"Сортировка контрактов по первой дате подписания", displaySortedContracts}},
        {8,{"Среднее значение контракта (проверка корректности через Excel)", displayAverageReSigningDates}},
        {9,{"Тест перегруженных операций", compareAverageReSigningDates}},
        {10,{"Перегруженный оператор сложения", sumContracts}},
        {11,{"Постфиксное и префиксное инкремент", addContract}}, 
        {12,{"Присваивание", assignmentConstructor}},
    };


    int choice = 0;
    cout <<"=============== Меню ==============="<<endl;
    cout <<""<<endl;
        for (const auto& item : menu) 
        {
            cout << "Пункт "<< item.first << ". " << item.second.title << endl;
        }
    cout <<"0. Выход"<< endl;
    while (true){
        //enterChoice(choice, "Введите выбор пункта");
        enterNumber(choice, "Введите выбор пункт");
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

    }
    return 0;
}