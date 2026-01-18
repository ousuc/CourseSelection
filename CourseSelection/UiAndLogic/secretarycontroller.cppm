export module maincontroller:secretarycontroller;

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

// 前置声明（如果需要）

// 莫名奇妙生成的类
class TaskCreationRequest;

export class SecretaryController {
public:
    SecretaryController(SecretaryRole* sec, CourseBroker* cBroker, TeacherBroker* tBroker,
                       TeachingTaskBroker* taskBroker, DataBroker* db);

    bool createCourse(const string& courseId, const string& courseName, float credits);

    bool createTeachingTask(const TaskCreationRequest& request);

    bool toggleCourseActive(const string& courseId, bool active);

    vector<Course*> getAllCourses();
    bool assignTeacherToTask(const string& taskId, const string& teacherId);

private:
    SecretaryRole* secretary;
    CourseBroker* courseBroker;
    TeacherBroker* teacherBroker;
    TeachingTaskBroker* taskBroker;
    DataBroker* dataBroker;
};

SecretaryController::SecretaryController(SecretaryRole* sec, CourseBroker* cBroker,
                                        TeacherBroker* tBroker, TeachingTaskBroker* tskBroker,
                                        DataBroker* db)
    : secretary(sec), courseBroker(cBroker), teacherBroker(tBroker),
      taskBroker(tskBroker), dataBroker(db) {}

bool SecretaryController::createCourse(const string& courseId, const string& courseName, float credits) {
    if (courseId.empty() || courseName.empty()) throw std::invalid_argument("课程ID/名称不能为空");
    if (credits <= 0) throw std::invalid_argument("学分需大于0");
    if (courseBroker->findCourseById(courseId)) throw std::runtime_error("课程ID已存在");

    Course* course = new Course(courseId, courseName, credits);
    return courseBroker->saveCourse(course);
}

//
// bool SecretaryController::createTeachingTask(const TaskCreationRequest& request) {
//     string courseId = request.getCourseId();
//     string teacherId = request.getTeacherId();
//     int maxCapacity = request.getMaxCapacity();

//     if (maxCapacity <= 0) throw std::invalid_argument("任务容量需大于0");
//     Course* course = courseBroker->findCourseById(courseId);
//     if (!course || !course->getIsActive()) throw std::runtime_error("课程未激活，无法创建任务");
//     TeacherRole* teacher = teacherBroker->findTeacherById(teacherId);
//     if (!teacher) throw std::runtime_error("教师不存在");

//     // 生成任务ID + 设置选课时间（默认30天）
//     string taskId = courseId + "_" + std::to_string(std::time(nullptr));
//     std::time_t now = std::time(nullptr);
//     TeachingTask* task = new TeachingTask(
//         taskId,
//         request.getSchedule(),
//         now,
//         now + 30 * 24 * 3600, // 选课周期30天
//         maxCapacity,
//         courseId,
//         teacherId
//     );

//     bool saveOk = taskBroker->saveTask(task);
//     if (saveOk) assignTeacherToTask(taskId, teacherId);
//     return saveOk;
// }

// 删除对应
// bool SecretaryController::toggleCourseActive(const string& courseId, bool active) {
//     Course* course = courseBroker->findCourseById(courseId);
//     if (!course) throw std::runtime_error("课程不存在");
//     // 删除： 没有这个接口
//     // course->setIsActive(active);
//     return active ? courseBroker->activateCourse(courseId) : courseBroker->deactivateCourse(courseId);
// }


// 使用了接口没有提供的方法，  todo：尝试实现对应接口
// vector<Course*> SecretaryController::getAllCourses() {
//     return courseBroker->getAllCourses();
// }

bool SecretaryController::assignTeacherToTask(const string& taskId, const string& teacherId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    return taskBroker->assignTeacherToTask(taskId, teacherId);
}
