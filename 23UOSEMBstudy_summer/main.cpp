#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision


#include "Student_Info.h"
#include "grade.h"
#include "myStr.h"

int main()
{
    FASTIO;

	vector<string> v;
    string s;
    while (cin >> s) {
        v.push_back(s);
    }

    auto framev = frame(v);

    for (auto& s : framev)
        cout << s << "\n";


    return 0;
}


