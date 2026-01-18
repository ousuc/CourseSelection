export module terminalUI;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;

export import maincontroller;
export import InputHelper;
export import TableFormatter;
export import std;

using std::vector;
using std::string;
using std::print;
using std::endl;

export class TerminalUI {
public:
    friend class MainController;
    TerminalUI(MainController* mc);
    void showMainMenu();
    void showStudentMenu(const string& studentId);
    void showTeacherMenu(const string& teacherId);
    void showSecretaryMenu();
    void displayMessage(const string& message);
    void displayError(const string& error);
    string getUserInput(const string& prompt);
    int getMenuSelection(int min, int max);
private:
    MainController* mainController;
};

TerminalUI::TerminalUI(MainController* mc) : mainController(mc) {}

void TerminalUI::showMainMenu() {
    std::system("clear"); // Windows清屏，Linux/Mac替换为"clear"
    print("==================== 选课系统主菜单 ====================\n");
    print("1. 学生登录\n");
    print("2. 教师登录\n");
  //  print("3. 教务秘书登录\n");
    print("0. 退出系统\n");
    print("========================================================\n");

    int choice = InputHelper::getMenuChoice();
    switch (choice) {
        case 1: {
            string studentId = InputHelper::getNoEmptyInput("请输入学生ID：");
            if(mainController->sBroker->findStudentById(studentId))
            {
                showStudentMenu(studentId);
            }else{
                std::println("没有找到对应的学生！");
                std::system("read -n 1 -s -p \"按任意键继续...\"");
                showMainMenu();
            }

            break;
        }
        case 2: {
            string teacherId = InputHelper::getNoEmptyInput("请输入教师ID：");
            if(mainController->tBroker->findTeacherById(teacherId))
            {
                showTeacherMenu(teacherId);
            }else{
                std::println("没有找到对应的老师！");
                std::system("read -n 1 -s -p \"按任意键继续...\"");
                showMainMenu();
            }
            break;
        }
        // 删除秘书
        // case 3:
        //     showSecretaryMenu();
        //     break;
        case 0:
            displayMessage("感谢使用选课系统！");
            std::exit(0);
        default:
            displayError("无效选项，请重新选择！");
            showMainMenu();
    }
}

void TerminalUI::showStudentMenu(const string& studentId) {
    std::system("clear");
    print("==================== 学生功能菜单 [{}] ====================\n",studentId);
    print("1. 查看个人信息\n");
    print("2. 查看已选课程/任务\n");
    print("3. 选课\n");
    print("4. 退课\n");
    // 暂时丢弃查看成绩功能
//    print("5. 查看成绩/GPA\n");
    print("0. 返回主菜单\n");
    print("======================================================================\n");

    int choice = InputHelper::getMenuChoice();
    // 看起来很像工厂模式，但是实际上感觉有问题，因为根本没有对应的函数
    try {
        // todo : 等待实现的代码
        mainController->executeStudentCommand(choice, studentId);
        std::system("read -n 1 -s -p \"按任意键继续...\"");
    } catch (const std::exception& e) {
        displayError(e.what());
    }

    if (choice != 0) showStudentMenu(studentId);
    else showMainMenu();
}

void TerminalUI::showTeacherMenu(const string& teacherId) {
    std::system("clear");
    print("==================== 教师功能菜单 [{}] ====================\n",teacherId);
    print("1. 查看个人信息\n");
    print("2. 查看授课任务\n");
//    print("3. 录入学生成绩\n");
    print("3. 查看任务学生名单\n");
    print("0. 返回主菜单\n");
    print("======================================================================\n");

    int choice = InputHelper::getMenuChoice();
    try {
        //需要实现
        mainController->executeTeacherCommand(choice, teacherId);
        std::system("read -n 1 -s -p \"按任意键继续...\"");
    } catch (const std::exception& e) {
        displayError(e.what());
    }

    if (choice != 0) showTeacherMenu(teacherId);
    else showMainMenu();
}

// 第一次迭代不需要教学秘书
// void TerminalUI::showSecretaryMenu() {
//     std::system("clear");
//     print("==================== 教务秘书功能菜单 ====================\n");
//     print("1. 创建课程\n");
//     print("2. 创建授课任务\n");
//     print("3. 激活/停用课程\n");
//     print("4. 查看所有课程\n");
//     print("0. 返回主菜单\n");
//     print("==========================================================\n");

//     int choice = InputHelper::getMenuChoice();
//     try {
//         mainController->executeSecretaryCommand(choice);
//     } catch (const exception& e) {
//         displayError(e.what());
//     }

//     if (choice != 0) showSecretaryMenu();
//     else showMainMenu();
// }


void TerminalUI::displayMessage(const string& message) {
    print("\n[信息] {}\n" , message );
// 这个是windows的 优化为 linux版本
    //std::system("pause");
    std::system("read -n 1 -s -p \"按任意键继续...\"");
}

void TerminalUI::displayError(const string& error) {
    print("\n[错误]{}\n " ,error );
//   std::system("pause");
    std::system("read -n 1 -s -p \"按任意键继续...\"");
}

std::string TerminalUI::getUserInput(const string& prompt) {
    return InputHelper::getNoEmptyInput(prompt);
}

int TerminalUI::getMenuSelection(int min, int max) {
    int choice;
    do {
        choice = InputHelper::getMenuChoice();
    } while (choice < min || choice > max);
    return choice;
}
