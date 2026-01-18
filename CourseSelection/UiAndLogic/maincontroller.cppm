export module maincontroller;

export import :studentcontroller;
export import :teachercontroller;
export import :secretarycontroller;
export import :coursecontroller;
export import :gradecontroller;
export import DataBase;
export import std;
import InputHelper;
class TerminalUI;

export class MainController {
public:
    friend  class TerminalUI;
    MainController();
    // 定义析构函数
    ~MainController();
    StudentController* getStudentController();
    TeacherController* getTeacherController();
    SecretaryController* getSecretaryController();
    CourseController* getCourseController();
    GradeController* getGradeController();
    void initialize();

    // 添加执行学生和执行老师的方法
    void executeTeacherCommand(int choice, const string& teacherId) const;
    void executeStudentCommand(int choice, const string& studentId) const;
// 重新将UI类构建到该处过于复杂耗时，直接暴露数据库控制成员，但是对外交互是UI所以暂时
// 是不会暴露给最外层
    CourseBroker* cBroker;
    TeachingTaskBroker* ttBroker;
    TeacherBroker* tBroker;
    StudentBroker* sBroker;
    DataBroker* db;
private:
    std::unique_ptr<StudentController> studentController;
    std::unique_ptr<TeacherController> teacherController;
    std::unique_ptr<SecretaryController> secretaryController;
    std::unique_ptr<CourseController> courseController;
    std::unique_ptr<GradeController> gradeController;

};
MainController::~MainController()
{
    delete cBroker;
    delete ttBroker;
    delete tBroker;
    delete sBroker;
    delete db;
}

// 执行老师的命令
// print("==================== 教师功能菜单 [{}] ====================\n",teacherId);
// print("1. 查看个人信息\n");
// print("2. 查看授课任务\n");
// print("3. 录入学生成绩\n");
// print("4. 查看任务学生名单\n");
// print("0. 返回主菜单\n");
// print("======================================================================\n");
void MainController::executeTeacherCommand(int choice, const string& teacherId) const {
switch(choice) {
    case 1:
        TeacherRole* teacher;
        try{
            teacher = teacherController->getTeacherProfile(teacherId);
        }catch (std::exception& e){
            std::println("{} 异常",e.what());
            break;
        }
        std::println("{}",teacher->getProfile());
        delete teacher;
    case 2:
        tBroker->printTeachingTasks(teacherId);
    case 3:
        tBroker->printTaskStudentsGrouped(teacherId);
    // case 2:
    // case 3:
    // case 4:
    // case 5:
    // case 0:
}
}

// 执行学生的命令
// print("==================== 学生功能菜单 [{}] ====================\n",studentId);
// print("1. 查看个人信息\n");
// print("2. 查看已选课程/任务[功能未实现]\n");
// print("3. 选课\n");
// print("4. 退课\n");
// print("5. 查看成绩/GPA\n");
// print("0. 返回主菜单\n");
// print("======================================================================\n");
void MainController::executeStudentCommand(int choice, const string& studentId) const {
switch(choice) {
    case 1:
        StudentRole* student;
        try{
            student = studentController->getStudentProfile(studentId);
        }catch (std::exception& e){
            std::println("{}",e.what());
            break;
        }
        std::println("{}",student->getProfile());
        delete student;
        break;
    case 2:
        std::println("---已经选择课程---------");
        studentController->getAllCourses(studentId);
        break;
    case 3:{
        std::println("---任务----------------");
        ttBroker->show();
        std::string taskId = InputHelper::getNoEmptyInput("请输入想要选择的任务Id");
        try{
            studentController->enrollStudent(studentId, taskId);
        } catch (std::exception& e) {
            std::println("{}",e.what());
        }
        break;
        }
    case 4:
        std::println("---任务----------------");
        ttBroker->show();
        std::string taskId2 = InputHelper::getNoEmptyInput("请输入想要退课的任务Id");
        try{
            studentController->dropStudent(studentId, taskId2);
        } catch (std::exception& e) {
            std::println("{}",e.what());
        }
        break;


    // case 5:
    // case 0:
}
}

MainController::MainController() {
    std::println("正在启动主控制器...");
    initialize();
    std::println("初始化成功");
}

// 智能指针构造函数参数添加 +++++
void MainController::initialize() {
// 创建数据库管理器
    db = new DataBroker();
    sBroker = new StudentBroker(db);
    tBroker = new TeacherBroker(db);
    ttBroker = new TeachingTaskBroker(db);
    cBroker = new CourseBroker(db);



    studentController = std::make_unique<StudentController>(sBroker,cBroker,ttBroker);
    teacherController = std::make_unique<TeacherController>(tBroker,cBroker,ttBroker);
//  暂时删除秘书控制器，老师也可以安排选课，todo：第二次实现这个教学秘书选课的能力
//   secretaryController = std::make_unique<SecretaryController>();
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

