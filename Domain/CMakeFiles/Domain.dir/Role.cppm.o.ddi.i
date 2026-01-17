# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/Role.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/Domain/Role.cppm"
export module role;
import std;
using std::string;
export class Role{
public:
    Role(string id,string name,string gender);
    virtual ~Role();

    string getProfile();
    string getId();
    string getName() const noexcept;
    string getGender() const noexcept;
    virtual string getRoleType() = 0;
private:
    string id;
    string name;
    string gender;
};

Role::Role(string Id,string Name, string Gender)
: id(Id),name(Name),gender(Gender)
{}

Role::~Role(){}

string Role::getProfile(){
    return std::format(" ID：{}  Name：{}  Gender：{}",id,name,gender);
}
string Role::getId(){
    return std::format("{}",id);
}
string Role::getName() const noexcept{ return name; }
string Role::getGender() const noexcept{ return gender; }
