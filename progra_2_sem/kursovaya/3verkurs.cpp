#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Struct representing a student
struct Student {
    string name;
    string surname;
    int group;
    vector<int> grades;
    double scholarship;
};

// Struct representing a group
struct Group {
    int number;
    vector<Student> students;
};

// Class for working with students
class Stream {
public:
    Stream() : sum_scholarship(0) {}

    void add_student(const Student& student);
    void remove_student(const string& name, const string& surname);
    void add_group();
    void remove_group(int number);
    void print_all_students() const;
    void print_all_groups() const;
    void read_from_file(const string& file_name);
    void write_to_file(const string& file_name) const;

private:
    vector<Group> groups;
    double sum_scholarship;

    void calculate_sum_scholarship();
    int find_group(int number) const;
    int find_student(const string& name, const string& surname) const;
};

void Stream::add_student(const Student& student) {
    int group_number = student.group;
    int index = find_group(group_number);

    if (index != -1) {
        groups[index].students.push_back(student);
    } else {
        Group group{group_number, {student}};
        groups.push_back(group);
    }

    sum_scholarship += student.scholarship;
}

void Stream::remove_student(const string& name, const string& surname) {
    int index = find_student(name, surname);

    if (index != -1) {
        int group_number = groups[index].students[index].group;
        groups[index].students.erase(groups[index].students.begin() + index);

        if (groups[index].students.empty()) {
            groups.erase(groups.begin() + index);
        }

        calculate_sum_scholarship();
    } else {
        cout << "Студент не найден" << endl;
    }
}

void Stream::add_group() {
    int number = groups.empty() ? 1 : groups.back().number + 1;
    Group group{number, {}};
    groups.push_back(group);
}

void Stream::remove_group(int number) {
    int index = find_group(number);

    if (index != -1) {
        groups.erase(groups.begin() + index);
        calculate_sum_scholarship();
    } else {
        cout << "Группа не найдена" << endl;
    }
}

void Stream::print_all_students() const {
    for (const auto& group : groups) {
        for (const auto& student : group.students) {
            cout << "Имя: " << student.name << "; Фамилия: " << student.surname
                 << "; Группа: " << student.group << "; Оценки за последнюю сессию: ";
            for (const auto& grade : student.grades) {
                cout << grade << " ";
            }
            cout << "; Стипендия: " << student.scholarship << " руб." << endl;
        }
    }
}

void Stream::print_all_groups() const {
    for (const auto& group : groups) {
        double group_scholarship = 0;

        for (const auto& student : group.students) {
            group_scholarship += student.scholarship;
        }

        double percentage = group_scholarship / sum_scholarship * 100;
        cout << "Номер группы: " << group.number << "; Процент от общей стипендии: " << percentage << "%" << endl;
    }
}

bool is_file_empty(ifstream& pFile) {
    return pFile.peek() == ifstream::traits_type::eof();
}

void Stream::read_from_file(const string& file_name) {
    ifstream file(file_name);

    if (!is_file_empty(file)) {
        ifstream in(file_name);
        int numLines = 0;
        string unused;

        while (getline(in, unused)) {
            ++numLines;
        }

        int lineIndex = 0;

        while (lineIndex != numLines) {
            string name, surname;
            int group;
            string s;
            vector<int> grades;
            double scholarship;

            file >> name >> surname >> group >> s >> scholarship;

            for (size_t i = 0; i < s.size(); ++i) {
                grades.push_back(s[i] - '0');
            }

            Student student{name, surname, group, grades, scholarship};
            add_student(student);
            ++lineIndex;
        }

        file.close();
    }
}

void Stream::write_to_file(const string& file_name) const {
    ofstream file(file_name);

    for (const auto& group : groups) {
        for (const auto& student : group.students) {
            file << student.name << " " << student.surname << " " << student.group << " ";

            for (const auto& grade : student.grades) {
                file << grade;
            }

            file << " " << student.scholarship << endl;
        }
    }

    file.close();
}

void Stream::calculate_sum_scholarship() {
    sum_scholarship = 0;

    for (const auto& group : groups) {
        for (const auto& student : group.students) {
            sum_scholarship += student.scholarship;
        }
    }
}

int Stream::find_group(int number) const {
    auto it = find_if(groups.begin(), groups.end(), [number](const Group& group) {
        return group.number == number;
    });

    return it != groups.end() ? distance(groups.begin(), it) : -1;
}

int Stream::find_student(const string& name, const string& surname) const {
    auto it = find_if(groups.begin(), groups.end(), [name, surname](const Group& group) {
        return find_if(group.students.begin(), group.students.end(), [name, surname](const Student& student) {
            return student.name == name && student.surname == surname;
        }) != group.students.end();
    });

    return it != groups.end() ? distance(groups.begin(), it) : -1;
}

int main() {
    Stream stream;
    stream.read_from_file("students.txt");

    int choice;

    do {
        cout << "Выберите действие: " << endl;
        cout << "1. Добавить студента" << endl;
        cout << "2. Удалить студента" << endl;
        cout << "3. Добавить группу" << endl;
        cout << "4. Удалить группу" << endl;
        cout << "5. Вывести всех студентов" << endl;
        cout << "6. Вывести все группы" << endl;
        cout << "7. Сохранить данные в файл" << endl;
        cout << "0. Выйти" << endl;

        cin >> choice;

        switch (choice) {
            case 1: {
                string name, surname;
                int group;
                string s;
                vector<int> grades;
                double scholarship;

                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите фамилию: ";
                cin >> surname;
                cout << "Введите номер группы: ";
                cin >> group;
                cout << "Введите оценки через пробел: ";
                cin.ignore();
                getline(cin, s);
                cout << "Введите стипендию: ";
                cin >> scholarship;

                for (size_t i = 0; i < s.size(); ++i) {
                    grades.push_back(s[i] - '0');
                }

                Student student{name, surname, group, grades, scholarship};
                stream.add_student(student);
                break;
            }
            case 2: {
                string name, surname;
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите фамилию: ";
                cin >> surname;
                stream.remove_student(name, surname);
                break;
            }
            case 3:
                stream.add_group();
                break;
            case 4: {
                int number;
                cout << "Введите номер группы: ";
                cin >> number;
                stream.remove_group(number);
                break;
            }
            case 5:
                stream.print_all_students();
                break;
            case 6:
                stream.print_all_groups();
                break;
            case 7:
                stream.write_to_file("students.txt");
                break;
            case 0:
                break;
            default:
                cout << "Некорректный ввод" << endl;
                break;
        }

        cout << endl;
    } while (choice != 0);

    return 0;
}
