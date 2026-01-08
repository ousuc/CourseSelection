module;
#include<libpq-fe.h>
export module DataBase:StudentBroker;
import std;
import :DataBroker;
// 前置声明
class StudentRole;

export class StudentBroker{
public:
    StudentBroker(DataBroker* db);
    ~StudentBroker();

    bool saveStudent(StudentRole* student);
    StudentRole* findStudentById(const std::string& id);
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
    //  首先需要找到对应的表 就是先找到对应的教学任务teachingTask
    std::string findTaskSql = "SELECT task_id FROM Teaching_Tasks WHERE course_id = '" + courseId +
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
    std::string checkSql = "SELECT COUNT(*) FROM Grades WHERE student_id = '" +
                            studentId + "' AND task_id = '" + taskId + "'";
    auto checkRes = db->executeSQL(checkSql);
    int count = std::stoi(PQgetvalue(checkRes, 0, 0));
    PQclear(checkRes)

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

    // 检测查询出来的状态如何
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "查询失败: " << PQerrorMessage(connection) << std::endl;
        PQclear(res);
        return nullptr;
    }

    // 提取数据
    std::string student_id = PQgetvalue(res, 0, 0);
    std::string name = PQgetvalue(res, 0, 1);
    std::string gender = PQgetvalue(res, 0, 2);
    std::string gpa_str = PQgetvalue(res, 0, 3);
    // 转换类型
    float currentGPA = 0.0f;
    if (gpa_str != nullptr && strlen(gpa_str) > 0) {
            currentGPA = std::stof(gpa_str);
    }
    // 构建对象然后返回
    StudentRole* student = new StudentRole(
            student_id ? student_id : "",
            name ? name : "",
            gender ? gender : "",
            currentGPA
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
    float gpa = student->getCurrentGPA();
    std::string sql = "INSERT INTO Students (id, name, gender, currentGPA) VALUES ('" +
                         id + "', '" +
                         name + "', '" +
                         gender + "', " +
                         std::to_string(gpa) + ")";
    // 执行插入
    auto res = executeSQL(sql);
    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);

    PQclear(res);
    return success;
}

double StudentBroker::calculateGPA(const std::string& studentId)
{

    // todo: 计算GPA 可能会弃用
}
