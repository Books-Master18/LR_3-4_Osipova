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
    return str.length() == 1 && str[0] >= 'A' && str[0] <= 'Z';
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


bool user_input(string input) {
    if (input.empty()) return false;
    try {
         int num = stold(input); // Используем stod для вещественных чисел
        if (num < 0) {
            return false; // Проверка на отрицательное число
        }
    }
    catch (...)
    {
        return false;
    }
    return true;
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




void createContractcopy(vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для копирования (вектор пуст).\n";
        return;
    }

    // Выводим список контрактов с номерами
    cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        cout << "Контракт №" << (i + 1) << "\n";
        cout << contracts[i]<< endl;
    }

    // Спрашиваем пользователя, какой контракт нужно копировать
    int contractNumber;
    enterNumber(contractNumber, "Введите контракт, который хотите копировать");

    try {
        // Проверяем, что введенный номер контракта корректен
        if (contractNumber <= contracts.size() && contractNumber > 0) {
            // Получаем контракт для копирования
            Contract contr2 = contracts[contractNumber - 1]; // Получаем копию выбранного элемента

            cout << "Выбранный контракт для копирования:" << endl << contr2 << endl;

            // Создаем копию контракта с использованием конструктора копирования
            Contract contr3 = contr2;
            cout << "Контракт №" << contracts.size() + 1 << " (копия):" << endl << contr3 << endl;

            // Добавляем скопированный контракт в вектор
            contracts.push_back(contr3);
        } else {
            cout << "Ошибка: Введен некорректный номер контракта.\n";
        }
    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
    } catch (...) {
        cerr << "Произошла неизвестная ошибка.\n";
    }
}

// создает контракт при воде пользователем с клавиатуры каждого поля
void createContractconsol(vector<Contract>& contracts){
    Contract newContract;
    cin>>newContract;
    contracts.push_back(newContract);
    cout<<"введеннный контракт: "<< endl;
    cout << newContract<<endl;
}


// Функция для вычисления средней даты переподписания для одного контракта
string Contract::calculateAverageReSigningDate() const { // Добавляем const
    const vector<string>& reSigningDates = this->getReSigningDates(); // Используем this->

    if (reSigningDates.empty()) {
        return "Нет дат переподписания для вычисления средней даты.";
    }

    time_t totalTime = 0;
    int validDateCount = 0;

    for (const auto& dateStr : reSigningDates) {
        tm t{};
        istringstream ss(dateStr);
        ss >> get_time(&t, "%Y-%m-%d");

        if (!ss.fail()) {
            time_t tt = mktime(&t);
            if(tt != -1) {
                totalTime += tt;
                validDateCount++;
            } else {
                cerr << "Ошибка при преобразовании в time_t: " << dateStr << endl;
            }
        } else {
            cerr << "Ошибка при извлечении даты: " << dateStr << endl;
        }
    }

    if (validDateCount == 0) {
        return "Нет корректных дат переподписания для вычисления средней даты.";
    }

    time_t averageTime = totalTime / validDateCount;
    tm* timeinfo = localtime(&averageTime);
    if(timeinfo == nullptr) {
        cerr << "Ошибка при преобразовании в tm*" << endl;
        return "Ошибка вычисления средней даты";
    }

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer); // Возвращаем среднюю дату в виде строки
}


// Функция для отображения средних дат переподписания для всех контрактов
void displayAverageReSigningDates(const vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для отображения средних дат переподписания.\n";
        return;
    }

    cout << "--- Средние даты переподписания для всех контрактов ---\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        const Contract& contract = contracts[i];
        // Вызываем метод calculateAverageReSigningDate() для объекта contract без аргументов
        string averageDate = contract.calculateAverageReSigningDate();
        cout << "Контракт №" << (i + 1) << ": " << averageDate << endl;
    }
}



void addContract(vector<Contract>& contracts) {
    if (contracts.size() > 0) {
        // вывод списка контрактов
        cout << "\n Список контрактов\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            cout << "Контракт №" << (i + 1) << "\n";
            cout << contracts[i] << endl;
        }

        // ввод номера контракта для вычислений
        int contractNumber;
        enterNumber(contractNumber, "Введите контракт, который хотите копировать");

        try {
            if (contractNumber <= contracts.size() && contractNumber > 0) {
                cout << endl;
                
                cout << "постфиксный инкремент до" << endl;
                cout << endl;
                cout << contracts[contractNumber - 1]<< endl;

                cout << endl << "Постфиксный инкремент в процессе:" << endl;
                Contract oldContract = contracts[contractNumber - 1]++; 
                cout << "oldContract: " << endl; 
                cout << oldContract << endl;
                cout << endl;

                cout << "Постфиксный инкремент после:" << endl;
                cout << contracts[contractNumber - 1]<< endl; 
                cout << endl;

                cout << "префиксный инкремент до: " << endl;
                cout << contracts[contractNumber - 1] << endl;
                cout << endl;
                
                cout << "префиксный инкремент после: " << endl;
                cout<< ++contracts[contractNumber - 1] << endl;
                cout << endl;


            } else {
                cout << "Ошибка: Введен неверный номер контракта." << endl;
            }
        } catch (...) {
            cerr << "Ошибка, попробуйте ввести другой номер контракта" << endl;
        }
    } else {
        cout << "Нет контрактов." << endl;
    }
}


//складывает 2 контракта добавляя 2-ой вектор в конец первого
void sumContracts(vector<Contract>& contracts) {
    cout << "Сложение" << endl;

    if (contracts.size() > 0) {
        // вывод списка контрактов
        cout << "\n Список контрактов\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            cout << "Контракт №" << (i + 1) << "\n";
            cout << contracts[i] << endl;
        }

        // ввод номера контракта для вычислений

        int num1, num2;
        enterNumber(num1, "Введите номер первого контракта");
        enterNumber(num2, "Введите номер второго контракта");

        try {
            if (num1 <= contracts.size() && num2 <= contracts.size() && num1 > 0 && num2 > 0) { 
                Contract sumContract = contracts[num1 - 1] + contracts[num2 - 1]; 
                cout << "сумма контрактов: " << sumContract << endl;
                cout << endl;
                contracts.push_back(sumContract);
            } else {
                cout << "Ошибка: Введены некорректные номера контрактов." << endl;
            }
        } catch (const out_of_range& oor) {
            cerr << "Ошибка: выход за границы диапазона: " << oor.what() << endl;
        } catch (...) {
            cerr << "Ошибка, попробуйте ввести другой номер контракта" << endl;
        }
    } else {
        cout << "Нет контрактов для суммирования (вектор пуст).\n";
    }
}

// Функция для замены  продолжтельности контракта
void replaceContract(vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для преобразования (вектор пуст).\n";
        return;
    }

    // Выводим список контрактов с номерами
    cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
        cout << "Контракт №" << (i + 1) << "\n";
        cout << contracts[i] << endl;
    }

    // Запрашиваем у пользователя номер контракта для преобразования
    int contractNumber;
    enterNumber(contractNumber, "Введите номер контракта для преобразования: ");

    if (contractNumber <= 0 || contractNumber > contracts.size()) {
        cout << "Некорректный номер контракта.\n";
        return;
    }

    // Получаем старый контракт
    Contract oldContract = contracts[contractNumber - 1];

    // Создаем временный объект, чтобы сгенерировать случайную duration
    Contract tempContract;

    // Создаем новый контракт, используя конструктор преобразования, передавая duration из временного объекта
    Contract newContract(tempContract.getDuration());

    // Сохраняем остальные поля из старого контракта
    newContract.setside1(oldContract.getside1());
    newContract.setside2(oldContract.getside2());
    newContract.setSigningDate(oldContract.getSigningDate());
    newContract.setreSigningDates(oldContract.getReSigningDates());

    // Заменяем старый контракт новым
    contracts[contractNumber - 1] = newContract;

    cout << "Контракт №" << contractNumber << " успешно заменен (изменена duration на случайное значение, остальные поля остались без изменений).\n";
    cout << newContract <<endl;

}



void assignmentConstructor(vector<Contract>& contracts) {
    cout << "тест присваивания одного контракта другому" << endl;

    if (contracts.size() > 0) {
        // вывод списка контрактов
        cout << "\n Список контрактов\n";
        for (size_t i = 0; i < contracts.size(); ++i) {
            cout << "Контракт №" << (i + 1) << "\n";
            cout << contracts[i] << endl;
        }

        // ввод номера контракта для вычислений
        int num1,num2;
        enterNumber(num1, "Введите номер первого контракта (того, который хотите присвоить)");
        enterNumber(num2, "Введите номер второго контракта (которому хотите присвоить)");

        try {
            if (num1 <= contracts.size() && num2 <= contracts.size() && num1 > 0 && num2 > 0) { 
                Contract contr = contracts[num2 - 1] = contracts[num1 - 1]; 
                cout << "тест присваивания: " << contr << endl;
                cout << endl;
            } else {
                cout << "Ошибка: Введены некорректные номера контрактов." << endl;
            }
        } catch (...) {
            cerr << "Ошибка, попробуйте ввести другой номер контракта" << endl;
        }
    } else {
        cout << "Нет контрактов для присваивания (вектор пуст).\n";
    }
}




vector<Contract> sortContractsBySigningDate(vector<Contract> contracts) {
    sort(contracts.begin(), contracts.end(), [](const Contract& a, const Contract& b) {
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
        cout << "Контракт №" << (i + 1) << "\n" << contract << endl;
    }
}



void compareAverageReSigningDates(vector<Contract>& contracts) {
    if (contracts.empty()) {
        cout << "Нет контрактов для сравнения.\n";
        return;
    }

    // Вывод списка контрактов
    cout << "\nСписок контрактов:\n";
    for (size_t i = 0; i < contracts.size(); ++i) {
            cout << "Контракт №" << (i + 1) << "\n";
            cout << contracts[i] << endl;
    }

    // Ввод номеров контрактов для сравнения
            int num1,num2;
        enterNumber(num1, "Введите номер первого контракта для сравнения: ");
        enterNumber(num2, "Введите номер второго контракта для сравнения: ");

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
            cout << endl;

 // Сравниваем средние даты
    cout<<"тест операторов сравниения контрактов по средн. дате переподписания (формат вывода: 0 или 1)"<<endl;
    cout<<"тест оператора < (сравнение "<<avgDate1<< " < " <<avgDate2<<" ?): "<< (avgDate1<avgDate2) <<endl;
    cout<<"тест оператора > (сравнение "<<avgDate1<< " > " <<avgDate2<<" ?): "<< (avgDate1>avgDate2) <<endl;
    cout<<"тест оператора <= (сравнение "<<avgDate1<< " <= " <<avgDate2<<" ?): "<< (avgDate1<=avgDate2) <<endl;
    cout<<"тест оператора >= (сравнение "<<avgDate1<< " >= " <<avgDate2<<" ?): "<< (avgDate1>=avgDate2) <<endl;
    cout<<"тест оператора != (сравнение "<<avgDate1<< " != " <<avgDate2<<" ?): "<< (avgDate1!=avgDate2) <<endl;
    cout<<"тест оператора == (сравнение "<<avgDate1<< " == " <<avgDate2<<" ?): "<< (avgDate1 == avgDate2) <<endl;
            
        }

    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
    } catch (...) {
        cerr << "Произошла неизвестная ошибка.\n";
    }
}
#endif