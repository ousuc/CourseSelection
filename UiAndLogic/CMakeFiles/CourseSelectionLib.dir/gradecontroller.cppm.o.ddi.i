# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/gradecontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/gradecontroller.cppm"
export module maincontroller:gradecontroller;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;
export import DataTypes;

export import DataBase;
export import std;

using std::vector;
using std::string;

export class GradeController {
public:
    GradeController(TeacherBroker* tBroker, StudentBroker* sBroker, TeachingTaskBroker* tskBroker);
    bool submitFinalGrade(const GradeSubmission& submission);
    float getStudentGPA(const string& studentId);
    GradeRecord* getStudentTaskGrade(const string& studentId, const string& taskId);
    vector<GradeRecord*> getStudentAllGrades(const string& studentId);
    std::map<string, float> calculateTaskGradeStats(const string& taskId);
private:
    TeacherBroker* teacherBroker;
    StudentBroker* studentBroker;
    TeachingTaskBroker* taskBroker;
};

GradeController::GradeController(TeacherBroker* tBroker, StudentBroker* sBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), studentBroker(sBroker), taskBroker(tskBroker) {}
# 45 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/gradecontroller.cppm"
float GradeController::getStudentGPA(const string& studentId) {
    if (studentId.empty()) throw std::invalid_argument("学生ID不能为空");
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return studentBroker->calculateGPA(studentId);
}
