# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/teachercontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/teachercontroller.cppm"
export module maincontroller:teachercontroller;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;

export import DataBase;
export import std;

using std::vector;
using std::string;

export class TeacherController {
public:
    TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* taskBroker);
    TeacherRole* getTeacherProfile(const string& teacherId);
    vector<TeachingTask*> getTeachingAssignments(const string& teacherId);
    bool submitStudentGrade(const string& teacherId, const string& studentId, float grade);
    bool assignToCourseTask(const string& teacherId, const string& taskId);


    vector<StudentRole*> getTaskEnrollments(const string& taskId);
    vector<GradeRecord*> getTaskGrades(const string& taskId);

private:
    TeacherBroker* teacherBroker;
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;

    StudentBroker* studentBroker;
};

TeacherController::TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), courseBroker(cBroker), taskBroker(tskBroker), studentBroker(nullptr) {}

TeacherRole* TeacherController::getTeacherProfile(const string& teacherId) {
    if (teacherId.empty()) throw std::invalid_argument("教师ID不能为空");
    TeacherRole* teacher = teacherBroker->findTeacherById(teacherId);
    if (!teacher) throw std::runtime_error("教师不存在");
    return teacher;
}


vector<TeachingTask*> TeacherController::getTeachingAssignments(const std::string& teacherId) {
# 61 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/teachercontroller.cppm"
    vector<TeachingTask*> result;
    return result;
}
# 85 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/teachercontroller.cppm"
bool TeacherController::submitStudentGrade(const string& teacherId, const string& studentId, float grade) {

    if (teacherId.empty() || studentId.empty()) throw std::invalid_argument("教师ID或学生ID不能为空");
    if (grade < 0 || grade > 100) throw std::invalid_argument("成绩需在0-100之间");



    return false;
}

bool TeacherController::assignToCourseTask(const string& teacherId, const string& taskId) {

    if (teacherId.empty() || taskId.empty()) throw std::invalid_argument("教师ID或任务ID不能为空");



    return false;
}

vector<StudentRole*> TeacherController::getTaskEnrollments(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<StudentRole*> students;





    return students;
}

vector<GradeRecord*> TeacherController::getTaskGrades(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");


    vector<GradeRecord*> result;
    return result;
}
