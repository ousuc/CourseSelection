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

    void printTeachingTasks(const std::string& teacherId);
    void printTeachingTasks(Teacher* teacher);
    void printTaskStudentsGrouped(const std::string& teacherId);
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
    std::string sql = "select * from teachers where id='"+ id + "';";

    // 执行这个sql语句
    auto res = db->executeSQL(sql);
    if (PQntuples(res) <= 0)    {
    std::println("{}是执行语句",sql); //debug
        std::println("查询结果为空");
        db->clear(res);
        return nullptr;
    }
    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        std::println("查询结构状态问题");
        return nullptr; // 查询失败
    }

    // 检查是否找到了对应的老师 就是看有没有数据
    if (PQntuples(res) == 0) {
        PQclear(res);
        std::println("没有对应的行数");
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


// 增加查询教师任务的

// 查询老师的授课任务详细信息
void TeacherBroker::printTeachingTasks(const std::string& teacherId)
{
    if (teacherId.empty()) {
        std::cout << "错误：老师ID为空" << std::endl;
        return;
    }

    std::cout << "正在查询老师 " << teacherId << " 的授课任务..." << std::endl;
    std::cout << "========================================================" << std::endl;

    // 根据表设计文档，teaching_tasks表的正确列包括：
    // task_id, course_id, teacher_id, time_slot, enroll_start, enroll_end,
    // max_capacity, current_enrolled, created_at

    std::string sql = "SELECT "
                     "tt.task_id as 任务ID, "
                     "tt.course_id as 课程ID, "
                     "c.course_code as 课程代码, "
                     "c.name as 课程名称, "
                     "tt.time_slot as 上课时间, "
                     "tt.enroll_start as 选课开始, "
                     "tt.enroll_end as 选课结束, "
                     "tt.current_enrolled as 当前人数, "
                     "tt.max_capacity as 最大容量, "
                     "TO_CHAR(tt.created_at, 'YYYY-MM-DD HH24:MI') as 创建时间 "
                     "FROM teaching_tasks tt "
                     "LEFT JOIN courses c ON tt.course_id = c.id "
                     "WHERE tt.teacher_id = '" + teacherId + "' "
                     "ORDER BY tt.created_at DESC";

    auto result = db->executeSQL(sql);
    if (!result) {
        std::cout << "查询失败：返回空结果" << std::endl;
        return;
    }

    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cout << "查询执行失败" << std::endl;
        db->clear(result);
        return;
    }

    // 使用DataBroker中的selectPrint函数打印结果
    db->selectPrint(result);

    // 检查是否有数据
    int rowCount = PQntuples(result);
    if (rowCount == 0) {
        std::cout << "\n该老师暂无授课任务" << std::endl;
    } else {
        std::cout << "\n共找到 " << rowCount << " 个授课任务" << std::endl;

        // 添加统计信息
        std::string statSql = "SELECT "
                             "COUNT(*) as 总任务数, "
                             "SUM(current_enrolled) as 总学生数, "
                             "AVG(current_enrolled::float) as 平均选课人数, "
                             "SUM(max_capacity) as 总容量 "
                             "FROM teaching_tasks "
                             "WHERE teacher_id = '" + teacherId + "'";

        auto statResult = db->executeSQL(statSql);
        if (statResult && PQresultStatus(statResult) == PGRES_TUPLES_OK && PQntuples(statResult) > 0) {
            std::cout << "\n统计信息：" << std::endl;
            std::cout << "------------------------" << std::endl;
            std::cout << "总任务数: " << PQgetvalue(statResult, 0, 0) << std::endl;
            std::cout << "总学生数: " << PQgetvalue(statResult, 0, 1) << std::endl;

            std::string avgStudents = PQgetvalue(statResult, 0, 2);
            if (!avgStudents.empty()) {
                float avg = std::stof(avgStudents);
                std::cout << "平均选课人数: " << std::fixed << std::setprecision(1) << avg << std::endl;
            }

            std::cout << "总容量: " << PQgetvalue(statResult, 0, 3) << std::endl;
        }
        db->clear(statResult);
    }

    // 清理资源
    db->clear(result);

    std::cout << "========================================================" << std::endl;
}

// 重载版本，直接传入Teacher对象
void TeacherBroker::printTeachingTasks(Teacher* teacher)
{
    if (!teacher) {
        std::cout << "错误：老师对象为空" << std::endl;
        return;
    }

    printTeachingTasks(teacher->getId());
}

// 按任务分组显示学生名单
void TeacherBroker::printTaskStudentsGrouped(const std::string& teacherId)
{
    if (teacherId.empty()) {
        std::cout << "错误：老师ID为空" << std::endl;
        return;
    }

    std::cout << "老师 " << teacherId << " 的各任务学生名单" << std::endl;
    std::cout << "======================================================" << std::endl;

    // 首先获取老师的所有任务
    std::string taskSql = "SELECT "
                         "tt.task_id, "
                         "c.course_code, "
                         "c.name as course_name, "
                         "tt.current_enrolled "
                         "FROM teaching_tasks tt "
                         "LEFT JOIN courses c ON tt.course_id = c.id "
                         "WHERE tt.teacher_id = '" + teacherId + "' "
                         "ORDER BY tt.task_id";

    auto taskResult = db->executeSQL(taskSql);
    if (!taskResult || PQresultStatus(taskResult) != PGRES_TUPLES_OK) {
        std::cout << "查询任务失败" << std::endl;
        if (taskResult) db->clear(taskResult);
        return;
    }

    int taskCount = PQntuples(taskResult);
    if (taskCount == 0) {
        std::cout << "该老师没有教学任务" << std::endl;
        db->clear(taskResult);
        return;
    }

    // 遍历每个任务，查询学生名单
    for (int i = 0; i < taskCount; i++) {
        std::string taskId = PQgetvalue(taskResult, i, 0);
        std::string courseCode = PQgetvalue(taskResult, i, 1);
        std::string courseName = PQgetvalue(taskResult, i, 2);
        std::string enrolled = PQgetvalue(taskResult, i, 3);

        std::cout << "\n任务: " << taskId
                  << " | 课程: " << courseCode << " - " << courseName
                  << " | 学生人数: " << enrolled
                  << "\n------------------------------------------------------" << std::endl;

        // 查询该任务的学生名单
        std::string studentSql = "SELECT "
                                "g.student_id, "
                                "s.name, "
                                "s.gender, "
                                "COALESCE(CAST(g.score AS VARCHAR), '未评分') "
                                "FROM grades g "
                                "LEFT JOIN students s ON g.student_id = s.id "
                                "WHERE g.task_id = '" + taskId + "' "
                                "ORDER BY s.name";

        auto studentResult = db->executeSQL(studentSql);
        if (studentResult && PQresultStatus(studentResult) == PGRES_TUPLES_OK) {
            int studentCount = PQntuples(studentResult);

            if (studentCount == 0) {
                std::cout << "  暂无学生" << std::endl;
            } else {
                for (int j = 0; j < studentCount; j++) {
                    std::string stuId = PQgetvalue(studentResult, j, 0);
                    std::string stuName = PQgetvalue(studentResult, j, 1);
                    std::string gender = PQgetvalue(studentResult, j, 2);
                    std::string score = PQgetvalue(studentResult, j, 3);

                    std::cout << "  " << stuId << " | " << stuName
                              << " | " << gender << " | 成绩: " << score << std::endl;
                }
            }
        }

        if (studentResult) db->clear(studentResult);
    }

    db->clear(taskResult);
    std::cout << "======================================================" << std::endl;
}
