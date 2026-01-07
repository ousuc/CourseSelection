module;
#include<libpq-fe.h>

export module DataBase:CourseBroker;
import std;
import :DataBroker;
// 前置声明
class Course;

export class CourseBroker{
public:
    CourseBroker(DataBroker* db);
    ~CourseBroker();

    bool saveCourse(Course* Course);
    Course* findCourseById(const std::string& id);

// 激活相关接口
    bool activateCourse(const std::string& courseId);
    bool deactivateCourse(const std::string& courseId);
    bool isActiveCourse(const std::string& courseId);

private:
    DataBroker* db;
    const std::string& tableName;
};
// 默认构造函数是生成courses表名，硬编码，用于第一版可执行发行
CourseBroker::CourseBroker(DataBroker* db):
    db(db),tableName("courses")
{}
CourseBroker::~CourseBroker()
{}

Course* CourseBroker::findCourseById(const std::string& id)
{

}

bool CourseBroker::saveCourse(Course* Course)
{

}

// 激活系列可能会删除
bool activateCourse(const std::string& courseId)
{}
bool deactiveCourse(const std::string& courseId)
{}
bool isActiveCourse(const std::string& courseId)
{}
