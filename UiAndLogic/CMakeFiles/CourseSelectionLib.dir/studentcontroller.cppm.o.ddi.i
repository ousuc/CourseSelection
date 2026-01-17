# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/studentcontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/studentcontroller.cppm"
export module maincontroller:studentcontroller;

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

export class StudentController {
public:
    StudentController(StudentBroker* sBroker, CourseBroker* cBroker, TeachingTaskBroker* tBroker);
    StudentRole* getStudentProfile(const string& studentId);
    vector<Course*> getAllEnrolledCourses(const string& studentId);
    bool enrollStudent(const string& studentId, const string& taskId);
    bool dropStudent(const string& studentId, const string& taskId);
    float calculateGPA(const string& studentId);


    vector<class GradeRecord*> getStudentGrades(const string& studentId);
private:
    StudentBroker* studentBroker;
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
};

StudentController::StudentController(StudentBroker* sBroker, CourseBroker* cBroker, TeachingTaskBroker* tBroker)
    : studentBroker(sBroker), courseBroker(cBroker), taskBroker(tBroker) {}

StudentRole* StudentController::getStudentProfile(const string& studentId) {
    if (studentId.empty()) throw std::invalid_argument("学生ID不能为空");
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return student;
}
# 69 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/studentcontroller.cppm"
bool StudentController::enrollStudent(const string& studentId, const string& taskId) {

    StudentRole* student = getStudentProfile(studentId);
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");





    if (!task->isInEnrollTime()) throw std::runtime_error("超出选课时间范围");
    if (task->isFull()) throw std::runtime_error("任务人数已满，无法选课");
    if (student->hasTask(taskId)) throw std::runtime_error("已选该任务，无需重复选课");


    bool taskOk = task->addStudent(studentId);
    bool studentOk = student->enrollInTask(taskId);





    if (taskOk && studentOk) {
        taskBroker->saveTask(task);
        studentBroker->saveStudent(student);
        return true;
    }
    return false;
}

bool StudentController::dropStudent(const string& studentId, const string& taskId) {
    StudentRole* student = getStudentProfile(studentId);
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");

    if (!student->hasTask(taskId)) throw std::runtime_error("未选该任务，无法退课");

    bool taskOk = task->removeStudent(studentId);
    bool studentOk = student->dropTask(taskId);
    if (taskOk && studentOk) {
        taskBroker->saveTask(task);
        studentBroker->saveStudent(student);
        return true;
    }
    return false;
}
# 126 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/studentcontroller.cppm"
vector<class GradeRecord*> StudentController::getStudentGrades(const string& studentId) {


    DataBroker db;
    auto res = db.executeSQL("select * from students");
    db.selectPrint(res);
    db.clear(res);
    return {};
}
