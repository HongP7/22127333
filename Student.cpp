#include "Student.h"
#include <regex>

// List of valid faculties and student statuses
const vector<string> validFaculties = {"Law Faculty", "Business English Faculty", "Japanese Faculty", "French Faculty"};
const vector<string> validStatuses = {"Studying", "Graduated", "Dropped out", "Paused"};

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

    for (const auto &s : students) {
        if (s.getId() == keyword || s.getName().find(keyword) != string::npos) {
            s.display();
        }
    }
}
