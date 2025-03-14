#include "Student.h"
#include <iostream>

int main() {
    vector<Student> students;
    //loadFromCSVFile(students, "data.csv");
    loadFromXMLFile(students, "data.xml");
    int choice;

    do {
        cout << "0. Display All Students\n";
        cout << "1. Add students\n2. Delete students\n3. Update Student Information\n4. Student Search\n";
        cout << "5. Manage Faculties\n6. Manage Student Statuses\n7. Manage Programs\n8. Search Student by Faculty\n9. Search Student by Faculty and Name\n";
        cout << "";
        cout << "10.Exit\nSelect: ";
        cin >> choice;

        switch (choice) {
            case 0: displayAllStudents(students); break;
            //Ex01
            case 1: addStudent(students); break;
            case 2: deleteStudent(students); break;
            case 3: updateStudent(students); break;
            case 4: searchStudent(students); break;
            //Ex02
            case 5: manageFaculties(); break; // Gọi hàm quản lý khoa
            case 6: manageStatuses(); break;  // Gọi hàm quản lý trạng thái
            case 7: managePrograms(); break;  // Gọi hàm quản lý chương trình
            case 8: searchStudentByFaculty(students); break; // Tìm kiến sinh viên bằng tên khoa
            case 9: searchStudentByFacultyAndName(students); break; // Tìm kiến sinh viên bằng tên khoa và tên sinh viên 

            case 10: cout << "Exit the program.\n"; break;
            default: cout << "Invalid Selection!\n";
        }
    } while (choice != 10);
    saveToFile(students, "data.csv");

    return 0;
}
