# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/maincontroller.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/maincontroller.cppm"
export module maincontroller;

export import :studentcontroller;
export import :teachercontroller;
export import :secretarycontroller;
export import :coursecontroller;
export import :gradecontroller;
export import DataBase;
export import std;

export class MainController {
public:
    MainController();

    ~MainController();
    StudentController* getStudentController();
    TeacherController* getTeacherController();
    SecretaryController* getSecretaryController();
    CourseController* getCourseController();
    GradeController* getGradeController();
    void initialize();


    void executeTeacherCommand(int choice, const string& teacherId) const;
    void executeStudentCommand(int choice, const string& studentId) const;

private:
    std::unique_ptr<StudentController> studentController;
    std::unique_ptr<TeacherController> teacherController;
    std::unique_ptr<SecretaryController> secretaryController;
    std::unique_ptr<CourseController> courseController;
    std::unique_ptr<GradeController> gradeController;
    CourseBroker* cBroker;
    TeachingTaskBroker* ttBroker;
    TeacherBroker* tBroker;
    StudentBroker* sBroker;
    DataBroker* db;
};
MainController::~MainController()
{
    delete cBroker;
    delete ttBroker;
    delete tBroker;
    delete sBroker;
    delete db;
}
# 56 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/maincontroller.cppm"
void MainController::executeTeacherCommand(int choice, const string& teacherId) const {

}
# 69 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/maincontroller.cppm"
void MainController::executeStudentCommand(int choice, const string& studentId) const {

}

MainController::MainController() {
    std::println("正在启动主控制器...");
    initialize();
    std::println("初始化成功");
}


void MainController::initialize() {

    db = new DataBroker();
    sBroker = new StudentBroker(db);
    tBroker = new TeacherBroker(db);
    ttBroker = new TeachingTaskBroker(db);
    cBroker = new CourseBroker(db);



    studentController = std::make_unique<StudentController>(sBroker,cBroker,ttBroker);
    teacherController = std::make_unique<TeacherController>(tBroker,cBroker,ttBroker);


    courseController = std::make_unique<CourseController>(cBroker,ttBroker,sBroker);
    gradeController = std::make_unique<GradeController>(tBroker,sBroker,ttBroker);
}

StudentController* MainController::getStudentController() {
    return studentController.get();
}

TeacherController* MainController::getTeacherController() {
    return teacherController.get();
}

SecretaryController* MainController::getSecretaryController() {
    return secretaryController.get();
}

CourseController* MainController::getCourseController() {
    return courseController.get();
}

GradeController* MainController::getGradeController() {
    return gradeController.get();
}
