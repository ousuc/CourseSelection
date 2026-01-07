export module course;
import std;
using std::string;
export class Course {
public:
    Course(string courseId, string name, float credits);
    // 核心业务逻辑方法：
    string getInfo();                     // 获取课程详情

private:
    string courseId;
    string name;
    float credits;  //课程对应学分
};

Course::Course(string cId, string name, float credits)
:courseId(cId),name(name),credits(credits)
{}

string Course::getInfo(){
 return std::format("ID:{} name:{} credits:{}",courseId,name,credits);
}
