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

    Teacher* findTeacherById(const std::string& id);

    bool assignToCourse(const std::string& teacherId,const  std::string& courseId);

    bool inputStudentGrade(const std::string& teacherId,const std::string& studetnId, double grade);

private:
    DataBroker* db;
    std::string tableName;
};
TeacherBroker::TeacherBroker(DataBroker* db):
        db(db),tableName("teachers")
{}

bool TeacherBroker::inputStudentGrade(const std::string& teacherId, const std::string& studentId, double grade)
{

}

bool TeacherBroker::assignToCourse(const std::string& teacherId, const std::string& courseId)
{

}

Teacher* TeacherBroker::findTeacherById(const std::string& id)
{

}

bool TeacherBroker::saveTeacher(Teacher* teacher)
{
    // todo: 将这个插入到老师表中 ，实战应该不会使用，已经会填写一些测试数据
}

