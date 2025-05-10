#ifndef METHODS_H
#define METHODS_H

#include "Osipova_LR3-4_Contract.h" 
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// Определение глобального вектора 
vector<Contract> contracts;


// перегруженные операторы сравнения 

bool Contract::operator<(const Contract& other) const {
    return calculateAverageReSigningDate() < other.calculateAverageReSigningDate();
}
bool Contract::operator>(const Contract& other) const {
    return calculateAverageReSigningDate() > other.calculateAverageReSigningDate();
}

bool Contract::operator<=(const Contract& other) const {
    return calculateAverageReSigningDate() <= other.calculateAverageReSigningDate();
}

bool Contract::operator>=(const Contract& other) const {
    return calculateAverageReSigningDate() >= other.calculateAverageReSigningDate();
}

bool Contract::operator==(const Contract& other) const {
    return calculateAverageReSigningDate() == other.calculateAverageReSigningDate();
}

bool Contract::operator!=(const Contract& other) const {
    return calculateAverageReSigningDate() != other.calculateAverageReSigningDate();
}


bool isValidSingleAlphaString(const string& str) {
    // Проверяем, что строка состоит из одного символа
    if (str.length() != 1) {
        return false;
    }

    // Проверяем, что символ - английская буква
    return isalpha(static_cast<unsigned char>(str[0])) && (str[0] >= 'A' && str[0] <= 'Z');
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    int year, month, day;
    try {
        year = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day = stoi(date.substr(8, 2));
    } catch (const invalid_argument& ia) {
        return false;
    } catch (const out_of_range& oor) {
        return false;
    }
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) return false;
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > 29) return false;
        if (day == 29 && !isLeapYear) return false;
    }
    return true;
}

// Новая функция для проверки, является ли строка целым числом
bool isInteger(const std::string& s) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

// Новая функция для проверки, является ли строка положительным целым числом
bool isPositiveInteger(const string& s) {
    return isInteger(s) && (stoll(s) >= 0);
}

bool user_input(string input) {
    if (input.empty()) return false;
    try {
        // Теперь stold используется только для проверки, что это ЧИСЛО, а не буква
        stold(input);
    }
    catch (...)
    {
        return false;
    }
    return true;
}


unsigned enterChoice(const string& label) {
    unsigned choice;
    string raw_input;
    cout << label << " = ";
    getline(cin, raw_input);

    while (true) {
        try {
            choice = stoul(raw_input);
            if (choice >= 0) {
                return choice;
            }
            else {
                cout << "Пожалуйста, введите неотрицательное целое число: ";
                getline(cin, raw_input);
            }
        }
        catch (...) {
            cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
            getline(cin, raw_input);
        }
    }
}


void enterNumber(int& varLink, const string& label) {
    string raw_input;
    cout << label << " ";
    getline(cin, raw_input);

    while (!user_input(raw_input)) {
        cout << "Некорректный ввод. Пожалуйста, введите положительное вещественное число: " << label << " = ";
        getline(cin, raw_input);
    }
    try {
        varLink = stod(raw_input); // Изменено на stod для double
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: Некорректный ввод для преобразования в число. " << e.what() << endl;
        varLink = 0; // Или другое значение по умолчанию
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: Введенное число слишком велико. " << e.what() << endl;
        varLink = 0; // Или другое значение по умолчанию
    }
}

void enterString(string& varLink, const string& label) {
    string input;
    while (true) {
        cout << label << "";
        getline(cin, input);

        if (isValidSingleAlphaString(input)) {
            varLink = input;
            return;
        } else {
            cout << "Некорректный ввод. Пожалуйста, введите ОДНУ английскую букву.\n";
        }
    }
}

void enterDate(string& varLink, const string& label) {
    string raw_input;
    cout << label << " ";
    getline(cin, raw_input);

    while (!isValidDate(raw_input)) {
        cout << "Некорректный ввод. Пожалуйста, введите дату в формате ГГГГ-ММ-ДД: " << label << " = ";
        getline(cin, raw_input);
    }
    varLink = raw_input;
}




// Реализации функций, методов и т. д.

void createDefaultContract(vector<Contract>& contracts){
    Contract contr1,contr2;
    contracts.push_back(contr1);
    contracts.push_back(contr2);
    cout<<"Контракт № 1"<<endl;
    cout<<contr1<<endl;
    cout<<"Контракт № 2"<<endl;
    cout<<contr2<<endl;
}

void createParameterizedContract(vector<Contract>& contracts) {
    Contract newContract;
    cout << "Введите данные для нового параметризованного контракта:\n";
    cin >> newContract; // Используем перегруженный оператор >> для ввода данных
    contracts.push_back(newContract);
    cout << "Параметризованный контракт создан и добавлен.\n";
}

// Функция для отображения всех данных из Contracts
  void displayAllContracts(const vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для отображения.\n";
        return;
    }

    cout << "--- Все контракты ---\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        const Contract& contract = contracts[i];
        cout << "Контракт №" << (i + 1) << "\n";
        cout << contract << endl;
    }
}


// void createContractcopy(vector<Contract>& contracts) {
//     if (contracts.empty()) {
//         cout << "Нет контрактов для копирования (вектор пуст).\n";
//         return;
//     }

//     // Берем последний контракт, добавленный в вектор (предполагаем, что это последний созданный контракт по умолчанию)
//     Contract contr2 = contracts.back(); // Получаем копию последнего элемента

//     cout << "Последний добавленный контракта)" << endl << contr2 << endl;

//     Contract contr3 = contr2; // Используем конструктор копирования
//     cout << "Контракт № 3 (копия)" << endl << contr3 << endl;

//     contracts.push_back(contr3); // Добавляем скопированный контракт в вектор
// }

void createContractcopy(std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет контрактов для копирования (вектор пуст).\n";
        return;
    }

    // Выводим список контрактов с номерами
    std::cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        std::cout << (i + 1) << ") " << contracts[i] << std::endl;
    }

    // Спрашиваем пользователя, какой контракт нужно копировать
    unsigned contractNumber = enterChoice("Введите номер контракта для копирования: ");

    try {
        // Проверяем, что введенный номер контракта корректен
        if (contractNumber <= contracts.size() && contractNumber > 0) {
            // Получаем контракт для копирования
            Contract contr2 = contracts[contractNumber - 1]; // Получаем копию выбранного элемента

            std::cout << "Выбранный контракт для копирования:" << std::endl << contr2 << std::endl;

            // Создаем копию контракта с использованием конструктора копирования
            Contract contr3 = contr2;
            std::cout << "Контракт №" << contracts.size() + 1 << " (копия):" << std::endl << contr3 << std::endl;

            // Добавляем скопированный контракт в вектор
            contracts.push_back(contr3);
        } else {
            std::cout << "Ошибка: Введен некорректный номер контракта.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Произошла неизвестная ошибка.\n";
    }
}

// создает кампанию при воде пользователем с клавиатуры каждого поля
void createContractconsol(vector<Contract>& contracts){
    Contract newContract;
    cin>>newContract;
    contracts.push_back(newContract);
    cout<<"введеннный контракт: "<<newContract<<endl;
}


// Функция для вычисления средней даты переподписания для одного контракта
string Contract::calculateAverageReSigningDate() const { // Добавляем const
    const std::vector<std::string>& reSigningDates = this->getReSigningDates(); // Используем this->

    if (reSigningDates.empty()) {
        return "Нет дат переподписания для вычисления средней даты.";
    }

    std::time_t totalTime = 0;
    int validDateCount = 0;

    for (const auto& dateStr : reSigningDates) {
        std::tm t{};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&t, "%Y-%m-%d");

        if (!ss.fail()) {
            std::time_t tt = mktime(&t);
            if(tt != -1) {
                totalTime += tt;
                validDateCount++;
            } else {
                std::cerr << "Ошибка при преобразовании в time_t: " << dateStr << std::endl;
            }
        } else {
            std::cerr << "Ошибка при парсинге даты: " << dateStr << std::endl;
        }
    }

    if (validDateCount == 0) {
        return "Нет корректных дат переподписания для вычисления средней даты.";
    }

    std::time_t averageTime = totalTime / validDateCount;
    std::tm* timeinfo = localtime(&averageTime);
    if(timeinfo == nullptr) {
        std::cerr << "Ошибка при преобразовании в tm*" << std::endl;
        return "Ошибка вычисления средней даты";
    }

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer); // Возвращаем среднюю дату в виде строки
}


// Функция для отображения средних дат переподписания для всех контрактов
void displayAverageReSigningDates(const std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет контрактов для отображения средних дат переподписания.\n";
        return;
    }

    std::cout << "--- Средние даты переподписания для всех контрактов ---\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        const Contract& contract = contracts[i];
        // Вызываем метод calculateAverageReSigningDate() для объекта contract без аргументов
        std::string averageDate = contract.calculateAverageReSigningDate();
        std::cout << "Контракт №" << (i + 1) << ": " << averageDate << std::endl;
    }
}

// void replaceLastContract(vector<Contract>& contracts) {
//     if (contracts.empty()) {
//         cout << "Нет контрактов для замены (вектор пуст).\n";
//         return;
//     }

//     cout << "Введите данные для замены последнего контракта:\n";
//     cin >> contracts.back(); // Используем перегруженный оператор >> для ввода данных
//     cout << "Последний контракт успешно заменен.\n";
// }

void replaceContract(std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        std::cout << "Нет контрактов для замены (вектор пуст).\n";
        return;
    }

    // Выводим список контрактов с номерами
    std::cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        std::cout << (i + 1) << ") " << contracts[i] << std::endl;
    }

    // Спрашиваем пользователя, какой контракт нужно заменить
    unsigned contractNumber = enterChoice("Введите номер контракта для замены: ");

    try {
        // Проверяем, что введенный номер контракта корректен
        if (contractNumber <= contracts.size() && contractNumber > 0) {
            std::cout << "Введите данные для замены контракта №" << contractNumber << ":" << std::endl;
            std::cin >> contracts[contractNumber - 1]; // Используем перегруженный оператор >> для ввода данных
            std::cout << "Контракт №" << contractNumber << " успешно заменен.\n";
        } else {
            std::cout << "Ошибка: Введен некорректный номер контракта.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Произошла неизвестная ошибка.\n";
    }
}
void addContract(vector<Contract>& contracts) {
    if (contracts.size() > 0) {
        // вывод списка контрактов
        cout << "\n The list of contracts\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            cout << (i + 1) << ") " << contracts[i] << endl;
        }

        // ввод номера контракта для вычислений
        unsigned number = enterChoice("Введите номер кампании для расчета приращений: ");

        try {
            if (number <= contracts.size() && number > 0) {
                cout << "постфиксный инкремент до" << endl;
                cout  << endl;
                Contract oldContract = contracts[number - 1]++; //  Код для post increment
                cout << oldContract << endl;
                cout  << endl;
                cout << "после: " << contracts[number - 1] << endl;
                cout  << endl;
                cout << "префиксный инкремент: " << ++contracts[number - 1] << endl; // Код для pre increment

            } else {
                cout << "Ошибка: Введен неверный номер контракта." << endl;
            }
        } catch (const out_of_range& oor) {
            cerr << "Ошибка: выход за границы диапазона: " << oor.what() << endl;
        } catch (...) {
            cerr << "Ошибка, попробуйте ввести другой номер контракта" << endl;
        }
    } else {
        cout << "Нет контрактов." << endl;
    }
}


//складывает 2 контракта добавляя 2ой вектор в конец первого
void sumContracts(vector<Contract>& contracts) {
    cout << "Сложение" << endl;

    if (contracts.size() > 0) {
        // вывод списка контрактов
        cout << "\n Список контрактов\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            cout << (i + 1) << ") " << contracts[i] << endl;
        }

        // ввод номера контракта для вычислений
        unsigned num1 = enterChoice("Введите номер первого контракта");
        unsigned num2 = enterChoice("Введите номер второго контракта");

        try {
            if (num1 <= contracts.size() && num2 <= contracts.size() && num1 > 0 && num2 > 0) { // Adjusted condition
                Contract sumContract = contracts[num1 - 1] + contracts[num2 - 1]; // Subtract 1 for correct index
                cout << "сумма контрактов: " << sumContract << endl;
                contracts.push_back(sumContract);
            } else {
                std::cout << "Ошибка: Введены некорректные номера контрактов." << std::endl;
            }
        } catch (const std::out_of_range& oor) {
            std::cerr << "Ошибка: выход за границы диапазона: " << oor.what() << std::endl;
        } catch (...) {
            std::cerr << "Ошибка, попробуйте ввести другой номер контракта" << std::endl;
        }
    } else {
        std::cout << "Нет контрактов для суммирования (вектор пуст).\n";
    }
}



void assignmentConstructor(vector<Contract>& contracts) {
    std::cout << "тест присваивания одного контракта другому" << std::endl;

    if (contracts.size() > 0) {
        // вывод списка контрактов
        std::cout << "\n Список контрактов\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            std::cout << (i + 1) << ") " << contracts[i] << std::endl;
        }

        // ввод номера контракта для вычислений
        unsigned num1 = enterChoice("Введите номер первого контракта (того, который хотите присвоить)");
        unsigned num2 = enterChoice("Введите номер второго контракта (которому хотите присвоить)");

        try {
            if (num1 <= contracts.size() && num2 <= contracts.size() && num1 > 0 && num2 > 0) { // Adjusted condition
                Contract contr = contracts[num2 - 1] = contracts[num1 - 1]; // Subtract 1 for correct index
                std::cout << "тест присваивания: " << contr << std::endl;
            } else {
                std::cout << "Ошибка: Введены некорректные номера контрактов." << std::endl;
            }
        } catch (...) {
            std::cerr << "Ошибка, попробуйте ввести другой номер контракта" << std::endl;
        }
    } else {
        std::cout << "Нет контрактов для присваивания (вектор пуст).\n";
    }
}




vector<Contract> sortContractsBySigningDate(vector<Contract> contracts) {
    std::sort(contracts.begin(), contracts.end(), [](const Contract& a, const Contract& b) {
        return a.getSigningDate() < b.getSigningDate();
    });
    return contracts;
}

// Функция отображения отсортированных дат переподписания
void displaySortedContracts(const vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для отображения.\n";
        return;
    }

    vector<Contract> sortedContracts = sortContractsBySigningDate(contracts);

    cout << "--- Отсортированные контракты (по дате подписания) ---\n";
    for (size_t i = 0; i < sortedContracts.size(); ++i) {
        const Contract& contract = sortedContracts[i];
        std::cout << "Контракт №" << (i + 1) << "\n" << contract << std::endl;
    }
}



void compareAverageReSigningDates(std::vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для сравнения.\n";
        return;
    }

    // Вывод списка контрактов
    std::cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        cout << (i + 1) << ") " << contracts[i] << std::endl;
        cout <<endl;
    }

    // Ввод номеров контрактов для сравнения
    unsigned num1 = enterChoice("Введите номер первого контракта для сравнения: ");
    unsigned num2 = enterChoice("Введите номер второго контракта для сравнения: ");

    try {
        if (num1 <= contracts.size() && num2 <= contracts.size() && num1 > 0 && num2 > 0) {
            // Получаем контракты
            const Contract& contract1 = contracts[num1 - 1];
            const Contract& contract2 = contracts[num2 - 1];

            // Вычисляем средние даты
            string avgDate1 = contract1.calculateAverageReSigningDate();
            string avgDate2 = contract2.calculateAverageReSigningDate();

            cout << "Средняя дата переподписания для контракта №" << num1 << ": " << avgDate1 << endl;
            cout << "Средняя дата переподписания для контракта №" << num2 << ": " << avgDate2 << endl;

 // Сравниваем средние даты
    cout<<"тест операторов сравниения контрактов по средн. дате переподписания (формат вывода: 0 или 1)"<<endl;
    cout<<"тест оператора < : "<< (num1<num2) <<endl;
    cout<<"тест оператора > : "<< (num1>num2) <<endl;
    cout<<"тест оператора <= : "<< (num1<=num2) <<endl;
    cout<<"тест оператора >= : "<< (num1>=num2) <<endl;
    cout<<"тест оператора >= : "<< (num1!=num2) <<endl;
    cout<<"тест оператора >= : "<< (num1==num2) <<endl;
            
        }

    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
    } catch (...) {
        cerr << "Произошла неизвестная ошибка.\n";
    }
}
#endif