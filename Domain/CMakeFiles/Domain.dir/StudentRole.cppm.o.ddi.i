# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/StudentRole.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/StudentRole.cppm"
export module studentRole;
import std;
import role;
using std::string;
using std::vector;
export class StudentRole: public Role{
public:
    StudentRole(string id,string name,string gender);
    virtual string getRoleType();


    bool canEnroll(const string& newTime,const vector<string>& enrolledTime);
    bool hasTask(string taskId);
    bool enrollInTask(string taskId);
    bool dropTask(string taskId);
private:
    vector<string> enrolledTasksId;
};

StudentRole::StudentRole(string id,string name,string gender)
:Role(id,name,gender)
{}

string StudentRole::getRoleType(){
    return std::format("student");
}



bool StudentRole::canEnroll(const string& newTime,const vector<string>& enrolledTime){
    for(auto&& time :enrolledTime){
        if(newTime == time){
            return false;
        }
    }
    return true;
}
bool StudentRole::hasTask(string taskId){
    return find(enrolledTasksId.begin(), enrolledTasksId.end(), taskId) != enrolledTasksId.end();
}

bool StudentRole::enrollInTask(string taskId){

    if (hasTask(taskId)) return false;

    enrolledTasksId.emplace_back(taskId);
    return true;
}

bool StudentRole::dropTask(string taskId){
    auto it = find(enrolledTasksId.begin(), enrolledTasksId.end(), taskId);
    if (it != enrolledTasksId.end()){
        enrolledTasksId.erase(it);
        return true;
    }
    return false;
}
