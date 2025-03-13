#include "Student.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <sstream>
using namespace std;

// List of valid faculties and student statuses
vector<string> validFaculties = {"Law Faculty", "Business English Faculty", "Japanese Faculty", "French Faculty"};
vector<string> validStatuses = {"Studying", "Graduated", "Dropped out", "Paused"};
vector<string> programs = {"CLC", "Advanced", "Standard"};

//
string validDomain = "student.university.edu.vn";
string countryCode = "+84";
// Getters
string Student::getId() const { return id; }
string Student::getName() const { return name; }
string Student::getDob() const { return dob; }
string Student::getGender() const { return gender; }
string Student::getFaculty() const { return faculty; }
string Student::getCourse() const { return course; }
string Student::getProgram() const { return program; }
string Student::getAddress() const { return address; }
string Student::getEmail() const { return email; }
string Student::getPhone() const { return phone; }
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

void loadFromCSVFile(vector<Student> &students, const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    students.clear(); // Xóa dữ liệu cũ trong vector trước khi nạp mới

    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        string studentID, fullName, dob, gender, faculty, course, program, address, email, phone, status;

        getline(ss, studentID, ',');
        getline(ss, fullName, ',');
        getline(ss, dob, ',');
        getline(ss, gender, ',');
        getline(ss, faculty, ',');
        getline(ss, course, ',');
        getline(ss, program, ',');
        getline(ss, address, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, status, ',');

        students.emplace_back(studentID, fullName, dob, gender, faculty, course, program, address, email, phone, status);
    }
    file.close();
}

string extractValue(const string &line, const string &tag) {
    size_t start = line.find("<" + tag + ">");
    size_t end = line.find("</" + tag + ">");
    if (start == string::npos || end == string::npos) return "";
    start += tag.length() + 2;  // Để bỏ qua <tag>
    return line.substr(start, end - start);
}

// Hàm đọc dữ liệu từ file XML và lưu vào vector<Student>
void loadFromXMLFile(vector<Student> &students, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    students.clear();
    string id, name, dob, gender, faculty, course, program, address, email, phone, status;
    string line;

    while (getline(file, line)) {
        if (line.find("<Student>") != string::npos) { 
            // Bắt đầu một sinh viên mới -> reset các biến
            id = name = dob = gender = faculty = course = program = address = email = phone = status = "";
        } else if (line.find("<StudentID>") != string::npos) id = extractValue(line, "StudentID");
        else if (line.find("<FullName>") != string::npos) name = extractValue(line, "FullName");
        else if (line.find("<DateOfBirth>") != string::npos) dob = extractValue(line, "DateOfBirth");
        else if (line.find("<Gender>") != string::npos) gender = extractValue(line, "Gender");
        else if (line.find("<Faculty>") != string::npos) faculty = extractValue(line, "Faculty");
        else if (line.find("<Course>") != string::npos) course = extractValue(line, "Course");
        else if (line.find("<Program>") != string::npos) program = extractValue(line, "Program");
        else if (line.find("<Address>") != string::npos) address = extractValue(line, "Address");
        else if (line.find("<Email>") != string::npos) email = extractValue(line, "Email");
        else if (line.find("<Phone>") != string::npos) phone = extractValue(line, "Phone");
        else if (line.find("<Status>") != string::npos) status = extractValue(line, "Status");
        else if (line.find("</Student>") != string::npos) { 
            // Kết thúc sinh viên, thêm vào danh sách bằng emplace_back
            students.emplace_back(id, name, dob, gender, faculty, course, program, address, email, phone, status);
        }
    }

    file.close();
}

// Ex3
Student* findStudentById(vector<Student> &students, const string &id) {
    for (auto &student : students) {
        if (student.getId() == id) {
            return &student;
        }
    }
    return nullptr;
}

void addStudentWithCheck(vector<Student> &students, const string &validDomain, const string &countryCode) {
    string id, name, dob, gender, faculty, course, program, address, email, phone, status;
    cout << "Enter student ID: ";
    cin >> id;
    if (findStudentById(students, id) != nullptr) {
        cout << "Student ID already exists. Cannot add student.\n";
        return;
    }
    // Nhập các thông tin khác của sinh viên
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter date of birth (dd/mm/yyyy): ";
    cin >> dob;
    cout << "Enter gender: ";
    cin >> gender;
    cout << "Enter faculty: ";
    cin >> faculty;
    cout << "Enter course: ";
    cin >> course;
    cout << "Enter program: ";
    cin >> program;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter email: ";
    cin >> email;
    if (!isValidEmailDomain(email, validDomain)) {
        cout << "Invalid email domain. Cannot add student.\n";
        return;
    }
    cout << "Enter phone: ";
    cin >> phone;
    if (!isValidPhoneNumber(phone, countryCode)) {
        cout << "Invalid phone number. Cannot add student.\n";
        return;
    }
    cout << "Enter status: ";
    cin >> status;

    students.emplace_back(id, name, dob, gender, faculty, course, program, address, email, phone, status);
    cout << "Student added successfully.\n";
}

void updateStudentWithCheck(vector<Student> &students, const string &validDomain, const string &countryCode) {
    string id;
    cout << "Enter student ID to update: ";
    cin >> id;
    Student* student = findStudentById(students, id);
    if (student == nullptr) {
        cout << "Student ID not found. Cannot update student.\n";
        return;
    }
    // Nhập các thông tin mới của sinh viên
    string name, dob, gender, faculty, course, program, address, email, phone, status;
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter new date of birth (dd/mm/yyyy): ";
    cin >> dob;
    cout << "Enter new gender: ";
    cin >> gender;
    cout << "Enter new faculty: ";
    cin >> faculty;
    cout << "Enter new course: ";
    cin >> course;
    cout << "Enter new program: ";
    cin >> program;
    cout << "Enter new address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter new email: ";
    cin >> email;
    if (!isValidEmailDomain(email, validDomain)) {
        cout << "Invalid email domain. Cannot update student.\n";
        return;
    }
    cout << "Enter new phone: ";
    cin >> phone;
    if (!isValidPhoneNumber(phone, countryCode)) {
        cout << "Invalid phone number. Cannot update student.\n";
        return;
    }
    cout << "Enter new status: ";
    cin >> status;

    student->setName(name);
    student->setDob(dob);
    student->setGender(gender);
    student->setFaculty(faculty);
    student->setCourse(course);
    student->setProgram(program);
    student->setAddress(address);
    student->setEmail(email);
    student->setPhone(phone);
    student->setStatus(status);

    cout << "Student updated successfully.\n";
}

void manageStudents(vector<Student> &students) {
    int choice;
    do {
        cout << "1. Add Student\n2. Update Student\n3. Exit\nSelect: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudentWithCheck(students, validDomain, countryCode);
                break;
            case 2:
                updateStudentWithCheck(students, validDomain, countryCode);
                break;
            case 3:
                cout << "Exiting student management.\n";
                break;
            default:
                cout << "Invalid selection! Please try again.\n";
        }
    } while (choice != 3);
}


// Hàm kiểm tra email hợp lệ với tên miền cấu hình động
bool isValidEmailDomain(const string &email, const string &domain) {
    // Tạo biểu thức chính quy để kiểm tra email
    string pattern = "^[\\w.-]+@" + domain + "$";
    regex emailRegex(pattern);
    return regex_match(email, emailRegex);
}

// Hàm kiểm tra số điện thoại hợp lệ với mã quốc gia cấu hình động
bool isValidPhoneNumber(const string &phone, const string &countryCode) {
    // Tạo biểu thức chính quy để kiểm tra số điện thoại
    string pattern = "^" + countryCode + "\\d{9,10}$";
    regex phoneRegex(pattern);
    return regex_match(phone, phoneRegex);
}

