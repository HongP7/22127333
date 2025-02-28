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
    string getFaculty() const;
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
void manageFaculties();
void manageStatuses();
void managePrograms();
void searchStudentByFaculty(const vector<Student> &students);
void searchStudentByFacultyAndName(const vector<Student> &students);

//test
void test();
void test3();

#endif // STUDENT_H
