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
        v = split(s);
        for (auto& str : v) {
            cout << str << "\n";
        }
    }
    return 0;
}


