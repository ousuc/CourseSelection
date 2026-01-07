export module TeacherRole;
import std;
import Role;
export class TeacherRole : public Role{
public:
    // 核心业务逻辑方法：
    bool assignToTask(TeachingTask* task);                         // 接受授课任务
    bool inputStudentGrade(StudentRole* student, TeachingTask* task, float score);  // 录入成绩
    int getTeachingWorkload();                                     // 计算工作量
    vector<StudentRole*> getClassStudents(string taskId);          // 获取班级花名册

    virtual string getRoleType();
    virtual string getSpecificId();
private:
    string department;      // 院系，用于课程分配
    vector<TeachingTask*> assignedTasks;  // 授课任务，用于工作量计算和时间安排

};
