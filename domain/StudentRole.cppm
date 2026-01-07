export module studentRole;
import std;
import role;
using std::string;
using std::vector;
export class StudentRole: public Role{
public:
    StudentRole(string id,string name,string gender);
    virtual string getRoleType();


    bool canEnroll(const string& newTime,const vector<string>& enrolledTime);    //选课前检查检查时间冲突
    bool hasTask(string taskId); //是否选了某门课
    bool enrollInTask(string taskId);     // 选课
    bool dropTask(string taskId);              // 退课
private:
    vector<string> enrolledTasksId;  // 已选课程，用于用于时间冲突检查和课程管理
};

StudentRole::StudentRole(string id,string name,string gender)
:Role(id,name,gender)
{}

string StudentRole::getRoleType(){
    return std::format("student");
}

//参数:要选的新课程时间段，已选课程的时间段
//规则：一个学生不能在同一时间段上两门不同的课
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
//查找是否已选
    if (hasTask(taskId)) return false;
//若未选
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
