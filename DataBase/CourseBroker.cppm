module;
#include<libpq-fe.h>

export module DataBase:CourseBroker;
import std;
import :DataBroker;
// 前置声明
import course;

export class CourseBroker{
public:
    CourseBroker(DataBroker* db);
    ~CourseBroker();

    bool saveCourse(Course* Course);
    Course* findCourseById(const std::string& id);

// 激活相关接口 [[已废弃]]
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
    // todo ： 后期修复db类中容易被攻击的函数pgexec
    std::string sql = "select * from courses where id ='"+ id + "'";

    // 执行这个sql语句
    auto res = db->executeSQL(sql);

    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "查询失败" << std::endl;
        PQclear(res);
        return nullptr;
    }

    // 提取数据
    std::string course_id = PQgetvalue(res, 0, 0);
    std::string name = PQgetvalue(res, 0, 2);
    std::string credits = PQgetvalue(res, 0, 3);

    PQclear(res);

    // 构建Course对象
    Course* course = new Course(
        course_id,
        name,
        std::stof(credits)
    );

    return course;
}

bool CourseBroker::saveCourse(Course* Course)
{
    std::string sql = "INSERT INTO courses (id, name, credits) VALUES ('"
        + Course->getId() + "', '"
        + Course->getName() + "', '"
        + std::to_string(Course->getCredits()) + "');";

    auto res = db->executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
    PQclear(res);
    return success;
}

// 激活系列可能会删除 
[[deprecated]]
bool activateCourse(const std::string& courseId)
{
    return false;
}
[[deprecated]]
bool deactiveCourse(const std::string& courseId)
{
    return false;
}
[[deprecated]]
bool isActiveCourse(const std::string& courseId)
{
    return false;
}
