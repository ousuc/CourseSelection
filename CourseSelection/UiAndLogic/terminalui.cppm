export module TerminalUI;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;

export import MainController;
export import InputHelper;
export import TableFormatter;
export import std;

using std::vector;
using std::string;

export class TerminalUI {
public:
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
    system("cls"); // Windows清屏，Linux/Mac替换为"clear"
    print("==================== 选课系统主菜单 ====================\n");
    print("1. 学生登录\n");
    print("2. 教师登录\n");
    print("3. 教务秘书登录\n");
    print("0. 退出系统\n");
    print("========================================================\n");

    int choice = InputHelper::getMenuChoice();
    switch (choice) {
        case 1: {
            string studentId = InputHelper::getNoEmptyInput("请输入学生ID：");
            showStudentMenu(studentId);
            break;
        }
        case 2: {
            string teacherId = InputHelper::getNoEmptyInput("请输入教师ID：");
            showTeacherMenu(teacherId);
            break;
        }
        case 3:
            showSecretaryMenu();
            break;
        case 0:
            displayMessage("感谢使用选课系统！");
            exit(0);
        default:
            displayError("无效选项，请重新选择！");
            showMainMenu();
    }
}

void TerminalUI::showStudentMenu(const string& studentId) {
    system("cls");
    print("==================== 学生功能菜单 [{}] ====================\n",studentId);
    print("1. 查看个人信息\n");
    print("2. 查看已选课程/任务\n");
    print("3. 选课\n");
    print("4. 退课\n");
    print("5. 查看成绩/GPA\n");
    print("0. 返回主菜单\n");
    print("======================================================================\n");

    int choice = InputHelper::getMenuChoice();
    try {
        mainController->executeStudentCommand(choice, studentId);
    } catch (const exception& e) {
        displayError(e.what());
    }

    if (choice != 0) showStudentMenu(studentId);
    else showMainMenu();
}

void TerminalUI::showTeacherMenu(const string& teacherId) {
    system("cls");
    print("==================== 教师功能菜单 [{}] ====================\n",teacherId);
    print("1. 查看个人信息\n");
    print("2. 查看授课任务\n");
    print("3. 录入学生成绩\n");
    print("4. 查看任务学生名单\n");
    print("0. 返回主菜单\n");
    print("======================================================================" << endl;

    int choice = InputHelper::getMenuChoice();
    try {
        mainController->executeTeacherCommand(choice, teacherId);
    } catch (const exception& e) {
        displayError(e.what());
    }

    if (choice != 0) showTeacherMenu(teacherId);
    else showMainMenu();
}

void TerminalUI::showSecretaryMenu() {
    system("cls");
    print("==================== 教务秘书功能菜单 ====================\n");
    print("1. 创建课程\n");
    print("2. 创建授课任务\n");
    print("3. 激活/停用课程\n");
    print("4. 查看所有课程\n");
    print("0. 返回主菜单\n");
    print("==========================================================\n");

    int choice = InputHelper::getMenuChoice();
    try {
        mainController->executeSecretaryCommand(choice);
    } catch (const exception& e) {
        displayError(e.what());
    }

    if (choice != 0) showSecretaryMenu();
    else showMainMenu();
}

void TerminalUI::displayMessage(const string& message) {
    print("\n[信息] {}\n" , message );
    system("pause");
}

void TerminalUI::displayError(const string& error) {
    print("\n[错误]{}\n " ,error );
    system("pause");
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
