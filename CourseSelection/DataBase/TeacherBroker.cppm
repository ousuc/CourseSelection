module;
#include<libpq-fe.h>

export module DataBase:TeacherBroker;
import std;
import :DataBroker;
// 前置声明
import teacherRole;
using Teacher = TeacherRole;

export class TeacherBroker{
public:
    TeacherBroker(DataBroker* db);
    ~TeacherBroker();

    bool saveTeacher(Teacher* student);

    Teacher* findTeacherById(const std::string& id);

    bool assignToCourse(const std::string& teacherId,const  std::string& courseId);

    bool inputStudentGrade(const std::string& teacherId,const std::string& studentId, const std::string& courseId, double grade);   

private:
    DataBroker* db;
    std::string tableName;
};
TeacherBroker::TeacherBroker(DataBroker* db):
        db(db),tableName("teachers")
{}
TeacherBroker::~TeacherBroker() = default;

bool TeacherBroker::inputStudentGrade(const std::string& teacherId,
     const std::string& studentId,
     const std::string& courseId,
      double grade
    )
{
    // 通过课程和老师id查看到对应   教学任务的id --- 1. 查看老师是不是真的有对应的教学任务，也就是对应给学生成绩的权限
    std::string findTaskSql = 
        "SELECT task_id FROM teaching_tasks "
        "WHERE course_id = '" + courseId + "' "
        "AND teacher_id = '" + teacherId + "' LIMIT 1";

    auto taskRes = db->executeSQL(findTaskSql); 

    if (PQresultStatus(taskRes) != PGRES_TUPLES_OK || PQntuples(taskRes) == 0) {
        PQclear(taskRes);
        return false; // 该教师没有教授这门课
    }
    std::string taskId = PQgetvalue(taskRes, 0, 0);
    PQclear(taskRes);

    // 然后是验证这个学生是不是真的选了这个课程，虽然老师存在并且教授这个课程但是不一定学生选了这个课程
    std::string verifySql = 
    "SELECT 1 FROM grades "
    "WHERE student_id = '" + studentId + "' "
    "AND task_id = '" + taskId + "' "
    "LIMIT 1";

    PGresult* verifyRes = db->executeSQL(verifySql);
    bool isEnrolled = (PQntuples(verifyRes) > 0);
    PQclear(verifyRes);

    if (!isEnrolled) {
        return false; // 学生没有选这门课
    }
    // 最后是更新成绩
    std::string updateSql = 
    "UPDATE grades "
    "SET grade = " + std::to_string(grade) + " "
    "WHERE student_id = '" + studentId + "' "
    "AND task_id = '" + taskId + "'";

    auto updateRes = db->executeSQL(updateSql);
    bool success = (PQresultStatus(updateRes) == PGRES_COMMAND_OK);
    PQclear(updateRes);

    return success;   
        
}

// 给老师分配课程
bool TeacherBroker::assignToCourse(const std::string& teacherId, const std::string& courseId)
{
    // 直接更新 Teaching_Tasks 表的 teacher_id 字段
    std::string sql = "UPDATE teaching_tasks SET teacher_id = '" + teacherId +
                     "' WHERE course_id = '" + courseId + "'";
    
    auto res = db->executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
    PQclear(res);
    
    return success;
}

Teacher* TeacherBroker::findTeacherById(const std::string& id)
{
    // todo ： 后期修复db类中容易被攻击的函数pgexec
    std::string sql = "select * from teachers where id ='"+ id + "'";

    // 执行这个sql语句
    auto res = db->executeSQL(sql);
    if (PQntuples(res) <= 0)    {
        std::println("查询结果为空");
        db->clear(res);
        return nullptr;
    }
    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        return nullptr; // 查询失败
    }

    // 检查是否找到了对应的老师 就是看有没有数据
    if (PQntuples(res) == 0) {
        PQclear(res);
        return nullptr; // 没有找到对应的老师
    }

    // 提取数据
    std::string teacher_id = PQgetvalue(res, 0, 0);
    std::string name = PQgetvalue(res, 0, 1);
    std::string gender = PQgetvalue(res, 0, 2);

    PQclear(res);

    // 构建Teacher对象
    Teacher* teacher = new Teacher(
        teacher_id,
        name,
        gender
    );

    return teacher;
}

bool TeacherBroker::saveTeacher(Teacher* teacher)
{
    // todo: 将这个插入到老师表中 ，实战应该不会使用，已填写一些测试数据
    std::string sql = "INSERT INTO teachers (id, name, gender) VALUES ('"
        + teacher->getId() + "', '"
        + teacher->getName() + "', '"
        + teacher->getGender() + "');"; 
    auto res = db->executeSQL(sql); 
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);   
    PQclear(res);
    return success;
}

