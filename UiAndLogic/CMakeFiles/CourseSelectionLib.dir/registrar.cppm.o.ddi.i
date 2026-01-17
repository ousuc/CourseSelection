# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/registrar.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/registrar.cppm"
export module registrar;

import std;
import maincontroller;
import terminalUI;

export class Registrar {
public:
    static Registrar& getInstance() {

        static Registrar instance;
        return instance;
    }


    Registrar(const Registrar& other) = delete;
    Registrar& operator=(const Registrar& other) = delete;

    void exec();

private:
    Registrar() = default;
    ~Registrar() = default;
};

void Registrar::exec(){

        MainController* maincontroller = new MainController();
        maincontroller->initialize();
        TerminalUI* UI = new TerminalUI(maincontroller);


        UI->showMainMenu();
        delete maincontroller;
        delete UI;
}
