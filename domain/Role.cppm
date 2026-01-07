export module Role;
import std;
export class Role{
public:
    Role(string id,string name,string gender);
    virtual ~Role();

    string getProfile(); //返回个人所有信息组成的字符串
    string getId();   //返回id
    virtual string getRoleType() = 0;//返回用户类型
private:
    string id;
    string name;
    string gender;
};

Role::Role(string id,string name, string gender)
: id(id),name(name),gender(gender)
{}

Role::~Role(){}

string Role::getProfile(){
    return std::format(" ID：{}  Name：{}  Gender：{}",id,name,gender);
}
string Role::getId(){
    return std::format("{}",id);
}
