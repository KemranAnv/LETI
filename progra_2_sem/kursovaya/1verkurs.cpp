#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int groupNumber;
    float scholarship;
    float grades[5];
};

struct Group {
    int groupNumber;
    int numStudents;
    int numFailing;
    Student* students;
    float scholarship;
};

Group** groups;
int numGroups;

void printAllStudents() {
    for (int i = 0; i < numGroups; i++) {
        for (int j = 0; j < groups[i]->numStudents; j++) {
            cout << "Имя студента: " << groups[i]->students[j].name << endl;
            cout << "Номер группы: " << groups[i]->students[j].groupNumber << endl;
            cout << "Оценки: ";
            for (int k = 0; k < 5; k++) {
                cout << groups[i]->students[j].grades[k] << " ";
            }
            cout << endl << "Стипендия: " << groups[i]->students[j].scholarship << endl;
        }
    }
}

void writeToFile(string filename) {
    ofstream fout(filename);
    fout << numGroups << endl;
    for (int i = 0; i < numGroups; i++) {
        fout << groups[i]->groupNumber << " ";
        fout << groups[i]->numStudents << " ";
        fout << groups[i]->numFailing << " ";
        fout << groups[i]->scholarship << endl;
        for (int j = 0; j < groups[i]->numStudents; j++) {
            fout << groups[i]->students[j].name << " ";
            fout << groups[i]->students[j].groupNumber << " ";
            for (int k = 0; k < 5; k++) {
                fout << groups[i]->students[j].grades[k] << " ";
            }
            fout << groups[i]->students[j].scholarship << endl;
        }
    }
    fout.close();
}

void readFromFile(string filename) {
    ifstream fin(filename);
    fin >> numGroups;
    groups = new Group*[numGroups];
    for (int i = 0; i < numGroups; i++) {
        groups[i] = new Group;
        fin >> groups[i]->groupNumber;
        fin >> groups[i]->numStudents;
        fin >> groups[i]->numFailing;
        fin >> groups[i]->scholarship;
        groups[i]->students = new Student[groups[i]->numStudents];
        for (int j = 0; j < groups[i]->numStudents; j++) {
            fin >> groups[i]->students[j].name;
            fin >> groups[i]->students[j].groupNumber;
            for (int k = 0; k < 5; k++) {
                fin >> groups[i]->students[j].grades[k];
            }
            fin >> groups[i]->students[j].scholarship;
        }
    }
    fin.close();
}

void addGroup(int groupNumber, int numStudents, float scholarship, float* grades) {
    Group* newGroup = new Group;
    newGroup->groupNumber = groupNumber;
    newGroup->numStudents = numStudents;
    newGroup->numFailing = 0;
    newGroup->scholarship = scholarship;
    newGroup->students = new Student[numStudents];

    for (int i = 0; i < numStudents; i++) {
        newGroup->students[i].groupNumber = groupNumber;
        newGroup->students[i].scholarship = scholarship;
        for (int j = 0; j < 5; j++) {
            newGroup->students[i].grades[j] = grades[j];
            if (grades[j] < 4.0) {
                newGroup->numFailing++;
            }
        }
    }

    Group** newGroups = new Group*[numGroups + 1];
    for (int i = 0; i < numGroups; i++) {
        newGroups[i] = groups[i];
    }
    newGroups[numGroups] = newGroup;
    numGroups++;

    delete[] groups;
    groups = newGroups;
}

void removeGroup(int groupNumber) {
    int index = -1;
    for (int i = 0; i < numGroups; i++) {
        if (groups[i]->groupNumber == groupNumber) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Группа не найдена" << endl;
        return;
    }

    delete[] groups[index]->students;
    delete groups[index];

    for (int i = index; i < numGroups - 1; i++) {
        groups[i] = groups[i + 1];
    }

    numGroups--;

    Group** newGroups = new Group*[numGroups];
    for (int i = 0; i < numGroups; i++) {
        newGroups[i] = groups[i];
    }

    delete[] groups;
    groups = newGroups;
}

void printGroup(int groupNumber) {
    for (int i = 0; i < numGroups; i++) {
        if (groups[i]->groupNumber == groupNumber) {
            cout << "Группа " << groupNumber << ":" << endl;
            for (int j = 0; j < groups[i]->numStudents; j++) {
                cout << "Имя студента: " << groups[i]->students[j].name << endl;
                cout << "Оценки: ";
                for (int k = 0; k < 5; k++) {
                    cout << groups[i]->students[j].grades[k] << " ";
                }
                cout << endl << "Стипендия: " << groups[i]->students[j].scholarship << endl;
            }
            cout << "Количество неуспевающих: " << groups[i]->numFailing << endl;
            cout << "Средняя стипендия: " << groups[i]->scholarship << endl;
            return;
        }
    }
    cout << "Группа не найдена" << endl;
}

void printAllGroups() {
    for (int i = 0; i < numGroups; i++) {
        cout << "Группа " << groups[i]->groupNumber << ":" << endl;
        for (int j = 0; j < groups[i]->numStudents; j++) {
            cout << "Имя студента: " << groups[i]->students[j].name << endl;
        }
        cout << "Количество неуспевающих: " << groups[i]->numFailing << endl;
        cout << "Средняя стипендия: " << groups[i]->scholarship << endl;
    }
}

int main() {
    groups = nullptr;
    numGroups = 0;

    float grades[5] = { 5.0, 4.0, 5.0, 4.0, 5.0 };
    addGroup(1, 2, 2000, grades);

    grades[0] = 4.0;
    addGroup(2, 3, 1500, grades);

    printAllStudents();

    removeGroup(2);

    printAllGroups();

    writeToFile("data.txt");

    readFromFile("data.txt");

    printAllGroups();

    return 0;
}