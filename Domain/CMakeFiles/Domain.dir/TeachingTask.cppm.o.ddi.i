# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/TeachingTask.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/TeachingTask.cppm"
export module teachingTask;
import std;
using std::vector;
using std::string;
using std::println;
export class TeachingTask{
public:
    TeachingTask(string taskId,string timeSlot,std::time_t enrollStart,std::time_t enrollEnd,int max);

    bool isFull();
    bool isInEnrollTime();
    bool hasStudent(string studentId);

    bool addStudent(string studentId);
    bool removeStudent(string studentId);
    bool assignTeacher(string teacherId);
    bool hasTimeConflictWithOther(TeachingTask& other);

    string getInfo();
    string getId();
    string getTimeSlot();
    std::time_t getEnrollStart();
    std::time_t getEnrollEnd();
    int getMaxCapacity();
private:
    string taskId;
    string timeSlot;
    std::time_t enrollStart;
    std::time_t enrollEnd;
    int maxCapacity;
    int currentEnrolled;

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
    if (this == &other) return false;
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
