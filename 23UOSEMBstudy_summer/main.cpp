#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <map>
#include <algorithm>
#include "Student_Info.h"
#include "myStr.h"


int main()
{
    FASTIO;
    vector<Student_Info> students;
    Student_Info record;

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


