export module TableFormatter;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;
import std;

using std::vector;
using std::string;

export class TableFormatter {
public:
    void formatCourseTable(const vector<class Course*>& courses);
    void formatTaskTable(const vector<class TeachingTask*>& tasks);
    void formatGradeTable(const vector<class GradeRecord*>& grades);
    void formatStudentTable(const vector<class StudentRole*>& students);
    void formatTeacherTable(const vector<class TeacherRole*>& teachers);
};

void TableFormatter::formatCourseTable(const vector<Course*>& courses) {
    print("\n==================== 课程列表 ====================\n");
    print("{} {} {}\n",课程ID,课程名称,学分);
    print("-------------------------------------------------\n");
    for (const auto& course : courses) {
        print("{} {} {}\n",course->getCourseId(),course->getName(),course->getCredits());
    }
}

void TableFormatter::formatTaskTable(const vector<TeachingTask*>& tasks) {
    print("\n==================== 授课任务列表 ====================\n");
    print("{} {} {} {} {}\n ",任务ID,课程ID,时间槽,最大容量,已选人数);
    print("-----------------------------------------------------\n");
    for (const auto& task : tasks) {
        print("{} {} {} {} {}\n",task->getId(),task->getCourseId(),task->getTimeSlot() ,task->getMaxCapacity(),task->getCurrentEnrolled());
    }
}

void TableFormatter::formatGradeTable(const vector<GradeRecord*>& grades) {
    print("\n==================== 成绩列表 ====================\n");
    print("{} {} {}\n",学生ID,任务ID,成绩);
    print("-------------------------------------------------\n");
    for (const auto& grade : grades) {
        print("{} {} {}\n",grade->getStudentId(), grade->getTaskId(),grade->getScore());
    }
}

void TableFormatter::formatStudentTable(const vector<StudentRole*>& students) {
    print("\n==================== 学生列表 ====================\n");
    print("{} {} {}\n",学生ID,姓名,GPA);
    print("-------------------------------------------------");
    for (const auto& student : students) {
        print("{} {} {}\n",student->getId(),student->getName(),student->getCurrentGPA());
    }
}

void TableFormatter::formatTeacherTable(const vector<TeacherRole*>& teachers) {
    print("\n==================== 教师列表 ====================\n");
    print("{} {}\n",教师ID,姓名);
    print("-------------------------------------------------\n");
    for (const auto& teacher : teachers) {
        print("{} {}\n",teacher->getId(),teacher->getName());
    }
}

