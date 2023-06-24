#include "pch.h"
#include <iostream>
#include <iomanip>  //setprecision


#include "Student_Info.h"
#include "grade.h"
#include "myStr.h"

int main()
{
    FASTIO

    string s;

    while (getline(cin, s)) {
        vector<string> v = split(s);

        for (auto& word : v)
            cout << word << endl;
    }

    s.clear();

    while (cin >> s) {
        cout << s << "\n";
    }

    return 0;
}


