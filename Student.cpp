#include "Student.h"
#include <regex>

// List of valid faculties and student statuses
vector<string> validFaculties = {"Law Faculty", "Business English Faculty", "Japanese Faculty", "French Faculty"};
vector<string> validStatuses = {"Studying", "Graduated", "Dropped out", "Paused"};
vector<string> programs = {"CLC", "Advanced", "Standard"};
// Getters
string Student::getId() const { return id; }
string Student::getName() const { return name; }
string Student::getFaculty() const { return faculty; }
string Student::getStatus() const { return status; }

// Setters
void Student::setName(string name) { this->name = name; }
void Student::setDob(string dob) { this->dob = dob; }
void Student::setGender(string gender) { this->gender = gender; }
void Student::setFaculty(string faculty) { this->faculty = faculty; }
void Student::setCourse(string course) { this->course = course; }
void Student::setProgram(string program) { this->program = program; }
void Student::setAddress(string address) { this->address = address; }
void Student::setEmail(string email) { this->email = email; }
void Student::setPhone(string phone) { this->phone = phone; }
void Student::setStatus(string status) { this->status = status; }

// Email validation
bool Student::isValidEmail(const string &email) {
    return regex_match(email, regex(R"(^[a-zA-Z0-9._%+-]+@gmail\.com$)"));
}

// Phone number validation
bool Student::isValidPhone(const string &phone) {
    return regex_match(phone, regex(R"(^0\d{9}$)"));
}

// Faculty validation
bool Student::isValidFaculty(const string &faculty) {
    return find(validFaculties.begin(), validFaculties.end(), faculty) != validFaculties.end();
}

// Status validation
bool Student::isValidStatus(const string &status) {
    return find(validStatuses.begin(), validStatuses.end(), status) != validStatuses.end();
}

// Display student information
void Student::display() const {
    cout << "Student ID: " << id << ", Name: " << name << ", Faculty: " << faculty
         << ", Email: " << email << ", Phone: " << phone << ", Status: " << status << endl;
}

// Student management functions
void addStudent(vector<Student> &students) {
    string id, name, dob, gender, faculty, course, program, address, email, phone, status;

    cout << "Enter Student ID: "; cin >> id;
    cin.ignore();
    cout << "Enter Full Name: "; getline(cin, name);
    cout << "Enter Date of Birth: "; getline(cin, dob);
    cout << "Enter Gender: "; getline(cin, gender);
    cout << "Enter Faculty: "; getline(cin, faculty);
    cout << "Enter Course: "; getline(cin, course);
    cout << "Enter Program: "; getline(cin, program);
    cout << "Enter Address: "; getline(cin, address);
    cout << "Enter Email: "; getline(cin, email);
    cout << "Enter Phone Number: "; getline(cin, phone);
    cout << "Enter Status: "; getline(cin, status);

    if (!Student::isValidEmail(email) || !Student::isValidPhone(phone) ||
        !Student::isValidFaculty(faculty) || !Student::isValidStatus(status)) {
        cout << "Invalid information. Please try again.\n";
        return;
    }

    students.emplace_back(id, name, dob, gender, faculty, course, program, address, email, phone, status);
    cout << "Student added successfully!\n";
}

void deleteStudent(vector<Student> &students) {
    string studentId;
    cout << "Enter Student ID to delete: "; cin >> studentId;

    auto it = remove_if(students.begin(), students.end(), [&studentId](const Student &s) { return s.getId() == studentId; });

    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found!\n";
    }
}

void searchStudent(const vector<Student> &students) {
    string keyword;
    cout << "Enter Student ID or Full Name to search: ";
    cin.ignore();
    getline(cin, keyword);
    bool check = 0;

    for (const auto &s : students) {
        if (s.getId() == keyword || s.getName().find(keyword) != string::npos) {
            s.display();
            check = 1;
        }
    }
    if (check == 0) 
        cout << "Student not found!\n";
}

void displayAllStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "No students found in the list.\n";
        return;
    }
    
    cout << "\n===== List of Students =====\n";
    for (const auto &s : students) {
        s.display();
    }
    cout << "============================\n";
}

void updateStudent(vector<Student> &students) {
    string studentId;
    cout << "Enter Student ID to update: ";
    cin >> studentId;

    // Tìm kiếm sinh viên trong danh sách
    for (auto &s : students) {
        if (s.getId() == studentId) {
            int choice;
            do {
                cout << "\nWhat do you want to update?\n";
                cout << "1. Full Name\n2. Date of Birth\n3. Gender\n4. Faculty\n";
                cout << "5. Course\n6. Program\n7. Address\n8. Email\n9. Phone Number\n";
                cout << "10. Status\n11. Exit Update\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // Loại bỏ ký tự xuống dòng

                string newValue;
                switch (choice) {
                    case 1:
                        cout << "Enter new Full Name: ";
                        getline(cin, newValue);
                        s.setName(newValue);
                        break;
                    case 2:
                        cout << "Enter new Date of Birth: ";
                        getline(cin, newValue);
                        s.setDob(newValue);
                        break;
                    case 3:
                        cout << "Enter new Gender: ";
                        getline(cin, newValue);
                        s.setGender(newValue);
                        break;
                    case 4:
                        cout << "Enter new Faculty: ";
                        getline(cin, newValue);
                        if (Student::isValidFaculty(newValue)) {
                            s.setFaculty(newValue);
                        } else {
                            cout << "Invalid Faculty!\n";
                        }
                        break;
                    case 5:
                        cout << "Enter new Course: ";
                        getline(cin, newValue);
                        s.setCourse(newValue);
                        break;
                    case 6:
                        cout << "Enter new Program: ";
                        getline(cin, newValue);
                        s.setProgram(newValue);
                        break;
                    case 7:
                        cout << "Enter new Address: ";
                        getline(cin, newValue);
                        s.setAddress(newValue);
                        break;
                    case 8:
                        cout << "Enter new Email: ";
                        getline(cin, newValue);
                        if (Student::isValidEmail(newValue)) {
                            s.setEmail(newValue);
                        } else {
                            cout << "Invalid Email! Must end with '@gmail.com'\n";
                        }
                        break;
                    case 9:
                        cout << "Enter new Phone Number: ";
                        getline(cin, newValue);
                        if (Student::isValidPhone(newValue)) {
                            s.setPhone(newValue);
                        } else {
                            cout << "Invalid Phone Number! Must start with 0 and have 10 digits.\n";
                        }
                        break;
                    case 10:
                        cout << "Enter new Status: ";
                        getline(cin, newValue);
                        if (Student::isValidStatus(newValue)) {
                            s.setStatus(newValue);
                        } else {
                            cout << "Invalid Status!\n";
                        }
                        break;
                    case 11:
                        cout << "Update complete!\n";
                        return;
                    default:
                        cout << "Invalid choice! Try again.\n";
                }
            } while (choice != 11);

            return;
        }
    }
    cout << "Student ID not found!\n";
}


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

