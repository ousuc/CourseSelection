# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/TeacherRole.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/TeacherRole.cppm"
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

    bool inputStudentGrade(const string& studentId, const string& taskId, float score);
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

    if (studentId.empty() || taskId.empty()) {
        std::print("studentId/taskId 为空！\n");
        return false;
    }

    if (score < 0.0f || score > 100.0f){
        std::print("输入的分数不在[0,100]内！\n");
        return false;
    }


    string key = studentId + "|" + taskId;


    GradeRecord record;
    record.studentId = studentId;
    record.taskId = taskId;
    record.score = score;


    gradeRecords[key] = record;

    return true;
}
