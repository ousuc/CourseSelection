export module course;
import std;
using std::string;
export class Course{
public:
    Course(string courseId, string name, float credits);
    // 核心业务逻辑方法：
    string getInfo();                     // 获取课程详情
    float getCredits() const noexcept;
    string getId() const noexcept;
    string getName() const noexcept;
private:
    string courseId;
    string name;
    float credits;  //课程对应学分
};

Course::Course(string cId, string Name, float Credits)
:courseId(cId),name(Name),credits(Credits)
{}

string Course::getInfo(){
 return std::format("ID:{} name:{} credits:{}",courseId,name,credits);
}
float Course::getCredits() const noexcept { return credits; }
string Course::getId() const noexcept { return courseId; }
string Course::getName() const noexcept { return name; }
