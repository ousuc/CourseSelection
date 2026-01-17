# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/Course.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/Course.cppm"
export module course;
import std;
using std::string;
export class Course{
public:
    Course(string courseId, string name, float credits);

    string getInfo();
    float getCredits() const noexcept;
    string getId() const noexcept;
    string getName() const noexcept;
private:
    string courseId;
    string name;
    float credits;
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
