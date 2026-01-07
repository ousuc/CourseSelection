export module maincontroller;

import :studentcontroller;
import :teachercontroller;
import :secretarycontroller;
import :coursecontroller;
import :gradecontroller;

export import std;

export class MainController {
public:
    MainController();
    StudentController* getStudentController();
    TeacherController* getTeacherController();
    SecretaryController* getSecretaryController();
    CourseController* getCourseController();
    GradeController* getGradeController();
    void initialize();
private:
    std::unique_ptr<StudentController> studentController;
    std::unique_ptr<TeacherController> teacherController;
    std::unique_ptr<SecretaryController> secretaryController;
    std::unique_ptr<CourseController> courseController;
    std::unique_ptr<GradeController> gradeController;
};

MainController::MainController() {
    initialize();
}

void MainController::initialize() {
    studentController = std::make_unique<StudentController>();
    teacherController = std::make_unique<TeacherController>();
    secretaryController = std::make_unique<SecretaryController>();
    courseController = std::make_unique<CourseController>();
    gradeController = std::make_unique<GradeController>();
}

StudentController* MainController::getStudentController() {
    return studentController.get();
}

TeacherController* MainController::getTeacherController() {
    return teacherController.get();
}

SecretaryController* MainController::getSecretaryController() {
    return secretaryController.get();
}

CourseController* MainController::getCourseController() {
    return courseController.get();
}

GradeController* MainController::getGradeController() {
    return gradeController.get();
}

