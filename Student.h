#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
private:
    string id, name, dob, gender, faculty, course, program, address, email, phone, status;

public:
    // Constructor
    Student(string id, string name, string dob, string gender, string faculty,
            string course, string program, string address, string email, string phone, string status)
            : id(id), name(name), dob(dob), gender(gender), faculty(faculty),
            course(course), program(program), address(address), email(email), phone(phone), status(status) {}

    // Getters & Setters
    string getId() const;
    string getName() const;
    string getDob() const;
    string getGender() const;
    string getFaculty() const;
    string getCourse() const;
    string getProgram() const;
    string getAddress() const;
    string getEmail() const;
    string getPhone() const;
    string getStatus() const;

    void setName(string name);
    void setDob(string dob);
    void setGender(string gender);
    void setFaculty(string faculty);
    void setCourse(string course);
    void setProgram(string program);
    void setAddress(string address);
    void setEmail(string email);
    void setPhone(string phone);
    void setStatus(string status);

    // Kiểm tra hợp lệ
    static bool isValidEmail(const string &email);
    static bool isValidPhone(const string &phone);
    static bool isValidFaculty(const string &faculty);
    static bool isValidStatus(const string &status);

    // Hiển thị thông tin sinh viên
    void display() const;
    
};

// Hàm quản lý danh sách sinh viên
void addStudent(vector<Student> &students);
void deleteStudent(vector<Student> &students);
void updateStudent(vector<Student> &students);
void searchStudent(const vector<Student> &students);
void displayAllStudents(const vector<Student> &students);

//Ex2
void manageFaculties(); //allow renaming faculties, adding new faculties
void manageStatuses(); //allow renaming student status, adding new statuses
void managePrograms(); //allow renaming program, adding new program 
//allow searching student by faculties, faculties + name 
void searchStudentByFaculty(const vector<Student> &students); 
void searchStudentByFacultyAndName(const vector<Student> &students);
//import students from CSV files
void saveToFile(const vector<Student> &students, const string &filename);
//save data into files
void loadFromFile(vector<Student> &students, const string &filename);

#endif // STUDENT_H
