# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/secretarycontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/secretarycontroller.cppm"
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
# 103 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/secretarycontroller.cppm"
bool SecretaryController::assignTeacherToTask(const string& taskId, const string& teacherId) {
    TeachingTask* task = taskBroker->findTaskById(taskId);
    if (!task) throw std::runtime_error("授课任务不存在");
    return taskBroker->assignTeacherToTask(taskId, teacherId);
}
