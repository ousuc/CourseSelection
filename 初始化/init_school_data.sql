-- 1. 创建Students表
CREATE TABLE IF NOT EXISTS Students (
    id VARCHAR(50) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    gender VARCHAR(10),
    currentGPA FLOAT DEFAULT 0.0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 2. 创建Teachers表
CREATE TABLE IF NOT EXISTS Teachers (
    id VARCHAR(50) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    gender VARCHAR(10),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 3. 创建Courses表
CREATE TABLE IF NOT EXISTS Courses (
    id VARCHAR(50) PRIMARY KEY,
    course_code VARCHAR(50) UNIQUE NOT NULL,
    name VARCHAR(200) NOT NULL,
    credits FLOAT DEFAULT 3.0,
    department VARCHAR(100),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 4. 创建Teaching_Tasks表（外键关联Courses、Teachers）
CREATE TABLE IF NOT EXISTS Teaching_Tasks (
    id VARCHAR(50) PRIMARY KEY,
    task_id VARCHAR(50) UNIQUE NOT NULL,
    course_id VARCHAR(50) REFERENCES Courses(id),
    teacher_id VARCHAR(50) REFERENCES Teachers(id),
    time_slot VARCHAR(100),
    enroll_start TIMESTAMP,
    enroll_end TIMESTAMP,
    max_capacity INTEGER DEFAULT 0,
    current_enrolled INTEGER DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 5. 创建Grades表（SERIAL自增主键，外键关联Students、Teaching_Tasks）
CREATE TABLE IF NOT EXISTS Grades (
    id SERIAL PRIMARY KEY,
    student_id VARCHAR(50) REFERENCES Students(id),
    task_id VARCHAR(50) REFERENCES Teaching_Tasks(task_id),
    score FLOAT,
    recorded_by VARCHAR(50),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 插入Students测试数据
INSERT INTO Students (id, name, gender, currentGPA)
VALUES
('STU001', '张三', '男', 3.5),
('STU002', '李四', '女', 3.8),
('STU003', '王五', '男', 3.2),
('STU004', '赵六', '女', 3.9),
('STU005', '钱七', '男', 3.6);

-- 插入Teachers测试数据
INSERT INTO Teachers (id, name, gender)
VALUES
('TEA001', '刘教授', '男'),
('TEA002', '陈老师', '女'),
('TEA003', '张教授', '男'),
('TEA004', '李老师', '女');

-- 插入Courses测试数据
INSERT INTO Courses (id, course_code, name, credits, department)
VALUES
('COU001', 'CS101', '计算机科学导论', 3.0, '计算机学院'),
('COU002', 'MATH20101', '高等数学', 4.0, '数学学院'),
('COU003', 'ENG101', '大学英语', 2.0, '外语学院'),
('COU004', 'PHY301', '大学物理', 3.5, '物理学院'),
('COU005', 'DATA101', '数据结构', 3.0, '计算机学院');

-- 插入Teaching_Tasks测试数据
INSERT INTO Teaching_Tasks (id, task_id, course_id, teacher_id, time_slot, enroll_start, enroll_end, max_capacity, current_enrolled)
VALUES
('TASK001', 'T2023CS10101', 'COU001', 'TEA001', '周一 1-2节', '2024-02-20 08:00:00', '2024-02-27 23:59:59', 60, 45),
('TASK002', 'T2023MATH20101', 'COU002', 'TEA002', '周二 3-4节', '2024-02-21 08:00:00', '2024-02-28 23:59:59', 80, 72),
('TASK003', 'T2023ENG10101', 'COU003', 'TEA003', '周三 5-6节', '2024-02-22 08:00:00', '2024-03-01 23:59:59', 50, 48),
('TASK004', 'T2023PHY30101', 'COU004', 'TEA004', '周四 7-8节', '2024-02-23 08:00:00', '2024-03-02 23:59:59', 70, 65),
('TASK005', 'T2023DATA10101', 'COU005', 'TEA001', '周五 1-2节', '2024-02-24 08:00:00', '2024-03-03 23:59:59', 55, 50);

-- 插入Grades测试数据
INSERT INTO Grades (student_id, task_id, score, recorded_by)
VALUES
('STU001', 'T2023CS10101', 85.5, 'TEA001'),
('STU001', 'T2023MATH20101', 92.0, 'TEA002'),
('STU002', 'T2023CS10101', 88.0, 'TEA001'),
('STU002', 'T2023ENG10101', 95.5, 'TEA003'),
('STU003', 'T2023MATH20101', 76.5, 'TEA002'),
('STU003', 'T2023PHY30101', 81.0, 'TEA004'),
('STU004', 'T2023DATA10101', 89.5, 'TEA001'),
('STU004', 'T2023ENG10101', 93.0, 'TEA003'),
('STU005', 'T2023PHY30101', 87.5, 'TEA004'),
('STU005', 'T2023DATA10101', 91.0, 'TEA001');

-- 数据验证查询（执行后终端直接输出结果）
SELECT '==================== Students 表数据 ====================' AS "验证结果";
SELECT * FROM Students;
SELECT '==================== Teachers 表数据 ====================' AS "验证结果";
SELECT * FROM Teachers;
SELECT '==================== Courses 表数据 ====================' AS "验证结果";
SELECT * FROM Courses;
SELECT '==================== Teaching_Tasks 表数据 ====================' AS "验证结果";
SELECT * FROM Teaching_Tasks;
SELECT '==================== Grades 表数据 ====================' AS "验证结果";
SELECT * FROM Grades;

