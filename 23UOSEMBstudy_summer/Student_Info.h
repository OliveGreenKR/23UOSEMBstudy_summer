#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Student_Info {
    string name;
    double midterm = 0;
    double final = 0;
    vector<double> hw = vector<double>(0.f);
}; //dont forget to add ';'

bool compare_name(const Student_Info& A, const Student_Info& B);

istream& read_hw(istream& in, OUT vector<double>& hws);
istream& read_student(istream& in, OUT Student_Info& student);

bool compare_name(const Student_Info& A, const Student_Info& B);
