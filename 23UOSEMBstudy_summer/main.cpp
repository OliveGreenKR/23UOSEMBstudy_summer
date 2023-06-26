#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision
#include <map>

#include "Student_Info.h"
#include "grade.h"
#include "myStr.h"

int main()
{
    FASTIO;

    string s;
    map<string, int> counters;

    map<string, vector<int>> ret = xref(cin, find_urls);
    map<string, vector<int>> ret = xref(cin); //split

    for (auto& m : ret) {
        cout << m.first << "\n";
    }
    return 0;
}


