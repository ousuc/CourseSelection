module;
#include<libpq-fe.h>

export module DataBase:StudentBroker;
import std;
import :DataBroker;
// 前置声明
class Student;

export class StudentBroker{
public:
    StudentBroker(DataBroker* db);
    ~StudentBroker();

    bool saveStudent(Student* student);
    Student* findStudentById(std::string id);
    bool enrollInCourse(std::string studentId, std::string courseId);
    double calculateGPA(std::string studentId);
private:
    DataBroker* db;
    std::string tableName;
};


