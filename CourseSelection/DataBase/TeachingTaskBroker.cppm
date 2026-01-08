module;
#include<libpq-fe.h>

export module DataBase:TeachingTaskBroker;
import std;
import :DataBroker;
// 前置声明
class TeachingTask;

export class TeachingTaskBroker{
public:
    TeachingTaskBroker(DataBroker* db);
    ~TeachingTaskBroker();

    bool saveTask(TeachingTask* teachingTask);
    TeachingTask* findTaskById(const std::string& id);

    bool addStudentToTask(const std::string& taskId,const std::string& studentId);
    bool assignTeacherToTask(const std::string& taskId, const std::string& teacherId);
private:
    DataBroker* db;
    const std::string& tableName;
};

TeachingTaskBroker::TeachingTaskBroker(DataBroker* db):
    db(db),tableName("teaching_tasks")
{}

bool TeachingTaskBroker::saveTask(TeachingTask* teachingTask)
{   
    std::string sql = "INSERT INTO teaching_tasks (id, time_slot, enroll_start, enroll_end, max_students) VALUES ('"
        + teachingTask->getId() + "', '"
        + teachingTask->getTimeSlot() + "', "
        + std::to_string(teachingTask->getEnrollStart()) + ", "
        + std::to_string(teachingTask->getEnrollEnd()) + ", "
        + std::to_string(teachingTask->getMaxCapacity()) + ")";

    auto res = db->executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
    PQclear(res);
    return success;
}

// 通过id寻找到教学任务
TeachingTask* findTaskById(const std::string& id)
{
    // todo ： 后期修复db类中容易被攻击的函数pgexec
    std::string sql = "select * from teaching_tasks where id ='"+ id + "'";

    // 执行这个sql语句
    auto res = db->executeSQL(sql);

    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "查询失败: " << PQerrorMessage(connection) << std::endl;
        PQclear(res);
        return nullptr;
    }

    // 提取数据
    std::string task_id = PQgetvalue(res, 0, 0);
    std::string time_slot = PQgetvalue(res, 0, 4);
    std::string enroll_start = PQgetvalue(res, 0, 5);
    std::string enroll_end = PQgetvalue(res, 0, 6);
    std::string max = PQgetvalue(res, 0, 7);

    // 构建对象
    // todo: 时间类型转换-目前只是乱写的只为了可以运行
    TeachingTask* task = new TeachingTask(
        task_id,
        time_slot,
        (time_t)std::stoi(enroll_start),
        (time_t)std::stoi(enroll_end),
        std::stoi(max)
    );
    return task; 

}

// TODO : 将容量和时间检查功en能实现
bool addStudentToTask(const std::string& taskId, const std::string& studentId)
{
    // 检查是不是已经选择了
    std::string checkSql = "SELECT COUNT(*) FROM GRADES WHERE student_id = '"
    + studentId + "' AND task_id = '" + taskId + "';";

    auto checkRes = db->executeQuery(checkSql);
    int count = std::stoi(PQgetvalue(checkRes, 0, 0));
    PQclear(checkRes);
    
    if (count > 0) {
        return false;
    }

    // 将这个选课记录插入到GRADES表中
    std::string insertSql = "INSERT INTO GRADES (student_id, task_id) VALUES ('"
    + studentId + "', '" + taskId + "');";
    auto insertRes = db->executeSQL(insertSql);
    bool success = (PQresultStatus(insertRes) == PGRES_COMMAND_OK);
    PQclear(insertRes);

    // 更新 teaching_task 表的当前选课人数
    if (success) {
        std::string updateSql = "UPDATE Teaching_Tasks SET current_enrolled = current_enrolled + 1"
        "WHERE task_id = '" + taskId + "'";
        
        auto updateRes = db->executeSQL(updatesql);
        PQclear(checkRes);
    }
}

// 给老师分配教学任务
bool assignTeacherToTask(const string& taskId, const std::string& teacherId)
{
    // 直接更新 Teaching_Tasks 表的 teacher_id 字段
    std::string sql = "UPDATE Teaching_Tasks SET teacher_id = '" + teacherId + 
                     "' WHERE task_id = '" + taskId + "'";
    
    auto res = db->executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);
    PQclear(res);
    
    return success;
}

