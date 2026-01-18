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
    // 检查是否已管理该任务
    if (hasManagedTask(taskId)) {
        return false;
    }
    // 添加任务
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
