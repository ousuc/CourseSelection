# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/SecretaryRole.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/SecretaryRole.cppm"
export module secretaryRole;
import std;
import role;
using std::string;
using std::vector;
export class SecretaryRole: public Role{
public:
    SecretaryRole(string id,string name,string gender);
    virtual string getRoleType()override;
    bool addManagedTask(std::string taskId);
    bool removeManagedTask(const string taskId);
    bool hasManagedTask(const string taskId);
private:
    vector<string> managedTaskIds;
};

SecretaryRole::SecretaryRole(string id,string name,string gender)
:Role(id,name,gender)
{}
string SecretaryRole::getRoleType(){
    return std::format("secretary");
}
bool SecretaryRole::addManagedTask(std::string taskId) {

    if (hasManagedTask(taskId)) {
        return false;
    }

    managedTaskIds.emplace_back(taskId);
    return true;
}
bool SecretaryRole::removeManagedTask(const string taskId) {
    auto it = std::ranges::find(managedTaskIds, taskId);
    if (it == managedTaskIds.end()) {
        std::println("未找到对应task!");
        return false;
    }
    managedTaskIds.erase(it);
    return true;
}

bool SecretaryRole::hasManagedTask(const string taskId){
    return std::ranges::find(managedTaskIds, taskId) != managedTaskIds.end();
}
