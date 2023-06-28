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
    double grade() const;  //const  : �ش� �Լ��� ȣ���� Student_Info�� ������ �ٲ��� ���� ���̴�.
}; 
