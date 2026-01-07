export module maincontroller:gradecontroller

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

export class GradeController {
private:
    TeacherBroker* teacherBroker;
    StudentBroker* studentBroker;
    TeachingTaskBroker* taskBroker;
public:
    GradeController(TeacherBroker* tBroker, StudentBroker* sBroker, TeachingTaskBroker* taskBroker);
    bool submitGrade(const string& teacherId, const string& studentId, float grade);
    float getStudentGPA(const string& studentId);
    float getStudentTaskGrade(const string& studentId, const string& taskId);
};

GradeController::GradeController(TeacherBroker* tBroker, StudentBroker* sBroker, TeachingTaskBroker* tskBroker)
    : teacherBroker(tBroker), studentBroker(sBroker), taskBroker(tskBroker) {}

bool GradeController::submitFinalGrade(const GradeSubmission& submission) {
    // 复用TeacherController的成绩提交逻辑，标记为最终成绩
    TeacherController teacherCtrl(teacherBroker, nullptr, taskBroker);
    bool submitOk = teacherCtrl.submitStudentGrade(submission);
    if (submitOk) {
        // 实际项目中可添加“最终成绩锁定”逻辑
        return true;
    }
    return false;
}

float GradeController::getStudentGPA(const std::string& studentId) {
    if (studentId.empty()) throw std::invalid_argument("学生ID不能为空");
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return studentBroker->calculateGPA(studentId);
}

GradeRecord* GradeController::getStudentTaskGrade(const std::string& studentId, const std::string& taskId) {
    if (studentId.empty() || taskId.empty()) throw std::invalid_argument("学生ID/任务ID不能为空");
    return teacherBroker->getStudentTaskGrade(studentId, taskId);
}

std::vector<GradeRecord*> GradeController::getStudentAllGrades(const std::string& studentId) {
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return teacherBroker->getStudentAllGrades(studentId);
}

std::map<std::string, float> GradeController::calculateTaskGradeStats(const std::string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<GradeRecord*> grades = teacherBroker->getTaskGrades(taskId);

    std::map<std::string, float> stats;
    if (grades.empty()) {
        stats["平均分"] = 0.0f;
        stats["最高分"] = 0.0f;
        stats["最低分"] = 0.0f;
        return stats;
    }

    std::vector<float> scores;
    for (auto& grade : grades) {
        scores.push_back(grade->getScore());
    }

    stats["平均分"] = std::accumulate(scores.begin(), scores.end(), 0.0f) / scores.size();
    stats["最高分"] = *std::max_element(scores.begin(), scores.end());
    stats["最低分"] = *std::min_element(scores.begin(), scores.end());
    return stats;
}
