# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/coursecontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/coursecontroller.cppm"
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
