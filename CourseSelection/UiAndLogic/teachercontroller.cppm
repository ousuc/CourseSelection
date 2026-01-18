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

    // 添加缺失的声明
    vector<StudentRole*> getTaskEnrollments(const string& taskId);
    vector<GradeRecord*> getTaskGrades(const string& taskId);

private:
    TeacherBroker* teacherBroker;
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
    // 添加缺失的成员声明
    StudentBroker* studentBroker;  // 需要添加这个成员
};

TeacherController::TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), courseBroker(cBroker), taskBroker(tskBroker), studentBroker(nullptr) {}

TeacherRole* TeacherController::getTeacherProfile(const string& teacherId) {
    if (teacherId.empty()) throw std::invalid_argument("教师ID不能为空");
    std::println("开始获取老师简介");
    TeacherRole* teacher = teacherBroker->findTeacherById(teacherId);
    if (!teacher) throw std::runtime_error("教师不存在");
    return teacher;
}

// 直接改为查询task表  需要修复
vector<TeachingTask*> TeacherController::getTeachingAssignments(const std::string& teacherId) {
    // TeacherRole* teacher = getTeacherProfile(teacherId);
    // vector<TeachingTask*> allTasks = taskBroker->getAllTasks();
    // vector<TeachingTask*> teacherTasks;
    // for (auto& task : allTasks) {
    //     if (task->getTeacherId() == teacherId) {
    //         teacherTasks.push_back(task);
    //     }
    // }
    // return teacherTasks;
    // DataBroker db;
    // auto res = db.executeSQL("select * from teaching_tasks");

    // 需要返回具体的vector
    vector<TeachingTask*> result;
    return result;
}

// 这个submission中不存在相关的类 可以删除
// bool TeacherController::submitStudentGrade(const GradeSubmission& submission) {
//     // 1. 基础校验
//     const string& teacherId = submission.getTeacherId();
//     const string& studentId = submission.getStudentId();
//     const string& taskId = submission.getTaskId();
//     float score = submission.getScore();
//
//     if (score < 0 || score > 100) throw std::invalid_argument("成绩需在0-100之间");
//     TeacherRole* teacher = getTeacherProfile(teacherId);
//     TeachingTask* task = taskBroker->findTaskById(taskId);
//     if (!task) throw std::runtime_error("授课任务不存在");
//     if (task->getTeacherId() != teacherId) throw std::runtime_error("无该任务的评分权限");
//     if (!task->hasStudent(studentId)) throw std::runtime_error("学生未选该任务，无法评分");
//
//     // 2. 录入成绩
//     return teacherBroker->inputStudentGrade(teacherId, studentId, taskId, score);
// }

// submitStudentGrade的实现必须与声明一致
bool TeacherController::submitStudentGrade(const string& teacherId, const string& studentId, float grade) {
    // 简单实现以匹配声明
    if (teacherId.empty() || studentId.empty()) throw std::invalid_argument("教师ID或学生ID不能为空");
    if (grade < 0 || grade > 100) throw std::invalid_argument("成绩需在0-100之间");

    // 这里需要调用具体的业务逻辑
    // return teacherBroker->inputStudentGrade(teacherId, studentId, taskId, grade);
    return false; // 临时返回值
}

bool TeacherController::assignToCourseTask(const string& teacherId, const string& taskId) {
    // 需要实现这个函数
    if (teacherId.empty() || taskId.empty()) throw std::invalid_argument("教师ID或任务ID不能为空");

    // 这里需要调用具体的业务逻辑
    // return taskBroker->assignTeacherToTask(taskId, teacherId);
    return false; // 临时返回值
}

vector<StudentRole*> TeacherController::getTaskEnrollments(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<StudentRole*> students;
    // 注释掉使用了未定义studentBroker的代码
    // for (const auto& sid : task->getEnrolledStudentIds()) {
    //     StudentRole* student = studentBroker->findStudentById(sid);
    //     if (student) students.push_back(student);
    // }
    return students;
}

vector<GradeRecord*> TeacherController::getTaskGrades(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    // 注释掉使用了未定义方法的代码
    // return teacherBroker->getTaskGrades(taskId);
    vector<GradeRecord*> result;
    return result;
}
