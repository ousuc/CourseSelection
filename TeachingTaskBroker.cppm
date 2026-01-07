module;
#include<libpq-fe.h>

export module DataBase:TeachingTaskBroker;
import std;
import :DataBroker;
// 前置声明
class TeachingTask;

export class TeachingTaskBroker{
public:
    TeachingTaskBroker(DataBroker* db);
    ~TeachingTaskBroker();

    bool saveTask(TeachingTask* TeachingTask);
    TeachingTask* findTaskById(std::string id);

    bool addStudentToTask(std::string taskId,std::string studentId);
    bool assignTeacherToTask(std::string taskId, std::string teacherId);
private:
    DataBroker* db;
    std::string tableName;
};


