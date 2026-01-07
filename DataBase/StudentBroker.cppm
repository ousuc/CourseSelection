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
    Student* findStudentById(const std::string& id);
    bool enrollInCourse(const std::string& studentId,const std::string& courseId);
    double calculateGPA(const std::string& studentId);
private:
    DataBroker* db;
    std::string tableName;
};

// 构造函数默认将这个表名设置为students
StudentBroker::StudentBroker(DataBroker* db):
        db(db),tableName("students")
{}

StudentBroker::~StudentBroker(){
}

bool StudentBroker::enrollInCourse(const std::string& studentId, const std::string& courseId)
{
}

Student* StudentBroker::findStudentById(const std::string& id)
{
}

bool StudentBroker::saveStudent(Student* student)
{
    // todo: 将这个插入到学生表中
}

double StudentBroker::calculateGPA(const std::string& studentId)
{
    // todo: 计算GPA 可能会弃用
}
