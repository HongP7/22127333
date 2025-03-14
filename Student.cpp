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
void Student::setID(string id) { this->id = id; }
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

// Faculty validation
bool Student::isValidFaculty(const string &faculty) {
    return find(validFaculties.begin(), validFaculties.end(), faculty) != validFaculties.end();
}

// programs validation
bool Student::isValidPrograms(const string &programs_) {
    return find(programs.begin(), programs.end(), programs_) != programs.end();
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

    do {
        cout << "Enter student ID: ";
        cin >> id;

        if (findStudentById(students, id) != nullptr) 
            cout << "Student ID already exists. Please enter a new ID.\n";
        else 
            break; 
    } while (true);

    cin.ignore();
    cout << "Enter Full Name: "; getline(cin, name);
    cout << "Enter Date of Birth(dd/mm/yyyy): "; getline(cin, dob);
    cout << "Enter Gender(Male/Female): "; getline(cin, gender);

    cout << "Enter Faculty(";
    for (int i=0; i < validFaculties.size() - 1; i++) 
        cout << validFaculties[i] << ", ";
    cout << validFaculties[validFaculties.size()-1] << "): "; 
    getline(cin, faculty);

    cout << "Enter Course: "; getline(cin, course);
    cout << "Enter Program(";
    for (int i=0; i < programs.size() - 1; i++) 
        cout << programs[i] << ", ";
    cout << programs[programs.size()-1];
    cout << "): "; getline(cin, program);

    cout << "Enter Address: "; getline(cin, address);
    do {
        cout << "Enter Email(ABC@" << validDomain << "): "; getline(cin, email);
        if (!isValidEmailDomain(email, validDomain)) 
            cout << "Invalid email domain. Cannot update student.\n";
        else break;
        } while (true); 
    do {    
        cout << "Enter Phone Number(" << countryCode << "): "; getline(cin, phone);
        if (!isValidPhoneNumber(phone, countryCode)) 
            cout << "Invalid phone number. Cannot update student.\n";
        else break;
        } while (true);

    cout << "Enter Status(";
    for (int i=0; i < validStatuses.size() - 1; i++) 
        cout << validStatuses[i] << ", ";
    cout << validStatuses[validStatuses.size()-1];
    cout << "): "; getline(cin, status);

    if (!Student::isValidFaculty(faculty) || !Student::isValidStatus(status)) {
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
    } else 
        cout << "Student not found!\n";
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

    for (auto &s : students) {
        if (s.getId() == studentId) {
            int choice;
            do {
                cout << "\nWhat do you want to update?\n";
                cout << "0. ID\n1. Full Name\n2. Date of Birth\n3. Gender\n4. Faculty\n";
                cout << "5. Course\n6. Program\n7. Address\n8. Email\n9. Phone Number\n";
                cout << "10. Status\n11. Exit Update\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // Loại bỏ ký tự xuống dòng

                string newValue;
                switch (choice) {
                    case 0:
                        do {
                            cout << "Enter student ID: ";
                            getline(cin, newValue);
                    
                            if (findStudentById(students, newValue) != nullptr) 
                                cout << "Student ID already exists. Please enter a new ID.\n";
                            else 
                                s.setID(newValue);
                        } while (true);
                        break;
                    case 1:
                        cout << "Enter new Full Name: ";
                        getline(cin, newValue);
                        s.setName(newValue);
                        break;
                    case 2:
                        cout << "Enter new Date of Birth(dd/mm/yyyy): ";
                        getline(cin, newValue);
                        s.setDob(newValue);
                        break;
                    case 3:
                        cout << "Enter new Gender(Male/Female): ";
                        getline(cin, newValue);
                        s.setGender(newValue);
                        break;
                    case 4:
                        cout << "Enter new Faculty(";
                        for (int i=0; i < validFaculties.size() - 1; i++) 
                            cout << validFaculties[i] << ", ";
                        cout << validFaculties[validFaculties.size()-1] << "): ";
                        getline(cin, newValue);
                        if (Student::isValidFaculty(newValue)) 
                            s.setFaculty(newValue);
                        else 
                            cout << "Invalid Faculty!\n";
                        break;
                    case 5:
                        cout << "Enter new Course: ";
                        getline(cin, newValue);
                        s.setCourse(newValue);
                        break;
                    case 6:
                        cout << "Enter new Program: ";
                        for (int i=0; i < programs.size() - 1; i++) 
                            cout << programs[i] << ", ";
                        cout << programs[programs.size()-1] << "): ";
                        getline(cin, newValue);
                        if (Student::isValidFaculty(newValue)) 
                            s.setProgram(newValue);
                        else 
                            cout << "Invalid Programs!\n";
                        break;
                    case 7:
                        cout << "Enter new Address: ";
                        getline(cin, newValue);
                        s.setAddress(newValue);
                        break;
                    case 8:
                        do {
                            cout << "Enter Email(ABC@" << validDomain << "): "; getline(cin, newValue);
                            if (!isValidEmailDomain(newValue, validDomain)) 
                                cout << "Invalid email domain. Cannot update student.\n";
                            else  s.setEmail(newValue);
                            } while (true); 
                        break;
                    case 9:
                        do {
                            cout << "Enter Phone Number(" << countryCode << "): "; getline(cin, newValue);
                            if (!isValidEmailDomain(newValue, validDomain)) 
                                cout << "Invalid phone number. Cannot update student.\n";
                            else  s.setEmail(newValue);
                            } while (true); 
                        break;
                    case 10:
                        cout << "Enter new Status: ";
                        getline(cin, newValue);
                        if (Student::isValidStatus(newValue)) {
                            if(checkStatus(s.getStatus(), newValue))
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

bool isValidEmailDomain(const string &email, const string &domain) {
    // Tạo biểu thức chính quy để kiểm tra email
    string pattern = "^[\\w.-]+@" + domain + "$";
    regex emailRegex(pattern);
    return regex_match(email, emailRegex);
}

bool isValidPhoneNumber(const string &phone, const string &countryCode) {
    // Tạo biểu thức chính quy để kiểm tra số điện thoại
    string pattern = "^" + countryCode + "\\d{9,10}$";
    regex phoneRegex(pattern);
    return regex_match(phone, phoneRegex);
}

bool checkStatus(const string &status, const string &newStatus) {
    if (status == "Studying")  return true;
    if (status == "Graduated") {
        if (newStatus == "Studying" || newStatus == "Dropped out" || newStatus == "Paused")
            return false;
        else return true;
    }
}