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
    Teacher* getTeacherProfile(const string& teacherId);
    vector<TeachingTask*> getTeachingAssignments(const string& teacherId);
    bool submitStudentGrade(const string& teacherId, const string& studentId, float grade);
    bool assignToCourseTask(const string& teacherId, const string& taskId);
private:
    TeacherBroker* teacherBroker;
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
};

TeacherController::TeacherController(TeacherBroker* tBroker, CourseBroker* cBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), courseBroker(cBroker), taskBroker(tskBroker) {}

TeacherRole* TeacherController::getTeacherProfile(const string& teacherId) {
    if (teacherId.empty()) throw std::invalid_argument("教师ID不能为空");
    TeacherRole* teacher = teacherBroker->findTeacherById(teacherId);
    if (!teacher) throw std::runtime_error("教师不存在");
    return teacher;
}

vector<TeachingTask*> TeacherController::getTeachingAssignments(const std::string& teacherId) {
    TeacherRole* teacher = getTeacherProfile(teacherId);
    vector<TeachingTask*> allTasks = taskBroker->getAllTasks();
    vector<TeachingTask*> teacherTasks;
    for (auto& task : allTasks) {
        if (task->getTeacherId() == teacherId) {
            teacherTasks.push_back(task);
        }
    }
    return teacherTasks;
}

bool TeacherController::submitStudentGrade(const GradeSubmission& submission) {
    // 1. 基础校验
    const string& teacherId = submission.getTeacherId();
    const string& studentId = submission.getStudentId();
    const string& taskId = submission.getTaskId();
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

vector<StudentRole*> TeacherController::getTaskEnrollments(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<StudentRole*> students;
    for (const auto& sid : task->getEnrolledStudentIds()) {
        StudentRole* student = studentBroker->findStudentById(sid);
        if (student) students.push_back(student);
    }
    return students;
}

vector<GradeRecord*> TeacherController::getTaskGrades(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    return teacherBroker->getTaskGrades(taskId);
}


