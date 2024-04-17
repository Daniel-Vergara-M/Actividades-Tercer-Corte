#include "./map.h"

class GradeSystem : public Map<string, Map<string, double>>
{
public:
    GradeSystem(int size) : Map<string, Map<string, double>>(size){};

    void registerGrade(string studentName, string subjectName, double grade)
    {
        Pair<string, Map<string, double>> *studentGrades = this->find(studentName);
        studentGrades->value.insert(subjectName, grade);
    }

    double getGrade(string studentName, string subjectName)
    {
        Pair<string, Map<string, double>> *studentGrades = this->find(studentName);
        return studentGrades->value.get(subjectName);
    }

    double calculateStudentAverage(string studentName)
    {
        Pair<string, Map<string, double>> *studentGrades = this->find(studentName);
        vector<double> grades = studentGrades->value.values();
        double sum = 0;
        for (double grade : grades)
        {
            sum += grade;
        }
        return sum / grades.size();
    }

    double calculateSubjectAverage(string subjectName)
    {
        vector<string> students = this->keys();
        double sum = 0;
        int count = 0;
        for (string student : students)
        {
            Pair<string, Map<string, double>> *studentGrades = find(student);
            if (studentGrades->value.contains(subjectName))
            {
                sum += studentGrades->value.get(subjectName);
                count++;
            }
        }
        return sum / count;
    }
};

int main() {
    GradeSystem gradeSystem(10);
    gradeSystem.insert("Juan", Map<string, double>(10));
    gradeSystem.insert("Pedro", Map<string, double>(10));
    gradeSystem.insert("Juan", Map<string, double>(10));
    gradeSystem.registerGrade("Juan", "Matemáticas", 4.5);
    gradeSystem.registerGrade("Juan", "Ciencias", 3.5);
    gradeSystem.registerGrade("Pedro", "Matemáticas", 3.0);
    gradeSystem.registerGrade("Pedro", "Ciencias", 4.0);
    cout << "Promedio de Juan: " << gradeSystem.calculateStudentAverage("Juan") << endl;
    cout << "Promedio de Pedro: " << gradeSystem.calculateStudentAverage("Pedro") << endl;
    cout << "Promedio en Matemáticas: " << gradeSystem.calculateSubjectAverage("Matemáticas") << endl;
    cout << "Promedio en Ciencias: " << gradeSystem.calculateSubjectAverage("Ciencias") << endl;
    return 0;
}