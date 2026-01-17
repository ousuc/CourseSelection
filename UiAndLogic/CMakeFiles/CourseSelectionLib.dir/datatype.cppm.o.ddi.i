# 0 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/datatype.cppm"
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "/home/ousuc/作业克隆仓库/克隆/新建文件夹/CourseSelection/UiAndLogic/datatype.cppm"
export module DataTypes;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;
import std;

using std::vector;
using std::string;

export class TaskCreationRequest {
public:
    TaskCreationRequest(const string& cid, const string& tid, const string& cls, const string& sch, int cap);
    string getCourseId() const;
    string getTeacherId() const;
    string getClassroom() const;
    string getSchedule() const;
    int getMaxCapacity() const;
private:
    string courseId;
    string teacherId;
    string classroom;
    string schedule;
    int maxCapacity;
};

export class GradeSubmission {
public:
    GradeSubmission(const string& tid, const string& sid, const string& tskid, float s, const string& com = "");
    string getTeacherId() const;
    string getStudentId() const;
    string getTaskId() const;
    float getScore() const;
    string getComment() const;
private:
    string teacherId;
    string studentId;
    string taskId;
    float score;
    string comment;
};

TaskCreationRequest::TaskCreationRequest(const string& cid, const string& tid, const string& cls, const string& sch, int cap)
    : courseId(cid), teacherId(tid), classroom(cls), schedule(sch), maxCapacity(cap) {}

string TaskCreationRequest::getCourseId() const { return courseId; }
string TaskCreationRequest::getTeacherId() const { return teacherId; }
string TaskCreationRequest::getClassroom() const { return classroom; }
string TaskCreationRequest::getSchedule() const { return schedule; }
int TaskCreationRequest::getMaxCapacity() const { return maxCapacity; }

GradeSubmission::GradeSubmission(const string& tid, const string& sid, const string& tskid, float s, const string& com)
    : teacherId(tid), studentId(sid), taskId(tskid), score(s), comment(com) {}

string GradeSubmission::getTeacherId() const { return teacherId; }
string GradeSubmission::getStudentId() const { return studentId; }
string GradeSubmission::getTaskId() const { return taskId; }
float GradeSubmission::getScore() const { return score; }
string GradeSubmission::getComment() const { return comment; }
