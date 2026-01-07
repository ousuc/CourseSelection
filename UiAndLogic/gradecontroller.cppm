export module maincontroller:gradecontroller

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

float GradeController::getStudentGPA(const string& studentId) {
    if (studentId.empty()) throw std::invalid_argument("学生ID不能为空");
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return studentBroker->calculateGPA(studentId);
}

GradeRecord* GradeController::getStudentTaskGrade(const string& studentId, const string& taskId) {
    if (studentId.empty() || taskId.empty()) throw std::invalid_argument("学生ID/任务ID不能为空");
    return teacherBroker->getStudentTaskGrade(studentId, taskId);
}

vector<GradeRecord*> GradeController::getStudentAllGrades(const string& studentId) {
    StudentRole* student = studentBroker->findStudentById(studentId);
    if (!student) throw std::runtime_error("学生不存在");
    return teacherBroker->getStudentAllGrades(studentId);
}

std::map<string, float> GradeController::calculateTaskGradeStats(const string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    vector<GradeRecord*> grades = teacherBroker->getTaskGrades(taskId);

    std::map<string, float> stats;
    if (grades.empty()) {
        stats["平均分"] = 0.0f;
        stats["最高分"] = 0.0f;
        stats["最低分"] = 0.0f;
        return stats;
    }

    vector<float> scores;
    for (auto& grade : grades) {
        scores.push_back(grade->getScore());
    }

    stats["平均分"] = std::accumulate(scores.begin(), scores.end(), 0.0f) / scores.size();
    stats["最高分"] = *std::max_element(scores.begin(), scores.end());
    stats["最低分"] = *std::min_element(scores.begin(), scores.end());
    return stats;
}
