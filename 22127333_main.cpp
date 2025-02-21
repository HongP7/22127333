#include "Student.h"

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "1. Add students\n2. Delete students\n3. Student Search\n4. Exit\nSelect: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: deleteStudent(students); break;
            case 3: searchStudent(students); break;
            case 4: cout << "Exit the program.\n"; break;
            default: cout << "Invalid Selection!\n";
        }
    } while (choice != 4);

    return 0;
}
