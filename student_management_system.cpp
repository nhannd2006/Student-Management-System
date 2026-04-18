/******************************************************************************
 * Project: Student Information Management System
 * Course: Advanced Programming (Kỹ thuật lập trình)
 * Author: Nguyễn Đăng Nhân (ID: 24280038) 
 * Class: 24KDL1
 * University: VNU-HCM, University of Science (Trường Đại học Khoa học Tự nhiên, Đại học Quốc gia TP. Hồ Chí Minh)
 * Completion Date: 21/06/2025
 * Description: A C++ program for managing student records with sorting and statistical analysis features.
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

// -----

const char *FILE_PATH = "student_list.txt";
const int NUM_SUBJECTS = 2;
const char SUBJECTS[NUM_SUBJECTS][20] = {"Math", "Literature"};
const int MAX_STUDENTS = 100;

struct Name {
    char last[84], first[15];
};
struct Date {
    int day, month, year;
};

struct Student {
    char id[20];
    Name name;
    Date birthDate;
    char address[100];
    char email[100];
    char phoneNum[20];
    float Scores[NUM_SUBJECTS];
};
struct StudentList {
    Student students[MAX_STUDENTS];
    int count;
};

// -----

//
// Check data and file
void checkFile(ios &file);
//
bool checkId(StudentList list, char *id);
bool checkDate(Date birthDate);
bool checkEmail(char *email);
bool checkPhoneNum(char *phoneNum);
bool checkScore(float score);

//
// Format and convert data
void formatName(char *name);
void splitName(const char *nameStr, Name &name);
void splitDate(const char *dateStr, Date &birthDate);
void formatAddress(char *address);
float convertScore(const char *scoreStr);
//
void normalizeString(char *string);

//
// Input, output and file handling
void inputId(StudentList list, Student &student);
void inputName(Student &student);
void inputBirthDate(Student &student);
void inputAddress(Student &student);
void inputEmail(Student &student);
void inputPhone(Student &student);
void inputScore(Student &student, int subject);
//
void outputStudent(Student student);
//
void readData(ifstream &inputFile, StudentList &studentList);
//
void writeData(ofstream &outputFile, Student student);

//
// MANAGE:
void manageStudents(ofstream &outputFile, StudentList &studentList);
// Confirm changes
bool confirmChanges();
//
void addStudent(ofstream &outputFile, StudentList &studentList);
void editStudent(ofstream &outputFile, StudentList &studentList);
void deleteStudent(ofstream &outputFile, StudentList &studentList);

//
// SEARCH:
void searchStudents(ofstream &outputFile, StudentList &studentList);
// Find position by id and name
int findIdPosition(StudentList studentList, const char *id);
void findNamePositions(StudentList studentList, const char *keyword, int *positions, int &numPositions);
//
void searchExactId(ofstream &outputFile, StudentList &studentList);
void searchApproximateName(ofstream &outputFile, StudentList &studentList);

//
// STATISTICS:
void statisticsStudents(ofstream &outputFile, StudentList &studentList);
// Calculate average score
float calculateAverageScore(Student student);
// Output student list with sorting
void outputStudentList(StudentList studentList);
//
void displayStudentList(ofstream &outputFile, StudentList &studentList);
void sortById(ofstream &outputFile, StudentList &studentList);
void sortByName(ofstream &outputFile, StudentList &studentList);
void sortByAverageScore(ofstream &outputFile, StudentList &studentList);
//
void reportStatistics(ofstream &outputFile, StudentList &studentList);


//
// MAIN MENU:
void mainMenu(ofstream &outputFile, StudentList &studentList);


// -----


int main() {
    ifstream inputFile;
    ofstream outputFile;
    StudentList studentList;
    readData(inputFile, studentList);
    mainMenu(outputFile, studentList);
    return 0;
}


// -----


void checkFile(ios &file) {
    if (!file) cout << "File " << FILE_PATH << " cannot be opened. Please check again.\n";
}

bool checkId(StudentList studentList, char *id) {
    for (int i = 0; i < studentList.count; i++)
        if (strcmp(studentList.students[i].id, id) == 0) return true;
    return false;
}

bool checkEmail(char *email) {
    if (strlen(email) < 5) return false;
    int atCount = 0;
    int atPosition = -1;
    if (email[0] == '.' || email[0] == '@' || email[strlen(email)-1] == '.' || email[strlen(email)-1] == '@') return false;
    for (int i = 0; i < (int)strlen(email); i++) {
        char ch = email[i];
        if (ch == '@') {
            atCount++;
            atPosition = i;
        }
        if (!isalnum(ch) && ch != '.' && ch != '@' && ch != '_' && ch != '-') return false;
        if (i > 0) {
            if (ch == '.' && (email[i-1] == '.' || email[i-1] == '@')) return false;
            if (ch == '@' && email[i-1] == '.') return false;
        }
    }
    if (atCount != 1) return false;
    int dotCount = 0;
    for (int i = atPosition + 1; i < (int)strlen(email); i++) {
        if (email[i] == '.') dotCount++;
    }
    if (dotCount == 0) return false;
    return true;
}

bool checkDate(Date birthDate) {
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (birthDate.year < 1990 || birthDate.year > 2024) return false;
    else {
        if ((birthDate.year % 4 == 0 && birthDate.year % 100 != 0) || (birthDate.year % 400 == 0)) monthDays[1] = 29;
    }
    if (birthDate.month < 1 || birthDate.month > 12) return false;
    if (birthDate.day < 1 || birthDate.day > monthDays[birthDate.month-1]) return false;
    return true;
}

bool checkPhone(char *phoneNum) {
    if (strlen(phoneNum) != 10) return false;
    if (phoneNum[0] != '0') return false;
    for (int i = 0; i < 10; i++) {
        if (phoneNum[i] < '0' || phoneNum[i] > '9') return false;
    }
    return true;
}

bool checkScore(float score) {
    if (score < 0 || score > 10) return false;
    else return true;
}

// -

void formatName(char *name) {
    for (int i = 0; i < (int)strlen(name); i++) {
        if (name[i] >= 'a' && name[i] <= 'z') name[i] = name[i] - 32;
    }
}

void splitName(const char *nameString, Name &name) {
    int lastPosition = -1;
    for (int i = strlen(nameString) - 1; i >= 0; i--) {
        if (nameString[i] == ' ') {
            lastPosition = i;
            break;
        }
    }
    if (lastPosition == -1) {
        name.last[0] = '\0';
        strcpy(name.first, nameString);
    } else {
        strncpy(name.last, nameString, lastPosition);
        name.last[lastPosition] = '\0';
        strcpy(name.first, nameString+lastPosition+1);
    }
}

void splitDate(const char *dateString, Date &birthDate) {
    birthDate.day = (dateString[0]-'0')*10 + (dateString[1]-'0');
    birthDate.month = (dateString[3]-'0')*10 + (dateString[4]-'0');
    birthDate.year = (dateString[6]-'0')*1000 + (dateString[7]-'0')*100 + (dateString[8]-'0')*10 + (dateString[9]-'0');
}

void formatAddress(char *address) {
    for (int i = 0; i < (int)strlen(address); i++) {
        if (i == 0 || address[i-1] == ' ') {
            if (address[i] >= 'a' && address[i] <= 'z') address[i] -= 32;
        } else {
            if (address[i] >= 'A' && address[i] <= 'Z') address[i] += 32;
        }
    }
}

float convertScore(const char *scoreString) {
    float result = 0.0;
    float decimalPart = 0;
    float decimalFactor = 0.1;
    int dotCount = 0;
    bool afterDot = false;
    for (int i = 0; i < (int)strlen(scoreString); i++) {
        if (scoreString[i] == '.') {
            dotCount++;
            if (dotCount > 1) return -1.0;
            afterDot = true;
        } else if (scoreString[i] >= '0' && scoreString[i] <= '9') {
            if (afterDot) {
                decimalPart += (scoreString[i] - '0')*decimalFactor;
                decimalFactor /= 10;
            } else result = result*10 + (scoreString[i] - '0');
        } else {
            return -1.0;
        }
    }
    result += decimalPart;
    result = (int)(result*10 + 0.5) / 10.0;
    return result;
}

void normalizeString(char *str) {
    int position = 0;
    while (str[position] == ' ') position++;
    int writePosition = 0;
    bool hasSpace = false;
    while (str[position] != '\0') {
        if (str[position] != ' ') {
            str[writePosition++] = str[position];
            hasSpace = false;
        } else if (!hasSpace) {
            str[writePosition++] = ' ';
            hasSpace = true;
        }
        position++;
    }
    while (writePosition > 0 && str[writePosition-1] == ' ') writePosition--;
    str[writePosition] = '\0';
}

// -

void inputId(StudentList studentList, Student &student) {
    do {
        cout << "Enter student ID: ";
        cin.getline(student.id, 20);
    } while (checkId(studentList, student.id));
}

void inputName(Student &student) {
    cout << "Enter student's last and first name: ";
    char fullName[100];
    cin.getline(fullName, 100);
    formatName(fullName);
    splitName(fullName, student.name);
}

void inputBirthDate(Student &student) {
    do {
        cout << "Enter student's birth date [dd/mm/yyyy]: ";
        char dateString[11];
        cin.getline(dateString, 11);
        splitDate(dateString, student.birthDate);
    } while (checkDate(student.birthDate) == false);
}

void inputAddress(Student &student) {
    cout << "Enter student's address: ";
    cin.getline(student.address, 100);
    formatAddress(student.address);
}

void inputEmail(Student &student) {
    do {
        cout << "Enter student's email: ";
        cin.getline(student.email, 100);
    } while (checkEmail(student.email) == false);
}

void inputPhone(Student &student) {
    do {
        cout << "Enter student's phone number: ";
        cin.getline(student.phoneNum, 20);
    } while (checkPhone(student.phoneNum) == false);
}

void inputScore(Student &student, int subject) {
    do {
        cout << "Enter student's score for subject " << SUBJECTS[subject] << ": ";
        cin >> student.Scores[subject];
        cin.ignore();
    } while (checkScore(student.Scores[subject]) == false);
}

void outputStudent(Student student) {
    cout << ">> ";
    cout << student.id << " | ";
    cout << student.name.last << " " << student.name.first << " | ";
    cout << setfill('0') << setw(2) << student.birthDate.day << "/";
    cout << setfill('0') << setw(2) << student.birthDate.month << "/";
    cout << student.birthDate.year << " | ";
    cout << student.address << " | ";
    cout << student.email << " | ";
    cout << student.phoneNum << " | ";
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        cout << fixed << setprecision(1) << student.Scores[i];
        if (i < NUM_SUBJECTS - 1) cout << " ; ";
    }
    cout << endl;
}

void readData(ifstream &inputFile, StudentList &studentList) {
    inputFile.open(FILE_PATH);
    checkFile(inputFile);
    studentList.count = 0;
    char line[400];
    while (inputFile.getline(line,400) && studentList.count <= MAX_STUDENTS) {
        Student student;
        char *token = strtok(line,"|");
        int infoType = 0;
        while (token != NULL) {
            normalizeString(token);
            switch (infoType) {
                case 0:
                    strcpy(student.id, token);
                    break;
                case 1:
                    char fullName[100];
                    strcpy(fullName, token);
                    fullName[strlen(token)] = '\0';
                    splitName(fullName, student.name);
                    break;
                case 2:
                    splitDate(token, student.birthDate);
                    break;
                case 3:
                    strcpy(student.address, token);
                    break;
                case 4:
                    strcpy(student.email, token);
                    break;
                case 5:
                    strcpy(student.phoneNum, token);
                    break;
                case 6:
                    char *scoreToken = strtok(token, ";");
                    for (int i = 0; i < NUM_SUBJECTS && scoreToken != NULL; i++) {
                        normalizeString(scoreToken);
                        student.Scores[i] = convertScore(scoreToken);
                        scoreToken = strtok(NULL, ";");
                    }
                    break;
            }
            infoType++;
            token = strtok(NULL, "|");        
        }
        studentList.students[studentList.count] = student;
        studentList.count++;
    }
    inputFile.close();
}

void writeData(ofstream &outputFile, Student student) {
    outputFile << student.id << " | ";
    outputFile << student.name.last << " " << student.name.first << " | ";
    outputFile << setfill('0') << setw(2) << student.birthDate.day << "/";
    outputFile << setfill('0') << setw(2) << student.birthDate.month << "/";
    outputFile << student.birthDate.year << " | ";
    outputFile << student.address << " | ";
    outputFile << student.email << " | ";
    outputFile << student.phoneNum << " | ";
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        outputFile << fixed << setprecision(1) << student.Scores[i];
        if (i < NUM_SUBJECTS - 1) outputFile << " ; ";
    }
    outputFile << endl;
}

// -

void manageStudents(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "-----MANAGE STUDENTS-----\n";
    cout << " 0. Exit.\n";
    cout << " 1. Add student.\n";
    cout << " 2. Edit student information.\n";
    cout << " 3. Delete student.\n";
    int choice = -1;
    do {
        cout << "Choose function: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 3);
    switch (choice) {
        case 0:
            mainMenu(outputFile, studentList);
            return;
        case 1:
            addStudent(outputFile, studentList);
            break;
        case 2:
            editStudent(outputFile, studentList);
            break;
        case 3:
            deleteStudent(outputFile, studentList);
            break;
    }
}

bool confirmChanges() {
    char confirmation;
    do {
        cout << "Confirm save changes (y/n): ";
        cin >> confirmation;
        cin.ignore(); 
    } while (confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');
    return (confirmation == 'y' || confirmation == 'Y');
}

void addStudent(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---ADD STUDENT---\n";
    Student student;
    cout << "  Enter student information.\n";
    inputId(studentList, student);
    inputName(student);
    inputBirthDate(student);
    inputAddress(student);
    inputEmail(student);
    inputPhone(student);
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        inputScore(student, i);
    }
    if (confirmChanges()) {
        outputFile.open(FILE_PATH, ios::app);
        studentList.students[studentList.count++] = student;
        writeData(outputFile, student);
        cout << "Update completed. ";
        outputFile.close();
    } else cout << "Changes cancelled. ";
    system("pause");
    manageStudents(outputFile, studentList);
}

void editStudent(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---EDIT STUDENT INFORMATION---\n";
    char id[20];
    cout << "Enter student ID to edit (enter 0 to exit): ";
    cin.getline(id, 20);
    int position = findIdPosition(studentList, id);
    while (position == -1 && strcmp(id, "0")) {
        cout << ">> Student not found.\n";
        cout << "Enter student ID to edit (enter 0 to exit): ";
        cin.getline(id, 20);
        position = findIdPosition(studentList, id);
    }
    if (strcmp(id, "0")) {
        Student temp = studentList.students[position];
        int choice = -1;
        bool isEdited = false;
        do {
            outputStudent(studentList.students[position]);
            cout << "0. Exit.\n";
            cout << "1. Last and first name.\n";
            cout << "2. Birth date.\n";
            cout << "3. Address.\n";
            cout << "4. Email.\n";
            cout << "5. Phone number.\n";
            for (int i = 0; i < NUM_SUBJECTS; i++) {
                cout << 6 + i << ". Score for subject " << SUBJECTS[i] << ".\n";
            }
            cout << "Choose item to edit: ";
            cin >> choice;
            cin.ignore();
            if (choice == 0) break;
            switch (choice) {
                case 1:
                    inputName(temp);
                    break;
                case 2:
                    inputBirthDate(temp);
                    break;
                case 3:
                    inputAddress(temp);
                    break;
                case 4:
                    inputEmail(temp);
                    break;
                case 5:
                    inputPhone(temp);
                    break;
                default:
                    if (choice >= 6 && choice < 6 + NUM_SUBJECTS) {
                        inputScore(temp, choice - 6);
                    }
                    break;
            }
            isEdited = true;
        } while (choice != 0);
        if (isEdited) {
            cout << "Information after editing: ";
            outputStudent(temp);
            if (confirmChanges()) {
                studentList.students[position] = temp;
                outputFile.open(FILE_PATH);
                for (int i = 0; i < studentList.count; i++) {
                    writeData(outputFile, studentList.students[i]);
                }
                outputFile.close();
                cout << "Update completed. ";
            } else cout << "Changes cancelled. ";
        }
        system("pause");
    }
    manageStudents(outputFile, studentList);
}

void deleteStudent(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---DELETE STUDENT FROM LIST---\n";
    char id[20];
    cout << "Enter student ID to delete (enter 0 to exit): ";
    cin.getline(id, 20);
    int position = findIdPosition(studentList, id);
    while (position == -1 && strcmp(id, "0")) {
        cout << ">> Student not found.\n";
        cout << "Enter student ID to delete (enter 0 to exit): ";
        cin.getline(id, 20);
        position = findIdPosition(studentList, id);
    }
    if (strcmp(id, "0")) {
        Student temp = studentList.students[position];
        cout << "Information of student to delete: ";
        outputStudent(temp);
        if (confirmChanges()) {
            for (int i = position; i < studentList.count; i++) {
                studentList.students[i] = studentList.students[i+1];
            }
            studentList.count--;
            outputFile.open(FILE_PATH);
            for (int i = 0; i < studentList.count; i++) {
                writeData(outputFile, studentList.students[i]);
            }
            outputFile.close();
            cout << "Update completed. ";
        } else cout << "Changes cancelled. ";
        system("pause");
    }
    manageStudents(outputFile, studentList);
}

// -

int findIdPosition(StudentList studentList, const char *id) {
    for (int i = 0; i < studentList.count; i++) {
        if (strcmp(studentList.students[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void findNamePositions(StudentList studentList, const char *keyword, int *positions, int &numPositions) {
    numPositions = 0;
    char substring[100] = "";
    strcpy(substring, keyword);
    formatName(substring);
    for (int k = 0; k < studentList.count; k++) {
        char name[100] = "";
        strcat(name, studentList.students[k].name.last);
        strcat(name, " ");
        strcat(name, studentList.students[k].name.first);
        if (strlen(name) < strlen(substring)) continue;
        for (int i = 0; i <= (int)strlen(name) - (int)strlen(substring); i++) {
            bool matches = true;
            for (int j = 0; j < (int)strlen(substring); j++) {
                if (name[i+j] != substring[j]) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                positions[numPositions++] = k;
                break;
            }
        }
    }
}

void searchStudents(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "-----SEARCH STUDENTS-----\n";
    cout << " 0. Exit.\n";
    cout << " 1. Search student by ID (exact).\n";
    cout << " 2. Search student by last and first name (approximate).\n";
    int choice = -1;
    do {
        cout << "Choose function: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 2);
    switch (choice) {
        case 0:
            mainMenu(outputFile, studentList);
            break;
        case 1:
            searchExactId(outputFile, studentList);
            break;
        case 2:
            searchApproximateName(outputFile, studentList);
            break;
    }
}

void searchExactId(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---SEARCH STUDENT BY ID---\n";
    char id[20];
    cout << " Enter ID (enter 0 to exit): ";
    cin.getline(id, 20);
    while (strcmp(id, "0") != 0) {
        int position = findIdPosition(studentList, id);
        if (position == -1) cout << ">> Student not found.\n";
        else outputStudent(studentList.students[position]);
        cout << " Enter ID (enter 0 to exit): ";
        cin.getline(id, 20);
    }
    searchStudents(outputFile, studentList);
}

void searchApproximateName(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---SEARCH STUDENT BY NAME---\n";
    char name[100];
    cout << " Enter last first name (enter 0 to exit): ";
    cin.getline(name, 100);
    while (strcmp(name, "0") != 0) {
        int positions[100] = {0};
        int numPositions = 0;
        findNamePositions(studentList, name, positions, numPositions);
        if (numPositions == 0) cout << ">> Student not found.\n";
        else {
            for (int i = 0; i < numPositions; i++) {
                outputStudent(studentList.students[positions[i]]);
            }
        }
        cout << " Enter last first name (enter 0 to exit): ";
        cin.getline(name, 100);
    }
    searchStudents(outputFile, studentList);
}

// -

void statisticsStudents(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "-----STATISTICS STUDENTS-----\n";
    cout << "0. Exit.\n";
    cout << "1. Display list (with sorting).\n";
    cout << "2. Statistics report.\n";
    int choice = -1;
    do {
        cout << "Choose function: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 2);
    switch (choice) {
        case 0:
            mainMenu(outputFile, studentList);
            break;
        case 1:
            displayStudentList(outputFile, studentList);
            break;
        case 2:
            reportStatistics(outputFile, studentList);
            break;
    }
}

void displayStudentList(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---DISPLAY STUDENT LIST---\n";
    cout << "0. Exit.\n";
    cout << "1. List sorted by ID (ascending).\n";
    cout << "2. List sorted by last first name (A to Z).\n";
    cout << "3. List sorted by average score (descending).\n";
    int choice = -1;
    do {
        cout << "Choose function: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 3);
    switch (choice) {
        case 0:
            statisticsStudents(outputFile, studentList);
            break;
        case 1:
            sortById(outputFile, studentList);
            break;
        case 2:
            sortByName(outputFile, studentList);
            break;
        case 3:
            sortByAverageScore(outputFile, studentList);
            break;
    }
}

void sortById(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    StudentList sortedList = studentList;
    for (int i = 0; i < sortedList.count - 1; i++) {
        for (int j = i + 1; j < sortedList.count; j++) {
            if (strcmp(sortedList.students[i].id, sortedList.students[j].id) > 0) {
                swap(sortedList.students[i], sortedList.students[j]);
            }
        }
    }
    outputStudentList(sortedList);
    system("pause");
    displayStudentList(outputFile, studentList);
}

void sortByName(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    StudentList sortedList = studentList;
    for (int i = 0; i < sortedList.count - 1; i++) {
        for (int j = i + 1; j < sortedList.count; j++) {
            if (strcmp(sortedList.students[i].name.first, sortedList.students[j].name.first) > 0) {
                swap(sortedList.students[i], sortedList.students[j]);              
            } else if (strcmp(sortedList.students[i].name.first, sortedList.students[j].name.first) == 0) {
                if (strcmp(sortedList.students[i].name.last, sortedList.students[j].name.last) > 0) {
                    swap(sortedList.students[i], sortedList.students[j]);
                }
            }
        }
    }
    outputStudentList(sortedList);
    system("pause");
    displayStudentList(outputFile, studentList);
}

float calculateAverageScore(Student student) {
    if (NUM_SUBJECTS == 0) return 0;
    float totalScore = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        totalScore += student.Scores[i];
    }
    return (totalScore/NUM_SUBJECTS);
}

void sortByAverageScore(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    StudentList sortedList = studentList;
    for (int i = 0; i < sortedList.count - 1; i++) {
        for (int j = i + 1; j < sortedList.count; j++) {
            if (calculateAverageScore(sortedList.students[i]) < calculateAverageScore(sortedList.students[j])) {
                swap(sortedList.students[i], sortedList.students[j]);
            }
        }
    }
    outputStudentList(sortedList);
    system("pause");
    displayStudentList(outputFile, studentList);
}

void outputStudentList(StudentList studentList) {
    for (int i = 0; i < studentList.count; i++) {
        cout << setfill('0') << setw(2) << i + 1 << ": ";
        outputStudent(studentList.students[i]);
    }
}

void reportStatistics(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "---STUDENT STATISTICS REPORT---\n";
    cout << "Total number of students: " << studentList.count << ".\n";
    if (studentList.count) {
        cout << "\n";
        float highestAvgScore = 0.0, lowestAvgScore = 10.0;
        int highestAvgPositions[studentList.count] = {0}, lowestAvgPositions[studentList.count] = {0};
        int numHighestAvg = 0, numLowestAvg = 0;
        float highestScores[NUM_SUBJECTS], lowestScores[NUM_SUBJECTS];
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            highestScores[i] = 0.0;
            lowestScores[i] = 10.0;
        }
        int highestScorePositions[NUM_SUBJECTS][studentList.count] = {0}, lowestScorePositions[NUM_SUBJECTS][studentList.count] = {0};
        int numHighest[NUM_SUBJECTS] = {0}, numLowest[NUM_SUBJECTS] = {0};
        float avgScores[studentList.count];
        for (int i = 0; i < studentList.count; i++) {
            float totalScore = 0.0;
            for (int j = 0; j < NUM_SUBJECTS; j++) {
                if (highestScores[j] < studentList.students[i].Scores[j]) {
                    highestScores[j] = studentList.students[i].Scores[j];
                    highestScorePositions[j][0] = i;
                    numHighest[j] = 1;
                } else if (abs(highestScores[j] - studentList.students[i].Scores[j]) < 1e-6) {
                    highestScorePositions[j][numHighest[j]++] = i;
                }
                if (lowestScores[j] > studentList.students[i].Scores[j]) {
                    lowestScores[j] = studentList.students[i].Scores[j];
                    lowestScorePositions[j][0] = i;
                    numLowest[j] = 1;
                } else if (abs(lowestScores[j] - studentList.students[i].Scores[j]) < 1e-6) {
                    lowestScorePositions[j][numLowest[j]++] = i;
                }
                totalScore += studentList.students[i].Scores[j];
            }
            avgScores[i] = totalScore/NUM_SUBJECTS;
            if (highestAvgScore < avgScores[i]) {
                highestAvgScore = avgScores[i];
                highestAvgPositions[0] = i;
                numHighestAvg = 1;
            } else if (abs(highestAvgScore - avgScores[i]) < 1e-6) {
                highestAvgPositions[numHighestAvg++] = i;
            }
            if (lowestAvgScore > avgScores[i]) {
                lowestAvgScore = avgScores[i];
                lowestAvgPositions[0] = i;
                numLowestAvg = 1;
            } else if (abs(lowestAvgScore - avgScores[i]) < 1e-6) {
                lowestAvgPositions[numLowestAvg++] = i;
            }
        }
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            cout << "Students with highest " << SUBJECTS[i] << " score:\n";
            for (int j = 0; j < numHighest[i]; j++) {
                int position = highestScorePositions[i][j];
                outputStudent(studentList.students[position]);
            }
        }
        cout << "Students with highest average score [" << fixed << setprecision(2) << highestAvgScore << "]:\n";
        for (int i = 0; i < numHighestAvg; i++) {
            int position = highestAvgPositions[i];
            outputStudent(studentList.students[position]);
        }
        cout << "\n";
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            cout << "Students with lowest " << SUBJECTS[i] << " score:\n";
            for (int j = 0; j < numLowest[i]; j++) {
                int position = lowestScorePositions[i][j];
                outputStudent(studentList.students[position]);
            }
        }
        cout << "Students with lowest average score [" << fixed << setprecision(2) << lowestAvgScore << "]:\n";

        for (int i = 0; i < numLowestAvg; i++) {
            int position = lowestAvgPositions[i];
            outputStudent(studentList.students[position]);
        }
        cout << "\n";
        int excellent = 0, good = 0, fair = 0, average = 0, poor = 0;
        for (int i = 0; i < studentList.count; i++) {
            if (avgScores[i] > 9 || abs(avgScores[i] - 9) < 1e-6) excellent++;
            else if (avgScores[i] > 8 || abs(avgScores[i] - 8) < 1e-6) good++;
            else if (avgScores[i] > 6.5 || abs(avgScores[i] - 6.5) < 1e-6) fair++;
            else if (avgScores[i] > 5 || abs(avgScores[i] - 5) < 1e-6) average++;
            else poor++;
        }
        cout << "Number of excellent students: " << excellent << " (" << (excellent*100.0/studentList.count) << "%)\n";
        cout << "Number of good students: " << good << " (" << (good*100.0/studentList.count) << "%)\n";
        cout << "Number of fair students: " << fair << " (" << (fair*100.0 /studentList.count) << "%)\n";
        cout << "Number of average students: " << average << " (" << (average*100.0/studentList.count) << "%)\n";
        cout << "Number of poor students: " << poor << " (" << (poor*100.0/studentList.count) << "%)\n";
        cout << "\n";
        float subjectAverages[NUM_SUBJECTS];
        float totalAvg;
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            float totalScore = 0;
            for (int j = 0; j < studentList.count; j++) {
                totalScore += studentList.students[j].Scores[i];
            }
            subjectAverages[i] = totalScore/studentList.count;
            cout << "Average score for " << SUBJECTS[i] << ": " << fixed << setprecision(2) << subjectAverages[i] << ".\n";
            totalAvg += subjectAverages[i];
        }
        cout << "Overall average score: " << totalAvg/NUM_SUBJECTS <<".\n";
        cout << "\n";
        // TODO: Add median calculation if needed
    }
    system("pause");
    statisticsStudents(outputFile, studentList);
}

// -

void mainMenu(ofstream &outputFile, StudentList &studentList) {
    system("cls");
    cout << "-----STUDENT INFORMATION MANAGEMENT PROGRAM-----\n";
    cout << " 0. Exit.\n";
    cout << " 1. Manage students.\n";
    cout << " 2. Search students.\n";
    cout << " 3. Statistics students.\n";
    int choice = -1;
    do {
        cout << "Choose function: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 3);
    switch (choice) {
        case 0:
            cout << "\nSee you again.\n";
            return;
        case 1:
            manageStudents(outputFile, studentList);
            break;
        case 2:
            searchStudents(outputFile, studentList);
            break;
        case 3:
            statisticsStudents(outputFile, studentList);
            break;
    }
}