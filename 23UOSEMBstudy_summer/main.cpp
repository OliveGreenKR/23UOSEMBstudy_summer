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

    /* 1,2를 해결할 두 번째 방법
    * 핸들 클래스
    * 
    * 직접 포인터를 관리하는 것을 어렵고, 실수를 할 가능성도 높다.
    * 이러한 위험성을 대신 관리해주는 핸들 클래스를 만들어 사용하는 것이 가장 이상적이다.
    * 
    * 이렇게 복잡해진 클래스를 사용하는 방식으로 인해
    * 클래스 객체를 은닉화하여 이것을 관리 및 사용하는 새로운 클래스를 만드는 기술을 '핸들 클래스'라고 한다.
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

    }

    return 0;
}

