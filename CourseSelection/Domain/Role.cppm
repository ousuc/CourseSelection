export module role;
import std;
using std::string;
export class Role{
public:
    Role(string id,string name,string gender);
    virtual ~Role();

    string getProfile(); //返回个人所有信息组成的字符串
    string getId();
    string getName() const noexcept;
    string getGender() const noexcept;
    virtual string getRoleType() = 0;//返回用户类型
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
