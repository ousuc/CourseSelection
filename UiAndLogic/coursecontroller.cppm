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
public:
    CourseController(CourseBroker* cBroker, TeachingTaskBroker* tBroker, StudentBroker* sBroker);
    Course* getCourseDetails(const string& courseId);
    vector<TeachingTask*> getCourseTasks(const string& courseId);
    vector<StudentRole*> getTaskStudents(const string& taskId);
    bool isCourseActive(const string& courseId);
private:
    CourseBroker* courseBroker;
    TeachingTaskBroker* taskBroker;
    StudentBroker* studentBroker;
};

CourseController::CourseController(CourseBroker* cBroker, TeachingTaskBroker* tBroker, StudentBroker* sBroker)
    : courseBroker(cBroker), taskBroker(tBroker), studentBroker(sBroker) {}

Course* CourseController::getCourseDetails(const string& courseId) {
    if (courseId.empty()) throw std::invalid_argument("课程ID不能为空");
    Course* course = courseBroker->findCourseById(courseId);
    if (!course) throw std::runtime_error("课程不存在");
    return course;
}

// vector<TeachingTask*> CourseController::getCourseTasks(const string& courseId) {
//     Course* course = getCourseDetails(courseId);
//     vector<TeachingTask*> allTasks = taskBroker->getAllTasks();
//     vector<TeachingTask*> courseTasks;
//     for (auto& task : allTasks) {
//         if (task->getId() == courseId) {
//             courseTasks.push_back(task);
//         }
//     }
//     return courseTasks;
// }

// vector<StudentRole*> CourseController::getTaskStudents(const string& taskId) {
//     TeachingTask* task = taskBroker->findTaskById(taskId);
//     if (!task) throw std::runtime_error("授课任务不存在");
//     std::vector<StudentRole*> students;
//     for (const auto& sid : task->getEnrolledStudentIds()) {
//         StudentRole* student = studentBroker->findStudentById(sid);
//         if (student) students.push_back(student);
//     }
//     return students;
// }

// bool CourseController::isCourseActive(const string& courseId) {
//     Course* course = getCourseDetails(courseId);
//     return course->getIsActive();
// }

// vector<Course*> CourseController::getAvailableCourses() {
//     vector<Course*> allCourses = courseBroker->getAllCourses();
//     vector<Course*> availableCourses;
//     for (auto& course : allCourses) {
//         if (course->getIsActive()) {
//             availableCourses.push_back(course);
//         }
//     }
//     return availableCourses;
// }

