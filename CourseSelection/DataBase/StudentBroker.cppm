module;
#include<libpq-fe.h>
export module DataBase:StudentBroker;
import std;
import :DataBroker;
// 前置声明
import studentRole;

export class StudentBroker{
public:
    StudentBroker(DataBroker* db);
    ~StudentBroker();

    bool saveStudent(StudentRole* student);

    StudentRole* findStudentById(const std::string& id);

    bool enrollInCourse(const std::string& studentId,const std::string& courseId);

    double calculateGPA(const std::string& studentId);

    bool enrollInTask(const std::string& studentId, const std::string& taskId);

    bool dropInTask(const std::string& studentId, const std::string& taskId);
private:
    DataBroker* db;
    std::string tableName;
};

// 通过AI辅助生成
bool StudentBroker::enrollInTask(const std::string& studentId, const std::string& taskId)
{
    std::cout << "开始执行插入" << std::endl;

    // 第一步：软编码 - 动态查询grades表的最大id（使用libpq风格函数，与selectPrint一致）
    std::string selectMaxIdSql = "SELECT MAX(id) FROM grades;";
    auto resMaxId = db->executeSQL(selectMaxIdSql);
    if (resMaxId == nullptr) {
        std::cerr << "查询grades表最大id失败，无法生成新记录id" << std::endl;
        // 注意：resMaxId为nullptr时，无需调用clear（避免空指针异常）
        return false;
    }

    // 提取最大id（沿用libpq函数风格：PQresultStatus、PQntuples、PQgetvalue）
    int newId = 1; // 默认值：若表为空，id从1开始
    if (PQresultStatus(resMaxId) == PGRES_TUPLES_OK) { // 校验查询结果状态正常
        int rowCount = PQntuples(resMaxId); // 获取结果集行数（与selectPrint一致）
        if (rowCount > 0) { // 结果集有数据（表非空）
            string maxIdStr = PQgetvalue(resMaxId, 0, 0); // 提取第0行第0列的最大id（与selectPrint一致）
            if (!maxIdStr.empty()) { // 避免最大id为NULL（表有数据但id为空，极端场景）
                newId = std::stoi(maxIdStr) + 1; // 最大id+1，生成新id（软编码，无硬编码）
            }
        }
    }
    db->clear(resMaxId); // 清理最大id查询结果集，释放内存
    std::cout << newId << std::endl;
    // 第二步：软编码 - 构建INSERT语句（使用方法参数，无硬编码值）
    // 拼接SQL，使用studentId、taskId参数和动态生成的newId，避免硬编码
    std::string insertGradeSql = "INSERT INTO grades ("
                                 "id, "
                                 "student_id, "
                                 "task_id, "
                                 "score, "
                                 "recorded_by, "
                                 "created_at"
                                 ") VALUES ("
                                 + std::to_string(newId) + ", " // 动态生成的id（软编码）
                                 "'" + studentId + "', "       // 方法参数：学生ID（软编码，无硬编码STU001）
                                 "'" + taskId + "', "          // 方法参数：任务ID（软编码，无硬编码T2023DATA10101）
                                 "NULL, "
                                 "NULL, "
                                 "CURRENT_TIMESTAMP"
                                 ");";

    auto resInsert = db->executeSQL(insertGradeSql);
    if (resInsert == nullptr) {
        std::cerr << "插入grades表失败" << std::endl;
        db->clear(resInsert);
        return false;
    }
    db->clear(resInsert);

    std::cout << "开始执行更新" << std::endl;

    // 第三步：保留软编码更新逻辑（使用taskId参数，无硬编码）
    std::string updateTaskSql = "UPDATE teaching_tasks "
                     "SET current_enrolled = current_enrolled + 1 "
                     "WHERE task_id = '" + taskId + "' "        // 方法参数：目标任务ID（软编码）
                     "  AND max_capacity > current_enrolled;"; // 校验剩余容量

    auto resUpdate = db->executeSQL(updateTaskSql);
    if (resUpdate == nullptr) {
        std::cerr << "更新teaching_tasks表失败" << std::endl;
        db->clear(resUpdate);
        return false;
    }
    db->clear(resUpdate);

    return true;
}

bool StudentBroker::dropInTask(const std::string& studentId, const std::string& taskId)
{
    std::cout << "开始执行退课操作 - 学生ID: " << studentId
              << ", 任务ID: " << taskId << std::endl;

    try {
        std::cout << "执行1" << std::endl;
        // 第一步：检查教学任务是否存在
        {
            std::string sql = "SELECT 1 FROM teaching_tasks WHERE task_id = '" + taskId + "';";
            auto result = db->executeSQL(sql);

            if (!result) {
                std::cerr << "错误：查询教学任务返回空结果" << std::endl;
                return false;
            }

            ExecStatusType status = PQresultStatus(result);
            if (status != PGRES_TUPLES_OK) {
                std::cerr << "错误：查询教学任务失败，状态码: " << status << std::endl;
                db->clear(result);
                return false;
            }

            int rowCount = PQntuples(result);
            db->clear(result);

            if (rowCount == 0) {
                std::cerr << "错误：教学任务不存在 - " << taskId << std::endl;
                return false;
            }
        }
        std::cout << "execute 2" << std::endl;

        // 第二步：检查学生是否已选此课
        bool hasEnrolled = false;
        {
            std::string sql = "SELECT id FROM grades WHERE student_id = '" + studentId
                            + "' AND task_id = '" + taskId + "'";
            auto result = db->executeSQL(sql);
            std::println("------ print -------");
            db->selectPrint(result);
            std::println("--------------------");
            if (!result) {
                std::cerr << "错误：查询选课记录返回空结果" << std::endl;
                return false;
            }

            ExecStatusType status = PQresultStatus(result);
            if (status != PGRES_TUPLES_OK) {
                std::cerr << "错误：查询选课记录失败，状态码: " << status << std::endl;
                db->clear(result);
                return false;
            }

            hasEnrolled = (PQntuples(result) > 0);
            db->clear(result);
        }

        if (!hasEnrolled) {
            std::cerr << "错误：学生未选择该课程" << std::endl;
            return false;
        }

        std::cout << "验证通过，执行退课..." << std::endl;

        // 第三步：删除成绩记录
        int deletedRows = 0;
        {
            std::string sql = "DELETE FROM grades WHERE student_id = '" + studentId
                            + "' AND task_id = '" + taskId + "'";

            std::cout << "执行SQL: " << sql << std::endl;

            auto result = db->executeSQL(sql);
            if (!result) {
                std::cerr << "错误：删除操作返回空结果" << std::endl;
                return false;
            }

            ExecStatusType status = PQresultStatus(result);
            if (status != PGRES_COMMAND_OK) {
                std::cerr << "错误：删除操作失败，状态码: " << status << std::endl;
                db->clear(result);
                return false;
            }

            char* affectedStr = PQcmdTuples(result);
            if (affectedStr) {
                deletedRows = std::stoi(affectedStr);
            }
            db->clear(result);

            std::cout << "删除成功，影响行数: " << deletedRows << std::endl;
        }

        if (deletedRows == 0) {
            std::cerr << "警告：未删除任何记录" << std::endl;
            return false;
        }

        // 第四步：更新选课人数
        {
            std::string sql = "UPDATE teaching_tasks "
                            "SET current_enrolled = current_enrolled - 1 "
                            "WHERE task_id = '" + taskId + "' "
                            "AND current_enrolled > 0 "
                            "RETURNING current_enrolled";

            std::cout << "执行SQL: " << sql << std::endl;

            auto result = db->executeSQL(sql);
            if (!result) {
                std::cerr << "警告：更新选课人数返回空结果" << std::endl;
                // 即使更新失败，删除操作已成功，所以返回true
                return true;
            }

            ExecStatusType status = PQresultStatus(result);
            if (status == PGRES_TUPLES_OK && PQntuples(result) > 0) {
                std::string newCount = PQgetvalue(result, 0, 0);
                std::cout << "更新成功，当前选课人数: " << newCount << std::endl;
            }
            db->clear(result);
        }

        std::cout << "退课操作完成" << std::endl;
        return true;

    } catch (const std::exception& e) {
        std::cerr << "异常发生: " << e.what() << std::endl;
        return false;
    }
}
// 构造函数默认将这个表名设置为students
StudentBroker::StudentBroker(DataBroker* db):
        db(db),tableName("students")
{}

StudentBroker::~StudentBroker(){

}

bool StudentBroker::enrollInCourse(const std::string& studentId, const std::string& courseId)
{
    //  首先需要找到对应的表 就是先找到对应的教学任务teachingTask
    std::string findTaskSql = "SELECT task_id FROM teaching_tasks WHERE course_id = '" + courseId +
                                "' AND status IS NULL OR status != 'closed' LIMIT 1";
    auto taskRes = db->executeSQL(findTaskSql);

    // 如果课程没有在教学任务中， 那么就不应该开设这个课程
    if (PQresultStatus(taskRes) != PGRES_TUPLES_OK || PQntuples(taskRes) == 0) {
            PQclear(taskRes);
            return false; // 没有找到可用的教学任务
    }

    // 然后就是得到教学id
    std::string taskId = PQgetvalue(taskRes, 0, 0);
    PQclear(taskRes);

    // 从Grade表中看这个学生是否选择了这个课程
    std::string checkSql = "SELECT COUNT(*) FROM grades WHERE student_id = '" +
                            studentId + "' AND task_id = '" + taskId + "'";
    auto checkRes = db->executeSQL(checkSql);
    int count = std::stoi(PQgetvalue(checkRes, 0, 0));
    PQclear(checkRes);

    if ( count > 0 ) {
        return false;
    }
    std::string insertSql = "INSERT INTO Grades (student_id, task_id, score) VALUES ('" +
                               studentId + "', '" + taskId + "', NULL)";

    PGresult* insertRes = db->executeSQL(insertSql);
    bool success = (PQresultStatus(insertRes) == PGRES_COMMAND_OK);
    PQclear(insertRes);

    return success;
}

StudentRole* StudentBroker::findStudentById(const std::string& id)
{
    // todo ： 后期修复db类中容易被攻击的函数pgexec
    std::string sql = "select * from students where id ='"+ id + "'";

    // 执行这个sql语句
    auto res = db->executeSQL(sql);
    if (PQntuples(res) <= 0)    {
        std::println("查询结果为空");
        db->clear(res);
        return nullptr;
    }
    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "查询失败 "<< std::endl;
        PQclear(res);
        return nullptr;
    }
    if (res == nullptr) return nullptr;
    // 提取数据
    std::string student_id = PQgetvalue(res, 0, 0);
    std::string name = PQgetvalue(res, 0, 1);
    std::string gender = PQgetvalue(res, 0, 2);
    std::string gpa_str = PQgetvalue(res, 0, 3);
    // 转换类型
    float currentGPA = 0.0f;
    if (!gpa_str.empty()) {
            currentGPA = std::stof(gpa_str);
    }
    // 构建对象然后返回
    StudentRole* student = new StudentRole(
            student_id.empty() ? "":student_id,
            name.empty() ? "":name,
            gender.empty() ? "":gender
    );
    return student;
}

bool StudentBroker::saveStudent(StudentRole* student)
{
    // 首先检查学生
    if (!student) {
        return false;
    }
    // 获取学生信息
    std::string id = student->getId();
    std::string name = student->getName();
    std::string gender = student->getGender();
    // 丢弃掉废弃接口
    // float gpa = student->getCurrentGPA();

    std::string sql = "INSERT INTO students (id, name, gender) VALUES ('" +
                         id + "', '" +
                         name + "', '" +
                         gender + "', " +
                         ")";
    // 执行插入
    auto res = db->executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);

    PQclear(res);
    return success;

}

// 已经弃用 上层接口没有实现
double StudentBroker::calculateGPA(const std::string& studentId)
{
    return 0;
    // todo: 计算GPA 可能会弃用
}
