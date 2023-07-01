#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <map>
#include <algorithm>
#include "Student_Info.h"
#include "myStr.h"

bool compare_core_ptrs_name(const Core* p1, const Core* p2) {
    return compare_name(*p1,*p2);
}

int main(int argc, char** argv)
{
    //타입 의존성을 제거해서 Grad,Core 섞여있는 파일에도 동작 가능한 프로그램 만들기.
    

    /* 타입 의존성을 가지는 부분
    * 1. 학생 정보를 읽어 저장하는 벡터의 정의문(students)
    * 2. 학생 정보를 읽어 들이는 일시적 지역 변수 정의문(record)
    * 3. read함수   ->  가상 함수로 해결 
    * 4. grade함수  ->  가상 함수로 해결
    */

    FASTIO;

    /* 1,2를 해결할 첫 번째 방법.
    * 포인터를 다루도록 하기
    */
    
    vector<Core*> students;
    Core* record;

    char ch; //파일에서  Core/Grad를 구분할 접두어가 있다고 가정.
    size_t maxlen = 0;
    while (cin >> ch) {
        if(ch == 'U')
            record =  new Core;
        else
            record = new Grad;
		record->read(cin);
        maxlen = ::max(maxlen, record->name().size());
        students.push_back(record);
    }

    ::sort(students.begin(), students.end(), compare_core_ptrs_name);

    for (auto& student : students) {
        cout << student->name() << string(maxlen+1-student->name().size(), ' ');

        try {
            double final_grade = student->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec) << endl;
        }
        catch (domain_error e) {
            cout << e.what() << endl;
        }

        delete student; //할당 해제.

        /*
        * 실제로 Grad를 가리키더라도, Core* 의 할당을 해제해야함...
        * 
        * >> 가상 소멸자 사용하기
        * 
        * 가상 소멸자를 사용하면, 해당 포인터가 실제로 가리키는 객체 타입에 따라 실행하는 소멸자가 결정된다.
        * 따라서 시스템이 반환하는 메모리 타입도 포인터가 가리키는 실제 객체 타입에 따라 결정됨.
        */
    }

    return 0;
}


