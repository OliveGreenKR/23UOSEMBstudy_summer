#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <map>
#include <algorithm>
#include "myStr.h"
#include "Student_info.h"
#include "Handle.h"

int main(int argc, char** argv)
{
    FASTIO;

    vector<Ptr<Core>> students;
    Ptr<Core> record;
    size_t maxlen = 0;
    char ch;
    while (cin >> ch){
        if(ch == Student_info::core)
            record = new Core;
        else
            record = new Grad;

        record -> read(cin);
        maxlen =  max(maxlen, record->name().size());
        students.push_back(record);
    }

    ::sort(students.begin(), students.end(),[](const Ptr<Core>&A, const Ptr<Core>& B)
        { return Student_info::compare_name(*A, *B); });

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
    }

    return 0;
}

