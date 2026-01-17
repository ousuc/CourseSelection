export module TableFormatter;

export import role;
export import studentRole;
export import teacherRole;
export import secretaryRole;
export import course;
export import teachingTask;
import std;
using std::print;
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
    print("课程ID,课程名称,学分\n");
    print("-------------------------------------------------\n");
    for (const auto& course : courses) {
        print("{} {} {}\n",course->getId(),course->getName(),course->getCredits());
    }
}

void TableFormatter::formatTaskTable(const vector<TeachingTask*>& tasks) {
    print("\n==================== 授课任务列表 ====================\n");
    print("任务ID,课程ID,时间槽,最大容量,已选人数\n ");
    print("-----------------------------------------------------\n");
    for (const auto& task : tasks) {
    // 将最后一个格式化字符串改写为这个得到加入日期
        print("{} {} {} {} {}\n",task->getId(),task->getId(),task->getTimeSlot() ,task->getMaxCapacity(),task->getEnrollStart());
    }
}

void TableFormatter::formatGradeTable(const vector<GradeRecord*>& grades) {
    print("\n==================== 成绩列表 ====================\n");
    print("学生ID,任务ID,成绩\n");
    print("-------------------------------------------------\n");
    for (const auto& grade : grades) {
        print("{} {} {}\n",grade->studentId, grade->taskId,grade->score);
    }
}

// 删除GPA

void TableFormatter::formatStudentTable(const vector<StudentRole*>& students) {
    print("\n==================== 学生列表 ====================\n");
    print("学生ID,姓名");
    print("-------------------------------------------------");
    for (const auto& student : students) {
        print("{} {} \n",student->getId(),student->getName());
    }
}

void TableFormatter::formatTeacherTable(const vector<TeacherRole*>& teachers) {
    print("\n==================== 教师列表 ====================\n");
    print("教师ID,姓名\n");
    print("-------------------------------------------------\n");
    for (const auto& teacher : teachers) {
        print("{} {}\n",teacher->getId(),teacher->getName());
    }
}

