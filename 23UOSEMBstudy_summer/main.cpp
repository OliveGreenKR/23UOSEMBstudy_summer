#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <ios>      //streamsize
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "grade.h"
#include "Student_Info.h"

using namespace std;

bool operator < (Student_Info& A, Student_Info& B) {  // 성적순으로 학생을 sorting 가능(오름차순)
    return grade(A) < grade(B);
}

int main()
{

    vector<Student_Info> students;
    Student_Info record;

    while (read_student(cin, record)) {
        students.push_back(record);
    }
    
    //::sort(students.begin(), students.end()); //성적순
    ::sort(students.begin(), students.end(), compare_name); //이름순

    for (auto& s : students) {
        cout << s.name << "\n";
        try {
            double final_grade = grade(s);
            streamsize prec = cout.precision();

            cout << setprecision(3) << final_grade << setprecision(prec);
        }
        catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }
    return 0;
}


