# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/inputhelper.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/inputhelper.cppm"
export module InputHelper;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;
import std;
using std::cin;
using std::vector;
using std::string;


export class InputHelper {
public:

    static int getMenuChoice();
    static string getNoEmptyInput(const string& prompt);
    float getFloatInput(const string& prompt);
    bool getYesNoInput(const string& prompt);
};

int InputHelper::getMenuChoice() {
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

string InputHelper::getNoEmptyInput(const string& prompt) {
    string input;
    do {
        print("{}", prompt);
        getline(cin, input);
    } while (input.empty());
    return input;
}

float InputHelper::getFloatInput(const string& prompt) {
    float val;
    print("{}", prompt);
    cin >> val;
    cin.ignore();
    return val;
}

bool InputHelper::getYesNoInput(const string& prompt) {
    string input;
    do {
        print("{} (y/n): " ,prompt);
        getline(cin, input);
    } while (input != "y" && input != "n");
    return input == "y";
}
