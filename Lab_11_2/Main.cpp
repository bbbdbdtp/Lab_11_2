#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

enum Specialization { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_TRAINING };

union Grade {
    int programming;
    int numerical_methods;
    int pedagogy;
};

struct Student {
    string surname;
    int course;
    Specialization specialization;
    int physics_grade;
    int math_grade;
    Grade additional_grade;
};

void CreateStudents(Student* students, const int N);
double CalculateAverageGrade(const Student& student);
double CalculatePercentage(const Student* students, const int N);
void PrintStudents(const Student* students, const int N);
void WriteStudentsToFile(const Student* students, const int N, const char* filename);
void ReadStudentsFromFileAndPrint(const char* filename);
int CountPhysicsGrades(const Student* students, const int N, const int grade);
int CountBothPhysicsAndMathGrades(const Student* students, const int N);

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student* students = new Student[N];
    CreateStudents(students, N);

    cout << "\nStudents' table:\n";
    PrintStudents(students, N);

    double max_average_grade = 0;
    for (int i = 0; i < N; ++i) {
        double average_grade = CalculateAverageGrade(students[i]);
        if (average_grade > max_average_grade)
            max_average_grade = average_grade;
    }
    cout << "\nHighest average grade: " << max_average_grade << endl;

    double percentage = CalculatePercentage(students, N);
    cout << "Percentage of students with grades '5' or '4' in Physics: " << percentage << "%" << endl;

    int grade_five_physics = CountPhysicsGrades(students, N, 5);
    int grade_four_physics = CountPhysicsGrades(students, N, 4);
    int grade_three_physics = CountPhysicsGrades(students, N, 3);

    cout << "Number of students with grade '5' in Physics: " << grade_five_physics << endl;
    cout << "Number of students with grade '4' in Physics: " << grade_four_physics << endl;
    cout << "Number of students with grade '3' in Physics: " << grade_three_physics << endl;

    cout << "Number of students with grades '4' or '5' in both Physics and Mathematics: " << CountBothPhysicsAndMathGrades(students, N) << endl;

    const char* filename = "students_data.bin";
    WriteStudentsToFile(students, N, filename);

    cout << "\nStudents' data has been written to file.\n";

    cout << "\nReading students' data from file:\n";
    ReadStudentsFromFileAndPrint(filename);

    delete[] students;
    return 0;
}

void CreateStudents(Student* students, const int N) {
    for (int i = 0; i < N; ++i) {
        cout << "Student #" << i + 1 << ":\n";
        cout << "Surname: ";
        cin >> students[i].surname;
        cout << "Course: ";
        cin >> students[i].course;
        cout << "Specialization (0 - Computer Science, 1 - Informatics, 2 - Math and Economics, 3 - Physics and Informatics, 4 - Labor Training): ";
        int specialization;
        cin >> specialization;
        students[i].specialization = static_cast<Specialization>(specialization);
        cout << "Grade in Physics: ";
        cin >> students[i].physics_grade;
        cout << "Grade in Mathematics: ";
        cin >> students[i].math_grade;

        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            cout << "Programming grade: ";
            cin >> students[i].additional_grade.programming;
            break;
        case INFORMATICS:
            cout << "Numerical methods grade: ";
            cin >> students[i].additional_grade.numerical_methods;
            break;
        default:
            cout << "Pedagogy grade: ";
            cin >> students[i].additional_grade.pedagogy;
            break;
        }
        cout << endl;
    }
}

double CalculateAverageGrade(const Student& student) {
    double sum = student.physics_grade + student.math_grade;
    switch (student.specialization) {
    case COMPUTER_SCIENCE:
        sum += student.additional_grade.programming;
        break;
    case INFORMATICS:
        sum += student.additional_grade.numerical_methods;
        break;
    default:
        sum += student.additional_grade.pedagogy;
        break;
    }
    return sum / 3.0;
}

double CalculatePercentage(const Student* students, const int N) {
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (students[i].physics_grade == 5 || students[i].physics_grade == 4)
            ++count;
    return static_cast<double>(count) / N * 100;
}

int CountPhysicsGrades(const Student* students, const int N, const int grade) {
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (students[i].physics_grade == grade)
            ++count;
    return count;
}

int CountBothPhysicsAndMathGrades(const Student* students, const int N) {
    int count = 0;
    for (int i = 0; i < N; i++)
        if ((students[i].physics_grade == 4 || students[i].physics_grade == 5) &&
            (students[i].math_grade == 4 || students[i].math_grade == 5))
            count++;
    return count;
}


void PrintStudents(const Student* students, const int N) {
    cout << "========================================================================================================" << endl;
    cout << "| # | Surname       | Course | Specialization               | Physics | Mathematics | Additional Grade |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "| " << setw(1) << right << i + 1 << " | ";
        cout << setw(13) << left << students[i].surname << " | ";
        cout << setw(6) << right << students[i].course << " | ";

        switch (students[i].specialization) {
        case COMPUTER_SCIENCE:
            cout << setw(28) << left << "Computer Science" << " | ";
            cout << setw(7) << right << students[i].physics_grade << " | ";
            cout << setw(11) << right << students[i].math_grade << " | ";
            cout << setw(16) << right << students[i].additional_grade.programming << " |" << endl;
            break;
        case INFORMATICS:
            cout << setw(28) << left << "Informatics" << " | ";
            cout << setw(7) << right << students[i].physics_grade << " | ";
            cout << setw(11) << right << students[i].math_grade << " | ";
            cout << setw(16) << right << students[i].additional_grade.numerical_methods << " |" << endl;
            break;
        case MATH_ECONOMICS:
            cout << setw(28) << left << "Math and Economics" << " | ";
            cout << setw(7) << right << students[i].physics_grade << " | ";
            cout << setw(11) << right << students[i].math_grade << " | ";
            cout << setw(16) << right << students[i].additional_grade.pedagogy << " |" << endl;
            break;
        case PHYSICS_INFORMATICS:
            cout << setw(28) << left << "Physics and Informatics" << " | ";
            cout << setw(7) << right << students[i].physics_grade << " | ";
            cout << setw(11) << right << students[i].math_grade << " | ";
            cout << setw(16) << right << students[i].additional_grade.numerical_methods << " |" << endl;
            break;
        case LABOR_TRAINING:
            cout << setw(28) << left << "Labor Training" << " | ";
            cout << setw(7) << right << students[i].physics_grade << " | ";
            cout << setw(11) << right << students[i].math_grade << " | ";
            cout << setw(16) << right << students[i].additional_grade.pedagogy << " |" << endl;
            break;
        }
    }
    cout << "========================================================================================================" << endl;
}

void WriteStudentsToFile(const Student* students, const int N, const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&N), sizeof(N));
    file.write(reinterpret_cast<const char*>(students), N * sizeof(Student));
    file.close();
}

void ReadStudentsFromFileAndPrint(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    int N;
    file.read(reinterpret_cast<char*>(&N), sizeof(N));
    Student* students = new Student[N];
    file.read(reinterpret_cast<char*>(students), N * sizeof(Student));
    PrintStudents(students, N);
    file.close();
}