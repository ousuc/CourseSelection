module;
#include<libpq-fe.h>

export module DataBase:TeacherBroker;
import std;
import :DataBroker;
// 前置声明
class Teacher;

export class TeacherBroker{
public:
    TeacherBroker(DataBroker* db);
    ~TeacherBroker();

    bool saveTeacher(Teacher* student);

    Teacher* findTeacherById(std::string id);

    bool assignToCourse(std::string teacherId, std::string courseId);

    bool inputStudentGrade(std::string teacherId, std::string studetnId, double grade);

private:
    DataBroker* db;
    std::string tableName;
};


