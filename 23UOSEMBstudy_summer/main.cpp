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
    //Ÿ�� �������� �����ؼ� Grad,Core �����ִ� ���Ͽ��� ���� ������ ���α׷� �����.
    

    /* Ÿ�� �������� ������ �κ�
    * 1. �л� ������ �о� �����ϴ� ������ ���ǹ�(students)
    * 2. �л� ������ �о� ���̴� �Ͻ��� ���� ���� ���ǹ�(record)
    * 3. read�Լ�   ->  ���� �Լ��� �ذ� 
    * 4. grade�Լ�  ->  ���� �Լ��� �ذ�
    */

    FASTIO;

    /* 1,2�� �ذ��� �� ��° ���
    * �ڵ� Ŭ����
    * 
    * ���� �����͸� �����ϴ� ���� ��ư�, �Ǽ��� �� ���ɼ��� ����.
    * �̷��� ���輺�� ��� �������ִ� �ڵ� Ŭ������ ����� ����ϴ� ���� ���� �̻����̴�.
    * 
    * �̷��� �������� Ŭ������ ����ϴ� ������� ����
    * Ŭ���� ��ü�� ����ȭ�Ͽ� �̰��� ���� �� ����ϴ� ���ο� Ŭ������ ����� ����� '�ڵ� Ŭ����'��� �Ѵ�.
    */
    
    vector<Core*> students;
    Core* record;

    char ch; //���Ͽ���  Core/Grad�� ������ ���ξ �ִٰ� ����.
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

        delete student; //�Ҵ� ����.

    }

    return 0;
}

