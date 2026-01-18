export module teachingTask;
import std;
using std::vector;
using std::string;
using std::println;
export class TeachingTask{
public:
    TeachingTask(string taskId,string timeSlot,std::time_t enrollStart,std::time_t enrollEnd,int max);
// 核心业务逻辑方法：
    bool isFull();                             // 容量检查
    bool isInEnrollTime();       //是否在选课时间内
    bool hasStudent(string studentId); //判断是否有该学生

    bool addStudent(string studentId);     // 添加学生
    bool removeStudent(string studentId);      // 移除学生
    bool assignTeacher(string teacherId);  // 分配教师
    bool hasTimeConflictWithOther(TeachingTask& other); // 与某个Task是否存在上课时间冲突

    string getInfo();
    string getId();
    string getTimeSlot();
    std::time_t getEnrollStart();
    std::time_t getEnrollEnd();
    int getMaxCapacity();
private:
    string taskId;
    string timeSlot;  //学期与上课时间段：格式要固定！！
    std::time_t enrollStart;  // 选课开始时间戳
    std::time_t enrollEnd;    // 选课结束时间戳
    int maxCapacity;    //最大选课人数
    int currentEnrolled; //已选人数
    //关联
    string courseId;
    string teacherId;
    vector<string> enrolledStudentIds;
};


TeachingTask::TeachingTask(string TaskId,string TimeSlot,std::time_t EnrollStart,
std::time_t EnrollEnd,int max)
:taskId(TaskId),timeSlot(TimeSlot),enrollStart(EnrollStart),enrollEnd(EnrollEnd),maxCapacity(max),currentEnrolled(0)
{}

bool TeachingTask::isFull(){
    return currentEnrolled >= maxCapacity;
}

bool TeachingTask::isInEnrollTime(){
    std::time_t now = std::time(nullptr);
    return now >= enrollStart && now <= enrollEnd;
}

bool TeachingTask::hasStudent(string studentId){
    auto it = find(enrolledStudentIds.begin(), enrolledStudentIds.end(), studentId);
    if(it != enrolledStudentIds.end()){
        return 1;
    }
    return 0;
}

bool TeachingTask::addStudent(string studentId) {
        if (isFull()){
            println("该task学生容量已满！");
            return false;
        }
        if(hasStudent(studentId)){
            println("该task选课名单中已存在学生！");
            return false;
        }
        if(!isInEnrollTime()){
            println("不在该task选课时间段内！");
            return false;
        }
        enrolledStudentIds.emplace_back(studentId);
        currentEnrolled++;
        return true;

}
bool TeachingTask::removeStudent(string studentId) {
    auto it = find(enrolledStudentIds.begin(), enrolledStudentIds.end(), studentId);
    if (it != enrolledStudentIds.end()){
        enrolledStudentIds.erase(it);
        currentEnrolled--;
        return true;
    }
    println("该task选课名单中不存在该学生！\n");
    return false;
}
bool TeachingTask::assignTeacher(string teacherId) {
    if (teacherId.empty()) return false;
    this->teacherId = teacherId;
    return true;
}
bool TeachingTask::hasTimeConflictWithOther(TeachingTask& other){
    if (this == &other) return false;  // 不与自身冲突
    return timeSlot == other.timeSlot;
}

string TeachingTask::getInfo(){
   auto timeToString = [](long long ts) -> std::string {
        if (ts <= 0) return "未设置";
        std::time_t t = static_cast<std::time_t>(ts);

        std::tm* tm = std::localtime(&t);
        if (!tm) return "时间错误";

        std::ostringstream oss;
        oss << std::put_time(tm, "%Y年%m月%d日");
        return oss.str();
    };

    return std::format("ID:{} 上课时间:{} 学生容量:{} 已选人数:{}  选课时间：{}  至  {}",
    taskId,timeSlot,maxCapacity,currentEnrolled,timeToString(enrollStart),timeToString(enrollEnd));
}

string TeachingTask::getTimeSlot(){ return timeSlot; }
string TeachingTask::getId(){ return taskId; }
std::time_t TeachingTask::getEnrollStart(){ return enrollStart;}
std::time_t TeachingTask::getEnrollEnd(){ return enrollEnd;}
int TeachingTask::getMaxCapacity(){ return maxCapacity;}
