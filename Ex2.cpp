#include "Student.h"
#include <fstream>
#include <regex>

//EX2
void manageFaculties() {
    int choice;
    do {
        cout << "\n=== Manage Faculties ===\n";
        cout << "1. Rename a Faculty\n";
        cout << "2. Add New Faculty\n";
        cout << "3. Show All Faculties\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Current Faculties:\n";
            for (size_t i = 0; i < validFaculties.size(); i++) {
                cout << i + 1 << ". " << validFaculties[i] << endl;
            }
            int index;
            cout << "Enter number to rename: ";
            cin >> index;
            cin.ignore();
            if (index >= 1 && index <= validFaculties.size()) {
                cout << "Enter new name: ";
                getline(cin, validFaculties[index - 1]);
            } else {
                cout << "Invalid choice!\n";
            }
        } else if (choice == 2) {
            string newFaculty;
            cout << "Enter new faculty name: ";
            getline(cin, newFaculty);
            validFaculties.push_back(newFaculty);
            cout << "Faculty added successfully!\n";
        } else if (choice == 3) {
            cout << "\nList of Faculties:\n";
            for (const auto &faculty : validFaculties) {
                cout << "- " << faculty << endl;
            }
        }
    } while (choice != 4);
}

void manageStatuses() {
    int choice;
    do {
        cout << "\n=== Manage Student Statuses ===\n";
        cout << "1. Rename a Status\n";
        cout << "2. Add New Status\n";
        cout << "3. Show All Statuses\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Current Statuses:\n";
            for (size_t i = 0; i < validStatuses.size(); i++) {
                cout << i + 1 << ". " << validStatuses[i] << endl;
            }
            int index;
            cout << "Enter number to rename: ";
            cin >> index;
            cin.ignore();
            if (index >= 1 && index <= validStatuses.size()) {
                cout << "Enter new name: ";
                getline(cin, validStatuses[index - 1]);
            } else {
                cout << "Invalid choice!\n";
            }
        } else if (choice == 2) {
            string newStatus;
            cout << "Enter new status name: ";
            getline(cin, newStatus);
            validStatuses.push_back(newStatus);
            cout << "Status added successfully!\n";
        } else if (choice == 3) {
            cout << "\nList of Statuses:\n";
            for (const auto &status : validStatuses) {
                cout << "- " << status << endl;
            }
        }
    } while (choice != 4);
}

void managePrograms() {
    int choice;
    do {
        cout << "\n=== Manage Programs ===\n";
        cout << "1. Rename a Program\n";
        cout << "2. Add New Program\n";
        cout << "3. Show All Programs\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Current Programs:\n";
            for (size_t i = 0; i < programs.size(); i++) {
                cout << i + 1 << ". " << programs[i] << endl;
            }
            int index;
            cout << "Enter number to rename: ";
            cin >> index;
            cin.ignore();
            if (index >= 1 && index <= programs.size()) {
                cout << "Enter new name: ";
                getline(cin, programs[index - 1]);
            } else {
                cout << "Invalid choice!\n";
            }
        } else if (choice == 2) {
            string newProgram;
            cout << "Enter new program name: ";
            getline(cin, newProgram);
            programs.push_back(newProgram);
            cout << "Program added successfully!\n";
        } else if (choice == 3) {
            cout << "\nList of Programs:\n";
            for (const auto &program : programs) {
                cout << "- " << program << endl;
            }
        }
    } while (choice != 4);
}

void searchStudentByFaculty(const vector<Student> &students) {
    string faculty;
    cout << "Enter Faculty Name: ";
    cin.ignore();
    getline(cin, faculty);

    cout << "\n=== Students in " << faculty << " ===\n";
    bool found = false;
    for (const auto &s : students) {
        if (s.getFaculty() == faculty) {
            s.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No students found in this faculty.\n";
    }
}

void searchStudentByFacultyAndName(const vector<Student> &students) {
    string faculty, name;
    cout << "Enter Faculty Name: ";
    cin.ignore();
    getline(cin, faculty);
    
    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "\n=== Students in " << faculty << " with name '" << name << "' ===\n";
    bool found = false;
    for (const auto &s : students) {
        if (s.getFaculty() == faculty && s.getName().find(name) != string::npos) {
            s.display();
            found = true;
        }
    }
    if (!found) {
        cout << "No students found matching the criteria.\n";
    }
}

void saveToFile(const vector<Student> &students, const string &filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    // Ghi tiêu đề cột
    file << "Student ID,Full Name,Date of Birth,Gender,Faculty,Course,Program,Address,Email,Phone,Status\n";

    // Ghi dữ liệu từng sinh viên vào file
    for (const auto &s : students) {
        file << s.getId() << ","
             << s.getName() << ","
             << s.getDob() << ","
             << s.getGender() << ","
             << s.getFaculty() << ","
             << s.getCourse() << ","
             << s.getProgram() << ","
             << s.getAddress() << ","
             << s.getEmail() << ","
             << s.getPhone() << ","
             << s.getStatus() << "\n";
    }

    file.close();
    cout << "Data successfully saved to " << filename << endl;
}
