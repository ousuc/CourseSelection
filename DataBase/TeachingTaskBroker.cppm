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

    bool saveTask(TeachingTask* teachingTask);
    TeachingTask* findTaskById(const std::string& id);

    bool addStudentToTask(const std::string& taskId,const std::string& studentId);
    bool assignTeacherToTask(const std::string& taskId, const std::string& teacherId);
private:
    DataBroker* db;
    const std::string& tableName;
};

TeachingTaskBroker::TeachingTaskBroker(DataBroker* db):
    db(db),tableName("teaching_tasks")
{}

bool TeachingTaskBroker::saveTask(TeachingTask* teachingTask)
{   
}

TeachingTask* findTaskById(const std::string& id)
{}

bool addStudentToTask(const std::string& taskId, const std::string& studentId)
{}

bool assignTeacherToTask(const string& taskId, const std::string& teacherId)
{}

