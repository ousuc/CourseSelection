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
    Course* findCourseById(std::string id);

// 激活相关接口
    bool activateCourse(std::string courseId);
    bool deactivateCourse(std::string courseId);
    bool isActiveCourse(std::string courseId);

private:
    bool active;
    DataBroker* db;
    std::string tableName;
};


