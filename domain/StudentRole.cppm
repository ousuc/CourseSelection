export module StudentRole;
import std;
import Role;
export class StudentRole: public Role{
public:
    StudentRole(string id,string name,string gender,float currentGPA,vector<string> vec);
    virtual string getRoleType();
    //选课前检查检查时间冲突
    bool canEnroll(const string& newTime,const vector<string>& enrolledTime);
    bool enrollInTask(string taskId);     // 选课
    bool dropTask(string taskId);              // 退课


};
private:
    //vector<string> grades_id;
    vector<string> enrolledTasks_id;  // 已选课程，用于用于时间冲突检查和课程管理
};

StudentRole::StudentRole(string id,string name,string gender,float currentGPA,vector<string> vec)
:Role(id,name,gender),currentGPA(currentGPA),enrolledTasks_id(vec)
{}

string Role::getRoleType(){
    return std::format("student");
}

//参数:要选的新课程时间段，已选课程的时间段
//规则：一个学生不能在同一时间段上两门不同的课
bool Student::canEnroll(const string& newTime,const vector<string>& enrolledTime){
    for(auto&& time :enrolledTime){
        if(newTime == enrolledTime){
            return false;
        }
    }
    return true;
}

bool Student::enrollInTask(string taskId){
//查找是否已选
    auto it = std::find(enrolledTasks_id.begin(),enrolledTasks_id.end(),taskId);
    if(it != enrolledTasks_end()){
        return false;
    }
//若未选
    enrolledTasks_id.emplace_back(taskId);
    return true;
}

bool dropTask(string taskId){
    auto it = find(enrolledTaskIds.begin(), enrolledTaskIds.end(), taskId);
    if (it != enrolledTaskIds.end()){
        enrolledTaskIds.erase(it);
        return true;
    }
    return false;
}
