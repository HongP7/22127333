#include "Student.h"

int main() {
    vector<Student> students = {
        {"22127333", "Nguyen Hong Phuc", "07/02/2004", "Male", "Law Faculty", "22", "CLC", "Ho Chi Minh City", "nhphuc22@gmail.com", "0892983744", "Studying"},
        {"22128456", "Tran Thi Minh Chau", "15/06/2003", "Female", "Business English Faculty", "22", "Standard", "Ha Noi", "ttmchau03@gmail.com", "0912345678", "Graduated"},
        {"22129567", "Le Van Duc", "23/09/2005", "Male", "Japanese Faculty", "22", "CLC", "Da Nang", "lvduc05@yahoo.com", "0823456789", "Studying"},
        {"22121234", "Pham Hoang Nam", "11/11/2002", "Male", "French Faculty", "22", "Advanced", "Can Tho", "phnam02@hotmail.com", "0908765432", "Dropped out"},
        {"22127890", "Vo Thi Kim Ngan", "30/12/2004", "Female", "Law Faculty", "23", "Standard", "Hue", "vtkngan04@gmail.com", "0834567890", "Paused"}
    };
    
    int choice;

    do {
        cout << "1. Add students\n2. Delete students\n3. Student Search\n4. Update Student Information\n5. Display All Students\n6.Exit\nSelect: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: deleteStudent(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: displayAllStudents(students); break;
            case 6: cout << "Exit the program.\n"; break;
            default: cout << "Invalid Selection!\n";
        }
    } while (choice != 6);

    return 0;
}
