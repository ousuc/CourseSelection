export module maincontroller:coursecontroller;

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

export class CourseController {
private:
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
    StudentBroker* studentBroker;
public:
    CourseController(CourseBroker* cBroker, TeachingTaskBroker* tBroker, StudentBroker* sBroker);
    Course* getCourseDetails(const string& courseId);
    vector<TeachingTask*> getCourseTasks(const string& courseId);
    vector<Student*> getTaskStudents(const string& taskId);
    bool isCourseActive(const string& courseId);
};

CourseController::CourseController(CourseBroker* cBroker, TeachingTaskBroker* tBroker, StudentBroker* sBroker)
    : courseBroker(cBroker), taskBroker(tBroker), studentBroker(sBroker) {}

Course* CourseController::getCourseDetails(const std::string& courseId) {
    if (courseId.empty()) throw std::invalid_argument("课程ID不能为空");
    Course* course = courseBroker->findCourseById(courseId);
    if (!course) throw std::runtime_error("课程不存在");
    return course;
}

std::vector<TeachingTask*> CourseController::getCourseTasks(const std::string& courseId) {
    Course* course = getCourseDetails(courseId);
    std::vector<TeachingTask*> allTasks = taskBroker->getAllTasks();
    std::vector<TeachingTask*> courseTasks;
    for (auto& task : allTasks) {
        if (task->getCourseId() == courseId) {
            courseTasks.push_back(task);
        }
    }
    return courseTasks;
}

std::vector<StudentRole*> CourseController::getTaskStudents(const std::string& taskId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    std::vector<StudentRole*> students;
    for (const auto& sid : task->getEnrolledStudentIds()) {
        StudentRole* student = studentBroker->findStudentById(sid);
        if (student) students.push_back(student);
    }
    return students;
}

bool CourseController::isCourseActive(const std::string& courseId) {
    Course* course = getCourseDetails(courseId);
    return course->getIsActive();
}

std::vector<Course*> CourseController::getAvailableCourses() {
    std::vector<Course*> allCourses = courseBroker->getAllCourses();
    std::vector<Course*> availableCourses;
    for (auto& course : allCourses) {
        if (course->getIsActive()) {
            availableCourses.push_back(course);
        }
    }
    return availableCourses;
}

