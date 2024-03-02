#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // Для функции system

struct Patient {
    std::string passportNumber;
    std::string fullName;
    std::string branch;
    bool isDeleted; // Добавленный флаг

    Patient() : isDeleted(false) {} // Конструктор по умолчанию инициализирует isDeleted как false
};

const int TABLE_SIZE = 100;

void cls() {
    std::cin.get();
    system("clear");
}

int hashFunction(const std::string& passportNumber) {
    int sum = 0;
    for (char c : passportNumber) {
        if (std::isdigit(c)) {
            sum += c - '0';
        }
    }
    return sum % TABLE_SIZE;
}

bool isValidPassportFormat(const std::string& passportNumber) { // Функция проверки формата паспорта
    if (passportNumber.length() != 9) return false;
    for (int i = 0; i < passportNumber.length(); ++i) {
        if (i == 2) {
            if (passportNumber[i] != '-') return false;
        }
        else {
            if (!std::isdigit(passportNumber[i])) return false;
        }
    }
    return true;
}

void addRecord(std::unique_ptr<Patient> hashTable[], Patient patient) {
    int index = hashFunction(patient.passportNumber);
    int originalIndex = index;
    int attempts = 0;

    do {
        if (!hashTable[index] || hashTable[index]->isDeleted) {
            hashTable[index] = std::make_unique<Patient>(patient);
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Если целевая ячейка уже занята, вычисляется следующий индекс (Линейное опробование)
        attempts++;
    } while (index != originalIndex && attempts < TABLE_SIZE); // Предотвращаем бесконечный цикл

    std::cout << "Таблица заполнена, невозможно добавить запись." << std::endl;
}

void removeRecord(std::unique_ptr<Patient> hashTable[]) {
    bool isEmpty = true;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hashTable[i] != nullptr && !hashTable[i]->isDeleted) {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty) {
        system("clear");
        std::cout << "Невозможно показать записи, список записей пуст." << std::endl;
        std::cin.get();
        return;
    }

    std::cout << "Удаление записи по паспорту." << std::endl;
    std::string passportToRemove;
    do {
        std::cout << "Введите номер паспорта для удаления записи (формат NN-NNNNNN): ";
        std::cin >> passportToRemove;
        if (!isValidPassportFormat(passportToRemove)) {
            std::cout << "Неверный формат номера паспорта. Попробуйте снова.\n";
        }
    } while (!isValidPassportFormat(passportToRemove));

    int index = hashFunction(passportToRemove);
    int originalIndex = index;
    do {
        if (!hashTable[index]) {
            std::cout << "Запись с паспортом " << passportToRemove << " не найдена." << std::endl;
            std::cin.get();
            return;
        }

        if (!hashTable[index]->isDeleted && hashTable[index]->passportNumber == passportToRemove) {
            hashTable[index]->isDeleted = true;
            std::cout << "Запись с паспортом " << passportToRemove << " помечена как удаленная." << std::endl;
            std::cin.get();
            return;
        }

        index = (index + 1) % TABLE_SIZE;
    } while (index != originalIndex); // Предотвращаем бесконечный цикл
}

void viewAllRecords(const std::unique_ptr<Patient> hashTable[]) {
    bool isEmpty = true;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hashTable[i] && !hashTable[i]->isDeleted) {
            isEmpty = false;
            std::cout << "Паспорт: " << hashTable[i]->passportNumber
                << " ФИО: " << hashTable[i]->fullName
                << " Филиал: " << hashTable[i]->branch << std::endl;
        }
    }

    if (!isEmpty) {
        std::cin.get();
        return;
    }

    if (isEmpty) {
        system("clear");
        std::cout << "Невозможно показать записи, список записей пуст." << std::endl;
        std::cin.get();
        return;
    }
}

void removeAllRecords(std::unique_ptr<Patient> hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hashTable[i].reset(); // Освобождаем память и устанавливаем указатели в nullptr
    }
}

void searchByKey(std::unique_ptr<Patient> hashTable[], const std::string& passportNumber) {
    int index = hashFunction(passportNumber);
    int originalIndex = index;
    do {
        if (!hashTable[index]) {
            std::cout << "Запись с таким номером паспорта не найдена." << std::endl;
            std::cin.get();
            return;
        }

        if (!hashTable[index]->isDeleted && hashTable[index]->passportNumber == passportNumber) {
            std::cout << "Найдена запись." << std::endl
                << "Паспорт: " << hashTable[index]->passportNumber 
                << " ФИО: " << hashTable[index]->fullName 
                << " Филиал: " << hashTable[index]->branch << std::endl;
            std::cin.get();
            return;
        }

        index = (index + 1) % TABLE_SIZE;
    } while (index != originalIndex); // Предотвращаем бесконечный цикл
}


void searchByLastName(const std::unique_ptr<Patient> hashTable[], const std::string& lastName) {
    bool found = false;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hashTable[i] && !hashTable[i]->isDeleted && hashTable[i]->fullName.find(lastName) != std::string::npos) {
            std::cout << "Найдена запись." << std::endl
                << "Паспорт: " << hashTable[i]->passportNumber
                << " ФИО: " << hashTable[i]->fullName
                << " Филиал: " << hashTable[i]->branch << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Записи с такой фамилией не найдены." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    std::unique_ptr<Patient> hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) { // Инициализируем указатели в nullptr
        hashTable[i] = nullptr;
    }

    int choice;
    while (true) {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить запись\n";
        std::cout << "2. Удалить запись\n";
        std::cout << "3. Просмотр всех записей\n";
        std::cout << "4. Удалить все записи\n";
        std::cout << "5. Поиск по ключевому полю\n";
        std::cout << "6. Поиск по фамилии\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Данные о пациенте." << std::endl;
            Patient newPatient;

            std::string passportNumber;
            do {
                std::cout << "Введите номер паспорта (формат NN-NNNNNN): ";
                std::cin >> passportNumber;
                if (!isValidPassportFormat(passportNumber)) {
                    std::cout << "Неверный формат номера паспорта. Попробуйте снова.\n";
                }
            } while (!isValidPassportFormat(passportNumber));
            newPatient.passportNumber = passportNumber;

            std::cout << "Введите ФИО: ";
            std::cin.ignore();
            std::getline(std::cin, newPatient.fullName);

            std::cout << "Введите филиал: ";
            std::getline(std::cin, newPatient.branch);
            addRecord(hashTable, newPatient);

            cls();
            break;
        }
        case 2: {
            removeRecord(hashTable);
            cls();
            break;
        }
        case 3:
            viewAllRecords(hashTable);
            cls();
            break;
        case 4:
            removeAllRecords(hashTable);
            std::cout << "Удаление всех записей завершено... " << std::endl;
            cls();
            break;
        case 5: {
            std::cout << "Поиск записи по номеру паспорта." << std::endl;
            std::string passportToSearch;
            do {
                std::cout << "Введите номер паспорта для поиска (формат NN-NNNNNN): ";
                std::cin >> passportToSearch;
                if (!isValidPassportFormat(passportToSearch)) {
                    std::cout << "Неверный формат номера паспорта. Попробуйте снова.\n";
                }
            } while (!isValidPassportFormat(passportToSearch));
            searchByKey(hashTable, passportToSearch);
            cls();
            break;
        }
        case 6: {
            std::cout << "Поиск записи по фамилии." << std::endl;
            std::string lastName;
            std::cout << "Введите фамилию для поиска: ";
            std::cin.ignore();
            std::getline(std::cin, lastName);
            searchByLastName(hashTable, lastName);
            cls();
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "Некорректный выбор. Попробуйте снова.\n";
            cls();
        }
    }

    return 0;
}