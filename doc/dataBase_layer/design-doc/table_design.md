# 表的设计
## 1. Students 表

| 字段名 | 数据类型 | 约束  | 说明  |
| --- | --- | --- | --- |
| id  | VARCHAR(50) | PRIMARY KEY | 学生ID |
| name | VARCHAR(100) | NOT NULL | 姓名  |
| gender | VARCHAR(10) |     | 性别  |
| currentGPA | FLOAT | DEFAULT 0.0 | 当前GPA |
| created_at | TIMESTAMP | DEFAULT CURRENT_TIMESTAMP | 创建时间 |

## 2. Teachers 表

| 字段名 | 数据类型 | 约束  | 说明  |
| --- | --- | --- | --- |
| id  | VARCHAR(50) | PRIMARY KEY | 教师ID |
| name | VARCHAR(100) | NOT NULL | 姓名  |
| gender | VARCHAR(10) |     | 性别  |
| created_at | TIMESTAMP | DEFAULT CURRENT_TIMESTAMP | 创建时间 |

## 3. Courses 表

| 字段名 | 数据类型 | 约束  | 说明  |
| --- | --- | --- | --- |
| id  | VARCHAR(50) | PRIMARY KEY | 课程ID |
| course_code | VARCHAR(50) | UNIQUE NOT NULL | 课程代码 |
| name | VARCHAR(200) | NOT NULL | 课程名称 |
| credits | FLOAT | DEFAULT 3.0 | 学分  |
| department | VARCHAR(100) |     | 开课院系 |
| created_at | TIMESTAMP | DEFAULT CURRENT_TIMESTAMP | 创建时间 |

## 4. Teaching_Tasks 表

| 字段名 | 数据类型 | 约束  | 说明  |
| --- | --- | --- | --- |
| id  | VARCHAR(50) | PRIMARY KEY | 主键ID |
| task_id | VARCHAR(50) | UNIQUE NOT NULL | 教学任务ID |
| course_id | VARCHAR(50) | FOREIGN KEY REFERENCES courses(id) | 课程ID |
| teacher_id | VARCHAR(50) | FOREIGN KEY REFERENCES teachers(id) | 教师ID（可空） |
| time_slot | VARCHAR(100) |     | 上课时间 |
| enroll_start | TIMESTAMP |     | 选课开始时间 |
| enroll_end | TIMESTAMP |     | 选课结束时间 |
| max_capacity | INTEGER | DEFAULT 0 | 最大容量 |
| current_enrolled | INTEGER | DEFAULT 0 | 当前选课人数 |
| created_at | TIMESTAMP | DEFAULT CURRENT_TIMESTAMP | 创建时间 |

## 5. Grades 表

| 字段名 | 数据类型 | 约束  | 说明  |
| --- | --- | --- | --- |
| id  | SERIAL | PRIMARY KEY | 主键ID |
| student_id | VARCHAR(50) | FOREIGN KEY REFERENCES students(id) | 学生ID |
| task_id | VARCHAR(50) | FOREIGN KEY REFERENCES teaching_tasks(task_id) | 教学任务ID |
| score | FLOAT |     | 成绩分数 |
| recorded_by | VARCHAR(50) |     | 录入成绩的教师ID |
| created_at | TIMESTAMP | DEFAULT CURRENT_TIMESTAMP | 创建时间 |
