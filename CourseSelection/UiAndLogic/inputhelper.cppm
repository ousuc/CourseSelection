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

// advice： 我推荐这个换成这个工具类，不过不换也行
export class InputHelper {
public:
// 修改函数为静态方法
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

