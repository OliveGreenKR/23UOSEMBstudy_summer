#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Student_Info {
    string _name;
    double _midterm = 0.0;
    double _final = 0.0;
    vector<double> _homework = vector<double>(0.);

    std::istream& read(std::istream& );
    double grade() const;  //const  : 해당 함수의 호출은 Student_Info의 정보를 바꾸지 않을 것이다.
}; 
