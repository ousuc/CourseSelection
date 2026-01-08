export module teacherRole;
import std;
import role;
using std::map;
using std::string;
export class GradeRecord{
public:
    string studentId;
    string taskId;
    float score;
};

export class TeacherRole : public Role{
public:
    TeacherRole(string id, string name, string gender);
    // 核心业务逻辑方法：
    bool inputStudentGrade(const string& studentId, const string& taskId, float score);  // 录入成绩
    virtual string getRoleType();
private:
    map<string, GradeRecord> gradeRecords;
};


TeacherRole::TeacherRole(string id, string name, string gender)
    : Role(id, name, gender)
{}
string TeacherRole::getRoleType(){
    return std::format("teacher");
}
bool TeacherRole::inputStudentGrade(const string& studentId, const string& taskId, float score) {
    // 简单的参数验证
    if (studentId.empty() || taskId.empty()) {
        std::print("studentId/taskId 为空！\n");
        return false;
    }

    if (score < 0.0f || score > 100.0f){
        std::print("输入的分数不在[0,100]内！\n");
        return false;  // 分数范围0-100
    }

    // 生成唯一key
    string key = studentId + "|" + taskId;

    // 创建或更新成绩记录
    GradeRecord record;
    record.studentId = studentId;
    record.taskId = taskId;
    record.score = score;

    // 直接插入或覆盖
    gradeRecords[key] = record;

    return true;
}
