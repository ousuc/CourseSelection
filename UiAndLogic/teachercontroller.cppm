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
private:
    TeacherBroker* teacherBroker;
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
public:
    TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* taskBroker);
    Teacher* getTeacherProfile(const string& teacherId);
    vector<TeachingTask*> getTeachingAssignments(const string& teacherId);
    bool submitStudentGrade(const string& teacherId, const string& studentId, float grade);
    bool assignToCourseTask(const string& teacherId, const string& taskId);
};

TeacherController::TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), courseBroker(cBroker), taskBroker(tskBroker) {}

TeacherRole* TeacherController::getTeacherProfile(const std::string& teacherId) {
    if (teacherId.empty()) throw std::invalid_argument("教师ID不能为空");
    TeacherRole* teacher = teacherBroker->findTeacherById(teacherId);
    if (!teacher) throw std::runtime_error("教师不存在");
    return teacher;
}

std::vector<TeachingTask*> TeacherController::getTeachingAssignments(const std::string& teacherId) {
    TeacherRole* teacher = getTeacherProfile(teacherId);
    std::vector<TeachingTask*> allTasks = taskBroker->getAllTasks();
    std::vector<TeachingTask*> teacherTasks;
    for (auto& task : allTasks) {
        if (task->getTeacherId() == teacherId) {
            teacherTasks.push_back(task);
        }
    }
    return teacherTasks;
}

bool TeacherController::submitStudentGrade(const GradeSubmission& submission) {
    // 1. 基础校验
    const std::string& teacherId = submission.getTeacherId();
    const std::string& studentId = submission.getStudentId();
    const std::string& taskId = submission.getTaskId();
    float score = submission.getScore();

    if (score < 0 || score > 100) throw std::invalid_argument("成绩需在0-100之间");
    TeacherRole* teacher = getTeacherProfile(teacherId);
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    if (task->getTeacherId() != teacherId) throw std::runtime_error("无该任务的评分权限");
    if (!task->hasStudent(studentId)) throw std::runtime_error("学生未选该任务，无法评分");

    // 2. 录入成绩
    return teacherBroker->inputStudentGrade(teacherId, studentId, taskId, score);
}

std::vector<StudentRole*> TeacherController::getTaskEnrollments(const std::string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<StudentRole*> students;
    for (const auto& sid : task->getEnrolledStudentIds()) {
        StudentRole* student = studentBroker->findStudentById(sid);
        if (student) students.push_back(student);
    }
    return students;
}

std::vector<GradeRecord*> TeacherController::getTaskGrades(const std::string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    return teacherBroker->getTaskGrades(taskId);
}


