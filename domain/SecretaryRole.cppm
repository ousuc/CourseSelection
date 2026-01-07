export module secretaryRole;
import std;
import role;
using std::string;

export class SecretaryRole: public Role{
public:
    SecretaryRole(string id,string name,string gender);
    virtual string getRoleType()override;

};

SecretaryRole::SecretaryRole(string id,string name,string gender)
:Role(id,name,gender)
{}
string SecretaryRole::getRoleType(){
    return std::format("secretary");
}

