export module TeachingTask;
import std;

export class Course {
public:
    Course(string courseId, string name, float credits,long long enrollStart, long long enrollEnd);
    // 核心业务逻辑方法：
    string getInfo();                     // 获取课程详情

private:
    string courseId;
    string name;
    float credits;  //课程对应学分
};

Course::Course(string cId, string name, float credits,long long enrollStart, long long enrollEnd)
:courseId(cId),name(name),credits(credits)
{}

string Course::getInfo(){
 return std::format("ID:{} name:{} credits:{}",courseId,name,credits);
}
