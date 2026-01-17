export module registrar;

import std;
import maincontroller;
import terminalUI;

export class Registrar {
public:
    static Registrar& getInstance() {
        // 防止外部实例化
        static Registrar instance;
        return instance;
    }

    //禁用一些方法
    Registrar(const Registrar& other) = delete;
    Registrar& operator=(const Registrar& other) = delete;

    void exec();

private:
    Registrar() = default;
    ~Registrar() = default;
};

void Registrar::exec(){
// version one 手动内存管理
        MainController* maincontroller = new MainController();
        maincontroller->initialize();
        TerminalUI* UI = new TerminalUI(maincontroller);

// 启动 查询功能
        UI->showMainMenu();
        delete maincontroller;
        delete UI;
}
