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
    Student* getStudentProfile(const string& studentId);
    vector<Course*> getAllEnrolledCourses(const string& studentId);
    bool enrollStudent(const string& studentId, const string& taskId);
    bool dropStudent(const string& studentId, const string& taskId);
    float calculateGPA(const string& studentId);
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

vector<Course*> StudentController::getAllEnrolledCourses(const string& studentId) {
    StudentRole* student = getStudentProfile(studentId);
    vector<Course*> courses;
    for (const auto& taskId : student->getEnrolledTasksId()) {
        TeachingTask* task = taskBroker->findTaskById(taskId);
        if (task) {
            Course* course = courseBroker->findCourseById(task->getCourseId());
            if (course && std::find(courses.begin(), courses.end(), course) == courses.end()) {
                courses.push_back(course);
            }
        }
    }
    return courses;
}

vector<TeachingTask*> StudentController::getAllEnrolledTasks(const string& studentId) {
    StudentRole* student = getStudentProfile(studentId);
    vector<TeachingTask*> tasks;
    for (const auto& taskId : student->getEnrolledTasksId()) {
        TeachingTask* task = taskBroker->findTaskById(taskId);
        if (task) tasks.push_back(task);
    }
    return tasks;
}

bool StudentController::enrollStudentInTask(const string& studentId, const string& taskId) {
    // 1. 基础校验
    StudentRole* student = getStudentProfile(studentId);
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    Course* course = courseBroker->findCourseById(task->getCourseId());
    if (!course || !course->getIsActive()) throw std::runtime_error("课程未激活，无法选课");

    // 2. 业务规则校验
    if (!task->isInEnrollTime()) throw std::runtime_error("超出选课时间范围");
    if (task->isFull()) throw std::runtime_error("任务人数已满，无法选课");
    if (student->hasTask(taskId)) throw std::runtime_error("已选该任务，无需重复选课");

    // 3. 执行选课
    bool taskOk = task->addStudent(studentId);
    bool studentOk = student->enrollInTask(taskId);
    bool brokerOk = studentBroker->enrollInCourse(studentId, course->getCourseId());

    if (taskOk && studentOk && brokerOk) {
        taskBroker->saveTask(task);
        studentBroker->saveStudent(student);
        return true;
    }
    return false;
}

bool StudentController::dropStudentFromTask(const string& studentId, const string& taskId) {
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

float StudentController::calculateStudentGPA(const string& studentId) {
    float gpa = studentBroker->calculateGPA(studentId);
    StudentRole* student = getStudentProfile(studentId);
    student->setCurrentGPA(gpa);
    studentBroker->saveStudent(student);
    return gpa;
}

vector<GradeRecord*> StudentController::getStudentGrades(const string& studentId) {
    // 从TeacherBroker查询学生成绩（实际需扩展Broker接口）
    return studentBroker->getStudentGrades(studentId);
}



