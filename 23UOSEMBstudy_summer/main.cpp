#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <map>
#include <algorithm>
#include "Student_Info.h"
#include "myStr.h"


int main(int argc, char** argv)
{
    //타입 의존성을 제거해서 Grad,Core 섞여있는 파일에도 동작 가능한 프로그램 만들기.
    

    /* 타입 의존성을 가지는 부분
    * 1. 학생 정보를 읽어 저장하는 벡터의 정의문
    * 2. 학생 정보를 읽어 들이는 일시적 지역 변수 정의문
    * 3. read함수
    * 4. grade함수
    */

    FASTIO;
    
    vector<Core> students;
    Core record;

    size_t maxlen = 0;
    while (record.read(cin)) {
        maxlen = ::max(maxlen, record.name().size());
        students.push_back(record);
    }

    ::sort(students.begin(), students.end(), compare_name);

    for (auto& student : students) {
        cout << student.name() << string(maxlen+1-student.name().size(), ' ');

        try {
            double final_grade = student.grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec) << endl;
        }
        catch (domain_error e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}


